#include "MainVSSWindow.h"
#include "ui_MainVSSWindow.h"
#include <cmath>
#include <iostream>

MainVSSWindow::MainVSSWindow(QWidget *parent)
  : QMainWindow(parent),
    m_ui(new Ui::MainVSSWindow),
    m_mainWindowFrameTimer(new QTimer(this)),
    m_visionTimer(new QLabel()){
  m_ui->setupUi(this);
  this->readMainWindowConfig();

  setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
  qApp->installEventFilter(this);
  // Baseado na quantidade de jogadores.
  auto &robotLayout = m_ui->verticalLayout_3;

  for (size_t i = 0; i < MAX_PLAYERS; i++) {
    auto &widget = m_robotWidgets[i];


    widget = new RobotWidget(i, m_ui->scrollAreaWidgetContents);

    robotLayout->addWidget(widget);

    if (i + 1 < MAX_PLAYERS) {
      auto &line = m_robotLines[i];
      line = new QFrame(m_ui->scrollAreaWidgetContents);
      robotLayout->addWidget(line);
    }
  }

  rebuildRobotsScrollArea();
  connect(m_mainWindowFrameTimer, SIGNAL(timeout()), this, SLOT(update()));
  m_mainWindowFrameTimer->start(30);
  this->m_cameraCapture = true;
  this->m_videoCapture = false;
  this->m_firstTimeOpeningCamera = false;
  this->m_isRecording = false;
  this->m_cameraDialog = nullptr;
  this->m_visionDialog = nullptr;
  // this->m_maggicSegmentationDialog = nullptr;
  this->m_fieldDialog = nullptr;
  m_visionTimer->setFixedWidth(250);
  statusBar()->addWidget(m_visionTimer);
  getHalfFromFile();

  if (vss.getHalf() == 0) {
    m_ui->halfPushButton->setChecked(true);
  } else {
    m_ui->halfPushButton->setChecked(false);
  }

  this->m_ui->cameraIndexComboBox->installEventFilter(this);
  this->m_ui->cameraIndexComboBox->clear();
  std::vector<int> cameraListAux =
    CameraManager::singleton().returnCameraList();

  for (size_t i = 0; i < cameraListAux.size(); i++) {
    this->m_ui->cameraIndexComboBox->addItem(QString::number(cameraListAux[i]));
  }

  this->m_ui->cameraIndexComboBox->setCurrentText(QString::number(this->_mainWindowConfig["camIdx"].toString().toInt()));
  CameraManager::singleton().setCameraIndex(this->_mainWindowConfig["camIdx"].toString().toInt());

  this->m_maggicSegmentationDialog = new MaggicSegmentationDialog();
  initColors();
  Field::set3x3();
  this->m_ui->DistortionComboBox->setCurrentText("ELP-USB");
}

void MainVSSWindow::initColors() {
  QFile file(SECONDARY_COLOR_FILE);

  if (!file.open(QIODevice::ReadOnly)) {
    std::cout << "Couldn't open file : " << SECONDARY_COLOR_FILE << std::endl;
    exit(1);
  }

  QByteArray data = file.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(data));
  m_secondaryColorJson = loadDoc.object();
  int teamLabel = m_secondaryColorJson[TEAM_LABEL].toInt();
  // printf("team Label %d\n", teamLabel);
  if (teamLabel == 0) {
    this->on_primaryColor_clicked(false);
    Vision::singleton().setTeamColor(Color::BLUE);
  } else {
    this->on_primaryColor_clicked(true);
    Vision::singleton().setTeamColor(Color::YELLOW);
  }

  this->m_ui->primaryColor->setChecked(teamLabel);
}

MainVSSWindow::~MainVSSWindow() {
  for (size_t i = 0; i < MAX_PLAYERS; i++) {
    auto &widget = m_robotWidgets[i];
    delete widget;

    if (i + 1 < MAX_PLAYERS) {
      auto &line = m_robotLines[i];
      delete line;
    }
  }

  delete m_ui;
  m_mainWindowFrameTimer->stop();
  delete m_mainWindowFrameTimer;
  delete this->m_maggicSegmentationDialog;
}

void MainVSSWindow::selectCorrectFrame() {
  std::string frameType = m_ui->visualizationComboBox->currentText().toLocal8Bit().constData();

  if (frameType == "Original") {
    if (m_ui->cutFieldPushButton->isChecked()) {
        this->m_currentFrameLocker.lock();
      Vision::singleton().getCurrentFrame(m_currentFrame);
      this->m_currentFrameLocker.unlock();
    } else {
        this->m_currentFrameLocker.lock();
      CameraManager::singleton().getCurrentFrame(m_currentFrame);
      this->m_currentFrameLocker.unlock();
    }
  } else if (frameType == "Segmented") {
      this->m_currentFrameLocker.lock();
    Vision::singleton().getSegmentationFrame(m_currentFrame);
    this->m_currentFrameLocker.unlock();
  } else if (frameType == "Tracked") {
    cv::Mat frameAux, frameAux2;
    Vision::singleton().getCurrentFrame(frameAux);
    Vision::singleton().getDetectionFrame(frameAux2);
    cv::resize(frameAux2, frameAux2, frameAux.size());
    cv::Mat aux = vss.frameCopy();
    vss.clearFrame();
    cv::resize(aux, aux, frameAux2.size());
    this->m_currentFrameLocker.lock();
    this->m_currentFrame = frameAux + frameAux2 + aux;
    this->m_currentFrameLocker.unlock();
  } else {
    throw std::runtime_error("Invalid visualization option");
  }

  this->m_rawFrameLocker.lock();
  CameraManager::singleton().getCurrentFrame(m_rawFrame);
  this->m_rawFrameLocker.unlock();
}

void MainVSSWindow::setCameraFrame() {
  resizeFrames();
  cv::Mat cameraFrame;
    this->m_currentFrameLocker.lock();
  if (this->m_currentFrame.empty()) {
    this->m_currentFrame = cv::Mat::zeros(480, 640, CV_8UC3);
  }

  this->m_currentFrame.copyTo(cameraFrame);
  this->m_currentFrameLocker.unlock();

  if (!cameraFrame.empty()) {
    cv::Mat tempFrame = cameraFrame.clone();
    cv::Size newSize(this->m_ui->cameraLabel->width(),
                     this->m_ui->cameraLabel->height());
    cv::resize(tempFrame, tempFrame, newSize);
    cv::cvtColor(tempFrame, tempFrame, cv::COLOR_BGR2RGB);
    QImage qimg2(reinterpret_cast<uchar *>(tempFrame.data), tempFrame.cols, tempFrame.rows,
                 static_cast<int>(tempFrame.step), QImage::Format_RGB888);
    this->m_ui->cameraLabel->setPixmap(QPixmap::fromImage(qimg2));
  }
}

void MainVSSWindow::update() {
  if (m_isCaptureOpen) {
    selectCorrectFrame();
    setCameraFrame();
    record();
  }

  double visionTime = Vision::singleton().getVisionRunTime();
  m_visionTimer->setText(QString("Vision RunTime: ") +
                         QString::number(visionTime, 'f', 2) +
                         QString(" ms"));

  for (auto &widget : m_robotWidgets) {
    widget->update();
  }
  double fps = CameraManager::singleton().getCurrentFPS();
  m_ui->fpsLabel->setText(QString("FPS: ") + QString::number(fps,'f',2));

}

void MainVSSWindow::setFrame(QImage image) {
  m_ui->cameraLabel->setPixmap(QPixmap::fromImage(image));
}

void MainVSSWindow::setFrame() {
  resizeFrames();
  QImage tmp(m_currentFrame.data, m_currentFrame.cols, m_currentFrame.rows,
             static_cast<int>(m_currentFrame.step), QImage::Format_RGB888);
  m_ui->cameraLabel->setPixmap(QPixmap::fromImage(tmp));
}

void MainVSSWindow::clearFrame() {
  m_currentFrame = cv::Mat::zeros(static_cast<int>(Field::size().x), static_cast<int>(Field::size().y), CV_8UC3);
  this->setFrame();
}

void MainVSSWindow::resizeCameraFrame() {
  int height = m_ui->cameraFrame->height();
  int width = m_ui->cameraFrame->width();

  if ((width > height && width != height * 4 / 3) ||
      (height > width && height != width * 3 / 4)) {
    if (width > height) {
      m_ui->cameraLabel->setGeometry((width - height * 4 / 3) / 2, 0,
                                         height * 4 / 3, height);
    } else {
      m_ui->cameraLabel->setGeometry(0, (height - width * 3 / 4) / 2, width,
                                         width * 3 / 4);
    }
  }
}

void MainVSSWindow::resizeSimulationFrame() {
  // fazer para simulacao
}

void MainVSSWindow::resizeFrames() {
  resizeCameraFrame();
  resizeSimulationFrame();
}

void MainVSSWindow::on_capturePushButton_clicked() {
  if (m_ui->capturePushButton->isChecked()) {
    bool openSucceeded = false;

    if (this->m_cameraCapture) {
      openSucceeded = CameraManager::singleton().init(
                        this->m_ui->cameraIndexComboBox->currentText().toStdString()[0] -
                        '0');
    } else if (this->m_videoCapture) {
      openSucceeded = CameraManager::singleton().init(
                        this->m_videoFileName.toLocal8Bit().constData());
    }

    if (openSucceeded) {
      this->m_firstTimeOpeningCamera = true;
      m_ui->calibrateFieldPointspushButton->setEnabled(true);
      m_ui->cameraConfigPushButton->setEnabled(true);
      m_ui->visionInitPushButton->setEnabled(true);
      m_ui->visionConfigurePushButton->setEnabled(true);
      Vision::singleton().resetCorrection();
      if (m_ui->cutFieldPushButton->isChecked()) {
        this->on_cutFieldPushButton_clicked();
      }

      m_isCaptureOpen = true;

      if (this->m_videoCapture) {
        this->m_mainWindowFrameTimer->start(30);
      } else if (this->m_cameraCapture) {
        this->m_mainWindowFrameTimer->start(30);
      }

      emit startCameraUpdate();
      emit enableVisionThread(true);
    } else {
      this->m_ui->capturePushButton->setChecked(false);
      QMessageBox cameraAlert;
      cameraAlert.setText("Problem trying to open the camera!");
      cameraAlert.setInformativeText(
        "Certify that your camera is attached to the computer.");
      cameraAlert.exec();
    }
  } else {
    this->m_mainWindowFrameTimer->stop();
    this->m_isCaptureOpen = false;
    this->m_isRecording = false;
    this->clearFrame();

    this->m_videoRecordManager.release();
    
    m_ui->visionInitPushButton->setEnabled(false);
    m_ui->visionConfigurePushButton->setEnabled(false);
    m_ui->calibrateFieldPointspushButton->setEnabled(false);
    m_ui->cameraConfigPushButton->setEnabled(false);
    m_ui->halfPushButton->setEnabled(false);
    m_ui->startAllPushButton->setChecked(false);
    m_ui->recordPushButton->setChecked(false);

    if (m_ui->visionInitPushButton->isChecked()) {
      m_ui->visionInitPushButton->setChecked(false);
      m_ui->visualizationComboBox->clear();
      m_ui->visualizationComboBox->addItem("Original");
      m_ui->visualizationComboBox->setCurrentIndex(0);
    }
    emit enableVisionThread(false);
    emit pauseCameraUpdate();
  }
}

void MainVSSWindow::on_recordPushButton_clicked(){
  if (this->m_ui->recordPushButton->isChecked() && m_ui->capturePushButton->isChecked()) {
    this->m_ui->recordPushButton->setChecked(true);
    this->m_isRecording = true;
    this->startVideoRecording();
  } else {
    this->m_ui->recordPushButton->setChecked(false);
    this->m_isRecording = false;
    this->m_videoRecordManager.release();
  }
}

void MainVSSWindow::on_cutFieldPushButton_clicked() {
  if (this->m_ui->cutFieldPushButton->isChecked()) {
    //m_ui->visionInitPushButton->setEnabled(true);
    //m_ui->visionConfigurePushButton->setEnabled(true);
    Vision::singleton().resetCorrection();
    this->m_ui->halfPushButton->setEnabled(true);
  } else {
    //if (this->m_ui->visionInitPushButton->isChecked()) {
    //  this->on_visionInitPushButton_clicked();
    //}

    //m_ui->visionInitPushButton->setEnabled(false);
    //m_ui->visionConfigurePushButton->setEnabled(false);
    this->m_ui->startAllPushButton->setChecked(false);
    this->m_ui->halfPushButton->setEnabled(false);

  }

  Vision::singleton().setCorrection(m_ui->cutFieldPushButton->isChecked());
}

void MainVSSWindow::on_visionInitPushButton_clicked() {
  if (!this->m_ui->visionInitPushButton->isChecked()) {
    Vision::singleton().setProcessing(false);
    this->m_ui->visionInitPushButton->setChecked(false);
    this->m_ui->startAllPushButton->setChecked(false);
    m_ui->visualizationComboBox->clear();
    m_ui->visualizationComboBox->addItem("Original");
    m_ui->visualizationComboBox->setCurrentIndex(0);

  } else {
    Vision::singleton().setProcessing(true);
    this->m_ui->visionInitPushButton->setChecked(true);
    m_ui->visualizationComboBox->clear();
    m_ui->visualizationComboBox->addItem("Original");
    m_ui->visualizationComboBox->addItem("Segmented");
    m_ui->visualizationComboBox->addItem("Tracked");
    m_ui->visualizationComboBox->setCurrentIndex(2);
    }

    m_ui->visualizationComboBox->setCurrentText("Tracked");
}


void MainVSSWindow::on_DistortionComboBox_currentIndexChanged(
  const QString &arg1) {
  if (arg1 == "NULL") {
    CameraManager::singleton().setDistortionOption(NULO);
  }

  if (arg1 == "ELP-USB") {
    CameraManager::singleton().setDistortionOption(ELP);
  }
}

void MainVSSWindow::
on_calibrateFieldPointspushButton_clicked()  // Deveria ser apagado para
// evitar memory leak
{
  this->m_fieldDialog = new FieldPointsCalibrateDialog(
    m_ui->capturePushButton->isChecked(), this);
  this->m_fieldDialog->exec();

  if (this->m_fieldDialog->result() == QDialog::Accepted) {
  }

  delete this->m_fieldDialog;
  this->on_cutFieldPushButton_clicked();
}

void MainVSSWindow::on_visionConfigurePushButton_clicked() {
  this->m_visionDialog = new VisionConfigDialog(this->m_videoCapture);

  if (this->m_ui->visionInitPushButton->isChecked()) {
    this->m_visionDialog->setHasStarted(m_ui->visionInitPushButton->isChecked());
  } else {
    this->m_visionDialog->setHasStarted(false);
  }

  this->m_visionDialog->exec();
  //    if (this->m_visionDialog->result() == QDialog::Accepted) {
  //    <<-------------acho que não serve pra nada, só não apaguei por que não
  //    consigo abrir pra conferir
  //    } else {
  //    }
  delete this->m_visionDialog;
}

void MainVSSWindow::on_cameraConfigPushButton_clicked() {
  this->m_cameraDialog = new CameraConfigurationDialog();
  this->m_cameraDialog->exec();
  delete this->m_cameraDialog;
}

void MainVSSWindow::toggleMaggicSegmentationDialog() {
  if (!m_ui->maggicSegmentationButton->isChecked()) {
    m_ui->maggicSegmentationButton->setChecked(true);
    this->m_maggicSegmentationDialog->show();
  } else {
    m_ui->maggicSegmentationButton->setChecked(false);
    this->m_maggicSegmentationDialog->close();
  }
}

void MainVSSWindow::on_maggicSegmentationButton_clicked() {
  this->toggleMaggicSegmentationDialog();
}

void MainVSSWindow::record() {
  if (this->m_videoRecordManager.isOpened()) {
    cv::Mat frame;
    this->m_rawFrameLocker.lock();
    this->m_rawFrame.copyTo(frame);
    this->m_rawFrameLocker.unlock();
    this->m_videoRecordManager.write(frame);  
  }
}

void MainVSSWindow::startVideoRecording() {
  RecordingSettingsDialog settingsDialog;

  if (settingsDialog.exec() == QDialog::Accepted) {
      QString videoFileName = settingsDialog.videoNameLineEdit->text();
      int fps = settingsDialog.fpsSpinBox->value();

      if (videoFileName.isEmpty()) {
          videoFileName = QDateTime::currentDateTime().toString("dd-MM-yyyy_hh-mm-ss");
      }

      QDir().mkdir("../recordings");
      this->m_savedVideofileName = "../recordings/" + videoFileName + ".avi";

      std::cout << "Saving video to: " << this->m_savedVideofileName.toStdString() << std::endl;

      if (!this->m_savedVideofileName.isEmpty()) {
          this->m_videoRecordManager.open(
              this->m_savedVideofileName.toStdString(),
              cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps,
              cv::Size(FRAME_WIDTH_DEFAULT, FRAME_HEIGHT_DEFAULT));
      }

      if (!this->m_videoRecordManager.isOpened()) {
          std::cerr << "Error opening video file!" << std::endl;
          return;
      }

      this->m_firstTimeOpeningCamera = false;
  }else {
    this->m_ui->recordPushButton->setChecked(false);
    this->m_isRecording = false;
    this->m_videoRecordManager.release();    
  }

  record();

}

void MainVSSWindow::on_primaryColor_clicked(bool checked) {
  if (!checked) {
    Vision::singleton().setTeamColor(Color::BLUE);
    Vision::singleton().setDetectionParam(MYTEAM, Color::BLUE);
    Vision::singleton().setDetectionParam(ENEMYTEAM, Color::YELLOW);    
  } else {
    Vision::singleton().setTeamColor(Color::YELLOW);
    Vision::singleton().setDetectionParam(MYTEAM, Color::YELLOW);
    Vision::singleton().setDetectionParam(ENEMYTEAM, Color::BLUE);
  }
  Network::buttonsMessageTeamColor(this->m_ui->primaryColor->isChecked());
  this->saveColorFile();
}

void MainVSSWindow::saveColorFile() {
  QFile file(QString::fromStdString(SECONDARY_COLOR_FILE));

  if (!file.open(
        (QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))) {
    std::cout << "failed to open file : " << SECONDARY_COLOR_FILE << std::endl;
    exit(1);
  }

  QByteArray jsonFile = file.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(jsonFile));
  m_secondaryColorJson = loadDoc.object();
  m_secondaryColorJson[TEAM_LABEL] = m_ui->primaryColor->isChecked() ? 1 : 0;
  QJsonDocument saveDoc(m_secondaryColorJson);
  file.write(saveDoc.toJson());
}

bool MainVSSWindow::eventFilter(QObject *f_object, QEvent *f_event) {
  if (f_event->type() == QEvent::MouseButtonPress && f_object != nullptr) {
    static size_t listSize = 0;
    std::vector<int> cameraListAux =
      CameraManager::singleton().returnCameraList();

    if (listSize != cameraListAux.size()) {
      m_ui->cameraIndexComboBox->clear();

      for (size_t i = 0; i < cameraListAux.size(); i++) {
        m_ui->cameraIndexComboBox->addItem(QString::number(cameraListAux[i]));
      }

      this->m_ui->cameraIndexComboBox->setCurrentText(QString::number(this->_mainWindowConfig["camIdx"].toString().toInt()));
      CameraManager::singleton().setCameraIndex(this->_mainWindowConfig["camIdx"].toString().toInt());


      listSize = cameraListAux.size();
    }
  }

  return false;
}

void MainVSSWindow::on_videoPathBrowsePushButton_clicked() {
  this->m_videoFileName =
    QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(),
                                 tr("Videos (*.mp4 *.avi *.mpeg)"));

  if (!this->m_videoFileName.isEmpty() || this->m_cameraCapture == false) {
    this->m_ui->videoPathBrowsePushButton->setEnabled(true);
    this->m_ui->cameraConfigPushButton->setEnabled(false);
    this->m_ui->videoFileNameLabel->setText(
      QFileInfo(this->m_videoFileName).fileName());
  } else {
    this->m_ui->sourceTab->setCurrentIndex(1);
  }
}

void MainVSSWindow::on_sourceTab_currentChanged(int index) {
  if (index == 0) {
    std::vector<int> cameraListAux =
      CameraManager::singleton().returnCameraList();
    this->m_ui->cameraIndexComboBox->clear();

    for (size_t i = 0; i < cameraListAux.size(); i++)
      this->m_ui->cameraIndexComboBox->addItem(
        QString::number(cameraListAux[i]));

    CameraManager::singleton().setCameraIndex(
      this->m_ui->cameraIndexComboBox->currentText().toInt());
    this->m_videoCapture = false;
    this->m_cameraCapture = true;
    this->m_ui->cameraIndexComboBox->setEnabled(true);
  } else {
    this->m_videoCapture = true;
    this->m_cameraCapture = false;
    this->m_ui->cameraIndexComboBox->setEnabled(false);
  }
}

void MainVSSWindow::rebuildRobotsScrollArea() {
  for (auto &widget : m_robotWidgets) {
    widget->hide();
  }

  for (auto &line : m_robotLines) {
    line->hide();
  }

  size_t numberOfRobots =
    static_cast<size_t>(m_ui->numberOfPlayersSpinBox->value());

  for (size_t i = 0; i < numberOfRobots; i++) {
    auto &widget = m_robotWidgets[i];
    std::string widgetName = "Widget_Robot_" + std::to_string(i);
    widget->setObjectName(QString(widgetName.c_str()));
    widget->setMinimumSize(QSize(200, 150));
    widget->show();

    if (i + 1 < numberOfRobots) {
      auto &line = m_robotLines[i];
      line->setObjectName(QString(("line" + std::to_string(i)).c_str()));
      line->setFrameShape(QFrame::HLine);
      line->setFrameShadow(QFrame::Sunken);
      line->show();
    }
  }

  m_ui->robotsScrollArea->update();
}

void MainVSSWindow::getPointsFromFile() {
  QFile file(QString::fromStdString(FIELDLIMITSPATH));

  if (!file.open((QIODevice::ReadOnly))) {
    std::cout << "failed to open file : " << FIELDLIMITSPATH << std::endl;
    exit(1);
  }

  QByteArray jsonFile = file.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(jsonFile));
  QJsonObject pointsJson = loadDoc.object();
  std::string pointString = "point";
  QJsonObject value;

  for (int i = 1; i <= 4; i++) {
    std::string tempKey = pointString + std::to_string(i);
    value = pointsJson[tempKey.c_str()].toObject();
    m_limitPoints[i - 1].x = value["x"].toInt();
    m_limitPoints[i - 1].y = value["y"].toInt();
  }

  file.close();
}

void MainVSSWindow::savePointsToFile() {
  QFile file(QString::fromStdString(FIELDLIMITSPATH));

  if (!file.open(
        (QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))) {
    std::cout << "failed to open file : " << FIELDLIMITSPATH << std::endl;
    exit(1);
  }

  std::string pointString = "point";
  QJsonObject value;

  for (int i = 1; i <= 4; i++) {
    std::string tempKey = pointString + std::to_string(i);
    QJsonObject pair;
    pair.insert("x", m_limitPoints[i - 1].x);
    pair.insert("y", m_limitPoints[i - 1].y);
    value[tempKey.c_str()] = pair;
  }

  QJsonDocument saveDoc(value);
  QString temp(saveDoc.toJson(QJsonDocument::Compact));
  file.write(saveDoc.toJson());
  file.close();
}

void MainVSSWindow::getHalfFromFile() {
  QFile file(QString::fromStdString(HALF_FILE));

  if (!file.open((QIODevice::ReadOnly))) {
    std::cout << "failed to open file : " << HALF_FILE << std::endl;
    exit(1);
  }

  QByteArray jsonFile = file.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(jsonFile));
  QJsonObject halfJson = loadDoc.object();
  vss.setHalf(halfJson["half"].toInt());
  file.close();
}

void MainVSSWindow::saveHalf() {
  QFile file(QString::fromStdString(HALF_FILE));

  if (!file.open(
        (QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))) {
    std::cout << "failed to open file : " << HALF_FILE << std::endl;
    exit(1);
  }

  QByteArray jsonFile = file.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(jsonFile));
  QJsonObject halfJson = loadDoc.object();
  halfJson["half"] = vss.getHalf();
  QJsonDocument saveDoc(halfJson);
  file.write(saveDoc.toJson());
  file.close();
}

void MainVSSWindow::mirrorLimitPoints() {
  cv::Point aux;
  aux = m_limitPoints[0];
  m_limitPoints[0] = m_limitPoints[2];
  m_limitPoints[2] = aux;
  aux = this->m_limitPoints[1];
  m_limitPoints[1] = m_limitPoints[3];
  m_limitPoints[3] = aux;
}

void MainVSSWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape) {
    this->saveMainWindowConfig();
    this->close();
  }
}

void MainVSSWindow::on_numberOfPlayersSpinBox_valueChanged(int arg1) {
   m_ui->numbetOfPlayersConfirm->setEnabled(arg1 > 0);
}

void MainVSSWindow::on_numbetOfPlayersConfirm_clicked() {
  rebuildRobotsScrollArea();
  m_ui->numbetOfPlayersConfirm->setEnabled(false);
}

void MainVSSWindow::on_fieldSizeComboBox_currentIndexChanged(
  const QString &arg1) {
  if (arg1 == "3x3") {
    Field::set3x3();
  } else if (arg1 == "5x5") {
    Field::set5x5();
  }
}

void MainVSSWindow::on_halfPushButton_clicked() {
  if (vss.getHalf() == 0) {
    vss.setHalf(1);
    this->getPointsFromFile();
    this->mirrorLimitPoints();
    this->savePointsToFile();

    if (m_ui->cutFieldPushButton->isChecked()) {
      Vision::singleton().resetCorrection();
    }

    Vision::singleton().setCorrection(m_ui->cutFieldPushButton->isChecked());
  } else {
    vss.setHalf(0);
    this->getPointsFromFile();
    this->mirrorLimitPoints();
    this->savePointsToFile();

    if (m_ui->cutFieldPushButton->isChecked()) {
      Vision::singleton().resetCorrection();
    }
    Vision::singleton().setCorrection(m_ui->cutFieldPushButton->isChecked());
  }
}

void MainVSSWindow::on_playNNButton_clicked(bool checked)
{
    Network::buttonsMessagePlayNN(checked);
}

void MainVSSWindow::on_stopButton_clicked()
{
   Network::buttonsMessageStop();
}

void MainVSSWindow::readMainWindowConfig()
{
    QFile loadFile("./config.json");
    if (!loadFile.open(QIODevice::ReadOnly)) {
        std::cout <<  "Couldn't open config file ./config.json" << std::endl;
        return ;
      }
   QByteArray savedData = loadFile.readAll();
   QJsonDocument loadDoc(QJsonDocument::fromJson(savedData));
   this->_mainWindowConfig = loadDoc.object();

}

void MainVSSWindow::saveMainWindowConfig()
{
    // Create save file
    QFile saveFile("./config.json");
    if (!saveFile.open(QIODevice::WriteOnly)) {
     std::cout << "Couldn't open save file." << std::endl;
     return ;
    }
    this->_mainWindowConfig["camIdx"] = this->m_ui->cameraIndexComboBox->currentText();
    QJsonDocument saveDoc(this->_mainWindowConfig);
    saveFile.write(saveDoc.toJson());
}

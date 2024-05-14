#include "MainVSSWindow.h"
#include "ui_MainVSSWindow.h"

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
  this->m_videoCapture = false;
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
        this->m_currentFrameLocker.lock();
      Vision::singleton().getCurrentFrame(m_currentFrame);
      this->m_currentFrameLocker.unlock();
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
}

void MainVSSWindow::update() {
  if (m_isCaptureOpen) {
    selectCorrectFrame();
  }

  double visionTime = Vision::singleton().getVisionRunTime();
  m_visionTimer->setText(QString("Vision RunTime: ") +
                         QString::number(visionTime, 'f', 2) +
                         QString(" ms"));

  for (auto &widget : m_robotWidgets) {
    widget->update();
  }
}

void MainVSSWindow::setFrame() {
  resizeFrames();
  QImage tmp(m_currentFrame.data, m_currentFrame.cols, m_currentFrame.rows,
             static_cast<int>(m_currentFrame.step), QImage::Format_RGB888);
}

void MainVSSWindow::clearFrame() {
  m_currentFrame = cv::Mat::zeros(static_cast<int>(Field::size().x), static_cast<int>(Field::size().y), CV_8UC3);
  this->setFrame();
}

void MainVSSWindow::resizeSimulationFrame() {
  // fazer para simulacao
}

void MainVSSWindow::resizeFrames() {
  resizeSimulationFrame();
}

void MainVSSWindow::on_capturePushButton_clicked() {

    this->m_mainWindowFrameTimer->stop();
    this->m_isCaptureOpen = false;
    this->clearFrame();
    m_ui->visionInitPushButton->setEnabled(false);
    m_ui->visionConfigurePushButton->setEnabled(false);
    m_ui->calibrateFieldPointspushButton->setEnabled(false);
    m_ui->halfPushButton->setEnabled(false);
    m_ui->startAllPushButton->setChecked(false);

    if (m_ui->visionInitPushButton->isChecked()) {
      m_ui->visionInitPushButton->setChecked(false);
      m_ui->visualizationComboBox->clear();
      m_ui->visualizationComboBox->addItem("Original");
      m_ui->visualizationComboBox->setCurrentIndex(0);
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

void MainVSSWindow::on_videoPathBrowsePushButton_clicked() {
  this->m_videoFileName =
    QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(),
                                 tr("Videos (*.mp4 *.avi *.mpeg)"));

  if (!this->m_videoFileName.isEmpty()) {
    this->m_ui->videoPathBrowsePushButton->setEnabled(true);
    this->m_ui->videoFileNameLabel->setText(
      QFileInfo(this->m_videoFileName).fileName());
  } else {
    this->m_ui->sourceTab->setCurrentIndex(1);
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
    QJsonDocument saveDoc(this->_mainWindowConfig);
    saveFile.write(saveDoc.toJson());
}

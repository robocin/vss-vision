#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->_saveSecondaryColor = false;
  ui->setupUi(this);
  qApp->installEventFilter(this);

  this->mousePositionLabel = new QLabel();
  this->fpsLabel = new QLabel();
  this->strategyTimeLabel = new QLabel();
  this->visionTimeLabel = new QLabel();
  this->fpsLabel->setFixedWidth(100);
  this->visionTimeLabel->setFixedWidth(250);
  this->strategyTimeLabel->setFixedWidth(250);

  this->statusBar()->addWidget(this->mousePositionLabel);
  this->statusBar()->addWidget(this->fpsLabel);
  this->statusBar()->addWidget(this->strategyTimeLabel);
  this->statusBar()->addWidget(this->visionTimeLabel);

  this->_openCameraFlag = true;
  this->_openVideoFlag = false;
  this->_videoFileName = "";

  this->ui->cameraIndexComboBox->installEventFilter(this);
  this->ui->cameraIndexComboBox->clear();

  std::vector<int> cameraListAux =
      CameraManager::singleton().returnCameraList();
  for (size_t i = 0; i < cameraListAux.size(); i++)
    this->ui->cameraIndexComboBox->addItem(QString::number(cameraListAux[i]));
  CameraManager::singleton().setCameraIndex(
      this->ui->cameraIndexComboBox->currentText().toInt());

  this->_videoFileName = CameraManager::singleton().getLastVideoUrl();

  this->ui->videoFileNameLabel->setText(this->_videoFileName);

  this->initColorBoxes();

  this->_communicationRunning = false;

  this->_isCaptureOpen = false;
  this->_hasVisionStarted = false;
  this->_hasStrategyStarted = false;

  // setting initial state of this->_cameraFrame in function bellow
  this->clearCameraFrame();

  this->_updateMainWindowFrameTimer = new QTimer(this);
  connect(this->_updateMainWindowFrameTimer, SIGNAL(timeout()), this,
          SLOT(updateMainWindow()));

  this->_cameraDialog = NULL;
  this->_visionDialog = NULL;
  this->_maggicSegmentationDialog = NULL;
  this->_fieldDialog = NULL;
  this->_fieldCheck = false;
  this->_bezierLines = false;

  this->_strategyConfigDialogFileName = "Config/Strategy_temp.xml";
  this->_navigationConfigDialogFileName = "Config/Navigation_temp.xml";
  this->_gkConfigDialogFileName = "Config/GK_temp.xml";
  this->_dfConfigDialogFileName = "Config/DF_temp.xml";
  this->_atkConfigDialogFileName = "Config/ATK_temp.xml";
  this->_dfDefenderConfigFileName = "Config/DF_ZAGUEIRO_temp.xml";
  this->_dfMiddleConfigFileName = "Config/DF_MEIO_temp.xml";

  this->_debugFowardEnabled = false;

  this->getHalfFromXML(FIELDLIMITSPATH);
  if (this->_half == 0)
    this->ui->halfPushButton->setChecked(true);
  else
    this->ui->halfPushButton->setChecked(false);

  this->ui->halfPushButton->setEnabled(false);
  this->initColorXML();
  this->_currentFieldIndex = 2;
  this->ui->rolePotentialField3dPushButton->setIcon(QIcon(this->roleIcon[2]));
  on_tabWidget_currentChanged(this->ui->tabWidget->currentIndex());
  on_gameSetDock_dockLocationChanged(Qt::BottomDockWidgetArea);

  new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(close()));

  QTimer::singleShot(30, this, SLOT(resizeCamera()));

  this->_maggicSegmentationDialog = new MaggicSegmentationDialog();
  this->_maggicSegmentationRunning = true;

  this->ui->fps_checkBox->setChecked(false);
  this->ui->fps_checkBox->setEnabled(false);
}

MainWindow::~MainWindow() {
  this->_updateMainWindowFrameTimer->stop();
  delete this->_maggicSegmentationDialog;
  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Escape) {
    this->closeWindow();

  } else if (e->key() == Qt::Key_P &&
             (e->modifiers().testFlag(Qt::ControlModifier))) {
    this->pauseGame();
  }
}

void MainWindow::closeWindow() { this->close(); }

void MainWindow::pauseGame() {}

void MainWindow::on_visionConfigurePushButton_clicked() {
  this->_visionDialog = new VisionConfigDialog(this->_openVideoFlag);
  if (this->ui->visionInitPushButton->isChecked())
    this->_visionDialog->setHasStarted(this->_hasVisionStarted);
  else
    this->_visionDialog->setHasStarted(false);
  this->_visionDialog->exec();
  if (this->_visionDialog->result() == QDialog::Accepted) {
  } else {
  }
  delete this->_visionDialog;
}

void MainWindow::initColorBoxes() {
  QImage img(100, 26, QImage::Format_RGB32);
  QPainter p(&img);
  p.fillRect(img.rect(), Qt::black);

  Qt::GlobalColor colors[] = {Qt::red,  Qt::green,       Qt::magenta,
                              Qt::cyan, Qt::darkMagenta, Qt::darkYellow,
                              Qt::black};

  QImage img2(50, 16, QImage::Format_RGB32);
  QPainter p2(&img2);
  p2.fillRect(img2.rect(), Qt::black);
  QRect rect2 = img2.rect().adjusted(1, 1, -1, -1);

  for (int i = (RedCOL - 4); i <= (ColorStrange - 4); i++) {
    p2.fillRect(rect2, colors[i]);
    this->ui->robot_1_secondaryColorComboBox->addItem("", QColor(Qt::red));
    this->ui->robot_1_secondaryColorComboBox->setItemData(
        i, QPixmap::fromImage(img2), Qt::DecorationRole);

    this->ui->robot_2_secondaryColorComboBox->addItem("", QColor(Qt::red));
    this->ui->robot_2_secondaryColorComboBox->setItemData(
        i, QPixmap::fromImage(img2), Qt::DecorationRole);

    this->ui->robot_3_secondaryColorComboBox->addItem("", QColor(Qt::red));
    this->ui->robot_3_secondaryColorComboBox->setItemData(
        i, QPixmap::fromImage(img2), Qt::DecorationRole);
  }
  this->ui->robot_1_secondaryColorComboBox->setCurrentIndex((ColorStrange - 4));
  this->ui->robot_2_secondaryColorComboBox->setCurrentIndex((ColorStrange - 4));
  this->ui->robot_3_secondaryColorComboBox->setCurrentIndex((ColorStrange - 4));
}

void MainWindow::on_primaryColor_clicked(bool checked) {
  if (!checked) {
    Vision::singleton().setTeamColor(BlueCOL);
    Vision::singleton().setDetectionParam(MYTEAM, BlueCOL);
    Vision::singleton().setDetectionParam(ENEMYTEAM, YellowCOL);
  } else {
    Vision::singleton().setTeamColor(YellowCOL);
    Vision::singleton().setDetectionParam(MYTEAM, YellowCOL);
    Vision::singleton().setDetectionParam(ENEMYTEAM, BlueCOL);
  }
  this->saveColorXML();
}

void MainWindow::on_robot_1_secondaryColorComboBox_currentIndexChanged(
    int RadioIndexbyColor) {
  int sameIndex =
      Vision::singleton().setColorIndex(RadioIndexbyColor + RedCOL, 0);
  if (RadioIndexbyColor != (ColorStrange - RedCOL)) {
    switch (sameIndex) {
      case 1:
        this->ui->robot_2_secondaryColorComboBox->setCurrentIndex(ColorStrange -
                                                                  RedCOL);
        break;
      case 2:
        this->ui->robot_3_secondaryColorComboBox->setCurrentIndex(ColorStrange -
                                                                  RedCOL);
        break;
      default:
        break;
    }
  }
  this->saveColorXML();
}

void MainWindow::on_robot_2_secondaryColorComboBox_currentIndexChanged(
    int RadioIndexbyColor) {
  int sameIndex =
      Vision::singleton().setColorIndex(RadioIndexbyColor + RedCOL, 1);
  if (RadioIndexbyColor != (ColorStrange - RedCOL)) {
    switch (sameIndex) {
      case 0:
        this->ui->robot_1_secondaryColorComboBox->setCurrentIndex(ColorStrange -
                                                                  RedCOL);
        break;
      case 2:
        this->ui->robot_3_secondaryColorComboBox->setCurrentIndex(ColorStrange -
                                                                  RedCOL);
        break;
      default:
        break;
    }
  }
  this->saveColorXML();
}

void MainWindow::on_robot_3_secondaryColorComboBox_currentIndexChanged(
    int RadioIndexbyColor) {
  int sameIndex =
      Vision::singleton().setColorIndex(RadioIndexbyColor + RedCOL, 2);
  if (RadioIndexbyColor != (ColorStrange - RedCOL)) {
    switch (sameIndex) {
      case 0:
        this->ui->robot_1_secondaryColorComboBox->setCurrentIndex(ColorStrange -
                                                                  RedCOL);
        break;
      case 1:
        this->ui->robot_2_secondaryColorComboBox->setCurrentIndex(ColorStrange -
                                                                  RedCOL);
        break;
      default:
        break;
    }
  }
  this->saveColorXML();
}

void MainWindow::on_capturePushButton_clicked() {
  if (this->_isCaptureOpen) {
    this->_updateMainWindowFrameTimer->stop();
    this->_isCaptureOpen = false;
    this->clearCameraFrame();

    ui->visionInitPushButton->setEnabled(false);
    ui->visionConfigurePushButton->setEnabled(false);
    ui->calibrateFieldPointspushButton->setEnabled(false);
    ui->cameraConfigPushButton->setEnabled(false);
    ui->halfPushButton->setEnabled(false);
    ui->startAllPushButton->setChecked(false);

    if (this->_hasVisionStarted) {
      this->ui->visionInitPushButton->setChecked(false);
      ui->visualizationComboBox->removeItem(1);
      ui->visualizationComboBox->removeItem(1);
      ui->visualizationComboBox->removeItem(1);
      ui->visualizationComboBox->setCurrentIndex(0);
      this->_hasVisionStarted = false;
    }

    if (this->_hasStrategyStarted) {
      ui->strategyInitPushButton->setChecked(false);
      ui->strategyInitPushButton->setEnabled(false);
      ui->strategyConfigurePushButton->setEnabled(false);
      this->_hasStrategyStarted = false;
    }

    // this->ui->fps_checkBox->setEnabled(true);

    emit pauseCameraUpdate();

  } else {
    bool openSucceeded = false;

    if (this->_openCameraFlag) {
      openSucceeded = CameraManager::singleton().init(
          this->ui->cameraIndexComboBox->currentText().toStdString()[0] - '0');
    } else if (this->_openVideoFlag) {
      openSucceeded = CameraManager::singleton().init(
          this->_videoFileName.toLocal8Bit().constData());
    }

    if (openSucceeded) {
      this->_firstTimeOpeningCamera = true;
      this->_isRecording = false;
      ui->calibrateFieldPointspushButton->setEnabled(true);
      ui->cameraConfigPushButton->setEnabled(true);

      if (ui->cutFieldPushButton->isChecked()) {
        this->on_cutFieldPushButton_clicked();
      }

      if (this->ui->recordPushButton->isChecked()) {
        this->startVideoRecording();
      }

      this->_isCaptureOpen = true;

      if (this->_openVideoFlag)
        this->_updateMainWindowFrameTimer->start(30);
      else if (this->_openCameraFlag)
        this->_updateMainWindowFrameTimer->start(30);

      this->ui->capturePushButton->setChecked(true);
      // this->ui->fps_checkBox->setEnabled(false);

      emit startCameraUpdate();

    } else {
      this->ui->capturePushButton->setChecked(false);
      QMessageBox cameraAlert;
      cameraAlert.setText("Problem trying to open the camera!");
      cameraAlert.setInformativeText(
          "Certify that your camera is attached to the computer.");
      cameraAlert.exec();
    }
  }
}

void MainWindow::on_LonelyPlayerRole_currentIndexChanged(int role) {
  // Coach::singleton().setLonelyPlayerRole(role);
}

void MainWindow::updateMainWindow() {
  this->ui->fps_checkBox->setChecked(
      CameraManager::singleton().getCaptureFPS() == 60);
  if (this->_isCaptureOpen) {
    // set recording video for deep log correct file positioning
    Vision::singleton().setRecordingVideo(
        this->_videoRecordManager.isOpened() && this->_communicationRunning &&
        this->ui->recordPushButton->isChecked() && this->_isRecording);

    std::string visualizationComboBoxString =
        ui->visualizationComboBox->currentText().toLocal8Bit().constData();

    if (visualizationComboBoxString == "Original") {
      if (this->ui->cutFieldPushButton->isChecked())
        this->_currentFrame = Vision::singleton().getCurrentFrame().clone();
      else
        this->_currentFrame =
            CameraManager::singleton().getCurrentFrame().clone();

    } else if (visualizationComboBoxString == "Segmented") {
      this->_currentFrame = Vision::singleton().getSegmentationFrame();

    } else if (visualizationComboBoxString == "Tracked") {
      cv::Mat frameAux, frameAux2;

      frameAux = Vision::singleton().getCurrentFrame().clone();
      frameAux2 = Vision::singleton().getDetectionFrame();

      cv::resize(frameAux2, frameAux2, frameAux.size());
      this->_currentFrame = frameAux + frameAux2;


    }

    if (this->_hasVisionStarted) {
      this->_robotPositions = Vision::singleton().getRobotPositions();

      this->setRobotInfoInUi();
    }

    this->setCameraFrame();

    if (this->_videoRecordManager.isOpened() && this->_communicationRunning &&
        this->ui->recordPushButton->isChecked() && this->_isRecording) {
      cv::Mat recordedFrame;

      if (this->ui->cutFieldPushButton->isChecked()) {
        recordedFrame = Vision::singleton().getCurrentFrame();
      } else {
        recordedFrame = CameraManager::singleton().getCurrentFrame();
      }

      cv::resize(recordedFrame, recordedFrame,
                 cv::Size(FRAME_WIDTH_DEFAULT, FRAME_HEIGHT_DEFAULT));
      this->_videoRecordManager << recordedFrame;
    }

    QLabel *roleLabels[] = {this->ui->robot1Role, this->ui->robot2Role,
                            this->ui->robot3Role};

    roleLabels[0]->setPixmap(QPixmap(":/image/icon/028-invisibleIcon.png"));
    roleLabels[1]->setPixmap(QPixmap(":/image/icon/028-invisibleIcon.png"));
    roleLabels[2]->setPixmap(QPixmap(":/image/icon/028-invisibleIcon.png"));

    double fps = CameraManager::singleton().getCurrentFPS();
    this->fpsLabel->setText(QString("FPS: ") + QString::number(fps, 'f', 2));

    double visionTime = Vision::singleton().getVisionRunTime();
    this->visionTimeLabel->setText(QString("Vision RunTime: ") +
                                   QString::number(visionTime, 'f', 2) +
                                   QString(" ms"));
  }
}

void MainWindow::on_strategyInitPushButton_clicked() {
  if (this->_hasStrategyStarted) {
    emit this->enableStrategyThread(false);
    ui->strategyInitPushButton->setChecked(false);
    ui->startAllPushButton->setChecked(false);
    this->_hasStrategyStarted = false;
  } else {
    emit this->enableStrategyThread(true);
    ui->strategyInitPushButton->setChecked(true);
    this->_hasStrategyStarted = true;
    // this->ui->startAllPushButton->setChecked(true);
  }
}

void MainWindow::on_strategyConfigurePushButton_clicked() {
}

void MainWindow::setCameraFrame() {
  cv::Mat cameraFrame;
  if (this->_currentFrame.empty())
    this->_currentFrame = cv::Mat::zeros(480, 640, CV_8UC3);
  this->_currentFrame.copyTo(cameraFrame);

  if (!cameraFrame.empty()) {
    cv::Mat tempFrame = cameraFrame.clone();
    cv::Size newSize(this->ui->visualizationLabel->width(),
                     this->ui->visualizationLabel->height());
    cv::resize(tempFrame, tempFrame, newSize);
    cv::cvtColor(tempFrame, tempFrame, CV_BGR2RGB);
    QImage qimg2((uchar *)tempFrame.data, tempFrame.cols, tempFrame.rows,
                 tempFrame.step, QImage::Format_RGB888);
    this->ui->visualizationLabel->setPixmap(QPixmap::fromImage(qimg2));
  } else {
    spdlog::get("General")->warn(
        "You are setting a empty frame to QT Interface (function : "
        "MainWindow::setCameraFrame)");
  }
}

void MainWindow::clearCameraFrame() {
  this->_currentFrame =
      cv::Mat::zeros(Field::size().x, Field::size().y, CV_8UC3);
  this->setCameraFrame();
}

void MainWindow::on_sourceTab_currentChanged(int index) {
  if (index == 0) {
    std::vector<int> cameraListAux =
        CameraManager::singleton().returnCameraList();
    this->ui->cameraIndexComboBox->clear();
    for (size_t i = 0; i < cameraListAux.size(); i++)
      this->ui->cameraIndexComboBox->addItem(QString::number(cameraListAux[i]));
    CameraManager::singleton().setCameraIndex(
        this->ui->cameraIndexComboBox->currentText().toInt());
    this->_openVideoFlag = false;
    this->_openCameraFlag = true;
    this->ui->cameraIndexComboBox->setEnabled(true);
  } else {
    this->_openVideoFlag = true;
    this->_openCameraFlag = false;
    this->ui->cameraIndexComboBox->setEnabled(false);
  }
}

void MainWindow::on_visualizationComboBox_currentIndexChanged(
    const QString &arg1) {
  if (arg1 == "Original") {
    spdlog::get("General")->info("Original Visualization");
  } else if (arg1 == "Segmented") {
    spdlog::get("General")->info("Segmented Visualization");
  } else if (arg1 == "Tracked") {
    spdlog::get("General")->info("Tracked Visualization");
  }
}

void MainWindow::on_calibrateFieldPointspushButton_clicked() {
  this->_fieldDialog =
      new FieldPointsCalibrateDialog(this->_openVideoFlag, this);
  this->_fieldDialog->exec();

  if (this->_fieldDialog->result() == QDialog::Accepted) {
  } else {
  }
  delete this->_fieldDialog;

  this->on_cutFieldPushButton_clicked();
}

void MainWindow::on_cameraConfigPushButton_clicked() {
  this->_cameraDialog = new CameraConfigurationDialog();
  this->_cameraDialog->exec();

  if (this->_cameraDialog->result() == QDialog::Accepted) {
  } else {
  }
  delete this->_cameraDialog;
}

void MainWindow::on_videoPathBrowsePushButton_clicked() {
  this->_videoFileName =
      QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(),
                                   tr("Videos (*.mp4 *.avi *.mpeg)"));

  if (!this->_videoFileName.isEmpty() || this->_openCameraFlag == false) {
    this->ui->videoPathBrowsePushButton->setEnabled(true);
    this->ui->cameraConfigPushButton->setEnabled(false);
    this->ui->videoFileNameLabel->setText(
        QFileInfo(this->_videoFileName).fileName());
  } else {
    this->ui->sourceTab->setCurrentIndex(1);
  }
}

void MainWindow::on_bezierlines_checkbox_clicked(bool checked) {
  this->_bezierLines = checked;
}

void MainWindow::on_cameraIndexComboBox_activated(const QString &arg1) {
  std::stringstream ss;
  int cameraIndex;
  ss << arg1.toLocal8Bit().constData();
  ss >> cameraIndex;
  CameraManager::singleton().setCameraIndex(cameraIndex);
}

void MainWindow::on_cutFieldPushButton_clicked() {
  if (this->ui->cutFieldPushButton->isChecked()) {
    ui->visionInitPushButton->setEnabled(true);
    ui->visionConfigurePushButton->setEnabled(true);
    Vision::singleton().resetCorrection();

    if (this->_hasVisionStarted)
      this->ui->strategyInitPushButton->setEnabled(true);
    else
      this->ui->strategyInitPushButton->setEnabled(false);

    this->ui->halfPushButton->setEnabled(true);

    emit enableVisionThread(true);

  } else {
    if (this->ui->visionInitPushButton->isChecked()) {
      this->on_visionInitPushButton_clicked();
    }

    ui->visionInitPushButton->setEnabled(false);
    ui->visionConfigurePushButton->setEnabled(false);
    this->ui->startAllPushButton->setChecked(false);
    if (this->ui->strategyInitPushButton->isChecked()) {
      this->ui->halfPushButton->setEnabled(true);
      this->on_strategyInitPushButton_clicked();
    }
    this->ui->halfPushButton->setEnabled(false);
    this->ui->strategyInitPushButton->setEnabled(false);

    emit enableVisionThread(false);
  }

  Vision::singleton().setCorrection(ui->cutFieldPushButton->isChecked());
}

void MainWindow::on_visionInitPushButton_clicked() {
  if (this->_hasVisionStarted) {
    Vision::singleton().setProcessing(false);
    this->ui->visionInitPushButton->setChecked(false);
    this->ui->startAllPushButton->setChecked(false);
    ui->visualizationComboBox->removeItem(1);
    ui->visualizationComboBox->removeItem(1);
    ui->visualizationComboBox->setCurrentIndex(0);
    this->_hasVisionStarted = false;
    ui->strategyInitPushButton->setEnabled(false);
    ui->strategyConfigurePushButton->setEnabled(false);
    this->_hasStrategyStarted = false;
    this->ui->strategyInitPushButton->setChecked(false);
    this->ui->strategyInitPushButton->setEnabled(false);
  } else {
    Vision::singleton().setProcessing(true);
    this->ui->visionInitPushButton->setChecked(true);
    ui->visualizationComboBox->addItem("Segmented");
    ui->visualizationComboBox->addItem("Tracked");
    this->_hasVisionStarted = true;
    if (this->ui->cutFieldPushButton->isChecked())
      ui->strategyInitPushButton->setEnabled(true);
    ui->strategyConfigurePushButton->setEnabled(true);
    ui->visualizationComboBox->setCurrentText("Tracked");
  }
}

void MainWindow::toggleMaggicSegmentationDialog() {
  if (!this->_maggicSegmentationRunning) {
    this->_maggicSegmentationRunning = true;
    ui->maggicSegmentationButton->setChecked(true);
    this->_maggicSegmentationDialog->show();
  } else {
    this->_maggicSegmentationRunning = false;
    ui->maggicSegmentationButton->setChecked(false);
    this->_maggicSegmentationDialog->close();
  }
}

void MainWindow::on_maggicSegmentationButton_clicked() {
  this->toggleMaggicSegmentationDialog();
}

//void MainWindow::setRobotInfoInUi() {
//  for (int i = ROBOT1; i <= ROBOT3; i++) {
//    if (this->_robotPositions[i].isUpdated()) {
//      this->_allyRobotsPosition[i] =
//          this->_robotPositions[i].getPositionCartesian();
//      this->_secColor[i] = this->_robotPositions[i].getColor() - RedCOL;
//    } else {
//      this->_allyRobotsPosition[i] = cv::Point2d(-1.0, -1.0);
//      this->_secColor[i] = ColorStrange - RedCOL;
//    }
//  }

//  this->_robotPositions[ADV1].setEnemyFront();
//  this->_robotPositions[ADV2].setEnemyFront();
//  this->_robotPositions[ADV3].setEnemyFront();

//  this->ui->robot1SpeedLabel->setText(
//      this->getQString(this->_robotPositions[ROBOT1].getObjectSpeed()));
//  this->ui->robot2SpeedLabel->setText(
//      this->getQString(this->_robotPositions[ROBOT2].getObjectSpeed()));
//  this->ui->robot3SpeedLabel->setText(
//      this->getQString(this->_robotPositions[ROBOT3].getObjectSpeed()));

//  this->ui->robot1PositionLabel->setText(
//      this->getQString(this->_allyRobotsPosition[ROBOT1]));
//  this->ui->robot2PositionLabel->setText(
//      this->getQString(this->_allyRobotsPosition[ROBOT2]));
//  this->ui->robot3PositionLabel->setText(
//      this->getQString(this->_allyRobotsPosition[ROBOT3]));
//}

QString MainWindow::getQString(cv::Point2d position) {
  return QString("(" + QString::number(position.x, 'f', 0) + ";" +
                 QString::number(position.y, 'f', 0) + ")");
}

void MainWindow::on_startAllPushButton_clicked(bool checked) {
  if (checked) {
    this->_isCaptureOpen = false;
    this->_hasVisionStarted = false;
    this->_hasStrategyStarted = false;
    this->_communicationRunning = false;
    // Coach::singleton().setPausedGame(true);

    this->on_capturePushButton_clicked();
    if (_isCaptureOpen) {
      this->ui->cutFieldPushButton->setChecked(true);
      this->on_cutFieldPushButton_clicked();
      this->on_visionInitPushButton_clicked();
      this->on_strategyInitPushButton_clicked();
      this->on_communicationPushButton_clicked();
    } else {
      this->ui->startAllPushButton->setChecked(false);
    }

  } else {
    this->_isCaptureOpen = true;
    this->_hasVisionStarted = true;
    this->_hasStrategyStarted = true;
    this->_communicationRunning = true;
    // Coach::singleton().setPausedGame(false);
    this->ui->cutFieldPushButton->setChecked(false);

    this->on_communicationPushButton_clicked();
    this->on_strategyInitPushButton_clicked();
    this->on_visionInitPushButton_clicked();
    this->on_cutFieldPushButton_clicked();
    this->on_capturePushButton_clicked();
    this->ui->capturePushButton->setChecked(false);
  }
}

bool MainWindow::eventFilter(QObject *f_object, QEvent *f_event) {
  if (f_event->type() == QEvent::MouseButtonPress) {
    static size_t listSize = 0;
    std::vector<int> cameraListAux =
        CameraManager::singleton().returnCameraList();
    if (listSize != cameraListAux.size()) {
      this->ui->cameraIndexComboBox->clear();
      for (size_t i = 0; i < cameraListAux.size(); i++)
        this->ui->cameraIndexComboBox->addItem(
            QString::number(cameraListAux[i]));
      CameraManager::singleton().setCameraIndex(
          this->ui->cameraIndexComboBox->currentText().toInt());
      listSize = cameraListAux.size();
    }
  }

  if (f_event->type() == QEvent::MouseMove &&
      f_object == this->ui->visualizationLabel &&
      this->ui->cutFieldPushButton->isChecked()) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(f_event);
    cv::Point positioncm;
    positioncm.x = mouseEvent->x();
    positioncm.y = mouseEvent->y();
    positioncm.x =
        positioncm.x * (170.0 / this->ui->visualizationLabel->width());
    positioncm.y =
        130 - positioncm.y * (130.0 / this->ui->visualizationLabel->height());
    this->mousePositionLabel->setText(
        QString("Mouse Position: (%1,%2)").arg(positioncm.x).arg(positioncm.y));
  }

  return false;
}

void MainWindow::startVideoRecording() {
  if (this->_firstTimeOpeningCamera) {
    this->_savedVideofileName = QFileDialog::getSaveFileName(
        this, tr("Save File"), "/", tr("Videos (*.avi)"));
    Vision::singleton().setDeepLogFileName(
        this->_savedVideofileName.toStdString());
    this->_firstTimeOpeningCamera = false;
  }
}

void MainWindow::record() {
  if (!this->_savedVideofileName.isEmpty()) {
    this->_isRecording = true;
    this->_videoRecordManager.open(
        this->_savedVideofileName.toStdString() + ".avi",
        CV_FOURCC('M', 'J', 'P', 'G'), 30,
        cv::Size(FRAME_WIDTH_DEFAULT, FRAME_HEIGHT_DEFAULT));
    Vision::singleton().recordDeepLog();
  }
}

void MainWindow::saveCurrentVideo() {
  this->_videoRecordManager.release();
  Vision::singleton().closeDeepLog();
}

void MainWindow::on_checkBox_clicked(bool checked) {
  this->_fieldCheck = checked;
}

void MainWindow::on_static_decisions_checkbox_clicked(bool checked) {
  this->_static_decisions = checked;
  // Coach::singleton().setStaticDecisions(this->_static_decisions);
}

void MainWindow::on_halfPushButton_clicked() {
  if (this->_half == 0) {
    this->_half = 1;
    cv::Point aux;

    this->getPointsFromXML(FIELDLIMITSPATH);

    aux = this->_limitPoints[0];
    this->_limitPoints[0] = this->_limitPoints[2];
    this->_limitPoints[2] = aux;
    aux = this->_limitPoints[1];
    this->_limitPoints[1] = this->_limitPoints[3];
    this->_limitPoints[3] = aux;

    cv::FileStorage fs(FIELDLIMITSPATH, cv::FileStorage::WRITE);

    std::string pointString = "point";

    fs << HALF << this->_half;

    for (int i = 1; i <= 4; i++) {
      fs << pointString + std::to_string(i);
      fs << "{";
      fs << "x" << this->_limitPoints[i - 1].x;
      fs << "y" << this->_limitPoints[i - 1].y;
      fs << "}";
    }

    fs.release();

    if (this->ui->cutFieldPushButton->isChecked()) {
      Vision::singleton().resetCorrection();
    }

    Vision::singleton().setCorrection(ui->cutFieldPushButton->isChecked());
  } else {
    this->_half = 0;
    cv::Point aux;

    this->getPointsFromXML(FIELDLIMITSPATH);

    aux = this->_limitPoints[0];
    this->_limitPoints[0] = this->_limitPoints[2];
    this->_limitPoints[2] = aux;
    aux = this->_limitPoints[1];
    this->_limitPoints[1] = this->_limitPoints[3];
    this->_limitPoints[3] = aux;

    cv::FileStorage fs(FIELDLIMITSPATH, cv::FileStorage::WRITE);

    std::string pointString = "point";

    fs << HALF << this->_half;

    for (int i = 1; i <= 4; i++) {
      fs << pointString + std::to_string(i);
      fs << "{";
      fs << "x" << this->_limitPoints[i - 1].x;
      fs << "y" << this->_limitPoints[i - 1].y;
      fs << "}";
    }

    fs.release();
    if (this->ui->cutFieldPushButton->isChecked()) {
      Vision::singleton().resetCorrection();
    }

    Vision::singleton().setCorrection(ui->cutFieldPushButton->isChecked());
  }
}

void MainWindow::getPointsFromXML(std::string path) {
  cv::FileStorage fs(path, cv::FileStorage::READ);
  cv::FileNode n;

  if (!fs.isOpened()) {
    spdlog::get("General")->error("Diretorio não encontrado {}", path);
  }

  std::string pointString = "point";

  for (int i = 1; i <= 4; i++) {
    n = fs[pointString + std::to_string(i)];
    _limitPoints[i - 1].x = (int)n["x"];
    _limitPoints[i - 1].y = (int)n["y"];
  }

  fs.release();
}

void MainWindow::getHalfFromXML(std::string path) {
  cv::FileStorage fs(path, cv::FileStorage::READ);
  cv::FileNode n;

  if (!fs.isOpened()) {
    spdlog::get("General")->error("Diretorio não encontrado {}", path);
  }

  n = fs[OPENCVSTORAGE];
  this->_half = (int)n[HALF];
}

void MainWindow::saveColorXML() {
  if (this->_saveSecondaryColor) {
    cv::FileStorage file(SECONDARY_COLOR_XML, cv::FileStorage::WRITE);
    cv::FileNode n;

    if (!file.isOpened()) {
      spdlog::get("General")->error("Diretorio não encontrado {}",
                                    SECONDARY_COLOR_XML);
    }

    file << ROBOT0_LABEL
         << this->ui->robot_1_secondaryColorComboBox->currentIndex();
    file << ROBOT1_LABEL
         << this->ui->robot_2_secondaryColorComboBox->currentIndex();
    file << ROBOT2_LABEL
         << this->ui->robot_3_secondaryColorComboBox->currentIndex();

    if (this->ui->primaryColor->isChecked())
      file << TEAM_LABEL << 1;
    else
      file << TEAM_LABEL << 0;

    file.release();
  }
}

void MainWindow::initColorXML() {
  cv::FileStorage file(SECONDARY_COLOR_XML, cv::FileStorage::READ);
  cv::FileNode n;

  if (!file.isOpened()) {
    spdlog::get("General")->error("Diretorio não encontrado {}",
                                  SECONDARY_COLOR_XML);
  }

  n = file[OPENCVSTORAGE];
  this->ui->robot_1_secondaryColorComboBox->setCurrentIndex(
      (int)n[ROBOT0_LABEL]);
  this->ui->robot_2_secondaryColorComboBox->setCurrentIndex(
      (int)n[ROBOT1_LABEL]);
  this->ui->robot_3_secondaryColorComboBox->setCurrentIndex(
      (int)n[ROBOT2_LABEL]);

  if ((int)n[TEAM_LABEL] == 0) {
    this->on_primaryColor_clicked(false);
    Vision::singleton().setTeamColor(BlueCOL);
  } else {
    this->on_primaryColor_clicked(true);
    Vision::singleton().setTeamColor(YellowCOL);
  }

  this->ui->primaryColor->setChecked((int)n[TEAM_LABEL]);
  this->_saveSecondaryColor = true;
}

void MainWindow::on_actionExit_triggered() { this->closeWindow(); }

void MainWindow::on_rolePotentialField3dPushButton_clicked() {
  this->_currentFieldIndex = (this->_currentFieldIndex + 1) % 3;
  this->ui->rolePotentialField3dPushButton->setIcon(
      QIcon(this->roleIcon[this->_currentFieldIndex]));
}

void MainWindow::on_tabWidget_currentChanged(int index) {
  if (index == 0) {
    this->ui->view2DgroupBox->setVisible(true);
    this->ui->view3DgroupBox->setVisible(false);
  } else if (index == 1) {
    this->ui->view2DgroupBox->setVisible(false);
    this->ui->view3DgroupBox->setVisible(true);
  } else {
    this->ui->view2DgroupBox->setVisible(false);
    this->ui->view3DgroupBox->setVisible(false);
  }
}

void MainWindow::on_gameSetDock_dockLocationChanged(
    const Qt::DockWidgetArea &area) {
  if (area == Qt::RightDockWidgetArea || area == Qt::LeftDockWidgetArea ||
      area == Qt::NoDockWidgetArea) {
    this->ui->sourceTab->setGeometry(2, -2, 192, 91);
    this->ui->view3DgroupBox->setGeometry(2, 87, 192, 81);
    this->ui->view2DgroupBox->setGeometry(2, 87, 192, 81);
    this->ui->robot1Info->setGeometry(2, 148, 192, 118);
    this->ui->robot2Info->setGeometry(2, 250, 192, 118);
    this->ui->robot3Info->setGeometry(2, 352, 192, 118);
    this->ui->gameSetDock->setMaximumWidth(200);
    this->ui->gameSetDock->setMaximumHeight(500);
    this->ui->gameSetDock->setMinimumWidth(200);
    this->ui->gameSetDock->setMinimumHeight(500);
  } else {
    this->ui->sourceTab->setGeometry(58, 10, 192, 91);
    this->ui->view3DgroupBox->setGeometry(259, 20, 192, 81);
    this->ui->view2DgroupBox->setGeometry(259, 20, 192, 81);
    this->ui->robot1Info->setGeometry(458, -17, 192, 118);
    this->ui->robot2Info->setGeometry(659, -17, 192, 118);
    this->ui->robot3Info->setGeometry(860, -17, 192, 118);
    this->ui->gameSetDock->setMaximumWidth(16777215);
    this->ui->gameSetDock->setMaximumHeight(125);
    this->ui->gameSetDock->setMinimumWidth(170);
    this->ui->gameSetDock->setMinimumHeight(125);
  }
}

void MainWindow::on_actionRight_triggered() {
  addDockWidget(Qt::RightDockWidgetArea, this->ui->controlDock);
}

void MainWindow::on_actionLeft_triggered() {
  addDockWidget(Qt::LeftDockWidgetArea, this->ui->controlDock);
}

void MainWindow::on_actionRight_2_triggered() {
  addDockWidget(Qt::RightDockWidgetArea, this->ui->gameSetDock);
}

void MainWindow::on_actionLeft_2_triggered() {
  addDockWidget(Qt::LeftDockWidgetArea, this->ui->gameSetDock);
}

void MainWindow::on_actionBottom_triggered() {
  addDockWidget(Qt::BottomDockWidgetArea, this->ui->gameSetDock);
}

void MainWindow::on_actionMenu_2_triggered(bool checked) {
  if (checked) {
    this->ui->controlDock->show();
  } else {
    this->ui->controlDock->hide();
  }
}

void MainWindow::on_actionInfo_3_triggered(bool checked) {
  if (checked) {
    this->ui->gameSetDock->show();
  } else {
    this->ui->gameSetDock->hide();
  }
}

void MainWindow::resizeCamera() {
  int h = this->ui->visualizationFrame->height();
  int w = this->ui->visualizationFrame->width();

  if ((w > h && w != h * 4 / 3) || (h > w && h != w * 3 / 4)) {
    if (w > h) {
      this->ui->visualizationLabel->setGeometry((w - h * 4 / 3) / 2, 0,
                                                h * 4 / 3, h);
    } else {
      this->ui->visualizationLabel->setGeometry(0, (h - w * 3 / 4) / 2, w,
                                                w * 3 / 4);
    }
  }

  h = this->size().height();
  w = this->size().width();

  if (this->ui->gameSetDock->height() + this->ui->gameSetDock->y() > h &&
      !this->ui->gameSetDock->isFloating()) {
    addDockWidget(Qt::BottomDockWidgetArea, this->ui->gameSetDock);
  }

  QTimer::singleShot(30, this, SLOT(resizeCamera()));
}

void MainWindow::on_fps_checkBox_clicked(bool checked) {
  CameraManager::singleton().set60fps(checked);
}

void MainWindow::on_DistortionComboBox_currentIndexChanged(
    const QString &arg1) {
  if (arg1 == "NULL") {
    CameraManager::singleton().setDistortionOption(NULO);
  }
  if (arg1 == "ELP-USB") {
    CameraManager::singleton().setDistortionOption(ELP);
  }
}

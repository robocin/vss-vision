#include "segmentationconfigdialog.h"
#include "ui_segmentationconfigdialog.h"

SegmentationConfigDialog::SegmentationConfigDialog(const bool videoFlag,
                                                   QWidget *parent)
    : QDialog(parent), ui(new Ui::SegmentationConfigDialog) {
  ui->setupUi(this);
  this->_calibrationParameters = new ColorInterval[NUMBEROFCOLOR];
  this->_actualColorIndex = 0;
  this->_videoFlag = videoFlag;

  this->_quantization = Vision::singleton().getQuantizationBool();
  ui->QuantizationCheckBox->setChecked(this->_quantization);

  ui->YMinHorizontalSlider->setMinimum(0);
  ui->YMinHorizontalSlider->setMaximum(255);

  ui->UMinHorizontalSlider->setMinimum(0);
  ui->UMinHorizontalSlider->setMaximum(255);

  ui->VMinHorizontalSlider->setMinimum(0);
  ui->VMinHorizontalSlider->setMaximum(255);

  ui->YMaxHorizontalSlider->setMinimum(0);
  ui->YMaxHorizontalSlider->setMaximum(255);

  ui->UMaxHorizontalSlider->setMinimum(0);
  ui->UMaxHorizontalSlider->setMaximum(255);

  ui->VMaxHorizontalSlider->setMinimum(0);
  ui->VMaxHorizontalSlider->setMaximum(255);

  for (int i = 0; i < NUMBEROFCOLOR; i++) {
    ui->selectColorComboBox->addItem(
        QString::fromStdString(this->_colorLabels[i]));
    this->_visibleColors[i] = true;
  }

  this->readFromFile();
  this->attSliders();
  this->_click = false;
  this->initList();

  qApp->installEventFilter(this);
  this->_updateFrameTimer = new QTimer(this);
  connect(this->_updateFrameTimer, SIGNAL(timeout()), this,
          SLOT(updateFrame()));
  if (this->_videoFlag) {
    this->_updateFrameTimer->start(30);
  } else {
    this->_updateFrameTimer->start(30);
  }
  QTimer::singleShot(30, this, SLOT(resizeCamera()));
  this->ui->YUVMaxColorSampleLabel->setVisible(false);
  this->ui->YUVMinColorSampleLabel->setVisible(false);
}

SegmentationConfigDialog::~SegmentationConfigDialog() {
  this->_updateFrameTimer->stop();
  delete this->_updateFrameTimer;
  delete ui;
}

void SegmentationConfigDialog::readFromFile() {
  QFile file(QString::fromStdString(FileConstants::segmentationConfig));

  if (!file.open(QIODevice::ReadOnly)) {
    std::cout << "failed to open file : " << FileConstants::segmentationConfig
              << std::endl;
    exit(1);
  }

  QByteArray jsonFile = file.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(jsonFile));
  QJsonObject json = loadDoc.object();
  this->_grayTrashHoldLevel = json[GRAY_SCALE].toInt();
  QJsonObject value;
  for (int i = 0; i < NUMBEROFCOLOR; i++) {
    std::string key = this->_colorLabels[i];
    value = json[key.c_str()].toObject();
    this->setup(i, value[YMINLABEL].toInt(), value[UMINLABEL].toInt(),
                value[VMINLABEL].toInt(), value[YMAXLABEL].toInt(),
                value[UMAXLABEL].toInt(), value[VMAXLABEL].toInt());
  }
}

void SegmentationConfigDialog::saveInFile() {
  QFile file(QString::fromStdString(FileConstants::segmentationConfig));

  if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate |
                 QIODevice::Text)) {
    std::cout << "failed to open file : " << FileConstants::segmentationConfig
              << std::endl;
    exit(1);
  }

  QByteArray jsonFile = file.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(jsonFile));
  QJsonObject json = loadDoc.object();
  for (int i = 0; i < NUMBEROFCOLOR; i++) {
    std::string label = this->_colorLabels[i];
    QJsonObject parameter;
    parameter.insert(YMAXLABEL, this->_calibrationParameters[i].max.y);
    parameter.insert(UMAXLABEL, this->_calibrationParameters[i].max.u);
    parameter.insert(VMAXLABEL, this->_calibrationParameters[i].max.v);
    parameter.insert(YMINLABEL, this->_calibrationParameters[i].min.y);
    parameter.insert(UMINLABEL, this->_calibrationParameters[i].min.u);
    parameter.insert(VMINLABEL, this->_calibrationParameters[i].min.v);
    json[label.c_str()] = parameter;
  }

  json[GRAY_SCALE] = this->_grayTrashHoldLevel;
  QJsonDocument saveDoc(json);
  file.write(saveDoc.toJson());
  file.close();
}

void SegmentationConfigDialog::setup(int color, int minY, int minU, int minV,
                                     int maxY, int maxU, int maxV) {
  this->_calibrationParameters[color].min.y = minY;
  this->_calibrationParameters[color].min.u = minU;
  this->_calibrationParameters[color].min.v = minV;
  this->_calibrationParameters[color].max.y = maxY;
  this->_calibrationParameters[color].max.u = maxU;
  this->_calibrationParameters[color].max.v = maxV;
}

void SegmentationConfigDialog::attSliders() {
  // Set Current Value in UI
  ui->YMinLabel->setText(QString::number(
      this->_calibrationParameters[this->_actualColorIndex].min.y));
  ui->UMinLabel->setText(QString::number(
      this->_calibrationParameters[this->_actualColorIndex].min.u));
  ui->VMinLabel->setText(QString::number(
      this->_calibrationParameters[this->_actualColorIndex].min.v));
  ui->YMaxLabel->setText(QString::number(
      this->_calibrationParameters[this->_actualColorIndex].max.y));
  ui->UMaxLabel->setText(QString::number(
      this->_calibrationParameters[this->_actualColorIndex].max.u));
  ui->VMaxLabel->setText(QString::number(
      this->_calibrationParameters[this->_actualColorIndex].max.v));
  ui->GrayLevel->setText(QString::number(this->_grayTrashHoldLevel));

  // Set Min, Max and Slider Position
  ui->YMinHorizontalSlider->setSliderPosition(
      this->_calibrationParameters[this->_actualColorIndex].min.y);
  ui->UMinHorizontalSlider->setSliderPosition(
      this->_calibrationParameters[this->_actualColorIndex].min.u);
  ui->VMinHorizontalSlider->setSliderPosition(
      this->_calibrationParameters[this->_actualColorIndex].min.v);
  ui->YMaxHorizontalSlider->setSliderPosition(
      this->_calibrationParameters[this->_actualColorIndex].max.y);
  ui->UMaxHorizontalSlider->setSliderPosition(
      this->_calibrationParameters[this->_actualColorIndex].max.u);
  ui->VMaxHorizontalSlider->setSliderPosition(
      this->_calibrationParameters[this->_actualColorIndex].max.v);
  this->ui->horizontalSlider_grayScale->setSliderPosition(
      this->_grayTrashHoldLevel);
}

void SegmentationConfigDialog::on_ParametersListWidget_clicked() {
  this->readFromFile();
  this->attSliders();
}

void SegmentationConfigDialog::on_YMinHorizontalSlider_valueChanged(int value) {
  ui->YMinLabel->setText(QString::number(value));
  this->_calibrationParameters[this->_actualColorIndex].min.y = value;
}

void SegmentationConfigDialog::on_UMinHorizontalSlider_valueChanged(int value) {
  ui->UMinLabel->setText(QString::number(value));
  this->_calibrationParameters[this->_actualColorIndex].min.u = value;
}

void SegmentationConfigDialog::on_VMinHorizontalSlider_valueChanged(int value) {
  ui->VMinLabel->setText(QString::number(value));
  this->_calibrationParameters[this->_actualColorIndex].min.v = value;
}

void SegmentationConfigDialog::on_YMaxHorizontalSlider_valueChanged(int value) {
  ui->YMaxLabel->setText(QString::number(value));
  this->_calibrationParameters[this->_actualColorIndex].max.y = value;
}

void SegmentationConfigDialog::on_UMaxHorizontalSlider_valueChanged(int value) {
  ui->UMaxLabel->setText(QString::number(value));
  this->_calibrationParameters[this->_actualColorIndex].max.u = value;
}

void SegmentationConfigDialog::on_VMaxHorizontalSlider_valueChanged(int value) {
  ui->VMaxLabel->setText(QString::number(value));
  this->_calibrationParameters[this->_actualColorIndex].max.v = value;
}

void SegmentationConfigDialog::updateFrame() {
  if (Vision::singleton().isCorrectionEnabled()) {
    Vision::singleton().getCurrentFrame(this->_actualFrame);
  } else {
    CameraManager::singleton().getCurrentFrame(this->_actualFrame);
  }

  if (!this->_actualFrame.empty()) {
    this->setOriginalFrameOnScreen();

    this->_actualFrame = this->segmentFrameWithIntervals(this->_actualFrame);

    this->setFrameOnScreen();
  }
}

cv::Mat SegmentationConfigDialog::segmentFrameWithIntervals(cv::Mat frame) {
  RGB colorRGB;
  YUV colorYUV;
  bool haveRecievedLabel = false;
  uchar cutBitsDecimal = 15;

  for (int j = 0; j < frame.rows; ++j) {
    for (int i = 0; i < frame.cols; ++i) {
      colorRGB = frame.ptr<RGB>(j)[i];

      if (this->_quantization) {
        colorRGB.red = colorRGB.red | cutBitsDecimal;
        colorRGB.green = colorRGB.green | cutBitsDecimal;
        colorRGB.blue = colorRGB.blue | cutBitsDecimal;
      }

      if (abs(colorRGB.red - colorRGB.green) < this->_grayTrashHoldLevel &&
          abs(colorRGB.red - colorRGB.blue) < this->_grayTrashHoldLevel &&
          abs(colorRGB.blue - colorRGB.green) < this->_grayTrashHoldLevel) {
        frame.ptr<RGB>(j)[i] = ColorSpace::markerColors[ColorStrange];
      } else {
        colorYUV.y = static_cast<int>(Utils::bound(
            (306 * colorRGB.red + 601 * colorRGB.green + 117 * colorRGB.blue) >>
                10,
            0, 255));
        colorYUV.u = static_cast<int>(Utils::bound(((-172 * colorRGB.red - 340 * colorRGB.green +
                                    512 * colorRGB.blue) >>
                                   10) +
                                      128,
                                  0, 255));
        colorYUV.v = static_cast<int>(Utils::bound(
            ((512 * colorRGB.red - 419 * colorRGB.green - 83 * colorRGB.blue) >>
             10) +
                128,
            0, 255));

        for (int k = 0; k < NUMBEROFCOLOR; k++) {
          if (colorYUV.y >= this->_calibrationParameters[k].min.y &&
              colorYUV.y <= this->_calibrationParameters[k].max.y &&
              colorYUV.u >= this->_calibrationParameters[k].min.u &&
              colorYUV.u <= this->_calibrationParameters[k].max.u &&
              colorYUV.v >= this->_calibrationParameters[k].min.v &&
              colorYUV.v <= this->_calibrationParameters[k].max.v &&
              this->_visibleColors[k]) {
            frame.ptr<RGB>(j)[i] = ColorSpace::markerColors[k];
            haveRecievedLabel = true;
            break;
          }
        }

        if (!haveRecievedLabel) {
          frame.ptr<RGB>(j)[i] = ColorSpace::markerColors[ColorStrange];
        } else {
          haveRecievedLabel = false;
        }
      }
    }
  }

  return frame.clone();
}

void SegmentationConfigDialog::setFrameOnScreen() {
  if (!this->_actualFrame.empty()) {
    cv::Mat tempFrame = this->_actualFrame.clone();
    cv::Size newSize(this->ui->visualizationLabel->width(),
                     this->ui->visualizationLabel->height());
    cv::resize(tempFrame, tempFrame, newSize);
    cv::cvtColor(tempFrame, tempFrame, CV_BGR2RGB);
    if (this->getClick()) {
      this->putZoom(tempFrame);
      if (this->_qpoint.x() + ZOOM_ADJUST_X_MAX <=
              this->ui->visualizationLabel->width() &&
          this->_qpoint.x() - ZOOM_ADJUST_X_MIN >= 0 &&
          this->_qpoint.y() + ZOOM_ADJUST_Y <=
              this->ui->visualizationLabel->height()) {
        cv::Point rect1 = cv::Point(_qpoint.x() - ZOOM_ADJUST_X_MIN,
                                    _qpoint.y() - ZOOM_ADJUST_Y);
        cv::Point rect2 =
            cv::Point(_qpoint.x() + ZOOM_ADJUST_X_MAX, _qpoint.y());
        cv::rectangle(tempFrame, rect1, rect2, cv::Scalar(63, 27, 181));
      }
    }
    QImage qimg2(reinterpret_cast<uchar *>(tempFrame.data), tempFrame.cols, tempFrame.rows,
                 static_cast<int>(tempFrame.step), QImage::Format_RGB888);
    this->ui->visualizationLabel->setPixmap(QPixmap::fromImage(qimg2));
  } else {
    spdlog::get("General")->warn(
        "You are setting a empty frame to QT Interface (function : "
        "SegmentationConfigDialog::setFrameOnScreen)");
  }
}

void SegmentationConfigDialog::on_selectColorComboBox_currentIndexChanged(
    int index) {
  this->_actualColorIndex = index;
  this->attSliders();
}

void SegmentationConfigDialog::on_buttonBox_accepted() {
  this->saveInFile();
  Vision::singleton().resetSegmentation();
  this->_updateFrameTimer->stop();
}

void SegmentationConfigDialog::on_buttonBox_rejected() {
  this->_updateFrameTimer->stop();
}

void SegmentationConfigDialog::putZoom(cv::Mat Frame) {
  this->_zoom = Frame.clone();
  if (this->_qpoint.x() + ZOOM_ADJUST_X_MAX <=
          this->ui->visualizationLabel->width() &&
      this->_qpoint.x() - ZOOM_ADJUST_X_MIN >= 0 &&
      this->_qpoint.y() - ZOOM_ADJUST_Y >= 0 &&
      this->_qpoint.y() + ZOOM_ADJUST_Y <=
          this->ui->visualizationLabel->height()) {
    cv::Point rect1 =
        cv::Point(_qpoint.x() - ZOOM_ADJUST_X_MIN, _qpoint.y() - ZOOM_ADJUST_Y);
    cv::Point rect2 =
        cv::Point(_qpoint.x() + ZOOM_ADJUST_X_MAX, _qpoint.y() + ZOOM_ADJUST_Y);
    cv::Rect roi(rect1, rect2);
    this->_zoom = this->_zoom(roi);
    cv::resize(this->_zoom, this->_zoom, cv::Size(100, 100));
  }
  QImage q_zoom(reinterpret_cast<uchar *>(this->_zoom.data), this->_zoom.cols, this->_zoom.rows,
                static_cast<int>(this->_zoom.step), QImage::Format_RGB888);
  ui->zoomlabel->setPixmap(QPixmap::fromImage(q_zoom));
}

bool SegmentationConfigDialog::eventFilter(QObject *f_object, QEvent *f_event) {
  if (f_object == this->ui->visualizationLabel &&
      f_event->type() == QEvent::MouseMove) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(f_event);
    this->_qpoint = mouseEvent->pos();
    this->_click = true;
  }

  return false;
}

cv::Mat SegmentationConfigDialog::getFrame() {
  cv::Mat ori = this->_actualFrame.clone();
  return ori;
}

bool SegmentationConfigDialog::getClick() {
  bool cli = this->_click;
  return cli;
}

void SegmentationConfigDialog::on_saveSegmentationPushButton_clicked() {
  QString newSegmentationFile = QFileDialog::getSaveFileName(
      this, tr("Save Segmentation XML"), "./Config/Segmentation",
      tr("Vision Segmentation config file (*.xml)"));

  if (newSegmentationFile != nullptr) {
    this->_newSegmentationStdFile = newSegmentationFile.toStdString();
    if (newSegmentationFile.right(4).toStdString() != ".xml") {
      this->_newSegmentationStdFile.append(".xml");
    }
    this->saveInFile();
  }

  this->initList();
}

void SegmentationConfigDialog::initList() {
  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir("./Config/Segmentation/");
  this->ui->ParametersListWidget->clear();

  if (dpdf != nullptr) {
    while ((epdf = readdir(dpdf)) != nullptr) {
      QString newSegmentationFile = epdf->d_name;

      if (newSegmentationFile.right(4) == ".xml") {
        this->ui->ParametersListWidget->addItem(QString(epdf->d_name));
      }
    }
  }
  closedir(dpdf);
}

void SegmentationConfigDialog::on_NoCOLCheckBox_clicked(bool checked) {
  this->_visibleColors[NoCOL] = checked;
}

void SegmentationConfigDialog::on_OrangeCheckBox_clicked(bool checked) {
  this->_visibleColors[OrangeCOL] = checked;
}

void SegmentationConfigDialog::on_BlueCheckBox_clicked(bool checked) {
  this->_visibleColors[BlueCOL] = checked;
}

void SegmentationConfigDialog::on_YellowCheckBox_clicked(bool checked) {
  this->_visibleColors[YellowCOL] = checked;
}

void SegmentationConfigDialog::on_RedCheckBox_clicked(bool checked) {
  this->_visibleColors[RedCOL] = checked;
}

void SegmentationConfigDialog::on_GreenCheckBox_clicked(bool checked) {
  this->_visibleColors[GreenCOL] = checked;
}

void SegmentationConfigDialog::on_PinkCheckBox_clicked(bool checked) {
  this->_visibleColors[PinkCOL] = checked;
}

void SegmentationConfigDialog::on_LightBlueCheckBox_clicked(bool checked) {
  this->_visibleColors[LightBlueCOL] = checked;
}

void SegmentationConfigDialog::on_PurpleCheckBox_clicked(bool checked) {
  this->_visibleColors[PurpleCOL] = checked;
}

void SegmentationConfigDialog::on_ColorStrangeCheckBox_clicked(bool checked) {
  this->_visibleColors[ColorStrange] = checked;
}

void SegmentationConfigDialog::on_checkAll_clicked() {
  for (int i = 0; i < NUMBEROFCOLOR; i++) this->_visibleColors[i] = true;
  this->setAllCheckBoxUi(true);
}

void SegmentationConfigDialog::on_UnCheckAll_clicked() {
  for (int i = 0; i < NUMBEROFCOLOR; i++) this->_visibleColors[i] = false;
  this->setAllCheckBoxUi(false);
}

void SegmentationConfigDialog::setAllCheckBoxUi(bool check) {
  this->ui->NoCOLCheckBox->setChecked(check);
  this->ui->OrangeCheckBox->setChecked(check);
  this->ui->YellowCheckBox->setChecked(check);
  this->ui->BlueCheckBox->setChecked(check);
  this->ui->RedCheckBox->setChecked(check);
  this->ui->GreenCheckBox->setChecked(check);
  this->ui->PinkCheckBox->setChecked(check);
  this->ui->LightBlueCheckBox->setChecked(check);
  this->ui->PurpleCheckBox->setChecked(check);
  this->ui->ColorStrangeCheckBox->setChecked(check);
}

void SegmentationConfigDialog::on_QuantizationCheckBox_clicked(bool checked) {
  this->_quantization = checked;
  Vision::singleton().setQuantizationBool(this->_quantization);
}

void SegmentationConfigDialog::on_pushButton_CloseColor_clicked() {
  this->setup(this->_actualColorIndex, 0, 0, 0, 0, 0, 0);
  this->attSliders();
}

void SegmentationConfigDialog::on_pushButton_OpenColor_clicked() {
  this->setup(this->_actualColorIndex, 0, 0, 0, 255, 255, 255);
  this->attSliders();
}

void SegmentationConfigDialog::setOriginalFrameOnScreen() {
  if (!this->_actualFrame.empty()) {
    cv::Mat tempFrame = this->_actualFrame.clone();
    cv::Size newSize(this->ui->originalLabel->width(),
                     this->ui->originalLabel->height());
    cv::resize(tempFrame, tempFrame, newSize);
    cv::cvtColor(tempFrame, tempFrame, CV_BGR2RGB);

    QImage qimg2(reinterpret_cast<uchar *>(tempFrame.data), tempFrame.cols, tempFrame.rows,
                 static_cast<int>(tempFrame.step), QImage::Format_RGB888);
    this->ui->originalLabel->setPixmap(QPixmap::fromImage(qimg2));
  } else {
    spdlog::get("General")->warn(
        "You are setting a empty frame to QT Interface (function : "
        "SegmentationConfigDialog::setFrameOnScreen)");
  }
}

void SegmentationConfigDialog::resizeCamera(void) {
  int h = this->ui->rightFrame->height();
  int w = this->ui->rightFrame->width();

  if ((w > h && w != h * 4 / 3) || (h > w && h != w * 3 / 4)) {
    if (w > h) {
      this->ui->originalLabel->setGeometry((w - h * 4 / 3) / 2, 0, h * 4 / 3,
                                           h);
    } else {
      this->ui->originalLabel->setGeometry(0, (h - w * 3 / 4) / 2, w,
                                           w * 3 / 4);
    }
  }

  h = this->ui->leftFrame->height();
  w = this->ui->leftFrame->width();

  if ((w > h && w != h * 4 / 3) || (h > w && h != w * 3 / 4)) {
    if (w > h) {
      this->ui->visualizationLabel->setGeometry((w - h * 4 / 3) / 2, 0,
                                                h * 4 / 3, h);
    } else {
      this->ui->visualizationLabel->setGeometry(0, (h - w * 3 / 4) / 2, w,
                                                w * 3 / 4);
    }
  }

  QTimer::singleShot(30, this, SLOT(resizeCamera()));
}

void SegmentationConfigDialog::on_horizontalSlider_grayScale_valueChanged(
    int value) {
  this->ui->GrayLevel->setText(QString::number(value));
  this->_grayTrashHoldLevel = value;
}

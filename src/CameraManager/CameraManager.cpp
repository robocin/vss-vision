#include "CameraManager.h"

CameraManager::CameraManager() {
  this->_parametersString = "";

  const char *frameWidth = getenv("FRAME_WIDTH");
  const char *frameHeight = getenv("FRAME_HEIGHT");
  this->_frameHeight = atoi(frameHeight);
  this->_frameWidth = atoi(frameWidth);
  
  this->_is60fps = false;
  this->_isHD = false;
  this->_isNewFrameAvaliable = false;
  this->_cameraFPS = 0;
  this->_isFinished = false;
  this->_captureType = disabled;

  this->_distortionOption = NULO;

  cv::FileStorage opencv_file(
      "CameraManager/radialDistortion/camera_matrices.xml",
      cv::FileStorage::READ);
  if (!opencv_file.isOpened()) {
    std::cerr << "erro ao abrir o arquivo de distorção da camera CameraManager/radialDistortion/camera_matrices.xml" << std::endl;
    return;
  }
  opencv_file["matrix_x"] >> this->_map_x;
  opencv_file["matrix_y"] >> this->_map_y;
  opencv_file.release();
}

CameraManager& CameraManager::singleton() {
  static CameraManager instance;

  return instance;
}

CameraManager::~CameraManager() {
  this->_isFinished = true;
  this->releaseCamera();
}

bool CameraManager::init(int cameraIndex) {
  // try the HD settings for 60fps by default
  // this->_frameHeight = FRAME_HEIGHT_HD_DEFAULT;
  // this->_frameWidth = FRAME_WIDTH_HD_DEFAULT;
  this->_is60fps = true;

  if (this->_capture.isOpened()) {
    this->_capture.release();
  }

  this->_cameraIndex = cameraIndex;
  this->_capture.open(this->_cameraIndex);

  if (!this->_capture.isOpened()) {
    std::cout << "Error in CameraManipulation Constructor - Can be an error in "
                 "Camera Index"
              << std::endl;
    this->_errorInFrame = ERROR_FRAME_FROM_IMAGE;
    this->_cameraIndex = -1;
  }

  try {
    this->_capture >> this->_currentFrame;
  } catch (cv::Exception&) {
    this->_capture.release();
    this->_errorInFrame = ERROR_FRAME_FROM_IMAGE;

    return false;
  }

  this->_capture.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
  this->_capture.set(cv::CAP_PROP_FRAME_WIDTH, this->_frameWidth);
  this->_capture.set(cv::CAP_PROP_FRAME_HEIGHT, this->_frameHeight);

  if (this->_frameWidth !=
          static_cast<int>(this->_capture.get(cv::CAP_PROP_FRAME_WIDTH)) ||
      this->_frameHeight !=
          static_cast<int>(this->_capture.get(cv::CAP_PROP_FRAME_HEIGHT))) {
    this->_is60fps = false;
  }

  double cameraFps = this->_capture.get(cv::CAP_PROP_FPS);

  if (static_cast<int>(cameraFps) >= 60)
    this->_is60fps = true;
  else
    this->_is60fps = false;
  this->_frameRate = static_cast<int>(cameraFps);

  this->_captureType = usbCameraCapture;
  this->_cameraTimer.start();
  return true;
}

bool CameraManager::init(std::string videoPath) {
  if (this->_capture.isOpened()) {
    this->_capture.release();
  }

  this->_capture.open(videoPath);
  this->_lastVideoUrl = videoPath;
  if (!this->_capture.isOpened()) {
    std::cout << "Error in CameraManipulation Constructor - Can be an error in "
                 "Video Path"
              << std::endl;
    this->_errorInFrame = ERROR_FRAME_FROM_VIDEO;
    this->_cameraIndex = -1;

  } else {
    this->saveVideoUrl();
  }

  try {
    this->_capture >> this->_currentFrame;
  } catch (cv::Exception&) {
    this->_capture.release();
    this->_errorInFrame = ERROR_FRAME_FROM_IMAGE;

    return false;
  }

  this->_frameRate = static_cast<int>(this->_capture.get(cv::CAP_PROP_FPS));
  this->_captureType = videoCapture;
  return true;
}

void CameraManager::updateFrame() {
  cv::Mat frame;
  if (!this->_capture.isOpened()) {
    if (this->_errorInFrame == ERROR_FRAME_FROM_IMAGE) {
      std::cout << "Error while getting an image from the camera." << std::endl;
    } else if (this->_errorInFrame == ERROR_FRAME_FROM_VIDEO) {
      std::cout
          << "Error while getting the video, check video path in MainWindow.cpp"
          << std::endl;
    }

    frame =
        cv::Mat::zeros(this->_frameHeight, this->_frameWidth, CV_8UC3) * 255;

  } else {
    if (!this->_isFinished) this->_capture >> frame;
  }

  if ((frame.empty() || frame.cols < 1 || frame.rows < 1) &&
      this->_captureType == videoCapture) {
    this->setVideoFrameToBegin();
    if (!this->_isFinished) this->_capture >> frame;
  }

  this->_currentFrameTimeStamp = QTime::currentTime();

  // if (this->_is60fps) { // assuming it's FRAME_HEIGHTp, always
  // if (this->_frameWidth == 1920 && this->_frameHeight == 1080 &&
  //         frame.rows == 1080 && frame.cols == 1920) {
  //     cv::resize(frame, frame,
  //                cv::Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0);
  //     this->_frameWidth = frame.cols;
  //     this->_frameHeight = frame.rows;
  // }

  this->_cameraFrameLocker.lock();
  this->_currentFrame = frame;
  if (this->_distortionOption > NULO) {
    remap(frame, frame, this->_map_x, this->_map_y, cv::INTER_LINEAR);
  }
  this->_cameraFrameLocker.unlock();

  this->_isNewFrameAvaliable = true;
  this->_cameraFPS = static_cast<double>(this->_cameraTimer.getInFPS() * 0.2 +
                                         this->_cameraFPS * 0.8);
  this->_cameraTimer.stop();
  this->_cameraTimer.start();
}

std::string CameraManager::listConfig() {
  if (this->_cameraIndex == -1) return "";

  std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                             std::to_string(this->_cameraIndex) +
                             " --list-ctrls";
  this->_v4l2_process.start(v4l2_command.c_str());
  this->_v4l2_process.waitForFinished(-1);
  QString stdout = this->_v4l2_process.readAllStandardOutput();
  this->_parametersString = stdout.toLocal8Bit().constData();

  return this->_parametersString;
}

void CameraManager::setWhiteBalance(int whiteBalance) {
  if (this->_cameraIndex != -1) {
    this->_whiteBalanceTemperature.currentValue = whiteBalance;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c white_balance_temperature=";
    v4l2_command +=
        (std::to_string(this->_whiteBalanceTemperature.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setWhiteBalanceAuto(int whiteBalanceAuto) {
  if (this->_cameraIndex != -1) {
    this->_whiteBalanceTemperatureAuto.currentValue = whiteBalanceAuto;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c white_balance_temperature_auto=";
    v4l2_command +=
        (std::to_string(this->_whiteBalanceTemperatureAuto.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setBacklightComp(int backlight) {
  if (this->_cameraIndex != -1) {
    this->_backlight.currentValue = backlight;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c backlight_compensation=";
    v4l2_command += (std::to_string(this->_backlight.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setExposureAuto(int exposureAuto) {
  if (this->_cameraIndex != -1) {
    this->_exposureAuto.currentValue = exposureAuto;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c exposure_auto=";
    v4l2_command += (std::to_string(this->_exposureAuto.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setFocusAuto(int focusAuto) {
  if (this->_cameraIndex != -1) {
    this->_focusAuto.currentValue = focusAuto;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c focus_auto=";
    v4l2_command += (std::to_string(this->_focusAuto.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setGain(int gain) {
  if (this->_cameraIndex != -1) {
    this->_gain.currentValue = gain;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) + " -c gain=";
    v4l2_command += (std::to_string(this->_gain.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setBrightness(int brightness) {
  if (this->_cameraIndex != -1) {
    this->_brightness.currentValue = brightness;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c brightness=";
    v4l2_command += (std::to_string(this->_brightness.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setExposureAbsolute(int exposureAbsolute) {
  if (this->_cameraIndex != -1) {
    this->_exposureAbsolute.currentValue = exposureAbsolute;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c exposure_absolute=";
    v4l2_command += (std::to_string(this->_exposureAbsolute.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setSaturation(int saturation) {
  if (this->_cameraIndex != -1) {
    this->_saturation.currentValue = saturation;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c saturation=";
    v4l2_command += (std::to_string(this->_saturation.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setExposureAutoPriority(int exposureAutoPriority) {
  if (this->_cameraIndex != -1) {
    this->_exposureAutoPriority.currentValue = exposureAutoPriority;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c exposure_auto_priority=";
    v4l2_command += (std::to_string(this->_exposureAutoPriority.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

void CameraManager::setContrast(int contrast) {
  if (this->_cameraIndex != -1) {
    this->_contrast.currentValue = contrast;
    std::string v4l2_command = "v4l2-ctl -d /dev/video" +
                               std::to_string(this->_cameraIndex) +
                               " -c contrast=";
    v4l2_command += (std::to_string(this->_contrast.currentValue));
    this->_v4l2_process.start(v4l2_command.c_str());
    this->_v4l2_process.waitForFinished(-1);
  }
}

CameraParameter CameraManager::getWhiteBalance() {
  this->listConfig();
  this->_whiteBalanceTemperature =
      this->returnParameterFromList("white_balance_temperature ");
  return this->_whiteBalanceTemperature;
}

CameraParameter CameraManager::getWhiteBalanceAuto() {
  this->listConfig();
  this->_whiteBalanceTemperatureAuto =
      this->returnParameterFromList("white_balance_temperature_auto ");
  return this->_whiteBalanceTemperatureAuto;
}

CameraParameter CameraManager::getBlacklightComp() {
  this->listConfig();
  this->_backlight = this->returnParameterFromList("backlight_compensation");
  return this->_backlight;
}

CameraParameter CameraManager::getExposureAuto() {
  this->listConfig();
  this->_exposureAuto = this->returnParameterFromList("exposure_auto");
  return this->_exposureAuto;
}

CameraParameter CameraManager::getFocusAuto() {
  this->listConfig();
  this->_focusAuto = this->returnParameterFromList("focus_auto");
  return this->_focusAuto;
}

CameraParameter CameraManager::getGain() {
  this->listConfig();
  this->_gain = this->returnParameterFromList("gain");
  return this->_gain;
}

CameraParameter CameraManager::getBrightness() {
  this->listConfig();
  this->_brightness = this->returnParameterFromList("brightness");
  return this->_brightness;
}

CameraParameter CameraManager::getExposureAbsolute() {
  this->listConfig();
  this->_exposureAbsolute = this->returnParameterFromList("exposure_absolute");
  return this->_exposureAbsolute;
}

CameraParameter CameraManager::getSaturation() {
  this->listConfig();
  this->_saturation = this->returnParameterFromList("saturation");
  return this->_saturation;
}

CameraParameter CameraManager::getExposureAutoPriority() {
  this->listConfig();
  this->_exposureAutoPriority =
      this->returnParameterFromList("exposure_auto_priority");
  return this->_exposureAutoPriority;
}

CameraParameter CameraManager::getContrast() {
  this->listConfig();
  this->_contrast = this->returnParameterFromList("contrast");
  return this->_contrast;
}

int CameraManager::getFrameWidth() { return this->_frameWidth; }

int CameraManager::getFrameHeight() { return this->_frameHeight; }

cv::Mat CameraManager::getCurrentFrame() {
  this->_cameraFrameLocker.lock();
  cv::Mat frame = this->_currentFrame.clone();
  this->_cameraFrameLocker.unlock();
  return frame;
}

void CameraManager::getCurrentFrame(cv::Mat& frame) {
  this->_cameraFrameLocker.lock();
  this->_currentFrame.copyTo(frame);
  this->_cameraFrameLocker.unlock();
}

void CameraManager::setVideoFrameToBegin() {
  this->_capture.set(cv::CAP_PROP_POS_FRAMES, 0);
}

CameraParameter CameraManager::returnParameterFromList(
    std::string searchString) {
  std::istringstream iss(this->_parametersString);
  std::string line;
  CameraParameter returnValue;

  while (std::getline(iss, line)) {
    if (line.find(searchString) != std::string::npos) {
      returnValue.currentValue = this->searchInRegex(line, "value=(-?\\d+)");
      returnValue.defaultValue = this->searchInRegex(line, "default=(-?\\d+)");
      returnValue.minValue = this->searchInRegex(line, "min=(-?\\d+)");
      returnValue.maxValue = this->searchInRegex(line, "max=(-?\\d+)");
      break;
    } else {
      returnValue.currentValue = 0;
      returnValue.defaultValue = 0;
      returnValue.minValue = 0;
      returnValue.maxValue = 0;
    }
  }
  return returnValue;
}

int CameraManager::searchInRegex(std::string line, QString regexString) {
  int numberToReturn = 0;
  QRegExp rx(regexString);
  QString str = QString::fromStdString(line);
  QStringList list;
  int pos = 0;

  while ((pos = rx.indexIn(str, pos)) != -1) {
    list << rx.cap(1);
    pos += rx.matchedLength();
  }

  if (static_cast<int>(list.size()) >= 1) {
    std::stringstream ss;
    ss << list.at(0).toLocal8Bit().constData();
    ss >> numberToReturn;
  }

  return numberToReturn;
}

int CameraManager::getCameraIndex() { return this->_cameraIndex; }

void CameraManager::setCameraIndex(int cameraIndex) {
  this->_cameraIndex = cameraIndex;
}

void CameraManager::releaseCamera() {
  if (this->_capture.isOpened()) {
    this->_capture.release();
  }
}

int CameraManager::getCaptureFPS() {
  if (!this->_capture.isOpened()) return -1;

  return this->_frameRate;
}

std::vector<int> CameraManager::returnCameraList() {
  std::vector<int> t;
  std::string v4l2_command = " v4l2-ctl --list-devices";
  this->_v4l2_process.start(v4l2_command.c_str());
  this->_v4l2_process.waitForFinished(-1);
  QString stdout = this->_v4l2_process.readAllStandardOutput();
  std::string cameraDevicesString = stdout.toLocal8Bit().constData();
  std::istringstream iss(cameraDevicesString);
  std::string line;
  int numberToReturn = 0;

  while (std::getline(iss, line)) {
    if (line.find("/dev/video") != std::string::npos) {
      QRegExp rx("/dev/video(\\d+)");
      QString str = QString::fromStdString(line);
      QStringList list;
      int pos = 0;

      while ((pos = rx.indexIn(str, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
      }

      std::stringstream ss;
      ss << list.at(0).toLocal8Bit().constData();
      ss >> numberToReturn;
      t.push_back(numberToReturn);
    }
  }
  return t;
}

QString CameraManager::getLastVideoUrl() {
  cv::FileStorage fs(LAST_VIDEO_FILE, cv::FileStorage::READ);

  if (!fs.isOpened()) {
    spdlog::get("General")->warn("Camera Manipulation Xml: Directory Error");
    spdlog::get("General")->info("Please uncheck shadow build");
    return QString("Error");
  }

  this->_lastVideoUrl = std::string(fs[VIDEO_URL]).c_str();
  fs.release();

  return QString(this->_lastVideoUrl.c_str());
}

void CameraManager::saveVideoUrl() {
  cv::FileStorage fs(LAST_VIDEO_FILE, cv::FileStorage::WRITE);
  fs << VIDEO_URL << this->_lastVideoUrl;
  fs.release();
}

void CameraManager::loadAndApplyFile(std::string path) {
  QFile file(QString::fromStdString(path));

  if (!file.open(QIODevice::ReadOnly)) {
    std::cout << "couldn't open file " << path << std::endl;
    exit(1);
  }
  std::cout << path << std::endl;
  QByteArray jsonFile = file.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(jsonFile));
  QJsonObject json = loadDoc.object();
  this->setWhiteBalanceAuto(json[WHITE_BALANCE_TEMPERATURE_AUTO].toInt());
  this->setExposureAuto(json[EXPOSURE_AUTO].toInt());
  this->setFocusAuto(json[FOCUS_AUTO].toInt());
  this->setWhiteBalance(json[WHITE_BALANCE_TEMPERATURE].toInt());
  this->setBacklightComp(json[BACKLIGHT].toInt());
  this->setGain(json[GAIN].toInt());
  this->setBrightness(json[BRIGHTNESS].toInt());
  this->setExposureAbsolute(json[EXPOSURE_ABSOLUTE].toInt());
  this->setSaturation(json[SATURATION].toInt());
  this->setExposureAutoPriority(json[EXPOSURE_AUTO_PRIORITY].toInt());
  this->setContrast(json[CONTRAST].toInt());
  std::cout << json[BRIGHTNESS].toInt() << std::endl;

  file.close();
}

void CameraManager::saveFile(std::string path) {
  QFile file(QString::fromStdString(path));

  if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate |
                 QIODevice::Text)) {
    std::cout << "failed to open " << path << std::endl;
    exit(1);
  }

  QByteArray jsonFile = file.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(jsonFile));
  QJsonObject json = loadDoc.object();
  json.insert(WHITE_BALANCE_TEMPERATURE,
              this->_whiteBalanceTemperatureAuto.currentValue);
  json.insert(EXPOSURE_AUTO, this->_exposureAuto.currentValue);
  json.insert(FOCUS_AUTO, this->_focusAuto.currentValue);
  json.insert(WHITE_BALANCE_TEMPERATURE,
              this->_whiteBalanceTemperature.currentValue);
  json.insert(BACKLIGHT, this->_backlight.currentValue);
  json.insert(GAIN, this->_gain.currentValue);
  json.insert(BRIGHTNESS, this->_brightness.currentValue);
  json.insert(EXPOSURE_ABSOLUTE, this->_exposureAbsolute.currentValue);
  json.insert(SATURATION, this->_saturation.currentValue);
  json.insert(EXPOSURE_AUTO_PRIORITY, this->_exposureAutoPriority.currentValue);
  json.insert(CONTRAST, this->_contrast.currentValue);
  QJsonDocument saveDoc(json);

  file.write(saveDoc.toJson());

  file.close();
}

void CameraManager::set60fps(bool want60fps) {
  if (want60fps) {
    this->_frameHeight = FRAME_HEIGHT;
    this->_frameWidth = FRAME_WIDTH;
    this->_is60fps = true;
  } else {
    this->_frameHeight = FRAME_HEIGHT;
    this->_frameWidth = FRAME_WIDTH;
    this->_is60fps = false;
  }
}

double CameraManager::getCurrentFPS() { return this->_cameraFPS; }

QTime CameraManager::getCurrentFrameTimeStamp() {
  return this->_currentFrameTimeStamp;
}

bool CameraManager::isNewFrameAvaliable() { return this->_isNewFrameAvaliable; }

void CameraManager::setNewFrameAvailable(bool enabled) {
  this->_isNewFrameAvaliable = enabled;
}

CaptureType CameraManager::getCaptureType() { return this->_captureType; }

void CameraManager::setDistortionOption(Distortions distortionOption) {
  this->_distortionOption = distortionOption;
  getDistortionParameters();
}

void CameraManager::getDistortionParameters() {
  switch (this->_distortionOption) {
    case NULO:
      break;
    case ELP:
      cv::FileStorage opencv_file(
          "CameraManager/radialDistortion/camera_matrices.xml",
          cv::FileStorage::READ);
      if (!opencv_file.isOpened()) {
        std::cout << "erro ao abrir o arquivo CameraManager/radialDistortion/camera_matrices.xml" << std::endl;
      }
      opencv_file["matrix_x"] >> this->_map_x;
      opencv_file["matrix_y"] >> this->_map_y;
      opencv_file.release();
      break;
  }
}

#ifndef CAMERAMANIPULATION_H
#define CAMERAMANIPULATION_H

#include <Timer/Timer.h>
#include <QFile>
#include <QMutex>
#include <QProcess>
// #include <QRegExp>
#include <QString>
#include <QThread>
#include <QTime>
#include <iostream>
#include <iterator>
#include <opencv2/opencv.hpp>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <mutex>
#include "spdlog/spdlog.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <QRegularExpression>


#define FRAME_WIDTH_DEFAULT 1280
#define FRAME_HEIGHT_DEFAULT 720
#define FRAME_WIDTH_HD_DEFAULT 1280
#define FRAME_HEIGHT_HD_DEFAULT 720
#define NO_ERROR_FRAME 0
#define ERROR_FRAME_FROM_IMAGE 1
#define ERROR_FRAME_FROM_VIDEO 2
#define LAST_VIDEO_FILE "Config/Video.xml"
#define VIDEO_URL "VIDEO_URL"

#define CAMERA_CONFIG_D_JSON_PATH "Config/CameraConfigD.json"
#define CAMERA_CONFIG_L_JSON_PATH "Config/CameraConfigL.json"
#define DEFAULT "Default"

#define WHITE_BALANCE_TEMPERATURE "white_balance_temperature"
#define WHITE_BALANCE_TEMPERATURE_AUTO "white_balance_temperature_auto"
#define BACKLIGHT "blacklight"
#define EXPOSURE_AUTO "exposure_auto"
#define FOCUS_AUTO "focus_auto"
#define GAIN "gain"
#define BRIGHTNESS "brightness"
#define EXPOSURE_ABSOLUTE "exposure_absolute"
#define SATURATION "saturation"
#define EXPOSURE_AUTO_PRIORITY "exposure_auto_priority"
#define CONTRAST "contrast"

#define CAM_ID "0"

enum CaptureType { disabled = -1, videoCapture = 0, usbCameraCapture = 1 };

enum Distortions { NULO = 0, STANDARD = 1, HD = 2 };

/**
 * { Structure to represent parameters min value, max value, default value and
 * current value }
 */
typedef struct CameraParameter {
  int minValue;
  int maxValue;
  int defaultValue;
  int currentValue;
} CameraParameter;

/**
 * @brief    Class for camera manipulation.
 */
class CameraManager {
 public:
  void setDistortionOption(Distortions distortionOption);
  void getDistortionParameters();

  /**
   * @brief updates current frame in Camera Manipulation Class
   */
  void updateFrame();
  /**
   * @brief    { CameraManipulation Constructor }
   *
   * @param[in]  cameraIndex  The camera index to open VideoCapture
   *
   * @return { Return if the operation was succeeded }
   */
  bool init(int cameraIndex);

  /**
   * @brief    { CameraManipulation Constructor }
   *
   * @param[in]  videoPath  The video path to open VideoCapture
   *
   * @return { Return if the operation was succeeded }
   */
  bool init(std::string videoPath);

  /**
   * @brief    { List configuration of the camera parameters }
   *
   * @return   { Return a string with all parameters values in actual
   * configuration }
   */
  std::string listConfig();

  /**
   * @brief    Sets the white balance.
   *
   * @param[in]  whiteBalance  The white balance
   */
  void setWhiteBalance(int whiteBalance);

  /**
   * @brief    Sets the white balance auto.
   *
   * @param[in]  whiteBalance  The white balance auto
   */
  void setWhiteBalanceAuto(int whiteBalanceAuto);

  /**
   * @brief    Sets the backlight component.
   *
   * @param[in]  backlight  The backlight
   */
  void setBacklightComp(int backlight);

  /**
   * @brief    Sets the exposure automatic.
   *
   * @param[in]  exposureAuto  The exposure automatic
   */
  void setExposureAuto(int exposureAuto);

  /**
   * @brief    Sets the focus automatic.
   *
   * @param[in]  focusAuto  The focus automatic
   */
  void setFocusAuto(int focusAuto);

  /**
   * @brief    Sets the gain.
   *
   * @param[in]  gain  The gain
   */
  void setGain(int gain);

  /**
   * @brief    Sets the brightness.
   *
   * @param[in]  brightness  The brightness
   */
  void setBrightness(int brightness);

  /**
   * @brief    Sets the exposure absolute.
   *
   * @param[in]  exposureAbsolute  The exposure absolute
   */
  void setExposureAbsolute(int exposureAbsolute);

  /**
   * @brief    Sets the saturation.
   *
   * @param[in]  saturation  The saturation
   */
  void setSaturation(int saturation);

  /**
   * @brief    Sets the exposure auto priority"
.
   *
   * @param[in]  exposureAutoPriority The exposure_auto_priority
   */
  void setExposureAutoPriority(int exposureAutoPriority);

  /**
   * @brief    Sets the contrast.
   *
   * @param[in]  contrast  The contrast
   */
  void setContrast(int contrast);

  /**
   * @brief    Sets the frame width.
   *
   * @param[in]  frameWidth  The frame width
   */
  void setFrameWidth(int frameWidth);

  /**
   * @brief    Sets the frame height.
   *
   * @param[in]  frameHeight  The frame height
   */
  void setFrameHeight(int frameHeight);

  /**
   * @brief    Gets the white balance.
   *
   * @return   The white balance.
   */
  CameraParameter getWhiteBalance();

  /**
   * @brief    Gets the white balance.
   *
   * @return   The white balance.
   */
  CameraParameter getWhiteBalanceAuto();

  /**
   * @brief    Gets the backlight component.
   *
   * @return   The backlight component.
   */
  CameraParameter getBlacklightComp();

  /**
   * @brief    Gets the exposure automatic.
   *
   * @return   The exposure automatic.
   */
  CameraParameter getExposureAuto();

  /**
   * @brief    Gets the focus automatic.
   *
   * @return   The focus automatic.
   */
  CameraParameter getFocusAuto();

  /**
   * @brief    Gets the gain.
   *
   * @return   The gain.
   */
  CameraParameter getGain();

  /**
   * @brief    Gets the brightness.
   *
   * @return   The brightness.
   */
  CameraParameter getBrightness();

  /**
   * @brief    Gets the exposure absolute.
   *
   * @return   The exposure absolute.
   */
  CameraParameter getExposureAbsolute();

  /**
   * @brief    Gets the saturation.
   *
   * @return   The saturation.
   */
  CameraParameter getSaturation();

  /**
   * @brief    Gets the exposureAutoPriority.
   *
   * @return   The exposureAutoPriority.
   */
  CameraParameter getExposureAutoPriority();

  /**
   * @brief    Gets the contrast.
   *
   * @return   The contrast.
   */
  CameraParameter getContrast();

  /**
   * @brief    Gets the frame width.
   *
   * @return   The frame width.
   */
  int getFrameWidth();

  /**
   * @brief    Gets the frame height.
   *
   * @return   The frame height.
   */
  int getFrameHeight();

  /**
   * @brief    Gets the frame.
   *
   * @return   The frame.
   */
  cv::Mat getCurrentFrame();

  /**
   * @brief    Gets the frame and put in frame address.
   *
   * @param    frame  The frame
   */
  void getCurrentFrame(cv::Mat& frame);

  /**
   * @brief    Sets the video frame to begin using
   * CV_CAP_PROP_POS_FRAMES
   */
  void setVideoFrameToBegin();

  /**
   * @brief    Returns a parameter of the camera from list of parameters.
   *
   * @param[in]  searchString  The string parameter to search in list
   *
   * @return   { CAMERAPARAMETERS value returned}
   */
  CameraParameter returnParameterFromList(std::string searchString);

  /**
   * @brief    Function to use in setCameraList, that will grab all camera
   * devices in v4l2
   *
   * @return   { description_of_the_return_value }
   */
  std::vector<int> returnCameraList();

  /**
   * @brief    Sets the camera list.
   */
  void setCameraList();

  /**
   * @brief    Gets the camera list.
   *
   * @return   The camera list.
   */
  std::vector<int> getCameraList();

  int searchInRegex(std::string line, QString regexString);

  /**
   * @brief    Singleton method to acess CameraManipulation module
   *
   * @return   return a CameraManipulation reference, unique and common to all
   * class in the program
   */
  static CameraManager& singleton();

  /**
   * @brief    Sets the camera index.
   *
   * @param[in]  cameraIndex  The camera index
   */
  void setCameraIndex(int cameraIndex);

  /**
   * @brief    Gets the camera index.
   *
   * @return   The camera index.
   */
  int getCameraIndex();

  /**
   * @brief    Release camera.
   */
  void releaseCamera();

  int getCaptureFPS();
  /**
   * @brief get the url of the last used video
   * @return the url of the last used video in QString format
   */
  QString getLastVideoUrl();

  /**
   * @brief save the last used video url
   */
  void saveVideoUrl();

  /**
   * @brief load the XML with given filename and apply it on camera
   * @param filename
   */
  void loadAndApplyFile(std::string path);

  /**
   * @brief save a camera config XML
   * @param path, can be CAMERA_CONFIG_D_XML_PATH for Defaut XML or
   * CAMERA_CONFIG_L_XML_PATH for the last used configuration
   */
  void saveFile(std::string path);

  void set60fps(bool want60fps);

  double getCurrentFPS();

  QTime getCurrentFrameTimeStamp();

  bool isNewFrameAvaliable();

  void setNewFrameAvailable(bool enabled);

  CaptureType getCaptureType();

 private:
  /**
   * @brief     { CameraManipulation Private Constructor }
   */
  CameraManager();

  /**
   * @brief    CameraManipulation Private Copy Constructor
   *
   */
  CameraManager(const CameraManager&);

  /**
   * @brief    CameraManipulation Private assign operator
   *
   */
  CameraManager& operator=(const CameraManager&);

  /**
   * @brief    Destroys the object of the class Camera Manipulation.
   */
  ~CameraManager();

  CameraParameter _whiteBalanceTemperature;
  CameraParameter _whiteBalanceTemperatureAuto;
  CameraParameter _backlight;
  CameraParameter _exposureAuto;
  CameraParameter _focusAuto;
  CameraParameter _gain;
  CameraParameter _brightness;
  CameraParameter _exposureAbsolute;
  CameraParameter _saturation;
  CameraParameter _exposureAutoPriority;
  CameraParameter _contrast;

  std::mutex _cameraFrameLocker;

  cv::VideoCapture _capture;
  cv::Mat _currentFrame;
  int _frameWidth;
  int _frameHeight;
  int FRAME_WIDTH, FRAME_HEIGHT;
  bool _is60fps;
  bool _isHD;
  int _cameraIndex;
  int _frameRate;
  double _cameraFPS;
  Timer _cameraTimer;
  QTime _currentFrameTimeStamp;
  int _errorInFrame = NO_ERROR_FRAME;
  CaptureType _captureType;
  std::vector<int> _cameraList;
  std::string _parametersString;
  std::string _lastVideoUrl;
  QProcess _v4l2_process;
  std::atomic<bool> _isFinished;
  std::atomic<bool> _isNewFrameAvaliable;

  Distortions _distortionOption;
  cv::Mat _map_x_std;
  cv::Mat _map_y_std;

  cv::Mat _map_x_hd;
  cv::Mat _map_y_hd;

  cv::Mat _map_x;
  cv::Mat _map_y;
};

#endif

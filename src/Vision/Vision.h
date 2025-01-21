/**
 * mainpage Vision class made by the RoboCIn for the project IEEE - VSSL
 *
 * @author Robocin - Visão
 *
 * The Vision module was designed to facilitate the addition of new Filters and algorithms, and also provide a good level of abstraction to external modules.
 * For that, we have the Vision object as Facade, with simple methods to get position and debug frames of the module, and two interfaces to implement algorithms
 *
 * that will be part of some part of the frame processing. The Vision processing is composed by the following steps:
 *
 * 1. **Image Correction:** Aims to correct camera distortions such as shearing, radial distortion and making easier to get real points from image points.
 * 2. **Image Filtering:** Aims to improve the image quality, facilitating further processing. One goal of the image filtering step is minimizing the image noise.
 * 3. **Segmentation:** Aims to group similar pixels tagging them with the same tag (Usually the tag is represented as a color in RGB). Non relevant elements will be tagged together usually with a black color.
 * 4. **Tracking and Detection:** The detect part aims to, given the segmented frame, identify similar region as a entity and extract the **position and velocity** informations. The tracking part aims to,
 * given previous detection points, accelerate the detection process of the same points in subsequent frames.
 *
 */
#ifndef VISION_H
#define VISION_H

#include <opencv2/opencv.hpp>
#include "Entity/Entity.h"
#include "Vision/ColorSpace.h"
#include "Vision/PositionProcessing/PositionProcessing.h"
#include "Vision/ImageProcessing/ImageProcessing.h"
#include "Vision/PositionProcessing/BlobDetection.h"
#include "Vision/PositionProcessing/runlengthencoding.h"
#include "Vision/ImageProcessing/ImageProcessing.h"
#include "Vision/ImageProcessing/LUTSegmentation.h"
#include "Vision/ImageProcessing/WarpCorrection.h"
#include <QTime>
#include <QElapsedTimer>
#include <Timer/Timer.h>
#include "Network/visionServer/server.h"

//#include "Utils/Entity.h"
#include "Utils/Utils.h"
#include <stdlib.h>


/**
 * @brief    Class for vision module.
 *
 * This is the Vision module of the RoboCIn VSSL Software. It is responsible to process the camera frames and retreive **position and velocity**
 * of all robots in field using Image Processing and Computacional Vision algorithms, creating a abstraction to other layers of the project.
 *
 */
class Vision {
private:

  /**
   * @brief    Private Construtor
   */
  Vision();

  /**
   * @brief    Private Copy Constructor
   *
   */
  Vision(Vision const&);

  /**
   * @brief    Private assign operator
   *
   */
  Vision& operator=(Vision const&);

  /**
   * @brief    Private destructor of the object.
   */
  ~Vision();

  /**
   * { object responsible for robot detection in a segmented frame }
   */
  PositionProcessing* _detection;

  RunLengthEncoding* _compression;

  /**
   * { object responsible for robot tracking in a segmented frame }
   */
  PositionProcessing* _tracking;

  /**
   * { object responsible for apply the camera correction in a frame }
   */
  ImageProcessing* _correction;

  /**
   * { object responsible for segment a frame }
   */
  ImageProcessing* _segmentation;

  /**
   * { atribute of the frame that is being processed or will be processed by vision module }
   */
  cv::Mat _currentFrame;

  /**
   * { segmented frame with label of colors. It will be used in detection. }
   */
  cv::Mat _processingFrame;

  /**
   * { the original frame only with the correction, if it is enabled. }
   */
  cv::Mat _correctedFrame;

  /**
   * @brief convert (_wConvert, _hConvert) convertion px to cm
   */
  cv::Point2d _convert;

  /**
   * { Holds the state of enabling correction or not }
   */
  bool _isCorrectionEnabled;

  /**
   * { Holds the state of enabling frame processing or not }
   */
  bool _isProcessingEnabled;

  int _teamColor;

  /**
   * { Entity vector that keeps in output information of vision module. For mode information @see entities }
   */
  std::vector<Entity> _robotPositions;

  void setObjectsSpeed(QTime timeStamp, std::vector<Entity> &currentPositions);

  std::vector < std::queue < std::pair<cv::Point2d, QTime> > > _lastPositions;

  bool _firstFrameDeepLog, _deepLogRecord, _deepLogRecordingVideo;

  std::string _deepLogFileName, _deepLogFilePath, _deepLogFileFolder;
  FILE* _deepLogFile;
  unsigned int _deepLogInitialTime;
  Timer _visionTimer, _visionFrameTimer;
  double _visionRunTime;
  std::mutex _currentFrameLocker, _visionStatusLocker;

  QTime firstTime;

  Point _frameDimensions;

  VisionServer *server;

  void saveFrameDimensions(cv::Mat &frame);

  /**
   * @brief    Sets the frame that will be processed by vision module.
   *
   * @param[in]  frame  The frame wanted to be processed
   */
  void setFrame(cv::Mat &frame);

  /**
   * @brief    Process the frame , generating as output to (VSS) GameInfo entity's vector with velocity and position of all detected robots .
   */
  void update();

public:
  /**
   * @brief    Singleton method to acess Vision module
   *
   * @return   return a Vision reference, unique and common to all class in the program
   */
  static Vision& singleton();

  Point getFrameDimensions();

  /**
   * @brief    function called everytime a new frame reachs the camera
   *
   * @param[in]   frame The frame wanted to be processed
   * @param[in]   timeStamp
   * @param[in]   vss everything
   */
  void update(cv::Mat& frame, QTime timeStamp);

  /**
   * @brief    Gets the debug segmentation frame with all segmented regions colorized with your tag color.
   *
   * @param[in]   The segmentation frame.
   */
  void getSegmentationDebugFrame(cv::Mat& frame);

  /**
   * @brief    Gets the debug tracking frame with information of the area the tracking algorithm points as area with
   * 			   highest probability to find the tracked robot.
   *
   * @param[in]   The tracking frame.
   */
  void getTrackingDebugFrame(cv::Mat& frame);

  /**
   * @brief    Gets the debug detection frame with information of every color cluster points
   * @param[in]   The tracking frame.
   */
  void getDetectionDebugFrame(cv::Mat& frame);


  ImageProcessing* getSegmentationObject();

  /**
   * @brief    Sets in real time the tracking algorithm to be used in
   *       update() function.
   *
   * @param[in]  algorithmLabel  The algorithm label that should be executed.
   *
   * The algorithm label can be
   * 				- Generic Tracking
   *
   */
  bool setTrackingAlgorithm(std::string algorithmLabel);

  /**
   * @brief    Sets in real time the detection algorithm to be used in
   *       update() function.
   *
   * @param[in]  algorithmLabel  The algorithm label that should be executed
   *
   * The algorithm label can be
   * 				- KMEANS
   * 				- WHEREARE
   */
  bool setDetectionAlgorithm(std::string algorithmLabel);

  /**
   * @brief setDetectionParam set some param in detection class
   *
   * @param var string label, check xml
   *
   * @param value the value of new param
   */
  void setDetectionParam(std::string var,int value);
  /**
   * @brief setTrackParam
   *
   * @param var string label, check xml
   *
   * @param value value of the new param
   */
  void setTrackParam(std::string var,int value);
  /**
   * @brief SetDetectionParamFromXml set detection param from a xml file
   */
  void setDetectionParamFromXml();

  /**
   * @brief SetTrackParamFromXml set track param from a xml file
   */
  void setTrackParamFromXml();
  /**
   * @brief savePositionParam save all param of PositionProcessing into xml file
   */
  void savePositionParam();

  /**
   * @brief    Gets the corrected debug frame.
   *
   * @param    frame  The corrected frame
   */
  void getCorrectedDebugFrame(cv::Mat& frame);

  /**
   * @brief    { reinit the correction object }
   */
  void resetCorrection();

  /**
   * @brief    { reinit the segmentation object }
   */
  void resetSegmentation();

  /**
   * @brief    Gets the segmentation frame.
   *
   * @param[in]   The segmentation frame.
   */
  void getSegmentationFrame(cv::Mat& frame);

  /**
   * @brief    Gets the detection frame.
   *
   * @param[in]   The detection frame.
   */
  void getDetectionFrame(cv::Mat& frame);

  /**
   * @brief getConvert convert (_wConvert, _hConvert) convertion px to cm
   * @return
   */
  void setConvertAll(std::vector<Entity>& entities);

  /**
   * @brief    Determines if correction enabled.
   *
   * @return   True if correction enabled, False otherwise.
   */
  bool isCorrectionEnabled();
  
  /**
   * @brief    Enable/Disable the correction.
   *
   * @param[in]  enabled  Tells if the correction should be turned on or off
   */
  void setCorrection(bool enabled);

  /**
   * @brief    Determines if frame processing is enabled.
   *
   * @return   True if correction enabled, False otherwise.
   */
  bool isProcessingEnabled();

  /**
   * @brief    Enable/Disable the frame processing.
   *
   * @param[in]  enabled  Tells if the correction should be turned on or off
   */
  void setProcessing(bool enabled);

  /**
   * @brief setColorIndex
   * @param color { RedCOL to ColorStrange }
   * @param index 0, 1, 2
   */
  int setColorIndex(int color, int index);

  void setQuantizationBool(bool quantization);

  bool getQuantizationBool();

  std::vector<Entity> getRobotPositions();

  void setTeamColor(int color);

  int getTeamColor();

  void getCurrentFrame(cv::Mat& frame);

  void setDeepLogFileName(std::string fileName);
  void setRecordingVideo(bool value);
  void closeDeepLog();
  void recordDeepLog();

  int FRAME_WIDTH, FRAME_HEIGHT;


  /**
    * @brief Retrieves  the current runtime of the vision system
    *
    *
  */
  double getVisionRunTime();
};

#endif

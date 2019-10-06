#ifndef LUT_H
#define LUT_H

#include "ImageProcessing.h"
#include "Vision/ColorSpace.h"
#include <tbb/tbb.h>
#include <Timer/Timer.h>

#define LUTSIZE 16777216

#define YMAXLABEL "YMAX"
#define UMAXLABEL "UMAX"
#define VMAXLABEL "VMAX"

#define YMINLABEL "YMIN"
#define UMINLABEL "UMIN"
#define VMINLABEL "VMIN"

#define NOCOLLABEL "NoCOL"
#define ORANGELABEL "Orange"
#define BLUELABEL "Blue"
#define YELLOWLABEL "Yellow"
#define REDLABEL "Red"
#define GREENLABEL "Green"
#define PINKLABEL "Pink"
#define LIGHTBLUELABEL "LightBlue"
#define PURPLELABEL "Purple"
#define BROWNLABEL "Brown"
#define COLORSTRANGELABEL "ColorStrange"
#define GRAY_SCALE "GrayScale"
#define OPENCV_STORAGE "opencv_storage"

/**
 * @brief    Class for segmentation using a Look Up Table (LUT).
 */
class LUTSegmentation : public ImageProcessing {

 public:

  /**
   * @brief    Default Constructor
   */
  LUTSegmentation();

  /**
   * @brief    Destroys the object.
   */
  ~LUTSegmentation();

  /**
   * @brief    init the object with the given parameters
   *
   * @param[in]  paramaters  The paramaters
   */
  void init(std::map<std::string, int> parameters) final;

  /**
   * @brief    Change some parameter's value
   *
   * @param[in]  parameter  The parameter to be changed
   * @param[in]  value    The value to be placed
   */
  void setup(std::string parameter, int value) final;

  /**
   * @brief    Apply the algorithm on the given frame
   *
   * @param[in]  frame  The frame to be processed in BGR
   *
   * @return   A one channel's Mat with the labels on the pixels' value
   */
  cv::Mat run(cv::Mat &frame) final;

  /**
   * @brief    Gets the debug frame, a Mat in BGR channel
   *
   * @param[in]   The debug frame.
   */
  void getDebugFrame(cv::Mat& frame) final;

  /**
   * @brief    Init the object using the parameters from a desired file
   *
   * @param[in]  path  The file's path
   */
  void initFromFile(std::string path);

  /**
   * @brief    Sets a specific pixel of LUT with a valid Label
   *
   * @param    color  The color
   * @param[in]  id   The identifier that needs to conform with the Color enum present in Utils
   */
  void setLUTPixel(YUV &color, int id);

  void setQuantizationBool(bool quantization);

  bool getQuantizationBool();

  int *getLUT();

 private:

  /**
   * @brief    Gets the color Label to a given YUV color
   *
   * @param    color  The  YUV color
   *
   * @return   The colorLabel
   */
  int getColorLabel(YUV &color);

  /**
   * @brief    Init the Look Up Table with the already loaded parameters
   */
  void initLUT();
  std::mutex _frameLock;
  int *_LUT;
  ColorInterval *_calibrationParameters;
  cv::Mat _debugFrame;
  cv::Mat _segmentationFrame;
  std::string _colorLabels[NUMBEROFCOLOR] = { NOCOLLABEL,
                                              ORANGELABEL,
                                              BLUELABEL,
                                              YELLOWLABEL,
                                              REDLABEL,
                                              GREENLABEL,
                                              PINKLABEL,
                                              LIGHTBLUELABEL,
                                              PURPLELABEL,
                                              BROWNLABEL,
                                              COLORSTRANGELABEL
                                            };
  bool _quantization;
  int _grayTrashHoldLevel;

};

#endif

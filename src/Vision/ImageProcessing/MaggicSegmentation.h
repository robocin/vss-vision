#ifndef MAGGICSEGMENTATION_H
#define MAGGICSEGMENTATION_H

#include "ImageProcessing.h"
#include "Vision/ColorSpace.h"
#include <QPushButton>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <fstream>
typedef unsigned char uchar;

#define LUTSIZE 16777216

#define LUT_SIZE 16777216*3

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

template<typename T>
T max_element_of(T* data, size_t size) {
  T r = data[0];
  for (size_t i = 1; i < size; ++i) {
    r = (data[i] > r ? data[i] : r);
  }
  return r;
}


enum MaggicVisionDebugSelection {
  MaggicVisionDebugSelection_Undefined = 0,
  MaggicVisionDebugSelection_Thresholded,
  MaggicVisionDebugSelection_ExtremeSaturation,
  MaggicVisionDebugSelection_MultipliedResults,
  MaggicVisionDebugSelection_SegmentationFrame,
  MaggicVisionDebugSelection_DetailsFrame
};

typedef std::vector<cv::Rect> Rectangles;

/**
 * @brief    Class for segmentation using a Look Up Table (LUT).
 */
class MaggicSegmentation : public ImageProcessing
{

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

public:
  bool paused, enableEstimateRobots;
  bool useLoadedValues = false;
  
  /**
   * @brief    Default Constructor
   */
  MaggicSegmentation();

  /**
   * @brief    Destroys the object.
   */
  ~MaggicSegmentation();

  /**
   * @brief    Apply the algorithm on the given frame
   *
   * @param[in]  frame  The frame to be processed in BGR
   *
   * @return   A one channel's Mat with the labels on the pixels' value
   */
  cv::Mat run(cv::Mat& frame) final;

  /**
   * @brief    Gets the debug frame, a Mat in BGR channel
   *
   * @return   The debug frame.
   */
  void getDebugFrame(cv::Mat& frame) final;

  /**
   * @brief    Gets the segmentation frame from lut. Frame for debug).
   *
   * @return   The segmentation frame from lut, it's use in Vision to pass for other class.
   */
  void getSegmentationFrameFromLUT(cv::Mat& frame);


  void calibrate(cv::Mat &frame);

  int getFilterGrayThresholdValue();

  void setFilterGrayThresholdValue(int newFilterGrayThreshold);

  void getFilterGrayThresholdValues(int &minimum, int &maximum);

  void setFilterGrayThresholdValues(int minimum, int maximum);

  void setManyTimes(int manyTimes = 1);

  void setEntitiesCount(int entitiesCount = 1);

  int getEntitiesCount();

  void setDebugSelection(MaggicVisionDebugSelection selection);

  void setLearningThresholdValue(bool enabled);

  void getLearningThresholdValue(bool &enabled);

  bool isLearning();

  void setLearningThresholdFrames(uint frames);

  void getLearningThresholdFrames(uint &frames);

  void getCalibrationFrames(uint &frames);

  void updateFilterGrayThresholdValue();

  void setHUETable(bool fromFile = false);

  void generateLUTFromHUE();

  int* getLUT();

  void openLastSession();

  void saveSession();

  void loadDefaultHue();

  void setMousePosition(cv::Point2f mpos);

  void setMouseButtonPress(int btnId);

  void setMouseButtonRelease(int btnId);

  void setVectorscopeEnabled(bool enabled);

  void setFilterEnabled(bool enabled);

  void saveSelectedDebug();

private:
  int _minimumGrayThreshold = 10, _maximumGrayThreshold = 40, _intervalGrayThreshold = 30;
  static constexpr float div255 = 1.0f / 255.0f;
  static constexpr float div3255 = 1.0f/(255.0f+ 255.0f+ 255.0f);
  bool normalized_color;

  std::string _maggicSegmentationSessionFileName;

  uint _calibrationFrames, _learningThresholdFrames;

  uint _thresholdFrequency[256];
  bool _learningThresholdValue;

  int greatestSumOfAreas = 0;
  int filterGrayThreshold = 30;
  MaggicVisionDebugSelection _debugSelection;

  typedef std::vector<float> ColorDescriptor;
  ColorDescriptor colorDescriptors;
  std::vector<cv::Point2i> componentsCentroids;

  // @TODO : vector with the rectangles of estimated robots
  Rectangles componentsRectangles;

  struct RobotDescriptor {
    ColorDescriptor colors;
  };

  RobotDescriptor robotsDescriptors[8];

  int* _HUETable;
  bool isLUTReady;

  int _manyTimes, _entitiesCount;
  int component_id = 1;
  int n_components = 0;

  bool updateColors = false;

  void filterGray(cv::Mat &d, cv::Mat &o);

  inline void filterGray(cv::Vec3b &color, cv::Vec3b &coloro);

  void filterBinarizeColored(cv::Mat &d, cv::Mat &o);

  void filterExtremeSaturation(cv::Mat &d, cv::Mat &o);

  void updateHistogramDescriptors();

  void filterGrain(ColorDescriptor &dest, ColorDescriptor &orig);

  void _layeredAdd(cv::Mat &out, cv::Mat imgA, cv::Mat imgB);

  bool estimateRobots(cv::Mat img, int manyTimes, int n_components_reference = 7);

  void doDetails();

  void removeTopRectangle(Rectangles& rects, cv::Point& p);

  /**
   * @brief    Init the Look Up Table with the already loaded parameters
   */
  void initLUT();

  // vector of pair: <float hueValue, uchar colorLabel>
  std::vector<std::pair<float, int>> hueList;
  std::vector<std::pair<float, int>> defaultHueList;


  cv::Mat colorPalette,
      colorPaletteYUV,
      colorPaletteHSV,
      histo;

  int* _LUT;
  ColorInterval* _calibrationParameters;
  cv::Mat _imageBuffer;
  cv::Mat _imageBufferFiltered;
  cv::Mat _imageBufferHSV;
  cv::Mat _debugFrame;
  cv::Mat _segmentationFrame;
  cv::Mat _extremeSaturation, _multipliedResults, _firstThreshold, _secondThreshold;
  cv::Mat _detailsFrame, _colorDetailsFrame;
  cv::Mat _filterMask;
  cv::Point2i cursorPos;
  std::vector<cv::Point2i> lastCursorPos;
  Rectangles filterRectangles;
  std::mutex mut;
  int pressedId = 0, releasedId = 0;
  int dragpivotId = -1;
  bool pressedMouse = false, releasedMouse = false;
  bool pressedLeft = false, pressedRight = false;
  bool releasedLeft = false, releasedRight = false;
  bool mouseDrag = false;
  bool colorDistribution = false;
  bool enableFilter = false;

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
                        COLORSTRANGELABEL };

};

#endif

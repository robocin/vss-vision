#ifndef WARPCORRECTION_H
#define WARPCORRECTION_H

#include "ImageProcessing.h"
#include "Vision/ColorSpace.h"
#include <nlohmann/json.hpp>
#include <fstream>


#define FIELDWIDTH 170
#define FIELDHEIGHT 130

#define FIELDLIMITSPATH "Config/fieldLimits.json"
class WarpCorrection : public ImageProcessing {
 public:
  /**
   * @brief    { Constructor of the class WarpCorrection }
   */
  WarpCorrection();

  /**
   * @brief    Destroys the object WarpCorrection.
   */
  ~WarpCorrection();

  /**
   * @brief    init the object with the given parameters
   *
   * @param[in]  paramaters  The paramaters
   */
  void init(std::map<std::string, int>);

  /**
   * @brief    Change some parameter's value
   *
   * @param[in]  parameter  The parameter to be changed
   * @param[in]  value    The value to be placed
   */

  void initFromFile(std::string path, cv::Point2d* convert);

  void setup(std::string, int);

  /**
   * @brief    Apply the algorithm on the given frame
   *
   * @param[in]  frame  The frame to be processed in BGR
   *
   * @return   A one channel's Mat with the labels on the pixels' value
   */
  cv::Mat run(cv::Mat& frame);

  /**
   * @brief    Gets the debug frame, a Mat in BGR channel
   *
   * @return   The debug frame.
   */
  void getDebugFrame(cv::Mat& frame);

 private:
  void defineMaps();

  cv::Point2f _correctionPoints[4];
  cv::Mat _warpPespectiveFrame;
  cv::Mat _warpPespectiveMatrix;
  cv::Size _matrixSize;
  cv::Mat _transformationX;
  cv::Mat _transformationY;
  std::mutex _frameLocker, _mapsLocker, _pointsLocker;
};

#endif

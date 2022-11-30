#ifndef VSS_VISION_IMAGEPROCESSING_H
#define VSS_VISION_IMAGEPROCESSING_H

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <mutex>

/**
 * @brief    Class for image processing.
 */
class ImageProcessing {
 public:
  /**
   * @brief    run algorithm
   *
   * @param[in]  frame  The frame
   *
   * @return   frame with the filter
   */
  virtual cv::Mat run(cv::Mat& frame) = 0;

  /**
   * @brief    Gets the debug frame.
   *
   * @param[in]  frame  The debug frame
   */
  virtual void getDebugFrame(cv::Mat& frame) = 0;

  virtual ~ImageProcessing() = default;
};

#endif // VSS_VISION_IMAGEPROCESSING_H

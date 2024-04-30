#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/aruco.hpp"
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


class ArucoDetection {
  public:
	ArucoDetection();
	void detection(cv::Mat& frame);
	~ArucoDetection() = default;

  private:
    std::mutex mut;
	cv::Ptr<cv::aruco::DetectorParameters> parameters;
	cv::Ptr<cv::aruco::Dictionary> dictionary;
};

#endif

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <QReadWriteLock>

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
	 * @brief    initializes the algorithm
	 *
	 * @param[in]  paramaters  The paramaters
	 */
	virtual void init(std::map<std::string, int> paramaters) = 0;
	
	/**
	 * @brief    change the parameter
	 *
	 * @param[in]  parameter  The parameter
	 * @param[in]  value    The value
	 */
	virtual void setup(std::string parameter, int value) = 0;

	/**
	 * @brief    Gets the debug frame.
	 *
	 * @param[in]  frame  The frame
	 *
	 * @return   The debug frame.
	 */
  virtual cv::Mat getDebugFrame() = 0;

  virtual ~ImageProcessing() = default;
	
};

#endif

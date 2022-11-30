#ifndef VSS_VISION_RUNLENGHTENCODING_H
#define VSS_VISION_RUNLENGHTENCODING_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <vector>
#include <Utils/Utils.h>
#include <tbb/tbb.h>
#include <Timer/Timer.h>

typedef struct {
  int start;
  int width;
  int areaBlob;
  int parent;
  int parentRow;
  int sumX;
  int sumY;
  uchar color;
} Run;

class RunLengthEncoding {
 public:
  RunLengthEncoding();

  /**
   * @brief    Compress the source matrix image using the runLengthEncoding algorithm
   *
   * @param[in]  matrix   source matrix, already segmented
   */
  std::vector<std::vector<Run>> run(const cv::Mat& matrix);
};

#endif // VSS_VISION_RUNLENGHTENCODING_H

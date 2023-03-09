#ifndef RUNLENGHTENCODING_H
#define RUNLENGHTENCODING_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <vector>
#include <Utils/Utils.h>
#ifndef Q_MOC_RUN
#if defined(emit)
    #undef emit
    #include <tbb/parallel_for.h>
    #include <tbb/blocked_range.h>
    #define emit // restore the macro definition of "emit", as it was defined in gtmetamacros.h
#else
    #include <tbb/parallel_for.h>
    #include <tbb/blocked_range.h>
#endif // defined(emit)
#endif // Q_MOC_RUN
#include <Timer/Timer.h>

typedef struct{
   int start;
   int width;
   int areaBlob;
   int parent;
   int parentRow;
   int sumX;
   int sumY;
   uchar color;
}Run;

class RunLengthEncoding
{
public:
  RunLengthEncoding();

  /**
   * @brief    Compress the source matrix image using the runLengthEncoding algorithm
   *
   * @param[in]  matrix   source matrix, already segmented
   */
  std::vector< std::vector<Run> > run(const cv::Mat &matrix);

};

#endif // RUNLENGHTENCODING_H

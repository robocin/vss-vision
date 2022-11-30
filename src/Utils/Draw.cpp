#include "Draw.h"
#include "Utils.h"

cv::Mat Draw::circle(const Point& t_center,
                     const int& t_radius,
                     const cv::Scalar& t_color,
                     const int& t_thickness,
                     const int& t_lineType,
                     const int& t_shift) {
  cv::Mat ret;
  cv::circle(ret,
             Utils::convertPositionCmToPixel(t_center),
             t_radius,
             t_color,
             t_thickness,
             t_lineType,
             t_shift);
  return ret;
}

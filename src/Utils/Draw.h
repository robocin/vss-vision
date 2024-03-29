#ifndef DRAW_H
#define DRAW_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "Types.h"

// Cria uma matriz ja convertendo as dimensoes em cm para pixels, com a figura desenhada, pois durante todo o sw
// se trabalha apenas com cm.
namespace Draw {
  cv::Mat circle(const Point &t_center, const Int &t_radius,
                 const cv::Scalar &t_color, const Int &t_thickness,
                 const Int &t_lineType, const Int &t_shift);

}

#endif // DRAW_H

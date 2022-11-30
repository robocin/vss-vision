#ifndef VSS_VISION_GLOBAL_H
#define VSS_VISION_GLOBAL_H

#include "Types.h"
#include "EnumsAndConstants.h"
#include <opencv2/opencv.hpp>

class Global {
  inline static Point m_convertRatio;
  inline static float m_minPositionDifference = 5;
  // Qualquer valor menor que essa margem é igual a 0
  inline static float m_eps = 1e-6;

 public:
  static void setConvertRatio(const Point& t_convertRatio);
  static void setMinPositionDifference(const float& t_minPositionDifference);
  static void setEps(const float& t_eps);

  static const Point& convertRatio();
  static const float& minPositionDifference();
  static const float& eps();
};

#endif // VSS_VISION_GLOBAL_H

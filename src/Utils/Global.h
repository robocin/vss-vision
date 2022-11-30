#ifndef GLOBAL_H
#define GLOBAL_H

#include "Types.h"
#include "EnumsAndConstants.h"
#include <opencv2/opencv.hpp>

class Global {
  static float m_spinDistance;
  static float m_nearDistance;
  static Point m_convertRatio;
  static float m_minPositionDifference;
  // Qualquer valor menor que essa margem é igual a 0
  static float m_eps;
  static float m_halfAxis;

 public:
  static void setSpinDistance(const float& t_spinDistance);
  static void setNearDistance(const float& t_nearDistance);
  static void setConvertRatio(const Point& t_convertRatio);
  static void setMinPositionDifference(const float& t_minPositionDifference);
  static void setEps(const float& t_eps);
  static void setHalfAxis(const float& t_halfAxis);

  static const float& spinDistance();
  static const float& nearDistance();
  static const Point& convertRatio();
  static const float& minPositionDifference();
  static const float& eps();
  static const float& halfAxis();
};

#endif // GLOBAL_H

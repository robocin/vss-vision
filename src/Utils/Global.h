#ifndef GLOBAL_H
#define GLOBAL_H

#include "Types.h"
#include "EnumsAndConstants.h"
#include <opencv2/opencv.hpp>

class Global {
  static Float m_spinDistance;
  static Float m_nearDistance;
  static Point m_convertRatio;
  static Float m_minPositionDifference;
  // Qualquer valor menor que essa margem é igual a 0
  static Float m_eps;
  static Float m_halfAxis;

public:
  static Void setSpinDistance(const Float &t_spinDistance);
  static Void setNearDistance(const Float &t_nearDistance);
  static Void setConvertRatio(const Point &t_convertRatio);
  static Void setMinPositionDifference(const Float &t_minPositionDifference);
  static Void setEps(const Float &t_eps);
  static Void setHalfAxis(const Float &t_halfAxis);

  static const Float &spinDistance();
  static const Float &nearDistance();
  static const Point &convertRatio();
  static const Float &minPositionDifference();
  static const Float &eps();
  static const Float &halfAxis();
};

#endif // GLOBAL_H

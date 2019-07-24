#include "Global.h"

Void Global::setSpinDistance(const Float &t_spinDistance) {
  m_spinDistance = t_spinDistance;
}

Void Global::setNearDistance(const Float &t_nearDistance) {
  m_nearDistance = t_nearDistance;
}

// Setado na visao
Void Global::setConvertRatio(const Point &t_convertRatio) {
  m_convertRatio = t_convertRatio;
}

Void Global::setMinPositionDifference(const Float &t_minPositionDifference) {
  m_minPositionDifference = t_minPositionDifference;
}

Void Global::setEps(const Float &t_eps) {
  m_eps = t_eps;
}

Void Global::setHalfAxis(const Float &t_halfAxis) {
  m_halfAxis = t_halfAxis;
}

const Float &Global::spinDistance() {
  return m_spinDistance;
}

const Float &Global::nearDistance() {
  return m_nearDistance;
}

const Point &Global::convertRatio() {
  return m_convertRatio;
}

const Float &Global::minPositionDifference() {
  return m_minPositionDifference;
}

const Float &Global::eps() {
  return m_eps;
}

const Float &Global::halfAxis() {
  return m_halfAxis;
}

Float Global::m_spinDistance;
Float Global::m_nearDistance;
Point Global::m_convertRatio;
Float Global::m_minPositionDifference = 2;
Float Global::m_eps = 1e-6;
Float Global::m_halfAxis = 3.5;

#include "Global.h"

void Global::setSpinDistance(const float &t_spinDistance) {
  m_spinDistance = t_spinDistance;
}

void Global::setNearDistance(const float &t_nearDistance) {
  m_nearDistance = t_nearDistance;
}

// Setado na visao
void Global::setConvertRatio(const Point &t_convertRatio) {
  m_convertRatio = t_convertRatio;
}

void Global::setMinPositionDifference(const float &t_minPositionDifference) {
  m_minPositionDifference = t_minPositionDifference;
}

void Global::setEps(const float &t_eps) {
  m_eps = t_eps;
}

void Global::setHalfAxis(const float &t_halfAxis) {
  m_halfAxis = t_halfAxis;
}

const float &Global::spinDistance() {
  return m_spinDistance;
}

const float &Global::nearDistance() {
  return m_nearDistance;
}

const Point &Global::convertRatio() {
  return m_convertRatio;
}

const float &Global::minPositionDifference() {
  return m_minPositionDifference;
}

const float &Global::eps() {
  return m_eps;
}

const float &Global::halfAxis() {
  return m_halfAxis;
}

float Global::m_spinDistance;
float Global::m_nearDistance;
Point Global::m_convertRatio;
float Global::m_minPositionDifference = 5;
float Global::m_eps = 1e-6;
float Global::m_halfAxis = 3.5;

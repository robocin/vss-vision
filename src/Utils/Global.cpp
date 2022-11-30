#include "Global.h"

// Setado na visao
void Global::setConvertRatio(const Point& t_convertRatio) {
  m_convertRatio = t_convertRatio;
}

void Global::setMinPositionDifference(const float& t_minPositionDifference) {
  m_minPositionDifference = t_minPositionDifference;
}

void Global::setEps(const float& t_eps) {
  m_eps = t_eps;
}

const Point& Global::convertRatio() {
  return m_convertRatio;
}

const float& Global::minPositionDifference() {
  return m_minPositionDifference;
}

const float& Global::eps() {
  return m_eps;
}

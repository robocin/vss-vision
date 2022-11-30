#include "kalmanfilter.h"

KalmanFilter::KalmanFilter() :
    K(4, 2),
    P(4, 4),
    x(4, 1),
    A(Matrix2d::createIdentity(4)),
    Q(Matrix2d::createIdentity(4) * 0.4),
    H(Matrix2d::createIdentity(2, 4)),
    R(Matrix2d::createIdentity(2) * 10),
    x_(4, 1),
    P_(4, 4),
    z(2, 1),
    ifInit(false) {
  A(0, 2) = A(1, 3) = 1;
}

KalmanFilter::~KalmanFilter() {
}
/**
 * @brief init Kalman filter
 * @param px
 * @param py
 * @param vx
 * @param vy
 */
void KalmanFilter::init(float px, float py, float vx, float vy) {
  this->x = Matrix2d(4, 1, {px, py, vx, vy});
  this->K = Matrix2d(4, 2);
  this->P = Matrix2d::createIdentity(4) * 5;
  ifInit = true;
}

/**
 * @brief update module of Kalman filter
 * @param px
 * @param py
 * @return
 */
const Matrix2d& KalmanFilter::update(float px, float py) {
  if (ifInit == false) {
    ifInit = true;
    init(px, py, 0, 0);
  }
  z = Matrix2d(2, 1, {px, py});
  x_ = A * x;
  P_ = A * P * A.transpose() + Q;
  K = P_ * H.transpose() * ((H * P_ * H.transpose() + R).inverse());
  x = x_ + K * (z - H * x_);
  P = P_ - K * H * P_;
  return x;
}

const Matrix2d& KalmanFilter::update(Geometry::PT pos) {
  return update(pos.x, pos.y);
}

/**
 * @brief not update just follow
 * @param px
 * @param py
 * @return
 */
const Matrix2d& KalmanFilter::follow(float px, float py) {
  x = Matrix2d(4, 1, {z(0, 0), z(1, 0), px - z(0, 0), py - z(1, 0)});
  return update(px, py);
}

const Matrix2d& KalmanFilter::follow(Geometry::PT pos) {
  return follow(pos.x, pos.y);
}

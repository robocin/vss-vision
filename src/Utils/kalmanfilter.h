#ifndef KALMANFILTER_H
#define KALMANFILTER_H
#include "Utils/matrix2d.h"
#include "Utils/Geometry.h"

/**
 * @brief The KalmanFilter class
 */
class KalmanFilter {
 public:
  KalmanFilter();
  ~KalmanFilter();
  void init(float, float, float, float);
  const Matrix2d& update(float, float);
  const Matrix2d& update(Geometry::PT pos);
  const Matrix2d& follow(float, float);
  const Matrix2d& follow(Geometry::PT pos);

 private:
  Matrix2d K;
  Matrix2d P;
  Matrix2d x;
  Matrix2d A;
  Matrix2d Q;
  Matrix2d H;
  Matrix2d R;
  Matrix2d x_;
  Matrix2d P_;
  Matrix2d z;
  bool ifInit;
};

#endif // KALMANFILTER_H

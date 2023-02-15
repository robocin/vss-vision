#include "Utils.h"

double Utils::to_positive_angle(double angle) {
  return fmod(angle + 2*M_PI, 2 * M_PI);
}

double Utils::smallestAngleDiff(double target, double source) {
  double a;
  a = to_positive_angle(target) - to_positive_angle(source);

  if (a > M_PI) {
    a = a - 2 * M_PI;
  } else if (a < -M_PI) {
    a = a + 2 * M_PI;
  }
  return a;
}

double Utils::to180range(double angle) {
  angle = fmod(angle, 2 * M_PI);
  if (angle < -M_PI) {
    angle = angle + 2 * M_PI;
  } else if (angle > M_PI) {
    angle = angle - 2 * M_PI;
  }
  return angle;
}

double Utils::double_dif(double x, double y) {
  return ((x-y)*(x-y));
}

double Utils::sumOfSquares(cv::Point alfa, cv::Point beta) {
  return (pow(alfa.x - beta.x, 2) + pow(alfa.y - beta.y, 2));
}

double Utils::angle(cv::Point alfa,cv::Point beta) {
  return atan2((beta.y - alfa.y), (alfa.x - beta.x));
}

double Utils::median(std::vector<double> list) {
  double median;
  size_t size = list.size();
  sort(list.begin(), list.end());
  if (size  % 2 == 0)
  {
    median = (list[size / 2 - 1] + list[size / 2]) / 2;
  }
  else 
  {
    median = list[size / 2];
  }

  return median;
}

bool Utils::pairCompareSecond(const std::pair<int, double>& firstElem, const std::pair<int, double>& secondElem) {
  return firstElem.second < secondElem.second;
}

cv::Point2d Utils::getLineParameters(double x1, double y1, double x2, double y2) {
  double a, b;
  a = ((y1 - y2)) / (x1 - x2);
  b = y1 - (a * x1);
  return cv::Point2d(a, b);
}

cv::Point2d Utils::getLineParameters(cv::Point2d p1, cv::Point2d p2) {
  return getLineParameters(p1.x, p1.y, p2.x, p2.y);
}

double Utils::yInLine(cv::Point2d param, double x) {
  return param.y + (param.x * x);
}

double Utils::xInLine(cv::Point2d param, double y) {
  return (y - param.y) / param.x;
}

double Utils::localToGlobalX(double dx, double theta) {
  return dx * cos(theta);
}

double Utils::localToGlobalY(double dx, double theta) {
  return dx * sin(theta);
}

cv::Point2d Utils::bisectorLine(cv::Point2d vertex_center, cv::Point2d pole1, cv::Point2d pole2) {
  if(vertex_center.x == pole1.x) vertex_center.x-=1;
  double inc_A = (vertex_center.y - pole1.y)/(vertex_center.x - pole1.x);
  double inc_B = (vertex_center.y - pole2.y)/(vertex_center.x - pole2.x);
  double bisecAngular = tan((atan(inc_A) + atan(inc_B)) / 2.0);
  double biseclinear = vertex_center.y - vertex_center.x*bisecAngular;
  return cv::Point2d(bisecAngular,biseclinear);
}

std::pair<cv::Point2d, cv::Point2d> Utils::intersectionArc(cv::Point2d line, double h, double a, double k, double b) {
  //curve formula: [(x-h)**2] / a**2 + [(y-k)**2] / b**2 = 1
  //line formula : y = m*x + c ---> y = line.x * x + line.y

  double e = (line.y - k);
  double s = (line.y + line.x*h);
  int x1, x2, y1, y2;
  double Ax, Ay, B, delta;

  Ax = (h*b*b) - (line.x*a*a*e);
  Ay = (s*b*b) + (k*a*a*line.x*line.x);
  B = a*a*line.x*line.x + b*b;
  delta = sqrt(a*a*line.x*line.x + b*b - s*s - k*k + 2*s*k);

  x1 = (Ax + a*b*delta)/B;
  x2 = (Ax - a*b*delta)/B;
  y1 = (Ay + a*b*line.x*delta)/B;
  y2 = (Ay - a*b*line.x*delta)/B;

  return std::make_pair(cv::Point2d(x1, y1) , cv::Point2d(x2, y2));
}

double Utils::inverseAngle(double angle) {
  if(angle<0) {
    angle = 2*M_PI + angle;
    angle = angle + M_PI;
    if(angle > 2* M_PI) {
      angle = angle - 2*M_PI;
    }
    if(angle > M_PI) {
      angle = angle - 2*M_PI;
    }    
  }else{
    angle = angle + M_PI;
    angle = angle - 2*M_PI;
  }
  return angle;
}

Point Utils::convertPositionCmToPixel(const Point &position)
{
  return Point(
    (position.x + Field::size().x / 2) / Global::convertRatio().x,
    (Field::size().y / 2 - position.y) / Global::convertRatio().y
  );
}

Point Utils::convertPositionPixelToCm(const Point &position) {
  return Point(
    position.x * Global::convertRatio().x - Field::size().x / 2, 
    (Field::size().y / 2) - position.y * Global::convertRatio().y
  );
}

double Utils::map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

bool Utils::between(double number, double min_limit, double range)
{
  return (number >= min_limit && number <= min_limit+range);
}

double Utils::bound(double x, double low, double high)
{
  if (x < low) x = low;
  if (x > high) x = high;
  return x;
}

double Utils::linearEquationY(double x_in,cv::Point2d xCoord, cv::Point2d yCoord) {
  double m = (yCoord.y - yCoord.x)/(xCoord.y - xCoord.x);
  double b = yCoord.x - (m*xCoord.x);
  return ((m*x_in)+b);
}

double Utils::mod_vec(cv::Point2d vec) {
  return (sqrt(vec.x*vec.x+vec.y*vec.y));
}

cv::Point2d Utils::desloc_vec(cv::Point2d v1, cv::Point2d v2) {
  return (cv::Point2d(v2.x-v1.x,v2.y-v1.y));
}

double Utils::scale_prod_vec(cv::Point2d v1, cv::Point2d v2) {
  return (v1.x*v2.x+v1.y*v2.y);
}

double Utils::angleBetweenTwoVectors(cv::Point2d v1, cv::Point2d v2) {
  return (acos(scale_prod_vec(v1,v2)/(mod_vec(v1)*mod_vec(v2))));
}

double Utils::reverseAngle(double angle)
{
  if (angle > 0) angle = angle - M_PI;
  else angle = angle + M_PI;

  return angle;
}

double Utils::sign(double value)
{
  double ans = 1;
  if (value < 0) ans = -1;

  return ans;
}

double Utils::gaussian(double r, double delta)
{
  return std::exp(- pow(r,2.0)/(2.0*pow(delta,2.0)));
}

double Utils::angleDouble(cv::Point2d alfa,cv::Point2d beta) {
  return atan2((beta.y - alfa.y), (alfa.x - beta.x));
}

double Utils::crossProduct(cv::Point2d& alpha, cv::Point2d& beta) {
  return alpha.x*beta.y - alpha.y*beta.x;
}

bool Utils::isTeamColor(const int &t_color) {
  for (auto color : {Color::BLUE, Color::YELLOW}) {
    if (color == t_color) {
      return true;
    }
  }
  return false;
}

bool Utils::isRobotColor(const int &t_color) {
  if (isTeamColor(t_color)) {
    return false;
  }
  for (auto color : Color::_values()) {
    if (color == t_color) {
      return true;
    }
  }
  return false;
}

#include "WarpCorrection.h"

WarpCorrection::WarpCorrection() {
}

WarpCorrection::~WarpCorrection() {
}

void WarpCorrection::init(std::map<std::string, int>) {
}

void WarpCorrection::initFromFile(std::string path, cv::Point2d* convert) {
  QFile file(QString::fromStdString(path));

  if (!file.open(QIODevice::ReadOnly)) {
    std::cout << "Couldn't open file : " << path << std::endl;
    exit(1);
  }

  QByteArray data = file.readAll();

  QJsonDocument loadDoc(QJsonDocument::fromJson(data));

  QJsonObject pointsJson = loadDoc.object();

  std::string pointString = "point";

  QJsonObject value;

  this->_pointsLocker.lock();

  for (int i = 1; i <= 4; i++) {
    std::string tempKey = pointString + std::to_string(i);
    value = pointsJson[tempKey.c_str()].toObject();
    this->_correctionPoints[i - 1].x = value["x"].toInt();
    this->_correctionPoints[i - 1].y = value["y"].toInt();
  }

  file.close();

  std::vector<cv::Point> boxPoints;

  for (int i = 0; i < 4; i++) {
    boxPoints.push_back(_correctionPoints[i]);
  }

  cv::RotatedRect box = cv::minAreaRect(cv::Mat(boxPoints));

  convert->x = (170.0 / ((float) box.boundingRect().width));
  convert->y = (130.0 / ((float) box.boundingRect().height));

  cv::Point2f dstPoints[4];

  dstPoints[0] = cv::Point(0, 0);
  dstPoints[1] = cv::Point(0, box.boundingRect().height - 1);
  dstPoints[2] = cv::Point(box.boundingRect().width - 1, box.boundingRect().height - 1);
  dstPoints[3] = cv::Point(box.boundingRect().width - 1, 0);

  this->_mapsLocker.lock();

  this->_warpPespectiveMatrix = cv::getPerspectiveTransform(_correctionPoints, dstPoints);

  this->_matrixSize = cv::Size(box.boundingRect().width, box.boundingRect().height);

  this->defineMaps();

  this->_mapsLocker.unlock();
  this->_pointsLocker.unlock();
}

void WarpCorrection::defineMaps() {
  cv::Mat inverseTransMatrix;

  cv::invert(this->_warpPespectiveMatrix, inverseTransMatrix);

  cv::Mat mapX, mapY, srcTM;
  srcTM = inverseTransMatrix.clone();

  mapX.create(this->_matrixSize, CV_32FC1);
  mapY.create(this->_matrixSize, CV_32FC1);

  double M11, M12, M13, M21, M22, M23, M31, M32, M33;
  M11 = srcTM.at<double>(0, 0);
  M12 = srcTM.at<double>(0, 1);
  M13 = srcTM.at<double>(0, 2);

  M21 = srcTM.at<double>(1, 0);
  M22 = srcTM.at<double>(1, 1);
  M23 = srcTM.at<double>(1, 2);

  M31 = srcTM.at<double>(2, 0);
  M32 = srcTM.at<double>(2, 1);
  M33 = srcTM.at<double>(2, 2);

  for (int y = 0; y < this->_matrixSize.height; y++) {
    double fy = static_cast<double>(y);
    for (int x = 0; x < this->_matrixSize.width; x++) {
      double fx = static_cast<double>(x);
      double w = ((M31 * fx) + (M32 * fy) + M33);
      if (w != 0.0f) {
        w = (1.0f / w);
      } else {
        w = 0.0f;
      }
      float newX = static_cast<float>(((M11 * fx) + (M12 * fy) + M13) * w);
      float newY = static_cast<float>(((M21 * fx) + (M22 * fy) + M23) * w);
      mapX.at<float>(y, x) = newX;
      mapY.at<float>(y, x) = newY;
    }
  }

  this->_transformationX.create(this->_matrixSize, CV_16SC2);
  this->_transformationY.create(this->_matrixSize, CV_16UC1);

  cv::convertMaps(mapX, mapY, this->_transformationX, this->_transformationY, false);
}

void WarpCorrection::setup(std::string, int) {
}

cv::Mat WarpCorrection::run(cv::Mat& frame) {
  cv::Mat tmp = cv::Mat::zeros(this->_matrixSize, CV_8UC3);
  cv::remap(frame, tmp, this->_transformationX, this->_transformationY, cv::INTER_LINEAR);

  // Masking corners
  int w = this->_matrixSize.width * (1 / (float) 17);
  int h = this->_matrixSize.height * (45 / (float) 130);

  // top left
  cv::rectangle(tmp, cv::Rect(0, 0, w, h), cv::Scalar(0, 0, 0), -1);
  // top right
  cv::rectangle(tmp, cv::Rect(this->_matrixSize.width - w, 0, w, h), cv::Scalar(0, 0, 0), -1);
  // bottom left
  cv::rectangle(tmp, cv::Rect(0, this->_matrixSize.height - h, w, h), cv::Scalar(0, 0, 0), -1);
  // bottom right
  cv::rectangle(tmp,
                cv::Rect(this->_matrixSize.width - w, this->_matrixSize.height - h, w, h),
                cv::Scalar(0, 0, 0),
                -1);

  this->_frameLocker.lock();
  tmp.copyTo(this->_warpPespectiveFrame);
  this->_frameLocker.unlock();

  return tmp;
}

void WarpCorrection::getDebugFrame(cv::Mat& frame) {
  this->_frameLocker.lock();

  if (this->_warpPespectiveFrame.empty()) {
    this->_warpPespectiveFrame = cv::Mat::zeros(640, 480, CV_8UC3);
  }
  this->_warpPespectiveFrame.copyTo(frame);

  this->_frameLocker.unlock();
}

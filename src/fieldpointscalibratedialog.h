#ifndef FIELDPOINTSCALIBRATEDIALOG_H
#define FIELDPOINTSCALIBRATEDIALOG_H

#include <QDialog>
#include <QKeyEvent>

#include <CameraManager/CameraManager.h>
#include <Vision/ImageProcessing/WarpCorrection.h>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMouseEvent>
#include <QTimer>
#include <iostream>
#include <opencv2/opencv.hpp>

#define YELLOW_SCALAR cv::Scalar(0, 255, 255)
#define BLUE_SCALAR cv::Scalar(255, 0, 0)
#define RED_SCALAR cv::Scalar(0, 0, 255)
#define LINE_THICKNESS 1
#define CIRCLE_RADIUS 2.0
#define OPENCVSTORAGE "opencv_storage"
#define HALF "half"

namespace Ui {
  class FieldPointsCalibrateDialog;
}

class FieldPointsCalibrateDialog : public QDialog {
  Q_OBJECT

 public:
  explicit FieldPointsCalibrateDialog(const bool videoFlag, QWidget* parent = 0);
  ~FieldPointsCalibrateDialog();

 protected:
  void keyPressEvent(QKeyEvent* e);
  void mousePressEvent(QMouseEvent* event);
  void showEvent(QShowEvent* event);

 private slots:
  void on_buttonBox_accepted();
  void updateFrame();

  void on_buttonBox_rejected();

 private:
  Ui::FieldPointsCalibrateDialog* ui;
  cv::Point _limitPoints[4];
  int _selectedPointIndex, _frameRows, _frameCols;
  cv::Mat _cameraFrame;
  std::string _filePath;
  bool _videoFlag;
  QTimer* _updateFrameTimer;

  void getPointsFromFile(std::string path);
  void drawPoints();
};

#endif // FIELDPOINTSCALIBRATEDIALOG_H

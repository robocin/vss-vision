#include <CameraManager/CameraThread.h>
#include <TBBThreadManager.h>
#include <visionthread.h>
#include <QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Entity/Entity.h"
#include "Field/Field.h"
#include "Windows/MainVSSWindow.h"
#include "maggicsegmentationdialog.h"

int main(int argc, char* argv[]) {
  TBBThreadManager Graph;

  cv::useOptimized();
  Logging::init();
  QApplication app(argc, argv);
  MainVSSWindow vsswindow;

  QObject::connect(&vsswindow, SIGNAL(startCameraUpdate()), &Graph, SLOT(cameraStart()));
  QObject::connect(&vsswindow, SIGNAL(pauseCameraUpdate()), &Graph, SLOT(cameraPause()));
  QObject::connect(&vsswindow, SIGNAL(enableVisionThread(bool)), &Graph, SLOT(visionStart()));
  QObject::connect(&vsswindow, SIGNAL(finishVisionThread()), &Graph, SLOT(visionPause()));

  vsswindow.showMaximized();
  return app.exec();
}

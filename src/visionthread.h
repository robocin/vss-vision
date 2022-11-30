#ifndef VSS_VISION_VISIONTHREAD_H
#define VSS_VISION_VISIONTHREAD_H

#include <QThread>
#include <QMutex>
#include <iostream>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <Vision/Vision.h>
#include <CameraManager/CameraManager.h>

class MainWindow;

class VisionThread : public QThread {
  Q_OBJECT
 public:
  VisionThread();
  ~VisionThread();

 public slots:
  void pause();
  void startWork();
  void finish();
  void enableResultSignal(bool enable);

 signals:
  void resultReady();

 private:
  QMutex _threadMutex;
  QWaitCondition _threadController;

  bool _isRunning;
  bool _hasFinished;
  bool _resultSignalEnabled;

  void run() override;
};

#endif // VSS_VISION_VISIONTHREAD_H

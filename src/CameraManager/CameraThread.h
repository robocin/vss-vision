#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <QMutex>
#include <iostream>
#include <QWaitCondition>
#include <CameraManager/CameraManager.h>

class CameraThread : public QThread
{
  Q_OBJECT
public:
  CameraThread();
  ~CameraThread();


public slots:
  void pause();
  void startWork();
  void finish();
  void enableResultSignal(bool enabled);

private:
  QMutex _threadMutex;
  QWaitCondition _threadController;

  bool _isRunning;
  bool _hasFinished;
  bool _enableResultSignal;

  void run() override;
signals:
  void updatedFrame();

};

#endif // CAMERATHREAD_H

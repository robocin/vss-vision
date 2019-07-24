#include "CameraThread.h"

CameraThread::CameraThread()
{
  this->_isRunning = false;
  this->_hasFinished = false;
  this->_enableResultSignal = false;
}

CameraThread::~CameraThread()
{
   this->finish();
  this->wait();
}

void CameraThread::enableResultSignal(bool enabled)
{
  this->_enableResultSignal = enabled;
}

void CameraThread::pause()
{
  this->_isRunning = false;
}

void CameraThread::finish()
{
  this->_hasFinished = true;
  this->_isRunning = false;
  this->_threadController.wakeAll();
}

void CameraThread::startWork()
{
  this->_isRunning = true;
  this->_threadController.wakeAll();
}

void CameraThread::run()
{
  while(!this->_hasFinished) {
    this->_threadMutex.lock();
    this->_threadController.wait(&this->_threadMutex);
    this->_threadMutex.unlock();

    if (this->_hasFinished) break;

    while(this->_isRunning) {

      CameraManager::singleton().updateFrame();
      if (this->_enableResultSignal) {
        emit updatedFrame();
      }

      if (CameraManager::singleton().getCaptureType() == videoCapture) usleep(29000);
    }
  }
}

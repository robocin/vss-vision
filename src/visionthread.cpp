#include "visionthread.h"

VisionThread::VisionThread()
{
  this->_hasFinished = false;
  this->_isRunning = false;
  this->_resultSignalEnabled = false;
}

VisionThread::~VisionThread()
{
  this->finish();
  this->wait();
}

void VisionThread::pause()
{
  this->_isRunning = false;
}

void VisionThread::finish()
{
  this->_hasFinished = true;
  this->_isRunning = false;
  this->_threadController.wakeAll();
}

void VisionThread::startWork()
{
  this->_isRunning = true;
  this->_threadController.wakeAll();
}

void VisionThread::enableResultSignal(bool enable)
{
  this->_resultSignalEnabled = enable;
}

void VisionThread::run()
{
  while (!this->_hasFinished) {
    this->_threadMutex.lock();
    this->_threadController.wait(&this->_threadMutex);
    this->_threadMutex.unlock();

    if (this->_hasFinished) break;

    cv::Mat frame = CameraManager::singleton().getCurrentFrame();
    QTime timeStamp = CameraManager::singleton().getCurrentFrameTimeStamp();

    Vision::singleton().update(frame,timeStamp);


    if (this->_resultSignalEnabled) {
      emit resultReady();
    }
  }
}

#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <tbb/flow_graph.h>
#include <CameraManager/CameraManager.h>
#include <Vision/Vision.h>
#include <stdio.h>
#include <QObject>
#include "Entity/Entity.h"
//#define WITHFEEDBACK

using namespace tbb::flow;

struct cameraBody {
  bool &cameraStop;
  cameraBody(bool &x): cameraStop(x) {}
  bool operator()(tbb::flow::continue_msg) const {

    CameraManager::singleton().updateFrame();
    if (CameraManager::singleton().getCaptureType() == videoCapture) usleep(29000);

    return !cameraStop;
  }
};

struct visionBody {
  bool *visionStop;
  visionBody(bool &x): visionStop(&x) {}
  void operator()(tbb::flow::continue_msg) const {

    if(!(*visionStop)) {
      cv::Mat frame;
      CameraManager::singleton().getCurrentFrame(frame);
      QTime timeStamp = CameraManager::singleton().getCurrentFrameTimeStamp();

      Vision::singleton().update(frame,timeStamp);
    }

  }
};

class TBBThreadManager :public QObject
{
  Q_OBJECT
public:

  tbb::flow::graph g;


  TBBThreadManager();
  ~TBBThreadManager();


public slots:
  void cameraPause();
  void cameraStart();

  void visionPause();
  void visionStart();

  void startAll();
  void pauseAll();

private:
   tbb::flow::source_node <tbb::flow::continue_msg> _cameraNode;
   tbb::flow::function_node<tbb::flow::continue_msg, tbb::flow::continue_msg> _visionNode;
   tbb::flow::indexer_node<tbb::flow::continue_msg, tbb::flow::continue_msg> _indexerNode;

   bool _cameraStop;
   bool _visionStop;


};

#endif // THREADMANAGER_H

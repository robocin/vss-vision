#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#ifndef Q_MOC_RUN
#if defined(emit)
    #undef emit
    #include <tbb/flow_graph.h>
    #define emit // restore the macro definition of "emit", as it was defined in gtmetamacros.h
#else
    #include <tbb/flow_graph.h>
#endif // defined(emit)
#endif // Q_MOC_RUN

#include <CameraManager/CameraManager.h>
#include <Vision/Vision.h>
#include <stdio.h>
#include <QObject>
#include "Entity/Entity.h"
//#define WITHFEEDBACK

struct cameraBody {
  bool *cameraStop;
  cameraBody(bool *x): cameraStop(x) {}
  tbb::flow::continue_msg operator()(tbb::flow_control &fc) const {
    // if (!cameraStop) return false;

    if (*cameraStop) {
      fc.stop();
      return {};
    } else {
      CameraManager::singleton().updateFrame();
      if (CameraManager::singleton().getCaptureType() == videoCapture) usleep(29000);
      return {};
    }
  }
};

struct visionBody {
  bool *visionStop;
  visionBody(bool *x): visionStop(x) {}
  void operator()(tbb::flow::continue_msg) const {
//      if (!visionStop) return false;
      if (!visionStop) return;
      cv::Mat frame;
      CameraManager::singleton().getCurrentFrame(frame);
      QTime timeStamp = CameraManager::singleton().getCurrentFrameTimeStamp();

      Vision::singleton().update(frame,timeStamp);

//    return !*visionStop;

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
   tbb::flow::input_node <tbb::flow::continue_msg> _cameraNode;
   tbb::flow::limiter_node <tbb::flow::continue_msg> _limiterNode;
//   tbb::flow::source_node <tbb::flow::continue_msg> _visionNode;
   tbb::flow::function_node<tbb::flow::continue_msg, tbb::flow::continue_msg> _visionNode;
   tbb::flow::indexer_node<tbb::flow::continue_msg, tbb::flow::continue_msg> _indexerNode;

   bool _cameraStop;
   bool _visionStop;


};

#endif // THREADMANAGER_H

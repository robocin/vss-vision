#include "TBBThreadManager.h"

TBBThreadManager::TBBThreadManager()
  : _cameraNode(g, cameraBody(this->_cameraStop), false),
    _visionNode(g, tbb::flow::unlimited, visionBody(this->_visionStop)),
    _indexerNode(g){
  this->_cameraStop = false;
  this->_visionStop = true;
  tbb::flow::make_edge(this->_cameraNode, this->_visionNode);
#ifdef WITHFEEDBACK
  tbb::flow::make_edge(this->_visionNode, input_port<0>(this->_indexerNode));
  //tbb::flow::make_edge(this->_indexerNode, this->_limiter.decrement);
#endif
}

TBBThreadManager::~TBBThreadManager() {
  this->cameraPause();
  g.wait_for_all();
  tbb::flow::remove_edge(this->_cameraNode, this->_visionNode);
#ifdef WITHFEEDBACK
  tbb::flow::remove_edge(this->_visionNode, input_port<0>(this->_indexerNode));
  //tbb::flow::remove_edge(this->_indexerNode, this->_limiter.decrement);
#endif
}

void TBBThreadManager::cameraPause() {
  this->_cameraStop = true;
  this->_cameraNode.try_consume();
}

void TBBThreadManager::cameraStart() {
  this->_cameraStop = false;
  this->_cameraNode.activate();
}

void TBBThreadManager::visionPause() {
  this->_visionStop = true;
}

void TBBThreadManager::visionStart() {
  this->_visionStop = false;
}

void TBBThreadManager::startAll() {
  this->visionStart();
  this->cameraStart();
}

void TBBThreadManager::pauseAll() {
  this->visionPause();
  this->cameraPause();
}




#include "TBBThreadManager.h"

TBBThreadManager::TBBThreadManager()
  : _cameraNode(g, cameraBody(&this->_cameraStop)),
    _limiterNode(g,1),
    _visionNode(g, tbb::flow::serial, visionBody(&this->_visionStop)),
//    _visionNode(g, tbb::flow::unlimited, visionBody(&this->_visionStop)),
//    _visionNode(g, visionBody(&this->_visionStop), false),
    _indexerNode(g){
  this->_cameraStop = false;
  this->_visionStop = true;
  tbb::flow::make_edge(this->_limiterNode, this->_visionNode);
  tbb::flow::make_edge(this->_visionNode, this->_limiterNode.decrementer());
  tbb::flow::make_edge(this->_cameraNode, this->_limiterNode);
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
//  this->_visionNode.try_consume();
}

void TBBThreadManager::visionStart() {
  this->_visionStop = false;
//  this->_visionNode.activate();
}

void TBBThreadManager::startAll() {
  this->visionStart();
  this->cameraStart();
}

void TBBThreadManager::pauseAll() {
  this->visionPause();
  this->cameraPause();
}




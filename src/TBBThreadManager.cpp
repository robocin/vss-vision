#include "TBBThreadManager.h"

TBBThreadManager::TBBThreadManager()
  : _cameraNode(g, cameraBody(this->_cameraStop), false),
    _visionNode(g, tbb::flow::unlimited, visionBody(this->_visionStop)),
    _strategyNode(g, tbb::flow::unlimited, strategyBody(this->_strategyStop)),
    //_navigationNode(g, tbb::flow::unlimited, navigationBody(this->_strategyStop)),
    _indexerNode(g),
    _limiter(g, 1),
    _strategyLimiter(g, 1) {
  this->_cameraStop = false;
  this->_visionStop = true;
  this->_strategyStop = true;
  tbb::flow::make_edge(this->_cameraNode, this->_limiter);
  tbb::flow::make_edge(this->_limiter, this->_visionNode);
#ifdef WITHFEEDBACK
  tbb::flow::make_edge(this->_visionNode, this->_strategyLimiter);
  tbb::flow::make_edge(this->_strategyLimiter, this->_strategyNode);
  tbb::flow::make_edge(this->_strategyNode, this->_strategyLimiter.decrement);
  tbb::flow::make_edge(this->_visionNode, input_port<0>(this->_indexerNode));
  tbb::flow::make_edge(this->_indexerNode, this->_navigationNode);
  tbb::flow::make_edge(this->_navigationNode, this->_limiter.decrement);
#endif
#ifndef WITHFEEDBACK
  tbb::flow::make_edge(this->_visionNode, this->_strategyNode);
  tbb::flow::make_edge(this->_strategyNode, this->_limiter.decrement);
#endif
}

TBBThreadManager::~TBBThreadManager() {
  this->cameraPause();
  g.wait_for_all();
  tbb::flow::remove_edge(this->_cameraNode, this->_limiter);
  tbb::flow::remove_edge(this->_limiter, this->_visionNode);
#ifdef WITHFEEDBACK
  tbb::flow::remove_edge(this->_visionNode, this->_strategyLimiter);
  tbb::flow::remove_edge(this->_strategyLimiter, this->_strategyNode);
  tbb::flow::remove_edge(this->_strategyNode, this->_strategyLimiter.decrement);
  tbb::flow::remove_edge(this->_visionNode, input_port<0>(this->_indexerNode));
  tbb::flow::remove_edge(this->_indexerNode, this->_navigationNode);
  tbb::flow::remove_edge(this->_navigationNode, this->_limiter.decrement);
#endif
#ifndef WITHFEEDBACK
  tbb::flow::remove_edge(this->_visionNode, this->_strategyNode);
  tbb::flow::remove_edge(this->_strategyNode, this->_limiter.decrement);
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

void TBBThreadManager::strategyPause() {
  this->_strategyStop = true;
}

void TBBThreadManager::strategyStart() {
  this->_strategyStop = !this->_strategyStop;
}

void TBBThreadManager::startAll() {
  this->strategyStart();
  this->visionStart();
  this->cameraStart();
}

void TBBThreadManager::pauseAll() {
  this->strategyStart();
  this->visionPause();
  this->cameraPause();
}




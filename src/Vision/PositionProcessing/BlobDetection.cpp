#include "BlobDetection.h"
#include <iostream>

BlobDetection::BlobDetection()
{
  memset(this->_colorIndex,-1,sizeof(this->_colorIndex));
  this->debugSrc = cv::Mat::zeros(480,640,CV_8UC3);
}

void BlobDetection::run(std::vector< std::vector<Run> > runs, int rows, int cols)
{
  //std::cout << rows <<" aqui "<< cols << std::endl;
  cv::Mat currentFrame = cv::Mat::zeros(rows,cols,CV_8UC3);

  this->_runs = runs;
  this->findBlobs(currentFrame);
  this->matchBlobs(currentFrame);

  this->_frameLocker.lock();
  currentFrame.copyTo(this->debugSrc);
  this->_frameLocker.unlock();
}

void BlobDetection::init()
{
  initDefault();
}

void BlobDetection::getDebugFrame(cv::Mat& frame)
{
  this->_frameLocker.lock();
  this->debugSrc.copyTo(frame);
  this->_frameLocker.unlock();
}

void BlobDetection::saveParam()
{
  this->saveXML();
}

void BlobDetection::findBlobs(cv::Mat& debugFrame) {

  memset(_clusterCount,0,sizeof(_clusterCount));

  uchar cor;
  int diff;

  for(int i = NoCOL ; i < ColorStrange ; ++i) {
    for (int j=0; j < CLUSTERSPERCOLOR; j++) {
      blob[i][j].valid = false;
      blob[i][j].position = cv::Point(0,0);
      blob[i][j].area = 0;
    }
  }

  Run r1, r2;
  unsigned long i1, i2; //indexes for first and second row

  // union find
  for(unsigned long row = 1 ; row < this->_runs.size() ; row++) {
    i1=0, i2=0;

    while(i2 < this->_runs[row].size() && i1 < this->_runs[row-1].size()) {
      r1 = this->_runs[row-1][i1], r2 = this->_runs[row][i2];

      if (r1.color == r2.color &&
          ( (r2.start <= r1.start && r1.start < r2.start+r2.width)
            || (r1.start <= r2.start && r2.start < r1.start+r1.width) ) ) {

        if (r1.parent == -1) {
          r1.parent = i2;
          r1.parentRow = row;

          r2.areaBlob += r1.areaBlob;
          r2.sumX += r1.sumX;
          r2.sumY += r1.sumY;
        }
      }

      this->_runs[row-1][i1] = r1;
      this->_runs[row][i2] = r2;

      diff = (r2.start + r2.width) - (r1.start + r1.width);

      if(diff >= 0) i1++;
      if(diff <= 0) i2++;

    }

  }

  // turning fathers into blobs
  Blob varBlob;
  Run r;
  for(unsigned long i = 0 ; i < this->_runs.size() ; i++) {

    for(unsigned long j  = 0 ; j < this->_runs[i].size() ; j++) {
      r = this->_runs[i][j];

      if(r.parent == -1) {
         if(Utils::between(r.areaBlob, this->_minSize, this->_maxSize - this->_minSize) ||
            (r.color == OrangeCOL && Utils::between(r.areaBlob, this->_minSizeBall, this->_maxSizeBall - this->_minSizeBall)) ||
            ((r.color == BlueCOL || r.color == YellowCOL) && Utils::between(r.areaBlob, this->_minTeamSize, this->_maxTeamSize - this->_minTeamSize)) ) {

          cor = this->_runs[i][j].color;

          if(_clusterCount[cor] < NUMBEROFCOLOR) {
            blob[cor][_clusterCount[cor]].position.x = r.sumY / r.areaBlob;
            blob[cor][_clusterCount[cor]].position.y = r.sumX / this->_runs[i][j].areaBlob;
            blob[cor][_clusterCount[cor]].area = r.areaBlob;
            blob[cor][_clusterCount[cor]].valid = true;
            blob[cor][_clusterCount[cor]].id = _clusterCount[cor];
            blob[cor][_clusterCount[cor] + 1].valid = false;
            _clusterCount[cor]++;

            //draw blob in screen
            cv::circle(debugFrame,blob[cor][_clusterCount[cor]-1].position,5,cv::Scalar(255,255,255),1, cv::LINE_AA);
          }
        }
      }

    }
  }
}

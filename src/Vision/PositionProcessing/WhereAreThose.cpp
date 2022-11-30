#include "WhereAreThose.h"
#include <iostream>

BlobDetection::BlobDetection() {
  memset(this->_colorIndex, -1, sizeof(this->_colorIndex));
  this->debugSrc = cv::Mat::zeros(480, 640, CV_8UC3);
}

void BlobDetection::run(std::vector<Entity>& entities,
                        std::vector<std::vector<Run>> runs,
                        int rows,
                        int cols) {
  cv::Mat currentFrame = cv::Mat::zeros(rows, cols, CV_8UC3);

  this->_runLengthEncoding = runs;
  this->findBlobs(currentFrame);
  this->matchBlobs(entities, currentFrame);

  this->_frameLocker.lockForWrite();
  this->debugSrc = currentFrame;
  this->_frameLocker.unlock();
}

void BlobDetection::init() {
  initDefault();
}

cv::Mat BlobDetection::getDebugFrame() {
  this->_frameLocker.lockForRead();
  cv::Mat frame = this->debugSrc;
  this->_frameLocker.unlock();
  return frame;
}

void BlobDetection::saveParam() {
  this->saveXML();
}

void BlobDetection::findBlobs(cv::Mat& debugFrame) {

  memset(_numberOfCluster, 0, sizeof(_numberOfCluster));

  uchar cor;

  for (i = NoCOL; i < ColorStrange; ++i) {
    blob[i][0].valid = false;
    blob[i][0].position = cv::Point(0, 0);
    blob[i][0].element = 0;
  }
  for (int g = 1; g < this->_runLengthEncoding.size(); g++) {

    for (int h = 0; h < this->_runLengthEncoding[g].size(); h++) {
      cor = this->_runLengthEncoding[g][h].color;
      int end = this->_runLengthEncoding[g][h].start + this->_runLengthEncoding[g][h].width;
      register int lastLine = 0;
      while (g - 1 >= 0 && lastLine < this->_runLengthEncoding[g - 1].size() &&
             this->_runLengthEncoding[g - 1][lastLine].start <=
                 end) { // não sei por que que ta dando o banzo ainda

        if (this->_runLengthEncoding[g - 1][lastLine].start +
                    this->_runLengthEncoding[g - 1][lastLine].width >=
                this->_runLengthEncoding[g][h].start &&
            this->_runLengthEncoding[g - 1][lastLine].color == cor) {

          // pergunto se ele não tem pai faço com que o de baixo vire pai do de cima
          if (this->_runLengthEncoding[g - 1][lastLine].parent == -1) {

            this->_runLengthEncoding[g - 1][lastLine].parent = h;
            this->_runLengthEncoding[g - 1][lastLine].subsetCol = g - 1;
            this->_runLengthEncoding[g][h].areaBlob +=
                this->_runLengthEncoding[g - 1][lastLine].areaBlob;
            this->_runLengthEncoding[g][h].mediax +=
                this->_runLengthEncoding[g - 1][lastLine].mediax;
            this->_runLengthEncoding[g][h].mediay +=
                this->_runLengthEncoding[g - 1][lastLine].mediay;
          }
        }

        lastLine++;
      }
    }
  }
  Blob varBlob;
  for (int g = 0; g < this->_runLengthEncoding.size(); g++) {

    for (int h = 0; h < this->_runLengthEncoding[g].size(); h++) {
      if (this->_runLengthEncoding[g][h].parent == -1) {
        if ((this->_runLengthEncoding[g][h].areaBlob >= this->_minSize &&
             this->_runLengthEncoding[g][h].areaBlob <= this->_maxSize) ||
            (this->_runLengthEncoding[g][h].color == OrangeCOL &&
             this->_runLengthEncoding[g][h].areaBlob >= this->_minSizeBall &&
             this->_runLengthEncoding[g][h].areaBlob <= this->_maxSizeBall)) {
          cor = this->_runLengthEncoding[g][h].color;
          if (_numberOfCluster[cor] < NUMBEROFCOLOR) {
            blob[cor][_numberOfCluster[cor]].position.x =
                this->_runLengthEncoding[g][h].mediay / this->_runLengthEncoding[g][h].areaBlob;
            blob[cor][_numberOfCluster[cor]].position.y =
                this->_runLengthEncoding[g][h].mediax / this->_runLengthEncoding[g][h].areaBlob;
            blob[cor][_numberOfCluster[cor]].element = this->_runLengthEncoding[g][h].areaBlob;
            blob[cor][_numberOfCluster[cor]].valid = true;
            blob[cor][_numberOfCluster[cor] + 1].valid = false;
            _numberOfCluster[cor]++;
            cv::circle(debugFrame,
                       blob[cor][_numberOfCluster[cor] - 1].position,
                       5,
                       cv::Scalar(255, 255, 255),
                       2);
          }
        }
      }
    }
  }
  this->_runLengthEncoding.clear();
}

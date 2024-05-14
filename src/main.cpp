#include <opencv2/core/persistence.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Entity/Entity.h"
#include "Field/Field.h"
#include "Vision/PositionProcessing/runlengthencoding.h"
#include "Vision/Vision.h"
#include "Utils/Utils.h"

int main(int argc, char *argv[]) {
  cv::useOptimized();

  Utils::FrameType frametype = Utils::FrameType::Tracked;
  if(argv[1] != NULL) {
    if(strcmp(argv[1], "-s") == 0) {
      frametype = Utils::FrameType::Segmented;
    }
  }

  Vision& vis = Vision::singleton();

  // cv::Mat frame = cv::Mat::zeros(FRAME_HEIGHT_DEFAULT, FRAME_WIDTH_DEFAULT, CV_8UC3) * 255;
  cv::Mat frame = cv::imread("../image.png");

  cv::Mat res = vis.update(frame, frametype);

  std::cout << "Processing done" << std::endl;
  cv::imwrite("../segmented.png", res);

  return 0;
}

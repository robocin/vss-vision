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

  Utils::HUE hueList = {
    {10, Color::RED}, 
    {15.0, Color::ORANGE}, 
    {40.0, Color::YELLOW}, 
    {97.0, Color::GREEN}, 
    {150.0, Color::CYAN}, 
    {200.0, Color::BLUE}, 
    {220.0, Color::PINK}
  };

  Vision& vis = Vision::singleton(hueList);

  // cv::Mat frame = cv::Mat::zeros(FRAME_HEIGHT_DEFAULT, FRAME_WIDTH_DEFAULT, CV_8UC3) * 255;
  cv::Mat frame = cv::imread("../image.png");

  cv::Mat res = vis.update(frame, frametype);

  std::cout << "Processing done" << std::endl;
  cv::imwrite("../segmented.png", res);

  return 0;
}

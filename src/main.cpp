#include <opencv2/core/persistence.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Entity/Entity.h"
#include "Field/Field.h"
#include "Vision/PositionProcessing/runlengthencoding.h"
#include "Vision/Vision.h"
#include "Utils/Utils.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <Python.h>

namespace py=pybind11;

Utils::FrameType frametype = Utils::FrameType::Tracked;
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

py::array run_seg(py::array_t<uint8_t>& img) {
  py::buffer_info buf = img.request();
  cv::Mat frame(buf.shape[0], buf.shape[1], CV_8UC3, (unsigned char*)buf.ptr);

  cv::Mat image = vis.update(frame, frametype);

  // std::cout << "received" << std::endl;
  // return vis.update(frame, frametype);
  // cv::Mat image = cv::imread("image.png");

  return py::array({image.rows, image.cols, static_cast<int>(image.channels())}, image.data);
}


// int run_seg(int arg) {
// 
//   return 1234 - arg;
// }


PYBIND11_MODULE(_vss_vision, m) {
  m.doc() = "vision lerolero";
  m.def("run_seg", run_seg, "run segmentation on frame");
}


// int main(int argc, char *argv[]) {
//   cv::useOptimized();
// 
//   Utils::FrameType frametype = Utils::FrameType::Tracked;
//   if(argv[1] != NULL) {
//     if(strcmp(argv[1], "-s") == 0) {
//       frametype = Utils::FrameType::Segmented;
//     }
//   }
// 
//   Utils::HUE hueList = {
//     {10, Color::RED}, 
//     {15.0, Color::ORANGE}, 
//     {40.0, Color::YELLOW}, 
//     {97.0, Color::GREEN}, 
//     {150.0, Color::CYAN}, 
//     {200.0, Color::BLUE}, 
//     {220.0, Color::PINK}
//   };
// 
//   Vision& vis = Vision::singleton(hueList);
// 
//   // cv::Mat frame = cv::Mat::zeros(FRAME_HEIGHT_DEFAULT, FRAME_WIDTH_DEFAULT, CV_8UC3) * 255;
//   cv::Mat frame = cv::imread("../image.png");
// 
//   cv::Mat res = vis.update(frame, frametype);
// 
//   std::cout << "Processing done" << std::endl;
//   cv::imwrite("../segmented.png", res);
// 
//   return 0;
// }

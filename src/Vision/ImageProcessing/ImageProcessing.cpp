#include "ImageProcessing.h"

ArucoDetection::ArucoDetection() {
    this->parameters = cv::aruco::DetectorParameters::create();
    this->dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);
}

void ArucoDetection::detection(cv::Mat& frame) {
    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;

    cv::aruco::detectMarkers(frame, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);

    if(markerIds.size() < 1) {
        return;
    }

    cv::Mat outputImage = frame.clone();
    for (int i = 0; i < markerIds.size(); i++) {
    //   std::cout << "Marker ID: " << markerIds[i] << std::endl;
    //   std::cout << "Corners: " << std::endl << markerCorners[i] << std::endl;
      cv::Point2f center = (markerCorners[i][0] + markerCorners[i][1] + markerCorners[i][2] + markerCorners[i][3]) / 4;
      cv::circle(outputImage, center, 3, cv::Scalar(150, 0, 255), -1);
    //   std::cout << "Center: " << center << std::endl;
    }

    cv::aruco::drawDetectedMarkers(outputImage, markerCorners, markerIds);
    
    mut.lock();
    outputImage.copyTo(frame);
    mut.unlock();
}

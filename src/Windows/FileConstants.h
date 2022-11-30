#ifndef VSS_VISION_FILECONSTANTS_H
#define VSS_VISION_FILECONSTANTS_H

#include <string>

class FileConstants {
 public:
  static constexpr const char* fieldLimits = "Config/fieldLimits.json";
  ;
  static constexpr const char* secondaryColor = "Config/SecondaryColor.json";
  static constexpr const char* cameraConfig = "Config/CameraConfig.json";
  static constexpr const char* videoPath = "Config/Video.json";
  static constexpr const char* segmentationConfig = "Config/Segmentation/Default.json";
};

#endif // VSS_VISION_FILECONSTANTS_H

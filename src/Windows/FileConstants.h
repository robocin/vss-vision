#ifndef FILECONSTANTS_H
#define FILECONSTANTS_H
#include <string>

class FileConstants
{
public:
  static constexpr const char* fieldLimits = "Config/fieldLimits.json";;
  static constexpr const char* secondaryColor = "Config/SecondaryColor.json";
  static constexpr const char* videoPath = "Config/Video.json";
  static constexpr const char* segmentationConfig = "Config/Segmentation/Default.json";
};

#endif // FILECONSTANTS_H

/**\mainpage Logging classes made by the RoboCIn for the project IEEE - VSS
 * @author Marvson Allan
 *
 * This class contains all the configuration of logging and debug.
 *
 */

#ifndef VSS_VISION_LOGGING_H
#define VSS_VISION_LOGGING_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/dist_sink.h>

#include <memory>
#include <ctime>
#include <cstring>
#include <QDir>
#include <QString>

namespace Logging {
#define SIZE_LOG 1024 * 1024
#define NFILES_LOG 20
  void init();
  const std::string currentDateTime();
  void createFolder(QString folderPath);
}; // namespace Logging

#endif // VSS_VISION_UTILS_H

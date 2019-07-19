#include "logging.h"

void Logging::init() {
  spdlog::set_async_mode(8192, spdlog::async_overflow_policy::block_retry, nullptr, std::chrono::seconds(2));
  std::string nameGeneral, nameOthers, nameVision, nameStrategy;
  nameGeneral = "../src/Log/general/executions/execution " + currentDateTime() + ".log";
  nameOthers = "../src/Log/others/executions/execution " + currentDateTime() + ".log";
  nameVision = "../src/Log/vision/executions/execution " + currentDateTime() + ".log";
  nameStrategy = "../src/Log/strategy/executions/execution " + currentDateTime() + ".log";

  createFolder("../src/Log/general/executions/");
  createFolder("../src/Log/others/executions/");
  createFolder("../src/Log/vision/executions/");
  createFolder("../src/Log/strategy/executions/");

  createFolder("../src/Log/general/rotative/");
  createFolder("../src/Log/others/rotative/");
  createFolder("../src/Log/vision/rotative/");
  createFolder("../src/Log/strategy/rotative/");

  auto distGeneral = std::make_shared<spdlog::sinks::dist_sink_mt>();
  auto distVision = std::make_shared<spdlog::sinks::dist_sink_mt>();
  auto distStrategy = std::make_shared<spdlog::sinks::dist_sink_mt>();
  auto distOthers = std::make_shared<spdlog::sinks::dist_sink_mt>();

  auto rGeneral = std::make_shared<spdlog::sinks::rotating_file_sink_mt> ("../src/Log/general/rotative/rotative", SIZE_LOG, NFILES_LOG);
  auto rOthers = std::make_shared<spdlog::sinks::rotating_file_sink_mt> ("../src/Log/others/rotative/rotative", SIZE_LOG, NFILES_LOG);
  auto rVision = std::make_shared<spdlog::sinks::rotating_file_sink_mt> ("../src/Log/vision/rotative/rotative", SIZE_LOG, NFILES_LOG);
  auto rStrategy = std::make_shared<spdlog::sinks::rotating_file_sink_mt> ("../src/Log/strategy/rotative/rotative", SIZE_LOG, NFILES_LOG);

  auto fGeneral = std::make_shared<spdlog::sinks::simple_file_sink_mt>(nameGeneral);
  auto fOthers = std::make_shared<spdlog::sinks::simple_file_sink_mt>(nameOthers);
  auto fVision = std::make_shared<spdlog::sinks::simple_file_sink_mt>(nameVision);
  auto fStrategy = std::make_shared<spdlog::sinks::simple_file_sink_mt>(nameStrategy);

  auto fTemporaryLog = std::make_shared<spdlog::sinks::simple_file_sink_mt>("../src/Log/tempLog.log", true);
  auto stdout_sink = spdlog::sinks::stdout_sink_mt::instance();
  auto color_sink = std::make_shared<spdlog::sinks::ansicolor_sink>(stdout_sink);
  color_sink->set_level(spdlog::level::info);

  distGeneral->add_sink(color_sink);
  distGeneral->add_sink(rGeneral);
  distGeneral->add_sink(fGeneral);
  distGeneral->add_sink(fTemporaryLog);

  distVision->add_sink(color_sink);
	distVision->add_sink(rVision);
  distVision->add_sink(rGeneral);
	distVision->add_sink(fVision);
  distVision->add_sink(fGeneral);
  distVision->add_sink(fTemporaryLog);

  distOthers->add_sink(color_sink);
	distOthers->add_sink(rOthers);
  distOthers->add_sink(rGeneral);
	distOthers->add_sink(fOthers);
  distOthers->add_sink(fGeneral);
  distOthers->add_sink(fTemporaryLog);

  distStrategy->add_sink(color_sink);
	distStrategy->add_sink(rStrategy);
  distStrategy->add_sink(rGeneral);
	distStrategy->add_sink(fStrategy);
  distStrategy->add_sink(fGeneral);
  distStrategy->add_sink(fTemporaryLog);

	auto general = std::make_shared<spdlog::logger>("General", distGeneral);
	auto vision = std::make_shared<spdlog::logger>("Vision", distVision);
	auto strategy = std::make_shared<spdlog::logger>("Strategy", distStrategy);
	auto others = std::make_shared<spdlog::logger>("Others", distOthers);

  spdlog::register_logger(general);
  spdlog::register_logger(vision);
  spdlog::register_logger(strategy);
  spdlog::register_logger(others);
}


void Logging::createFolder(QString folderPath)
{
  QDir dir(folderPath);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
}

const std::string Logging::currentDateTime() {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}

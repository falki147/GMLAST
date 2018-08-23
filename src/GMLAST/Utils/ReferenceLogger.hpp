#pragma once

#include <GMLAST/Utils/ILogger.hpp>

namespace GMLAST {

struct ReferenceLogger : ILogger {
  ReferenceLogger(ILogger& logger) : logger{logger} {}

  virtual void log(Level level, std::string msg, Location begin,
                   Location end) override {
    logger.log(level, std::move(msg), begin, end);
  }

  ILogger& logger;
};

}  // namespace GMLAST

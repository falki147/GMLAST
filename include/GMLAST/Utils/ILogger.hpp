#pragma once

#include <GMLAST/Utils/Location.hpp>
#include <string>

namespace GMLAST {

struct ILogger {
  enum class Level { Warning, Error };

  virtual ~ILogger() = default;
  virtual void log(Level level, std::string msg, Location begin,
                   Location end) = 0;
};

}  // namespace GMLAST

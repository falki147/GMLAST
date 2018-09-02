/**
 * \file ILogger.hpp
 */

#pragma once

#include <GMLAST/Utils/Location.hpp>
#include <string>

namespace GMLAST {

/**
 * \brief Logger interface for handling warnings and errors
 *
 * This allows the user to handle these messages instead of stopping parsing or
 * lexing and throwing an exception.
 */
struct ILogger {
  /**
   * \brief Importance of the message
   */
  enum class Level {
    Warning,  ///< Message can be ignored, but should be acknowledged
    Error     ///< Message is critical
  };

  /**
   * \brief Virtual default destructor to make interface deletable
   */
  virtual ~ILogger() = default;

  /**
   * \brief Abstract log function which needs to be implemented by the user. It
   * may throw depending on the implementation.
   *
   * \param level Severity of the message
   * \param msg Message to be forwarded to the logging function
   * \param begin %Location of the first character where the error occurd
   * \param end %Location after the last character where the error occurd
   */
  virtual void log(Level level, std::string msg, Location begin,
                   Location end) = 0;
};

}  // namespace GMLAST

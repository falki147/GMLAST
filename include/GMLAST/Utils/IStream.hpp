/**
 * \file IStream.hpp
 */

#pragma once

namespace GMLAST {

/**
 * \brief Stream interface for implementing different inputs
 */
struct IStream {
  /**
   * \brief Virtual default destructor to make interface deletable
   */
  virtual ~IStream() = default;

  /**
   * \brief Get a byte from the stream
   *
   * \return The byte or EOF
   */
  virtual int get() = 0;
};

}  // namespace GMLAST

#pragma once

#include <GMLAST/Utils/Location.hpp>
#include <stdexcept>

namespace GMLAST {

class ParserException : public std::runtime_error {
 public:
  ParserException(const char* msg) : std::runtime_error(msg) {}
  ParserException(const std::string& msg) : std::runtime_error(msg) {}

  ParserException(const char* msg, Location first, Location last)
      : std::runtime_error(msg), m_first{first}, m_last{last} {}

  ParserException(const std::string& msg, Location first, Location last)
      : std::runtime_error(msg), m_first{first}, m_last{last} {}

  const Location& first() const noexcept { return m_first; }

  const Location& last() const noexcept { return m_last; }

  bool hasPosition() const noexcept { return m_first && m_last; }

 private:
  Location m_first, m_last;
};

}  // namespace GMLAST

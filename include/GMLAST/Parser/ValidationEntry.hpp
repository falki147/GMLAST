#pragma once

#include <GMLAST/Utils/Location.hpp>
#include <string>

namespace GMLAST {

class ValidationEntry {
 public:
  enum class Type { Error, Warning };

  ValidationEntry(Type type, std::string message, Location first, Location last)
      : m_type{type}, m_message{message}, m_first{first}, m_last{last} {}

  Type type() const noexcept { return m_type; }

  const std::string& message() const noexcept { return m_message; }

  const Location& first() const noexcept { return m_first; }

  const Location& last() const noexcept { return m_last; }

 private:
  Type m_type;
  std::string m_message;
  Location m_first, m_last;
};

}  // namespace GMLAST

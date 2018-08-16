#pragma once

#include <GMLAST/Lexer/NullBuffer.hpp>
#include <ostream>

namespace GMLAST {

class NullStream : public std::ostream {
 public:
  NullStream() : std::ostream(&m_nullBuffer) {}

 private:
  NullBuffer m_nullBuffer;
};

}  // namespace GMLAST

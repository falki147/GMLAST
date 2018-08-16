#pragma once

#include <GMLAST/Lexer/Token.hpp>

namespace GMLAST {

struct ILexer {
  virtual ~ILexer() = default;
  virtual Token lex() = 0;
};

}  // namespace GMLAST

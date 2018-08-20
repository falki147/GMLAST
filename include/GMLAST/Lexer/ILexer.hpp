#pragma once

#include <GMLAST/Lexer/Token.hpp>

namespace GMLAST {

struct ILogger;

struct ILexer {
  virtual ~ILexer() = default;
  virtual Token lex() = 0;
  virtual ILogger& logger() = 0;
};

}  // namespace GMLAST

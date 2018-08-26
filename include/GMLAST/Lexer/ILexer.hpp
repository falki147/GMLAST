#pragma once

#include <GMLAST/Lexer/Token.hpp>
#include <memory>

namespace GMLAST {

struct ILogger;

struct ILexer {
  virtual ~ILexer() = default;
  virtual Token lex() = 0;
  virtual std::shared_ptr<ILogger> logger() = 0;
};

}  // namespace GMLAST

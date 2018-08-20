#pragma once

#include <GMLAST/Lexer/ILexer.hpp>
#include <random>

namespace ParserTest {

class RandomLexer : public GMLAST::ILexer {
 public:
  RandomLexer(std::size_t numTokens, unsigned int seed = 0);

  virtual GMLAST::Token lex() override;
  virtual GMLAST::ILogger& logger() override;

 private:
  std::size_t m_numTokensLeft;
  std::default_random_engine m_rand;
};

}  // namespace ParserTest

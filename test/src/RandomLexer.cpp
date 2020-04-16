#include <RandomLexer.hpp>
#include <stdexcept>

namespace ParserTest {

RandomLexer::RandomLexer(std::size_t numTokens, unsigned int seed)
    : m_numTokensLeft{numTokens}, m_rand{seed} {}

GMLAST::Token RandomLexer::lex() {
  if (m_numTokensLeft == 0) return {};

  --m_numTokensLeft;

  const auto type = static_cast<GMLAST::Token::Type>(m_rand() % 71 + 1);

  switch (type) {
    case GMLAST::Token::Type::ConstString:
    case GMLAST::Token::Type::Identifier:
      return {type, {}, {}, std::string{}};
    case GMLAST::Token::Type::ConstInt:
      return {type, {}, {}, int{}};
    case GMLAST::Token::Type::ConstDouble:
      return {type, {}, {}, double{}};
    default:
      return {type, {}, {}};
  }
}

std::shared_ptr<GMLAST::ILogger> RandomLexer::logger() {
  throw std::runtime_error("no logger assigned");
}

}  // namespace ParserTest

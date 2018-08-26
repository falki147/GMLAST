#include <ParserTest/RandomLexer.hpp>
#include <array>

namespace ParserTest {

static const std::array<GMLAST::Token::Type, 71> TokenTypes{
    {GMLAST::Token::Type::ArrayClose,
     GMLAST::Token::Type::ArrayOpen,
     GMLAST::Token::Type::ArrayOpenGrid,
     GMLAST::Token::Type::ArrayOpenList,
     GMLAST::Token::Type::ArrayOpenMap,
     GMLAST::Token::Type::ArrayOpenRef,
     GMLAST::Token::Type::Assign,
     GMLAST::Token::Type::AssignAdd,
     GMLAST::Token::Type::AssignBitAnd,
     GMLAST::Token::Type::AssignBitOr,
     GMLAST::Token::Type::AssignBitXor,
     GMLAST::Token::Type::AssignDiv,
     GMLAST::Token::Type::AssignMod,
     GMLAST::Token::Type::AssignMul,
     GMLAST::Token::Type::AssignSub,
     GMLAST::Token::Type::BitwiseAnd,
     GMLAST::Token::Type::BitwiseLeft,
     GMLAST::Token::Type::BitwiseNot,
     GMLAST::Token::Type::BitwiseOr,
     GMLAST::Token::Type::BitwiseRight,
     GMLAST::Token::Type::BitwiseXor,
     GMLAST::Token::Type::BraceClose,
     GMLAST::Token::Type::BraceOpen,
     GMLAST::Token::Type::Break,
     GMLAST::Token::Type::Case,
     GMLAST::Token::Type::CmpEqual,
     GMLAST::Token::Type::CmpGreater,
     GMLAST::Token::Type::CmpGreaterEqual,
     GMLAST::Token::Type::CmpNotEqual,
     GMLAST::Token::Type::CmpLess,
     GMLAST::Token::Type::CmpLessEqual,
     GMLAST::Token::Type::Colon,
     GMLAST::Token::Type::Comma,
     GMLAST::Token::Type::ConstDouble,
     GMLAST::Token::Type::ConstInt,
     GMLAST::Token::Type::ConstString,
     GMLAST::Token::Type::Continue,
     GMLAST::Token::Type::Decrement,
     GMLAST::Token::Type::Default,
     GMLAST::Token::Type::Divide,
     GMLAST::Token::Type::Do,
     GMLAST::Token::Type::Dot,
     GMLAST::Token::Type::Else,
     GMLAST::Token::Type::Enum,
     GMLAST::Token::Type::Equal,
     GMLAST::Token::Type::Exit,
     GMLAST::Token::Type::For,
     GMLAST::Token::Type::Globalvar,
     GMLAST::Token::Type::Identifier,
     GMLAST::Token::Type::If,
     GMLAST::Token::Type::Increment,
     GMLAST::Token::Type::IntDivide,
     GMLAST::Token::Type::LogicalAnd,
     GMLAST::Token::Type::LogicalNot,
     GMLAST::Token::Type::LogicalOr,
     GMLAST::Token::Type::LogicalXor,
     GMLAST::Token::Type::Minus,
     GMLAST::Token::Type::Modulo,
     GMLAST::Token::Type::Multiply,
     GMLAST::Token::Type::ParenClose,
     GMLAST::Token::Type::ParenOpen,
     GMLAST::Token::Type::Plus,
     GMLAST::Token::Type::Repeat,
     GMLAST::Token::Type::Return,
     GMLAST::Token::Type::Semicolon,
     GMLAST::Token::Type::Switch,
     GMLAST::Token::Type::Then,
     GMLAST::Token::Type::Until,
     GMLAST::Token::Type::Var,
     GMLAST::Token::Type::While,
     GMLAST::Token::Type::With}};

RandomLexer::RandomLexer(std::size_t numTokens, unsigned int seed)
    : m_numTokensLeft{numTokens}, m_rand{seed} {}

GMLAST::Token RandomLexer::lex() {
  if (m_numTokensLeft == 0) return {};

  --m_numTokensLeft;

  const auto type = TokenTypes[m_rand() % TokenTypes.size()];

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

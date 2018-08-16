#include <GMLAST/Lexer/Token.hpp>

namespace GMLAST {

std::string ToString(Token::Type type) noexcept {
  switch (type) {
    case Token::Type::ArrayClose:
      return "array close";
    case Token::Type::ArrayOpen:
      return "array open";
    case Token::Type::ArrayOpenGrid:
      return "array open (grid)";
    case Token::Type::ArrayOpenList:
      return "array open (list)";
    case Token::Type::ArrayOpenMap:
      return "array open (map)";
    case Token::Type::ArrayOpenRef:
      return "array open (reference)";
    case Token::Type::Assign:
      return "assign";
    case Token::Type::AssignAdd:
      return "add assign";
    case Token::Type::AssignBitAnd:
      return "bitwise and assign";
    case Token::Type::AssignBitOr:
      return "bitwise or assign";
    case Token::Type::AssignBitXor:
      return "bitwise xor assign";
    case Token::Type::AssignDiv:
      return "divide assign";
    case Token::Type::AssignMod:
      return "modulo assign";
    case Token::Type::AssignMul:
      return "multiply assign";
    case Token::Type::AssignSub:
      return "subtract assign";
    case Token::Type::BitwiseAnd:
      return "bitwise and";
    case Token::Type::BitwiseLeft:
      return "bitwise left";
    case Token::Type::BitwiseNot:
      return "bitwise not";
    case Token::Type::BitwiseOr:
      return "bitwise or";
    case Token::Type::BitwiseRight:
      return "bitwise right";
    case Token::Type::BitwiseXor:
      return "bitwise xor";
    case Token::Type::BraceClose:
      return "right curly bracket";
    case Token::Type::BraceOpen:
      return "left curly bracket";
    case Token::Type::Break:
      return "break";
    case Token::Type::Case:
      return "case";
    case Token::Type::CmpEqual:
      return "compare equal";
    case Token::Type::CmpGreater:
      return "compare greater";
    case Token::Type::CmpGreaterEqual:
      return "compare greater or equal";
    case Token::Type::CmpNotEqual:
      return "compare not equal";
    case Token::Type::CmpLess:
      return "compare less";
    case Token::Type::CmpLessEqual:
      return "compare less or equal";
    case Token::Type::Colon:
      return "colon";
    case Token::Type::Comma:
      return "comma";
    case Token::Type::ConstDouble:
      return "constant double";
    case Token::Type::ConstInt:
      return "constant integer";
    case Token::Type::ConstString:
      return "const string";
    case Token::Type::Continue:
      return "continue";
    case Token::Type::Decrement:
      return "decrement";
    case Token::Type::Default:
      return "default";
    case Token::Type::Divide:
      return "divide";
    case Token::Type::Do:
      return "do";
    case Token::Type::Dot:
      return "dot";
    case Token::Type::Else:
      return "eles";
    case Token::Type::Enum:
      return "enum";
    case Token::Type::Equal:
      return "equal sign";
    case Token::Type::Exit:
      return "exit";
    case Token::Type::For:
      return "for";
    case Token::Type::Globalvar:
      return "globalvar";
    case Token::Type::Identifier:
      return "identifier";
    case Token::Type::If:
      return "if";
    case Token::Type::Increment:
      return "increment";
    case Token::Type::IntDivide:
      return "integer divide";
    case Token::Type::LogicalAnd:
      return "logical and";
    case Token::Type::LogicalNot:
      return "logical not";
    case Token::Type::LogicalOr:
      return "logical or";
    case Token::Type::LogicalXor:
      return "logical xor";
    case Token::Type::Minus:
      return "minus sign";
    case Token::Type::Modulo:
      return "modulo";
    case Token::Type::Multiply:
      return "multiply";
    case Token::Type::ParenClose:
      return "close parenthesis";
    case Token::Type::ParenOpen:
      return "open parenthesis";
    case Token::Type::Plus:
      return "plus sign";
    case Token::Type::Repeat:
      return "repeat";
    case Token::Type::Return:
      return "return";
    case Token::Type::Semicolon:
      return "semicolon";
    case Token::Type::Switch:
      return "switch";
    case Token::Type::Then:
      return "then";
    case Token::Type::Until:
      return "until";
    case Token::Type::Var:
      return "var";
    case Token::Type::While:
      return "while";
    case Token::Type::With:
      return "with";
    default:
      return {};
  }
}

}  // namespace GMLAST

#pragma once

#include <GMLAST/Utils/Location.hpp>
#include <cassert>
#include <string>

namespace GMLAST {

class Token {
 public:
  enum class Type {
    Invalid,
    ArrayClose,
    ArrayOpen,
    ArrayOpenGrid,
    ArrayOpenList,
    ArrayOpenMap,
    ArrayOpenRef,
    Assign,
    AssignAdd,
    AssignBitAnd,
    AssignBitOr,
    AssignBitXor,
    AssignDiv,
    AssignMod,
    AssignMul,
    AssignSub,
    BitwiseAnd,
    BitwiseLeft,
    BitwiseNot,
    BitwiseOr,
    BitwiseRight,
    BitwiseXor,
    BraceClose,
    BraceOpen,
    Break,
    Case,
    CmpEqual,
    CmpGreater,
    CmpGreaterEqual,
    CmpNotEqual,
    CmpLess,
    CmpLessEqual,
    Colon,
    Comma,
    ConstDouble,
    ConstInt,
    ConstString,
    Continue,
    Decrement,
    Default,
    Divide,
    Do,
    Dot,
    Else,
    Enum,
    Equal,
    Exit,
    For,
    Globalvar,
    Identifier,
    If,
    Increment,
    IntDivide,
    LogicalAnd,
    LogicalNot,
    LogicalOr,
    LogicalXor,
    Minus,
    Modulo,
    Multiply,
    ParenClose,
    ParenOpen,
    Plus,
    Repeat,
    Return,
    Semicolon,
    Switch,
    Then,
    Until,
    Var,
    While,
    With
  };

  Token() = default;

  Token(Type type, Location first, Location last)
      : m_type{type}, m_first{first}, m_last{last} {
    assert(type != Type::ConstDouble && type != Type::ConstInt &&
           type != Type::ConstString && type != Type::Identifier);
  }

  Token(Type type, Location first, Location last, const std::string& value)
      : m_type{type}, m_first{first}, m_last{last}, m_string{value} {
    assert(type == Type::ConstString || type == Type::Identifier);
  }

  Token(Type type, Location first, Location last, std::string&& value)
      : m_type{type}, m_first{first}, m_last{last}, m_string{std::move(value)} {
    assert(type == Type::ConstString || type == Type::Identifier);
  }

  Token(Type type, Location first, Location last, int value)
      : m_type{type}, m_first{first}, m_last{last}, m_integer{value} {
    assert(type == Type::ConstInt);
  }

  Token(Type type, Location first, Location last, double value)
      : m_type{type}, m_first{first}, m_last{last}, m_double{value} {
    assert(type == Type::ConstDouble);
  }

  operator bool() const noexcept { return m_type != Type::Invalid; }

  Type type() const noexcept { return m_type; }

  bool is(Type type) const noexcept { return m_type == type; }

  const Location& first() const noexcept { return m_first; }

  const Location& last() const noexcept { return m_last; }

  bool hasPosition() const noexcept { return m_first && m_last; }

  const std::string& getString() const noexcept {
    assert(m_type == Type::ConstString || m_type == Type::Identifier);
    return m_string;
  }

  int getInteger() const noexcept {
    assert(m_type == Type::ConstInt);
    return m_integer;
  }

  double getDouble() const noexcept {
    assert(m_type == Type::ConstDouble);
    return m_double;
  }

 private:
  Type m_type{Type::Invalid};
  Location m_first, m_last;
  std::string m_string;

  union {
    int m_integer;
    double m_double;
  };
};

std::string ToString(Token::Type type) noexcept;

}  // namespace GMLAST

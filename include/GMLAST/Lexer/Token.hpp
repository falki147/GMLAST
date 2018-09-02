/**
 * \file Token.hpp
 */

#pragma once

#include <GMLAST/Utils/Location.hpp>
#include <cassert>
#include <string>

namespace GMLAST {

/**
 * \brief Contains information about the position in the input, the type of the
 * token and optional data created by the lexer.
 */
class Token {
 public:
  /**
   * \brief Type of the Token
   *
   * To convert the values to a string use \link ToString() ToString\endlink.
   */
  enum class Type {
    Invalid,  ///< Indicates that the token is invalid. This can happen if the
              /// lexer has no more input. This is the default value.

    ArrayClose,       ///< `]`
    ArrayOpen,        ///< `[`
    ArrayOpenGrid,    ///< `[#`
    ArrayOpenList,    ///< `[|`
    ArrayOpenMap,     ///< `[?`
    ArrayOpenRef,     ///< `[@`
    Assign,           ///< `:=`
    AssignAdd,        ///< `+=`
    AssignBitAnd,     ///< `&=`
    AssignBitOr,      ///< `|=`
    AssignBitXor,     ///< `^=`
    AssignDiv,        ///< `/=`
    AssignMod,        ///< `%=`
    AssignMul,        ///< `*=`
    AssignSub,        ///< `-=`
    BitwiseAnd,       ///< `&`
    BitwiseLeft,      ///< `<<`
    BitwiseNot,       ///< `~`
    BitwiseOr,        ///< `|`
    BitwiseRight,     ///< `>>`
    BitwiseXor,       ///< `^`
    BraceClose,       ///< `}` or `end`
    BraceOpen,        ///< `{` or `begin`
    Break,            ///< `break`
    Case,             ///< `case`
    CmpEqual,         ///< `==`
    CmpGreater,       ///< `>`
    CmpGreaterEqual,  ///< `>=`
    CmpNotEqual,      ///< `!=`
    CmpLess,          ///< `<`
    CmpLessEqual,     ///< `<=`
    Colon,            ///< `:`
    Comma,            ///< `,`

    ConstDouble,  ///< Flotaing point (double) constant e.g. `1.0`, `12.34`; The
                  /// value can be retrieved using #getDouble.

    ConstInt,  ///< Integer constant e.g. `10`, `1234`; The value can be
               /// retrieved using #getInteger.

    ConstString,  ///< String constant e.g. `"test"`, `'hello world'`;  The
                  /// value can be retrieved using #getString.

    Continue,   ///< `continue`
    Decrement,  ///< `--`
    Default,    ///< `default`
    Divide,     ///< `/`
    Do,         ///< `do`
    Dot,        ///< `.`
    Else,       ///< `else`
    Enum,       ///< `enum`
    Equal,      ///< `=`
    Exit,       ///< `exit`
    For,        ///< `for`
    Globalvar,  ///< `globalvar`

    Identifier,  ///< Identifier e.g. `foo`, `_bar`, `foo2`; The value can be
                 /// retrieved using #getString.

    If,          ///< `if`
    Increment,   ///< `++`
    IntDivide,   ///< `div`
    LogicalAnd,  ///< `&&` or `and`
    LogicalNot,  ///< `!` or `not`
    LogicalOr,   ///< `||` or `or`
    LogicalXor,  ///< `^^` or `xor`
    Minus,       ///< `-`
    Modulo,      ///< `%` or `mod`
    Multiply,    ///< `*`
    ParenClose,  ///< `)`
    ParenOpen,   ///< `(`
    Plus,        ///< `+`
    Repeat,      ///< `repeat`
    Return,      ///< `return`
    Semicolon,   ///< `;`
    Switch,      ///< `switch`
    Then,        ///< `then`
    Until,       ///< `until`
    Var,         ///< `var`
    While,       ///< `while`
    With         ///< `with`
  };

  /**
   * \brief Default constructor.
   *
   * Initalizes the type with Type::Invalid and sets the locations to their
   * default value
   */
  Token() = default;

  /**
   * \brief Constructor which sets the type and locations. This constructor
   * should not be used with the Type::ConstDouble, Type::ConstInt,
   * Type::ConstString and Type::Identifier types
   *
   * \param type Type of the token
   * \param first %Location of the first character of the token in the input
   * \param last %Location after the last character of the token in the input
   */
  Token(Type type, Location first, Location last)
      : m_type{type}, m_first{first}, m_last{last} {
    assert(type != Type::ConstDouble && type != Type::ConstInt &&
           type != Type::ConstString && type != Type::Identifier);
  }

  /**
   * \brief Constructor which sets the type, locations and the string value
   * This constructor should only be used with the Type::ConstString and
   * Type::Identifier types
   *
   * \param type Type of the token
   * \param first %Location of the first character of the token in the input
   * \param last %Location after the last character of the token in the input
   * \param value String value to set to
   */
  Token(Type type, Location first, Location last, const std::string& value)
      : m_type{type}, m_first{first}, m_last{last}, m_string{value} {
    assert(type == Type::ConstString || type == Type::Identifier);
  }

  /**
   * \brief Constructor which sets the type, locations and the string value
   * This constructor should only be used with the Type::ConstString and
   * Type::Identifier types
   *
   * \param type Type of the token
   * \param first %Location of the first character of the token in the input
   * \param last %Location after the last character of the token in the input
   * \param value String value to set to
   */
  Token(Type type, Location first, Location last, std::string&& value)
      : m_type{type}, m_first{first}, m_last{last}, m_string{std::move(value)} {
    assert(type == Type::ConstString || type == Type::Identifier);
  }

  /**
   * \brief Constructor which sets the type, locations and the integer value.
   * This constructor should only be used with the Type::ConstInt type
   *
   * \param type Type of the token
   * \param first %Location of the first character of the token in the input
   * \param last %Location after the last character of the token in the input
   * \param value Integer value to set to
   */
  Token(Type type, Location first, Location last, int value)
      : m_type{type}, m_first{first}, m_last{last}, m_integer{value} {
    assert(type == Type::ConstInt);
  }

  /**
   * \brief Constructor which sets the type, locations and the double value
   * This constructor should only be used with the Type::ConstDouble type
   *
   * \param type Type of the token
   * \param first %Location of the first character of the token in the input
   * \param last %Location after the last character of the token in the input
   * \param value Double value to set to
   */
  Token(Type type, Location first, Location last, double value)
      : m_type{type}, m_first{first}, m_last{last}, m_double{value} {
    assert(type == Type::ConstDouble);
  }

  /**
   * \brief Utility function for checking if \ref type is Type::Invalid
   */
  operator bool() const noexcept { return m_type != Type::Invalid; }

  /**
   * \brief Returns the type
   */
  Type type() const noexcept { return m_type; }

  /**
   * \brief Utility function for checking if \ref type is \p type
   */
  bool is(Type type) const noexcept { return m_type == type; }

  /**
   * \brief Returns the first location (position at first character). It may be
   * invalid.
   */
  const Location& first() const noexcept { return m_first; }

  /**
   * \brief Returns the last location (position after last character). It may be
   * invalid.
   */
  const Location& last() const noexcept { return m_last; }

  /**
   * \brief Returns the string value
   *
   * This function should only be called if \ref type is Type::ConstString or
   * Type::Identifier
   */
  const std::string& getString() const noexcept {
    assert(m_type == Type::ConstString || m_type == Type::Identifier);
    return m_string;
  }

  /**
   * \brief Returns the integer value
   *
   * This function should only be called if \ref type is Type::ConstInt
   */
  int getInteger() const noexcept {
    assert(m_type == Type::ConstInt);
    return m_integer;
  }

  /**
   * \brief Returns the double value
   *
   * This function should only be called if \ref type is Type::ConstDouble
   */
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

/**
 * \brief Converts a Token::Type into its corresponding string
 *
 * The returned values may differ from the enum names. The intended use of the
 * function is to provide the user with more meaningful information about the
 * token in case of an error. If a type is not handled the function returns an
 * empty string (e.g. Token::Type::Invalid)
 *
 * \param type Type
 * \return A string representation of the value or an empty string
 */
std::string ToString(Token::Type type);

}  // namespace GMLAST

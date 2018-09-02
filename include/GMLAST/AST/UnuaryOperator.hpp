/**
 * \file UnuaryOperator.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

/**
 * \brief Node which represents a expression with one operand
 */
class UnuaryOperator : public Value {
 public:
  /**
   * \brief Type of the operator
   */
  enum class Type {
    BitwiseNot,        ///< Bitiwse NOT e.g. `~a`
    LogicalNot,        ///< Logical Not e.g. `!a` or `not a`
    PostfixDecrement,  ///< Postfix Decrement e.g. `a--`
    PostfixIncrement,  ///< Postfix Increment e.g. `a++`
    PrefixDecrement,   ///< Prefix Decrement e.g. `--a`
    PrefixIncrement,   ///< Prefix Increment e.g. `++a`
    Minus,             ///< Minus e.g. `-a`
    Plus               ///< Plus e.g. `+a`
  };

  /**
   * \brief It represents `+value` where `+` is different depending on the type.
   *
   * \param type Type of the operator
   * \param value Value which is used. It must not be null.
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  UnuaryOperator(Type type, std::unique_ptr<Value> value, Location first = {},
                 Location last = {});

  /**
   * \brief Function which calls IVisitor::onUnuaryOperator
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return type
   */
  Type type() const noexcept { return m_type; }

  /**
   * \brief Return reference to value expression
   */
  const Value& value() const noexcept { return *m_value.get(); }

 private:
  Type m_type;
  std::unique_ptr<Value> m_value;
};

}  // namespace GMLAST

/**
 * \file BinaryOperator.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

/**
 * \brief Node which represents a expression with two operands
 */
class BinaryOperator : public Value {
 public:
  /**
   * \brief Type of the operator
   */
  enum class Type {
    Add,             ///< Add left and right e.g. `a + b`
    BitwiseAnd,      ///< Bitwise AND of left and right e.g. `a & b`
    BitwiseLeft,     ///< Bitwise left shift of right by left  e.g. `a << b`
    BitwiseOr,       ///< Bitwise OR of left and right e.g. `a | b`
    BitwiseRight,    ///< Bitwise right shift of right by left  e.g. `a >> b`
    BitwiseXor,      ///< Bitwise XOR of left and right e.g. `a ^ b`
    CompareEqual,    ///< Check if left equals right e.g. `a == b`
    CompareGreater,  ///< Check if left is greater than right e.g. `a > b`

    CompareGreaterEqual,  ///< Check if left is greater than or equal right e.g.
                          /// `a > b`

    CompareLess,  ///< Check if left is less than right e.g. `a < b`

    CompareLessEqual,  ///< Check if left is less than or equal right e.g.
                       /// `a <= b`

    CompareNotEqual,  ///< Check if left doesn't equal right e.g. `a != b`
    Divide,           ///< Divide left and right e.g. `a / b`

    IntDivide,  ///< Integer divide (division with discarding decimal places) of
                /// left and right e.g. `a div b`

    LogicalAnd,  ///< Check if left and right are true e.g. `a && b`
    LogicalOr,   ///< Check if left or right or both are true e.g. `a || b`
    LogicalXor,  ///< Check if either left or right is true e.g. `a ^^ b`
    Modulo,      ///< Left modulo right e.g. `a % b` or `a mod b`
    Multiply,    ///< Multiply left and right e.g. `a * b`
    Subtract     ///< Subtract left and right e.g. `a - b`
  };

  /**
   * \brief It represents `left + right`, where `+` is different depending on
   * the type.
   *
   * \param type Type of the operator
   * \param left Left value of expression. It must not be null.
   * \param right Right value of expression. It must not be null.
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  BinaryOperator(Type type, std::unique_ptr<Value> left,
                 std::unique_ptr<Value> right, Location first = {},
                 Location last = {});

  /**
   * \brief Function which calls IVisitor::onBinaryOperator
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return type
   */
  Type type() const noexcept { return m_type; }

  /**
   * \brief Return reference to left expression
   */
  const Value& left() const noexcept { return *m_left.get(); }

  /**
   * \brief Return reference to right expression
   */
  const Value& right() const noexcept { return *m_right.get(); }

 private:
  Type m_type;
  std::unique_ptr<Value> m_left, m_right;
};

}  // namespace GMLAST

/**
 * \file AssignStatement.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

/**
 * \brief Node which represents a assignment expression
 */
class AssignStatement : public Value {
 public:
  /**
   * \brief Type of the operator
   */
  enum class Type {
    Assign,  ///< Normal assignment e.g. `a = b`
    Add,     ///< Assign addition of left and right e.g. `a += b`
    BitAnd,  ///< Assign bitwise AND of left and right e.g. `a &= b`
    BitOr,   ///< Assign bitwise OR of left and right e.g. `a |= b`
    BitXor,  ///< Assign bitwise XOR of left and right e.g. `a ^= b`
    Div,     ///< Assign division of left and right e.g. `a /= b`
    Mod,     ///< Assign modulo of left and right e.g. `a %= b`
    Mul,     ///< Assign multiplication of left and right e.g. `a *= b`
    Sub      ///< Assign subtraction of left and right e.g. `a -= b`
  };

  /**
   * \brief It represents `left = right`, where `=` is different depending on
   * the type.
   *
   * \param type Type of the operator
   * \param left %Value which gets overwritten. It must not be null.
   * \param right %Value to assign. It must not be null.
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  AssignStatement(Type type, std::unique_ptr<Value> left,
                  std::unique_ptr<Value> right, Location first = {},
                  Location last = {});

  /**
   * \brief Function which calls IVisitor::onAssignStatement
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

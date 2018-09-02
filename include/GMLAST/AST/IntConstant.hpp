/**
 * \file IntConstant.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>

namespace GMLAST {

/**
 * \brief Node which represents integers e.g. `10`
 */
class IntConstant : public Value {
 public:
  /**
   * \brief It represents integers e.g. `10`
   *
   * \param value Parsed value of the integer
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  IntConstant(int value, Location first = {}, Location last = {});

  /**
   * \brief Function which calls IVisitor::onIntConstant
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return value
   */
  int value() const noexcept { return m_value; }

 private:
  int m_value;
};

}  // namespace GMLAST

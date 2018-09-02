/**
 * \file DoubleConstant.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>

namespace GMLAST {

/**
 * \brief Node which represents floating point numbers e.g. `1.0`
 */
class DoubleConstant : public Value {
 public:
  /**
   * \brief It represents floating point numbers e.g. `1.0`
   *
   * \param value Parsed value of the floating point number
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  DoubleConstant(double value, Location first = {}, Location last = {})
      : Value{first, last}, m_value{value} {}

  /**
   * \brief Function which calls IVisitor::onDoubleConstant
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return value
   */
  double value() const noexcept { return m_value; }

 private:
  double m_value;
};

}  // namespace GMLAST

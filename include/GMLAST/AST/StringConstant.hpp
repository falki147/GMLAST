/**
 * \file StringConstant.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

/**
 * \brief Node which represents strings e.g. `'hello'` or `"world"`
 */
class StringConstant : public Value {
 public:
  /**
   * \brief It represents strings e.g. `'hello'` or `"world"`
   *
   * \param value String value
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  StringConstant(const std::string& value, Location first = {},
                 Location last = {})
      : Value{first, last, NodeType::StringConstant}, m_value{value} {}

  /**
   * \brief Function which calls IVisitor::onStringConstant
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return value
   */
  const std::string& value() const noexcept { return m_value; }

 private:
  std::string m_value;
};

}  // namespace GMLAST

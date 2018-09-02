/**
 * \file Variable.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

/**
 * \brief Node which represents a variable expression
 */
class Variable : public Value {
 public:
  /**
   * \brief It represents `name`.
   *
   * \param name Name of the variable
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  Variable(const std::string& name, Location first = {}, Location last = {})
      : Value{first, last}, m_name{name} {}

  /**
   * \brief Function which calls IVisitor::onVariable
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return name
   */
  const std::string& name() const noexcept { return m_name; }

 private:
  std::string m_name;
};

}  // namespace GMLAST

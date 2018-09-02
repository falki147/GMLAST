/**
 * \file DotOperator.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

/**
 * \brief Node which represents a dot expression
 */
class DotOperator : public Value {
 public:
  /**
   * \brief It represents `expression.name`.
   *
   * \param name Name of the referenced variable
   * \param expression Expression which results into an object
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  DotOperator(const std::string& name, std::unique_ptr<Value> expression,
              Location first = {}, Location last = {});

  /**
   * \brief Function which calls IVisitor::onDotOperator
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return name
   */
  const std::string& name() const noexcept { return m_name; }

  /**
   * \brief Return reference to expression
   */
  const Value& expression() const noexcept { return *m_expression.get(); }

 private:
  std::string m_name;
  std::unique_ptr<Value> m_expression;
};

}  // namespace GMLAST

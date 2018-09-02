/**
 * \file ReturnStatement.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

/**
 * \brief Node which represents a return statement
 */
class ReturnStatement : public Statement {
 public:
  /**
   * \brief It represents `return expression`.
   *
   * \param expression Expression which value is returned. It must not be null.
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  ReturnStatement(std::unique_ptr<Value> expression, Location first = {},
                  Location last = {});

  /**
   * \brief Function which calls IVisitor::onReturnStatement
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return reference to expression
   */
  const Value& expression() const noexcept { return *m_expression.get(); }

 private:
  std::unique_ptr<Value> m_expression;
};

}  // namespace GMLAST

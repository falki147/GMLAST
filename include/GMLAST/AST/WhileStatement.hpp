/**
 * \file WhileStatement.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

/**
 * \brief Node which represents a while statement
 *
 * \dotfile WhileStatement.dot Flowchart
 */
class WhileStatement : public Statement {
 public:
  /**
   * \brief It represents `while expression statement`.
   *
   * \param expression Expression which determines when the loop is exited. It
   * must not be null.
   * \param statement Statement which is executed inside the loop. It must not
   * be null.
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  WhileStatement(std::unique_ptr<Value> expression,
                 std::unique_ptr<Statement> statement, Location first = {},
                 Location last = {});

  /**
   * \brief Function which calls IVisitor::onWhileStatement
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return reference to expression
   */
  const Value& expression() const noexcept { return *m_expression.get(); }

  /**
   * \brief Return reference to statement
   */
  const Statement& statement() const noexcept { return *m_statement.get(); }

 private:
  std::unique_ptr<Value> m_expression;
  std::unique_ptr<Statement> m_statement;
};

}  // namespace GMLAST

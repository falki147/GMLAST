/**
 * \file RepeatStatement.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

/**
 * \brief Node which represents a repeat statement
 *
 * Execute statement the number times what the expression evaluates to. It can
 * be also written as a \link ForStatement for loop\endlink. i.e.
 * \code
 * for (var n = expression; n > 0; n -= 1)
 *   statement
 * \endcode
 */
class RepeatStatement : public Statement {
 public:
  /**
   * \brief It represents `repeat expression statement`.
   *
   * \param expression Expression which determines how often the statement is
   * executed. It must not be null.
   * \param statement Statement which is executed inside the loop. It must not
   * be null.
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  RepeatStatement(std::unique_ptr<Value> expression,
                  std::unique_ptr<Statement> statement, Location first = {},
                  Location last = {});

  /**
   * \brief Function which calls IVisitor::onRepeatStatement
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

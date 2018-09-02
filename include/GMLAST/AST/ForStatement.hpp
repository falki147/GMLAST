/**
 * \file ForStatement.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

/**
 * \brief Node which represents a for statement
 *
 * \dotfile ForStatement.dot Flowchart
 */
class ForStatement : public Statement {
 public:
  /**
   * \brief It represents `for (initStatement; expression; iterationStatement)
   * statement`.
   *
   * \param initStatement %Statement, which is called at the beginning
   * \param expression Expression, which determines if the loop should break
   * \param iterationStatement %Statement, which is executed every time after
   * the first iteration
   * \param statement %Statement, which is executed every time
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  ForStatement(std::unique_ptr<Statement> initStatement,
               std::unique_ptr<Value> expression,
               std::unique_ptr<Statement> iterationStatement,
               std::unique_ptr<Statement> statement, Location first = {},
               Location last = {});

  /**
   * \brief Function which calls IVisitor::onForStatement
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return reference to init statement
   */
  const Statement& initStatement() const noexcept {
    return *m_initStatement.get();
  }

  /**
   * \brief Return reference to expression
   */
  const Value& expression() const noexcept { return *m_expression.get(); }

  /**
   * \brief Return reference to iteration statement
   */
  const Statement& iterationStatement() const noexcept {
    return *m_iterationStatement.get();
  }

  /**
   * \brief Return reference to statement
   */
  const Statement& statement() const noexcept { return *m_statement.get(); }

 private:
  std::unique_ptr<Value> m_expression;
  std::unique_ptr<Statement> m_initStatement, m_iterationStatement, m_statement;
};

}  // namespace GMLAST

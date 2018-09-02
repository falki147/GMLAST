/**
 * \file IfStatement.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

/**
 * \brief Node which represents a if statement
 *
 * \dotfile IfStatement.dot Flowchart without else
 * \dotfile IfStatementWithElse.dot Flowchart with else
 */
class IfStatement : public Statement {
 public:
  /**
   * \brief It represents `if expression statement`.
   *
   * \param expression Expression which determines if the statement is executed.
   * It must not be null.
   * \param statement %Statement which is executed if expression is true. It
   * must not be null.
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  IfStatement(std::unique_ptr<Value> expression,
              std::unique_ptr<Statement> statement, Location first = {},
              Location last = {});

  /**
   * \brief It represents `if expression statement else statement`.
   *
   * \param expression Expression which determines which statement is executed.
   * It must not be null.
   * \param statement %Statement which is executed if expression is true. It
   * must not be null.
   * \param elseStatement %Statement which is executed if expression is false.
   * It must not be null.
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  IfStatement(std::unique_ptr<Value> expression,
              std::unique_ptr<Statement> statement,
              std::unique_ptr<Statement> elseStatement, Location first = {},
              Location last = {});

  /**
   * \brief Function which calls IVisitor::onIfStatement
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

  /**
   * \brief Return reference to else statement
   */
  const Statement& elseStatement() const noexcept {
    return *m_elseStatement.get();
  }

  /**
   * \brief Check if else statement is valid/set
   */
  bool hasElseStatement() const noexcept {
    return static_cast<bool>(m_elseStatement);
  }

 private:
  std::unique_ptr<Value> m_expression;
  std::unique_ptr<Statement> m_statement, m_elseStatement;
};

}  // namespace GMLAST

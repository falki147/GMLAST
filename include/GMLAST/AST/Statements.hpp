/**
 * \file Statements.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

/**
 * \brief Node which groups several statements into one
 */
class Statements : public Statement {
 private:
  using StatementVector = std::vector<std::unique_ptr<Statement>>;

 public:
  /**
   * \brief It represents `{ statements }` where `statements` are zero or more
   * statements.
   *
   * \param statements Array of statements. Every pointer must be not null.
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  Statements(StatementVector statements, Location first = {},
             Location last = {});

  /**
   * \brief Function which calls IVisitor::onStatements
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return reference to statements array
   */
  const StatementVector& statements() const noexcept { return m_statements; }

 private:
  StatementVector m_statements;
};

}  // namespace GMLAST

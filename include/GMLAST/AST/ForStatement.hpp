#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

class ForStatement : public Statement {
 public:
  ForStatement(std::unique_ptr<Statement> initStatement,
               std::unique_ptr<Value> expression,
               std::unique_ptr<Statement> iterationStatement,
               std::unique_ptr<Statement> statement, Location first = {},
               Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  const Statement& initStatement() const noexcept {
    return *m_initStatement.get();
  }

  const Value& expression() const noexcept { return *m_expression.get(); }

  const Statement& iterationStatement() const noexcept {
    return *m_iterationStatement.get();
  }

  const Statement& statement() const noexcept { return *m_statement.get(); }

 private:
  std::unique_ptr<Value> m_expression;
  std::unique_ptr<Statement> m_initStatement, m_iterationStatement, m_statement;
};

}  // namespace GMLAST

#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

class IfStatement : public Statement {
 public:
  IfStatement(std::unique_ptr<Value> expression,
              std::unique_ptr<Statement> statement, Location first = {},
              Location last = {});

  IfStatement(std::unique_ptr<Value> expression,
              std::unique_ptr<Statement> statement,
              std::unique_ptr<Statement> elseStatement, Location first = {},
              Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  const Value& expression() const noexcept { return *m_expression.get(); }

  const Statement& statement() const noexcept { return *m_statement.get(); }

  const Statement& elseStatement() const noexcept {
    return *m_elseStatement.get();
  }

  bool hasElseStatement() const noexcept {
    return static_cast<bool>(m_elseStatement);
  }

 private:
  std::unique_ptr<Value> m_expression;
  std::unique_ptr<Statement> m_statement, m_elseStatement;
};

}  // namespace GMLAST

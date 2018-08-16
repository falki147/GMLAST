#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

class DoStatement : public Statement {
 public:
  DoStatement(std::unique_ptr<Value> expression,
              std::unique_ptr<Statement> statement, Location first = {},
              Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  const Value& expression() const noexcept { return *m_expression.get(); }

  const Statement& statement() const noexcept { return *m_statement.get(); }

 private:
  std::unique_ptr<Value> m_expression;
  std::unique_ptr<Statement> m_statement;
};

}  // namespace GMLAST

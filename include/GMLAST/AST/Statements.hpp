#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

class Statements : public Statement {
 private:
  using StatementVector = std::vector<std::unique_ptr<Statement>>;

 public:
  Statements(StatementVector statements, Location first = {},
             Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  const StatementVector& statements() const noexcept { return m_statements; }

 private:
  StatementVector m_statements;
};

}  // namespace GMLAST

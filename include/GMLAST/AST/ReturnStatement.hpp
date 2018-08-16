#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

class ReturnStatement : public Statement {
 public:
  ReturnStatement(std::unique_ptr<Value> expression, Location first = {},
                  Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  const Value& expression() const noexcept { return *m_expression.get(); }

 private:
  std::unique_ptr<Value> m_expression;
};

}  // namespace GMLAST

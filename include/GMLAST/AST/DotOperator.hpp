#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

class DotOperator : public Value {
 public:
  DotOperator(const std::string& name, std::unique_ptr<Value> expression,
              Location first = {}, Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  const std::string& name() const noexcept { return m_name; }

  const Value& expression() const noexcept { return *m_expression.get(); }

 private:
  std::string m_name;
  std::unique_ptr<Value> m_expression;
};

}  // namespace GMLAST

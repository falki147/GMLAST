#pragma once

#include <GMLAST/AST/SwitchEntry.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

class SwitchStatement : public Statement {
 public:
  SwitchStatement(std::unique_ptr<Value> expression,
                  std::vector<SwitchEntry> switchEntries, Location first = {},
                  Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  const Value& expression() const noexcept { return *m_expression.get(); }

  const std::vector<SwitchEntry>& switchEntries() const noexcept {
    return m_switchEntries;
  }

 private:
  std::unique_ptr<Value> m_expression;
  std::vector<SwitchEntry> m_switchEntries;
};

}  // namespace GMLAST

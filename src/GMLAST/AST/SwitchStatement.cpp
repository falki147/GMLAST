#include <GMLAST/AST/SwitchStatement.hpp>
#include <cassert>

namespace GMLAST {

SwitchStatement::SwitchStatement(std::unique_ptr<Value> expression,
                                 std::vector<SwitchEntry> switchEntries,
                                 Location first, Location last)
    : Statement{first, last, NodeType::SwitchStatement},
      m_expression{std::move(expression)},
      m_switchEntries{std::move(switchEntries)} {
  assert(m_expression);
}

void SwitchStatement::visit(IVisitor& visitor) const {
  visitor.onSwitchStatement(*this);
}

}  // namespace GMLAST

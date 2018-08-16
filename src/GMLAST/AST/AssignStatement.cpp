#include <GMLAST/AST/AssignStatement.hpp>
#include <cassert>

namespace GMLAST {

AssignStatement::AssignStatement(Type type, std::unique_ptr<Value> left,
                                 std::unique_ptr<Value> right, Location first,
                                 Location last)
    : Value{first, last},
      m_type{type},
      m_left{std::move(left)},
      m_right{std::move(right)} {
  assert(m_left && m_right);
}

void AssignStatement::visit(IVisitor& visitor) const {
  visitor.onAssignStatement(*this);
}

}  // namespace GMLAST

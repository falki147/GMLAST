#include <GMLAST/AST/UnuaryOperator.hpp>
#include <cassert>

namespace GMLAST {

UnuaryOperator::UnuaryOperator(Type type, std::unique_ptr<Value> value,
                               Location first, Location last)
    : Value{first, last, NodeType::UnuaryOperator},
      m_type{type},
      m_value{std::move(value)} {
  assert(m_value);
}

void UnuaryOperator::visit(IVisitor& visitor) const {
  visitor.onUnuaryOperator(*this);
}

}  // namespace GMLAST

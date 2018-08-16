#include <GMLAST/AST/BinaryOperator.hpp>
#include <array>
#include <cassert>

namespace GMLAST {

BinaryOperator::BinaryOperator(Type type, std::unique_ptr<Value> left,
                               std::unique_ptr<Value> right, Location first,
                               Location last)
    : Value{first, last},
      m_type{type},
      m_left{std::move(left)},
      m_right{std::move(right)} {
  assert(m_left && m_right);
}

void BinaryOperator::visit(IVisitor& visitor) const {
  visitor.onBinaryOperator(*this);
}

}  // namespace GMLAST

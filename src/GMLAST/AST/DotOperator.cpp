#include <GMLAST/AST/DotOperator.hpp>
#include <cassert>

namespace GMLAST {

DotOperator::DotOperator(const std::string& name,
                         std::unique_ptr<Value> expression, Location first,
                         Location last)
    : Value{first, last}, m_name{name}, m_expression{std::move(expression)} {
  assert(m_expression);
}

void DotOperator::visit(IVisitor& visitor) const {
  visitor.onDotOperator(*this);
}

}  // namespace GMLAST

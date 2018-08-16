#include <GMLAST/AST/IntConstant.hpp>

namespace GMLAST {

IntConstant::IntConstant(int value, Location first, Location last)
    : Value{first, last}, m_value{value} {}

void IntConstant::visit(IVisitor& visitor) const {
  visitor.onIntConstant(*this);
}

}  // namespace GMLAST

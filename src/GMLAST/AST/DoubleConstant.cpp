#include <GMLAST/AST/DoubleConstant.hpp>

namespace GMLAST {

void DoubleConstant::visit(IVisitor& visitor) const {
  visitor.onDoubleConstant(*this);
}

}  // namespace GMLAST

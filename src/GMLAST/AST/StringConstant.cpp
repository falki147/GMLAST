#include <GMLAST/AST/StringConstant.hpp>

namespace GMLAST {

void StringConstant::visit(IVisitor& visitor) const {
  visitor.onStringConstant(*this);
}

}  // namespace GMLAST

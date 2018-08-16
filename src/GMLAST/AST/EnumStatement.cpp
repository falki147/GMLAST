#include <GMLAST/AST/EnumStatement.hpp>

namespace GMLAST {

void EnumStatement::visit(IVisitor& visitor) const {
  visitor.onEnumStatement(*this);
}

}  // namespace GMLAST

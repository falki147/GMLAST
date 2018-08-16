#include <GMLAST/AST/ExitStatement.hpp>

namespace GMLAST {

void ExitStatement::visit(IVisitor& visitor) const {
  visitor.onExitStatement(*this);
}

}  // namespace GMLAST

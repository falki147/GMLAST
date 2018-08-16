#include <GMLAST/AST/ContinueStatement.hpp>

namespace GMLAST {

void ContinueStatement::visit(IVisitor& visitor) const {
  visitor.onContinueStatement(*this);
}

}  // namespace GMLAST

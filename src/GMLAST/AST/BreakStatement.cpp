#include <GMLAST/AST/BreakStatement.hpp>

namespace GMLAST {

void BreakStatement::visit(IVisitor& visitor) const {
  visitor.onBreakStatement(*this);
}

}  // namespace GMLAST

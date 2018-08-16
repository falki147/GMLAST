#include <GMLAST/AST/DeclarationStatement.hpp>

namespace GMLAST {

void DeclarationStatement::visit(IVisitor& visitor) const {
  visitor.onDeclarationStatement(*this);
}

}  // namespace GMLAST

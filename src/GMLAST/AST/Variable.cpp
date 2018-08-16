#include <GMLAST/AST/Variable.hpp>

namespace GMLAST {

void Variable::visit(IVisitor& visitor) const { visitor.onVariable(*this); }

}  // namespace GMLAST

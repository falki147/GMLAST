#include <GMLAST/AST/Error.hpp>

namespace GMLAST {

void Error::visit(IVisitor& visitor) const { visitor.onError(*this); }

}  // namespace GMLAST

#include <GMLAST/AST/ReturnStatement.hpp>
#include <cassert>

namespace GMLAST {

ReturnStatement::ReturnStatement(std::unique_ptr<Value> expression,
                                 Location first, Location last)
    : Statement{first, last}, m_expression{std::move(expression)} {
  assert(m_expression);
}

void ReturnStatement::visit(IVisitor& visitor) const {
  visitor.onReturnStatement(*this);
}

}  // namespace GMLAST

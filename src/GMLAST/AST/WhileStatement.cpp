#include <GMLAST/AST/WhileStatement.hpp>
#include <cassert>

namespace GMLAST {

WhileStatement::WhileStatement(std::unique_ptr<Value> expression,
                               std::unique_ptr<Statement> statement,
                               Location first, Location last)
    : Statement{first, last},
      m_expression{std::move(expression)},
      m_statement{std::move(statement)} {
  assert(m_expression && m_statement);
}

void GMLAST::WhileStatement::visit(IVisitor& visitor) const {
  visitor.onWhileStatement(*this);
}

}  // namespace GMLAST

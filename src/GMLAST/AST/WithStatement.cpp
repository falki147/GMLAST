#include <GMLAST/AST/WithStatement.hpp>
#include <cassert>

namespace GMLAST {

WithStatement::WithStatement(std::unique_ptr<Value> expression,
                             std::unique_ptr<Statement> statement,
                             Location first, Location last)
    : Statement{first, last, NodeType::WithStatement},
      m_expression{std::move(expression)},
      m_statement{std::move(statement)} {
  assert(m_expression && m_statement);
}

void WithStatement::visit(IVisitor& visitor) const {
  visitor.onWithStatement(*this);
}

}  // namespace GMLAST

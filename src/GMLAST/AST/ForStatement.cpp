#include <GMLAST/AST/ForStatement.hpp>
#include <cassert>

namespace GMLAST {

ForStatement::ForStatement(std::unique_ptr<Statement> initStatement,
                           std::unique_ptr<Value> expression,
                           std::unique_ptr<Statement> iterationStatement,
                           std::unique_ptr<Statement> statement, Location first,
                           Location last)
    : Statement{first, last, NodeType::ForStatement},
      m_expression{std::move(expression)},
      m_initStatement{std::move(initStatement)},
      m_iterationStatement{std::move(iterationStatement)},
      m_statement{std::move(statement)} {
  assert(m_expression && m_initStatement && m_iterationStatement &&
         m_statement);
}

void ForStatement::visit(IVisitor& visitor) const {
  visitor.onForStatement(*this);
}

}  // namespace GMLAST

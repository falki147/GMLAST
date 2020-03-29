#include <GMLAST/AST/IfStatement.hpp>
#include <cassert>

namespace GMLAST {

IfStatement::IfStatement(std::unique_ptr<Value> expression,
                         std::unique_ptr<Statement> statement, Location first,
                         Location last)
    : Statement{first, last, NodeType::IfStatement},
      m_expression{std::move(expression)},
      m_statement{std::move(statement)} {
  assert(m_expression && m_statement);
}

IfStatement::IfStatement(std::unique_ptr<Value> expression,
                         std::unique_ptr<Statement> statement,
                         std::unique_ptr<Statement> elseStatement,
                         Location first, Location last)
    : Statement{first, last, NodeType::IfStatement},
      m_expression{std::move(expression)},
      m_statement{std::move(statement)},
      m_elseStatement{std::move(elseStatement)} {
  assert(m_expression && m_statement && m_elseStatement);
}

void IfStatement::visit(IVisitor& visitor) const {
  visitor.onIfStatement(*this);
}

}  // namespace GMLAST

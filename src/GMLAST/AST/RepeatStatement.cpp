#include <GMLAST/AST/RepeatStatement.hpp>
#include <cassert>

namespace GMLAST {

RepeatStatement::RepeatStatement(std::unique_ptr<Value> expression,
                                 std::unique_ptr<Statement> statement,
                                 Location first, Location last)
    : Statement{first, last},
      m_expression{std::move(expression)},
      m_statement{std::move(statement)} {
  assert(m_expression && m_statement);
}

void RepeatStatement::visit(IVisitor& visitor) const {
  visitor.onRepeatStatement(*this);
}

}  // namespace GMLAST

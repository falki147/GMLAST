#include <GMLAST/AST/Statements.hpp>
#include <algorithm>
#include <cassert>

namespace GMLAST {

Statements::Statements(StatementVector statements, Location first,
                       Location last)
    : Statement{first, last, NodeType::Statements},
      m_statements{std::move(statements)} {
  assert(std::all_of(m_statements.begin(), m_statements.end(),
                     [](const std::unique_ptr<Statement>& ptr) {
                       return static_cast<bool>(ptr);
                     }));
}

void Statements::visit(IVisitor& visitor) const { visitor.onStatements(*this); }

}  // namespace GMLAST

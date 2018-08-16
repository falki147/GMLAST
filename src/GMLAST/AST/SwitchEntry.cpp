#include <GMLAST/AST/SwitchEntry.hpp>
#include <algorithm>
#include <cassert>

namespace GMLAST {

SwitchEntry::SwitchEntry(std::vector<SwitchCase> switchCases,
                         StatementVector statements)
    : m_switchCases{std::move(switchCases)},
      m_statements{std::move(statements)} {
  assert(std::all_of(m_statements.begin(), m_statements.end(),
                     [](const std::unique_ptr<Statement>& ptr) {
                       return static_cast<bool>(ptr);
                     }));
}

}  // namespace GMLAST

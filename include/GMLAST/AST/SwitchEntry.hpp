#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/SwitchCase.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

class SwitchEntry {
 private:
  using StatementVector = std::vector<std::unique_ptr<Statement>>;

 public:
  SwitchEntry(std::vector<SwitchCase> switchCases, StatementVector statements);

  const std::vector<SwitchCase>& switchCases() const noexcept {
    return m_switchCases;
  }

  const StatementVector& statements() const noexcept { return m_statements; }

 private:
  std::vector<SwitchCase> m_switchCases;
  StatementVector m_statements;
};

}  // namespace GMLAST

/**
 * \file SwitchEntry.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/SwitchCase.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

/**
 * \brief Represents multiple \link SwitchCase SwitchCases\endlink and zero or
 * more statements
 */
class SwitchEntry {
 private:
  using StatementVector = std::vector<std::unique_ptr<Statement>>;

 public:
  /**
   * \brief Represents multiple SwitchCases and zero or more statements
   *
   * \param switchCases Vector with switch cases
   * \param statements Vector with statements. Every pointer must be not null.
   */
  SwitchEntry(std::vector<SwitchCase> switchCases, StatementVector statements);

  /**
   * \brief Return reference to switch cases vector
   */
  const std::vector<SwitchCase>& switchCases() const noexcept {
    return m_switchCases;
  }

  /**
   * \brief Return reference to statements vector
   */
  const StatementVector& statements() const noexcept { return m_statements; }

 private:
  std::vector<SwitchCase> m_switchCases;
  StatementVector m_statements;
};

}  // namespace GMLAST

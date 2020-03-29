/**
 * \file DeclarationStatement.hpp
 */

#pragma once

#include <GMLAST/AST/DeclarationEntry.hpp>
#include <GMLAST/AST/Statement.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

/**
 * \brief Node which represents zero or more \link DeclarationEntry
 * DeclarationEntries\endlink
 */
class DeclarationStatement : public Statement {
 public:
  /**
   * \brief It represents `var entries` or `globalvar entries` where `entries`
   * are zero or more \link DeclarationEntry DeclarationEntries\endlink
   *
   * \param isGlobal If statement is `var` this should be `false` otherwise
   * `true`.
   * \param entries Declaration entries i.e. everything after the inital keyword
   * e.g. `a` or `b = 1`
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  DeclarationStatement(bool isGlobal, std::vector<DeclarationEntry> entries,
                       Location first = {}, Location last = {})
      : Statement{first, last, NodeType::DeclarationStatement},
        m_isGlobal{isGlobal},
        m_entries{std::move(entries)} {}

  /**
   * \brief Function which calls IVisitor::onDeclarationStatement
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return if function is `globalvar` or not (`var` in this case)
   */
  bool isGlobal() const noexcept { return m_isGlobal; }

  /**
   * \brief Return reference to entries array
   */
  const std::vector<DeclarationEntry>& entries() const noexcept {
    return m_entries;
  }

 private:
  bool m_isGlobal;
  std::vector<DeclarationEntry> m_entries;
};

}  // namespace GMLAST

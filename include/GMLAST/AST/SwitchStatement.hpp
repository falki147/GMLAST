/**
 * \file SwitchStatement.hpp
 */

#pragma once

#include <GMLAST/AST/SwitchEntry.hpp>
#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

/**
 * \brief Node which represents a switch statement
 */
class SwitchStatement : public Statement {
 public:
  /**
   * \brief It represents `switch expression { switchCases }` where
   * `switchCases` are zero or more \link SwitchEntry SwitchEntries \endlink.
   *
   * \param expression Expression which is used to compare cases against. It
   * must not be null.
   * \param switchEntries Entries with cases and statements
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  SwitchStatement(std::unique_ptr<Value> expression,
                  std::vector<SwitchEntry> switchEntries, Location first = {},
                  Location last = {});

  /**
   * \brief Function which calls IVisitor::onSwitchStatement
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return reference to expression
   */
  const Value& expression() const noexcept { return *m_expression.get(); }

  /**
   * \brief Return reference to switch entries vector
   */
  const std::vector<SwitchEntry>& switchEntries() const noexcept {
    return m_switchEntries;
  }

 private:
  std::unique_ptr<Value> m_expression;
  std::vector<SwitchEntry> m_switchEntries;
};

}  // namespace GMLAST

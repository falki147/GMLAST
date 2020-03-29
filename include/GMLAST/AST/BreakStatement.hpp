/**
 * \file BreakStatement.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>

namespace GMLAST {

/**
 * \brief Node which represents a break statement
 */
class BreakStatement : public Statement {
 public:
  /**
   * \brief It represents `break`.
   *
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  BreakStatement(Location first = {}, Location last = {})
      : Statement{first, last, NodeType::BreakStatement} {}

  /**
   * \brief Function which calls IVisitor::onBreak
   */
  virtual void visit(IVisitor& visitor) const override;
};

}  // namespace GMLAST

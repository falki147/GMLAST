/**
 * \file ContinueStatement.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>

namespace GMLAST {

/**
 * \brief Node which represents a continue statement
 */
class ContinueStatement : public Statement {
 public:
  /**
   * \brief It represents `continue`.
   *
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  ContinueStatement(Location first = {}, Location last = {})
      : Statement{first, last, NodeType::ContinueStatement} {}

  /**
   * \brief Function which calls IVisitor::onContinue
   */
  virtual void visit(IVisitor& visitor) const override;
};

}  // namespace GMLAST

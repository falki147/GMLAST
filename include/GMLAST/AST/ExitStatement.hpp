/**
 * \file ExitStatement.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>

namespace GMLAST {

/**
 * \brief Node which represents an exit statement
 */
class ExitStatement : public Statement {
 public:
  /**
   * \brief It represents `exit`.
   *
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  ExitStatement(Location first = {}, Location last = {})
      : Statement{first, last, NodeType::ExitStatement} {}

  /**
   * \brief Function which calls IVisitor::onExit
   */
  virtual void visit(IVisitor& visitor) const override;
};

}  // namespace GMLAST

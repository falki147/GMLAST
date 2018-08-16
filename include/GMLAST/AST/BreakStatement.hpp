#pragma once

#include <GMLAST/AST/Statement.hpp>

namespace GMLAST {

class BreakStatement : public Statement {
 public:
  BreakStatement(Location first = {}, Location last = {})
      : Statement{first, last} {}

  virtual void visit(IVisitor& visitor) const override;
};

}  // namespace GMLAST

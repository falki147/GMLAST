#pragma once

#include <GMLAST/AST/Statement.hpp>

namespace GMLAST {

class ContinueStatement : public Statement {
 public:
  ContinueStatement(Location first = {}, Location last = {})
      : Statement{first, last} {}

  virtual void visit(IVisitor& visitor) const override;
};

}  // namespace GMLAST

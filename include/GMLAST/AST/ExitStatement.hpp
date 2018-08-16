#pragma once

#include <GMLAST/AST/Statement.hpp>

namespace GMLAST {

class ExitStatement : public Statement {
 public:
  ExitStatement(Location first = {}, Location last = {})
      : Statement{first, last} {}

  virtual void visit(IVisitor& visitor) const override;
};

}  // namespace GMLAST

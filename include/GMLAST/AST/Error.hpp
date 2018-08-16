#pragma once

#include <GMLAST/AST/Value.hpp>

namespace GMLAST {

class Error : public Value {
 public:
  virtual void visit(IVisitor& visitor) const override;
};

}  // namespace GMLAST

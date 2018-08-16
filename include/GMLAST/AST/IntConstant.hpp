#pragma once

#include <GMLAST/AST/Value.hpp>

namespace GMLAST {

class IntConstant : public Value {
 public:
  IntConstant(int value, Location first = {}, Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  int value() const noexcept { return m_value; }

 private:
  int m_value;
};

}  // namespace GMLAST

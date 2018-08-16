#pragma once

#include <GMLAST/AST/Value.hpp>

namespace GMLAST {

class DoubleConstant : public Value {
 public:
  DoubleConstant(double value, Location first = {}, Location last = {})
      : Value{first, last}, m_value{value} {}

  virtual void visit(IVisitor& visitor) const override;

  double value() const noexcept { return m_value; }

 private:
  double m_value;
};

}  // namespace GMLAST

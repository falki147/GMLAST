#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

class StringConstant : public Value {
 public:
  StringConstant(const std::string& value, Location first = {},
                 Location last = {})
      : Value{first, last}, m_value{value} {}

  virtual void visit(IVisitor& visitor) const override;

  const std::string& value() const noexcept { return m_value; }

 private:
  std::string m_value;
};

}  // namespace GMLAST

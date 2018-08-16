#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

class Variable : public Value {
 public:
  Variable(const std::string& name, Location first = {}, Location last = {})
      : Value{first, last}, m_name{name} {}

  virtual void visit(IVisitor& visitor) const override;

  const std::string& name() const noexcept { return m_name; }

 private:
  std::string m_name;
};

}  // namespace GMLAST

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>
#include <vector>

namespace GMLAST {

class FunctionCall : public Value {
 private:
  using ArgumentVector = std::vector<std::unique_ptr<Value>>;

 public:
  FunctionCall(const std::string& name, ArgumentVector arguments,
               Location first = {}, Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  const std::string& name() const noexcept { return m_name; }

  const ArgumentVector& arguments() const noexcept { return m_arguments; }

 private:
  std::string m_name;
  ArgumentVector m_arguments;
};

}  // namespace GMLAST

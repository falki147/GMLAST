#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

class EnumEntry {
 public:
  EnumEntry(const std::string& name);

  EnumEntry(const std::string& name, std::unique_ptr<Value> expression);

  const std::string& name() const noexcept { return m_name; }

  const Value& expression() const noexcept { return *m_expression.get(); }

  bool hasExpression() const noexcept {
    return static_cast<bool>(m_expression);
  }

 private:
  std::string m_name;
  std::unique_ptr<Value> m_expression;
};

}  // namespace GMLAST

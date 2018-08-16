#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

class SwitchCase {
 public:
  SwitchCase() = default;

  SwitchCase(std::unique_ptr<Value> value);

  const Value& value() const noexcept { return *m_value.get(); }

  bool hasValue() const noexcept { return static_cast<bool>(m_value); }

 private:
  std::unique_ptr<Value> m_value;
};

}  // namespace GMLAST

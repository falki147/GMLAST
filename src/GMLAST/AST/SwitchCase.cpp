#include <GMLAST/AST/SwitchCase.hpp>
#include <cassert>

namespace GMLAST {

SwitchCase::SwitchCase(std::unique_ptr<Value> value)
    : m_value{std::move(value)} {
  assert(m_value);
}

}  // namespace GMLAST

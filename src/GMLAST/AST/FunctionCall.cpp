#include <GMLAST/AST/FunctionCall.hpp>
#include <algorithm>
#include <cassert>

namespace GMLAST {

FunctionCall::FunctionCall(const std::string& name, ArgumentVector arguments,
                           Location first, Location last)
    : Value{first, last}, m_name{name}, m_arguments{std::move(arguments)} {
  assert(std::all_of(m_arguments.begin(), m_arguments.end(),
                     [](const std::unique_ptr<Value>& ptr) {
                       return static_cast<bool>(ptr);
                     }));
}

void FunctionCall::visit(IVisitor& visitor) const {
  visitor.onFunctionCall(*this);
}

}  // namespace GMLAST

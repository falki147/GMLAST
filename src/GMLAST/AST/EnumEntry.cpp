#include <GMLAST/AST/EnumEntry.hpp>
#include <cassert>

namespace GMLAST {

EnumEntry::EnumEntry(const std::string& name) : m_name{name} {}

EnumEntry::EnumEntry(const std::string& name, std::unique_ptr<Value> expression)
    : m_name{name}, m_expression{std::move(expression)} {
  assert(m_expression);
}

}  // namespace GMLAST

#include <GMLAST/AST/DeclarationEntry.hpp>
#include <cassert>

namespace GMLAST {

DeclarationEntry::DeclarationEntry(const std::string& name) : m_name{name} {}

DeclarationEntry::DeclarationEntry(const std::string& name,
                                   std::unique_ptr<Value> expression)
    : m_name{name}, m_expression{std::move(expression)} {
  assert(m_expression);
}

}  // namespace GMLAST

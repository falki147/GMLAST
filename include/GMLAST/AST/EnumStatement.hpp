#pragma once

#include <GMLAST/AST/EnumEntry.hpp>
#include <GMLAST/AST/Statement.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

class EnumStatement : public Statement {
 public:
  EnumStatement(const std::string& name, std::vector<EnumEntry> entries,
                Location first = {}, Location last = {})
      : Statement{first, last}, m_name{name}, m_entries{std::move(entries)} {}

  virtual void visit(IVisitor& visitor) const override;

  const std::string& name() const noexcept { return m_name; }

  const std::vector<EnumEntry>& entries() const noexcept { return m_entries; }

 private:
  std::string m_name;
  std::vector<EnumEntry> m_entries;
};

}  // namespace GMLAST

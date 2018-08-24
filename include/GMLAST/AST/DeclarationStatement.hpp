#pragma once

#include <GMLAST/AST/DeclarationEntry.hpp>
#include <GMLAST/AST/Statement.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

class DeclarationStatement : public Statement {
 public:
  DeclarationStatement(bool isGlobal, std::vector<DeclarationEntry> entries,
                       Location first = {}, Location last = {})
      : Statement{first, last},
        m_isGlobal{isGlobal},
        m_entries{std::move(entries)} {}

  virtual void visit(IVisitor& visitor) const override;

  bool isGlobal() const noexcept { return m_isGlobal; }

  const std::vector<DeclarationEntry>& entries() const noexcept {
    return m_entries;
  }

 private:
  bool m_isGlobal;
  std::vector<DeclarationEntry> m_entries;
};

}  // namespace GMLAST

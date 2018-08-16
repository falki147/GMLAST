#pragma once

#include <GMLAST/AST/IVisitor.hpp>
#include <GMLAST/Utils/Location.hpp>

namespace GMLAST {

class Base {
 public:
  Base() = default;
  Base(Location first, Location last) : m_first{first}, m_last{last} {}

  virtual ~Base() = default;
  virtual void visit(IVisitor& visitor) const = 0;

  const Location& first() const noexcept { return m_first; }

  const Location& last() const noexcept { return m_last; }
  
  bool hasPosition() const noexcept { return m_first && m_last; }
  
 private:
  Location m_first, m_last;
};

}  // namespace GMLAST

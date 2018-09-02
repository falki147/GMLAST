/**
 * \file EnumStatement.hpp
 */

#pragma once

#include <GMLAST/AST/EnumEntry.hpp>
#include <GMLAST/AST/Statement.hpp>
#include <memory>
#include <vector>

namespace GMLAST {

/**
 * \brief Node which represents a enum statement with zero or more \link
 * EnumEntry EnumEntries\endlink
 */
class EnumStatement : public Statement {
 public:
  /**
   * \brief It represents `enum name { entries }` where `entries` are zero or
   * more \link EnumEntry EnumEntries\endlink.
   *
   * \param name Name of the enum
   * \param entries Enum entries i.e. everything inside the curly braces e.g.
   * `a` or `b = 1`
   * \param first %Location of the first character of the statement in the input
   * \param last %Location after the last character of the statement in the
   * input
   */
  EnumStatement(const std::string& name, std::vector<EnumEntry> entries,
                Location first = {}, Location last = {})
      : Statement{first, last}, m_name{name}, m_entries{std::move(entries)} {}

  /**
   * \brief Function which calls IVisitor::onEnumStatement
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return name of the enum
   */
  const std::string& name() const noexcept { return m_name; }

  /**
   * \brief Return reference to entries array
   */
  const std::vector<EnumEntry>& entries() const noexcept { return m_entries; }

 private:
  std::string m_name;
  std::vector<EnumEntry> m_entries;
};

}  // namespace GMLAST

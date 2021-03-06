/**
 * \file Base.hpp
 */

#pragma once

#include <GMLAST/AST/IVisitor.hpp>
#include <GMLAST/AST/NodeType.hpp>
#include <GMLAST/Utils/Location.hpp>

namespace GMLAST {

/**
 * \brief %Base class of every AST node
 */
class Base {
 public:
  /**
   * \brief Default constructor which leaves the locations default (invalid)
   */
  Base() = default;

  /**
   * \brief Constructor which sets the locations
   *
   * \param first %Location of the first character of the expression or
   * statement in the input
   * \param last %Location after the last character of the expression or
   * statement in the input
   * \param type Type of the node
   */
  Base(Location first, Location last, NodeType type = NodeType::Error)
      : m_first{first}, m_last{last}, m_nodeType{type} {}

  /**
   * \brief Virtual default destructor to make class deletable
   */
  virtual ~Base() = default;

  /**
   * \brief Abstract method which calls the method in the IVisitor interface
   * that belongs to the implementing class
   */
  virtual void visit(IVisitor& visitor) const = 0;

  /**
   * \brief Returns the first location (position at first character). It may be
   * invalid.
   */
  const Location& first() const noexcept { return m_first; }

  /**
   * \brief Returns the last location (position after last character). It may be
   * invalid.
   */
  const Location& last() const noexcept { return m_last; }

  /**
   * \brief Returns the type of the node.
   */
  const NodeType nodeType() const noexcept { return m_nodeType; }

 private:
  Location m_first, m_last;
  NodeType m_nodeType{NodeType::Error};
};

}  // namespace GMLAST

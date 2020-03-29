/**
 * \file Statement.hpp
 */

#pragma once

#include <GMLAST/AST/Base.hpp>

namespace GMLAST {

/**
 * \brief Base class of every statement
 */
class Statement : public Base {
 public:
  /**
   * \brief Default constructor which leaves the locations default (invalid)
   */
  Statement() = default;

  /**
   * \brief Constructor which sets the locations
   *
   * \param first %Location of the first character of the expression or
   * statement in the input
   * \param last %Location after the last character of the expression or
   * statement in the input
   * \param type Type of the node
   */
  Statement(Location first, Location last, NodeType type = NodeType::Error)
      : Base(first, last, type) {}
};

}  // namespace GMLAST

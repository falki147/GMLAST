/**
 * \file Value.hpp
 */

#pragma once

#include <GMLAST/AST/Statement.hpp>

namespace GMLAST {

/**
 * \brief Base class of every expression
 */
class Value : public Statement {
 public:
  /**
   * \brief Default constructor which leaves the locations default (invalid)
   */
  Value() = default;

  /**
   * \brief Constructor which sets the locations
   *
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  Value(Location first, Location last) : Statement(first, last) {}
};

}  // namespace GMLAST

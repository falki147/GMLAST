/**
 * \file Location.hpp
 */

#pragma once

namespace GMLAST {

/**
 * \brief Contains line, column and index information.
 *
 * It is only valid if all three members are not negative.
 */
struct Location {
  /**
   * \brief Default constructor. Sets the Location to an invalid state.
   */
  Location() = default;

  /**
   * \brief Constructor which sets the location values
   */
  Location(int line, int column, int index)
      : line{line}, column{column}, index{index} {}

  /**
   * \brief Utility function which checks if the location is valid
   */
  operator bool() const noexcept {
    return line >= 0 && column >= 0 && index >= 0;
  }

  /**
   * \brief The number of lines since the beginning (first line is 0)
   */
  int line{-1};

  /**
   * \brief The number of UTF-8 characters since the last line break (first
   * column is 0)
   */
  int column{-1};

  /**
   * \brief The number of UTF-8 characters since the beginning
   */
  int index{-1};
};

}  // namespace GMLAST

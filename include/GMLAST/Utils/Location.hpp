#pragma once

namespace GMLAST {

struct Location {
  Location() = default;

  Location(int line, int column, int index)
      : line{line}, column{column}, index{index} {}

  operator bool() const noexcept {
    return line >= 0 && column >= 0 && index >= 0;
  }

  int line{-1}, column{-1}, index{-1};
};

}  // namespace GMLAST

#pragma once

namespace GMLAST {

struct Location {
  operator bool() const noexcept {
    return line != InvalidValue && column != InvalidValue;
  }

  static const auto InvalidValue = 0xFFFFFFFF;
  unsigned int line{InvalidValue}, column{InvalidValue};
};

}  // namespace GMLAST

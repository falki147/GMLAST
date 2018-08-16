#pragma once

#include <GMLAST/AST/Base.hpp>

namespace GMLAST {

class Statement : public Base {
 public:
  Statement() = default;
  Statement(Location first, Location last) : Base(first, last) {}
};

}  // namespace GMLAST

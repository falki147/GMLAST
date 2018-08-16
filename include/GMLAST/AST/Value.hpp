#pragma once

#include <GMLAST/AST/Statement.hpp>

namespace GMLAST {

class Value : public Statement {
 public:
  Value() = default;
  Value(Location first, Location last) : Statement(first, last) {}
};

}  // namespace GMLAST

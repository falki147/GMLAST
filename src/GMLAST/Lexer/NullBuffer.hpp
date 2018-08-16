#pragma once

#include <streambuf>

namespace GMLAST {

struct NullBuffer : std::streambuf {
  int overflow(int c) { return c; }
};

}  // namespace GMLAST

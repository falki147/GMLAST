#pragma once

namespace GMLAST {

struct IStream {
  virtual ~IStream() = default;
  virtual int get() = 0;
};

}  // namespace GMLAST

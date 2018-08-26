#pragma once

#include <memory>
#include <utility>

namespace GMLAST {

template <typename T, typename... Args>
std::unique_ptr<T> MakeUnique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
std::shared_ptr<T> MakeShared(Args&&... args) {
  return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
}

}  // namespace GMLAST

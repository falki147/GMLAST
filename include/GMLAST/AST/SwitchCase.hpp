/**
 * \file SwitchCase.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

/**
 * \brief Represents switch cases in a SwitchEntry
 */
class SwitchCase {
 public:
  /**
   * \brief It represents `default:` inside a SwitchEntry
   */
  SwitchCase() = default;

  /**
   * \brief It represents `case expression:` inside a SwitchEntry
   *
   * \param value Expression to compare to. It must not be null.
   */
  SwitchCase(std::unique_ptr<Value> value);

  /**
   * \brief Return reference to value
   */
  const Value& value() const noexcept { return *m_value.get(); }

  /**
   * \brief Check if value is valid/set
   */
  bool hasValue() const noexcept { return static_cast<bool>(m_value); }

 private:
  std::unique_ptr<Value> m_value;
};

}  // namespace GMLAST

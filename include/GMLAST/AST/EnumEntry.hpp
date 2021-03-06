/**
 * \file EnumEntry.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>

namespace GMLAST {

/**
 * \brief Represents `name` or `name = expression` in a EnumStatement
 */
class EnumEntry {
 public:
  /**
   * \brief It represents `name` inside a EnumStatement
   *
   * \param name Name of the declared variable
   */
  EnumEntry(const std::string& name);

  /**
   * \brief It represents `name = expression` inside a EnumStatement
   *
   * \param name Name of the declared variable
   * \param expression Expression which the variable is initialized to. It must
   * not be null.
   */
  EnumEntry(const std::string& name, std::unique_ptr<Value> expression);

  /**
   * \brief Return name of the declared variable
   */
  const std::string& name() const noexcept { return m_name; }

  /**
   * \brief Return reference to expression
   */
  const Value& expression() const noexcept { return *m_expression.get(); }

  /**
   * \brief Check if expression is valid/set
   */
  bool hasExpression() const noexcept {
    return static_cast<bool>(m_expression);
  }

 private:
  std::string m_name;
  std::unique_ptr<Value> m_expression;
};

}  // namespace GMLAST

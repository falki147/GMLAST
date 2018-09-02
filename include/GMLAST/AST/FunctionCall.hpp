/**
 * \file FunctionCall.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>
#include <string>
#include <vector>

namespace GMLAST {

/**
 * \brief Node which represents a function call expression
 */
class FunctionCall : public Value {
 private:
  using ArgumentVector = std::vector<std::unique_ptr<Value>>;

 public:
  /**
   * \brief It represents `name(arguments)` where `arguments` are zero or more
   * expressions.
   *
   * \param name Name of the function which is called
   * \param arguments Arguments which are passed to the function when calling.
   * All arguments must not be null.
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  FunctionCall(const std::string& name, ArgumentVector arguments,
               Location first = {}, Location last = {});

  /**
   * \brief Function which calls IVisitor::onFunctionCall
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return name
   */
  const std::string& name() const noexcept { return m_name; }

  /**
   * \brief Return reference to arguments array
   */
  const ArgumentVector& arguments() const noexcept { return m_arguments; }

 private:
  std::string m_name;
  ArgumentVector m_arguments;
};

}  // namespace GMLAST

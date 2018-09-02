/**
 * \file ArrayOperator.hpp
 */

#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

/**
 * \brief Node which represents a array expression
 */
class ArrayOperator : public Value {
 public:
  /**
   * \brief Type of the operator
   */
  enum class Type {
    Array,     ///< Normal array operator e.g. `a[b]` or `a[b,c]`
    Grid,      ///< Grid accessor e.g. <tt>a[\#b,c]</tt>
    List,      ///< List accessor e.g. `a[|b]`
    Map,       ///< Map accessor e.g. `a[?b]`
    Reference  ///< Reference array operator e.g. `a[@b]` or `a[@b,c]`
  };

  /**
   * \brief Constructor which sets only one index. It represents
   * `array[index1]`, where `[` is different depending on the type.
   *
   * This constructor should only be used with Type::Array, Type::List,
   * Type::Map or Type::Reference.
   *
   * \param type Type of the operator
   * \param array Index of the data structure or array. It must not be null.
   * \param index1 Index or key in the array or data structure. It must not be
   * null.
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  ArrayOperator(Type type, std::unique_ptr<Value> array,
                std::unique_ptr<Value> index1, Location first = {},
                Location last = {});

  /**
   * \brief Constructor which sets two indecies. It represents `array[index1,
   * index2]`, where `[` is different depending on the type.
   *
   * This constructor should only be used with Type::Array, Type::Grid or
   * Type::Reference
   *
   * \param type Type of the operator
   * \param array Index of the data structure or array. It must not be null.
   * \param index1 Index or x position in the array or data structure. It must
   * not be null.
   * \param index2 Second index or y position in the array or data structure. It
   * must not be null.
   * \param first %Location of the first character of the expression in the
   * input
   * \param last %Location after the last character of the expression in the
   * input
   */
  ArrayOperator(Type type, std::unique_ptr<Value> array,
                std::unique_ptr<Value> index1, std::unique_ptr<Value> index2,
                Location first = {}, Location last = {});

  /**
   * \brief Function which calls IVisitor::onArrayOperator
   */
  virtual void visit(IVisitor& visitor) const override;

  /**
   * \brief Return type
   */
  Type type() const noexcept { return m_type; }

  /**
   * \brief Return reference to array expression
   */
  const Value& array() const noexcept { return *m_array.get(); }

  /**
   * \brief Return reference to index1 expression
   */
  const Value& index1() const noexcept { return *m_index1.get(); }

  /**
   * \brief Return reference to index2 expression
   */
  const Value& index2() const noexcept { return *m_index2.get(); }

  /**
   * \brief Check if index2 is valid/set
   */
  bool hasIndex2() const noexcept { return static_cast<bool>(m_index2); }

 private:
  Type m_type;
  std::unique_ptr<Value> m_array, m_index1, m_index2;
};

}  // namespace GMLAST

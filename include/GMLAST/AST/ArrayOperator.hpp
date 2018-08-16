#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

class ArrayOperator : public Value {
 public:
  enum class Type { Array, Grid, List, Map, Reference };

  ArrayOperator(Type type, std::unique_ptr<Value> array,
                std::unique_ptr<Value> index1, Location first = {},
                Location last = {});

  ArrayOperator(Type type, std::unique_ptr<Value> array,
                std::unique_ptr<Value> index1, std::unique_ptr<Value> index2,
                Location first = {}, Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  Type type() const noexcept { return m_type; }

  const Value& array() const noexcept { return *m_array.get(); }

  const Value& index1() const noexcept { return *m_index1.get(); }

  const Value& index2() const noexcept { return *m_index2.get(); }

  bool hasIndex2() const noexcept { return static_cast<bool>(m_index2); }

 private:
  Type m_type;
  std::unique_ptr<Value> m_array, m_index1, m_index2;
};

}  // namespace GMLAST

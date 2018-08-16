#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

class BinaryOperator : public Value {
 public:
  enum class Type {
    Add,
    BitwiseAnd,
    BitwiseLeft,
    BitwiseOr,
    BitwiseRight,
    BitwiseXor,
    CompareEqual,
    CompareGreater,
    CompareGreaterEqual,
    CompareLess,
    CompareLessEqual,
    CompareNotEqual,
    Divide,
    IntDivide,
    LogicalAnd,
    LogicalOr,
    LogicalXor,
    Modulo,
    Multiply,
    Subtract
  };

  BinaryOperator(Type type, std::unique_ptr<Value> left,
                 std::unique_ptr<Value> right, Location first = {},
                 Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  Type type() const noexcept { return m_type; }

  const Value& left() const noexcept { return *m_left.get(); }

  const Value& right() const noexcept { return *m_right.get(); }

 private:
  Type m_type;
  std::unique_ptr<Value> m_left, m_right;
};

}  // namespace GMLAST

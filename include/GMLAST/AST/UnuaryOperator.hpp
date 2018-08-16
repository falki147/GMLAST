#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

class UnuaryOperator : public Value {
 public:
  enum class Type {
    BitwiseNot,
    LogicalNot,
    PostfixDecrement,
    PostfixIncrement,
    PrefixDecrement,
    PrefixIncrement,
    Minus,
    Plus
  };

  UnuaryOperator(Type type, std::unique_ptr<Value> value, Location first = {},
                 Location last = {});

  virtual void visit(IVisitor& visitor) const override;

  Type type() const noexcept { return m_type; }

  const Value& value() const noexcept { return *m_value.get(); }

 private:
  Type m_type;
  std::unique_ptr<Value> m_value;
};

}  // namespace GMLAST

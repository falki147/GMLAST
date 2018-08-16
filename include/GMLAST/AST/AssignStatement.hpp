#pragma once

#include <GMLAST/AST/Value.hpp>
#include <memory>

namespace GMLAST {

class AssignStatement : public Value {
 public:
  enum class Type { Assign, Add, BitAnd, BitOr, BitXor, Div, Mod, Mul, Sub };

  AssignStatement(Type type, std::unique_ptr<Value> left,
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

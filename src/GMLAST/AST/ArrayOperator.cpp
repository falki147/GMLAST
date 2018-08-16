#include <GMLAST/AST/ArrayOperator.hpp>
#include <cassert>

namespace GMLAST {

ArrayOperator::ArrayOperator(Type type, std::unique_ptr<Value> array,
                             std::unique_ptr<Value> index1, Location first,
                             Location last)
    : Value{first, last},
      m_type{type},
      m_array{std::move(array)},
      m_index1{std::move(index1)} {
  assert(type == Type::Array || type == Type::List || type == Type::Map ||
         type == Type::Reference);

  assert(m_array && m_index1);
}

ArrayOperator::ArrayOperator(Type type, std::unique_ptr<Value> array,
                             std::unique_ptr<Value> index1,
                             std::unique_ptr<Value> index2, Location first,
                             Location last)
    : Value{first, last},
      m_type{type},
      m_array{std::move(array)},
      m_index1{std::move(index1)},
      m_index2{std::move(index2)} {
  assert(type == Type::Array || type == Type::Grid || type == Type::Reference);

  assert(m_array && m_index1 && m_index2);
}

void ArrayOperator::visit(IVisitor& visitor) const {
  visitor.onArrayOperator(*this);
}

}  // namespace GMLAST

#include <GMLAST/AST/Base.hpp>
#include <GMLAST/Parser/IsLValue.hpp>

namespace GMLAST {

bool IsLValue::visit(const Base& base) {
  IsLValue visitor;
  base.visit(visitor);
  return visitor.m_isLValue;
}

void IsLValue::onArrayOperator(const ArrayOperator&) { m_isLValue = true; }

void IsLValue::onAssignStatement(const AssignStatement&) { m_isLValue = true; }

void IsLValue::onBinaryOperator(const BinaryOperator&) {}

void IsLValue::onBreakStatement(const BreakStatement&) {}

void IsLValue::onContinueStatement(const ContinueStatement&) {}

void IsLValue::onDeclarationStatement(const DeclarationStatement&) {}

void IsLValue::onDoStatement(const DoStatement&) {}

void IsLValue::onDotOperator(const DotOperator&) { m_isLValue = true; }

void IsLValue::onDoubleConstant(const DoubleConstant&) {}

void IsLValue::onEnumStatement(const EnumStatement&) {}

void IsLValue::onError(const Error&) { m_isLValue = true; }

void IsLValue::onExitStatement(const ExitStatement&) {}

void IsLValue::onForStatement(const ForStatement&) {}

void IsLValue::onFunctionCall(const FunctionCall&) {}

void IsLValue::onIfStatement(const IfStatement&) {}

void IsLValue::onIntConstant(const IntConstant&) {}

void IsLValue::onRepeatStatement(const RepeatStatement&) {}

void IsLValue::onReturnStatement(const ReturnStatement&) {}

void IsLValue::onStatements(const Statements&) {}

void IsLValue::onStringConstant(const StringConstant&) {}

void IsLValue::onSwitchStatement(const SwitchStatement&) {}

void IsLValue::onUnuaryOperator(const UnuaryOperator&) {}

void IsLValue::onVariable(const Variable&) { m_isLValue = true; }

void IsLValue::onWhileStatement(const WhileStatement&) {}

void IsLValue::onWithStatement(const WithStatement&) {}

}  // namespace GMLAST

#include <GMLAST/AST/Base.hpp>
#include <GMLAST/Parser/IsLValue.hpp>

namespace GMLAST {

bool IsLValue::visit(const Base& base) {
  IsLValue visitor;
  base.visit(visitor);
  return visitor.m_isLValue;
}

void IsLValue::onArrayOperator(const ArrayOperator& arrayOperator) {
  m_isLValue = true;
}

void IsLValue::onAssignStatement(const AssignStatement& assignStatement) {
  m_isLValue = true;
}

void IsLValue::onBinaryOperator(const BinaryOperator& binaryOperator) {}

void IsLValue::onBreakStatement(const BreakStatement& breakStatement) {}

void IsLValue::onContinueStatement(const ContinueStatement& continueStatement) {
}

void IsLValue::onDeclarationStatement(
    const DeclarationStatement& declarationStatement) {}

void IsLValue::onDoStatement(const DoStatement& doStatement) {}

void IsLValue::onDotOperator(const DotOperator& dotOperator) {
  m_isLValue = true;
}

void IsLValue::onDoubleConstant(const DoubleConstant& doubleConstant) {}

void IsLValue::onEnumStatement(const EnumStatement& enumStatement) {}

void IsLValue::onError(const Error& error) { m_isLValue = true; }

void IsLValue::onExitStatement(const ExitStatement& exitStatement) {}

void IsLValue::onForStatement(const ForStatement& forStatement) {}

void IsLValue::onFunctionCall(const FunctionCall& functionCall) {}

void IsLValue::onIfStatement(const IfStatement& ifStatement) {}

void IsLValue::onIntConstant(const IntConstant& intConstant) {}

void IsLValue::onRepeatStatement(const RepeatStatement& repeatStatement) {}

void IsLValue::onReturnStatement(const ReturnStatement& returnStatement) {}

void IsLValue::onStatements(const Statements& statements) {}

void IsLValue::onStringConstant(const StringConstant& stringConstant) {}

void IsLValue::onSwitchStatement(const SwitchStatement& switchStatement) {}

void IsLValue::onUnuaryOperator(const UnuaryOperator& unuaryOperator) {}

void IsLValue::onVariable(const Variable& variable) { m_isLValue = true; }

void IsLValue::onWhileStatement(const WhileStatement& whileStatement) {}

void IsLValue::onWithStatement(const WithStatement& withStatement) {}

}  // namespace GMLAST

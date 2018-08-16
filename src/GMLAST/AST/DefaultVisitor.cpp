#include <GMLAST/AST/DefaultVisitor.hpp>
#include <cassert>

namespace GMLAST {

void DefaultVisitor::onArrayOperator(const ArrayOperator&) { assert(false); }

void DefaultVisitor::onAssignStatement(const AssignStatement&) {
  assert(false);
}

void DefaultVisitor::onBinaryOperator(const BinaryOperator&) { assert(false); }

void DefaultVisitor::onBreakStatement(const BreakStatement&) { assert(false); }

void DefaultVisitor::onContinueStatement(const ContinueStatement&) {
  assert(false);
}

void DefaultVisitor::onDeclarationStatement(const DeclarationStatement&) {
  assert(false);
}

void DefaultVisitor::onDoStatement(const DoStatement&) { assert(false); }

void DefaultVisitor::onDotOperator(const DotOperator&) { assert(false); }

void DefaultVisitor::onDoubleConstant(const DoubleConstant&) { assert(false); }

void DefaultVisitor::onEnumStatement(const EnumStatement&) { assert(false); }

void DefaultVisitor::onError(const Error&) { assert(false); }

void DefaultVisitor::onExitStatement(const ExitStatement&) { assert(false); }

void DefaultVisitor::onForStatement(const ForStatement&) { assert(false); }

void DefaultVisitor::onFunctionCall(const FunctionCall&) { assert(false); }

void DefaultVisitor::onIfStatement(const IfStatement&) { assert(false); }

void DefaultVisitor::onIntConstant(const IntConstant&) { assert(false); }

void DefaultVisitor::onRepeatStatement(const RepeatStatement&) {
  assert(false);
}

void DefaultVisitor::onReturnStatement(const ReturnStatement&) {
  assert(false);
}

void DefaultVisitor::onStatements(const Statements&) { assert(false); }

void DefaultVisitor::onStringConstant(const StringConstant&) { assert(false); }

void DefaultVisitor::onSwitchStatement(const SwitchStatement&) {
  assert(false);
}

void DefaultVisitor::onUnuaryOperator(const UnuaryOperator&) { assert(false); }

void DefaultVisitor::onVariable(const Variable&) { assert(false); }

void DefaultVisitor::onWhileStatement(const WhileStatement&) { assert(false); }

void DefaultVisitor::onWithStatement(const WithStatement&) { assert(false); }

}  // namespace GMLAST

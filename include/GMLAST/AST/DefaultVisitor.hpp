#pragma once

#include <GMLAST/AST/IVisitor.hpp>

namespace GMLAST {

struct DefaultVisitor : IVisitor {
  virtual void onArrayOperator(const ArrayOperator& arrayOperator) override;
  virtual void onAssignStatement(
      const AssignStatement& assignStatement) override;
  virtual void onBinaryOperator(const BinaryOperator& binaryOperator) override;
  virtual void onBreakStatement(const BreakStatement& breakStatement) override;
  virtual void onContinueStatement(
      const ContinueStatement& continueStatement) override;
  virtual void onDeclarationStatement(
      const DeclarationStatement& declarationStatement) override;
  virtual void onDoStatement(const DoStatement& doStatement) override;
  virtual void onDotOperator(const DotOperator& dotOperator) override;
  virtual void onDoubleConstant(const DoubleConstant& doubleConstant) override;
  virtual void onEnumStatement(const EnumStatement& enumStatement) override;
  virtual void onError(const Error& error) override;
  virtual void onExitStatement(const ExitStatement& exitStatement) override;
  virtual void onForStatement(const ForStatement& forStatement) override;
  virtual void onFunctionCall(const FunctionCall& functionCall) override;
  virtual void onIfStatement(const IfStatement& ifStatement) override;
  virtual void onIntConstant(const IntConstant& intConstant) override;
  virtual void onRepeatStatement(
      const RepeatStatement& repeatStatement) override;
  virtual void onReturnStatement(
      const ReturnStatement& returnStatement) override;
  virtual void onStatements(const Statements& statements) override;
  virtual void onStringConstant(const StringConstant& stringConstant) override;
  virtual void onSwitchStatement(
      const SwitchStatement& switchStatement) override;
  virtual void onUnuaryOperator(const UnuaryOperator& unuaryOperator) override;
  virtual void onVariable(const Variable& variable) override;
  virtual void onWhileStatement(const WhileStatement& whileStatement) override;
  virtual void onWithStatement(const WithStatement& withStatement) override;
};

}  // namespace GMLAST

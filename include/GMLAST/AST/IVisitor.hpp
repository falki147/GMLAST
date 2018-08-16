#pragma once

namespace GMLAST {

class ArrayOperator;
class AssignStatement;
class BinaryOperator;
class BreakStatement;
class ContinueStatement;
class DeclarationStatement;
class DoStatement;
class DotOperator;
class DoubleConstant;
class EnumStatement;
class Error;
class ExitStatement;
class ForStatement;
class FunctionCall;
class IfStatement;
class IntConstant;
class RepeatStatement;
class ReturnStatement;
class Statements;
class StringConstant;
class SwitchStatement;
class UnuaryOperator;
class Variable;
class WhileStatement;
class WithStatement;

struct IVisitor {
  virtual ~IVisitor() = default;
  virtual void onArrayOperator(const ArrayOperator& arrayOperator) = 0;
  virtual void onAssignStatement(const AssignStatement& assignStatement) = 0;
  virtual void onBinaryOperator(const BinaryOperator& binaryOperator) = 0;
  virtual void onBreakStatement(const BreakStatement& breakStatement) = 0;
  virtual void onContinueStatement(
      const ContinueStatement& continueStatement) = 0;
  virtual void onDeclarationStatement(
      const DeclarationStatement& declarationStatement) = 0;
  virtual void onDoStatement(const DoStatement& doStatement) = 0;
  virtual void onDotOperator(const DotOperator& dotOperator) = 0;
  virtual void onDoubleConstant(const DoubleConstant& doubleConstant) = 0;
  virtual void onEnumStatement(const EnumStatement& enumStatement) = 0;
  virtual void onError(const Error& error) = 0;
  virtual void onExitStatement(const ExitStatement& exitStatement) = 0;
  virtual void onForStatement(const ForStatement& forStatement) = 0;
  virtual void onFunctionCall(const FunctionCall& functionCall) = 0;
  virtual void onIfStatement(const IfStatement& ifStatement) = 0;
  virtual void onIntConstant(const IntConstant& intConstant) = 0;
  virtual void onRepeatStatement(const RepeatStatement& repeatStatement) = 0;
  virtual void onReturnStatement(const ReturnStatement& returnStatement) = 0;
  virtual void onStatements(const Statements& statements) = 0;
  virtual void onStringConstant(const StringConstant& stringConstant) = 0;
  virtual void onSwitchStatement(const SwitchStatement& switchStatement) = 0;
  virtual void onUnuaryOperator(const UnuaryOperator& unuaryOperator) = 0;
  virtual void onVariable(const Variable& variable) = 0;
  virtual void onWhileStatement(const WhileStatement& whileStatement) = 0;
  virtual void onWithStatement(const WithStatement& withStatement) = 0;
};

}  // namespace GMLAST

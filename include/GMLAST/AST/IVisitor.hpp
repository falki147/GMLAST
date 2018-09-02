/**
 * \file IVisitor.hpp
 */

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

/**
 * \brief Interface for implementing a visitor
 */
struct IVisitor {
  /**
   * \brief Virtual default destructor to make class deletable
   */
  virtual ~IVisitor() = default;

  /**
   * \brief Called when Base::visit is called on ArrayOperator
   */
  virtual void onArrayOperator(const ArrayOperator& arrayOperator) = 0;

  /**
   * \brief Called when Base::visit is called on AssignStatement
   */
  virtual void onAssignStatement(const AssignStatement& assignStatement) = 0;

  /**
   * \brief Called when Base::visit is called on BinaryOperator
   */
  virtual void onBinaryOperator(const BinaryOperator& binaryOperator) = 0;

  /**
   * \brief Called when Base::visit is called on BreakStatement
   */
  virtual void onBreakStatement(const BreakStatement& breakStatement) = 0;

  /**
   * \brief Called when Base::visit is called on ContinueStatement
   */
  virtual void onContinueStatement(
      const ContinueStatement& continueStatement) = 0;

  /**
   * \brief Called when Base::visit is called on DeclarationStatement
   */
  virtual void onDeclarationStatement(
      const DeclarationStatement& declarationStatement) = 0;

  /**
   * \brief Called when Base::visit is called on DoStatement
   */
  virtual void onDoStatement(const DoStatement& doStatement) = 0;

  /**
   * \brief Called when Base::visit is called on DotOperator
   */
  virtual void onDotOperator(const DotOperator& dotOperator) = 0;

  /**
   * \brief Called when Base::visit is called on DoubleConstant
   */
  virtual void onDoubleConstant(const DoubleConstant& doubleConstant) = 0;

  /**
   * \brief Called when Base::visit is called on EnumStatement
   */
  virtual void onEnumStatement(const EnumStatement& enumStatement) = 0;

  /**
   * \brief Called when Base::visit is called on Error
   */
  virtual void onError(const Error& error) = 0;

  /**
   * \brief Called when Base::visit is called on ExitStatement
   */
  virtual void onExitStatement(const ExitStatement& exitStatement) = 0;

  /**
   * \brief Called when Base::visit is called on ForStatement
   */
  virtual void onForStatement(const ForStatement& forStatement) = 0;

  /**
   * \brief Called when Base::visit is called on FunctionCall
   */
  virtual void onFunctionCall(const FunctionCall& functionCall) = 0;

  /**
   * \brief Called when Base::visit is called on IfStatement
   */
  virtual void onIfStatement(const IfStatement& ifStatement) = 0;

  /**
   * \brief Called when Base::visit is called on IntConstant
   */
  virtual void onIntConstant(const IntConstant& intConstant) = 0;

  /**
   * \brief Called when Base::visit is called on RepeatStatement
   */
  virtual void onRepeatStatement(const RepeatStatement& repeatStatement) = 0;

  /**
   * \brief Called when Base::visit is called on ReturnStatement
   */
  virtual void onReturnStatement(const ReturnStatement& returnStatement) = 0;

  /**
   * \brief Called when Base::visit is called on Statements
   */
  virtual void onStatements(const Statements& statements) = 0;

  /**
   * \brief Called when Base::visit is called on StringConstant
   */
  virtual void onStringConstant(const StringConstant& stringConstant) = 0;

  /**
   * \brief Called when Base::visit is called on SwitchStatement
   */
  virtual void onSwitchStatement(const SwitchStatement& switchStatement) = 0;

  /**
   * \brief Called when Base::visit is called on UnuaryOperator
   */
  virtual void onUnuaryOperator(const UnuaryOperator& unuaryOperator) = 0;

  /**
   * \brief Called when Base::visit is called on Variable
   */
  virtual void onVariable(const Variable& variable) = 0;

  /**
   * \brief Called when Base::visit is called on WhileStatement
   */
  virtual void onWhileStatement(const WhileStatement& whileStatement) = 0;

  /**
   * \brief Called when Base::visit is called on WithStatement
   */
  virtual void onWithStatement(const WithStatement& withStatement) = 0;
};

}  // namespace GMLAST

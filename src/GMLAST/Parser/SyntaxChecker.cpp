#include <GMLAST/AST/ArrayOperator.hpp>
#include <GMLAST/AST/AssignStatement.hpp>
#include <GMLAST/AST/BinaryOperator.hpp>
#include <GMLAST/AST/DeclarationStatement.hpp>
#include <GMLAST/AST/DoStatement.hpp>
#include <GMLAST/AST/DotOperator.hpp>
#include <GMLAST/AST/DoubleConstant.hpp>
#include <GMLAST/AST/EnumStatement.hpp>
#include <GMLAST/AST/ForStatement.hpp>
#include <GMLAST/AST/FunctionCall.hpp>
#include <GMLAST/AST/IfStatement.hpp>
#include <GMLAST/AST/IntConstant.hpp>
#include <GMLAST/AST/RepeatStatement.hpp>
#include <GMLAST/AST/ReturnStatement.hpp>
#include <GMLAST/AST/Statements.hpp>
#include <GMLAST/AST/StringConstant.hpp>
#include <GMLAST/AST/SwitchStatement.hpp>
#include <GMLAST/AST/UnuaryOperator.hpp>
#include <GMLAST/AST/Variable.hpp>
#include <GMLAST/AST/WhileStatement.hpp>
#include <GMLAST/AST/WithStatement.hpp>
#include <GMLAST/Parser/IsLValue.hpp>
#include <GMLAST/Parser/SyntaxChecker.hpp>
#include <GMLAST/Utils/ILogger.hpp>
#include <cassert>

namespace GMLAST {

void SyntaxChecker::visit(const Base& base, ILogger& logger) {
  SyntaxChecker visitor(logger);
  base.visit(visitor);
}

void SyntaxChecker::logNotTopLevel(const Base& base) {
  m_logger.log(ILogger::Level::Error,
               "expression is not a top level expression", base.first(),
               base.last());
}

void SyntaxChecker::logSubLevelAssignment(const Base& base) {
  m_logger.log(
      ILogger::Level::Error,
      "the assignment operator can only be used in an top level expression",
      base.first(), base.last());
}

void SyntaxChecker::visitSubExpression(const Base& base) {
  m_isStatement = false;
  base.visit(*this);
  m_isStatement = true;
}

void SyntaxChecker::onArrayOperator(const ArrayOperator& arrayOperator) {
  if (m_isStatement) logNotTopLevel(arrayOperator);

  visitSubExpression(arrayOperator.array());
  visitSubExpression(arrayOperator.index1());

  if (arrayOperator.hasIndex2()) visitSubExpression(arrayOperator.index2());
}

void SyntaxChecker::onAssignStatement(const AssignStatement& assignStatement) {
  if (!m_isStatement) logSubLevelAssignment(assignStatement);

  if (!IsLValue::visit(assignStatement.left()))
    m_logger.log(ILogger::Level::Error, "expression is not a lvalue",
                 assignStatement.left().first(), assignStatement.left().last());

  visitSubExpression(assignStatement.left());
  visitSubExpression(assignStatement.right());
}

void SyntaxChecker::onBinaryOperator(const BinaryOperator& binaryOperator) {
  if (m_isStatement) logNotTopLevel(binaryOperator);

  visitSubExpression(binaryOperator.left());
  visitSubExpression(binaryOperator.right());
}

void SyntaxChecker::onBreakStatement(const BreakStatement& breakStatement) {
  assert(m_isStatement);
}

void SyntaxChecker::onContinueStatement(
    const ContinueStatement& continueStatement) {
  assert(m_isStatement);
}

void SyntaxChecker::onDeclarationStatement(
    const DeclarationStatement& declarationStatement) {
  assert(m_isStatement);

  for (auto& entry : declarationStatement.entries())
    if (entry.hasExpression()) visitSubExpression(entry.expression());
}

void SyntaxChecker::onDoStatement(const DoStatement& doStatement) {
  assert(m_isStatement);

  visitSubExpression(doStatement.expression());
  doStatement.statement().visit(*this);
}

void SyntaxChecker::onDotOperator(const DotOperator& dotOperator) {
  if (m_isStatement) logNotTopLevel(dotOperator);

  visitSubExpression(dotOperator.expression());
}

void SyntaxChecker::onDoubleConstant(const DoubleConstant& doubleConstant) {
  if (m_isStatement) logNotTopLevel(doubleConstant);
}

void SyntaxChecker::onEnumStatement(const EnumStatement& enumStatement) {
  assert(m_isStatement);

  for (auto& entry : enumStatement.entries())
    if (entry.hasExpression()) visitSubExpression(entry.expression());
}

void SyntaxChecker::onError(const Error& error) {}

void SyntaxChecker::onExitStatement(const ExitStatement& exitStatement) {
  assert(m_isStatement);
}

void SyntaxChecker::onForStatement(const ForStatement& forStatement) {
  assert(m_isStatement);

  forStatement.initStatement().visit(*this);
  visitSubExpression(forStatement.expression());
  forStatement.iterationStatement().visit(*this);
  forStatement.statement().visit(*this);
}

void SyntaxChecker::onFunctionCall(const FunctionCall& functionCall) {
  for (auto& arg : functionCall.arguments()) visitSubExpression(*arg);
}

void SyntaxChecker::onIfStatement(const IfStatement& ifStatement) {
  assert(m_isStatement);

  visitSubExpression(ifStatement.expression());
  ifStatement.statement().visit(*this);

  if (ifStatement.hasElseStatement()) ifStatement.elseStatement().visit(*this);
}

void SyntaxChecker::onIntConstant(const IntConstant& intConstant) {
  if (m_isStatement) logNotTopLevel(intConstant);
}

void SyntaxChecker::onRepeatStatement(const RepeatStatement& repeatStatement) {
  assert(m_isStatement);

  visitSubExpression(repeatStatement.expression());
  repeatStatement.statement().visit(*this);
}

void SyntaxChecker::onReturnStatement(const ReturnStatement& returnStatement) {
  assert(m_isStatement);

  visitSubExpression(returnStatement.expression());
}

void SyntaxChecker::onStatements(const Statements& statements) {
  assert(m_isStatement);

  for (auto& statement : statements.statements()) statement->visit(*this);
}

void SyntaxChecker::onStringConstant(const StringConstant& stringConstant) {
  if (m_isStatement) logNotTopLevel(stringConstant);
}

void SyntaxChecker::onSwitchStatement(const SwitchStatement& switchStatement) {
  assert(m_isStatement);

  visitSubExpression(switchStatement.expression());

  for (auto& entry : switchStatement.switchEntries()) {
    for (auto& switchCase : entry.switchCases())
      if (switchCase.hasValue()) visitSubExpression(switchCase.value());

    for (auto& statement : entry.statements()) statement->visit(*this);
  }
}

void SyntaxChecker::onUnuaryOperator(const UnuaryOperator& unuaryOperator) {
  if (unuaryOperator.type() != UnuaryOperator::Type::PrefixIncrement &&
      unuaryOperator.type() != UnuaryOperator::Type::PrefixDecrement &&
      unuaryOperator.type() != UnuaryOperator::Type::PostfixIncrement &&
      unuaryOperator.type() != UnuaryOperator::Type::PostfixDecrement) {
    if (m_isStatement) logNotTopLevel(unuaryOperator);

    visitSubExpression(unuaryOperator.value());
    return;
  }

  if (!IsLValue::visit(unuaryOperator.value()))
    m_logger.log(ILogger::Level::Error, "expression is not a lvalue",
                 unuaryOperator.value().first(), unuaryOperator.value().last());

  visitSubExpression(unuaryOperator.value());
}

void SyntaxChecker::onVariable(const Variable& variable) {
  if (m_isStatement) logNotTopLevel(variable);
}

void SyntaxChecker::onWhileStatement(const WhileStatement& whileStatement) {
  assert(m_isStatement);

  visitSubExpression(whileStatement.expression());
  whileStatement.statement().visit(*this);
}

void SyntaxChecker::onWithStatement(const WithStatement& withStatement) {
  assert(m_isStatement);

  visitSubExpression(withStatement.expression());
  withStatement.statement().visit(*this);
}

}  // namespace GMLAST

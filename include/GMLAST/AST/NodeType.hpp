#pragma once

namespace GMLAST {

enum class NodeType {
  ArrayOperator,
  AssignStatement,
  BinaryOperator,
  BreakStatement,
  ContinueStatement,
  DeclarationStatement,
  DoStatement,
  DotOperator,
  DoubleConstant,
  EnumStatement,
  Error,
  ExitStatement,
  ForStatement,
  FunctionCall,
  IfStatement,
  IntConstant,
  RepeatStatement,
  ReturnStatement,
  Statements,
  StringConstant,
  SwitchStatement,
  UnuaryOperator,
  Variable,
  WhileStatement,
  WithStatement
};

}  // namespace GMLAST

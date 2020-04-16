#include <GMLAST/AST/ArrayOperator.hpp>
#include <GMLAST/AST/AssignStatement.hpp>
#include <GMLAST/AST/Base.hpp>
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
#include <GMLAST/Lexer/Lexer.hpp>
#include <GMLAST/Parser/Parser.hpp>
#include <JsonSerializer.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace GMLAST {

static void to_json(nlohmann::json& j, ArrayOperator::Type type);
static void to_json(nlohmann::json& j, AssignStatement::Type type);
static void to_json(nlohmann::json& j, BinaryOperator::Type type);
static void to_json(nlohmann::json& j, UnuaryOperator::Type type);

class JsonSerializerVisitor : IVisitor {
 public:
  static nlohmann::json visit(const Base& base) {
    JsonSerializerVisitor visitor;
    base.visit(visitor);
    return std::move(visitor.m_node);
  }

 private:
  JsonSerializerVisitor() = default;

  virtual void onArrayOperator(const ArrayOperator& arrayOperator) override {
    nlohmann::json j;
    j.emplace("type", "ArrayOperator");
    j.emplace("array-type", arrayOperator.type());

    arrayOperator.array().visit(*this);
    j.emplace("array", std::move(m_node));

    arrayOperator.index1().visit(*this);
    j.emplace("index1", std::move(m_node));

    if (arrayOperator.hasIndex2()) {
      arrayOperator.index2().visit(*this);
      j.emplace("index2", std::move(m_node));
    }

    m_node = std::move(j);
  }

  virtual void onAssignStatement(
      const AssignStatement& assignStatement) override {
    nlohmann::json j;
    j.emplace("type", "AssignStatement");
    j.emplace("assign-type", assignStatement.type());

    assignStatement.left().visit(*this);
    j.emplace("left", std::move(m_node));

    assignStatement.right().visit(*this);
    j.emplace("right", std::move(m_node));

    m_node = std::move(j);
  }

  virtual void onBinaryOperator(const BinaryOperator& binaryOperator) override {
    nlohmann::json j;
    j.emplace("type", "BinaryOperator");
    j.emplace("operator-type", binaryOperator.type());

    binaryOperator.left().visit(*this);
    j.emplace("left", std::move(m_node));

    binaryOperator.right().visit(*this);
    j.emplace("right", std::move(m_node));

    m_node = std::move(j);
  }

  virtual void onBreakStatement(const BreakStatement& breakStatement) override {
    nlohmann::json j;
    j.emplace("type", "BreakStatement");
    m_node = std::move(j);
  }

  virtual void onContinueStatement(
      const ContinueStatement& continueStatement) override {
    nlohmann::json j;
    j.emplace("type", "ContinueStatement");
    m_node = std::move(j);
  }

  virtual void onDeclarationStatement(
      const DeclarationStatement& declarationStatement) override {
    nlohmann::json j, jEntries(nlohmann::json::array());
    j.emplace("type", "DeclarationStatement");
    j.emplace("isGlobal", declarationStatement.isGlobal());

    for (auto& entry : declarationStatement.entries()) {
      nlohmann::json jEntry;
      jEntry.emplace("name", entry.name());

      if (entry.hasExpression()) {
        entry.expression().visit(*this);
        jEntry.emplace("expression", std::move(m_node));
      }

      jEntries.emplace_back(std::move(jEntry));
    }

    j.emplace("declarations", jEntries);
    m_node = std::move(j);
  }

  virtual void onDoStatement(const DoStatement& doStatement) override {
    nlohmann::json j;
    j.emplace("type", "DoStatement");

    doStatement.expression().visit(*this);
    j.emplace("expression", std::move(m_node));

    doStatement.statement().visit(*this);
    j.emplace("statement", std::move(m_node));

    m_node = std::move(j);
  }

  virtual void onDotOperator(const DotOperator& dotOperator) override {
    nlohmann::json j;
    j.emplace("type", "DotOperator");
    j.emplace("name", dotOperator.name());

    dotOperator.expression().visit(*this);
    j.emplace("expression", std::move(m_node));

    m_node = std::move(j);
  }

  virtual void onDoubleConstant(const DoubleConstant& doubleConstant) override {
    nlohmann::json j;
    j.emplace("type", "DoubleConstant");
    j.emplace("value", doubleConstant.value());
    m_node = std::move(j);
  }

  virtual void onEnumStatement(const EnumStatement& enumStatement) override {
    nlohmann::json j, jEntries(nlohmann::json::array());
    j.emplace("type", "EnumStatement");
    j.emplace("name", enumStatement.name());

    for (auto& entry : enumStatement.entries()) {
      nlohmann::json jEntry;
      jEntry.emplace("name", entry.name());

      if (entry.hasExpression()) {
        entry.expression().visit(*this);
        jEntry.emplace("expression", std::move(m_node));
      }

      jEntries.emplace_back(std::move(jEntry));
    }

    j.emplace("entries", std::move(jEntries));
    m_node = std::move(j);
  }

  virtual void onError(const Error& error) override { assert(true); }

  virtual void onExitStatement(const ExitStatement& exitStatement) override {
    nlohmann::json j;
    j.emplace("type", "ExitStatement");
    m_node = std::move(j);
  }

  virtual void onForStatement(const ForStatement& forStatement) override {
    nlohmann::json j;
    j.emplace("type", "ForStatement");

    forStatement.initStatement().visit(*this);
    j.emplace("init-statement", std::move(m_node));

    forStatement.expression().visit(*this);
    j.emplace("expression", std::move(m_node));

    forStatement.iterationStatement().visit(*this);
    j.emplace("iteration-statement", std::move(m_node));

    forStatement.statement().visit(*this);
    j.emplace("statement", std::move(m_node));

    m_node = std::move(j);
  }

  virtual void onFunctionCall(const FunctionCall& functionCall) override {
    nlohmann::json j, jArguments(nlohmann::json::array());
    j.emplace("type", "FunctionCall");
    j.emplace("name", functionCall.name());

    for (auto& arg : functionCall.arguments()) {
      arg->visit(*this);
      jArguments.emplace_back(std::move(m_node));
    }

    j.emplace("arguments", std::move(jArguments));
    m_node = std::move(j);
  }

  virtual void onIfStatement(const IfStatement& ifStatement) override {
    nlohmann::json j, jArguments(nlohmann::json::array());
    j.emplace("type", "IfStatement");

    ifStatement.expression().visit(*this);
    j.emplace("expression", std::move(m_node));

    ifStatement.statement().visit(*this);
    j.emplace("statement", std::move(m_node));

    if (ifStatement.hasElseStatement()) {
      ifStatement.elseStatement().visit(*this);
      j.emplace("else-statement", std::move(m_node));
    }

    m_node = std::move(j);
  }

  virtual void onIntConstant(const IntConstant& intConstant) override {
    nlohmann::json j;
    j.emplace("type", "IntConstant");
    j.emplace("value", intConstant.value());
    m_node = std::move(j);
  }

  virtual void onRepeatStatement(
      const RepeatStatement& repeatStatement) override {
    nlohmann::json j;
    j.emplace("type", "RepeatStatement");

    repeatStatement.expression().visit(*this);
    j.emplace("expression", std::move(m_node));

    repeatStatement.statement().visit(*this);
    j.emplace("statement", std::move(m_node));

    m_node = std::move(j);
  }

  virtual void onReturnStatement(
      const ReturnStatement& returnStatement) override {
    nlohmann::json j;
    j.emplace("type", "ReturnStatement");

    returnStatement.expression().visit(*this);
    j.emplace("expression", std::move(m_node));

    m_node = std::move(j);
  }

  virtual void onStatements(const Statements& statements) override {
    nlohmann::json j, jStatements(nlohmann::json::array());
    j.emplace("type", "Statements");

    for (auto& statement : statements.statements()) {
      statement->visit(*this);
      jStatements.emplace_back(std::move(m_node));
    }

    j.emplace("statements", std::move(jStatements));
    m_node = std::move(j);
  }

  virtual void onStringConstant(const StringConstant& stringConstant) override {
    nlohmann::json j;
    j.emplace("type", "StringConstant");
    j.emplace("value", stringConstant.value());
    m_node = std::move(j);
  }

  virtual void onSwitchStatement(
      const SwitchStatement& switchStatement) override {
    nlohmann::json j;
    j.emplace("type", "SwitchStatement");

    switchStatement.expression().visit(*this);
    j.emplace("expression", std::move(m_node));

    auto jEntries(nlohmann::json::array());

    for (auto& entry : switchStatement.switchEntries()) {
      auto jSwitchCases(nlohmann::json::array());

      for (auto& switchCase : entry.switchCases()) {
        if (switchCase.hasValue()) {
          switchCase.value().visit(*this);
          jSwitchCases.emplace_back(std::move(m_node));
        } else
          jSwitchCases.emplace_back();
      }

      auto jStatements(nlohmann::json::array());

      for (auto& statement : entry.statements()) {
        statement->visit(*this);
        jStatements.emplace_back(std::move(m_node));
      }

      nlohmann::json jEntry;
      jEntry.emplace("switch-cases", std::move(jSwitchCases));
      jEntry.emplace("statements", std::move(jStatements));
      jEntries.emplace_back(std::move(jEntry));
    }

    j.emplace("entries", std::move(jEntries));
    m_node = std::move(j);
  }

  virtual void onUnuaryOperator(const UnuaryOperator& unuaryOperator) override {
    nlohmann::json j;
    j.emplace("type", "UnuaryOperator");
    j.emplace("operator-type", unuaryOperator.type());

    unuaryOperator.value().visit(*this);
    j.emplace("value", std::move(m_node));

    m_node = std::move(j);
  }

  virtual void onVariable(const Variable& variable) override {
    nlohmann::json j;
    j.emplace("type", "Variable");
    j.emplace("name", variable.name());
    m_node = std::move(j);
  }

  virtual void onWhileStatement(const WhileStatement& whileStatement) override {
    nlohmann::json j;
    j.emplace("type", "WhileStatement");

    whileStatement.expression().visit(*this);
    j.emplace("expression", std::move(m_node));

    whileStatement.statement().visit(*this);
    j.emplace("statement", std::move(m_node));

    m_node = std::move(j);
  }

  virtual void onWithStatement(const WithStatement& withStatement) override {
    nlohmann::json j;
    j.emplace("type", "WithStatement");

    withStatement.expression().visit(*this);
    j.emplace("expression", std::move(m_node));

    withStatement.statement().visit(*this);
    j.emplace("statement", std::move(m_node));

    m_node = std::move(j);
  }

  nlohmann::json m_node;
};

void to_json(nlohmann::json& j, const Base& base) {
  j = JsonSerializerVisitor::visit(base);
}

void to_json(nlohmann::json& j, ArrayOperator::Type type) {
  using Type = ArrayOperator::Type;

  switch (type) {
    case Type::Array:
      j = "Array";
      break;
    case Type::Grid:
      j = "Grid";
      break;
    case Type::List:
      j = "List";
      break;
    case Type::Map:
      j = "Map";
      break;
    case Type::Reference:
      j = "Reference";
      break;
    default:
      assert(false);
  }
}

void to_json(nlohmann::json& j, AssignStatement::Type type) {
  using Type = AssignStatement::Type;

  switch (type) {
    case Type::Assign:
      j = "Assign";
      break;
    case Type::Add:
      j = "Add";
      break;
    case Type::BitAnd:
      j = "BitAnd";
      break;
    case Type::BitOr:
      j = "BitOr";
      break;
    case Type::BitXor:
      j = "BitXor";
      break;
    case Type::Div:
      j = "Div";
      break;
    case Type::Mod:
      j = "Mod";
      break;
    case Type::Mul:
      j = "Mul";
      break;
    case Type::Sub:
      j = "Sub";
      break;
    default:
      assert(false);
  }
}

void to_json(nlohmann::json& j, BinaryOperator::Type type) {
  using Type = BinaryOperator::Type;

  switch (type) {
    case Type::Add:
      j = "Add";
      break;
    case Type::BitwiseAnd:
      j = "BitwiseAnd";
      break;
    case Type::BitwiseLeft:
      j = "BitwiseLeft";
      break;
    case Type::BitwiseOr:
      j = "BitwiseOr";
      break;
    case Type::BitwiseRight:
      j = "BitwiseRight";
      break;
    case Type::BitwiseXor:
      j = "BitwiseXor";
      break;
    case Type::CompareEqual:
      j = "CompareEqual";
      break;
    case Type::CompareGreater:
      j = "CompareGreater";
      break;
    case Type::CompareGreaterEqual:
      j = "CompareGreaterEqual";
      break;
    case Type::CompareLess:
      j = "CompareLess";
      break;
    case Type::CompareLessEqual:
      j = "CompareLessEqual";
      break;
    case Type::CompareNotEqual:
      j = "CompareNotEqual";
      break;
    case Type::Divide:
      j = "Divide";
      break;
    case Type::IntDivide:
      j = "IntDivide";
      break;
    case Type::LogicalAnd:
      j = "LogicalAnd";
      break;
    case Type::LogicalOr:
      j = "LogicalOr";
      break;
    case Type::LogicalXor:
      j = "LogicalXor";
      break;
    case Type::Modulo:
      j = "Modulo";
      break;
    case Type::Multiply:
      j = "Multiply";
      break;
    case Type::Subtract:
      j = "Subtract";
      break;
    default:
      assert(false);
  }
}

void to_json(nlohmann::json& j, UnuaryOperator::Type type) {
  using Type = UnuaryOperator::Type;

  switch (type) {
    case Type::BitwiseNot:
      j = "BitwiseNot";
      break;
    case Type::LogicalNot:
      j = "LogicalNot";
      break;
    case Type::PostfixDecrement:
      j = "PostfixDecrement";
      break;
    case Type::PostfixIncrement:
      j = "PostfixIncrement";
      break;
    case Type::PrefixDecrement:
      j = "PrefixDecrement";
      break;
    case Type::PrefixIncrement:
      j = "PrefixIncrement";
      break;
    case Type::Minus:
      j = "Minus";
      break;
    case Type::Plus:
      j = "Plus";
      break;
    default:
      assert(false);
  }
}
}  // namespace GMLAST
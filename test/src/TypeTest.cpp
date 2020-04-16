#include <GMLAST/AST/ArrayOperator.hpp>
#include <GMLAST/AST/AssignStatement.hpp>
#include <GMLAST/AST/BinaryOperator.hpp>
#include <GMLAST/AST/BreakStatement.hpp>
#include <GMLAST/AST/ContinueStatement.hpp>
#include <GMLAST/AST/DeclarationStatement.hpp>
#include <GMLAST/AST/DoStatement.hpp>
#include <GMLAST/AST/DotOperator.hpp>
#include <GMLAST/AST/DoubleConstant.hpp>
#include <GMLAST/AST/EnumStatement.hpp>
#include <GMLAST/AST/Error.hpp>
#include <GMLAST/AST/ExitStatement.hpp>
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
#include <catch.hpp>
#include <memory>

template <typename T, typename... Args>
std::unique_ptr<T> MakeUnique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

TEST_CASE("Array Operator", "[TypeTest]") {
  const auto node1 = MakeUnique<GMLAST::ArrayOperator>(
      GMLAST::ArrayOperator::Type::Array, MakeUnique<GMLAST::Error>(),
      MakeUnique<GMLAST::Error>());

  CHECK(node1->nodeType() == GMLAST::NodeType::ArrayOperator);

  const auto node2 = MakeUnique<GMLAST::ArrayOperator>(
      GMLAST::ArrayOperator::Type::Array, MakeUnique<GMLAST::Error>(),
      MakeUnique<GMLAST::Error>(), MakeUnique<GMLAST::Error>());

  CHECK(node2->nodeType() == GMLAST::NodeType::ArrayOperator);
}

TEST_CASE("Assign Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::AssignStatement>(
      GMLAST::AssignStatement::Type::Assign, MakeUnique<GMLAST::Error>(),
      MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::AssignStatement);
}

TEST_CASE("Binary Operator", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::BinaryOperator>(
      GMLAST::BinaryOperator::Type::Add, MakeUnique<GMLAST::Error>(),
      MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::BinaryOperator);
}

TEST_CASE("Break Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::BreakStatement>();

  CHECK(node->nodeType() == GMLAST::NodeType::BreakStatement);
}

TEST_CASE("Continue Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::ContinueStatement>();

  CHECK(node->nodeType() == GMLAST::NodeType::ContinueStatement);
}

TEST_CASE("Declaration Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::DeclarationStatement>(
      false, std::vector<GMLAST::DeclarationEntry>{});

  CHECK(node->nodeType() == GMLAST::NodeType::DeclarationStatement);
}

TEST_CASE("Do Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::DoStatement>(
      MakeUnique<GMLAST::Error>(), MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::DoStatement);
}

TEST_CASE("Dot Operator", "[TypeTest]") {
  const auto node =
      MakeUnique<GMLAST::DotOperator>("", MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::DotOperator);
}

TEST_CASE("Double Constant", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::DoubleConstant>(0);

  CHECK(node->nodeType() == GMLAST::NodeType::DoubleConstant);
}

TEST_CASE("Enum Statement", "[TypeTest]") {
  const auto node =
      MakeUnique<GMLAST::EnumStatement>("", std::vector<GMLAST::EnumEntry>{});

  CHECK(node->nodeType() == GMLAST::NodeType::EnumStatement);
}

TEST_CASE("Error", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::Error>();

  CHECK(node->nodeType() == GMLAST::NodeType::Error);
}

TEST_CASE("Exit Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::ExitStatement>();

  CHECK(node->nodeType() == GMLAST::NodeType::ExitStatement);
}

TEST_CASE("For Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::ForStatement>(
      MakeUnique<GMLAST::Error>(), MakeUnique<GMLAST::Error>(),
      MakeUnique<GMLAST::Error>(), MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::ForStatement);
}

TEST_CASE("Function Call", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::FunctionCall>(
      "", std::vector<std::unique_ptr<GMLAST::Value>>{});

  CHECK(node->nodeType() == GMLAST::NodeType::FunctionCall);
}

TEST_CASE("If Statement", "[TypeTest]") {
  const auto node1 = MakeUnique<GMLAST::IfStatement>(
      MakeUnique<GMLAST::Error>(), MakeUnique<GMLAST::Error>());

  CHECK(node1->nodeType() == GMLAST::NodeType::IfStatement);

  const auto node2 = MakeUnique<GMLAST::IfStatement>(
      MakeUnique<GMLAST::Error>(), MakeUnique<GMLAST::Error>(),
      MakeUnique<GMLAST::Error>());

  CHECK(node2->nodeType() == GMLAST::NodeType::IfStatement);
}

TEST_CASE("Int Constant", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::IntConstant>(0);

  CHECK(node->nodeType() == GMLAST::NodeType::IntConstant);
}

TEST_CASE("Repeat Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::RepeatStatement>(
      MakeUnique<GMLAST::Error>(), MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::RepeatStatement);
}

TEST_CASE("Return Statement", "[TypeTest]") {
  const auto node =
      MakeUnique<GMLAST::ReturnStatement>(MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::ReturnStatement);
}

TEST_CASE("Statements", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::Statements>(
      std::vector<std::unique_ptr<GMLAST::Statement>>{});

  CHECK(node->nodeType() == GMLAST::NodeType::Statements);
}

TEST_CASE("String Constant", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::StringConstant>("");

  CHECK(node->nodeType() == GMLAST::NodeType::StringConstant);
}

TEST_CASE("Switch Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::SwitchStatement>(
      MakeUnique<GMLAST::Error>(), std::vector<GMLAST::SwitchEntry>{});

  CHECK(node->nodeType() == GMLAST::NodeType::SwitchStatement);
}

TEST_CASE("Unuary Operator", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::UnuaryOperator>(
      GMLAST::UnuaryOperator::Type::Plus, MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::UnuaryOperator);
}

TEST_CASE("Variable", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::Variable>("");

  CHECK(node->nodeType() == GMLAST::NodeType::Variable);
}

TEST_CASE("While Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::WhileStatement>(
      MakeUnique<GMLAST::Error>(), MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::WhileStatement);
}

TEST_CASE("With Statement", "[TypeTest]") {
  const auto node = MakeUnique<GMLAST::WithStatement>(
      MakeUnique<GMLAST::Error>(), MakeUnique<GMLAST::Error>());

  CHECK(node->nodeType() == GMLAST::NodeType::WithStatement);
}

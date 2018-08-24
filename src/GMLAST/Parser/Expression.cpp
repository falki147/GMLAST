#include <GMLAST/AST/ArrayOperator.hpp>
#include <GMLAST/AST/AssignStatement.hpp>
#include <GMLAST/AST/BinaryOperator.hpp>
#include <GMLAST/AST/DotOperator.hpp>
#include <GMLAST/AST/DoubleConstant.hpp>
#include <GMLAST/AST/FunctionCall.hpp>
#include <GMLAST/AST/IntConstant.hpp>
#include <GMLAST/AST/StringConstant.hpp>
#include <GMLAST/AST/UnuaryOperator.hpp>
#include <GMLAST/AST/Variable.hpp>
#include <GMLAST/Parser/DefaultParser.hpp>
#include <GMLAST/Utils/ILogger.hpp>
#include <GMLAST/Utils/UniquePtrHelper.hpp>

namespace GMLAST {

std::unique_ptr<Value> DefaultParser::tryParseExpression(
    bool equalIsAssignment) {
  return tryParseAssignment(equalIsAssignment);
}

std::unique_ptr<Value> DefaultParser::tryParseAssignment(
    bool equalIsAssignment) {
  const auto first = firstLocation();
  auto value = tryParseLogical(equalIsAssignment);
  if (!value) return {};

  AssignStatement::Type type;

  switch (peek().type()) {
    case Token::Type::Assign:
      type = AssignStatement::Type::Assign;
      break;
    case Token::Type::AssignAdd:
      type = AssignStatement::Type::Add;
      break;
    case Token::Type::AssignBitAnd:
      type = AssignStatement::Type::BitAnd;
      break;
    case Token::Type::AssignBitOr:
      type = AssignStatement::Type::BitOr;
      break;
    case Token::Type::AssignBitXor:
      type = AssignStatement::Type::BitXor;
      break;
    case Token::Type::AssignDiv:
      type = AssignStatement::Type::Div;
      break;
    case Token::Type::AssignMod:
      type = AssignStatement::Type::Mod;
      break;
    case Token::Type::AssignMul:
      type = AssignStatement::Type::Mul;
      break;
    case Token::Type::AssignSub:
      type = AssignStatement::Type::Sub;
      break;
    case Token::Type::Equal:
      // ParseComparison always takes the equal first if it can, so we don't
      // need to add any additional logic
      type = AssignStatement::Type::Assign;
      break;
    default:
      return value;
  }

  consume();
  auto right = checkValue(tryParseAssignment(false));

  const auto last = lastLocation();
  return MakeUnique<AssignStatement>(type, std::move(value), std::move(right),
                                     first, last);
}

std::unique_ptr<Value> DefaultParser::tryParseLogical(bool equalIsAssignment) {
  const auto first = firstLocation();
  auto value = tryParseComparison(equalIsAssignment);
  if (!value) return {};

  for (;;) {
    BinaryOperator::Type type;

    switch (peek().type()) {
      case Token::Type::LogicalAnd:
        type = BinaryOperator::Type::LogicalAnd;
        break;
      case Token::Type::LogicalOr:
        type = BinaryOperator::Type::LogicalOr;
        break;
      case Token::Type::LogicalXor:
        type = BinaryOperator::Type::LogicalXor;
        break;
      default:
        return value;
    }

    consume();
    auto right = checkValue(tryParseComparison(false));

    const auto last = lastLocation();
    value = MakeUnique<BinaryOperator>(type, std::move(value), std::move(right),
                                       first, last);
  }
}

std::unique_ptr<Value> DefaultParser::tryParseComparison(
    bool equalIsAssignment) {
  const auto first = firstLocation();
  auto value = tryParseBitwise();
  if (!value) return {};

  for (;;) {
    BinaryOperator::Type type;

    switch (peek().type()) {
      case Token::Type::CmpEqual:
        type = BinaryOperator::Type::CompareEqual;
        break;
      case Token::Type::CmpGreater:
        type = BinaryOperator::Type::CompareGreater;
        break;
      case Token::Type::CmpGreaterEqual:
        type = BinaryOperator::Type::CompareGreaterEqual;
        break;
      case Token::Type::CmpLess:
        type = BinaryOperator::Type::CompareLess;
        break;
      case Token::Type::CmpLessEqual:
        type = BinaryOperator::Type::CompareLessEqual;
        break;
      case Token::Type::CmpNotEqual:
        type = BinaryOperator::Type::CompareNotEqual;
        break;
      case Token::Type::Equal:
        if (!equalIsAssignment) {
          type = BinaryOperator::Type::CompareEqual;
          logger().log(ILogger::Level::Warning,
                       "'=' shouldn't be used for comparison", peek().first(),
                       peek().last());
          break;
        }

        return value;
      default:
        return value;
    }

    consume();
    auto right = checkValue(tryParseBitwise());

    const auto last = lastLocation();
    value = MakeUnique<BinaryOperator>(type, std::move(value), std::move(right),
                                       first, last);
  }
}

std::unique_ptr<Value> DefaultParser::tryParseBitwise() {
  const auto first = firstLocation();
  auto value = tryParseAdditive();
  if (!value) return {};

  for (;;) {
    BinaryOperator::Type type;

    switch (peek().type()) {
      case Token::Type::BitwiseAnd:
        type = BinaryOperator::Type::BitwiseAnd;
        break;
      case Token::Type::BitwiseLeft:
        type = BinaryOperator::Type::BitwiseLeft;
        break;
      case Token::Type::BitwiseOr:
        type = BinaryOperator::Type::BitwiseOr;
        break;
      case Token::Type::BitwiseRight:
        type = BinaryOperator::Type::BitwiseRight;
        break;
      case Token::Type::BitwiseXor:
        type = BinaryOperator::Type::BitwiseXor;
        break;
      default:
        return value;
    }

    consume();
    auto right = checkValue(tryParseAdditive());

    const auto last = lastLocation();
    value = MakeUnique<BinaryOperator>(type, std::move(value), std::move(right),
                                       first, last);
  }
}

std::unique_ptr<Value> DefaultParser::tryParseAdditive() {
  const auto first = firstLocation();
  auto value = tryParseMultiplicative();
  if (!value) return {};

  for (;;) {
    BinaryOperator::Type type;

    switch (peek().type()) {
      case Token::Type::Plus:
        type = BinaryOperator::Type::Add;
        break;
      case Token::Type::Minus:
        type = BinaryOperator::Type::Subtract;
        break;
      default:
        return value;
    }

    consume();
    auto right = checkValue(tryParseMultiplicative());

    const auto last = lastLocation();
    value = MakeUnique<BinaryOperator>(type, std::move(value), std::move(right),
                                       first, last);
  }
}

std::unique_ptr<Value> DefaultParser::tryParseMultiplicative() {
  const auto first = firstLocation();
  auto value = tryParsePrefix();
  if (!value) return {};

  for (;;) {
    BinaryOperator::Type type;

    switch (peek().type()) {
      case Token::Type::Multiply:
        type = BinaryOperator::Type::Multiply;
        break;
      case Token::Type::Divide:
        type = BinaryOperator::Type::Divide;
        break;
      case Token::Type::Modulo:
        type = BinaryOperator::Type::Modulo;
        break;
      case Token::Type::IntDivide:
        type = BinaryOperator::Type::IntDivide;
        break;
      default:
        return value;
    }

    consume();
    auto right = checkValue(tryParsePrefix());

    const auto last = lastLocation();
    value = MakeUnique<BinaryOperator>(type, std::move(value), std::move(right),
                                       first, last);
  }
}

std::unique_ptr<Value> DefaultParser::tryParsePrefix() {
  const auto first = firstLocation();
  UnuaryOperator::Type type;

  switch (peek().type()) {
    case Token::Type::Increment:
      type = UnuaryOperator::Type::PrefixIncrement;
      break;
    case Token::Type::Decrement:
      type = UnuaryOperator::Type::PrefixDecrement;
      break;
    case Token::Type::Plus:
      type = UnuaryOperator::Type::Plus;
      break;
    case Token::Type::Minus:
      type = UnuaryOperator::Type::Minus;
      break;
    case Token::Type::BitwiseNot:
      type = UnuaryOperator::Type::BitwiseNot;
      break;
    case Token::Type::LogicalNot:
      type = UnuaryOperator::Type::LogicalNot;
      break;
    default:
      return tryParsePostfix();
  }

  consume();
  auto value = checkValue(tryParsePrefix());

  const auto last = lastLocation();
  return MakeUnique<UnuaryOperator>(type, std::move(value), first, last);
}

std::unique_ptr<Value> DefaultParser::tryParsePostfix() {
  const auto first = firstLocation();
  auto value = tryParseValue();
  if (!value) return {};

  for (;;) {
    const auto type = peek().type();

    if (type == Token::Type::Increment || type == Token::Type::Decrement) {
      consume();

      const auto unuaryOpType = type == Token::Type::Increment
                                    ? UnuaryOperator::Type::PostfixIncrement
                                    : UnuaryOperator::Type::PostfixDecrement;

      const auto last = lastLocation();
      value = MakeUnique<UnuaryOperator>(unuaryOpType, std::move(value), first,
                                         last);
    } else if (type == Token::Type::Dot) {
      consume();

      if (!continueIf(Token::Type::Identifier)) return value;

      auto identifier = read().getString();

      const auto last = lastLocation();
      value = MakeUnique<DotOperator>(std::move(identifier), std::move(value),
                                      first, last);
    } else if (type == Token::Type::ArrayOpen ||
               type == Token::Type::ArrayOpenGrid ||
               type == Token::Type::ArrayOpenList ||
               type == Token::Type::ArrayOpenMap ||
               type == Token::Type::ArrayOpenRef) {
      ArrayOperator::Type type;

      switch (peek().type()) {
        case Token::Type::ArrayOpenGrid:
          type = ArrayOperator::Type::Grid;
          break;
        case Token::Type::ArrayOpenList:
          type = ArrayOperator::Type::List;
          break;
        case Token::Type::ArrayOpenMap:
          type = ArrayOperator::Type::Map;
          break;
        case Token::Type::ArrayOpenRef:
          type = ArrayOperator::Type::Reference;
          break;
        default:
          type = ArrayOperator::Type::Array;
          break;
      }

      consume();

      auto index1 = checkValue(tryParseExpression());

      if (type == ArrayOperator::Type::Grid) {
        consumeIf(Token::Type::Comma);
        auto index2 = checkValue(tryParseExpression());
        consumeIf(Token::Type::ArrayClose);

        const auto last = lastLocation();
        return MakeUnique<ArrayOperator>(type, std::move(value),
                                         std::move(index1), std::move(index2),
                                         first, last);

      } else if (type == ArrayOperator::Type::Array ||
                 type == ArrayOperator::Type::Reference) {
        std::unique_ptr<Value> arrayValue;

        if (peek().is(Token::Type::Comma)) {
          consume();
          auto index2 = checkValue(tryParseExpression());

          const auto last = lastLocation();
          arrayValue = MakeUnique<ArrayOperator>(
              type, std::move(value), std::move(index1), std::move(index2),
              first, last);
        } else {
          const auto last = lastLocation();
          arrayValue = MakeUnique<ArrayOperator>(
              type, std::move(value), std::move(index1), first, last);
        }

        consumeIf(Token::Type::ArrayClose);
        return arrayValue;
      } else {
        consumeIf(Token::Type::ArrayClose);

        const auto last = lastLocation();
        return MakeUnique<ArrayOperator>(type, std::move(value),
                                         std::move(index1), first, last);
      }
    } else
      return value;
  }
}

std::unique_ptr<Value> DefaultParser::tryParseValue() {
  const auto type = peek().type();

  if (type == Token::Type::ParenOpen) {
    consume();
    auto ret = checkValue(tryParseExpression());
    consumeIf(Token::Type::ParenClose);
    return ret;
  } else if (type == Token::Type::Identifier) {
    const auto first = firstLocation();
    auto token = read();

    if (peek().is(Token::Type::ParenOpen)) {
      consume();

      std::vector<std::unique_ptr<Value>> args;

      if (!peek().is(Token::Type::ParenClose)) {
        for (;;) {
          args.emplace_back(checkValue(tryParseExpression()));

          if (peek().is(Token::Type::ParenClose)) {
            consume();
            break;
          }

          if (peek().is(Token::Type::Comma)) {
            consume();
            continue;
          }

          errorUnexpected(peek());
          break;
        }
      } else
        consume();

      const auto last = lastLocation();
      return MakeUnique<FunctionCall>(token.getString(), std::move(args), first,
                                      last);
    } else {
      const auto last = lastLocation();
      return MakeUnique<Variable>(token.getString(), first, last);
    }
  } else if (type == Token::Type::ConstInt) {
    const auto token = read();
    return MakeUnique<IntConstant>(token.getInteger(), token.first(),
                                   token.last());
  } else if (type == Token::Type::ConstDouble) {
    const auto token = read();
    return MakeUnique<DoubleConstant>(token.getDouble(), token.first(),
                                      token.last());
  } else if (type == Token::Type::ConstString) {
    const auto token = read();
    return MakeUnique<StringConstant>(token.getString(), token.first(),
                                      token.last());
  }

  return {};
}

}  // namespace GMLAST

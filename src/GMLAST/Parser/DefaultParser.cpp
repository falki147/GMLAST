#include <GMLAST/AST/BreakStatement.hpp>
#include <GMLAST/AST/ContinueStatement.hpp>
#include <GMLAST/AST/DeclarationStatement.hpp>
#include <GMLAST/AST/DoStatement.hpp>
#include <GMLAST/AST/EnumStatement.hpp>
#include <GMLAST/AST/Error.hpp>
#include <GMLAST/AST/ExitStatement.hpp>
#include <GMLAST/AST/ForStatement.hpp>
#include <GMLAST/AST/IfStatement.hpp>
#include <GMLAST/AST/RepeatStatement.hpp>
#include <GMLAST/AST/ReturnStatement.hpp>
#include <GMLAST/AST/Statement.hpp>
#include <GMLAST/AST/Statements.hpp>
#include <GMLAST/AST/SwitchStatement.hpp>
#include <GMLAST/AST/WhileStatement.hpp>
#include <GMLAST/AST/WithStatement.hpp>
#include <GMLAST/Lexer/ILexer.hpp>
#include <GMLAST/Parser/DefaultParser.hpp>
#include <GMLAST/Parser/Parser.hpp>
#include <GMLAST/Parser/SyntaxChecker.hpp>
#include <GMLAST/Utils/ILogger.hpp>
#include <GMLAST/Utils/MemoryHelper.hpp>
#include <cassert>
#include <sstream>

namespace GMLAST {

std::unique_ptr<Base> DefaultParser::parse(std::unique_ptr<ILexer> lexer,
                                           std::shared_ptr<ILogger> logger) {
  DefaultParser parser(std::move(lexer), std::move(logger));

  const auto first = parser.firstLocation();
  std::vector<std::unique_ptr<Statement>> statements;

  for (;;) {
    auto statement = parser.tryParseStatement();

    if (!statement) {
      if (!parser.peek()) break;

      parser.errorExpected(parser.peek(), "statement");
      parser.consume();
    } else {
      parser.skipSemicolons();
      statements.emplace_back(std::move(statement));
    }
  }

  const auto last = parser.lastLocation();
  auto ast = MakeUnique<Statements>(std::move(statements), first, last);
  SyntaxChecker::visit(*ast, *parser.m_logger);

  return ast;
}

std::unique_ptr<Base> DefaultParser::parseExpression(
    std::unique_ptr<ILexer> lexer, std::shared_ptr<ILogger> logger) {
  DefaultParser parser(std::move(lexer), std::move(logger));

  for (;;) {
    auto expression = parser.tryParseExpression(true);

    if (!expression) {
      parser.errorExpected(parser.peek(), "expression");

      if (parser.peek()) {
        parser.consume();
        // Retry expression parsing
        continue;
      }

      return MakeUnique<Error>();
    } else {
      if (parser.peek()) {
        parser.errorUnexpected(parser.peek());
      }

      SyntaxChecker::visitExpression(*expression, *parser.m_logger);
      return expression;
    }
  }
}

DefaultParser::DefaultParser(std::unique_ptr<ILexer> lexer,
                             std::shared_ptr<ILogger> logger)
    : m_lexer(std::move(lexer)), m_logger(std::move(logger)) {
  assert(m_lexer);

  if (!m_logger) {
    m_logger = m_lexer->logger();
    assert(m_logger);
  }

  m_token = m_lexer->lex();
  m_last = m_token.first();
}

void DefaultParser::errorExpected(const Token& token, Token::Type expectation) {
  errorExpected(token, expectation == Token::Type::Invalid
                           ? "EOF"
                           : ToString(expectation));
}

void DefaultParser::errorExpected(const Token& token,
                                  const std::string& expectation) {
  std::stringstream ss;
  ss << "expected " << expectation << " but got ";

  if (token)
    ss << ToString(token.type());
  else
    ss << "EOF";

  m_logger->log(ILogger::Level::Error, ss.str(), token.first(), token.last());
}

void DefaultParser::errorUnexpected(const Token& token) {
  std::stringstream ss;
  ss << "unexpected ";

  if (token)
    ss << ToString(token.type());
  else
    ss << "EOF";

  m_logger->log(ILogger::Level::Error, ss.str(), token.first(), token.last());
}

void DefaultParser::consume() {
  m_last = m_token.last();
  m_token = m_lexer->lex();
}

bool DefaultParser::consumeIf(Token::Type expectation) {
  if (!continueIf(expectation)) return false;
  consume();
  return true;
}

bool DefaultParser::continueIf(Token::Type expectation) {
  if (!peek().is(expectation)) {
    errorExpected(peek(), expectation);
    return false;
  }

  return true;
}

std::unique_ptr<Value> DefaultParser::checkValue(std::unique_ptr<Value> value) {
  if (!value) {
    errorUnexpected(peek());
    return MakeUnique<Error>();
  }

  return value;
}

void DefaultParser::skipSemicolons() {
  while (peek().is(Token::Type::Semicolon)) consume();
}

std::unique_ptr<Statement> DefaultParser::parseBlock() {
  const auto first = firstLocation();
  consumeIf(Token::Type::BraceOpen);

  std::vector<std::unique_ptr<Statement>> statements;

  for (;;) {
    auto statement = tryParseStatement();

    if (!statement) {
      if (!peek() || peek().is(Token::Type::BraceClose)) break;

      errorExpected(peek(), "statement");
      consume();
    } else {
      skipSemicolons();
      statements.emplace_back(std::move(statement));
    }
  }

  consumeIf(Token::Type::BraceClose);

  const auto last = lastLocation();
  return MakeUnique<Statements>(std::move(statements), first, last);
}

std::unique_ptr<Statement> DefaultParser::parseGlobalVar() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Globalvar);

  std::vector<DeclarationEntry> entries;

  if (peek().is(Token::Type::Identifier)) {
    for (;;) {
      entries.emplace_back(read().getString());

      if (!peek().is(Token::Type::Comma)) break;
      consume();

      if (!continueIf(Token::Type::Identifier)) break;
    }
  }

  const auto last = lastLocation();
  return MakeUnique<DeclarationStatement>(true, std::move(entries), first,
                                          last);
}

std::unique_ptr<Statement> DefaultParser::parseStatement() {
  auto value = tryParseStatement();

  if (!value) {
    errorExpected(peek(), "statement");
    return MakeUnique<Error>();
  }

  return value;
}

std::unique_ptr<Statement> DefaultParser::tryParseStatement() {
  switch (peek().type()) {
    case Token::Type::BraceOpen:
      return parseBlock();
    case Token::Type::Var:
      return parseVar();
    case Token::Type::Globalvar:
      return parseGlobalVar();
    case Token::Type::If:
      return parseIfStatement();
    case Token::Type::Repeat:
      return parseRepeatStatement();
    case Token::Type::While:
      return parseWhileStatement();
    case Token::Type::Do:
      return parseDoStatement();
    case Token::Type::For:
      return parseForStatement();
    case Token::Type::Switch:
      return parseSwitchStatement();
    case Token::Type::With:
      return parseWithStatement();
    case Token::Type::Return:
      return parseReturnStatement();
    case Token::Type::Exit:
      return parseExitStatement();
    case Token::Type::Break:
      return parseBreakStatement();
    case Token::Type::Continue:
      return parseContinueStatement();
    case Token::Type::Enum:
      return parseEnumStatement();
    default:
      return tryParseExpression(true);
  }
}

std::unique_ptr<Statement> DefaultParser::parseVar() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Var);

  std::vector<DeclarationEntry> entries;

  if (peek().is(Token::Type::Identifier)) {
    for (;;) {
      auto name = read().getString();

      if (peek().is(Token::Type::Equal)) {
        consume();
        entries.emplace_back(name, checkValue(tryParseExpression()));
      } else
        entries.emplace_back(name);

      if (!peek().is(Token::Type::Comma)) break;
      consume();

      if (!continueIf(Token::Type::Identifier)) break;
    }
  }

  const auto last = lastLocation();
  return MakeUnique<DeclarationStatement>(false, std::move(entries), first,
                                          last);
}

std::unique_ptr<Statement> DefaultParser::parseIfStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::If);

  auto expression = checkValue(tryParseExpression());

  if (peek().is(Token::Type::Then)) consume();

  auto statement = parseStatement();
  skipSemicolons();

  if (peek().is(Token::Type::Else)) {
    consume();

    auto elseStatement = parseStatement();
    skipSemicolons();

    const auto last = lastLocation();
    return MakeUnique<IfStatement>(std::move(expression), std::move(statement),
                                   std::move(elseStatement), first, last);
  }

  const auto last = lastLocation();
  return MakeUnique<IfStatement>(std::move(expression), std::move(statement),
                                 first, last);
}

std::unique_ptr<Statement> DefaultParser::parseRepeatStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Repeat);

  auto expression = checkValue(tryParseExpression());
  auto statement = parseStatement();
  skipSemicolons();

  const auto last = lastLocation();
  return MakeUnique<RepeatStatement>(std::move(expression),
                                     std::move(statement), first, last);
}

std::unique_ptr<Statement> DefaultParser::parseWhileStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::While);

  auto expression = checkValue(tryParseExpression());
  auto statement = parseStatement();
  skipSemicolons();

  const auto last = lastLocation();
  return MakeUnique<WhileStatement>(std::move(expression), std::move(statement),
                                    first, last);
}

std::unique_ptr<Statement> DefaultParser::parseDoStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Do);

  auto statement = parseStatement();
  skipSemicolons();

  consumeIf(Token::Type::Until);
  auto expression = checkValue(tryParseExpression());

  const auto last = lastLocation();
  return MakeUnique<DoStatement>(std::move(expression), std::move(statement),
                                 first, last);
}

std::unique_ptr<Statement> DefaultParser::parseForStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::For);
  consumeIf(Token::Type::ParenOpen);

  auto initStatement = peek().is(Token::Type::Var)
                           ? static_cast<std::unique_ptr<Statement>>(parseVar())
                           : static_cast<std::unique_ptr<Statement>>(
                                 checkValue(tryParseExpression(true)));

  skipSemicolons();

  auto checkExpression = checkValue(tryParseExpression());
  skipSemicolons();

  auto iterationStatement = checkValue(tryParseExpression(true));
  skipSemicolons();

  consumeIf(Token::Type::ParenClose);
  auto statement = parseStatement();

  const auto last = lastLocation();
  return MakeUnique<ForStatement>(
      std::move(initStatement), std::move(checkExpression),
      std::move(iterationStatement), std::move(statement), first, last);
}

std::unique_ptr<Statement> DefaultParser::parseSwitchStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Switch);

  auto expression = checkValue(tryParseExpression());

  consumeIf(Token::Type::BraceOpen);

  std::vector<SwitchEntry> entries;

  for (;;) {
    if (!peek().is(Token::Type::Case) && !peek().is(Token::Type::Default))
      break;

    std::vector<SwitchCase> cases;

    for (;;) {
      if (peek().is(Token::Type::Case)) {
        consume();

        auto caseExpression = checkValue(tryParseExpression());
        consumeIf(Token::Type::Colon);

        cases.emplace_back(std::move(caseExpression));

      } else if (peek().is(Token::Type::Default)) {
        consume();
        consumeIf(Token::Type::Colon);
        cases.emplace_back();
      } else
        break;
    }

    std::vector<std::unique_ptr<Statement>> statements;

    for (;;) {
      auto statement = tryParseStatement();

      if (!statement) {
        if (!peek() || peek().is(Token::Type::BraceClose) ||
            peek().is(Token::Type::Case) || peek().is(Token::Type::Default))
          break;

        errorExpected(peek(), "statement");
        consume();
      } else {
        skipSemicolons();
        statements.emplace_back(std::move(statement));
      }
    }

    entries.emplace_back(std::move(cases), std::move(statements));
  }

  consumeIf(Token::Type::BraceClose);
  const auto last = lastLocation();

  return MakeUnique<SwitchStatement>(std::move(expression), std::move(entries),
                                     first, last);
}

std::unique_ptr<Statement> DefaultParser::parseWithStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::With);

  auto expression = checkValue(tryParseExpression());
  auto statement = parseStatement();
  skipSemicolons();

  const auto last = lastLocation();
  return MakeUnique<WithStatement>(std::move(expression), std::move(statement),
                                   first, last);
}

std::unique_ptr<Statement> DefaultParser::parseReturnStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Return);

  auto expression = checkValue(tryParseExpression());

  const auto last = lastLocation();
  return MakeUnique<ReturnStatement>(std::move(expression), first, last);
}

std::unique_ptr<Statement> DefaultParser::parseExitStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Exit);
  const auto last = lastLocation();
  return MakeUnique<ExitStatement>(first, last);
}

std::unique_ptr<Statement> DefaultParser::parseBreakStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Break);
  const auto last = lastLocation();
  return MakeUnique<BreakStatement>(first, last);
}

std::unique_ptr<Statement> DefaultParser::parseContinueStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Continue);
  const auto last = lastLocation();
  return MakeUnique<ContinueStatement>(first, last);
}

std::unique_ptr<Statement> DefaultParser::parseEnumStatement() {
  const auto first = firstLocation();
  consumeIf(Token::Type::Enum);

  const auto enumName =
      continueIf(Token::Type::Identifier) ? read().getString() : std::string{};

  consumeIf(Token::Type::BraceOpen);

  std::vector<EnumEntry> entries;

  for (;;) {
    while (peek() && !peek().is(Token::Type::Identifier) &&
           !peek().is(Token::Type::BraceClose))
      errorUnexpected(read());

    if (!peek() || peek().is(Token::Type::BraceClose)) break;

    auto name = read().getString();

    if (peek().is(Token::Type::Equal)) {
      consume();
      entries.emplace_back(name, checkValue(tryParseExpression()));
    } else
      entries.emplace_back(name);

    if (peek().is(Token::Type::BraceClose)) break;

    consumeIf(Token::Type::Comma);
  }

  consumeIf(Token::Type::BraceClose);

  const auto last = lastLocation();
  return MakeUnique<EnumStatement>(enumName, std::move(entries), first, last);
}

}  // namespace GMLAST

#pragma once

#include <GMLAST/Lexer/Token.hpp>
#include <memory>

namespace GMLAST {

class Base;
class Statement;
class Value;
struct ILogger;
struct ILexer;

class DefaultParser {
 public:
  static std::unique_ptr<Base> parse(std::unique_ptr<ILexer> lexer,
                                     std::unique_ptr<ILogger> logger);

 private:
  DefaultParser(std::unique_ptr<ILexer> lexer, std::unique_ptr<ILogger> logger);

  void errorExpected(const Token& token, Token::Type expectation);
  void errorExpected(const Token& token, const std::string& expectation);
  void errorUnexpected(const Token& token);

  const Token& peek() const noexcept { return m_token; }

  Token read() {
    auto old = std::move(m_token);
    consume();
    return old;
  }

  void consume();

  Location firstLocation() { return m_token.first(); }

  Location lastLocation() { return m_last; }

  bool consumeIf(Token::Type expectation);
  bool continueIf(Token::Type expectation);
  std::unique_ptr<Value> checkValue(std::unique_ptr<Value> value);

  void skipSemicolons();

  std::unique_ptr<Value> tryParseExpression(bool equalIsAssignment = false);
  std::unique_ptr<Value> tryParseAssignment(bool equalIsAssignment);
  std::unique_ptr<Value> tryParseLogical(bool equalIsAssignment);
  std::unique_ptr<Value> tryParseComparison(bool equalIsAssignment);
  std::unique_ptr<Value> tryParseBitwise();
  std::unique_ptr<Value> tryParseAdditive();
  std::unique_ptr<Value> tryParseMultiplicative();
  std::unique_ptr<Value> tryParsePrefix();
  std::unique_ptr<Value> tryParsePostfix();
  std::unique_ptr<Value> tryParseValue();
  std::unique_ptr<Statement> parseStatement();
  std::unique_ptr<Statement> tryParseStatement();
  std::unique_ptr<Statement> parseBlock();
  std::unique_ptr<Statement> parseGlobalVar();
  std::unique_ptr<Statement> parseVar();
  std::unique_ptr<Statement> parseIfStatement();
  std::unique_ptr<Statement> parseRepeatStatement();
  std::unique_ptr<Statement> parseWhileStatement();
  std::unique_ptr<Statement> parseDoStatement();
  std::unique_ptr<Statement> parseForStatement();
  std::unique_ptr<Statement> parseSwitchStatement();
  std::unique_ptr<Statement> parseWithStatement();
  std::unique_ptr<Statement> parseReturnStatement();
  std::unique_ptr<Statement> parseExitStatement();
  std::unique_ptr<Statement> parseBreakStatement();
  std::unique_ptr<Statement> parseContinueStatement();
  std::unique_ptr<Statement> parseEnumStatement();

  Token m_token;
  std::unique_ptr<ILexer> m_lexer;
  std::unique_ptr<ILogger> m_logger;
  Location m_last;
};

}  // namespace GMLAST

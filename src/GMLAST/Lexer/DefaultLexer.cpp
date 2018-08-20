#include <GMLAST/Lexer/DefaultLexer.hpp>
#include <GMLAST/Utils/ILogger.hpp>
#include <GMLAST/Utils/IStream.hpp>
#include <cassert>

namespace GMLAST {

DefaultLexer::DefaultLexer(std::unique_ptr<IStream> stream,
                           std::unique_ptr<ILogger> logger)
    : m_stream{std::move(stream)}, m_logger{std::move(logger)} {
  assert(m_stream && m_logger);
  m_value = m_stream->get();
}

Token DefaultLexer::lex() {
  for (;;) {
    if (eof()) return {};

    const auto begColumn = m_column;

    switch (peek()) {
      case '\t':
      case '\r':
      case '\n':
      case ' ':
        consume();
        break;
      case '!':
        consume();
        if (!eof() && peek() == '=') {
          consume();
          return {Token::Type::CmpNotEqual,
                  {m_line, begColumn},
                  {m_line, m_column}};
        }
        return {
            Token::Type::LogicalNot, {m_line, begColumn}, {m_line, m_column}};
      case '\"':
        return handleString();
      case '$':
        return handleHexNumber();
      case '%':
        consume();
        if (!eof() && peek() == '=') {
          consume();
          return {
              Token::Type::AssignMod, {m_line, begColumn}, {m_line, m_column}};
        }
        return {Token::Type::Modulo, {m_line, begColumn}, {m_line, m_column}};
      case '&':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '&':
              consume();
              return {Token::Type::LogicalAnd,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '=':
              consume();
              return {Token::Type::AssignBitAnd,
                      {m_line, begColumn},
                      {m_line, m_column}};
          }
        }
        return {
            Token::Type::BitwiseAnd, {m_line, begColumn}, {m_line, m_column}};
      case '\'':
        return handleString();
      case '(':
        consume();
        return {
            Token::Type::ParenOpen, {m_line, begColumn}, {m_line, m_column}};
      case ')':
        consume();
        return {
            Token::Type::ParenClose, {m_line, begColumn}, {m_line, m_column}};
      case '*':
        consume();
        if (!eof() && peek() == '=') {
          consume();
          return {
              Token::Type::AssignMul, {m_line, begColumn}, {m_line, m_column}};
        }
        return {Token::Type::Multiply, {m_line, begColumn}, {m_line, m_column}};
      case '+':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '+':
              consume();
              return {Token::Type::Increment,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '=':
              consume();
              return {Token::Type::AssignAdd,
                      {m_line, begColumn},
                      {m_line, m_column}};
          }
        }
        return {Token::Type::Plus, {m_line, begColumn}, {m_line, m_column}};
      case ',':
        consume();
        return {Token::Type::Comma, {m_line, begColumn}, {m_line, m_column}};
      case '-':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '-':
              consume();
              return {Token::Type::Decrement,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '=':
              consume();
              return {Token::Type::AssignSub,
                      {m_line, begColumn},
                      {m_line, m_column}};
          }
        }
        return {Token::Type::Minus, {m_line, begColumn}, {m_line, m_column}};
      case '/':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '*':
              consume();
              handleMultilineComment();
              return lex();
            case '/':
              consume();
              handleComment();
              return lex();
            case '=':
              consume();
              return {Token::Type::AssignDiv,
                      {m_line, begColumn},
                      {m_line, m_column}};
          }
        }
        return {Token::Type::Divide, {m_line, begColumn}, {m_line, m_column}};
      case ':':
        consume();
        if (!eof() && peek() == '=') {
          consume();
          return {Token::Type::Assign, {m_line, begColumn}, {m_line, m_column}};
        }
        return {Token::Type::Colon, {m_line, begColumn}, {m_line, m_column}};
      case ';':
        consume();
        return {
            Token::Type::Semicolon, {m_line, begColumn}, {m_line, m_column}};
      case '<':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '<':
              consume();
              return {Token::Type::BitwiseLeft,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '=':
              consume();
              return {Token::Type::CmpLessEqual,
                      {m_line, begColumn},
                      {m_line, m_column}};
          }
        }
        return {Token::Type::CmpLess, {m_line, begColumn}, {m_line, m_column}};
      case '=':
        consume();
        if (!eof() && peek() == '=') {
          consume();
          return {
              Token::Type::CmpEqual, {m_line, begColumn}, {m_line, m_column}};
        }
        return {Token::Type::Equal, {m_line, begColumn}, {m_line, m_column}};
      case '>':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '=':
              consume();
              return {Token::Type::CmpGreaterEqual,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '>':
              consume();
              return {Token::Type::BitwiseRight,
                      {m_line, begColumn},
                      {m_line, m_column}};
          }
        }
        return {
            Token::Type::CmpGreater, {m_line, begColumn}, {m_line, m_column}};
      case '[':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '#':
              consume();
              return {Token::Type::ArrayOpenGrid,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '?':
              consume();
              return {Token::Type::ArrayOpenMap,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '@':
              consume();
              return {Token::Type::ArrayOpenRef,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '|':
              consume();
              return {Token::Type::ArrayOpenList,
                      {m_line, begColumn},
                      {m_line, m_column}};
          }
        }
        return {
            Token::Type::ArrayOpen, {m_line, begColumn}, {m_line, m_column}};
      case ']':
        consume();
        return {
            Token::Type::ArrayClose, {m_line, begColumn}, {m_line, m_column}};
      case '^':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '=':
              consume();
              return {Token::Type::AssignBitXor,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '^':
              consume();
              return {Token::Type::LogicalXor,
                      {m_line, begColumn},
                      {m_line, m_column}};
          }
        }
        return {
            Token::Type::BitwiseXor, {m_line, begColumn}, {m_line, m_column}};
      case '{':
        consume();
        return {
            Token::Type::BraceOpen, {m_line, begColumn}, {m_line, m_column}};
      case '|':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '=':
              consume();
              return {Token::Type::AssignBitOr,
                      {m_line, begColumn},
                      {m_line, m_column}};
            case '|':
              consume();
              return {Token::Type::LogicalOr,
                      {m_line, begColumn},
                      {m_line, m_column}};
          }
        }
        return {
            Token::Type::BitwiseOr, {m_line, begColumn}, {m_line, m_column}};
      case '}':
        consume();
        return {
            Token::Type::BraceClose, {m_line, begColumn}, {m_line, m_column}};
      case '~':
        consume();
        return {
            Token::Type::BitwiseNot, {m_line, begColumn}, {m_line, m_column}};
      default:
        if (peek() == '.') return handleDot();

        if (peek() >= '0' && peek() <= '9') return handleNumber();

        if (peek() == '_' || (peek() >= 'A' && peek() <= 'Z') ||
            (peek() >= 'a' && peek() <= 'z'))
          return handleIdentifier();

        handleUnexpectedCharacter();
    }
  }
}

ILogger& DefaultLexer::logger() { return *m_logger; }

int DefaultLexer::peek() { return m_value; }

void DefaultLexer::consume() {
  if (m_value == '\n') {
    ++m_line;
    m_column = 0;
  } else if ((m_value & 0xC0) != 0x80)  // Only increase column if byte is ASCII
                                        // or the start of an UTF8 sequence
    ++m_column;

  m_value = m_stream->get();
}

bool DefaultLexer::eof() { return m_value == EOF; }

Token DefaultLexer::handleDot() {
  const auto beginColumn = m_column;
  consume();

  if (peek() < '0' || peek() > '9')
    return {Token::Type::Dot, {m_line, beginColumn}, {m_line, m_column}};

  std::string buffer(1, '.');

  while (peek() >= '0' && peek() <= '9') {
    buffer += peek();
    consume();
  }

  try {
    return {Token::Type::ConstDouble,
            {m_line, beginColumn},
            {m_line, m_column},
            std::stod(buffer)};
  } catch (const std::logic_error& ex) {
    m_logger->log(ILogger::Level::Error, ex.what(), {m_line, beginColumn},
                  {m_line, m_column});
    return lex();
  }
}

Token DefaultLexer::handleHexNumber() {
  const auto beginColumn = m_column;
  int number{0};

  consume();

  if ((peek() < '0' || peek() > '9') && (peek() < 'A' || peek() > 'F') &&
      (peek() < 'a' || peek() > 'f')) {
    m_logger->log(ILogger::Level::Error, "unexpected character '$'",
                  {m_line, m_column - 1}, {m_line, m_column});

    return lex();
  }

  for (;;) {
    if (peek() >= '0' && peek() <= '9')
      number = (number << 4) | (peek() - '0');
    else if (peek() >= 'A' && peek() <= 'F')
      number = (number << 4) | (peek() - 'A' + 0x0A);
    else if (peek() >= 'a' && peek() <= 'f')
      number = (number << 4) | (peek() - 'a' + 0x0A);
    else
      break;

    consume();
  }

  return {
      Token::Type::ConstInt, {m_line, beginColumn}, {m_line, m_column}, number};
}

Token DefaultLexer::handleIdentifier() {
  const auto beginColumn = m_column;
  std::string buffer;

  while (peek() == '_' || (peek() >= '0' && peek() <= '9') ||
         (peek() >= 'A' && peek() <= 'Z') || (peek() >= 'a' && peek() <= 'z')) {
    buffer += peek();
    consume();
  }

  auto type{Token::Type::Identifier};

  switch (buffer.size()) {
    case 2:
      if (buffer == "do")
        type = Token::Type::Do;
      else if (buffer == "if")
        type = Token::Type::If;
      else if (buffer == "or")
        type = Token::Type::LogicalOr;

      break;
    case 3:
      if (buffer == "and")
        type = Token::Type::LogicalAnd;
      else if (buffer == "div")
        type = Token::Type::IntDivide;
      else if (buffer == "for")
        type = Token::Type::For;
      else if (buffer == "mod")
        type = Token::Type::Modulo;
      else if (buffer == "not")
        type = Token::Type::LogicalNot;
      else if (buffer == "var")
        type = Token::Type::Var;
      else if (buffer == "xor")
        type = Token::Type::LogicalXor;

      break;
    case 4:
      if (buffer == "case")
        type = Token::Type::Case;
      else if (buffer == "else")
        type = Token::Type::Else;
      else if (buffer == "enum")
        type = Token::Type::Enum;
      else if (buffer == "exit")
        type = Token::Type::Exit;
      else if (buffer == "then")
        type = Token::Type::Then;
      else if (buffer == "with")
        type = Token::Type::With;

      break;
    case 5:
      if (buffer == "break")
        type = Token::Type::Break;
      else if (buffer == "until")
        type = Token::Type::Until;
      else if (buffer == "while")
        type = Token::Type::While;

      break;
    case 6:
      if (buffer == "repeat")
        type = Token::Type::Repeat;
      else if (buffer == "return")
        type = Token::Type::Return;
      else if (buffer == "switch")
        type = Token::Type::Switch;

      break;
    case 7:
      if (buffer == "default") type = Token::Type::Default;
      break;
    case 8:
      if (buffer == "continue") type = Token::Type::Continue;
      break;
    case 9:
      if (buffer == "globalvar") type = Token::Type::Globalvar;
      break;
  }

  if (type != Token::Type::Identifier)
    return {type, {m_line, beginColumn}, {m_line, m_column}};

  return {Token::Type::Identifier,
          {m_line, beginColumn},
          {m_line, m_column},
          std::move(buffer)};
}

Token DefaultLexer::handleNumber() {
  const auto beginColumn = m_column;

  try {
    std::string buffer;

    while (peek() >= '0' && peek() <= '9') {
      buffer += peek();
      consume();
    }

    if (peek() == '.') {
      buffer += '.';
      consume();

      while (peek() >= '0' && peek() <= '9') {
        buffer += peek();
        consume();
      }

      return {Token::Type::ConstDouble,
              {m_line, beginColumn},
              {m_line, m_column},
              std::stod(buffer)};
    } else {
      return {Token::Type::ConstInt,
              {m_line, beginColumn},
              {m_line, m_column},
              std::stoi(buffer)};
    }
  } catch (const std::logic_error& ex) {
    m_logger->log(ILogger::Level::Error, ex.what(), {m_line, beginColumn},
                  {m_line, m_column});
    return lex();
  }
}

Token DefaultLexer::handleString() {
  const auto beginLine = m_line;
  const auto beginColumn = m_column;
  const auto endChar = peek();

  consume();

  std::string out;
  while (!eof() && peek() != endChar) {
    out.push_back(peek());
    consume();
  }

  if (eof())
    m_logger->log(ILogger::Level::Error,
                  "unexpected end of file, string has no end",
                  {m_line, m_column}, {m_line, m_column});

  consume();
  return {Token::Type::ConstString,
          {beginLine, beginColumn},
          {m_line, m_column},
          std::move(out)};
}

void DefaultLexer::handleComment() {
  while (!eof() && peek() != '\n') consume();
  consume();
}

void DefaultLexer::handleMultilineComment() {
  while (!eof()) {
    if (peek() == '*') {
      consume();

      if (peek() == '/') {
        consume();
        return;
      }
    } else
      consume();
  }

  m_logger->log(ILogger::Level::Error,
                "unexpected end of file, comment has no end",
                {m_line, m_column}, {m_line, m_column});
}

void DefaultLexer::handleUnexpectedCharacter() {
  std::string msg{"unexpected character "};

  // Display control characters as numbers
  if (peek() < 32) {
    msg += std::to_string(peek());
    consume();
  } else {
    msg += '\'';
    msg += peek();
    consume();

    // Add remaining bytes of UTF8 sequence
    while (!eof() && (peek() & 0xC0) == 0x80) {
      msg += peek();
      consume();
    }

    msg += '\'';
  }

  m_logger->log(ILogger::Level::Error, std::move(msg), {m_line, m_column - 1},
                {m_line, m_column});
}

}  // namespace GMLAST

#include <GMLAST/Lexer/DefaultLexer.hpp>
#include <GMLAST/Utils/ILogger.hpp>
#include <GMLAST/Utils/IStream.hpp>
#include <cassert>

namespace GMLAST {

DefaultLexer::DefaultLexer(std::shared_ptr<IStream> stream,
                           std::shared_ptr<ILogger> logger)
    : m_stream{std::move(stream)}, m_logger{std::move(logger)} {
  assert(m_stream && m_logger);
  m_value = m_stream->get();
}

Token DefaultLexer::lex() {
  for (;;) {
    if (eof()) return {Token::Type::Invalid, location(), location()};

    const auto begLocation = location();

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
          return {Token::Type::CmpNotEqual, begLocation, location()};
        }
        return {Token::Type::LogicalNot, begLocation, location()};
      case '\"':
        return handleString();
      case '$':
        return handleHexNumber();
      case '%':
        consume();
        if (!eof() && peek() == '=') {
          consume();
          return {Token::Type::AssignMod, begLocation, location()};
        }
        return {Token::Type::Modulo, begLocation, location()};
      case '&':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '&':
              consume();
              return {Token::Type::LogicalAnd, begLocation, location()};
            case '=':
              consume();
              return {Token::Type::AssignBitAnd, begLocation, location()};
          }
        }
        return {Token::Type::BitwiseAnd, begLocation, location()};
      case '\'':
        return handleString();
      case '(':
        consume();
        return {Token::Type::ParenOpen, begLocation, location()};
      case ')':
        consume();
        return {Token::Type::ParenClose, begLocation, location()};
      case '*':
        consume();
        if (!eof() && peek() == '=') {
          consume();
          return {Token::Type::AssignMul, begLocation, location()};
        }
        return {Token::Type::Multiply, begLocation, location()};
      case '+':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '+':
              consume();
              return {Token::Type::Increment, begLocation, location()};
            case '=':
              consume();
              return {Token::Type::AssignAdd, begLocation, location()};
          }
        }
        return {Token::Type::Plus, begLocation, location()};
      case ',':
        consume();
        return {Token::Type::Comma, begLocation, location()};
      case '-':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '-':
              consume();
              return {Token::Type::Decrement, begLocation, location()};
            case '=':
              consume();
              return {Token::Type::AssignSub, begLocation, location()};
          }
        }
        return {Token::Type::Minus, begLocation, location()};
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
              return {Token::Type::AssignDiv, begLocation, location()};
          }
        }
        return {Token::Type::Divide, begLocation, location()};
      case ':':
        consume();
        if (!eof() && peek() == '=') {
          consume();
          return {Token::Type::Assign, begLocation, location()};
        }
        return {Token::Type::Colon, begLocation, location()};
      case ';':
        consume();
        return {Token::Type::Semicolon, begLocation, location()};
      case '<':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '<':
              consume();
              return {Token::Type::BitwiseLeft, begLocation, location()};
            case '=':
              consume();
              return {Token::Type::CmpLessEqual, begLocation, location()};
          }
        }
        return {Token::Type::CmpLess, begLocation, location()};
      case '=':
        consume();
        if (!eof() && peek() == '=') {
          consume();
          return {Token::Type::CmpEqual, begLocation, location()};
        }
        return {Token::Type::Equal, begLocation, location()};
      case '>':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '=':
              consume();
              return {Token::Type::CmpGreaterEqual, begLocation, location()};
            case '>':
              consume();
              return {Token::Type::BitwiseRight, begLocation, location()};
          }
        }
        return {Token::Type::CmpGreater, begLocation, location()};
      case '[':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '#':
              consume();
              return {Token::Type::ArrayOpenGrid, begLocation, location()};
            case '?':
              consume();
              return {Token::Type::ArrayOpenMap, begLocation, location()};
            case '@':
              consume();
              return {Token::Type::ArrayOpenRef, begLocation, location()};
            case '|':
              consume();
              return {Token::Type::ArrayOpenList, begLocation, location()};
          }
        }
        return {Token::Type::ArrayOpen, begLocation, location()};
      case ']':
        consume();
        return {Token::Type::ArrayClose, begLocation, location()};
      case '^':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '=':
              consume();
              return {Token::Type::AssignBitXor, begLocation, location()};
            case '^':
              consume();
              return {Token::Type::LogicalXor, begLocation, location()};
          }
        }
        return {Token::Type::BitwiseXor, begLocation, location()};
      case '{':
        consume();
        return {Token::Type::BraceOpen, begLocation, location()};
      case '|':
        consume();
        if (!eof()) {
          switch (peek()) {
            case '=':
              consume();
              return {Token::Type::AssignBitOr, begLocation, location()};
            case '|':
              consume();
              return {Token::Type::LogicalOr, begLocation, location()};
          }
        }
        return {Token::Type::BitwiseOr, begLocation, location()};
      case '}':
        consume();
        return {Token::Type::BraceClose, begLocation, location()};
      case '~':
        consume();
        return {Token::Type::BitwiseNot, begLocation, location()};
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

std::shared_ptr<ILogger> DefaultLexer::logger() { return m_logger; }

int DefaultLexer::peek() { return m_value; }

void DefaultLexer::consume() {
  if (m_value == '\n') {
    ++m_line;
    m_lineIndex = ++m_index;
  } else if ((m_value & 0xC0) != 0x80)  // Only increase column if byte is ASCII
                                        // or the start of an UTF8 sequence
    ++m_index;

  m_value = m_stream->get();
}

bool DefaultLexer::eof() { return m_value == EOF; }

Location DefaultLexer::location() const {
  return {m_line, m_index - m_lineIndex, m_index};
}

Token DefaultLexer::handleDot() {
  const auto begLocation = location();
  consume();

  if (peek() < '0' || peek() > '9')
    return {Token::Type::Dot, begLocation, location()};

  std::string buffer(1, '.');

  while (peek() >= '0' && peek() <= '9') {
    buffer += static_cast<char>(peek());
    consume();
  }

  try {
    return {Token::Type::ConstDouble, begLocation, location(),
            std::stod(buffer)};
  } catch (const std::logic_error& ex) {
    m_logger->log(ILogger::Level::Error, ex.what(), begLocation, location());
    return lex();
  }
}

Token DefaultLexer::handleHexNumber() {
  const auto begLocation = location();
  int number{0};

  consume();

  if ((peek() < '0' || peek() > '9') && (peek() < 'A' || peek() > 'F') &&
      (peek() < 'a' || peek() > 'f')) {
    m_logger->log(ILogger::Level::Error, "unexpected character '$'",
                  begLocation, location());

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

  return {Token::Type::ConstInt, begLocation, location(), number};
}

Token DefaultLexer::handleIdentifier() {
  const auto begLocation = location();
  std::string buffer;

  while (peek() == '_' || (peek() >= '0' && peek() <= '9') ||
         (peek() >= 'A' && peek() <= 'Z') || (peek() >= 'a' && peek() <= 'z')) {
    buffer += static_cast<char>(peek());
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

  if (type != Token::Type::Identifier) return {type, begLocation, location()};

  return {Token::Type::Identifier, begLocation, location(), std::move(buffer)};
}

Token DefaultLexer::handleNumber() {
  const auto begLocation = location();

  try {
    std::string buffer;

    while (peek() >= '0' && peek() <= '9') {
      buffer += static_cast<char>(peek());
      consume();
    }

    if (peek() == '.') {
      buffer += '.';
      consume();

      while (peek() >= '0' && peek() <= '9') {
        buffer += static_cast<char>(peek());
        consume();
      }

      return {Token::Type::ConstDouble, begLocation, location(),
              std::stod(buffer)};
    } else {
      return {Token::Type::ConstInt, begLocation, location(),
              std::stoi(buffer)};
    }
  } catch (const std::logic_error& ex) {
    m_logger->log(ILogger::Level::Error, ex.what(), begLocation, location());
    return lex();
  }
}

Token DefaultLexer::handleString() {
  const auto begLocation = location();
  const auto endChar = peek();

  consume();

  std::string out;
  while (!eof() && peek() != endChar) {
    out.push_back(static_cast<char>(peek()));
    consume();
  }

  if (eof())
    m_logger->log(ILogger::Level::Error,
                  "unexpected end of file, string has no end", begLocation,
                  location());

  consume();
  return {Token::Type::ConstString, begLocation, location(), std::move(out)};
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
                "unexpected end of file, comment has no end", location(),
                location());
}

void DefaultLexer::handleUnexpectedCharacter() {
  std::string msg{"unexpected character "};

  // Display control characters as numbers
  if (peek() < 32) {
    msg += std::to_string(peek());
    consume();
  } else {
    msg += '\'';
    msg += static_cast<char>(peek());
    consume();

    // Add remaining bytes of UTF8 sequence
    while (!eof() && (peek() & 0xC0) == 0x80) {
      msg += static_cast<char>(peek());
      consume();
    }

    msg += '\'';
  }

  m_logger->log(ILogger::Level::Error, std::move(msg),
                {m_line, m_index - m_lineIndex - 1, m_index - 1}, location());
}

}  // namespace GMLAST

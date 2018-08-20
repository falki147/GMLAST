#pragma once

#include <GMLAST/Lexer/ILexer.hpp>
#include <memory>

namespace GMLAST {

struct IStream;
struct ILogger;

class DefaultLexer : public ILexer {
 public:
  DefaultLexer(std::unique_ptr<IStream> stream,
               std::unique_ptr<ILogger> logger);

  virtual Token lex() override;
  virtual ILogger& logger() override;

 private:
  int peek();
  void consume();
  bool eof();

  Token handleDot();
  Token handleHexNumber();
  Token handleIdentifier();
  Token handleNumber();
  Token handleString();

  void handleComment();
  void handleMultilineComment();
  void handleUnexpectedCharacter();

  std::unique_ptr<IStream> m_stream;
  std::unique_ptr<ILogger> m_logger;
  int m_value{0};
  unsigned int m_line{0}, m_column{0};
};

}  // namespace GMLAST

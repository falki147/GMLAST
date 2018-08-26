#pragma once

#include <GMLAST/Lexer/ILexer.hpp>
#include <memory>

namespace GMLAST {

struct IStream;
struct ILogger;

class DefaultLexer : public ILexer {
 public:
  DefaultLexer(std::shared_ptr<IStream> stream,
               std::shared_ptr<ILogger> logger);

  virtual Token lex() override;
  virtual std::shared_ptr<ILogger> logger() override;

 private:
  int peek();
  void consume();
  bool eof();

  Location location() const;

  Token handleDot();
  Token handleHexNumber();
  Token handleIdentifier();
  Token handleNumber();
  Token handleString();

  void handleComment();
  void handleMultilineComment();
  void handleUnexpectedCharacter();

  std::shared_ptr<IStream> m_stream;
  std::shared_ptr<ILogger> m_logger;
  int m_value{0};
  int m_line{0}, m_index{0}, m_lineIndex{0};
};

}  // namespace GMLAST

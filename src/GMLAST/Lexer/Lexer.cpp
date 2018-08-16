#include <GMLAST/Lexer/DefaultLexer.hpp>
#include <GMLAST/Lexer/Lexer.hpp>
#include <GMLAST/Lexer/NullStream.hpp>

namespace GMLAST {

class DefaultLexer : public ILexer {
 public:
  DefaultLexer(const reflex::Input& input) : m_base{input, m_outStream} {}

  virtual Token lex() override { return m_base.lexToken(); }

 private:
  DefaultLexerBase m_base;
  NullStream m_outStream;
};

std::unique_ptr<ILexer> CreateDefaultLexer(const char* cstring) {
  return std::make_unique<DefaultLexer>(reflex::Input{cstring});
}

std::unique_ptr<ILexer> CreateDefaultLexer(const wchar_t* wstring) {
  return std::make_unique<DefaultLexer>(reflex::Input{wstring});
}

std::unique_ptr<ILexer> CreateDefaultLexer(const std::string& string) {
  return std::make_unique<DefaultLexer>(reflex::Input{string});
}

std::unique_ptr<ILexer> CreateDefaultLexer(const std::wstring& wstring) {
  return std::make_unique<DefaultLexer>(reflex::Input{wstring});
}

std::unique_ptr<ILexer> CreateDefaultLexer(std::istream& istream) {
  return std::make_unique<DefaultLexer>(reflex::Input{istream});
}

}  // namespace GMLAST

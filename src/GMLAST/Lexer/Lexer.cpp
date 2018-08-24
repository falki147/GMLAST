#include <GMLAST/Lexer/DefaultLexer.hpp>
#include <GMLAST/Lexer/Lexer.hpp>
#include <GMLAST/Utils/ILogger.hpp>
#include <GMLAST/Utils/ReferenceLogger.hpp>
#include <GMLAST/Utils/UniquePtrHelper.hpp>

namespace GMLAST {

template <class T>
class IteratorStream : public IStream {
 public:
  IteratorStream(T begin, T end) : m_cur{begin}, m_end{end} {}

  virtual int get() override {
    if (m_cur == m_end) return EOF;
    return *m_cur++;
  }

 private:
  T m_cur, m_end;
};

struct StdStream : IStream {
  StdStream(std::istream& stream) : stream{stream} {}

  virtual int get() override { return stream.get(); }

  std::istream& stream;
};

std::unique_ptr<ILexer> CreateDefaultLexer(const char* cstring,
                                           std::unique_ptr<ILogger> logger) {
  return MakeUnique<DefaultLexer>(
      MakeUnique<IteratorStream<const char*>>(
          cstring, cstring + std::char_traits<char>::length(cstring)),
      std::move(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(const std::string& string,
                                           std::unique_ptr<ILogger> logger) {
  return MakeUnique<DefaultLexer>(
      MakeUnique<IteratorStream<std::string::const_iterator>>(string.cbegin(),
                                                              string.cend()),
      std::move(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(std::istream& istream,
                                           std::unique_ptr<ILogger> logger) {
  return MakeUnique<DefaultLexer>(MakeUnique<StdStream>(istream),
                                  std::move(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(std::unique_ptr<IStream> stream,
                                           std::unique_ptr<ILogger> logger) {
  return MakeUnique<DefaultLexer>(std::move(stream), std::move(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(const char* cstring,
                                           ILogger& logger) {
  return CreateDefaultLexer(cstring, MakeUnique<ReferenceLogger>(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(const std::string& string,
                                           ILogger& logger) {
  return CreateDefaultLexer(string, MakeUnique<ReferenceLogger>(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(std::istream& istream,
                                           ILogger& logger) {
  return CreateDefaultLexer(istream, MakeUnique<ReferenceLogger>(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(std::unique_ptr<IStream> stream,
                                           ILogger& logger) {
  return CreateDefaultLexer(std::move(stream),
                            MakeUnique<ReferenceLogger>(logger));
}

}  // namespace GMLAST

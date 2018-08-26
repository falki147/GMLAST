#include <GMLAST/Lexer/DefaultLexer.hpp>
#include <GMLAST/Lexer/Lexer.hpp>
#include <GMLAST/Utils/ILogger.hpp>
#include <GMLAST/Utils/MemoryHelper.hpp>

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
                                           std::shared_ptr<ILogger> logger) {
  const auto length = std::char_traits<char>::length(cstring);

  auto stream =
      MakeUnique<IteratorStream<const char*>>(cstring, cstring + length);

  return MakeUnique<DefaultLexer>(std::move(stream), std::move(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(const std::string& string,
                                           std::shared_ptr<ILogger> logger) {
  using StringStream = IteratorStream<std::string::const_iterator>;

  return MakeUnique<DefaultLexer>(
      MakeShared<StringStream>(string.cbegin(), string.cend()),
      std::move(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(std::istream& istream,
                                           std::shared_ptr<ILogger> logger) {
  return MakeUnique<DefaultLexer>(MakeShared<StdStream>(istream),
                                  std::move(logger));
}

std::unique_ptr<ILexer> CreateDefaultLexer(std::shared_ptr<IStream> stream,
                                           std::shared_ptr<ILogger> logger) {
  return MakeUnique<DefaultLexer>(std::move(stream), std::move(logger));
}

}  // namespace GMLAST

%top{
#include <GMLAST/Lexer/Token.hpp>

template <class It>
GMLAST::Location GetLocation(It beg, It end) {
  GMLAST::Location loc{0, 0};

  for (; beg != end; ++beg) {
    if (*beg == '\r') {
      if (std::next(beg) != end && *std::next(beg) == '\n') ++beg;

      ++loc.line;
      loc.column = 0;
    } else if (*beg == '\n') {
      ++loc.line;
      loc.column = 0;
    } else if ((static_cast<std::uint8_t>(*beg) & 0xC0) != 0x80)
      ++loc.column;
  }

  return loc;
}

%}

%class{
 public:
  Token lexToken() {
    if (lex() == 0) return {};

    return std::move(m_token);
  }

  const Token& token() const noexcept { return m_token; }

 private:
  template <class... Args>
  void createToken(Token::Type type, Args&&... args) {
    const auto line1 = lineno();
    const auto column1 = columno();

    const auto relativeEndLoc = GetLocation(matcher().begin(), matcher().end());

    const auto line2 = line1 + relativeEndLoc.line;
    const auto column2 = relativeEndLoc.line == 0
                             ? column1 + relativeEndLoc.column
                             : relativeEndLoc.column;

    m_token = {
        type, {line1, column1}, {line2, column2}, std::forward<Args>(args)...};
  }

  Token m_token;
%}

%{

template <class It>
int StringToInt(It beg, It end) {
  int result = 0;

  for (; beg != end; ++beg) result = 10 * result + (*beg - '0');

  return result;
}

template <class It>
int HexStringToInt(It beg, It end) {
  int result = 0;

  for (; beg != end; ++beg) {
    if (*beg >= '0' && *beg <= '9')
      result = (result << 4) + (*beg - '0');
    else if (*beg >= 'A' && *beg <= 'F')
      result = (result << 4) + (*beg - 'A' + 10);
    else if (*beg >= 'a' && *beg <= 'f')
      result = (result << 4) + (*beg - 'a' + 10);
  }

  return result;
}

template <class It>
double StringToDouble(It beg, It end) {
  long double result = 0;

  for (; beg != end && *beg != '.'; ++beg) result = result * 10 + (*beg - '0');

  if (beg != end) {
    long double fraction = 0;

    for (--end; beg != end; --end) fraction = fraction / 10 + (*end - '0');

    result += fraction / 10;
  }

  return static_cast<double>(result);
}

%}

%option nodefault
%option noyywrap

%option lexer=DefaultLexerBase

%option namespace=GMLAST

%x COMMENT

D  [0-9]
ND [_a-zA-Z]
ID {ND}({ND}|{D})*
NI {D}+
NF ({D}*\.{D}+|{D}+\.{D}*)
NH "$"[0-9a-fA-F]+
WS [ \t]
SS '[^']*'
SD \"[^"]*\"

%%

\/\/.*
"/*" start(COMMENT);

<COMMENT>{
[^*]*
"*"+[^*/]*
"*"+"/" start();
}

"[#"         createToken(Token::Type::ArrayOpenGrid); return 1;
"[|"         createToken(Token::Type::ArrayOpenList); return 1;
"[?"         createToken(Token::Type::ArrayOpenMap); return 1;
"[@"         createToken(Token::Type::ArrayOpenRef); return 1;
":="         createToken(Token::Type::Assign); return 1;
"+="         createToken(Token::Type::AssignAdd); return 1;
"&="         createToken(Token::Type::AssignBitAnd); return 1;
"|="         createToken(Token::Type::AssignBitOr); return 1;
"^="         createToken(Token::Type::AssignBitXor); return 1;
"/="         createToken(Token::Type::AssignDiv); return 1;
"%="         createToken(Token::Type::AssignMod); return 1;
"*="         createToken(Token::Type::AssignMul); return 1;
"-="         createToken(Token::Type::AssignSub); return 1;
"<<"         createToken(Token::Type::BitwiseLeft); return 1;
">>"         createToken(Token::Type::BitwiseRight); return 1;
"=="         createToken(Token::Type::CmpEqual); return 1;
">="         createToken(Token::Type::CmpGreaterEqual); return 1;
"!="         createToken(Token::Type::CmpNotEqual); return 1;
"<="         createToken(Token::Type::CmpLessEqual); return 1;
"--"         createToken(Token::Type::Decrement); return 1;
"++"         createToken(Token::Type::Increment); return 1;
"&&"         createToken(Token::Type::LogicalAnd); return 1;
"||"         createToken(Token::Type::LogicalOr); return 1;
"^^"         createToken(Token::Type::LogicalXor); return 1;

"]"          createToken(Token::Type::ArrayClose); return 1;
"["          createToken(Token::Type::ArrayOpen); return 1;
"&"          createToken(Token::Type::BitwiseAnd); return 1;
"~"          createToken(Token::Type::BitwiseNot); return 1;
"|"          createToken(Token::Type::BitwiseOr); return 1;
"^"          createToken(Token::Type::BitwiseXor); return 1;
"}"          createToken(Token::Type::BraceClose); return 1;
"{"          createToken(Token::Type::BraceOpen); return 1;
">"          createToken(Token::Type::CmpGreater); return 1;
"<"          createToken(Token::Type::CmpLess); return 1;
":"          createToken(Token::Type::Colon); return 1;
","          createToken(Token::Type::Comma); return 1;
"/"          createToken(Token::Type::Divide); return 1;
"."          createToken(Token::Type::Dot); return 1;
"="          createToken(Token::Type::Equal); return 1;
"!"          createToken(Token::Type::LogicalNot); return 1;
"-"          createToken(Token::Type::Minus); return 1;
"%"          createToken(Token::Type::Modulo); return 1;
"*"          createToken(Token::Type::Multiply); return 1;
")"          createToken(Token::Type::ParenClose); return 1;
"("          createToken(Token::Type::ParenOpen); return 1;
"+"          createToken(Token::Type::Plus); return 1;
";"          createToken(Token::Type::Semicolon); return 1;

"and"        createToken(Token::Type::LogicalAnd); return 1;
"break"      createToken(Token::Type::Break); return 1;
"case"       createToken(Token::Type::Case); return 1;
"continue"   createToken(Token::Type::Continue); return 1;
"default"    createToken(Token::Type::Default); return 1;
"div"        createToken(Token::Type::IntDivide); return 1;
"do"         createToken(Token::Type::Do); return 1;
"else"       createToken(Token::Type::Else); return 1;
"enum"       createToken(Token::Type::Enum); return 1;
"exit"       createToken(Token::Type::Exit); return 1;
"for"        createToken(Token::Type::For); return 1;
"globalvar"  createToken(Token::Type::Globalvar); return 1;
"if"         createToken(Token::Type::If); return 1;
"mod"        createToken(Token::Type::Modulo); return 1;
"not"        createToken(Token::Type::LogicalNot); return 1;
"or"         createToken(Token::Type::LogicalOr); return 1;
"repeat"     createToken(Token::Type::Repeat); return 1;
"return"     createToken(Token::Type::Return); return 1;
"switch"     createToken(Token::Type::Switch); return 1;
"then"       createToken(Token::Type::Then); return 1;
"until"      createToken(Token::Type::Until); return 1;
"var"        createToken(Token::Type::Var); return 1;
"while"      createToken(Token::Type::While); return 1;
"with"       createToken(Token::Type::With); return 1;
"xor"        createToken(Token::Type::LogicalXor); return 1;

{SS}         createToken(Token::Type::ConstString, std::string { matcher().begin() + 1, matcher().end() - 1 }); return 1;
{SD}         createToken(Token::Type::ConstString, std::string { matcher().begin() + 1, matcher().end() - 1 }); return 1;
{NI}         createToken(Token::Type::ConstInt, StringToInt(matcher().begin(), matcher().end())); return 1;
{NH}         createToken(Token::Type::ConstInt, HexStringToInt(matcher().begin() + 1, matcher().end())); return 1;
{NF}         createToken(Token::Type::ConstDouble, StringToDouble(matcher().begin(), matcher().end())); return 1;
{ID}         createToken(Token::Type::Identifier, matcher().str()); return 1;
{WS}+
.            createToken(Token::Type::InvalidSymbol, matcher().str()); return 1;

%%

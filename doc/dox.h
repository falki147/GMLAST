/**
 * \file dox.h
 * \brief General documentation built from a doxygen comment
 */

/**
\mainpage GMLAST - Parser for GML

\section intro Introduction

GMLAST is a parser and lexer for the Game Maker Language (GML). It takes an
UTF-8 string or stream and converts it into an <a
href="https://en.wikipedia.org/wiki/Abstract_syntax_tree">abstract syntax tree
(AST)</a> for further processing. It can also be used for error detection.

The library consists of two parts. The lexer and the parser. The lexer splits
the input into smaller pieces, so called \link GMLAST::Token tokens\endlink.
E.g. `+` becomes a token with the type \link GMLAST::Token::Type::Plus
Token::Type::Plus\endlink. These tokens are then fed to the parser which
generates an abstract syntax tree. Any error or warning that occurs during the
lexing or parsing is handled by the \link GMLAST::ILogger logger\endlink.

\dotfile GMLAST.dot

\section example AST Example

Script:
\code{.cpp}
if (a > b)
  a = 1 + 2 * 3;
\endcode

Output:
\dotfile AST.dot

\section usage Usage

There is one lexer provided by the library. It can be instantiated with the
\link GMLAST::CreateDefaultLexer() CreateDefaultLexer\endlink functions. Other
lexers can be used by implementing the \link GMLAST::ILexer ILexer\endlink
interface which has to be implemented by all lexers. The lexer can then be
forwarded to the \link GMLAST::ParseDefault() ParseDefault\endlink function
which creates the AST tree. It can be traversed by implementing the \link
GMLAST::IVisitor IVisitor\endlink interface. When calling \link
GMLAST::Base::visit visit\endlink on the node it'll call the corresponding
function in the interface e.g. calling \link GMLAST::ArrayOperator::visit
ArrayOperator::visit\endlink calls \link GMLAST::IVisitor::onArrayOperator
IVisitor::onArrayOperator\endlink on the given interface.

Parsing any code only takes one line (assuming a \link GMLAST::ILogger
logger\endlink is implemented and the input can be used in \link
GMLAST::CreateDefaultLexer() CreateDefaultLexer\endlink):
\code{.cpp}
auto ast =
    ParseDefault(CreateDefaultLexer(code, std::make_unqiue<CustomLogger>()));
\endcode

\section building Building

For building this project <a href="https://cmake.org/">CMake</a> is required.

*/

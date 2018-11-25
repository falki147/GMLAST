# GMLAST - Parser for GML
## Introduction

GMLAST is a parser and lexer for the Game Maker Language (GML). It takes an
UTF-8 string or stream and converts it into an abstract syntax tree (AST) for
further processing. It can also be used for error detection.

The library consists of two parts. The lexer and the parser. The lexer splits
the input into smaller pieces, so called tokens. E.g. + becomes a token with
the type Token::Type::Plus. These tokens are then fed to the parser which
generates an abstract syntax tree. Any error or warning that occurs during the
lexing or parsing is handled by the logger.

![GMLAST Flowchart](https://www.preinfalk.co.at/projects/GMLAST/dot_GMLAST.svg)

## AST Example

Script: 
```
if (a > b)
	a = 1 + 2 * 3;
```
Output:

![AST](https://www.preinfalk.co.at/projects/GMLAST/dot_AST.svg)

## Usage

There is one lexer provided by the library. It can be instantiated with the
CreateDefaultLexer functions. Other lexers can be used by implementing the
ILexer interface which has to be implemented by all lexers. The lexer can then
be forwarded to the ParseDefault function which creates the AST tree. It can be
traversed by implementing the IVisitor interface. When calling visit on the
node it'll call the corresponding function in the interface e.g. calling
ArrayOperator::visit calls IVisitor::onArrayOperator on the given interface.

Parsing any code only takes one line (assuming a logger is implemented and the
input can be used in CreateDefaultLexer):
```
auto ast = ParseDefault(CreateDefaultLexer(code,
		std::make_unqiue<CustomLogger>()));
```

## Building
For building this project CMake is required.

## Example
See [online editor](https://www.preinfalk.co.at/projects/GMLAST/example/)

## Documentation
See [Doxygen](https://www.preinfalk.co.at/projects/GMLAST/)

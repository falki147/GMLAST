#include <GMLAST/AST/Base.hpp>
#include <GMLAST/Parser/DefaultParser.hpp>
#include <GMLAST/Parser/Parser.hpp>

namespace GMLAST {

std::unique_ptr<Base> ParseDefault(std::unique_ptr<ILexer> lexer) {
  return DefaultParser::parse(std::move(lexer));
}

std::unique_ptr<Base> ParseDefault(
    std::unique_ptr<ILexer> lexer,
    std::vector<ValidationEntry>& validationEntries) {
  return DefaultParser::parse(std::move(lexer), validationEntries);
}

}  // namespace GMLAST

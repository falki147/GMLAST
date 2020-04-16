#include <GMLAST/AST/Base.hpp>
#include <GMLAST/Lexer/ILexer.hpp>
#include <GMLAST/Parser/DefaultParser.hpp>
#include <GMLAST/Parser/Parser.hpp>
#include <GMLAST/Utils/ILogger.hpp>
#include <GMLAST/Utils/MemoryHelper.hpp>

namespace GMLAST {

std::unique_ptr<Base> ParseDefault(std::unique_ptr<ILexer> lexer,
                                   std::shared_ptr<ILogger> logger) {
  return DefaultParser::parse(std::move(lexer), std::move(logger));
}

std::unique_ptr<Base> ParseExpressionDefault(std::unique_ptr<ILexer> lexer,
                                             std::shared_ptr<ILogger> logger) {
  return DefaultParser::parseExpression(std::move(lexer), std::move(logger));
}

}  // namespace GMLAST

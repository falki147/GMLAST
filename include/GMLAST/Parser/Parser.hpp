/**
 * \file Parser.hpp
 */

#pragma once

#include <memory>

namespace GMLAST {
class Base;
struct ILexer;
struct ILogger;

/**
 * \brief Parses input from lexer
 *
 * If there is an error while parsing the AST might contain an Error node.
 *
 * \param lexer Lexer interface which provides the token. The default lexer can
 * be created using \link CreateDefaultLexer() CreateDefaultLexer\endlink.
 * \param logger Logger interface or null pointer. If it is null it calls \link
 * GMLAST::ILexer::logger ILexer::logger \endlink and uses its logger.
 */
std::unique_ptr<Base> ParseDefault(std::unique_ptr<ILexer> lexer,
                                   std::shared_ptr<ILogger> logger = {});

}  // namespace GMLAST

/**
 * \file Lexer.hpp
 */

#pragma once

#include <GMLAST/Utils/IStream.hpp>
#include <istream>
#include <memory>
#include <string>

namespace GMLAST {

struct ILexer;
struct ILogger;

/**
 * \brief Creates the default lexer
 *
 * This function creates an instance of the default lexer of the library. It
 * provides a location for each token. It can only handle UTF-8 and ASCII
 * inputs.
 *
 * \param cstring String to be used as input. It has to be null terminated and
 * must not be destroyed during the lifetime of the lexer because the lexer
 * doesn't copy the string.
 * \param logger Logger which handles all the warning and error messages. It is
 * stored in the lexer and is destroyed when the lexer is.
 */
std::unique_ptr<ILexer> CreateDefaultLexer(const char* cstring,
                                           std::shared_ptr<ILogger> logger);

/**
 * \brief Creates the default lexer
 *
 * This function creates an instance of the default lexer of the library. It
 * provides a location for each token. It can only handle UTF-8 and ASCII
 * inputs.
 *
 * \param string String to be used as input. It takes a reference of the string
 * and thus must not be destroyed during the lifetime of the lexer.
 * \param logger Logger which handles all the warning and error messages. It is
 * stored in the lexer and is destroyed when the lexer is.
 */
std::unique_ptr<ILexer> CreateDefaultLexer(const std::string& string,
                                           std::shared_ptr<ILogger> logger);

/**
 * \brief Creates the default lexer
 *
 * This function creates an instance of the default lexer of the library. It
 * provides a location for each token. It can only handle UTF-8 and ASCII
 * inputs.
 *
 * \param istream Stream to be used as input. It takes a reference of the stream
 * and thus must not be destroyed during the lifetime of the lexer.
 * \param logger Logger which handles all the warning and error messages. It is
 * stored in the lexer and is destroyed when the lexer is.
 */
std::unique_ptr<ILexer> CreateDefaultLexer(std::istream& istream,
                                           std::shared_ptr<ILogger> logger);

/**
 * \brief Creates the default lexer
 *
 * This function creates an instance of the default lexer of the library. It
 * provides a location for each token. It can only handle UTF-8 and ASCII
 * inputs.
 *
 * \param stream Stream to be used as input. The stream is destroyed (or the
 * reference counter decreased) after the destruction of the lexer.
 * \param logger Logger which handles all the warning and error messages. It is
 * stored in the lexer and is destroyed when the lexer is.
 */
std::unique_ptr<ILexer> CreateDefaultLexer(std::shared_ptr<IStream> stream,
                                           std::shared_ptr<ILogger> logger);

}  // namespace GMLAST

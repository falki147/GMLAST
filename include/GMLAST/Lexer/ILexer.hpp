/**
 * \file ILexer.hpp
 */

#pragma once

#include <GMLAST/Lexer/Token.hpp>
#include <memory>

namespace GMLAST {

struct ILogger;

/**
 * \brief Lexer interface
 */
struct ILexer {
  /**
   * \brief Virtual default destructor to make interface deletable
   */
  virtual ~ILexer() = default;

  /**
   * \brief Scan for a token
   *
   * If it is at the end of the input it always returns an invalid token
   * (Token::Type::Invalid) even if the function is called multiple times. It is
   * implementation defined if a location is provided for the returned token but
   * it is recommended.
   *
   * \return Scanned token or an invalid one.
   */
  virtual Token lex() = 0;

  /**
   * \brief Return logger associated with lexer
   *
   * If the lexer doesn't have a logger it must throw an exception. It is
   * guaranteed to return an interface or throw.
   *
   * \return Logger interface
   */
  virtual std::shared_ptr<ILogger> logger() = 0;
};

}  // namespace GMLAST

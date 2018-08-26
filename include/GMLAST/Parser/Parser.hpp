#pragma once

#include <memory>

namespace GMLAST {
class Base;
struct ILexer;
struct ILogger;

std::unique_ptr<Base> ParseDefault(std::unique_ptr<ILexer> lexer,
                                   std::shared_ptr<ILogger> logger = {});

}  // namespace GMLAST

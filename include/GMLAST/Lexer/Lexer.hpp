#pragma once

#include <GMLAST/Utils/IStream.hpp>
#include <istream>
#include <memory>
#include <string>

namespace GMLAST {

struct ILexer;
struct ILogger;

std::unique_ptr<ILexer> CreateDefaultLexer(const char* cstring,
                                           std::unique_ptr<ILogger> logger);

std::unique_ptr<ILexer> CreateDefaultLexer(const std::string& string,
                                           std::unique_ptr<ILogger> logger);

std::unique_ptr<ILexer> CreateDefaultLexer(std::istream& istream,
                                           std::unique_ptr<ILogger> logger);

std::unique_ptr<ILexer> CreateDefaultLexer(std::unique_ptr<IStream> stream,
                                           std::unique_ptr<ILogger> logger);

}  // namespace GMLAST

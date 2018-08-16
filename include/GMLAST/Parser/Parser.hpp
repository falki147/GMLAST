#pragma once

#include <GMLAST/Parser/ValidationEntry.hpp>
#include <memory>
#include <vector>

namespace GMLAST {
class Base;
struct ILexer;

std::unique_ptr<Base> ParseDefault(std::unique_ptr<ILexer> lexer);
std::unique_ptr<Base> ParseDefault(
    std::unique_ptr<ILexer> lexer,
    std::vector<ValidationEntry>& validationEntries);

}  // namespace GMLAST

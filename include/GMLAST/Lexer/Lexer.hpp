#pragma once

#include <GMLAST/Lexer/ILexer.hpp>
#include <istream>
#include <memory>
#include <string>

namespace GMLAST {

std::unique_ptr<ILexer> CreateDefaultLexer(const char* cstring);
std::unique_ptr<ILexer> CreateDefaultLexer(const wchar_t* wstring);
std::unique_ptr<ILexer> CreateDefaultLexer(const std::string& string);
std::unique_ptr<ILexer> CreateDefaultLexer(const std::wstring& wstring);
std::unique_ptr<ILexer> CreateDefaultLexer(std::istream& istream);

}  // GMLAST

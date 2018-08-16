#define CATCH_CONFIG_MAIN
#include <GMLAST/AST/Base.hpp>
#include <GMLAST/Lexer/Lexer.hpp>
#include <GMLAST/Parser/Parser.hpp>
#include <GMLAST/Parser/ParserException.hpp>
#include <ParserTest/JsonSerializer.hpp>
#include <ParserTest/RandomLexer.hpp>
#include <catch.hpp>
#include <ctime>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <testdata.hpp>

TEST_CASE("Test Data Scripts", "[DefaultParser]") {
  for (auto file : TestDataScriptFiles) {
    SECTION(file) {
      std::ifstream f(file, std::ios::in | std::ios::binary);

      if (f.fail()) continue;

      // Skip define
      if (f.peek() == '#') {
        while (f.get() != '\n') {
        }
      }

      CHECK_NOTHROW(GMLAST::ParseDefault(GMLAST::CreateDefaultLexer(f)));
    }
  }
}

TEST_CASE("Test Data Tests", "[DefaultParser]") {
  for (auto file : TestDataTestFiles) {
    SECTION(file) {
      auto data = nlohmann::json::parse(
          std::ifstream(file, std::ios::in | std::ios::binary));

      for (auto& entry : data.items()) {
        if (!entry.value().is_null()) {
          std::unique_ptr<GMLAST::Base> ast;

          CHECK_NOTHROW(ast = GMLAST::ParseDefault(
                            GMLAST::CreateDefaultLexer(entry.key())));

          CHECK(*ast == entry.value());
        } else
          CHECK_THROWS(
              GMLAST::ParseDefault(GMLAST::CreateDefaultLexer(entry.key())));
      }
    }
  }
}

TEST_CASE("Random Scripts", "[DefaultParser]") {
  const auto time = std::time(nullptr);

  for (auto i = 0u; i < 100; ++i) {
    const auto seed = time + i;

    SECTION("Random " + std::to_string(seed)) {
      std::vector<GMLAST::ValidationEntry> entries;
      CHECK_NOTHROW(GMLAST::ParseDefault(
          std::unique_ptr<GMLAST::ILexer>{new ParserTest::RandomLexer(
              100, static_cast<unsigned int>(seed))},
          entries));
    }
  }
}

#define CATCH_CONFIG_MAIN
#include <GMLAST/AST/Base.hpp>
#include <GMLAST/Lexer/Lexer.hpp>
#include <GMLAST/Parser/Parser.hpp>
#include <GMLAST/Utils/ILogger.hpp>
#include <ParserTest/JsonSerializer.hpp>
#include <ParserTest/RandomLexer.hpp>
#include <catch.hpp>
#include <ctime>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <sstream>
#include <testdata.hpp>

struct ExceptionLogger : GMLAST::ILogger {
  virtual void log(Level level, std::string msg, GMLAST::Location beg,
                   GMLAST::Location) override {
    if (level == Level::Error) {
      std::stringstream ss;
      ss << beg.line + 1 << ':' << beg.column + 1 << ':' << msg;
      throw std::runtime_error(ss.str());
    }
  }
};

struct NullLogger : GMLAST::ILogger {
  virtual void log(Level, std::string, GMLAST::Location,
                   GMLAST::Location) override {}
};

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

      CHECK_NOTHROW(GMLAST::ParseDefault(
          GMLAST::CreateDefaultLexer(f, std::make_unique<ExceptionLogger>())));
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

          CHECK_NOTHROW(ast = GMLAST::ParseDefault(GMLAST::CreateDefaultLexer(
                            entry.key(), std::make_unique<ExceptionLogger>())));

          CHECK(*ast == entry.value());
        } else
          CHECK_THROWS(GMLAST::ParseDefault(GMLAST::CreateDefaultLexer(
              entry.key(), std::make_unique<ExceptionLogger>())));
      }
    }
  }
}

TEST_CASE("Random Scripts", "[DefaultParser]") {
  const auto time = std::time(nullptr);

  for (auto i = 0u; i < 100; ++i) {
    const auto seed = time + i;

    SECTION("Random " + std::to_string(seed)) {
      CHECK_NOTHROW(
          GMLAST::ParseDefault(std::make_unique<ParserTest::RandomLexer>(
                                   100, static_cast<unsigned int>(seed)),
                               std::make_unique<NullLogger>()));
    }
  }
}

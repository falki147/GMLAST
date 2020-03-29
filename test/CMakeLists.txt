add_subdirectory(data)

file(GLOB_RECURSE PARSERTEST_SOURCE ParserTest/*.cpp)

add_executable(ParserTest ${PARSERTEST_SOURCE})

target_link_libraries(
  ParserTest PRIVATE Catch2::Catch2 nlohmann_json GMLAST TestData)
target_include_directories(ParserTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(ParserTest PUBLIC cxx_std_11)

add_test(NAME ParserTest COMMAND ParserTest)

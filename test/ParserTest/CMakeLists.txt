file(GLOB_RECURSE PARSERTEST_SOURCE *.cpp)

add_executable(ParserTest ${PARSERTEST_SOURCE})
target_link_libraries(ParserTest PRIVATE Catch2::Catch GMLAST TestData)
target_include_directories(ParserTest PRIVATE ${CMAKE_SOURCE_DIR}/test)

add_test(NAME ParserTest COMMAND ParserTest)

add_subdirectory(data)

file(GLOB_RECURSE GMLASTTEST_SOURCE src/*.cpp)

add_executable(GMLASTTest ${GMLASTTEST_SOURCE})

target_link_libraries(GMLASTTest PRIVATE Catch2::Catch2 nlohmann_json GMLAST
                                         TestData)
target_include_directories(GMLASTTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_features(GMLASTTest PUBLIC cxx_std_11)

add_test(NAME GMLASTTest COMMAND GMLASTTest)

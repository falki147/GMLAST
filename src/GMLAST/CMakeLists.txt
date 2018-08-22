file(GLOB_RECURSE AST_SOURCE AST/*.cpp)
file(GLOB_RECURSE LEXER_SOURCE Lexer/*.cpp)
file(GLOB_RECURSE PARSER_SOURCE Parser/*.cpp)

add_library(GMLAST STATIC ${LEXER_SOURCE} ${PARSER_SOURCE} ${AST_SOURCE})

set_target_properties(GMLAST PROPERTIES DEBUG_POSTFIX d)

target_include_directories(GMLAST
                           PRIVATE
                           ${CMAKE_SOURCE_DIR}/src
                           ${CMAKE_CURRENT_BINARY_DIR}/src
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>)

target_compile_features(GMLAST PUBLIC cxx_std_11)

install(TARGETS GMLAST EXPORT GMLAST ARCHIVE DESTINATION "lib/GMLAST")

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/GMLAST DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")

install(EXPORT GMLAST DESTINATION "lib/cmake/GMLAST" FILE "GMLASTConfig.cmake")

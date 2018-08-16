# Generate lexer in binary dir
set(LEXER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/src/GMLAST/Lexer)

REFLEX_TARGET(Lexer/DefaultLexer.l
              ${LEXER_BINARY_DIR}/DefaultLexer.cpp
              HEADER_FILE
              ${LEXER_BINARY_DIR}/DefaultLexer.hpp)

file(GLOB_RECURSE AST_SOURCE AST/*.cpp)
file(GLOB_RECURSE LEXER_SOURCE Lexer/*.cpp)
file(GLOB_RECURSE PARSER_SOURCE Parser/*.cpp)

add_library(GMLAST
            STATIC
            ${REFLEX_SOURCE}
            ${LEXER_BINARY_DIR}/DefaultLexer.cpp
            ${LEXER_SOURCE}
            ${PARSER_SOURCE}
            ${AST_SOURCE})

set_target_properties(GMLAST PROPERTIES DEBUG_POSTFIX d)

if(MINGW) # localtime_r (used in debug.cpp) is undefined if _POSIX_C_SOURCE
          # isn't set
  target_compile_definitions(GMLAST PRIVATE -D_POSIX_C_SOURCE)
endif()

target_include_directories(GMLAST
                           PRIVATE
                           ${REFLEX_INCLUDE_DIR}
                           ${CMAKE_SOURCE_DIR}/src
                           ${CMAKE_CURRENT_BINARY_DIR}/src
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>)

install(TARGETS GMLAST EXPORT GMLAST ARCHIVE DESTINATION "lib/GMLAST")

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/GMLAST DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")

install(EXPORT GMLAST DESTINATION "lib/cmake/GMLAST" FILE "GMLASTConfig.cmake")

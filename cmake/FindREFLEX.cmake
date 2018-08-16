# FindREFLEX
# --------
#
# Find reflex executable and provides a macro to generate custom build rules
#
# The module defines the following variables: FLEX_FOUND - true is flex
# executable is found FLEX_EXECUTABLE - the path to the flex executable
# FLEX_VERSION - the version of flex FLEX_LIBRARIES - The flex libraries
# FLEX_INCLUDE_DIRS - The path to the flex headers

function(find_directory var)
  cmake_parse_arguments(ARGS "FULLPATH" "NAME;PATH;DOC" "" ${ARGN})

  file(TO_CMAKE_PATH ${ARGS_PATH} ARGS_PATH)

  if(EXISTS ${ARGS_PATH}/${ARGS_NAME})
    if(${ARGS_FULLPATH})
      set(${var} ${ARGS_PATH}/${ARGS_NAME} CACHE PATH ${ARGS_DOC} FORCE)
    else()
      set(${var} ${ARGS_PATH} CACHE PATH ${ARGS_DOC} FORCE)
    endif()
  else()
    set(${var} ${ARGS_NAME}-NOTFOUND CACHE PATH ${ARGS_DOC})
  endif()
endfunction()

find_program(REFLEX_EXECUTABLE NAMES reflex DOC "path to the reflex executable")
mark_as_advanced(REFLEX_EXECUTABLE)

get_filename_component(REFLEX_EXECUTABLE_DIR ${REFLEX_EXECUTABLE} DIRECTORY)

find_directory(REFLEX_INCLUDE_DIR
               NAME
               reflex
               PATH
               ${REFLEX_EXECUTABLE_DIR}/../include
               DOC
               "path to the include directory")

mark_as_advanced(REFLEX_INCLUDE_DIR)

find_directory(REFLEX_LIB_DIR
               NAME
               lib
               PATH
               ${REFLEX_EXECUTABLE_DIR}/..
               FULLPATH
               DOC
               "path to the lib directory")

mark_as_advanced(REFLEX_LIB_DIR)

find_directory(REFLEX_UNICODE_DIR
               NAME
               unicode
               PATH
               ${REFLEX_EXECUTABLE_DIR}/..
               FULLPATH
               DOC
               "path to the unicode directory")

mark_as_advanced(REFLEX_UNICODE_DIR)

if(REFLEX_LIB_DIR)
  file(GLOB_RECURSE REFLEX_LIB_SOURCE ${REFLEX_LIB_DIR}/*.cpp)
endif()

if(REFLEX_UNICODE_DIR)
  file(GLOB_RECURSE REFLEX_UNICODE_SOURCE ${REFLEX_UNICODE_DIR}/*.cpp)
endif()

list(APPEND REFLEX_SOURCE ${REFLEX_LIB_SOURCE} ${REFLEX_UNICODE_SOURCE})

if(REFLEX_EXECUTABLE)
  execute_process(COMMAND ${REFLEX_EXECUTABLE} --version
                  OUTPUT_VARIABLE REFLEX_version_output
                  ERROR_VARIABLE REFLEX_version_error
                  RESULT_VARIABLE REFLEX_version_result)

  if(NOT ${FLEX_version_result} EQUAL 0)
    string(CONCAT ERROR_MESSAGE
           "Command \"${REFLEX_EXECUTABLE} --version\" "
           "failed with output:\n${REFLEX_version_output}\n"
           "${REFLEX_version_error}")

    if(REFLEX_FIND_REQUIRED)
      message(SEND_ERROR ${ERROR_MESSAGE})
    else()
      message("${ERROR_MESSAGE} REFLEX_VERSION will not be available")
    endif()
  else()
    string(REGEX MATCH
                 [0-9]\.[0-9]\.[0-9]
                 REFLEX_VERSION
                 ${REFLEX_version_output})
  endif()

  function(REFLEX_TARGET Input Output)
    cmake_parse_arguments(ARGS "" "COMPILE_FLAGS;HEADER_FILE" "" ${ARGN})

    if(ARGS_UNPARSED_ARGUMENTS)
      message(
        SEND_ERROR
          "REFLEX_TARGET(<Input> <Output> [COMPILE_FLAGS <string>] [HEADER_FILE <string>]"
        )
    else()
      separate_arguments(ARGS_COMPILE_FLAGS)

      if(ARGS_HEADER_FILE)
        list(APPEND ARGS_COMPILE_FLAGS --header-file=${ARGS_HEADER_FILE})
      endif()

      add_custom_command(
        OUTPUT ${Output}
        COMMAND ${REFLEX_EXECUTABLE} ${ARGS_COMPILE_FLAGS} -o${Output} ${Input}
        VERBATIM
        DEPENDS ${Input}
        COMMENT
          "[REFLEX][${Input}] Building scanner with reflex ${REFLEX_VERSION}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
  endfunction()
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(REFLEX
                                  REQUIRED_VARS
                                  REFLEX_EXECUTABLE
                                  REFLEX_INCLUDE_DIR
                                  REFLEX_LIB_DIR
                                  REFLEX_UNICODE_DIR
                                  VERSION_VAR
                                  REFLEX_VERSION)

set(TESTDATA_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/testdata)

file(GLOB_RECURSE TESTDATA_SCRIPT_FILES *.gml)
file(GLOB_RECURSE TESTDATA_TEST_FILES *.test.json)

if(TESTDATA_SCRIPT_FILES)
  string(REPLACE ";"
                 "),\nTESTDATA_STRINGIFY("
                 TESTDATA_SCRIPT_FILES
                 "TESTDATA_STRINGIFY(${TESTDATA_SCRIPT_FILES})")
endif()

if(TESTDATA_TEST_FILES)
  string(REPLACE ";"
                 "),\nTESTDATA_STRINGIFY("
                 TESTDATA_TEST_FILES
                 "TESTDATA_STRINGIFY(${TESTDATA_TEST_FILES})")
endif()

configure_file(testdata.hpp.in ${TESTDATA_BINARY_DIR}/testdata.hpp)

add_library(TestData INTERFACE)
target_include_directories(TestData INTERFACE ${TESTDATA_BINARY_DIR})

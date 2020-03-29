cmake_minimum_required(VERSION 3.11)

project(GMLAST LANGUAGES CXX VERSION 1.1.0)

option(GMLAST_BUILD_LIBRARY "Enable building the library" ON)
option(GMLAST_GENERATE_DOCS "Enable generating the documentation" OFF)
option(BUILD_TESTING "Enable testing for GMLAST" OFF)

set(GMLAST_BASE ${CMAKE_CURRENT_SOURCE_DIR})
set(GMLAST_FULLNAME ${PROJECT_NAME}-${PROJECT_VERSION})
set(GMLAST_INSTALL_PREFIX lib/${GMLAST_FULLNAME})

if(BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  set(GMLAST_BUILD_TEST ON)
else()
  set(GMLAST_BUILD_TEST OFF)
endif()

if(GMLAST_BUILD_LIBRARY OR GMLAST_BUILD_TEST)
  add_subdirectory(src)
endif()

if(GMLAST_GENERATE_DOCS)
  add_subdirectory(doc)
endif()

if(GMLAST_BUILD_TEST)
  find_package(Catch2 REQUIRED)
  find_package(nlohmann_json REQUIRED)

  enable_testing()

  add_subdirectory(test)
endif()

cmake_minimum_required(VERSION 3.11)

project(GMLAST LANGUAGES CXX)

option(GMLAST_BUILD_LIBRARY "Enable building the library" ON)
option(GMLAST_GENERATE_DOCS "Enable generating the documentation" OFF)
option(BUILD_TESTING "Enable testing for GMLAST" OFF)

if(GMLAST_BUILD_LIBRARY OR BUILD_TESTING)
  add_subdirectory(src)
endif()

if(GMLAST_GENERATE_DOCS)
  add_subdirectory(doc)
endif()

if(BUILD_TESTING)
  find_package(Catch2 REQUIRED)
  find_package(nlohmann_json REQUIRED)

  enable_testing()

  add_subdirectory(testdata)
  add_subdirectory(test)
endif()

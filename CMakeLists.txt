cmake_minimum_required(VERSION 3.11)

project(GMLAST LANGUAGES CXX)

option(BUILD_TESTING "Enable testing for GMLAST" OFF)

add_subdirectory(src)

if(BUILD_TESTING)
  find_package(Catch2 REQUIRED)
  find_package(nlohmann_json REQUIRED)

  enable_testing()

  add_subdirectory(testdata)
  add_subdirectory(test)
endif()

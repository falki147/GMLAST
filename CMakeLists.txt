cmake_minimum_required(VERSION 3.11)

project(GMLAST)

option(GMLAST_ENABLE_TESTING "Enable testing for GMLAST" OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(REFLEX REQUIRED)

add_subdirectory(src)

if(GMLAST_ENABLE_TESTING)
  find_package(Catch2 REQUIRED)
  find_package(nlohmann_json REQUIRED)

  enable_testing()

  add_subdirectory(testdata)
  add_subdirectory(test)
endif()

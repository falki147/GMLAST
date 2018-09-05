include(CMakePackageConfigHelpers)

file(GLOB_RECURSE GMLAST_SOURCE GMLAST/*.cpp)

add_library(GMLAST STATIC ${GMLAST_SOURCE})

set_target_properties(GMLAST PROPERTIES DEBUG_POSTFIX d)

target_include_directories(GMLAST
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           PUBLIC
                           $<BUILD_INTERFACE:${GMLAST_BASE}/include>
                           $<INSTALL_INTERFACE:${GMLAST_INSTALL_PREFIX}/include>
                           )

target_compile_features(GMLAST PUBLIC cxx_std_11)

install(TARGETS GMLAST
        EXPORT GMLAST
        ARCHIVE DESTINATION ${GMLAST_INSTALL_PREFIX}/lib)

install(DIRECTORY ${GMLAST_BASE}/include DESTINATION ${GMLAST_INSTALL_PREFIX}
        FILES_MATCHING PATTERN "*.hpp")

install(EXPORT GMLAST
               DESTINATION
               ${GMLAST_INSTALL_PREFIX}/cmake
               FILE
               "GMLASTConfig.cmake")

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/GMLASTConfigVersion.cmake COMPATIBILITY
  SameMinorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/GMLASTConfigVersion.cmake DESTINATION
              ${GMLAST_INSTALL_PREFIX}/cmake)
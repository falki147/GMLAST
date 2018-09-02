find_package(Doxygen REQUIRED dot)

set(DOXYGEN_BASEDIR ${CMAKE_SOURCE_DIR})
set(DOXYGEN_OUTPUTDIR ${CMAKE_CURRENT_BINARY_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
               ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

file(GLOB_RECURSE DOXYGEN_INCLUDE_FILES ${DOXYGEN_BASEDIR}/include/*.hpp)
file(GLOB_RECURSE DOXYGEN_DOC_FILES ${DOXYGEN_BASEDIR}/doc/*.h)

add_custom_target(Doc ALL DEPENDS doxygen.stamp)

add_custom_command(OUTPUT doxygen.stamp
                   DEPENDS Doxyfile
                   COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
                   COMMAND ${CMAKE_COMMAND} -E touch doxygen.stamp
                   COMMENT "Generating GMLAST documentation" VERBATIM)

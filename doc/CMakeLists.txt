find_package(Doxygen REQUIRED dot)

get_target_property(DOXYGEN_DOT_EXECUTABLE Doxygen::dot IMPORTED_LOCATION)
get_filename_component(DOXYGEN_DOT_PATH ${DOXYGEN_DOT_EXECUTABLE} DIRECTORY)

file(TO_NATIVE_PATH ${DOXYGEN_DOT_EXECUTABLE} DOXYGEN_DOT_EXECUTABLE)
file(TO_NATIVE_PATH ${DOXYGEN_DOT_PATH} DOXYGEN_DOT_PATH)

file(TO_NATIVE_PATH ${CMAKE_SOURCE_DIR} DOXYGEN_BASEDIR)
file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR} DOXYGEN_OUTPUTDIR)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
               ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

add_custom_target(Doc ALL DEPENDS doxygen.stamp)

add_custom_command(OUTPUT doxygen.stamp
                   DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                   COMMAND Doxygen::doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                   COMMAND ${CMAKE_COMMAND} -E touch doxygen.stamp
                   COMMENT "Generating GMLAST documentation" VERBATIM)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION
                  ${GMLAST_INSTALL_PREFIX}/doc)

FILE(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/doc/html/")

FIND_PACKAGE(Doxygen)

IF(DOXYGEN_FOUND)
	IF(DOXYGEN_DOT_FOUND)
		SET(CF_UNIPAX_HAS_DOT "YES")
	ELSE()
		SET(CF_UNIPAX_HAS_DOT "NO")
	ENDIF()

  CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/doc/Doxyfile.in ${PROJECT_BINARY_DIR}/doc/Doxyfile)
  
  #######################################################################
  ## doc
  ADD_CUSTOM_TARGET(doc ${AUTO_BUILD_DOC}
                    COMMAND ${CMAKE_COMMAND} -E echo "Creating html documentation"
                    COMMAND ${CMAKE_COMMAND} -E remove_directory doc/html
                    COMMAND ${CMAKE_COMMAND} -E chdir doc ${DOXYGEN_EXECUTABLE} Doxyfile
                    COMMAND ${CMAKE_COMMAND} -E echo "The documentation has been successfully created."
                    COMMAND ${CMAKE_COMMAND} -E echo "You can now open '${PROJECT_BINARY_DIR}/doc/html/index.html' in a web browser."
                    COMMENT "Build the doxygen documentation"
                    COMPONENT "${COMPONENT_DOCUMENTATION_HTML}"
                    VERBATIM)
ENDIF()

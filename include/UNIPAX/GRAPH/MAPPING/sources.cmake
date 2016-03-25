### list all filenames of the directory here ###
SET(GROUP "GRAPH/MAPPING")

SET(DIRECTORY "${CMAKE_SOURCE_DIR}/include/UNIPAX/${GROUP}")

FILE(GLOB HEADERS_LIST "${DIRECTORY}/*.h")	

ADD_UNIPAX_HEADERS("${GROUP}" "${HEADERS_LIST}")

IF (database STREQUAL "oracle")
	INCLUDE(${CMAKE_SOURCE_DIR}/include/UNIPAX/GRAPH/MAPPING/ORACLE/sources.cmake)
ENDIF (database STREQUAL "oracle")

IF (NOT (database STREQUAL "oracle"))
	INCLUDE(${CMAKE_SOURCE_DIR}/include/UNIPAX/GRAPH/MAPPING/MYSQL/sources.cmake)
ENDIF (NOT (database STREQUAL "oracle"))


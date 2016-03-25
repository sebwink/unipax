SET(SOURCES_LIST
	MappingEngine.cpp
)

ADD_UNIPAX_SOURCES("GRAPH/MAPPING" "${SOURCES_LIST}")

IF (database STREQUAL "oracle")
	INCLUDE("GRAPH/MAPPING/ORACLE/sources.cmake")
ENDIF (database STREQUAL "oracle")

IF (NOT (database STREQUAL "oracle"))
	INCLUDE("GRAPH/MAPPING/MYSQL/sources.cmake")
ENDIF (NOT (database STREQUAL "oracle"))


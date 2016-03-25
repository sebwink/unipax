IF (database STREQUAL "oracle")
	INCLUDE("SERVER/BACKEND/ORACLE/sources.cmake")
ENDIF (database STREQUAL "oracle")

IF (NOT (database STREQUAL "oracle"))
	INCLUDE("SERVER/BACKEND/MYSQL/sources.cmake")
ENDIF (NOT (database STREQUAL "oracle"))

SET(SOURCES_LIST
QueryEngine.cpp
)

ADD_UNIPAX_SOURCES("SERVER/BACKEND" "${SOURCES_LIST}")



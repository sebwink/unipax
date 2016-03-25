IF (database STREQUAL "oracle")
	INCLUDE("PERSISTENCE/ORACLE/sources.cmake")
ENDIF (database STREQUAL "oracle")

IF (NOT (database STREQUAL "oracle"))
	INCLUDE("PERSISTENCE/MYSQL/sources.cmake")
ENDIF (NOT (database STREQUAL "oracle"))

SET(SOURCES_LIST
	DBManager.cpp
	ODBWorker.cpp
	ODBRunnable.cpp
	ODBLoadRunnable.cpp
	ODBUnloadRunnable.cpp
	ODBUpdateRunnable.cpp
	ODBPersistRunnable.cpp
)

ADD_UNIPAX_SOURCES("PERSISTENCE" "${SOURCES_LIST}")

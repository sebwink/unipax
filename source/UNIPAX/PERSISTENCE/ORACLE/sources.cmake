INCLUDE("PERSISTENCE/ORACLE/BIOPAX/sources.cmake")
INCLUDE("PERSISTENCE/ORACLE/EXT/sources.cmake")

SET(SOURCES_LIST
	OracleManager.cpp
	OracleODBWorker.cpp
	OracleODBLoadRunnable.cpp
	OracleODBUpdateRunnable.cpp
	OracleODBPersistRunnable.cpp
)

ADD_UNIPAX_SOURCES("PERSISTENCE/ORACLE" "${SOURCES_LIST}")

INCLUDE("PERSISTENCE/MYSQL/BIOPAX/sources.cmake")
INCLUDE("PERSISTENCE/MYSQL/EXT/sources.cmake")

SET(SOURCES_LIST
	MySQLManager.cpp
	MySQLODBWorker.cpp
	MySQLODBLoadRunnable.cpp
	MySQLODBUnloadRunnable.cpp
	MySQLODBUpdateRunnable.cpp
	MySQLODBPersistRunnable.cpp
)

ADD_UNIPAX_SOURCES("PERSISTENCE/MYSQL" "${SOURCES_LIST}")

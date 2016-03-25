# - Find mysqlclient
# Find the native MySQL includes and library
#
#  MYSQL_INCLUDE_DIR - where to find mysql.h, etc.
#  MYSQL_LIBRARY   - List of libraries when using MySQL.
#  MYSQL_FOUND       - True if MySQL found.

IF (NOT (database STREQUAL "oracle"))
  INCLUDE(LibFindMacros)

  FIND_PATH(MYSQL_INCLUDE_DIR mysql.h
    /usr/local/include/mysql
    /usr/include/mysql
  )

  SET(MYSQL_NAMES mysqlclient_r)
  FIND_LIBRARY(MYSQL_LIBRARY
    NAMES ${MYSQL_NAMES}
    PATHS /usr/lib /usr/local/lib
    PATH_SUFFIXES mysql
  )

  SET(MYSQL_PROCESS_INCLUDES MYSQL_INCLUDE_DIR)
  SET(MYSQL_PROCESS_LIBS MYSQL_LIBRARY)
  LIBFIND_PROCESS(MYSQL)
  SET(UNIPAX_DATABASE_FLAGS "-D ODB_MYSQL")
  
ENDIF (NOT (database STREQUAL "oracle"))
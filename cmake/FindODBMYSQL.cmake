# - Try to find LIBODB
# Once done, this will define
#
#  ODBMYSQL_FOUND - system has LIBODB
#  ODBMYSQL_INCLUDE_DIR - the LIBODB include directories
#  ODBMYSQL_LIBRARY - link these to use LIBODB

INCLUDE(LibFindMacros)

# Use pkg-config to get hints about paths
LIBFIND_PKG_CHECK_MODULES(ODBMYSQL_PKGCONF libodb-mysql)

# Include dir
FIND_PATH(ODBMYSQL_INCLUDE_DIR
  NAMES odb/mysql/mysql.hxx
	  PATHS ${ODBMYSQL_PKGCONF_INCLUDE_DIRS}
		PATH_SUFFIXES odb-mysql
)

# Finally the library itself
FIND_LIBRARY(ODBMYSQL_LIBRARY
  NAMES odb-mysql
	  PATHS ${ODBMYSQL_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
SET(ODBMYSQL_PROCESS_INCLUDES ODBMYSQL_INCLUDE_DIR)
SET(ODBMYSQL_PROCESS_LIBS ODBMYSQL_LIBRARY)
LIBFIND_PROCESS(ODBMYSQL)

# - Try to find LIBODB
# Once done, this will define
#
#  ODBORACLE_FOUND - system has LIBODB
#  ODBORACLE_INCLUDE_DIR - the LIBODB include directories
#  ODBORACLE_LIBRARY - link these to use LIBODB

IF (database STREQUAL "oracle")
  INCLUDE(LibFindMacros)

  # Use pkg-config to get hints about paths
  LIBFIND_PKG_CHECK_MODULES(ODBORACLE_PKGCONF libodb-oracle)

  # Include dir
  FIND_PATH(ODBORACLE_INCLUDE_DIR
    NAMES odb/oracle/version.hxx
	    PATHS ${ODBORACLE_PKGCONF_INCLUDE_DIRS}
		  PATH_SUFFIXES odb-oracle
  )

  # Finally the library itself
  FIND_LIBRARY(ODBORACLE_LIBRARY
    NAMES odb-oracle
	    PATHS ${ODBORACLE_PKGCONF_LIBRARY_DIRS}
  )

  # Set the include dir variables and the libraries and let libfind_process do the rest.
  # NOTE: Singular variables for this library, plural for libraries this this lib depends on.
  SET(ODBORACLE_PROCESS_INCLUDES ODBORACLE_INCLUDE_DIR)
  SET(ODBORACLE_PROCESS_LIBS ODBORACLE_LIBRARY)
  LIBFIND_PROCESS(ODBORACLE)
  SET(UNIPAX_DATABASE_FLAGS "-D ODB_ORACLE")

ENDIF (database STREQUAL "oracle")

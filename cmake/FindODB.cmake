# - Try to find ODB
# Once done, this will define
#
#  ODB_FOUND - system has ODB
#  ODB_INCLUDE_DIR - the ODB include directories
#  ODB_LIBRARY - link these to use ODB

INCLUDE(LibFindMacros)

# Use pkg-config to get hints about paths
LIBFIND_PKG_CHECK_MODULES(ODB_PKGCONF libodb)

# Include dir
FIND_PATH(ODB_INCLUDE_DIR
  NAMES odb/core.hxx
	  PATHS ${ODB_PKGCONF_INCLUDE_DIRS}
		PATH_SUFFIXES odb
)
#MESSAGE(STATUS "OBD_INCLUDE_DIR=" ${ODB_INCLUDE_DIR})

# Finally the library itself
FIND_LIBRARY(ODB_LIBRARY
  NAMES odb
	  PATHS ${ODB_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
SET(ODB_PROCESS_INCLUDES ODB_INCLUDE_DIR)
SET(ODB_PROCESS_LIBS ODB_LIBRARY)
LIBFIND_PROCESS(ODB)

# - Try to find LIBODB
# Once done, this will define
#
#  ODBBOOST_FOUND - system has LIBODB
#  ODBBOOST_INCLUDE_DIR - the LIBODB include directories
#  ODBBOOST_LIBRARY - link these to use LIBODB

INCLUDE(LibFindMacros)

# Use pkg-config to get hints about paths
LIBFIND_PKG_CHECK_MODULES(ODBBOOST_PKGCONF libodb-boost)

# Include dir
FIND_PATH(ODBBOOST_INCLUDE_DIR
  NAMES odb/boost/version.hxx
	  PATHS ${ODBBOOST_PKGCONF_INCLUDE_DIRS}
		PATH_SUFFIXES odb-boost
)

# Finally the library itself
FIND_LIBRARY(ODBBOOST_LIBRARY
  NAMES odb-boost
	  PATHS ${ODBBOOST_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
SET(ODBBOOST_PROCESS_INCLUDES ODBBOOST_INCLUDE_DIR)
SET(ODBBOOST_PROCESS_LIBS ODBBOOST_LIBRARY)
LIBFIND_PROCESS(ODBBOOST)

# - Find Lemon library
# Once done, this will define
#
#  LEMON_FOUND - system has Lemon
#  LEMON_INCLUDE_DIR - the Lemon include directories
#  LEMON_LIBRARY - link these to use Lemon


INCLUDE(LibFindMacros)

# Use pkg-config to get hints about paths
LIBFIND_PKG_CHECK_MODULES(LEMON_PKGCONF lemon)

# Include dir
FIND_PATH(LEMON_INCLUDE_DIR
  NAMES lemon/config.h
	  PATHS ${LEMON_PKGCONF_INCLUDE_DIRS}
		PATH_SUFFIXES lemon
)


# Finally the library itself
FIND_LIBRARY(LEMON_LIBRARY
  NAMES emon
	  PATHS ${LEMON_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
SET(LEMON_PROCESS_INCLUDES LEMON_INCLUDE_DIR)
SET(LEMON_PROCESS_LIBS LEMON_LIBRARY)
LIBFIND_PROCESS(EMON)

ADD_DEFINITIONS(-DLEMON_HAVE_LONG_LONG)

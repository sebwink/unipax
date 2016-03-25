# - Try to find SBML
# Once done, this will define
#
#  SBML_FOUND - system has ODB
#  SBML_INCLUDE_DIR - the ODB include directories
#  SBML_LIBRARY - link these to use ODB

INCLUDE(LibFindMacros)

# Use pkg-config to get hints about paths
LIBFIND_PKG_CHECK_MODULES(SBML_PKGCONF libsbml)

# Include dir
FIND_PATH(SBML_INCLUDE_DIR
  NAMES sbml/SBMLTypes.h
	  PATHS ${SBML_PKGCONF_INCLUDE_DIRS}
		PATH_SUFFIXES sbml
)
#MESSAGE(STATUS "SBML_INCLUDE_DIR=" ${SBML_INCLUDE_DIR})

# Finally the library itself
FIND_LIBRARY(SBML_LIBRARY
  NAMES sbml
	  PATHS ${SBML_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
SET(SBML_PROCESS_INCLUDES SBML_INCLUDE_DIR)
SET(SBML_PROCESS_LIBS SBML_LIBRARY)
LIBFIND_PROCESS(SBML)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

INCLUDE_DIRECTORIES(
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_BINARY_DIR}/include"
)

##
## Inclusion of additional macros, etc.
##
INCLUDE(cmake/UniPAXCompilerSpecific.cmake)

##
## Configuration of external packages
##

#Configure boost
INCLUDE(cmake/UniPAXConfigBoost.cmake)
INCLUDE(cmake/file_copy.cmake)

#Configure Qt4
FIND_PACKAGE(Qt4 REQUIRED)

SET(QT_USE_QTCORE TRUE)
SET(QT_USE_QTXML TRUE)
SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTNETWORK TRUE)
SET(QT_USE_QTGUI TRUE)

INCLUDE(${QT_USE_FILE})


# Configure libSVM
#
# NOTE: I did not make this mandatory as usually the variables for libSVM must
#       be passed on the command line which is simply unconvenient ;-)
#FIND_PACKAGE(LIBSVM)

# Configure libODB
FIND_PACKAGE(ODB REQUIRED)

IF (database STREQUAL "oracle")
	# Configure oracle
	FIND_PACKAGE(ORACLE REQUIRED)
	# Configure libODB-Oracle
	FIND_PACKAGE(ODBORACLE REQUIRED)
ENDIF (database STREQUAL "oracle")

IF (NOT (database STREQUAL "oracle"))
	# Configure MySQL
	FIND_PACKAGE(MYSQL REQUIRED)
	# Configure libODB-MySQL
	FIND_PACKAGE(ODBMYSQL REQUIRED)
ENDIF (NOT (database STREQUAL "oracle"))

# Configure libODB-Boost
FIND_PACKAGE(ODBBOOST REQUIRED)

#configure libSBML
FIND_PACKAGE(SBML REQUIRED)

#configure libemon (lemon)
FIND_PACKAGE(LEMON REQUIRED)


##
## Creation of configure files
##
CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/cmake/config.h.in" "${CMAKE_BINARY_DIR}/include/UNIPAX/CONFIG/config.h")

##
## Inclusion of additional macros/targets/directories
##
OPTION(TESTING_ENABLED "Enable the CTest testing framework" OFF)

IF(TESTING_ENABLED)
	ENABLE_TESTING()
	ADD_SUBDIRECTORY(test EXCLUDE_FROM_ALL)
ENDIF()


#Add the subdirectories that should be built
ADD_SUBDIRECTORY(source)



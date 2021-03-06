### list all filenames of the directory here ###
SET(GROUP REST/GRAPHALGORITHMSERVERHANDLER)

SET(DIRECTORY "${CMAKE_SOURCE_DIR}/include/PLUGINS/${GROUP}")

FILE(GLOB HEADERS_LIST "${DIRECTORY}/*.h")	

FILE(GLOB MOCS "${DIRECTORY}/*.h")

LIST(APPEND GraphAlgorithmServerHandler_MOC_HEADERS_LIST ${MOCS})

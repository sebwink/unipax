### list all filenames of the directory here ###
SET(GROUP "GRAPH/LEMON")

SET(DIRECTORY "${CMAKE_SOURCE_DIR}/include/UNIPAX/${GROUP}")

FILE(GLOB HEADERS_LIST "${DIRECTORY}/*.h")	

ADD_UNIPAX_HEADERS("${GROUP}" "${HEADERS_LIST}")

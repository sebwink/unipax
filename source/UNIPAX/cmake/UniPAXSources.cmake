SET(UNIPAX_sources CACHE INTERNAL "This variable should hold all UniPAX sources at the end of the config step")
SET(UNIPAX_headers CACHE INTERNAL "This variable should hold all UniPAX headers at the end of the config step")

#We also need the header files as dependency because of various reasons:
# - Build solution generators (e.g. Visual Studio, Eclipse)
# - Dependency checking

INCLUDE(KERNEL/sources.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/include/UNIPAX/KERNEL/sources.cmake)
INCLUDE(PERSISTENCE/sources.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/include/UNIPAX/PERSISTENCE/sources.cmake)
INCLUDE(COMMON/sources.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/include/UNIPAX/COMMON/sources.cmake)
INCLUDE(IMPORT/sources.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/include/UNIPAX/IMPORT/sources.cmake)
INCLUDE(SERVER/sources.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/include/UNIPAX/SERVER/sources.cmake)

INCLUDE(GRAPH/sources.cmake)
INCLUDE(${CMAKE_SOURCE_DIR}/include/UNIPAX/GRAPH/sources.cmake)

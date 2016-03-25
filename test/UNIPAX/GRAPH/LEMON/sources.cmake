SET(SOURCES_LIST
	test_RecursiveEnumerationAlgorithm.cpp
)

UNIPAX_ADD_TESTS("UNIPAX/GRAPH/LEMON" ${SOURCES_LIST})

# for searching lokal MOCKS subdirectories:
#INCLUDE_DIRECTORIES("UNIPAX/GRAPH/LEMON/MOCKS")

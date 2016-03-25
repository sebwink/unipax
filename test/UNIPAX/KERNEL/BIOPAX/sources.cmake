SET(SOURCES_LIST
	teststub.cpp
	test_BindingFeature.cpp
	test_BioSource.cpp
)

UNIPAX_ADD_TESTS("UNIPAX/KERNEL/BIOPAX" ${SOURCES_LIST})

# for searching lokal MOCKS subdirectories:
INCLUDE_DIRECTORIES("UNIPAX/KERNEL/BIOPAX/MOCKS")

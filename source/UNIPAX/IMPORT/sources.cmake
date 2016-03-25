INCLUDE("IMPORT/BIOPAX/sources.cmake")
INCLUDE("IMPORT/SBML/sources.cmake")
INCLUDE("IMPORT/GENESET/sources.cmake")
INCLUDE("IMPORT/TFENCYCLOPEDIA/sources.cmake")
INCLUDE("IMPORT/GRAPHML/sources.cmake")
INCLUDE("IMPORT/MZTAB/sources.cmake")

SET(SOURCES_LIST
	UniProtReader.cpp
	BridgeDBWrapper.cpp
	BridgeDBLinkREST.cpp
)

ADD_UNIPAX_SOURCES("IMPORT" "${SOURCES_LIST}")

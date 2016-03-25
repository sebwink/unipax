SET(SOURCES_LIST
  PersistenceManager.cpp
  KernelCollector.cpp
  DBConnector.cpp
  KernelClassSet.cpp
  OrganismSet.cpp
  PathwaySet.cpp
  MergerInputAdapter.cpp
)

ADD_UNIPAX_SOURCES("COMMON" "${SOURCES_LIST}")

## Add the header files in HEADERS_LIST to the list
## of files compiled into libUniPAX, and mark them as
## part of source group GROUP
MACRO(ADD_UNIPAX_HEADERS GROUP HEADERS_LIST)
	SET(DIRECTORY ${CMAKE_SOURCE_DIR}/include/UNIPAX/${GROUP})

	### add full path to the filenames ###
	SET(HEADERS)
	FOREACH(i ${HEADERS_LIST})
		### make sure we do not have absolute paths flying around...
		GET_FILENAME_COMPONENT(i ${i} NAME)
		LIST(APPEND HEADERS ${DIRECTORY}/${i})
	ENDFOREACH()

	### pass source file list to the upper instance ###
	SET(UNIPAX_headers ${UNIPAX_headers} ${HEADERS})

	### source group definition ###
	STRING(REGEX REPLACE "/" "\\\\" S_GROUP ${GROUP})
	SOURCE_GROUP("Header Files\\\\${S_GROUP}" FILES ${HEADERS})
ENDMACRO()

## Add the source files in SOURCES_LIST to the list
## of files compiled into libUniPAX, and mark them as
## part of source group GROUP
MACRO(ADD_UNIPAX_SOURCES GROUP SOURCES_LIST)
	SET(DIRECTORY ${GROUP})

	### add full path to the filenames ###
	SET(SOURCES)
	FOREACH(i ${SOURCES_LIST})
		LIST(APPEND SOURCES ${DIRECTORY}/${i})
	ENDFOREACH()

	### pass source file list to the upper instance ###
	SET(UNIPAX_sources ${UNIPAX_sources} ${SOURCES})

	### source group definition ###
	STRING(REGEX REPLACE "/" "\\\\" S_GROUP ${GROUP})
	SOURCE_GROUP("Source Files\\\\${S_GROUP}" FILES ${SOURCES})
ENDMACRO()

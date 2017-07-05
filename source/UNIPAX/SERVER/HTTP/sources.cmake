SET(SOURCES_LIST
qhttpconnection.cpp
qhttprequest.cpp
qhttpresponse.cpp
qhttpserver.cpp
http_parser.c
RequestHandler.cpp
)

ADD_UNIPAX_SOURCES("SERVER/HTTP" "${SOURCES_LIST}")



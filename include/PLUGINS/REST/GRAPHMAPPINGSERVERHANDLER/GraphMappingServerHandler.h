#ifndef GRAPHMAPPINGSERVERHANDLER_H_
#define GRAPHMAPPINGSERVERHANDLER_H_

#include <UNIPAX/SERVER/REST/RESTServerHandler.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>

#ifdef ODB_MYSQL
#include <UNIPAX/GRAPH/MAPPING/MYSQL/MySQLMappingEngine.h>
#elif defined ODB_ORACLE
#include <UNIPAX/GRAPH/MAPPING/ORACLE/OracleMappingEngine.h>
#endif

#include <boost/shared_ptr.hpp>

#include <QObject>
#include <vector>



class GraphMappingServerHandler : public QObject, protected UniPAX::SERVER::RESTServerHandler
{
	Q_OBJECT
	Q_INTERFACES(UniPAX::SERVER::RESTServerHandler)

public:

	GraphMappingServerHandler();

	~GraphMappingServerHandler();

	QString help(QString format = "");

	bool handle(QHttpRequest *req, QHttpResponse *resp);

	void init(boost::program_options::variables_map & _vm);

private:

	bool _rebuild_mapping_index;

#ifdef ODB_MYSQL
	boost::shared_ptr<UniPAX::GRAPH::mysql::MySQLMappingEngine> mapping_engine;
#elif defined ODB_ORACLE
	boost::shared_ptr<UniPAX::GRAPH::oracle::OracleMappingEngine> mapping_engine;
#endif

	static QRegExp graph_ppi, graph_regulatory, graph_metabolic;
};


#endif /* GRAPHMAPPINGSERVERHANDLER_H_ */

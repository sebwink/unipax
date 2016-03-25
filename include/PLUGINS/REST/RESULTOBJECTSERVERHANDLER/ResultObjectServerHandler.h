#ifndef RESULTOBJECTSERVERHANDLER_H_
#define RESULTOBJECTSERVERHANDLER_H_

#include <UNIPAX/SERVER/REST/RESTServerHandler.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>
#include <UNIPAX/COMMON/DBConnector.h>

#include <QObject>
#include <vector>


class ResultObjectServerHandler : public QObject, protected UniPAX::SERVER::RESTServerHandler
{
	Q_OBJECT
	Q_INTERFACES(UniPAX::SERVER::RESTServerHandler)

public:

	ResultObjectServerHandler();

	~ResultObjectServerHandler();

	QString help(QString format = "");

	void init(boost::program_options::variables_map & _vm);

	bool handle(QHttpRequest *req, QHttpResponse *resp);

private:

	static QRegExp filter, add, subtract, intersect, add_data, map_data, list, label, gmt;
	UniPAX::DBConnectorPtr dbc;
	static const int max_ids = 100000; // restriction to prevent delay of the service
};


#endif /* RESULTOBJECTSERVERHANDLER_H_ */

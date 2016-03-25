#ifndef GETOBJECTSERVERHANDLER_H_
#define GETOBJECTSERVERHANDLER_H_

#include <UNIPAX/SERVER/REST/RESTServerHandler.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>

#include <QObject>
#include <vector>


class GetObjectServerHandler : public QObject, protected UniPAX::SERVER::RESTServerHandler
{
	Q_OBJECT
	Q_INTERFACES(UniPAX::SERVER::RESTServerHandler)

public:

	GetObjectServerHandler();

	~GetObjectServerHandler();

	QString help(QString format = "");

	void init(boost::program_options::variables_map & _vm);

	bool handle(QHttpRequest *req, QHttpResponse *resp);

private:

	static QRegExp get, id, datasource, all, all_types, info_xrefs;
};


#endif /* GETOBJECTSERVERHANDLER_H_ */

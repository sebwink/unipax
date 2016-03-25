#ifndef PATHWAYSOFSERVERHANDLER_H_
#define PATHWAYSOFSERVERHANDLER_H_

#include <UNIPAX/SERVER/REST/RESTServerHandler.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>

#include <QObject>
#include <vector>


class PathwaysOfServerHandler : public QObject, protected UniPAX::SERVER::RESTServerHandler
{
	Q_OBJECT
	Q_INTERFACES(UniPAX::SERVER::RESTServerHandler)

public:

	PathwaysOfServerHandler();

	~PathwaysOfServerHandler();

	QString help(QString format = "");

	void init(boost::program_options::variables_map & _vm);

	bool handle(QHttpRequest *req, QHttpResponse *resp);

private:

	static QRegExp pathwaysOf;
	static QRegExp pathwaysOfAll;

};


#endif /* PATHWAYSOFSERVERHANDLER_H_ */

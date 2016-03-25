#ifndef SEARCHSERVERHANDLER_H_
#define SEARCHSERVERHANDLER_H_

#include <UNIPAX/SERVER/REST/RESTServerHandler.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>

#include <QObject>
#include <vector>


class SearchServerHandler : public QObject, protected UniPAX::SERVER::RESTServerHandler
{
	Q_OBJECT
	Q_INTERFACES(UniPAX::SERVER::RESTServerHandler)

public:

	SearchServerHandler();

	~SearchServerHandler();

	QString help(QString format = "");

	void init(boost::program_options::variables_map & _vm);

	bool handle(QHttpRequest *req, QHttpResponse *resp);

private:

	static QRegExp _name, _xref;

};


#endif /* SEARCHSERVERHANDLER_H_ */

#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>

#include <UNIPAX/SERVER/HTTP/qhttpserver.h>
#include <UNIPAX/SERVER/HTTP/qhttprequest.h>
#include <UNIPAX/SERVER/HTTP/qhttpresponse.h>


#include <QStringList>
#include <QRegExp>
#include <QtNetwork/QTcpServer>


namespace UniPAX
{


namespace SERVER
{

class RequestHandler: public QObject {
	Q_OBJECT

public:
	RequestHandler(QHttpRequest *request, QHttpResponse *response);
	~RequestHandler();

	private slots:
	void onEnd();

	signals:
	void requestComplete(QHttpRequest *request, QHttpResponse *response);

	private:
	QHttpRequest * m_request;
	QHttpResponse *m_response;
};

}

}
#endif /* REQUESTHANDLER_H */

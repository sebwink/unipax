#ifndef UNIPAXBROWSER_H
#define UNIPAXBROWSER_H

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>

#include <UNIPAX/SERVER/HTTP/qhttpserver.h>
#include <UNIPAX/SERVER/HTTP/qhttprequest.h>
#include <UNIPAX/SERVER/HTTP/qhttpresponse.h>

#include <UNIPAX/SERVER/HTTP/RequestHandler.h>
#include <UNIPAX/SERVER/BROWSER/UnipaxBrowserHandler.h>

#include <QStringList>
#include <QRegExp>
#include <QtNetwork/QTcpServer>


namespace UniPAX
{


namespace SERVER
{

class UNIPAX_EXPORT UnipaxBrowser : public QObject
{
	Q_OBJECT

public:
	UnipaxBrowser();
	~UnipaxBrowser();


	void setEngine(QueryEngine* engine);

	bool listen(const QHostAddress &address = QHostAddress::Any, quint16 port=0);

	bool listen(quint16 port=0);



	private slots:

	void handle(QHttpRequest *req, QHttpResponse *resp);
	void handleRequestComplete(QHttpRequest *req, QHttpResponse *resp);

	private:

	QueryEngine* engine;

	std::vector<std::pair<UnipaxBrowserHandler*, std::vector<QRegExp> > > handlers;

};

}
}
#endif /* UNIPAXBROWSER_H */

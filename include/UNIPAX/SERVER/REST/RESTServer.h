#ifndef RESTSERVER_H
#define RESTSERVER_H

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>

#include <UNIPAX/SERVER/HTTP/qhttpserver.h>
#include <UNIPAX/SERVER/HTTP/qhttprequest.h>
#include <UNIPAX/SERVER/HTTP/qhttpresponse.h>

#include <UNIPAX/SERVER/HTTP/RequestHandler.h>
#include <UNIPAX/SERVER/REST/RESTServerHandler.h>

#include <QStringList>
#include <QRegExp>
#include <QtNetwork/QTcpServer>


namespace UniPAX
{


namespace SERVER
{

class UNIPAX_EXPORT RESTServer : public QObject
{
	Q_OBJECT

public:
	RESTServer();
	~RESTServer();


	void setEngine(QueryEngine* engine);

	void loadPlugins();

	void initPlugins(boost::program_options::variables_map & vm);

	bool listen(const QHostAddress &address = QHostAddress::Any, quint16 port=0);

	bool listen(quint16 port=0);

	void addPluginsDirectory(std::string dir);

	std::vector<RESTServerHandler*> & getPlugins()
			{
		return loaded_plugins;
			}

	RESTServerHandler* getPlugin(std::string name)
	{
		for (std::vector<RESTServerHandler*>::const_iterator it = loaded_plugins.begin(); it != loaded_plugins.end(); ++it)
		{
			if ((*it)->name() == name.c_str())
				return *it;
		}

		return 0;
	}

	private slots:

	void handle(QHttpRequest *req, QHttpResponse *resp);
	void handleRequestComplete(QHttpRequest *req, QHttpResponse *resp);

	private:

	std::set<std::string> plugin_directories;

	std::vector<RESTServerHandler*> loaded_plugins;

	QueryEngine* engine;

	std::vector<std::pair<RESTServerHandler*, std::vector<QRegExp> > > handlers;

};

}

}
#endif /* RESTSERVER_H */

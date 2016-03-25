#include <UNIPAX/SERVER/REST/RESTServer.h>

#include <stdlib.h>

#include <QtXml>

#include <QPluginLoader>

UniPAX::SERVER::RequestHandler::RequestHandler(QHttpRequest *request, QHttpResponse *response): m_request(request), m_response(response)
{
    m_request->storeBody();
    connect(m_request, SIGNAL(end()), this, SLOT(onEnd()));
    connect(m_response, SIGNAL(done()), this, SLOT(deleteLater()));
}

UniPAX::SERVER::RequestHandler::~RequestHandler()
{
    delete m_request;
}

void UniPAX::SERVER::RequestHandler::onEnd()
{
    Q_EMIT requestComplete(m_request, m_response);
}


UniPAX::SERVER::RESTServer::RESTServer()
{

}

UniPAX::SERVER::RESTServer::~RESTServer()
{
	engine = 0;
}

void UniPAX::SERVER::RESTServer::addPluginsDirectory(std::string dir)
{
	plugin_directories.insert(dir);
}

void UniPAX::SERVER::RESTServer::loadPlugins()
{

	for (std::set<std::string>::const_iterator it = plugin_directories.begin(); it != plugin_directories.end(); ++it)
	{
		QDir pluginsDir(QString::fromStdString(*it));

		std::cout << "Loading plugins from " << pluginsDir.absolutePath().toStdString() << std::endl;

		foreach (QString fileName, pluginsDir.entryList(QDir::Files))
		{
			QString file = pluginsDir.absoluteFilePath(fileName);

			QPluginLoader loader(file);

			QObject *plugin = loader.instance();
			if (plugin) {
				RESTServerHandler* handler = qobject_cast<RESTServerHandler*>(plugin);
				if (handler)
				{
					loaded_plugins.push_back(handler);

					std::cout << "\t Loaded plugin " << handler->name().toStdString() << std::endl;
				}
			} else
			{
				std::cout << loader.errorString().toStdString()  << std::endl;
			}
		}
	}

}


void UniPAX::SERVER::RESTServer::initPlugins(boost::program_options::variables_map & vm)
{

	for (std::vector<RESTServerHandler*>::const_iterator it = loaded_plugins.begin(); it != loaded_plugins.end(); ++it)
	{
		RESTServerHandler* handler = *it;

		std::pair<RESTServerHandler*, std::vector<QRegExp> > entry(handler, std::vector<QRegExp>());

		foreach (QRegExp exp, handler->pattern())
		{
			if (exp.isValid() && !exp.isEmpty())
				entry.second.push_back(exp);

		}

		if (!entry.second.empty())
		{
			handlers.push_back(entry);
			handler->setEngine(engine);
			handler->init(vm);
		}
	}

}

void UniPAX::SERVER::RESTServer::handle(QHttpRequest *req, QHttpResponse *resp)
{
	RequestHandler * h = new RequestHandler(req, resp);
	connect(h, SIGNAL(requestComplete(QHttpRequest*,QHttpResponse*)), this, SLOT(handleRequestComplete(QHttpRequest*,QHttpResponse*)));
}

void UniPAX::SERVER::RESTServer::handleRequestComplete(QHttpRequest *req, QHttpResponse *resp)
//void UniPAX::SERVER::RESTServer::handle(QHttpRequest *req, QHttpResponse *resp)
{

	QString path(req->path());

	if (path.startsWith("/help"))
	{
		QByteArray output;
		output.append("<html><head></head><body>");
		output.append("<b>UniPAX Webservice Help</b></br></br>");
		output.append("<table>");
		for (std::vector<std::pair<RESTServerHandler*, std::vector<QRegExp> > >::const_iterator it = handlers.begin(); it != handlers.end(); it++)
		{
			QString help = it->first->help("html");
			output.append(help);
			output.append("<tr><td colspan=2></td></tr>");
		}
		output.append("</table></body></html>");
		resp->setHeader("Content-Type", "text/html; charset=UTF-8");
		resp->writeHead(200);
		resp->write(output);
		resp->end();
		return;
	} else if (path.startsWith("/plugins")) {
		QByteArray output;
		for (std::vector<std::pair<RESTServerHandler*, std::vector<QRegExp> > >::const_iterator it = handlers.begin(); it != handlers.end(); it++)
		{
			QString name = it->first->name();
			output.append(name + "\n");
		}
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(output);
		resp->end();
		return;
	}


	for (std::vector<std::pair<RESTServerHandler*, std::vector<QRegExp> > >::const_iterator it = handlers.begin(); it != handlers.end(); it++)
	{

		bool match = false;

		for (std::vector<QRegExp>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			if (it2->exactMatch(path))
			{
				match = true;
				break;
			}
		}

		if (match)
		{
			std::cout << "Forwarding " << req->url().toString().toStdString() << " to " << it->first->name().toStdString() << "." << std::endl;

			if (it->first->handle(req, resp))
			{
				return;
			}
		}
	}

	resp->writeHead(405);
	resp->end();
}

void UniPAX::SERVER::RESTServer::setEngine(QueryEngine* _engine)
{
	engine = _engine;
}

bool UniPAX::SERVER::RESTServer::listen(const QHostAddress &address, quint16 port)
{
	QHttpServer *server = new QHttpServer;
	connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)), this, SLOT(handle(QHttpRequest*, QHttpResponse*)));
	return server->listen(address, port);
}

bool UniPAX::SERVER::RESTServer::listen(quint16 port)
{
    return listen(QHostAddress::Any, port);
}



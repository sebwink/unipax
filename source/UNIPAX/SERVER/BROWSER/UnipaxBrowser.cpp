#include <UNIPAX/SERVER/BROWSER/UnipaxBrowser.h>

#include <stdlib.h>

#include <QtXml>

#include <QPluginLoader>


UniPAX::SERVER::UnipaxBrowser::UnipaxBrowser()
{

}

UniPAX::SERVER::UnipaxBrowser::~UnipaxBrowser()
{
	engine = 0;
}


void UniPAX::SERVER::UnipaxBrowser::handle(QHttpRequest *req, QHttpResponse *resp)
{
	RequestHandler * h = new RequestHandler(req, resp);
	connect(h, SIGNAL(requestComplete(QHttpRequest*,QHttpResponse*)), this, SLOT(handleRequestComplete(QHttpRequest*,QHttpResponse*)));
}

void UniPAX::SERVER::UnipaxBrowser::handleRequestComplete(QHttpRequest *req, QHttpResponse *resp)
//void UniPAX::SERVER::UnipaxBrowser::handle(QHttpRequest *req, QHttpResponse *resp)
{

	QString path(req->path());

	if (path.startsWith("/help"))
	{
		QByteArray output;
		output.append("<html><head></head><body>");
		output.append("<b>UniPAX Webservice Help</b></br></br>");
		output.append("<table>");
		for (std::vector<std::pair<UnipaxBrowserHandler*, std::vector<QRegExp> > >::const_iterator it = handlers.begin(); it != handlers.end(); it++)
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
		for (std::vector<std::pair<UnipaxBrowserHandler*, std::vector<QRegExp> > >::const_iterator it = handlers.begin(); it != handlers.end(); it++)
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


	for (std::vector<std::pair<UnipaxBrowserHandler*, std::vector<QRegExp> > >::const_iterator it = handlers.begin(); it != handlers.end(); it++)
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

void UniPAX::SERVER::UnipaxBrowser::setEngine(QueryEngine* _engine)
{
	engine = _engine;
}

bool UniPAX::SERVER::UnipaxBrowser::listen(const QHostAddress &address, quint16 port)
{
	QHttpServer *server = new QHttpServer;
	connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)), this, SLOT(handle(QHttpRequest*, QHttpResponse*)));
	return server->listen(address, port);
}

bool UniPAX::SERVER::UnipaxBrowser::listen(quint16 port)
{
    return listen(QHostAddress::Any, port);
}



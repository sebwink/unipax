#include <PLUGINS/REST/PATHWAYSOFSERVERHANDLER/PathwaysOfServerHandler.h>

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#include <UNIPAX/IMPORT/GRAPHML/GraphMLWriter.h>
#include <UNIPAX/IMPORT/GENESET/GeneSetWriter.h>
#include <UNIPAX/COMMON/KernelCollector.h>

#include <stdlib.h>
#include <sstream>
#include <time.h>

#include <QtXml>

#include <QtCore/qplugin.h>

QRegExp PathwaysOfServerHandler::pathwaysOf("/pathwaysOf/([0-9]|[a-zA-Z])+(,([0-9]|[a-zA-Z])+)*", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp PathwaysOfServerHandler::pathwaysOfAll("/pathwaysOfAll/", Qt::CaseSensitive, QRegExp::RegExp2);

PathwaysOfServerHandler::PathwaysOfServerHandler() : RESTServerHandler("Pathways Of Server Handler")
{
	_pattern.push_back(PathwaysOfServerHandler::pathwaysOf);
	_pattern.push_back(PathwaysOfServerHandler::pathwaysOfAll);
}


PathwaysOfServerHandler::~PathwaysOfServerHandler()
{
	engine = 0;
}

void PathwaysOfServerHandler::init(boost::program_options::variables_map & _vm)
{
}

QString PathwaysOfServerHandler::help(QString format)
{
	if (format == "html")
	{
		return QString("<tr><td colspan=2><b>Get pathways of objects:</b></td></tr>")
					.append("<tr><td valign=top><b>/pathwaysOf</b></td><td>")
						.append("Returns one or more pathways containing the object from the database.<br/>")
						.append("<br/>")
						.append("<b>Syntax:</b> /pathwaysOf/&lt;id&gt;?&lt;parameters&gt;<br/>")
						.append("<br/>")
						.append("<b>Parameters:</b> ")
						.append("<ul>")
						.append("<li>type - specifies the type of the id (geneid | unipaxid)</li>")
						.append("</ul>")
					.append("</td></tr>")
					.append("<tr><td valign=top><b>/pathwaysOfAll/</b></td><td>")
						.append("Returns for list of all genes and the pathway in which they occur. <br/>")
						.append("<br/>")
						.append("</td></tr>");
	}

	return "";

}

bool PathwaysOfServerHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{
	QString path(req->path());

	std::cout << path.toStdString() << std::endl;

	if( PathwaysOfServerHandler::pathwaysOf.exactMatch(path) )
	{
		QString parameter = path.section('/', 2, 3);
		QStringList ids = parameter.split(",");
		QString type = req->url().queryItemValue("type");

		QByteArray output;
		if (type == "geneid") {
			if (engine->getPathwaysOfGeneIDs(output, ids))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(200);
				resp->write(output);
			}
			else
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(output);
			}
		}
		else {
			if (engine->getPathwaysOfs(output, ids))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(200);
				resp->write(output);
			}
			else
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(output);
			}
		}
		resp->end();
	}
	else if( PathwaysOfServerHandler::pathwaysOfAll.exactMatch(path) )
	{
//		QString id = path.section('/', 2, 3);

		QByteArray output;
		if (engine->getPathwaysOfAllGeneIDs(output))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(200);
			resp->write(output);
		}
		else
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(output);
		}
		resp->end();
	}

	return false;
}

Q_EXPORT_PLUGIN2(PathwaysOfServerHandler, PathwaysOfServerHandler)


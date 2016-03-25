#include <PLUGINS/REST/SEARCHSERVERHANDLER/SearchServerHandler.h>

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#include <UNIPAX/IMPORT/GRAPHML/GraphMLWriter.h>
#include <UNIPAX/IMPORT/GENESET/GeneSetWriter.h>
#include <UNIPAX/COMMON/KernelCollector.h>

#include <stdlib.h>

#include <QtCore/qplugin.h>

QRegExp SearchServerHandler::_name("/name/.+", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp SearchServerHandler::_xref("/xref/.+/.+", Qt::CaseSensitive, QRegExp::RegExp2);

SearchServerHandler::SearchServerHandler() : RESTServerHandler("Search Object Handler")
{
	_pattern.push_back(SearchServerHandler::_name);
	_pattern.push_back(SearchServerHandler::_xref);
}


SearchServerHandler::~SearchServerHandler()
{

}

void SearchServerHandler::init(boost::program_options::variables_map & _vm)
{
}

QString SearchServerHandler::help(QString format)
{
	if (format == "html")
	{
		return 	QString("<tr><td colspan=2><b>Search for objects by name or description:</b></td></tr>")
				.append("<tr><td>name</td><td>Returns a list of matching objects.</td></tr>");
	}

	return "";

}

bool SearchServerHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{
	QString path(req->path());

	if( SearchServerHandler::_name.exactMatch(path) )
	{
		QString name = path.section('/', 2, 3);

		std::map<UnipaxId, std::string> result_name;
		engine->getUnipaxIdsByName(result_name, name);

		std::set<UnipaxId> ids;
		for (std::map<UnipaxId, std::string>::iterator it = result_name.begin(); it != result_name.end(); ++it)
		{
			ids.insert(it->first);
		}

		QString format = req->url().queryItemValue("format");
		if (format == "")
			format = "ids";

		respond(req, resp, ids, format);
	}
	else if ( SearchServerHandler::_xref.exactMatch(path) )
	{
		QString db = path.section('/', 2, 2);
		QString id = path.section('/', 3, 3);

		std::set<UnipaxId> result;
		engine->getUnipaxIdsByXref(result, db, id);

		QString format = req->url().queryItemValue("format");
		if (format == "")
			format = "ids";

		respond(req, resp, result, format);
	}


	return false;
}

Q_EXPORT_PLUGIN2(SearchServerHandler, SearchServerHandler)


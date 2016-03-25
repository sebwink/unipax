#include <PLUGINS/REST/RESULTOBJECTSERVERHANDLER/ResultObjectServerHandler.h>

#include <UNIPAX/COMMON/OrganismSet.h>
#include <UNIPAX/COMMON/PathwaySet.h>
#include <UNIPAX/COMMON/KernelClassSet.h>
#include <UNIPAX/KERNEL/EXT/ResultObject.h>
#include <UNIPAX/KERNEL/all.h>

#include <UNIPAX/COMMON/Singleton.h>
#include <UNIPAX/IMPORT/SBML/MiriamLinkREST.h>

#include <UNIPAX/PERSISTENCE/DBManager.h>
#include <UNIPAX/SERVER/HTTP/qhttpconnection.h>

#include <stdlib.h>
#include <sstream>
#include <time.h>

#include <QtXml>

#include <QtCore/qplugin.h>
#include <QtNetwork>

QRegExp ResultObjectServerHandler::filter("/filter", Qt::CaseSensitive, QRegExp::RegExp2);

QRegExp ResultObjectServerHandler::add("/add", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp ResultObjectServerHandler::subtract("/subtract", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp ResultObjectServerHandler::intersect("/intersect", Qt::CaseSensitive, QRegExp::RegExp2);

QRegExp ResultObjectServerHandler::add_data("/add/data", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp ResultObjectServerHandler::map_data("/map/data", Qt::CaseSensitive, QRegExp::RegExp2);

QRegExp ResultObjectServerHandler::list("/list", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp ResultObjectServerHandler::label("/label", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp ResultObjectServerHandler::gmt("/gmt", Qt::CaseSensitive, QRegExp::RegExp2);


ResultObjectServerHandler::ResultObjectServerHandler() : RESTServerHandler("ResultObject Server Handler")
{

	_pattern.push_back(ResultObjectServerHandler::filter);
	_pattern.push_back(ResultObjectServerHandler::add);
	_pattern.push_back(ResultObjectServerHandler::subtract);
	_pattern.push_back(ResultObjectServerHandler::intersect);
	_pattern.push_back(ResultObjectServerHandler::add_data);
	_pattern.push_back(ResultObjectServerHandler::map_data);
	_pattern.push_back(ResultObjectServerHandler::list);
	_pattern.push_back(ResultObjectServerHandler::label);
	_pattern.push_back(ResultObjectServerHandler::gmt);
}


ResultObjectServerHandler::~ResultObjectServerHandler()
{
	engine = 0;
}

void ResultObjectServerHandler::init(boost::program_options::variables_map & _vm)
{
	dbc = UniPAX::DBConnectorPtr(new UniPAX::DBConnector());
	dbc->setEngine(UnipaxPtr<UniPAX::SERVER::QueryEngine>::type(engine));
}

QString ResultObjectServerHandler::help(QString format)
{
	if (format == "html")
	{
		return 	QString("<tr><td colspan=2><b>Create ResultObjects by filtering, uniting, subtracting, disection. Add experimental data. List the contents:</b></td></tr>")
				// filter
				.append("<tr><td valign=top><b>/filter</b></td><td>")
				.append("Returns the id of the ResultObject created by filtering.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /filter?organism=&lt;name/id&gt;,...&pathway=&lt;name/id&gt;,...&type=&lt;name/id&gt;,...<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>organism - specifies the organism to which the filtered objects shall belong to. Can be a list. Can be empty.</li>")
				.append("<li>pathway - specifies the pathway to which the filtered objects shall belong to. Can be a list. Can be empty.</li>")
				.append("<li>type - specifies the type of which all of the objects shall be. Can be a list. Can be empty.</li>")
				.append("</ul>")
				.append("</td></tr>")
				// add
				.append("<tr><td valign=top><b>/add</b></td><td>")
				.append("Returns the id of the ResultObject created by addition of existing ResultObjects.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /add?results=&lt;ResultObject id&gt;,...<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>results - specifies the ResultObjects which to add to create a new ResultObject. Can be a list. Can not be empty.</li>")
				.append("</ul>")
				.append("</td></tr>")
				// subtract
				.append("<tr><td valign=top><b>/subtract</b></td><td>")
				.append("Returns the id of the ResultObject created by subtraction of existing ResultObjects.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /subtract?from=&lt;ResultObject id&gt;&results=&lt;ResultObject id&gt;,...<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>from - specifies the minuend ResultObject. Can not be empty.</li>")
				.append("<li>results - specifies the subtrahend ResultObject(s). Can be a list. Can not be empty.</li>")
				.append("</ul>")
				.append("</td></tr>")
				// intersect
				.append("<tr><td valign=top><b>/intersect</b></td><td>")
				.append("Returns the id of the ResultObject created by intersection of existing ResultObjects.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /intersect?results=&lt;ResultObject id&gt;,...<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>results - specifies the ResultObjects which to intersect to create a new ResultObject. Can be a list. Can not be empty.</li>")
				.append("</ul>")
				.append("</td></tr>")
				// add_data
				.append("<tr><td valign=top><b>/add/data</b></td><td>")
				.append("Returns the id of the ResultObject created by addition of existing 'Series' objects.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /add/data?result=&lt;ResultObject id&gt;&series=&lt;Series id&gt;,...<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>result - specifies the id of a 'ResultObject' to which the data should be added. Can not be empty.</li>")
				.append("<li>series - specifies the ids of 'Series' objects which to add to a new ResultObject. Can be a list. Can not be empty.</li>")
				.append("</ul>")
				.append("</td></tr>")
				// map_data
				.append("<tr><td valign=top><b>/map/data</b></td><td>")
				.append("Returns the id of the ResultObject created by mapping of the IDs in attached 'Series' objects.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /map/data?result=&lt;ResultObject id&gt;&from=&lt;ID system&gt;&to=&lt;ID system&gt;<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>result - specifies the id of a 'ResultObject' which data should be mapped. Can not be empty.</li>")
				.append("<li>from - specifies the primal ID system of the 'Series' data. Can be 'auto' for auto detection. Can not be empty.</li>")
				.append("<li>to - specifies the target ID system of the 'Series' data. Can not be empty.</li>")
				.append("</ul>")
				.append("</td></tr>")
				// list
				.append("<tr><td valign=top><b>/list</b></td><td>")
				.append("Returns the contents of the ResultObject as a list.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /list?result=&lt;ResultObject id&gt;&format=(info|attributes|ids)&attributes=(&lt;attr&gt;:&lt;attr&gt;:...)<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>result - specifies the id of a 'ResultObject' for which the contents should be listed. Can not be empty.</li>")
				.append("<li>format - specifies the output format. 'info' gives information about the object, 'attributes' see below, 'ids' gives back a list of all contained ids.</li>")
				.append("<li>attributes - only if format=attributes, which attributes to show, separated by ':'.<br/>Available attributes: type, name/standardName, organism, displayName</li>")
				.append("</ul>")
				.append("</td></tr>")
				// label
				.append("<tr><td valign=top><b>/label</b></td><td>")
				.append("Sets the label of a ResultObject.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /label?result=&lt;ResultObject id&gt;&label=&lt;text&gt;<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>result - specifies the id of a 'ResultObject' for which the contents should be listed. Can not be empty.</li>")
				.append("<li>label - some label text.</li>")
				.append("</ul>")
				.append("</td></tr>")
				// gmt
				.append("<tr><td valign=top><b>/gmt	</b></td><td>")
				.append("Returns a file in transposed geneset matrix format for a list of ResultObjects (RO). Each RO defines one set of ids. The name of the set is the description of the RO.<br/>")
				.append("<br/>")
				.append("<b>Syntax 1st form:</b> /gmt?result=&lt;ResultObject id&gt;,...&id_type=&lt;UniProt&gt;<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>result - specifies the ids of 'ResultObjects' from which the gmt file shall be constructed. Can not be empty.</li>")
				.append("<li>id_db - Name of the database from which the ids are originating. Can not be empty.</li>")
				.append("</ul>")
				.append("<b>Syntax 2nd form:</b> /gmt?result=&lt;ResultObject id&gt;&grouping=&lt;pathway&gt;|&lt;xref&gt;&xref_db=&lt;db name&gt;&id_db=&lt;db name&gt;<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>result - specifies the id of a 'ResultObject' containing the ids of entities from which the sets should be generated. Can not be empty.</li>")
				.append("<li>grouping - specifies the grouping criteria for the sets. Can be pathway or xref</li>")
				.append("<li>xref_db - Name of the database from which the ids are originating. Only valid with grouping=xref.</li>")
				.append("<li>id_db - Name of the database from which the ids are originating. Can not be empty.</li>")
				.append("</ul>")
				.append("</td></tr>");
	}

	return "";

}

bool ResultObjectServerHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{
	QString path(req->path());

	if ( ResultObjectServerHandler::filter.exactMatch(path) )
	{
		//		QString cacheString = "filter:";
		//
		//		UniPAX::ResultObjectPtr result = 0;
		//
		//		QString existing_resultset = req->url().queryItemValue("result");
		//
		//		if (existing_resultset != "")
		//		{
		//			bool ok;
		//			UnipaxId id = existing_resultset.toULongLong(&ok);
		//			if (UniPAX::DBManager::isType(id, UniPAX::ClassType::idResultObject))
		//			{
		//				result = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(id));
		//			}
		//
		//			if (!result.get())
		//			{
		//				// organism *it neither valid ID.
		//				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		//				resp->writeHead(404);
		//				resp->write(QString("ERROR: '%1' is not a valid result set id.\n").arg(existing_resultset));
		//				resp->end();
		//				return true;
		//			}
		//
		//			cacheString.append(existing_resultset);
		//		}
		//
		//		if (result == 0)
		//		{
		//			result = ResultObjectPtr(new UniPAX::ResultObject());
		//
		//
		//
		//			cacheString.append("all");
		//		}

		// construct org_set
		UniPAX::OrganismSet org_set(dbc);
		{
			QStringList organisms = req->url().queryItemValue("organism").split(",", QString::SkipEmptyParts);
			for (QStringList::iterator it = organisms.begin(); it != organisms.end(); ++it)
			{
				QString name = it->replace(QString("%20"), QString(" "));

				bool ok;
				UnipaxId id = name.toULongLong(&ok);
				if (ok && UniPAX::DBManager::isType(id, UniPAX::ClassType::idBioSource))
				{
					if (!org_set.addById(id))
					{
						// organism *it neither valid ID.
						resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
						resp->writeHead(404);
						resp->write(QString("ERROR: '%1' is no valid ID of an organism.\n").arg(id));
						resp->end();
						return true;
					}
				}
				else
				{
					std::map<UnipaxId, std::string> result;

					engine->getUnipaxIdsByName(result, name);

					for (std::map<UnipaxId, std::string>::iterator it2 = result.begin(); it2 != result.end(); ++it2)
					{
						if (UniPAX::DBManager::isType(it2->first, UniPAX::ClassType::idBioSource)) {
							if (!org_set.addById(it2->first))
							{
								// organism *it neither valid name.
								resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
								resp->writeHead(404);
								resp->write(QString("ERROR: '%1' is no valid name of an organism.\n").arg(*it));
								resp->end();
								return true;
							}
						}
					}
				}
			}
		}
		// construct pw_set
		UniPAX::PathwaySet pw_set(dbc);
		{
			QStringList pathways = req->url().queryItemValue("pathway").split(",", QString::SkipEmptyParts);
			for (QStringList::iterator it = pathways.begin(); it != pathways.end(); ++it)
			{
				QString name = it->replace(QString("%20"), QString(" "));

				bool ok;
				UnipaxId id = name.toULongLong(&ok);
				if (ok && UniPAX::DBManager::isType(id, UniPAX::ClassType::idPathway))
				{
					if (!pw_set.addById(id))
					{
						// pathway *it neither valid ID.
						resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
						resp->writeHead(404);
						resp->write(QString("ERROR: '%1' is no valid ID of a pathway.\n").arg(id));
						resp->end();
						return true;
					}
				}
				else
				{
					std::map<UnipaxId, std::string> result;

					engine->getUnipaxIdsByName(result, name);

					for (std::map<UnipaxId, std::string>::iterator it2 = result.begin(); it2 != result.end(); ++it2)
					{
						if (UniPAX::DBManager::isType(it2->first, UniPAX::ClassType::idPathway)) {
							if (!pw_set.addById(it2->first))
							{
								// pathway *it neither valid name.
								resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
								resp->writeHead(404);
								resp->write(QString("ERROR: '")
										.append(*it)
										.append("' is no valid name or ID of a pathway.\n"));
								resp->end();
								return true;
							}
						}
					}
				}
			}
		}
		// construct type_set
		UniPAX::KernelClassSet tp_set(dbc);
		{
			QStringList types = req->url().queryItemValue("type").split(",", QString::SkipEmptyParts);
			for (QStringList::const_iterator it = types.constBegin(); it != types.constEnd(); ++it)
			{
				if (!tp_set.addByName(it->toStdString()))
				{
					bool ok;
					if(!tp_set.addById((UniPAX::ClassType::ID)it->toUInt(&ok)) || !ok)
					{
						// type *it neither valid name nor ID.
						resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
						resp->writeHead(404);
						resp->write(QString("ERROR: '%1' is no valid name or ID of a kernel class.\n").arg(*it));
						resp->end();
						return true;
					}
				}
			}
		}
		// create ResultObject:
		UniPAX::ResultObjectPtr result;
		if (!dbc->resultObjectExists(result, req->queryString()))
		{
			result = dbc->query(org_set, pw_set, tp_set);
			result->setConstitutingQuery(req->queryString().toStdString());
			if (result == 0)
			{
				std::cerr << "ResultObjectServerHandler::handle: ResultObjectPtr == 0." << std::endl;
				return false;
			}
			if (result->isEmpty())
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("No object matches the selected filter criteria.\n"));
				resp->end();
				return true;
			}
			if (!dbc->persist(result))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(500);
				resp->write(QString("ERROR: Created ResultObject could not be persisted."));
				resp->end();
				return true;
			}
			if (!dbc->update(result))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(500);
				resp->write(QString("ERROR: Created ResultObject could not be updated."));
				resp->end();
				return true;
			}
		}
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(QString::number(result->getUnipaxId()));
		resp->end();
		return true;
	}

	else if ( ResultObjectServerHandler::add.exactMatch(path) )
	{
		QStringList results = req->url().queryItemValue("results").split(",");
		if (results.size() < 2)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'add' needs at least two ResultObject ids as arguments."));
			resp->end();
			return true;
		}
		UniPAX::ResultObjectPtr result_union, result_a;
		for (QStringList::iterator it = results.begin(); it != results.end(); ++it)
		{
			bool ok;
			UnipaxId result_id = it->toULongLong(&ok);
			if (!ok)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not convert '%1' to a UnipaxId.").arg(*it));
				resp->end();
				return true;
			}
			if (it == results.begin())
			{
				if (!dbc->isValid(result_id))
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: id '%1' is not a valid id.").arg(*it));
					resp->end();
					return true;
				}
				result_union = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
				if (result_union == 0)
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Could not load ResultObject from id '%1'.").arg(*it));
					resp->end();
					return true;
				}
			}
			else
			{
				UniPAX::ResultObjectPtr result_a = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
				if (result_a == 0)
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Could not load ResultObject from id '%1'.").arg(*it));
					resp->end();
					return true;
				}
				result_union = result_union->clone();// necessary to prevent persistence manager from getting confused about object ids
				result_union->setUnipaxId(0);
				*result_union = result_union->union_(*result_a);
			}
		}
		if (!dbc->resultObjectExists(result_union, req->queryString()))
		{
			result_union->setConstitutingQuery(req->queryString().toStdString());
			dbc->assignId(result_union);
			if (!dbc->persist(result_union))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Created ResultObject could not be persisted."));
				resp->end();
				return true;
			}
		}
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(QString::number(result_union->getUnipaxId()));
		resp->end();
		return true;

	}
	else if ( ResultObjectServerHandler::subtract.exactMatch(path) )
	{
		QString from = req->url().queryItemValue("from");
		if (from.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'subtract' needs a ResultObject id as 'from' argument."));
			resp->end();
			return true;

		}
		bool ok;
		UnipaxId from_id = from.toULongLong(&ok);
		if (!ok)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not convert '%1' to a UnipaxId.").arg(from));
			resp->end();
			return true;
		}
		UniPAX::ResultObjectPtr result_diff = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(from_id));
		if (result_diff == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not load ResultObject from id '%1'.").arg(from));
			resp->end();
			return true;
		}

		QStringList results = req->url().queryItemValue("results").split(",");
		if (results.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'subtract' needs at least one ResultObject id as 'results' argument."));
			resp->end();
			return true;
		}
		UniPAX::ResultObjectPtr result_a;
		for (QStringList::iterator it = results.begin(); it != results.end(); ++it)
		{
			UnipaxId result_id = it->toULongLong(&ok);
			if (!ok)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not convert '")
						.append(*it)
						.append(QString("' to a UnipaxId.")));
				resp->end();
				return true;
			}
			result_a = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
			if (result_a == 0)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not load ResultObject from id '")
						.append(*it)
						.append(QString("'.")));
				resp->end();
				return true;
			}
			result_diff = result_diff->clone();// necessary to prevent persistence manager from getting confused about object ids
			result_diff->setUnipaxId(0);

			*result_diff = result_diff->difference_(*result_a);
		}
		if (!dbc->resultObjectExists(result_diff, req->queryString()))
		{
			result_diff->setConstitutingQuery(req->queryString().toStdString());
			dbc->assignId(result_diff);
			if (!dbc->persist(result_diff))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Created ResultObject could not be persisted."));
				resp->end();
				return true;
			}
		}
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(QString::number(result_diff->getUnipaxId()));
		resp->end();
		return true;

	}
	else if ( ResultObjectServerHandler::intersect.exactMatch(path) )
	{
		QStringList results = req->url().queryItemValue("results").split(",");
		if (results.size() < 2)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'intersect' needs at least two ResultObject ids as arguments."));
			resp->end();
			return true;
		}
		UniPAX::ResultObjectPtr result_isection, result_a;
		for (QStringList::iterator it = results.begin(); it != results.end(); ++it)
		{
			bool ok;
			UnipaxId result_id = it->toULongLong(&ok);
			if (!ok)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not convert '")
						.append(*it)
						.append(QString("' to a UnipaxId.")));
				resp->end();
				return true;
			}
			if (it == results.begin())
			{
				result_isection = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
				if (result_isection == 0)
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Could not load ResultObject from id '")
							.append(*it)
							.append(QString("'.")));
					resp->end();
					return true;
				}
			}
			else
			{
				result_a = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
				if (result_a == 0)
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Could not load ResultObject from id '")
							.append(*it)
							.append(QString("'.")));
					resp->end();
					return true;
				}
				result_isection = result_isection->clone();// necessary to prevent persistence manager from getting confused about object ids
				result_isection->setUnipaxId(0);
				*result_isection = result_isection->intersection_(*result_a);
			}
		}
		if (!dbc->resultObjectExists(result_isection, req->queryString()))
		{
			result_isection->setConstitutingQuery(req->queryString().toStdString());
			dbc->assignId(result_isection);
			if (!dbc->persist(result_isection))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Created ResultObject could not be persisted."));
				resp->end();
				return true;
			}
		}
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(QString::number(result_isection->getUnipaxId()));
		resp->end();
		return true;

	}
	else if ( ResultObjectServerHandler::add_data.exactMatch(path) )
	{
		QString result = req->url().queryItemValue("result");
		if (result.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'add/data' needs a ResultObject id as 'result' argument."));
			resp->end();
			return true;

		}
		bool ok;
		UnipaxId result_id = result.toULongLong(&ok);
		if (!ok)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not convert '")
					.append(result)
					.append(QString("' to a UnipaxId.")));
			resp->end();
			return true;
		}
		if (!dbc->getEngine()->getDBManager()->isValid(result_id))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: id '")
					.append(result)
					.append(QString("' is not a valid id.")));
			resp->end();
			return true;
		}
		UniPAX::ResultObjectPtr result_obj;
		try
		{
			result_obj = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
		}
		catch (std::bad_cast & e)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: id '")
					.append(result)
					.append(QString("' is not a ResultObject id.")));
			resp->end();
			return true;
		}
		QStringList series = req->url().queryItemValue("series").split(",");
		if (series.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'add/data' needs at least one Series id as 'series' argument."));
			resp->end();
			return true;
		}
		result_obj = result_obj->clone(); // make it a new ResultObject
		for (QStringList::iterator it = series.begin(); it != series.end(); ++it)
		{
			UnipaxId series_id = it->toULongLong(&ok);
			if (!ok)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not convert '")
						.append(*it)
						.append(QString("' to a UnipaxId.")));
				resp->end();
				return true;
			}
			if (!dbc->getEngine()->getDBManager()->isValid(series_id))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: id '")
						.append(result)
						.append(QString("' is not a valid id.")));
				resp->end();
				return true;
			}
			// check if id is a Series object id
			UniPAX::SeriesPtr series_obj;
			try
			{
				series_obj = boost::dynamic_pointer_cast<UniPAX::Series>(dbc->getObject(series_id));
			}
			catch (std::bad_cast & e)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: id '")
						.append(*it)
						.append(QString("' is not a Series id.")));
				resp->end();
				return true;
			}
			catch (std::exception & e)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: ")
						.append(QString(e.what())));
				resp->end();
				return true;
			}
			// add it to the result_obj
			result_obj->setDataSeries(series_obj); // should be add (but only one Series obj possible)
		}
		// serialization of result_obj
		if (!dbc->resultObjectExists(result_obj, req->queryString()))
		{
			result_obj->setUnipaxId(0);
			if (!dbc->assignId(result_obj))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: No ID could be assigned to the created ResultObject."));
				resp->end();
				return true;
			}

			result_obj->setConstitutingQuery(req->queryString().toStdString());
			if (!dbc->persist(result_obj))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Created ResultObject could not be persisted."));
				resp->end();
				return true;
			}
		}
		// report id of new ResultObject
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(QString::number(result_obj->getUnipaxId()));
		resp->end();
		return true;
	}
	else if ( ResultObjectServerHandler::map_data.exactMatch(path) )
	{
		// check ResultObject
		QString result = req->url().queryItemValue("result");
		if (result.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'map/data' needs a ResultObject id as 'result' argument."));
			resp->end();
			return true;

		}
		bool ok;
		UnipaxId result_id = result.toULongLong(&ok);
		if (!ok)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not convert '")
					.append(result)
					.append(QString("' to a UnipaxId.")));
			resp->end();
			return true;
		}
		if (!dbc->isValid(result_id))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: id '")
					.append(result)
					.append(QString("' is not a valid id.")));
			resp->end();
			return true;
		}
		UniPAX::ResultObjectPtr result_obj;
		try
		{
			result_obj = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
		}
		catch (std::bad_cast & e)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: id '")
					.append(result)
					.append(QString("' is not a ResultObject id.")));
			resp->end();
			return true;
		}
		result_obj = result_obj->clone(); // make it a new ResultObject
		UniPAX::SeriesPtr series = result_obj->getDataSeries();
		if (series == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Result object has no attached data series."));
			resp->end();
			return true;
		}
		// check mapping
		QString from_id = req->url().queryItemValue("from").replace(QString("%20"), QString(" "));
		if (from_id.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'map/data' needs the source ID system name as 'from' argument."));
			resp->end();
			return true;
		}
		if (from_id == "auto")
		{
			from_id = QString::fromStdString(series->getIdMappingList().front()->getDbName());
		}
		UniPAX::MiriamLink* miriam = UniPAX::Singleton<UniPAX::MiriamLink>::getInstance(new UniPAX::MiriamLink()).get();
		if (miriam->getDataTypeURIs(from_id.toStdString()).empty())
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: The source ID systems name '").append(from_id).append("' is not MIRIAM compliant."));
			resp->end();
			return true;
		}
		QString to_id = req->url().queryItemValue("to").replace(QString("%20"), QString(" "));
		if (to_id.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'map/data' needs the target ID system name as 'to' argument."));
			resp->end();
			return true;
		}
		if (miriam->getDataTypeURIs(to_id.toStdString()).empty())
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: The target ID systems name '").append(to_id).append("' is not MIRIAM compliant."));
			resp->end();
			return true;
		}
		// check if mapping is supported
		if (!dbc->isMappingSupported(from_id.toStdString(), to_id.toStdString()))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Mapping Ids from '").append(from_id).append("' to '").append(to_id).append("' is not supported."));
			resp->end();
			return true;
		}

		// collect set of IDs from the data series
		std::vector<std::string> src_ids;
		for (std::vector<UniPAX::IdMappingPtr>::const_iterator it = series->getIdMappingList().begin(); it != series->getIdMappingList().end(); ++it)
		{
			if((*it)->getDbName().compare(from_id.toStdString()) == 0)
			{
				for (std::multimap<int, std::string>::iterator id_it = (*it)->getIds().begin(); id_it != (*it)->getIds().end(); ++id_it)
				{
					src_ids.push_back(id_it->second);
				}
			}
		}
		if (src_ids.empty())
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Series object has no id mapping of type '").append(from_id).append("'."));
			resp->end();
			return true;
		}
		std::multimap<std::string, std::string> src_tgtUnipaxIds;
		// mapIds(from_id, src_ids_idx, to_id, idx_unipax_ids)
		if (!dbc->mapIds(from_id.toStdString(), src_ids, to_id.toStdString(), src_tgtUnipaxIds))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Mapping Ids from '").append(from_id).append("' to '").append(to_id).append("' failed."));
			resp->end();
			return true;
		}
		// remove existing IdMappings of selected target type
		for (std::vector<UniPAX::IdMappingPtr>::iterator it = series->getIdMappingList().begin(); it != series->getIdMappingList().end(); ) // deliberately missing increment!!!
		{
			if (*it == 0)
			{
				std::cout << "ResultObjectServerHandler::handle : Empty IdMappingPtr" << std::endl;
			}
			if ((*it)->getDbName().empty())
			{
				std::cout << "ResultObjectServerHandler::handle : Warning, skipping IdMapping "
						<< (*it)->getUnipaxId() << " with empty db_name attribute!" << std::endl;
			}
			if ((*it)->getDbName().compare(to_id.toStdString()) == 0)
			{
				series->getIdMappingList().erase(it);
			}
			else
			{
				++it;
			}
		}
		// create new IdMapping with UniPAX ids
		std::vector<UniPAX::IdMappingPtr> new_mappings;
		for (std::vector<UniPAX::IdMappingPtr>::const_iterator it = series->getIdMappingList().begin(); it != series->getIdMappingList().end(); ++it)
		{
			if (*it == 0)
			{
				std::cout << "ResultObjectServerHandler::handle : Empty IdMappingPtr" << std::endl;
			}
			if ((*it)->getDbName().empty())
			{
				std::cout << "ResultObjectServerHandler::handle : Warning, skipping IdMapping "
						<< (*it)->getUnipaxId() << " with empty db_name attribute!" << std::endl;
				continue;
			}
			if ((*it)->getDbName().compare(from_id.toStdString()) == 0)
			{
				UniPAX::IdMappingPtr mapping(new UniPAX::IdMapping);
				mapping->setSampleIndex((*it)->getSampleIndex());
				mapping->setDbName(to_id.toStdString());
				for (std::multimap<int, std::string>::iterator id_it = (*it)->getIds().begin(); id_it != (*it)->getIds().end(); ++id_it)
				{
					// iff mapping existent insert
					std::pair<std::multimap<std::string, std::string>::iterator, std::multimap<std::string, std::string>::iterator> found = src_tgtUnipaxIds.equal_range(id_it->second);
					for (std::multimap<std::string, std::string>::iterator hit = found.first; hit != found.second; ++hit)
					{
						mapping->getIds().insert(std::pair<int, std::string>(id_it->first, hit->second));
					}
				}
				new_mappings.push_back(mapping);
			}
		}
		for (std::vector<UniPAX::IdMappingPtr>::const_iterator it = new_mappings.begin(); it != new_mappings.end(); ++it)
		{
			dbc->assignId(*it);
			if (!dbc->persist(*it))
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Created IdMapping could not be persisted."));
				resp->end();
				return true;
			}
			series->getIdMappingList().push_back(*it);
		}

		// serialization of series
		if (!dbc->update(result_obj))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Changed ResultObject could not be persisted."));
			resp->end();
			return true;
		}

		// report id of new ResultObject
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(QString::number(result_obj->getUnipaxId()));
		resp->end();
		return true;
	}
	else if ( ResultObjectServerHandler::list.exactMatch(path) )
	{
		QString result = req->url().queryItemValue("result");
		if (result.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'list' needs a ResultObject id as 'result' argument."));
			resp->end();
			return true;

		}
		bool ok;
		UnipaxId result_id = result.toULongLong(&ok);
		if (!ok)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not convert '")
					.append(result)
					.append(QString("' to a UnipaxId.")));
			resp->end();
			return true;
		}
		if (!dbc->isValid(result_id))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: id '")
					.append(result)
					.append(QString("' is not a valid id.")));
			resp->end();
			return true;
		}
		UniPAX::ResultObjectPtr result_obj;
		try
		{
			std::cout << "Loading result object " << result.toStdString() << "... " << std::flush;
			result_obj = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
			std::cout << "done." << std::endl;
		}
		catch (std::bad_cast & e)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: id '")
					.append(result)
					.append(QString("' is not a ResultObject id.")));
			resp->end();
			return true;
		}
		// output format
		QString format = req->url().queryItemValue("format").toLower();
		if (format == "info")
		{
			QString body("ResultObject id:\t");
			body.append(QString::number(result_obj->getUnipaxId()))
												.append(QString("\n"))
												.append(QString("constituting query:\t"))
												.append(QString::fromStdString(result_obj->getConstitutingQuery()))
												.append(QString("\n"))
												.append(QString("creation time:\t"))
												.append(QString::fromStdString(boost::posix_time::to_simple_string(result_obj->getCreationTime())))
												.append(QString("\n"))
												.append(QString("description:\t"))
												.append(QString::fromStdString(result_obj->getDescription())).append(QString("\n"))
												.append(QString("number of unipaxIds: "))
												.append(QString::number(result_obj->getObjectIds().size()))
												.append(QString("\n"));
			if (result_obj->getDataSeries() != 0)
			{
				body.append(QString("data series:\t"))
													.append(QString::number(result_obj->getDataSeries()->getUnipaxId()))
													.append(QString("\n"));
			}
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(200);
			resp->write(body);
			resp->end();
		}
		else if (format != "ids" && result_obj->getObjectIds().size() > max_ids)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(413);
			resp->write(QString("ResultObject contains more than %1 ids. Listing disabled to prevent overload.").arg(max_ids));
			resp->end();
		}
		else
		{
			respond(req, resp, result_obj->getObjectIds(), format);
		}

		return true;
	}
	else if ( ResultObjectServerHandler::label.exactMatch(path) )
	{
		QString result = req->url().queryItemValue("result");
		if (result.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'list' needs a ResultObject id as 'result' argument."));
			resp->end();
			return true;

		}
		bool ok;
		UnipaxId result_id = result.toULongLong(&ok);
		if (!ok)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not convert '")
					.append(result)
					.append(QString("' to a UnipaxId.")));
			resp->end();
			return true;
		}
		if (!dbc->isValid(result_id))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: id '")
					.append(result)
					.append(QString("' is not a valid id.")));
			resp->end();
			return true;
		}
		UniPAX::ResultObjectPtr result_obj;
		try
		{
			std::cout << "Loading result object " << result.toStdString() << "... " << std::flush;
			result_obj = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
			std::cout << "done." << std::endl;
		}
		catch (std::bad_cast & e)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: id '")
					.append(result)
					.append(QString("' is not a ResultObject id.")));
			resp->end();
			return true;
		}
		QString label = req->url().queryItemValue("label");
		result_obj->setDescription(label.toStdString());
		// serialization of description
		if (!dbc->update(result_obj))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Changed ResultObject could not be persisted."));
			resp->end();
			return true;
		}

		// report id of new ResultObject
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(QString::number(result_obj->getUnipaxId()));
		resp->end();
		return true;
	}
	else if ( ResultObjectServerHandler::gmt.exactMatch(path) )
	{
		QString id_db = req->url().queryItemValue("id_db").replace(QString("%20"), QString(" "));
		if (id_db.isEmpty())
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: creation of gene set file needs an 'id_db' argument."));
			resp->end();
			return true;
		}
		QStringList results = req->url().queryItemValue("result").split(",");
		if (results.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: 'results' needs at least one ResultObject id as argument."));
			resp->end();
			return true;
		}
		QString gmt_file;
		QString grouping = req->url().queryItemValue("grouping");
		if (grouping.isEmpty())
		{ // first form
			for (QStringList::iterator it = results.begin(); it != results.end(); ++it)
			{
				bool ok;
				UnipaxId result_id = it->toULongLong(&ok);
				if (!ok)
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Could not convert '")
							.append(*it)
							.append(QString("' to a UnipaxId.")));
					resp->end();
					return true;
				}
				UniPAX::ResultObjectPtr result_object = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
				if (result_object == 0)
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Could not load ResultObject from id '")
							.append(*it)
							.append(QString("'.")));
					resp->end();
					return true;
				}
				gmt_file.append(QString::fromStdString(result_object->getDescription()))
						.append(QString("\t"))
						.append(QString::fromStdString(result_object->getConstitutingQuery()));
				for (std::set<UnipaxId>::const_iterator id_it = result_object->getObjectIds().begin(); id_it != result_object->getObjectIds().end(); ++id_it)
				{
					std::vector<std::string> ids = dbc->getUnificationXrefIds(*id_it, id_db.toStdString());
					if (!ids.empty())
					{
						// What to do with multiple matches? We take only 1st for now:
						gmt_file.append(QString("\t"))
								.append(QString::fromStdString(ids.front()));
					}
				}
				gmt_file.append(QString("\n"));
			}
		}
		else
		{ // second form
			if (results.size() > 1)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Only one ResultObject id allowed in second form."));
				resp->end();
				return true;
			}
			bool ok;
			UnipaxId result_id = results.front().toULongLong(&ok);
			if (!ok)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not convert '")
						.append(results.front())
						.append(QString("' to a UnipaxId.")));
				resp->end();
				return true;
			}
			UniPAX::ResultObjectPtr result_object = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getObject(result_id));
			if (result_object == 0)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not load ResultObject from id '")
						.append(results.front())
						.append(QString("'.")));
				resp->end();
				return true;
			}
			if (grouping=="xref")
			{
				QString xref_db = req->url().queryItemValue("xref_db");
				if (xref_db.isEmpty())
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: creation of gene set file needs an 'xref_db' argument."));
					resp->end();
					return true;
				}
				std::map<UnipaxId, std::string> uid_xref;

				//TODO sort all ids by selected xref type
			}
			else if (grouping=="pathway")
			{
				// sort all object ids by pathways
				std::multimap<UnipaxId, UnipaxId> pw_id;
				if (!dbc->getPathwayMapOfIds(pw_id, std::vector<UnipaxId>(result_object->getObjectIds().begin(), result_object->getObjectIds().end())))
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: unable to retrieve Pathway-membership of ids from ResultObject."));
					resp->end();
					return true;
				}
				// get all UnificationXref ids to the objects
				UnipaxId current_pw = 0;
				for (std::multimap<UnipaxId, UnipaxId>::const_iterator it = pw_id.begin(); it != pw_id.end(); ++it)
				{
					if (it->first != current_pw)
					{
						// if not first row
						if (current_pw != 0)
						{
							gmt_file.append(QString("\n"));
						}
						// set current_pw
						current_pw = it->first;
						// get Pathway name and description
						UniPAX::SERVER::Attributes pw_attributes;
						if (!dbc->getAttributes(pw_attributes, current_pw))
						{
							resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
							resp->writeHead(404);
							resp->write(QString("ERROR: unable to retrieve Attributes for Pathway '")
									.append(QString::number(current_pw)));
							resp->end();
							return true;
						}
						gmt_file.append(pw_attributes.standardName)
								.append(QString("\t"))
								.append(pw_attributes.type)
								.append(" from source ")
								.append(QString::number(pw_attributes.dataSource));
					}
					std::set<std::string> ids;
					// Find matching Xref ids
					{
						std::vector<std::string> entity_ids = dbc->getUnificationXrefIds(it->second, id_db.toStdString());
						ids.insert(entity_ids.begin(), entity_ids.end());
					}
					{
						// For Entities that have an EntityReference object linked.
						UniPAX::SERVER::Attributes entity_attributes;
						if (!dbc->getAttributes(entity_attributes, it->second))
						{
							resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
							resp->writeHead(404);
							resp->write(QString("ERROR: unable to retrieve Attributes for Entity '")
									.append(QString::number(it->second)));
							resp->end();
							return true;
						}
						std::vector<std::string> reference_ids = dbc->getReferenceIds(QString::number(it->second).toStdString());
						for (std::vector<std::string>::const_iterator ref_it = reference_ids.begin(); ref_it != reference_ids.end(); ++ref_it)
						{
							std::vector<std::string> ux_ids = dbc->	getUnificationXrefIds(QString::fromStdString(*ref_it).toULongLong(), id_db.toStdString());
							ids.insert(ux_ids.begin(), ux_ids.end());
						}
					}
					for (std::set<std::string>::const_iterator id_it = ids.begin(); id_it != ids.end(); ++id_it)
					{
						gmt_file.append(QString("\t"))
								.append(QString::fromStdString(*id_it));
					}
				}
				gmt_file.append(QString("\n"));
			}
		}
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(gmt_file);
		resp->end();
		return true;
	}

	return false;
}

Q_EXPORT_PLUGIN2(ResultObjectServerHandler, ResultObjectServerHandler)


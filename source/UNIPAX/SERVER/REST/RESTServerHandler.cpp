#include <UNIPAX/SERVER/REST/RESTServerHandler.h>

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#include <UNIPAX/IMPORT/GRAPHML/GraphMLWriter.h>
#include <UNIPAX/IMPORT/GENESET/GeneSetWriter.h>

#include <UNIPAX/SERVER/HTTP/qhttpconnection.h>
#include <QtNetwork>

UniPAX::SERVER::RESTServerHandler::RESTServerHandler(QString name) : _options(name.toStdString()), _name(name), engine()
{
}


void UniPAX::SERVER::RESTServerHandler::respond(QHttpRequest *req, QHttpResponse *resp, std::set<UnipaxId> & ids, QString format)
{


	if (format == "" || format == "ids")
	{
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);

		QByteArray output;
		for (std::set<UnipaxId>::iterator it = ids.begin(); it != ids.end(); ++it)
		{
			output.append(QVariant::fromValue(*it).toString()).append("\n");
		}

		resp->write(output);
		resp->end();
	}
	else if (format == "attributes")
	{
		UniPAX::u_map<QString, QString>::type & org_map = engine->getOrganismMap();
		UniPAX::u_map<QString, QString>::type & datasource_map = engine->getDataSourceMap();


		std::map<UnipaxId, UniPAX::SERVER::Attributes> result_attr;
		engine->getAttributes(result_attr, ids);

		resp->setHeader("Content-Type", "text/csv; charset=UTF-8");
		resp->writeHead(200);

		QByteArray output;
		output.append("%");
		output.append("UnipaxID");
		output.append("\tType");
		output.append("\tStandardName");
		output.append("\tDisplayName");
		output.append("\tOrganism");
		output.append("\tDataSource");
		output.append("\tEntityModification");
		output.append("\n");


		for (std::map<UnipaxId, UniPAX::SERVER::Attributes>::iterator it = result_attr.begin(); it != result_attr.end(); ++it)
		{
			output.append(QVariant::fromValue(it->first).toString());
			output.append("\t").append(QString(it->second.type));
			output.append("\t\"").append(QString(it->second.standardName));
			output.append("\"\t\"").append(QString(it->second.displayName));
			output.append("\"\t");
			if (org_map.find(QVariant::fromValue(it->second.organism).toString()) != org_map.end())
				output.append(org_map[QVariant::fromValue(it->second.organism).toString()]);
			else
				output.append(QVariant::fromValue(it->second.organism).toString());
			output.append("\t");
			if (datasource_map.find(QVariant::fromValue(it->second.dataSource).toString()) != datasource_map.end())
				output.append(datasource_map[QVariant::fromValue(it->second.dataSource).toString()]);
			else
				output.append(QVariant::fromValue(it->second.dataSource).toString());

			output.append("\t").append(QString(it->second.entityModification));
			output.append("\n");
		}

		resp->write(output);
		resp->end();
	}
	else if (format == "biopax")
	{
		bool recursive = req->url().queryItemValue("recursive") == "false";

		std::vector<UnipaxId> _ids;
		_ids.assign(ids.begin(), ids.end());

		std::vector<boost::shared_ptr<UniPAX::UPBase> > objects;
		engine->getObjects(objects, _ids);


		UniPAX::KernelCollector collector;
		collector.skipPathwaySteps(true);
		collector.collect(objects);

		resp->setHeader("Content-Type", "text/xml; charset=UTF-8");
		resp->writeHead(200);

		UniPAX::BIOPAXWriter writer;
		writer.setPersistenceManager(collector);

		QXmlStreamWriter out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));
		out.setCodec("UTF-8");
		out.setAutoFormatting(true);
		out.writeStartDocument();

		writer.writeHeader(out);
		if (!recursive)
		{
			writer.write(out);
		}
		else
		{
			for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::const_iterator it(objects.begin()); it != objects.end(); it++)
			{
				std::stringstream ss;
				ss << (*it)->getUnipaxId();
				std::string s;
				ss >> s;

				writer.writeObject(s, (*it)->getType(), out);
			}
		}
		writer.writeFooter(out);
		out.writeEndDocument();
		resp->end();
	}
	else if (format == "graphml")
	{
		UniPAX::KernelCollector collector;
		collector.skipPathwaySteps(true);

		std::vector<UnipaxId> _ids;
		_ids.assign(ids.begin(), ids.end());

		std::vector<boost::shared_ptr<UniPAX::UPBase> > objects;
		engine->getObjects(objects, _ids);

		collector.collect(objects);

		resp->setHeader("Content-Type", "text/xml; charset=UTF-8");
		resp->writeHead(200);

		UniPAX::GraphMLWriter graphmlWriter;
		graphmlWriter.setPersistenceManager(collector);

		QXmlStreamWriter out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));
		graphmlWriter.openDocument(out);
		graphmlWriter.writeHeader(out);
		graphmlWriter.write(out);
		graphmlWriter.writeFooter(out);
		graphmlWriter.closeDocument(out);
		resp->end();
	}
	else if (format == "gmx" || format == "gmt")
	{
		UniPAX::KernelCollector collector;
		collector.skipPathwaySteps(true);

		std::vector<UnipaxId> _ids;
		for (std::set<UnipaxId>::iterator it = ids.begin(); it != ids.end(); ++it)
		{
			if (DBManager::isType(*it, ClassType::idPathway))
				_ids.push_back(*it);
		}


		std::vector<boost::shared_ptr<UniPAX::UPBase> > objects;
		engine->getObjects(objects, _ids);


		bool gmx_format = true;
		if ((req->url().queryItemValue("format") != "gmx") || objects.size() > 1)
			gmx_format = false;

		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);

		std::vector<boost::shared_ptr<UniPAX::UPBase> >::iterator it;
		for (it = objects.begin(); it != objects.end(); it++)
		{
			UniPAX::KernelCollector collector;
			collector.skipPathwaySteps(true);
			collector.collect(*it);

			std::string title;
			std::string description;
			boost::shared_ptr<UniPAX::Entity> first_obj = boost::dynamic_pointer_cast<UniPAX::Entity>(*it);
			if (first_obj)
			{
				title = first_obj->getStandardName() + " (" + first_obj->getDataSource()->getStandardName() + ")";
				std::vector<std::string> descriptions = first_obj->getComments();
				std::string help;
				for (std::vector<std::string>::iterator it = descriptions.begin(); it != descriptions.end(); it++)
				{
					help = *it;
					std::replace(help.begin(), help.end(), '\n', ' ');
					description = description + help;
				}
			}

			UniPAX::GeneSetWriter gmxWriter;
			gmxWriter.setPersistenceManager(collector);
			QTextStream out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));
			out.setCodec("UTF-8");
			gmxWriter.setTitle(title);
			gmxWriter.setDescription(description);
			if (req->url().queryItemValue("idtype").isEmpty())
			{
				gmxWriter.write(out,
						req->url().queryItemValue("geneid") == "true",
						gmx_format);
			}
			else
			{
				if (!gmxWriter.write(out,
						req->url().queryItemValue("idtype").toStdString(),
						gmx_format))
				{
					std::set<std::string> idTypes = gmxWriter.getAvailableIdTypes();
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Only the following ID types are contained:\n"));
					for (std::set<std::string>::const_iterator it = idTypes.begin(); it != idTypes.end(); ++it)
					{
						resp->write(QString::fromStdString(*it).append("\n"));
					}
					resp->end();
				}
			}
		}
	}
	else
	{
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(404);
		resp->write(QString("ERROR: Unknown format.\n"));
		resp->end();
	}
}

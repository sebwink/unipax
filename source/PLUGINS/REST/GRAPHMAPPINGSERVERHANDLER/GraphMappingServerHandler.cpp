#include <PLUGINS/REST/GRAPHMAPPINGSERVERHANDLER/GraphMappingServerHandler.h>

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#include <UNIPAX/IMPORT/GRAPHML/GraphMLWriter.h>
#include <UNIPAX/IMPORT/GENESET/GeneSetWriter.h>
#include <UNIPAX/COMMON/KernelCollector.h>

#include <UNIPAX/SERVER/HTTP/qhttpconnection.h>

#include <UNIPAX/GRAPH/LEMON/GMLGraphWriter.h>
#include <UNIPAX/GRAPH/LEMON/GraphMLGraphWriter.h>
#include <UNIPAX/GRAPH/LEMON/SIFGraphWriter.h>
#include <UNIPAX/GRAPH/LEMON/GMXGraphWriter.h>

#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#endif

#include <UNIPAX/KERNEL/all.h>

#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>


#include <lemon/core.h>
#include <lemon/lgf_writer.h>
#include <lemon/edge_set.h>
#include <lemon/adaptors.h>
#include <lemon/list_graph.h>


#include <unistd.h>
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <sstream>



#include <stdlib.h>
#include <sstream>
#include <time.h>

#include <QtXml>

#include <QtCore/qplugin.h>
#include <QtNetwork>


QRegExp GraphMappingServerHandler::graph_ppi("/graph/ppi", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp GraphMappingServerHandler::graph_regulatory("/graph/regulatory", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp GraphMappingServerHandler::graph_metabolic("/graph/metabolic", Qt::CaseSensitive, QRegExp::RegExp2);

GraphMappingServerHandler::GraphMappingServerHandler() : RESTServerHandler("Graph Mapping Server Handler"), _rebuild_mapping_index(false)
{
	_pattern.push_back(GraphMappingServerHandler::graph_ppi);
	_pattern.push_back(GraphMappingServerHandler::graph_regulatory);
	_pattern.push_back(GraphMappingServerHandler::graph_metabolic);

	_options.add_options()
						("rebuild-mapping-index", "Rebuild mapping engine index")
						;
}


GraphMappingServerHandler::~GraphMappingServerHandler()
{
	engine = 0;
}

void GraphMappingServerHandler::init(boost::program_options::variables_map & _vm)
{
#ifdef ODB_MYSQL
	mapping_engine = boost::shared_ptr<UniPAX::GRAPH::mysql::MySQLMappingEngine>(new UniPAX::GRAPH::mysql::MySQLMappingEngine(engine->getDBManager()));
#elif defined ODB_ORACLE
	mapping_engine = boost::shared_ptr<UniPAX::GRAPH::oracle::OracleMappingEngine>(new UniPAX::GRAPH::oracle::OracleMappingEngine(engine->getDBManager()));
#endif

	_rebuild_mapping_index = _vm.count("rebuild-mapping-index");

	if (_rebuild_mapping_index || mapping_engine->needsRebuildDatabaseCache())
		mapping_engine->rebuildDatabaseCache();
}

QString GraphMappingServerHandler::help(QString format)
{
	if (format == "html")
	{
		return 	QString("<tr><td colspan=2><b>Returns graph mappings:</b></td></tr>")
				.append("<tr><td valign=top><b>/graph/ppi</b></td><td>")
				.append("Returns a protein-protein interaction network.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /graph/ppi?&lt;parameters&gt;<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>format - specifies the output format (gml | sif | lemon | gmx | graphml)</li>")
				.append("<li>nodelabel - assign node labels (xref!&lt;dbname&gt; | type | name | data)</li>")
				.append("<li>edgelabel - assign edge labels (xref!&lt;dbname&gt; | type | relation)</li>")
				.append("<li>result - id of a result object from which to construct the network</li>")
				.append("<li>filter - filter the network by (pathway!&lt;id&gt; | organism!&lt;id&gt; | nodetype!&lt;type&gt; | edgetype!&lt;type&gt;)(,&lt;more filter&gt;)* </li>")
				.append("</ul>")
				.append("</td></tr>")
				.append("<tr><td valign=top><b>/graph/regulatory</b></td><td>")
				.append("Returns a regulatory network.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /graph/regulatory?&lt;parameters&gt;<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>format - specifies the output format (gml | sif | lemon | gmx | graphml)</li>")
				.append("<li>nodelabel - assign node labels (xref!&lt;dbname&gt; | type | name)</li>")
				.append("<li>edgelabel - assign edge labels (xref!&lt;dbname&gt; | type | relation)</li>")
				.append("<li>result - id of a result object from which to construct the network</li>")
				.append("<li>filter - filter the network by (pathway!&lt;id&gt; | organism!&lt;id&gt; | nodetype!&lt;type&gt; | edgetype!&lt;type&gt;)(,&lt;more filter&gt;)* </li>")
				.append("</ul>")
				.append("</td></tr>")
				.append("<tr><td valign=top><b>/graph/metabolic</b></td><td>")
				.append("Returns a metabolic network.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /graph/metabolic?&lt;parameters&gt;<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>format - specifies the output format (gml | sif | lemon | gmx | graphml)</li>")
				.append("<li>nodelabel - assign node labels (xref!&lt;dbname&gt; | type | name)</li>")
				.append("<li>edgelabel - assign edge labels (xref!&lt;dbname&gt; | type | relation)</li>")
				.append("<li>result - id of a result object from which to construct the network</li>")
				.append("<li>filter - filter the network by (pathway!&lt;id&gt; | organism!&lt;id&gt; | nodetype!&lt;type&gt; | edgetype!&lt;type&gt;)(,&lt;more filter&gt;)* </li>")
				.append("</ul>")
				.append("</td></tr>")
				;
	}

	return "";

}

bool GraphMappingServerHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{
	QString path(req->path());

	if ( GraphMappingServerHandler::graph_ppi.exactMatch(path))
	{
		UniPAX::GRAPH::ProteinProteinInteractionNetworkPtr rg;

		QString result = req->url().queryItemValue("result");
		UnipaxId result_id = 0;
		if (result.size() != 0)
		{
			bool ok;
			result_id = result.toULongLong(&ok);
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
			UniPAX::ResultObjectPtr result_obj = boost::dynamic_pointer_cast<UniPAX::ResultObject>(engine->getDBManager()->getObjectByID(result_id));
			if (result_obj == 0)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not load ResultObject from id '")
						.append(result)
						.append(QString("'.")));
				resp->end();
				return true;
			}
			rg = mapping_engine->createProteinProteinInteractionNetwork(*result_obj);
		}
		else
		{
			rg = mapping_engine->createProteinProteinInteractionNetwork(UniPAX::Kernel::children("PhysicalEntity", true));
		}
		lemon::ListGraph::NodeMap<std::string> nodeTypeMap(rg->graph);
		mapping_engine->mapNodeTypes(*rg, nodeTypeMap);

		QString nodelabel = QUrl::fromPercentEncoding(req->url().queryItemValue("nodelabel").toUtf8());

		bool hasNodeLabels = false;

		typedef UniPAX::GRAPH::ProteinProteinInteractionNetwork PPINetwork;
		typedef PPINetwork::Graph::NodeMap<std::string> PPINodeLabel;
		typedef UnipaxPtr<PPINodeLabel>::type PPINodeLabelPtr;

		std::vector<std::pair<std::string, PPINodeLabelPtr> > nodeLabelMaps;
		//MetabolicNodeLabel nodeLabelMap(rg->graph);
		QStringList _nodelabel = nodelabel.split(",");
		for (int i = 0; i < _nodelabel.size(); ++i)
		{
			QString item = _nodelabel[i];
			PPINodeLabelPtr nodeLabelMap(new PPINodeLabel(rg->graph));

			if (item.startsWith("xref!"))
			{
				nodelabel.remove(0, QString("xref!").size());
				mapping_engine->mapXrefData(*rg, *nodeLabelMap, nodelabel.toStdString());
				nodeLabelMaps.push_back(std::pair<std::string, PPINodeLabelPtr>("xref", nodeLabelMap));
				hasNodeLabels = true;
			}
			else if (nodelabel == "type")
			{
				mapping_engine->mapNodeTypes(*rg, *nodeLabelMap);
				nodeLabelMaps.push_back(std::pair<std::string, PPINodeLabelPtr>("type", nodeLabelMap));
				hasNodeLabels = true;
			}
			else if (nodelabel == "name")
			{
				mapping_engine->mapNames(*rg, *nodeLabelMap, "display");
				nodeLabelMaps.push_back(std::pair<std::string, PPINodeLabelPtr>("name", nodeLabelMap));
				hasNodeLabels = true;
			}
			else if (nodelabel == "standardName")
			{
				mapping_engine->mapNames(*rg, *nodeLabelMap, "standard");
				nodeLabelMaps.push_back(std::pair<std::string, PPINodeLabelPtr>("name", nodeLabelMap));
				hasNodeLabels = true;
			}
			else if (nodelabel == "data")
			{
				// because of multiple data series we need to pass the vector
				mapping_engine->mapSeriesData(*rg, nodeLabelMaps, result_id);
				hasNodeLabels = true;
			}
		}

		QString filter = QUrl::fromPercentEncoding(req->url().queryItemValue("filter").toUtf8());

		if (filter.startsWith("\"") && filter.endsWith("\""))
		{
			filter.remove(0,1);
			filter.remove(filter.size() - 1, 1);
		}

		std::string pathway;
		std::string pathway_description;
		std::string organism;

		QStringList _filter = filter.split(",");
		for (int i = 0; i < _filter.size(); ++i)
		{
			QString item = _filter[i];
			if (item.startsWith("organism!"))
			{
				item.remove(0, QString("organism!").size());
				std::set<UnipaxId> organismIds;
				organismIds.insert(item.toULongLong());
				mapping_engine->filterByOrganisms(*rg, organismIds);

				organism = mapping_engine->getName(item.toULongLong());

			}
			else if (item.startsWith("pathway!"))
			{
				item.remove(0, QString("pathway!").size());
				std::set<UnipaxId> pathwayIds;
				pathwayIds.insert(item.toULongLong());
				mapping_engine->filterByPathways(*rg, pathwayIds);
				pathway = mapping_engine->getPathwayName(item.toULongLong());
				pathway_description = mapping_engine->getPathwayDescription(item.toULongLong());
			}
			else if (item.startsWith("nodetype!"))
			{
				item.remove(0, QString("nodetype!").size());
				if (UniPAX::Kernel::isType(item.toStdString()))
				{
					rg->filterNodes(nodeTypeMap, item.toStdString(), std::equal_to<std::string>());
				}
			}
		}

		rg->eraseDisconnectedNodes();

		QString format = req->url().queryItemValue("format").toLower();

		QTextStream out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));

		std::stringstream ss;

		QString download = QUrl::fromPercentEncoding(req->url().queryItemValue("download").toUtf8());

		if (format == "sif")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition",  "attachment; filename=network.sif");
			resp->writeHead(200);

			lemon::SIFGraphWriter<PPINetwork::Graph> w(rg->graph, ss);
			if (hasNodeLabels)
				w.labelMap(*(nodeLabelMaps.begin()->second));
			else
				w.labelMap(rg->node_id_map);

			w.relationMap(rg->edge_id_map).run();
		}
		else if (format == "lemon")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.lgf");
			resp->writeHead(200);

			lemon::DigraphWriter<PPINetwork::Graph> w(rg->graph, ss);
			w.nodeMap("unipaxId", rg->node_id_map);
			if (hasNodeLabels)
			{
				for (int i=0; i<nodeLabelMaps.size(); ++i)
					w.nodeMap(nodeLabelMaps.at(i).first, *(nodeLabelMaps.at(i).second));
			}

			w.run();
		}
		else if (format == "gmx")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.gmx");
			resp->writeHead(200);

			lemon::GMXDigraphWriter<PPINetwork::Graph> w(rg->graph, ss);
			if (hasNodeLabels)
				w.labelMap(*(nodeLabelMaps.begin()->second));
			else
				w.labelMap(rg->node_id_map);

			std::string title = "UniPAX Geneset";
			if (pathway != "")
				title = pathway;
			if (pathway_description == "")
				pathway_description = "na";
			if (organism != "")
				title += " (" + organism + ")";

			w.genesetDescription(pathway_description).genesetTitle(title).run();
		}
		else if (format == "graphml")
		{
			resp->setHeader("Content-Type", "text/xml; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.graphml");
			resp->writeHead(200);

			lemon::GraphMLDigraphWriter<PPINetwork::Graph> w(rg->graph, ss);
			w.nodeMap("unipaxId", rg->node_id_map);
			if (hasNodeLabels)
			{
				for (int i=0; i<nodeLabelMaps.size(); ++i)
					w.nodeMap(nodeLabelMaps.at(i).first, *(nodeLabelMaps.at(i).second));
			}

			w.run();
		}
		else if (format == "" || format == "gml")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.gml");
			resp->writeHead(200);

			lemon::GMLDigraphWriter<PPINetwork::Graph> w(rg->graph, ss);
			w.nodeMap("unipaxId", rg->node_id_map);
			if (hasNodeLabels)
			{
				for (int i=0; i<nodeLabelMaps.size(); ++i)
					w.nodeMap(nodeLabelMaps.at(i).first, *(nodeLabelMaps.at(i).second));
			}

			w.run();
		}

		out << ss.str().c_str();
		resp->end();

		return true;
	}
	else if ( GraphMappingServerHandler::graph_metabolic.exactMatch(path))
	{
		boost::shared_ptr<UniPAX::GRAPH::MetabolicNetwork> rg;
		QString result = req->url().queryItemValue("result");
		UnipaxId result_id = 0;
		if (result.size() != 0)
		{
			bool ok;
			result_id = result.toULongLong(&ok);
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
			UniPAX::ResultObjectPtr result_obj = boost::dynamic_pointer_cast<UniPAX::ResultObject>(engine->getDBManager()->getObjectByID(result_id));
			if (result_obj == 0)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not load ResultObject from id '")
						.append(result)
						.append(QString("'.")));
				resp->end();
				return true;
			}
			rg = mapping_engine->createMetabolicNetwork(UniPAX::Kernel::children("PhysicalEntity", true), *result_obj);
		}
		else
		{
			rg = mapping_engine->createMetabolicNetwork(UniPAX::Kernel::children("PhysicalEntity", true));
		}

		lemon::ListDigraph::NodeMap<std::string> nodeTypeMap(rg->graph);
		mapping_engine->mapNodeTypes(*rg, nodeTypeMap);

		QString nodelabel = QUrl::fromPercentEncoding(req->url().queryItemValue("nodelabel").toUtf8());

		bool hasNodeLabels = false;

		typedef UniPAX::GRAPH::MetabolicNetwork::Graph::NodeMap<std::string> MetabolicNodeLabel;
		typedef UnipaxPtr<MetabolicNodeLabel>::type MetabolicNodeLabelPtr;

		std::vector<std::pair<std::string, MetabolicNodeLabelPtr> > nodeLabelMaps;
		//MetabolicNodeLabel nodeLabelMap(rg->graph);
		QStringList _nodelabel = nodelabel.split(",");
		for (int i = 0; i < _nodelabel.size(); ++i)
		{
			QString item = _nodelabel[i];
			MetabolicNodeLabelPtr nodeLabelMap(new MetabolicNodeLabel(rg->graph));

			if (item.startsWith("xref!"))
			{
				nodelabel.remove(0, QString("xref!").size());
				mapping_engine->mapXrefData(*rg, *nodeLabelMap, nodelabel.toStdString());
				nodeLabelMaps.push_back(std::pair<std::string, MetabolicNodeLabelPtr>("xref", nodeLabelMap));
				hasNodeLabels = true;
			}
			else if (nodelabel == "type")
			{
				mapping_engine->mapNodeTypes(*rg, *nodeLabelMap);
				nodeLabelMaps.push_back(std::pair<std::string, MetabolicNodeLabelPtr>("type", nodeLabelMap));
				hasNodeLabels = true;
			}
			else if (nodelabel == "name")
			{
				mapping_engine->mapNames(*rg, *nodeLabelMap, "display");
				nodeLabelMaps.push_back(std::pair<std::string, MetabolicNodeLabelPtr>("name", nodeLabelMap));
				hasNodeLabels = true;
			}
			else if (nodelabel == "data")
			{
				// because of multiple data series we need to pass the vector
				mapping_engine->mapSeriesData(*rg, nodeLabelMaps, result_id);
				hasNodeLabels = true;
			}
		}

		QString filter = QUrl::fromPercentEncoding(req->url().queryItemValue("filter").toUtf8());

		if (filter.startsWith("\"") && filter.endsWith("\""))
		{
			filter.remove(0,1);
			filter.remove(filter.size() - 1, 1);
		}

		std::string pathway;
		std::string pathway_description;
		std::string organism;

		QStringList _filter = filter.split(",");
		for (int i = 0; i < _filter.size(); ++i)
		{
			QString item = _filter[i];
			if (item.startsWith("organism!"))
			{
				item.remove(0, QString("organism!").size());
				std::set<UnipaxId> organismIds;
				organismIds.insert(item.toULongLong());
				mapping_engine->filterByOrganisms(*rg, organismIds);

				organism = mapping_engine->getName(item.toULongLong());

			}
			else if (item.startsWith("pathway!"))
			{
				item.remove(0, QString("pathway!").size());
				std::set<UnipaxId> pathwayIds;
				pathwayIds.insert(item.toULongLong());
				mapping_engine->filterByPathways(*rg, pathwayIds);
				pathway = mapping_engine->getPathwayName(item.toULongLong());
				pathway_description = mapping_engine->getPathwayDescription(item.toULongLong());
			}
			else if (item.startsWith("nodetype!"))
			{
				item.remove(0, QString("nodetype!").size());
				if (UniPAX::Kernel::isType(item.toStdString()))
				{
					rg->filterNodes(nodeTypeMap, item.toStdString(), std::equal_to<std::string>());
				}
			}
		}

		rg->eraseDisconnectedNodes();

		QString format = req->url().queryItemValue("format").toLower();

		QTextStream out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));

		std::stringstream ss;

		QString download = QUrl::fromPercentEncoding(req->url().queryItemValue("download").toUtf8());

		if (format == "sif")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition",  "attachment; filename=network.sif");
			resp->writeHead(200);

			lemon::SIFDigraphWriter<UniPAX::GRAPH::MetabolicNetwork::Graph> w(rg->graph, ss);
			if (hasNodeLabels)
				w.labelMap(*(nodeLabelMaps.begin()->second));
			else
				w.labelMap(rg->node_id_map);

			w.run();
		}
		else if (format == "lemon")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.lgf");
			resp->writeHead(200);

			lemon::DigraphWriter<UniPAX::GRAPH::MetabolicNetwork::Graph> w(rg->graph, ss);
			w.nodeMap("unipaxId", rg->node_id_map);
			if (hasNodeLabels)
			{
				for (int i=0; i<nodeLabelMaps.size(); ++i)
					w.nodeMap(nodeLabelMaps.at(i).first, *(nodeLabelMaps.at(i).second));
			}

			w.run();
		}
		else if (format == "gmx")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.gmx");
			resp->writeHead(200);

			lemon::GMXDigraphWriter<UniPAX::GRAPH::MetabolicNetwork::Graph> w(rg->graph, ss);
			if (hasNodeLabels)
				w.labelMap(*(nodeLabelMaps.begin()->second));
			else
				w.labelMap(rg->node_id_map);

			std::string title = "UniPAX Geneset";
			if (pathway != "")
				title = pathway;
			if (pathway_description == "")
				pathway_description = "na";
			if (organism != "")
				title += " (" + organism + ")";

			w.genesetDescription(pathway_description).genesetTitle(title).run();
		}
		else if (format == "graphml")
		{
			resp->setHeader("Content-Type", "text/xml; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.graphml");
			resp->writeHead(200);

			lemon::GraphMLDigraphWriter<UniPAX::GRAPH::MetabolicNetwork::Graph> w(rg->graph, ss);
			w.nodeMap("unipaxId", rg->node_id_map);
			if (hasNodeLabels)
			{
				for (int i=0; i<nodeLabelMaps.size(); ++i)
					w.nodeMap(nodeLabelMaps.at(i).first, *(nodeLabelMaps.at(i).second));
			}

			w.run();
		}
		else if (format == "" || format == "gml")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.gml");
			resp->writeHead(200);

			lemon::GMLDigraphWriter<UniPAX::GRAPH::MetabolicNetwork::Graph> w(rg->graph, ss);
			w.nodeMap("unipaxId", rg->node_id_map);
			if (hasNodeLabels)
			{
				for (int i=0; i<nodeLabelMaps.size(); ++i)
					w.nodeMap(nodeLabelMaps.at(i).first, *(nodeLabelMaps.at(i).second));
			}

			w.run();
		}

		out << ss.str().c_str();
		resp->end();

		return true;
	}
	else if ( GraphMappingServerHandler::graph_regulatory.exactMatch(path) )
	{
		boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> rg;
		QString result = req->url().queryItemValue("result");
		if (result.size() != 0)
		{
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
			UniPAX::ResultObjectPtr result_obj = boost::dynamic_pointer_cast<UniPAX::ResultObject>(engine->getDBManager()->getObjectByID(result_id));
			if (result_obj == 0)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Could not load ResultObject from id '")
						.append(result)
						.append(QString("'.")));
				resp->end();
				return true;
			}
			rg = mapping_engine->createRegulatoryNetwork(UniPAX::Kernel::children("PhysicalEntity", true), *result_obj);
			mapping_engine->addComplexAssemblies(*rg, UniPAX::Kernel::children("PhysicalEntity", true), *result_obj, true);
			mapping_engine->addInteractions(*rg, *result_obj);

		}
		else
		{
			rg = mapping_engine->createRegulatoryNetwork(UniPAX::Kernel::children("PhysicalEntity", true));
			mapping_engine->addComplexAssemblies(*rg, UniPAX::Kernel::children("PhysicalEntity", true), true);
			mapping_engine->addInteractions(*rg, UniPAX::Kernel::children("PhysicalEntity", true));

		}

		UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcMap<std::string> edgeTypeMap(rg->graph);
		mapping_engine->mapRegulationTypes(*rg, edgeTypeMap);

		lemon::ListDigraph::NodeMap<std::string> nodeTypeMap(rg->graph);
		mapping_engine->mapNodeTypes(*rg, nodeTypeMap);

		lemon::ListDigraph::ArcMap<std::string> arcTypeMap(rg->graph);
		mapping_engine->mapArcTypes(*rg, arcTypeMap);



		QString nodelabel = QUrl::fromPercentEncoding(req->url().queryItemValue("nodelabel").toUtf8());
		QString edgelabel = QUrl::fromPercentEncoding(req->url().queryItemValue("edgelabel").toUtf8());

		QString nodedata = QUrl::fromPercentEncoding(req->url().queryItemValue("nodedata").toUtf8());

		bool hasNodeLabels = false;
		bool hasEdgeLabels = false;

		UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> nodeLabelMap(rg->graph);
		UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcMap<std::string> edgeLabelMap(rg->graph);

		UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> nodeDataMap(rg->graph);


		if (nodelabel.startsWith("xref!"))
		{
			nodelabel.remove(0, QString("xref!").size());
			mapping_engine->mapXrefData(*rg, nodeLabelMap, nodelabel.toStdString());
			hasNodeLabels = true;
		}
		else if (nodelabel == "type")
		{
			mapping_engine->mapNodeTypes(*rg, nodeLabelMap);
			hasNodeLabels = true;
		}
		else if (nodelabel == "name")
		{
			mapping_engine->mapNames(*rg, nodeLabelMap, "display");
			hasNodeLabels = true;
		}
		else if (nodelabel == "feature")
		{
			mapping_engine->mapFeatures(*rg, nodeLabelMap);
			hasNodeLabels = true;
		}

		if (edgelabel.startsWith("xref!"))
		{
			edgelabel.remove(0, QString("xref!").size());
			mapping_engine->mapXrefData(*rg, edgeLabelMap, edgelabel.toStdString());
			hasEdgeLabels = true;
		}
		else if (edgelabel == "type")
		{
			mapping_engine->mapArcTypes(*rg, edgeLabelMap);
			hasEdgeLabels = true;
		}
		else if (edgelabel == "relation")
		{
			mapping_engine->mapRegulationTypes(*rg, edgeLabelMap);
			hasEdgeLabels = true;
		}

		if (nodedata.startsWith("xref!"))
		{
			nodedata.remove(0, QString("xref!").size());
			mapping_engine->mapXrefData(*rg, nodeDataMap, nodelabel.toStdString());
		}
		else if (nodedata == "type")
		{
			mapping_engine->mapNodeTypes(*rg, nodeDataMap);
		}
		else if (nodedata == "name")
		{
			mapping_engine->mapNames(*rg, nodeDataMap);
		}
		else if (nodedata == "feature")
		{
			mapping_engine->mapFeatures(*rg, nodeDataMap);
		}


		QString filter = QUrl::fromPercentEncoding(req->url().queryItemValue("filter").toUtf8());

		if (filter.startsWith("\"") && filter.endsWith("\""))
		{
			filter.remove(0,1);
			filter.remove(filter.size() - 1, 1);
		}

		std::string pathway;
		std::string pathway_description;
		std::string organism;

		QStringList _filter = filter.split(",");
		for (int i = 0; i < _filter.size(); ++i)
		{
			QString item = _filter[i];
			if (item.startsWith("organism!"))
			{
				item.remove(0, QString("organism!").size());
				std::set<UnipaxId> organismIds;
				organismIds.insert(item.toULongLong());

				mapping_engine->filterByOrganisms(*rg, organismIds);
				organism = mapping_engine->getName(item.toULongLong());

			}
			else if (item.startsWith("pathway!"))
			{
				item.remove(0, QString("pathway!").size());
				std::set<UnipaxId> pathwayIds;
				pathwayIds.insert(item.toULongLong());

				mapping_engine->filterByPathways(*rg, pathwayIds);
				pathway = mapping_engine->getPathwayName(item.toULongLong());
				pathway_description = mapping_engine->getPathwayDescription(item.toULongLong());
			}
			else if (item.startsWith("nodetype!"))
			{
				item.remove(0, QString("nodetype!").size());
				if (UniPAX::Kernel::isType(item.toStdString()))
				{
					rg->filterNodes(nodeTypeMap, item.toStdString(), std::equal_to<std::string>());
				}
			}
			else if (item.startsWith("edgetype!"))
			{
				item.remove(0, QString("edgetype!").size());
				rg->filterArcs(edgeTypeMap, item.toStdString(), std::equal_to<std::string>());
			}

		}
		rg->eraseDisconnectedNodes();

		QString format = req->url().queryItemValue("format").toLower();

		QTextStream out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));

		std::stringstream ss;

		QString download = QUrl::fromPercentEncoding(req->url().queryItemValue("download").toUtf8());

		if (format == "sif")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition",  "attachment; filename=network.sif");
			resp->writeHead(200);

			lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, ss);
			if (hasNodeLabels)
				w.labelMap(nodeLabelMap);
			else
				w.labelMap(rg->node_id_map);

			w.relationMap(edgeTypeMap).run();
		}
		else if (format == "na")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition",  "attachment; filename=network.sif");
			resp->writeHead(200);

			std::stringstream nullstream;
			lemon::SIFDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, nullstream);
			w.nodeMap(nodedata.toStdString(), nodeDataMap, ss);
			w.labelMap(rg->node_id_map).relationMap(rg->arc_id_map).run();
		}
		else if (format == "lemon")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.lgf");
			resp->writeHead(200);

			lemon::DigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, ss);
			w.nodeMap("unipaxId", rg->node_id_map).arcMap("unipaxId", rg->arc_id_map);
			if (hasNodeLabels)
				w.nodeMap("label", nodeLabelMap);

			if (hasEdgeLabels)
				w.arcMap("label", edgeLabelMap);
			w.run();
		}
		else if (format == "gmx")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.gmx");
			resp->writeHead(200);

			lemon::GMXDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, ss);
			if (hasNodeLabels)
				w.labelMap(nodeLabelMap);
			else
				w.labelMap(rg->node_id_map);

			std::string title = "UniPAX Geneset";
			if (pathway != "")
				title = pathway;
			if (pathway_description == "")
				pathway_description = "na";
			if (organism != "")
				title += " (" + organism + ")";

			w.genesetDescription(pathway_description).genesetTitle(title).run();
		}
		else if (format == "graphml")
		{
			resp->setHeader("Content-Type", "text/xml; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.graphml");
			resp->writeHead(200);

			lemon::GraphMLDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, ss);
			w.nodeMap("unipaxId", rg->node_id_map).arcMap("unipaxId", rg->arc_id_map);
			if (hasNodeLabels)
				w.nodeMap("node.label", nodeLabelMap);

			if (hasEdgeLabels)
				w.arcMap("edge.label", edgeLabelMap);
			w.run();
		}
		else if (format == "" || format == "gml")
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			if (download != "false" && download != "no")
				resp->setHeader("Content-Disposition", "attachment; filename=network.gml");
			resp->writeHead(200);

			lemon::GMLDigraphWriter<UniPAX::GRAPH::RegulatoryNetwork::Graph> w(rg->graph, ss);
			w.nodeMap("unipaxId", rg->node_id_map).arcMap("unipaxId", rg->arc_id_map);
			if (hasNodeLabels)
				w.nodeMap("label", nodeLabelMap);

			if (hasEdgeLabels)
				w.arcMap("label", edgeLabelMap);
			w.run();
		}

		out << ss.str().c_str();
		resp->end();

		return true;
	}

	return false;
}

Q_EXPORT_PLUGIN2(GraphMappingServerHandler, GraphMappingServerHandler)


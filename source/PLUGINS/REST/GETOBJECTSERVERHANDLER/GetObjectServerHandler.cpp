#include <PLUGINS/REST/GETOBJECTSERVERHANDLER/GetObjectServerHandler.h>

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#include <UNIPAX/IMPORT/GRAPHML/GraphMLWriter.h>
#include <UNIPAX/IMPORT/GENESET/GeneSetWriter.h>
#include <UNIPAX/COMMON/KernelCollector.h>
#include <UNIPAX/KERNEL/EXT/ResultObject.h>

#include <UNIPAX/SERVER/HTTP/qhttpconnection.h>


#include <stdlib.h>
#include <sstream>
#include <time.h>

#include <QtXml>

#include <QtCore/qplugin.h>
#include <qstring.h>
#include <QtNetwork>

QRegExp GetObjectServerHandler::get("/get/([0-9]+,)*[0-9]+", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp GetObjectServerHandler::id("/id/([0-9]+,)*[0-9]+", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp GetObjectServerHandler::datasource("/datasource/[0-9]+", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp GetObjectServerHandler::all("/all/[a-zA-Z]+", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp GetObjectServerHandler::all_types("/all/?", Qt::CaseSensitive, QRegExp::RegExp2);
QRegExp GetObjectServerHandler::info_xrefs("/info/xrefdbs", Qt::CaseSensitive, QRegExp::RegExp2);


GetObjectServerHandler::GetObjectServerHandler() : RESTServerHandler("Get Object Server Handler")
{

	_pattern.push_back(GetObjectServerHandler::get);
	_pattern.push_back(GetObjectServerHandler::id);
	_pattern.push_back(GetObjectServerHandler::datasource);
	_pattern.push_back(GetObjectServerHandler::all);
	_pattern.push_back(GetObjectServerHandler::all_types);
	_pattern.push_back(GetObjectServerHandler::info_xrefs);
}


GetObjectServerHandler::~GetObjectServerHandler()
{
	engine = 0;
}

void GetObjectServerHandler::init(boost::program_options::variables_map & _vm)
{
}

QString GetObjectServerHandler::help(QString format)
{
	if (format == "html")
	{
		return 	QString("<tr><td colspan=2><b>Get objects by id or type:</b></td></tr>")
			.append("<tr><td valign=top><b>/get</b></td><td>")
				.append("Returns one or more objects from the database.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /get/&lt;unipaxId&gt;,&lt;unipaxId&gt;,...?format=(biopax|graphml|gmx|gmt)&recursive=(true|false)<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>format - specifies the output format (for more than one unipaxId gmx format is changed into gmt format)</li>")
				.append("<li>recursive - only if format=biopax, whether or not to output referenced objects</li>")
				.append("</ul>")
				.append("</td></tr>")
			.append("<tr><td valign=top><b>/datasource</b></td><td>")
				.append("Returns all pathways from the datasource.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /datasource/&lt;unipaxId&gt?format=(biopax|gmt)&recursive=(true|false)<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>format - specifies the output format</li>")
				.append("<li>recursive - only if format=biopax, whether or not to output referenced objects</li>")
				.append("</ul>")
				.append("</td></tr>")
				.append("<tr><td valign=top><b>/id</b></td><td>")
				.append("Returns one or more objects from the database.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /id/&lt;unipaxId&gt;,&lt;unipaxId&gt;,...?format=(biopax|graphml|gmx|gmt)&<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b> ")
				.append("<ul>")
				.append("<li>format - specifies the output format</li>")
				.append("<li>recursive - only if format=biopax, whether or not to output referenced objects</li>")
				.append("</ul>")
				.append("</td></tr>")
			.append("<tr><td valign=top><b>/all</b></td><td>")
				.append("Returns a list of all objects of the given type.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /all/&lt;type&gt;?format=(biopax|attributes|ids)&recursive=(true|false)&derived=(true|false)&attributes=(&lt;attr&gt;:&lt;attr&gt;:...)<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b><br/>")
				.append("<ul>")
				.append("<li>format - specifies the output format</li>")
				.append("<li>derived - output all objects derived from <type> </li>")
				.append("<li>recursive - only if format=biopax, whether or not to output referenced objects</li>")
				.append("<li>attributes - only if format=attributes, which attributes to show, separated by ':'.<br/>Available attributes: type, name/standardName, organism, displayName</li>")
				.append("</ul>")
				.append("</td></tr>")
			.append("<tr><td valign=top><b>/all</b></td><td>")
				.append("Returns a list of all types.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /all/?filter=(biopax|sbml|none)<br/>")
				.append("<br/>")
				.append("<b>Parameters:</b><br/>")
				.append("<ul>")
				.append("<li>filter - restrict to BioPAX or SBML objects </li>")
				.append("</ul>")
				.append("</td></tr>")
			.append("<tr><td valign=top><b>/info/xrefdbs</b></td><td>")
				.append("Returns a list of all databases referenced.")
				.append("</td></tr>");
	}

	return "";

}

bool GetObjectServerHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{
	QString path(req->path());

	if ( GetObjectServerHandler::id.exactMatch(path) || GetObjectServerHandler::get.exactMatch(path) )
	{
		QString id = path.section('/', 2, 3);

		std::set<UnipaxId> ids;

		QStringList l = id.split(",");
		for (int i = 0; i < l.length(); ++i)
		{
			bool okay;

			UnipaxId tmp = l.at(i).toULongLong(&okay);
			if (okay)
			{
				if ((tmp >> 24) == UniPAX::ClassType::idResultObject) // if ID is of ResultObject, replace by contained object IDs.
				{
					std::cerr << "GetObjectServerHandler::handle : replacing ResultObject by its contents ..." << std::endl;
					UniPAX::ResultObjectPtr object = boost::dynamic_pointer_cast<UniPAX::ResultObject>(engine->getObject(tmp));
					std::set<UnipaxId> result_ids = object->getObjectIds();
					for (std::set<UnipaxId>::iterator it = result_ids.begin(); it != result_ids.end(); ++it)
					{
						std::cerr << *it << std::endl;
						ids.insert(*it);
					}
				}
				else
				{
					ids.insert(tmp);
				}
			}
		}


		QString format = req->url().queryItemValue("format");
		if (format == "")
			format = "ids";

		respond(req, resp, ids, format);

		return true;
	}
	else if ( GetObjectServerHandler::datasource.exactMatch(path) )
	{
		QString id = path.section('/', 2, 3);
		QString format = req->url().queryItemValue("format");

		UnipaxId i = id.toULongLong();

		std::map<UnipaxId, std::vector<UnipaxId> > pathways;
		if (!engine->getDBManager()->listPathwaysById(pathways))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("Error while fetching all pathway ids for datasource.\n"));
			resp->end();

			return true;
		}


		if (pathways.find(i) == pathways.end())
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("No pathways found for the given datasource id.\n"));
			resp->end();

			return true;
		}

		std::set<UnipaxId> pathway_vec;
		for (std::vector<UnipaxId>::iterator pathway_it = pathways[i].begin(); pathway_it != pathways[i].end(); pathway_it++)
		{
			pathway_vec.insert(*pathway_it);
		}

		QString datasource_name = "network";

		bool ok = false;
		UniPAX::SERVER::Attributes attr = engine->getAttributes(i, ok);

		if (ok)
		{
			datasource_name = attr.displayName.replace(" ","");
		}
		datasource_name = "attachment; filename=unipax." + datasource_name;

		if (format == "gmt")
		{
			datasource_name = datasource_name + ".geneid.gmt";
		}
		else if (format == "biopax")
		{
			datasource_name = datasource_name + ".owl";
		}
		resp->setHeader("Content-Disposition", datasource_name);
		respond(req, resp, pathway_vec, format);

		return true;
	}
	else if ( GetObjectServerHandler::all.exactMatch(path) )
	{
		QString type = path.section('/', 2, 3);

		std::set<UnipaxId> result;
		try {
		engine->getUnipaxIdsByType(result, type);


		QString format = req->url().queryItemValue("format");
		if (format == "")
			format = "ids";

		respond(req, resp, result, format);
		} catch (std::runtime_error e) {
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString(e.what()));
			resp->end();
			return true;
		}

	}
	else if (GetObjectServerHandler::all_types.exactMatch(path))
	{

		QString filter = req->url().queryItemValue("filter").toLower();

		QTextStream out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);

		if (filter == "" || filter == "biopax")
		{
			out << "BindingFeature\n";
			out << "BioSource\n";
			out << "BiochemicalPathwayStep\n";
			out << "BiochemicalReaction\n";
			out << "Catalysis\n";
			out << "CellVocabulary\n";
			out << "CellularLocationVocabulary\n";
			out << "ChemicalStructure\n";
			out << "Complex\n";
			out << "ComplexAssembly\n";
			out << "Control\n";
			out << "ControlledVocabulary\n";
			out << "Conversion\n";
			out << "CovalentBindingFeature\n";
			out << "Degradation\n";
			out << "DeltaG\n";
			out << "Dna\n";
			out << "DnaReference\n";
			out << "DnaRegion\n";
			out << "DnaRegionReference\n";
			out << "Entity\n";
			out << "EntityFeature\n";
			out << "EntityReference\n";
			out << "EntityReferenceTypeVocabulary\n";
			out << "Evidence\n";
			out << "EvidenceCodeVocabulary\n";
			out << "ExperimentalForm\n";
			out << "ExperimentalFormVocabulary\n";
			out << "FragmentFeature\n";
			out << "Gene\n";
			out << "GeneticInteraction\n";
			out << "Interaction\n";
			out << "InteractionVocabulary\n";
			out << "KPrime\n";
			out << "ModificationFeature\n";
			out << "Modulation\n";
			out << "MolecularInteraction\n";
			out << "Pathway\n";
			out << "PathwayStep\n";
			out << "PhenotypeVocabulary\n";
			out << "PhysicalEntity\n";
			out << "Protein\n";
			out << "ProteinReference\n";
			out << "Provenance\n";
			out << "PublicationXref\n";
			out << "RelationshipTypeVocabulary\n";
			out << "RelationshipXref\n";
			out << "Rna\n";
			out << "RnaReference\n";
			out << "RnaRegion\n";
			out << "RnaRegionReference\n";
			out << "Score\n";
			out << "SequenceInterval\n";
			out << "SequenceLocation\n";
			out << "SequenceModificationVocabulary\n";
			out << "SequenceRegionVocabulary\n";
			out << "SequenceSite\n";
			out << "SmallMolecule\n";
			out << "SmallMoleculeReference\n";
			out << "Stoichiometry\n";
			out << "TemplateReaction\n";
			out << "TemplateReactionRegulation\n";
			out << "Thing\n";
			out << "TissueVocabulary\n";
			out << "Transport\n";
			out << "TransportWithBiochemicalReaction\n";
			out << "UnificationXref\n";
			out << "UtilityClass\n";
			out << "Xref\n";
		}

		if (filter == "" || filter == "sbml")
		{
			out << "AlgebraicRule\n";
			out << "AssignmentRule\n";
			out << "Constraint\n";
			out << "Delay\n";
			out << "Event\n";
			out << "EventAssignment\n";
			out << "FunctionDefinition\n";
			out << "InitialAssignment\n";
			out << "KineticLaw\n";
			out << "LocalParameter\n";
			out << "Math\n";
			out << "Model\n";
			out << "Parameter\n";
			out << "Priority\n";
			out << "RateRule\n";
			out << "Rule\n";
			out << "SBase\n";
			out << "Trigger\n";
			out << "Unit\n";
			out << "UnitDefinition\n";
		}

		if (filter == "")
		{
			out << "Experiment\n";
			out << "ImportSource\n";
			out << "Mapping\n";
			out << "Sample\n";
			out << "UPBase\n";
		}

		resp->end();

		return true;
	}
	else if (GetObjectServerHandler::info_xrefs.exactMatch(path))
	{

		QString filter = req->url().queryItemValue("filter").toLower();

		QTextStream out(dynamic_cast<QIODevice*>(resp->get_connection()->get_socket()));
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");


		QStringList dbs;
		try
		{
			engine->getXrefDbs(dbs);
			resp->writeHead(200);
			for (int i = 0; i < dbs.length(); ++i)
				out << dbs.at(i) << "\n";

		}
		catch (std::exception & e)
		{
			resp->writeHead(500);
			out << "ERROR: " << e.what() << "\n";
		}

		resp->end();

		return true;
	}

	return false;
}

Q_EXPORT_PLUGIN2(GetObjectServerHandler, GetObjectServerHandler)


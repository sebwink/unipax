#include <UNIPAX/KERNEL/Kernel.h>

#include <UNIPAX/GRAPH/LEMON/GMLGraphWriter.h>
#include <UNIPAX/GRAPH/LEMON/SIFGraphWriter.h>

#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#include <UNIPAX/GRAPH/MAPPING/MYSQL/MySQLMappingEngine.h>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#include <UNIPAX/GRAPH/MAPPING/ORACLE/OracleMappingEngine.h>
#endif

#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#include <UNIPAX/KERNEL/all.h>

#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>

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

int main(int argC, char** argV)
{
	std::string unipax_arg;
	std::string unipax_pw;
	std::string output;
	std::string format("gml");

	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
				("help,h", "produce help message")
				("clean,c", "Rebuild cache")
				("password,p", boost::program_options::value< std::string >(&unipax_pw), "Password for UniPAX database connection")
#ifdef ODB_MYSQL
				("unipax,u", boost::program_options::value< std::string >(&unipax_arg), "UniPAX database connection in format: username@hostname[:port]/dbname")
#elif defined ODB_ORACLE
				("unipax,u", boost::program_options::value< std::string >(&unipax_arg), "UniPAX database connection in format: username@hostname[:port]/sid")
#endif
				("output,o", boost::program_options::value< std::string >(&output), "Output file name")
				("format,f", boost::program_options::value< std::string >(&format), "Output format (sif|gml*|lemon) * = standard")
				;
	boost::program_options::positional_options_description pod;
	pod.add("unipax", 1);
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argC, argV).options(desc).positional(pod).run(), vm);
	boost::program_options::notify(vm);
	if (vm.count("help") || !vm.count("unipax"))
	{
		std::cout << desc << std::endl;
		return 0;
	}

	bool rebuild_cache = false;
	if (vm.count("clean"))
		rebuild_cache = true;

	std::string unipax_host;
	std::string unipax_user;
	std::string unipax_database;
#ifdef ODB_MYSQL
	int unipax_port = 3306;
#elif defined ODB_ORACLE
	int unipax_port = 1521;
#endif

	std::size_t pos = 0;
	if ( (pos = unipax_arg.find_first_of('@')) != unipax_arg.npos)
	{
		unipax_user = unipax_arg.substr(0, pos);
		unipax_arg = unipax_arg.substr(pos + 1);
	} else
	{
		std::cerr << "UniPAX username not found" << std::endl;
		return -1;
	}

	if ( (pos = unipax_arg.find_first_of(':')) != unipax_arg.npos)
	{
		unipax_host = unipax_arg.substr(0, pos);
		unipax_arg = unipax_arg.substr(pos + 1);

		if ( (pos = unipax_arg.find_first_of('/')) != unipax_arg.npos)
		{
			std::stringstream ss;
			ss << unipax_arg.substr(0, pos);
			ss >> unipax_port;
			unipax_arg = unipax_arg.substr(pos + 1);
		} else
		{
			std::cerr << "UniPAX database not found" << std::endl;
			return -1;
		}

	} else if ( (pos = unipax_arg.find_first_of('/')) != unipax_arg.npos)
	{
		unipax_host = unipax_arg.substr(0, pos);
		unipax_arg = unipax_arg.substr(pos + 1);
	} else
	{
		std::cerr << "UniPAX host not found" << std::endl;
		return -1;
	}

	unipax_database = unipax_arg;

	if (!vm.count("password"))
	{
		std::cerr << "Please enter password for UniPAX database (" << unipax_user << "@" << unipax_host << ":" << unipax_port << "/" << unipax_database << ")" << std::flush;
		unipax_pw = getpass(": ");
	}


#ifdef ODB_MYSQL
	boost::shared_ptr<UniPAX::mysql::MySQLManager> manager(new UniPAX::mysql::MySQLManager());
#elif defined ODB_ORACLE
	boost::shared_ptr<UniPAX::oracle::OracleManager> manager(new UniPAX::oracle::OracleManager());
#endif
	manager->setDBCredentials(unipax_user, unipax_pw, unipax_host, unipax_port, unipax_database);
	if (!manager->initDatabase())
		return -1;

#ifdef ODB_MYSQL
	UniPAX::GRAPH::mysql::MySQLMappingEngine mapping_engine(manager);
#elif defined ODB_ORACLE
	UniPAX::GRAPH::oracle::OracleMappingEngine mapping_engine(manager);
#endif


	// this has to called once after creating the database (enabled by -c program option)
	if (rebuild_cache)
		mapping_engine.rebuildDatabaseCache();


	std::cerr << "Loading regulatory network... " << std::endl;

	// using all entity types
	boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> rg = mapping_engine.createRegulatoryNetwork(UniPAX::Kernel::children("PhysicalEntity", true));
	std::cerr << "Add Complex Assemblies: " << mapping_engine.addComplexAssemblies(*rg, UniPAX::Kernel::children("PhysicalEntity", true), true) << std::endl;
	std::cerr << "Add Interactions: " << mapping_engine.addInteractions(*rg, UniPAX::Kernel::children("PhysicalEntity", true)) << std::endl;

	std::cerr << "Network contains " << lemon::countNodes(rg->graph) << " nodes and " << lemon::countArcs(rg->graph) << " edges." << std::endl;

	// load regulatory types (ACTIVATION, INHIBITION, phosphorylation, etc.)
	UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcMap<std::string> regulation_types(rg->graph);
	mapping_engine.mapRegulationTypes(*rg, regulation_types);

	// load uniprot ids
	UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> uniprotMap(rg->graph);
	mapping_engine.mapXrefData(*rg, uniprotMap, "Reactome");

	// load display names
	/*UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<std::string> nameMap(rg->graph);
	for(UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeIt n(rg->graph); n != lemon::INVALID; ++n)
	{
		boost::shared_ptr<UniPAX::Entity> ent = boost::dynamic_pointer_cast<UniPAX::Entity>(manager->getObjectByID(rg->node_id_map[n]));
		if(ent) {
			nameMap[n] = ent->get_firstName();
		}
	}*/

	// load types the nodes represent
	lemon::ListDigraph::NodeMap<std::string> nodeTypeMap(rg->graph);
	mapping_engine.mapNodeTypes(*rg, nodeTypeMap);

	// load types the arcs represent
	lemon::ListDigraph::ArcMap<std::string> arcTypeMap(rg->graph);
	mapping_engine.mapArcTypes(*rg, arcTypeMap);

	// modify the regulatory network
//	mapping_engine.filterByOrganism(*rg, 16777217) // apply organism filter
//	mapping_engine.filterByPathway(*rg, 620757637)
//			.filterNodes(nodeTypeMap, std::string("Protein"), std::equal_to<std::string>()) // filter by type of "Protein"
//			.filterArcs(regulation_types, std::string("ACTIVATION")) // restict to activations
//	.eraseDisconnectedNodes(); // remove nodes with degree = 0



	// Example on how to map expression values using unipax Id

	std::map<UnipaxId, double> unipaxId_expression_values; // fill this map with your values


	UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<double> targetData(rg->graph);
	rg->mapNodeData(targetData, // save the mapping in targetData
			UniPAX::GRAPH::data_mapping_function<UniPAX::GRAPH::RegulatoryNetwork::Graph::Node>(unipaxId_expression_values, -1.0)  // function for mapping given values
	);

	//  or use this static template function

//	UniPAX::GRAPH::mapNodeData(*rg,
//			targetData,
//			UniPAX::GRAPH::data_mapping_function<UniPAX::GRAPH::RegulatoryNetwork::Graph::Node>(unipaxId_expression_values, -1.0)
//	);


	// Example on how to map expression values using other node maps (here, uniprot data source keys)

	std::map<std::string, double> uniprotId_expression_values; // fill this map with your values

	UniPAX::GRAPH::RegulatoryNetwork::Graph::NodeMap<double> targetData2(rg->graph);
	rg->mapNodeData(targetData2, // save the mapping in targetData2
			uniprotMap, // use this node map as key for mapping
			UniPAX::GRAPH::data_mapping_function<UniPAX::GRAPH::RegulatoryNetwork::Graph::Node, std::string>(uniprotId_expression_values, -1.0) // function for mapping given values
	);

	//  or use this static template function

//	UniPAX::GRAPH::mapNodeData(*rg,
//			targetData2,
//			uniprotMap,
//			UniPAX::GRAPH::data_mapping_function<UniPAX::GRAPH::RegulatoryNetwork::Graph::Node, std::string>(uniprotId_expression_values, -1.0)
//	);

	std::cerr << "After filtering " << lemon::countNodes(rg->graph) << " nodes and " << lemon::countArcs(rg->graph) << " arcs."  << std::endl;

	if (output != "")
	{
		if (format == "sif")
		{
			lemon::sifDigraphWriter(rg->graph, output)
				.labelMap(rg->node_id_map)
				.relationMap(regulation_types).run();
//				.nodeMap("uniprot", uniprotMap, std::cout)
//				.nodeMap("names", nameMap, std::cout).run();
		}
		else if (format == "lemon")
		{
			lemon::digraphWriter(rg->graph, output).nodeMap("unipaxId", rg->node_id_map).nodeMap("label", uniprotMap).arcMap("label", regulation_types).run();
		}
		else
		{
			lemon::gmlDigraphWriter(rg->graph, output).nodeMap("unipaxId", rg->node_id_map).nodeMap("label", uniprotMap).arcMap("label", regulation_types).run();
		}
	}
	else
	{
		if (format == "sif")
		{
			lemon::sifDigraphWriter(rg->graph, std::cout).labelMap(uniprotMap).relationMap(regulation_types).run();
		}
		else if (format == "lemon")
		{
			lemon::digraphWriter(rg->graph, std::cout).nodeMap("unipaxId", rg->node_id_map).nodeMap("label", uniprotMap).arcMap("label", regulation_types).run();
		}
		else
		{
			lemon::gmlDigraphWriter(rg->graph, std::cout).nodeMap("unipaxId", rg->node_id_map).nodeMap("label", uniprotMap).arcMap("label", regulation_types).run();
		}
	}



	return 0;
}

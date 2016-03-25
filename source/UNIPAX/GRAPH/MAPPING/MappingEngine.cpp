#include <UNIPAX/GRAPH/MAPPING/MappingEngine.h>
#include <UNIPAX/PERSISTENCE/DBManager.h>

UniPAX::GRAPH::MappingEngine::MappingEngine(boost::shared_ptr<DBManager> _db_manager) :
	db_manager(_db_manager),
	network_cache(cache_size)
{

}

void UniPAX::GRAPH::MappingEngine::mapNodeTypes(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeTypeMap)
{
	for (RegulatoryNetwork::Graph::NodeIt it(network.graph); it != lemon::INVALID; ++it)
	{
		nodeTypeMap[it] = UniPAX::DBManager::getType(network.node_id_map[it], "");
	}
}

void UniPAX::GRAPH::MappingEngine::mapNodeTypes(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeTypeMap)
{
	for (MetabolicNetwork::Graph::NodeIt it(network.graph); it != lemon::INVALID; ++it)
	{
		nodeTypeMap[it] = UniPAX::DBManager::getType(network.node_id_map[it], "");
	}
}

void UniPAX::GRAPH::MappingEngine::mapNodeTypes(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeTypeMap)
{
	for (ProteinProteinInteractionNetwork::Graph::NodeIt it(network.graph); it != lemon::INVALID; ++it)
	{
		nodeTypeMap[it] = UniPAX::DBManager::getType(network.node_id_map[it], "");
	}
}

void UniPAX::GRAPH::MappingEngine::mapArcTypes(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & arcTypeMap)
{
	for (RegulatoryNetwork::Graph::ArcIt it(network.graph); it != lemon::INVALID; ++it)
	{
		arcTypeMap[it] = UniPAX::DBManager::getType(network.arc_id_map[it], "");
	}
}

void UniPAX::GRAPH::MappingEngine::mapEdgeTypes(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::EdgeMap<std::string> & edgeTypeMap)
{
	for (ProteinProteinInteractionNetwork::Graph::EdgeIt it(network.graph); it != lemon::INVALID; ++it)
	{
		edgeTypeMap[it] = UniPAX::DBManager::getType(network.edge_id_map[it], "");
	}
}

std::string UniPAX::GRAPH::MappingEngine::collate(const std::set<std::string> words)
{
	std::stringstream ss;
	for (std::set<std::string>::const_iterator it=words.begin(); it != words.end(); ++it)
	{
		ss << *it;
	}
	return ss.str();
}

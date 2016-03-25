#ifndef MAPPINGENGINE_H_
#define MAPPINGENGINE_H_

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/COMMON/MRUList.h>

#include <UNIPAX/GRAPH/MAPPING/BiologicalNetwork.h>
#include <UNIPAX/GRAPH/MAPPING/MetabolicNetwork.h>
#include <UNIPAX/GRAPH/MAPPING/ProteinProteinInteractionNetwork.h>
#include <UNIPAX/GRAPH/MAPPING/RegulatoryNetwork.h>
#include <UNIPAX/GRAPH/MAPPING/RelationsGraph.h>

#include <UNIPAX/KERNEL/EXT/ResultObject.h>

#include <lemon/list_graph.h>
#include <lemon/maps.h>

#include <boost/shared_ptr.hpp>

#include <set>
#include <string>

namespace UniPAX
{

namespace GRAPH
{

template<typename _Target, typename _Id, typename _Result>
struct mapping_function
{
	typedef _Target first_argument_type;   ///< the type of the first argument
	///  (no surprises here)

	typedef _Id second_argument_type;  ///< the type of the second argument
	typedef _Result result_type;         ///< type of the return type

};

template<typename _Target, typename _Id = UnipaxId, typename _Result = double>
struct data_mapping_function : public mapping_function<_Target, _Id, _Result>
{
	std::map<_Id, _Result> & values;
	_Result unknown_value;

	data_mapping_function(std::map<_Id, _Result> & _values, _Result _unknown_value) : values(_values), unknown_value(_unknown_value)
	{
	}

	_Result operator()(const _Target & t, const _Id & id) const
	{
		if (values.find(id) != values.end())
			return values[id];
		else
			return unknown_value;
	}
};

template<typename T, typename TV, template<class, class, class> class F> static void mapNodeData(T & network, typename T::Graph::template NodeMap<TV> & targetNodeDataMap, const F<typename T::Graph::Node, UnipaxId, TV> & f)
{
	for (typename T::Graph::NodeIt it(network.graph); it != lemon::INVALID; ++it)
	{
		targetNodeDataMap[it] = f(it, network.nodeIdMap[it]);
	}
}

template<typename T, typename TV, typename MV, template<class, class, class> class F> static void mapNodeData(T & network, typename T::Graph::template NodeMap<TV> & targetNodeDataMap, typename T::Graph::template NodeMap<MV> & mappingNodeDataMap, const F<typename T::Graph::Node, MV, TV> & f)
{
	for (typename T::Graph::NodeIt it(network.graph); it != lemon::INVALID; ++it)
	{
		targetNodeDataMap[it] = f(it, mappingNodeDataMap[it]);
	}
}

template<typename T, typename TV, template<class, class, class> class F> static void mapEdgeData(T & network, typename T::Graph::template EdgeMap<TV> & targetEdgeDataMap, const F<typename T::Graph::Edge, UnipaxId, TV> & f)
{
	for (typename T::Graph::EdgeIt it(network.graph); it != lemon::INVALID; ++it)
	{
		targetEdgeDataMap[it] = f(it, network.edgeIdMap[it]);
	}
}

template<typename T, typename TV, typename MV, template<class, class, class> class F> static void mapEdgeData(T & network, typename T::Graph::template EdgeMap<TV> & targetEdgeDataMap, typename T::Graph::template EdgeMap<MV> & mappingEdgeDataMap, const F<typename T::Graph::Edge, MV, TV> & f)
{
	for (typename T::Graph::EdgeIt it(network.graph); it != lemon::INVALID; ++it)
	{
		targetEdgeDataMap[it] = f(it, mappingEdgeDataMap[it]);
	}
}

template<typename T, typename TV, template<class, class, class> class F> static void mapArcData(T & network, typename T::Graph::template ArcMap<TV> & targetArcDataMap, const F<typename T::Graph::Arc, UnipaxId, TV> & f)
{
	for (typename T::Graph::ArcIt it(network.graph); it != lemon::INVALID; ++it)
	{
		targetArcDataMap[it] = f(it, network.arcIdMap[it]);
	}
}

template<typename T, typename TV, typename MV, template<class, class, class> class F> static void mapArcData(T & network, typename T::Graph::template ArcMap<TV> & targetArcDataMap, typename T::Graph::template ArcMap<MV> & mappingArcDataMap, const F<typename T::Graph::Arc, MV, TV> & f)
{
	for (typename T::Graph::ArcIt it(network.graph); it != lemon::INVALID; ++it)
	{
		targetArcDataMap[it] = f(it, mappingArcDataMap[it]);
	}
}

class UNIPAX_EXPORT MappingEngine
{
public:

	MappingEngine(boost::shared_ptr<DBManager> _db_manager);

	virtual ~MappingEngine()
	{

	}

	virtual bool needsRebuildDatabaseCache() = 0;

	virtual void rebuildDatabaseCache() = 0;

	virtual boost::shared_ptr<RelationsGraph> createRelationsGraph() = 0;
	virtual boost::shared_ptr<ProteinProteinInteractionNetwork> createProteinProteinInteractionNetwork(const std::set<std::string> & physical_entities) = 0;
	virtual boost::shared_ptr<ProteinProteinInteractionNetwork> createProteinProteinInteractionNetwork(const ResultObject & result_obj) = 0;
	virtual boost::shared_ptr<RegulatoryNetwork> createRegulatoryNetwork(const std::set<std::string> & physical_entities) = 0;
	virtual	boost::shared_ptr<RegulatoryNetwork> createRegulatoryNetwork(const std::set<std::string> & physical_entities, const ResultObject & result_obj) = 0;


	virtual int addInteractions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities) = 0;
	virtual int addInteractions(RegulatoryNetwork & network, const ResultObject & result_obj) = 0;
	virtual int addTemplateRegulations(RegulatoryNetwork & regulatory, const std::set<std::string> & physical_entities) = 0;
	virtual int addControlOfBiochemicalReactions(RegulatoryNetwork & regulatory, const std::set<std::string> & physical_entities) = 0;
	virtual int addControlOfConversions(RegulatoryNetwork & regulatory, const std::set<std::string> & physical_entities) = 0;
	virtual int addComplexAssemblies(RegulatoryNetwork & regulatory, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions = false) = 0;
	virtual int addComplexAssemblies(RegulatoryNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj, bool search_in_biochemicalreactions = false) = 0;

	virtual int addInteractions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities) = 0;
	virtual int addInteractions(ProteinProteinInteractionNetwork & network, const ResultObject & result_obj) = 0;
	virtual int addTemplateRegulations(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities) = 0;
	virtual int addTemplateRegulations(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj) = 0;
	virtual int addControlOfBiochemicalReactions(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities) = 0;
	virtual int addControlOfBiochemicalReactions(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj) = 0;
	virtual int addComplexAssemblies(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions = false) = 0;
	virtual int addComplexAssemblies(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj, bool search_in_biochemicalreactions = false) = 0;

	virtual bool mapRegulationTypes(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & regulation_type) = 0;

	virtual bool mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db) = 0;
	virtual bool mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & arcMap, std::string external_db) = 0;
	virtual bool mapNames(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "") = 0;

	virtual bool mapXrefData(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db) = 0;
	virtual bool mapXrefData(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::EdgeMap<std::string> & edgeMap, std::string external_db) = 0;
	virtual bool mapNames(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "") = 0;

	virtual bool getEntityIdsByOrganism(std::set<UnipaxId> & organism_entites, UnipaxId organismId) = 0;
	virtual bool getEntityIdsByPathway(std::set<UnipaxId> & pathway_entites, UnipaxId pathwayId) = 0;

	virtual std::string getName(UnipaxId unipaxId) = 0;
	virtual std::string getPathwayName(UnipaxId unipaxId) = 0;
	virtual std::string getPathwayDescription(UnipaxId unipaxId) = 0;

	virtual bool filterByOrganisms(RegulatoryNetwork & network, std::set<UnipaxId> & organismIds) = 0;
	virtual bool filterByOrganisms(ProteinProteinInteractionNetwork & network, std::set<UnipaxId> & organismIds) = 0;
	virtual bool filterByPathways(RegulatoryNetwork & network, std::set<UnipaxId> & pathwayIds) = 0;
	virtual bool filterByPathways(ProteinProteinInteractionNetwork & network, std::set<UnipaxId> & pathwayIds) = 0;

	virtual	boost::shared_ptr<MetabolicNetwork> createMetabolicNetwork(const std::set<std::string> & physical_entities) = 0;
	virtual	boost::shared_ptr<MetabolicNetwork> createMetabolicNetwork(const std::set<std::string> & physical_entities, const ResultObject & result_obj) = 0;
	virtual bool filterByOrganisms(MetabolicNetwork & network, std::set<UnipaxId> & organismIds) = 0;
	virtual bool filterByPathways(MetabolicNetwork & network, std::set<UnipaxId> & pathwayIds) = 0;


	void mapNodeTypes(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeTypeMap);
	void mapNodeTypes(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeTypeMap);
	void mapNodeTypes(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeTypeMap);
	void mapArcTypes(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & arcTypeMap);
	void mapEdgeTypes(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::EdgeMap<std::string> & edgeTypeMap);

protected:

	static std::string collate(const std::set<std::string>);

	boost::shared_ptr<DBManager> db_manager;
	MRUList<std::string, BiologicalNetworkPtr> network_cache;
	static const std::size_t cache_size = 10;

};

typedef UnipaxPtr<MappingEngine>::type MappingEnginePtr;

}

}


#endif /* MAPPINGENGINE_H_ */

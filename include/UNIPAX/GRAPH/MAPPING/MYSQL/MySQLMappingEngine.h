#ifndef MYSQLCACHE_H_
#define MYSQLCACHE_H_

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/GRAPH/MAPPING/MappingEngine.h>
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>

#include <UNIPAX/KERNEL/EXT/ResultObject.h>

#include <UNIPAX/KERNEL/Kernel.h>


#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QSqlError>

#include <map>
#include <exception>

namespace UniPAX
{

namespace GRAPH
{

namespace mysql
{

template<typename T>
struct TNodeMap
{
	typedef typename T::Graph::template NodeMap<std::string> type;
};

template<typename T>
struct TNodeMapPtr
{
	typedef typename UnipaxPtr<typename TNodeMap<T>::type>::type type;
};


class UNIPAX_EXPORT MySQLMappingEngine : public UniPAX::GRAPH::MappingEngine
{

public:

	MySQLMappingEngine(boost::shared_ptr<UniPAX::DBManager> _db_manager);

	~MySQLMappingEngine()
	{

	}

	bool needsRebuildDatabaseCache();

	void rebuildDatabaseCache();

	boost::shared_ptr<RelationsGraph> createRelationsGraph();

	boost::shared_ptr<ProteinProteinInteractionNetwork> createProteinProteinInteractionNetwork(const std::set<std::string> & physical_entities);
	boost::shared_ptr<ProteinProteinInteractionNetwork> createProteinProteinInteractionNetwork(const ResultObject & result_obj);

	boost::shared_ptr<RegulatoryNetwork> createRegulatoryNetwork(const std::set<std::string> & physical_entities, const ResultObject & result_obj);

	boost::shared_ptr<RegulatoryNetwork> createRegulatoryNetwork(const std::set<std::string> & physical_entities);

	boost::shared_ptr<MetabolicNetwork> createMetabolicNetwork(const std::set<std::string> & physical_entities);
	boost::shared_ptr<MetabolicNetwork> createMetabolicNetwork(const std::set<std::string> & physical_entities, const ResultObject & result_obj);

	int addInteractions(RegulatoryNetwork & network, const ResultObject & result_obj);

	int addInteractions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities);

	int addInteractions(ProteinProteinInteractionNetwork & network, const ResultObject & result_obj);

	int addInteractions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities);

	int addTemplateRegulations(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, const ResultObject & result_obj);

	int addTemplateRegulations(RegulatoryNetwork & network, const std::set<std::string> & physical_entities);

	int addControlOfBiochemicalReactions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, const ResultObject & result_obj);

	int addControlOfBiochemicalReactions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities);

	int addControlOfConversions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, const ResultObject & result_obj);

	int addControlOfConversions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities);

	int addComplexAssemblies(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, const ResultObject & result_obj, bool search_in_biochemicalreactions = false);

	int addComplexAssemblies(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions = false);

	int addTemplateRegulations(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities);

	int addControlOfBiochemicalReactions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities);

	int addComplexAssemblies(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions = false);

	int addBiochemicalReactions(MetabolicNetwork & network, const std::set<std::string> & physical_entities);
	int addBiochemicalReactions(MetabolicNetwork & network, const std::set<std::string> & physical_entities, const ResultObject & result_obj);

	bool mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db);

	bool mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & arcMap, std::string external_db);

	bool mapNames(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "");

	bool mapFeatures(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "");

	bool mapRegulationTypes(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & regulation_type);


	bool filterByOrganisms(RegulatoryNetwork & network, std::set<UnipaxId> & organismIds);

	bool filterByPathway(RegulatoryNetwork & network, UnipaxId pathwayId);

	bool filterByPathways(RegulatoryNetwork & network, std::set<UnipaxId> & pathwayIds);


	int addTemplateRegulations(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj);

	int addControlOfBiochemicalReactions(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj);

	int addComplexAssemblies(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj, bool search_in_biochemicalreactions = false);

	bool mapXrefData(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db);

	bool mapXrefData(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::EdgeMap<std::string> & edgeMap, std::string external_db);

	bool mapNames(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "");

	bool mapFeatures(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "");

	bool filterByOrganisms(ProteinProteinInteractionNetwork & network, std::set<UnipaxId> & organismIds);

	bool filterByPathways(ProteinProteinInteractionNetwork & network, std::set<UnipaxId> & pathwayIds);



	bool mapXrefData(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db);

	//	bool mapXrefData(MetabolicNetwork & network, MetabolicNetwork::Graph::ArcMap<std::string> & edgeMap, std::string external_db);

	bool mapNames(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "");

	bool mapFeatures(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "");

	bool mapSeriesData(MetabolicNetwork & network, std::vector<std::pair<std::string, TNodeMapPtr<MetabolicNetwork>::type> > & nodeMap, UnipaxId result_id);
	bool mapSeriesData(ProteinProteinInteractionNetwork & network, std::vector<std::pair<std::string, TNodeMapPtr<ProteinProteinInteractionNetwork>::type> > & nodeMap, UnipaxId result_id);
	bool mapSeriesData(RegulatoryNetwork & network, std::vector<std::pair<std::string, TNodeMapPtr<RegulatoryNetwork>::type> > & nodeMap, UnipaxId result_id);

	bool filterByOrganisms(MetabolicNetwork & network, std::set<UnipaxId> & organismIds);

	bool filterByPathways(MetabolicNetwork & network, std::set<UnipaxId> & pathwayIds);



	bool getEntityIdsByOrganism(std::set<UnipaxId> & organism_entites, UnipaxId organismId);

	bool getEntityIdsByPathway(std::set<UnipaxId> & pathway_entites, UnipaxId pathwayId);



	std::string getName(UnipaxId unipaxId);
	std::string getPathwayName(UnipaxId unipaxId);
	std::string getPathwayDescription(UnipaxId unipaxId);

private :
	template <typename N> int _addInteractions(N & network, const ResultObject & result_obj)
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::alterByInteractions: Failed to connect mysql with QT";
				return 0;
			}
		}

		std::map<UnipaxId, std::set<UnipaxId> > interaction_entity_map;

		UnipaxId interaction_base = DBManager::getBase("Interaction");

		// collect relations

		//for (std::set<UnipaxId>::const_iterator it = result_obj.getObjectIds().begin(); it != result_obj.getObjectIds().end(); it++)
		{
			//if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId min_id =*result_obj.getObjectIds().begin();
				UnipaxId max_id =*result_obj.getObjectIds().rbegin();
				QSqlQuery query = db->exec(QString("SELECT object_id, value FROM Interaction_participant WHERE value >= %1 AND value <= %2").arg(min_id).arg(max_id));

				while (query.next())
				{
					UnipaxId source = query.value(0).toULongLong();
					UnipaxId target = query.value(1).toULongLong();

					interaction_entity_map[source].insert(target);

				}
				query.finish();
			}
		}

		// create PPI graph

		std::set<UnipaxId> result_ids = result_obj.getObjectIds();
		int c = 0;

		for (std::map<UnipaxId, std::set<UnipaxId> >::const_iterator it = interaction_entity_map.begin(); it != interaction_entity_map.end(); it++)
		{
			if (it->second.size() <= 1)
				continue;

			for (std::set<UnipaxId>::const_iterator source = it->second.begin(); source != it->second.end(); source++)
			{
				typename N::Node sourceNode(lemon::INVALID);

				if (network.hasNode(*source))
					sourceNode = network.id_node_map[*source];
				else
				{
					if (result_ids.find(*source) != result_ids.end())
						sourceNode = network.createNode(*source);
				}

				std::set<UnipaxId>::const_iterator target(source);
				for (target++; target != it->second.end(); target++)
				{
					typename N::Node targetNode(lemon::INVALID);

					if (network.hasNode(*target))
						targetNode = network.getNode(*target);
					else
					{
						if (result_ids.find(*target) != result_ids.end())
							targetNode = network.createNode(*target);
					}
					if (sourceNode != lemon::INVALID && targetNode != lemon::INVALID)
						network.createEdge(sourceNode, targetNode, it->first);
				}
				++c;
			}
		}
		return c;
	}

	template <typename N> int _addInteractions(N & network, const std::set<std::string> & physical_entities)
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::alterByInteractions: Failed to connect mysql with QT";
				return 0;
			}
		}

		std::map<UnipaxId, std::set<UnipaxId> > interaction_entity_map;

		UnipaxId interaction_base = DBManager::getBase("Interaction");

		// collect relations

		for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
		{
			if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId entity_base = DBManager::getBase(*it);

				QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(interaction_base).arg(((interaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

				while (query.next())
				{
					UnipaxId source = query.value(0).toULongLong();
					UnipaxId target = query.value(1).toULongLong();

					interaction_entity_map[source].insert(target);

				}
				query.finish();
			}
		}

		// create PPI graph

		int c = 0;

		for (std::map<UnipaxId, std::set<UnipaxId> >::const_iterator it = interaction_entity_map.begin(); it != interaction_entity_map.end(); it++)
		{
			if (it->second.size() <= 1)
				continue;

			for (std::set<UnipaxId>::const_iterator source = it->second.begin(); source != it->second.end(); source++)
			{
				typename N::Node sourceNode;

				if (network.hasNode(*source))
					sourceNode = network.id_node_map[*source];
				else
					sourceNode = network.createNode(*source);

				std::set<UnipaxId>::const_iterator target(source);
				for (target++; target != it->second.end(); target++)
				{
					typename N::Node targetNode;

					if (network.hasNode(*target))
						targetNode = network.getNode(*target);
					else
						targetNode = network.createNode(*target);

					network.createEdge(sourceNode, targetNode, it->first);
				}

				++c;

			}
		}

		return c;

	}

	template <typename N> int _addTemplateRegulations(N & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::alterByTemplateRegulations: Failed to connect mysql with QT";
				return 0;
			}
		}

		std::map<UnipaxId, UnipaxId> templatereaction_entity_map;
		std::map<UnipaxId, UnipaxId> templatereactionregulation_templatereaction_map;
		std::map<UnipaxId, std::set<UnipaxId> > templatereactionregulation_entity_map;

		UnipaxId template_reaction_base = DBManager::getBase("TemplateReaction");

		UnipaxId template_reaction_regulation_base = DBManager::getBase("TemplateReactionRegulation");

		// collect template reactions and regulations

		for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
		{
			if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId entity_base = DBManager::getBase(*it);

				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(template_reaction_base).arg(((template_reaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						templatereaction_entity_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(template_reaction_regulation_base).arg(((template_reaction_regulation_base >> 24) + 1) << 24).arg(template_reaction_base).arg(((template_reaction_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						templatereactionregulation_templatereaction_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(template_reaction_regulation_base).arg(((template_reaction_regulation_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						templatereactionregulation_entity_map[source].insert(target);

					}
					query.finish();
				}
			}
		}


		// alter regulatory network
		std::set<UnipaxId> result_ids = result_obj.getObjectIds();
		int c = 0;

		for (std::map<UnipaxId, UnipaxId>::const_iterator it = templatereactionregulation_templatereaction_map.begin(); it != templatereactionregulation_templatereaction_map.end(); it++)
		{
			if (templatereaction_entity_map.find(it->second) != templatereaction_entity_map.end())
			{
				UnipaxId target = templatereaction_entity_map[it->second];

				if (templatereactionregulation_entity_map.find(it->first) != templatereactionregulation_entity_map.end())
				{
					std::set<UnipaxId> & sources = templatereactionregulation_entity_map[it->first];

					typename N::Node targetNode(lemon::INVALID);

					if (!sources.empty())
					{
						if (regulatory.hasNode(target))
							targetNode = regulatory.getNode(target);
						else
						{
							if (result_ids.find(target) != result_ids.end())
								targetNode = regulatory.createNode(target);
						}

						for (std::set<UnipaxId>::const_iterator sit = sources.begin(); sit != sources.end(); sit++)
						{
							UnipaxId source = *sit;

							typename N::Node sourceNode(lemon::INVALID);

							if (regulatory.hasNode(source))
								sourceNode = regulatory.getNode(source);
							else
							{
								if (result_ids.find(source) != result_ids.end())
									sourceNode = regulatory.createNode(source);
							}
							if (targetNode != lemon::INVALID && sourceNode != lemon::INVALID)
								regulatory.createEdge(sourceNode, targetNode, it->first);
						}
						++c;
					}
				}
			}
		}
		return c;
	}

	template <typename N> int _addTemplateRegulations(N & regulatory, const std::set<std::string> & physical_entities)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::alterByTemplateRegulations: Failed to connect mysql with QT";
				return 0;
			}
		}

		std::map<UnipaxId, UnipaxId> templatereaction_entity_map;
		std::map<UnipaxId, UnipaxId> templatereactionregulation_templatereaction_map;
		std::map<UnipaxId, std::set<UnipaxId> > templatereactionregulation_entity_map;

		UnipaxId template_reaction_base = DBManager::getBase("TemplateReaction");

		UnipaxId template_reaction_regulation_base = DBManager::getBase("TemplateReactionRegulation");

		// collect template reactions and regulations

		for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
		{
			if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId entity_base = DBManager::getBase(*it);

				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(template_reaction_base).arg(((template_reaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						templatereaction_entity_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(template_reaction_regulation_base).arg(((template_reaction_regulation_base >> 24) + 1) << 24).arg(template_reaction_base).arg(((template_reaction_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						templatereactionregulation_templatereaction_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(template_reaction_regulation_base).arg(((template_reaction_regulation_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						templatereactionregulation_entity_map[source].insert(target);

					}
					query.finish();
				}
			}
		}


		// alter regulatory network

		int c = 0;

		for (std::map<UnipaxId, UnipaxId>::const_iterator it = templatereactionregulation_templatereaction_map.begin(); it != templatereactionregulation_templatereaction_map.end(); it++)
		{
			if (templatereaction_entity_map.find(it->second) != templatereaction_entity_map.end())
			{
				UnipaxId target = templatereaction_entity_map[it->second];

				if (templatereactionregulation_entity_map.find(it->first) != templatereactionregulation_entity_map.end())
				{
					std::set<UnipaxId> & sources = templatereactionregulation_entity_map[it->first];

					typename N::Node targetNode;

					if (!sources.empty())
					{
						if (regulatory.hasNode(target))
							targetNode = regulatory.getNode(target);
						else
							targetNode = regulatory.createNode(target);

						for (std::set<UnipaxId>::const_iterator sit = sources.begin(); sit != sources.end(); sit++)
						{
							UnipaxId source = *sit;

							typename N::Node sourceNode;

							if (regulatory.hasNode(source))
								sourceNode = regulatory.getNode(source);
							else
								sourceNode = regulatory.createNode(source);

							regulatory.createEdge(sourceNode, targetNode, it->first);
						}

						++c;
					}
				}
			}

		}

		return c;
	}

	template <typename N> int _addControlOfBiochemicalReactions(N & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::alterByControlOfBiochemicalReactions: Failed to connect mysql with QT";
				return 0;
			}
		}

		// phosphorylations are stored using Control and BiochemicalReaction

		std::map<UnipaxId, UnipaxId> biochemicalreaction_entity_map;
		std::map<UnipaxId, UnipaxId> control_biochemicalreaction_map;
		std::map<UnipaxId, std::set<UnipaxId> > control_entity_map;

		UnipaxId biochemical_reaction_base = DBManager::getBase("BiochemicalReaction");

		UnipaxId control_base = DBManager::getBase("Control");

		// collect biochemical reactions and controls

		for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
		{
			if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId entity_base = DBManager::getBase(*it);

				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(biochemical_reaction_base).arg(((biochemical_reaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						biochemicalreaction_entity_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(control_base).arg(((control_base >> 24) + 1) << 24).arg(biochemical_reaction_base).arg(((biochemical_reaction_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						control_biochemicalreaction_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(control_base).arg(((control_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						control_entity_map[source].insert(target);

					}
					query.finish();
				}
			}
		}

		// alter network

		std::set<UnipaxId> result_ids = result_obj.getObjectIds();
		int c = 0;

		for (std::map<UnipaxId, UnipaxId>::const_iterator it = control_biochemicalreaction_map.begin(); it != control_biochemicalreaction_map.end(); it++)
		{
			if (biochemicalreaction_entity_map.find(it->second) != biochemicalreaction_entity_map.end())
			{
				UnipaxId target = biochemicalreaction_entity_map[it->second];

				if (control_entity_map.find(it->first) != control_entity_map.end())
				{
					std::set<UnipaxId> & sources = control_entity_map[it->first];

					typename N::Node targetNode(lemon::INVALID);

					if (!sources.empty())
					{
						if (regulatory.hasNode(target))
							targetNode = regulatory.getNode(target);
						else
						{
							if (result_ids.find(target) != result_ids.end())
								targetNode = regulatory.createNode(target);
						}

						for (std::set<UnipaxId>::const_iterator sit = sources.begin(); sit != sources.end(); sit++)
						{
							UnipaxId source = *sit;

							typename N::Node sourceNode(lemon::INVALID);

							if (regulatory.hasNode(source))
								sourceNode = regulatory.getNode(source);
							else
							{
								if (result_ids.find(source) != result_ids.end())
									sourceNode = regulatory.createNode(source);
							}

							if (targetNode !=lemon::INVALID && sourceNode != lemon::INVALID)
								regulatory.createEdge(sourceNode, targetNode, it->first);
						}
						++c;
					}
				}
			}
		}
		return c;
	}

	template <typename N> int _addControlOfBiochemicalReactions(N & regulatory, const std::set<std::string> & physical_entities)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::alterByControlOfBiochemicalReactions: Failed to connect mysql with QT";
				return 0;
			}
		}

		// phosphorylations are stored using Control and BiochemicalReaction

		std::map<UnipaxId, UnipaxId> biochemicalreaction_entity_map;
		std::map<UnipaxId, UnipaxId> control_biochemicalreaction_map;
		std::map<UnipaxId, std::set<UnipaxId> > control_entity_map;

		UnipaxId biochemical_reaction_base = DBManager::getBase("BiochemicalReaction");

		UnipaxId control_base = DBManager::getBase("Control");

		// collect biochemical reactions and controls

		for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
		{
			if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId entity_base = DBManager::getBase(*it);

				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(biochemical_reaction_base).arg(((biochemical_reaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						biochemicalreaction_entity_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(control_base).arg(((control_base >> 24) + 1) << 24).arg(biochemical_reaction_base).arg(((biochemical_reaction_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						control_biochemicalreaction_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(control_base).arg(((control_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						control_entity_map[source].insert(target);

					}
					query.finish();
				}
			}
		}

		// alter network

		int c = 0;

		for (std::map<UnipaxId, UnipaxId>::const_iterator it = control_biochemicalreaction_map.begin(); it != control_biochemicalreaction_map.end(); it++)
		{
			if (biochemicalreaction_entity_map.find(it->second) != biochemicalreaction_entity_map.end())
			{
				UnipaxId target = biochemicalreaction_entity_map[it->second];

				if (control_entity_map.find(it->first) != control_entity_map.end())
				{
					std::set<UnipaxId> & sources = control_entity_map[it->first];

					typename N::Node targetNode;

					if (!sources.empty())
					{
						if (regulatory.hasNode(target))
							targetNode = regulatory.getNode(target);
						else
							targetNode = regulatory.createNode(target);

						for (std::set<UnipaxId>::const_iterator sit = sources.begin(); sit != sources.end(); sit++)
						{
							UnipaxId source = *sit;

							typename N::Node sourceNode;

							if (regulatory.hasNode(source))
								sourceNode = regulatory.getNode(source);
							else
								sourceNode = regulatory.createNode(source);


							regulatory.createEdge(sourceNode, targetNode, it->first);
						}

						++c;
					}
				}
			}

		}

		return c;

	}

	template <typename N> int _addControlOfConversions(N & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLMappingEngine::_addControlOfConversions: Failed to connect mysql with QT";
				return 0;
			}
		}

		// protein regulations are stored using Control and Conversions

		std::map<UnipaxId, UnipaxId> conversion_entity_map;
		std::map<UnipaxId, UnipaxId> control_conversion_map;
		std::map<UnipaxId, std::set<UnipaxId> > control_entity_map;

		UnipaxId conversion_base = DBManager::getBase("Conversion");

		UnipaxId control_base = DBManager::getBase("Control");

		// collect biochemical reactions and controls

		for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
		{
			if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId entity_base = DBManager::getBase(*it);

				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(conversion_base).arg(((conversion_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						conversion_entity_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(control_base).arg(((control_base >> 24) + 1) << 24).arg(conversion_base).arg(((conversion_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						control_conversion_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(control_base).arg(((control_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						control_entity_map[source].insert(target);

					}
					query.finish();
				}
			}
		}

		// alter network

		std::set<UnipaxId> result_ids = result_obj.getObjectIds();
		int c = 0;

		for (std::map<UnipaxId, UnipaxId>::const_iterator it = control_conversion_map.begin(); it != control_conversion_map.end(); it++)
		{
			if (conversion_entity_map.find(it->second) != conversion_entity_map.end())
			{
				UnipaxId target = conversion_entity_map[it->second];

				if (control_entity_map.find(it->first) != control_entity_map.end())
				{
					std::set<UnipaxId> & sources = control_entity_map[it->first];

					typename N::Node targetNode(lemon::INVALID);

					if (!sources.empty())
					{
						if (regulatory.hasNode(target))
							targetNode = regulatory.getNode(target);
						else
						{
							if (result_ids.find(target) != result_ids.end())
								targetNode = regulatory.createNode(target);
						}

						for (std::set<UnipaxId>::const_iterator sit = sources.begin(); sit != sources.end(); sit++)
						{
							UnipaxId source = *sit;

							typename N::Node sourceNode(lemon::INVALID);

							if (regulatory.hasNode(source))
								sourceNode = regulatory.getNode(source);
							else
							{
								if (result_ids.find(source) != result_ids.end())
									sourceNode = regulatory.createNode(source);
							}

							if (targetNode != lemon::INVALID && sourceNode != lemon::INVALID)
								regulatory.createEdge(sourceNode, targetNode, it->first);
						}
						++c;
					}
				}
			}
		}
		return c;
	}

	template <typename N> int _addControlOfConversions(N & regulatory, const std::set<std::string> & physical_entities)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLMappingEngine::_addControlOfConversions: Failed to connect mysql with QT";
				return 0;
			}
		}

		// protein regulations are stored using Control and Conversions

		std::map<UnipaxId, UnipaxId> conversion_entity_map;
		std::map<UnipaxId, UnipaxId> control_conversion_map;
		std::map<UnipaxId, std::set<UnipaxId> > control_entity_map;

		UnipaxId conversion_base = DBManager::getBase("Conversion");

		UnipaxId control_base = DBManager::getBase("Control");

		// collect biochemical reactions and controls

		for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
		{
			if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId entity_base = DBManager::getBase(*it);

				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(conversion_base).arg(((conversion_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						conversion_entity_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(control_base).arg(((control_base >> 24) + 1) << 24).arg(conversion_base).arg(((conversion_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						control_conversion_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(control_base).arg(((control_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						control_entity_map[source].insert(target);

					}
					query.finish();
				}
			}
		}

		// alter network

		int c = 0;

		for (std::map<UnipaxId, UnipaxId>::const_iterator it = control_conversion_map.begin(); it != control_conversion_map.end(); it++)
		{
			if (conversion_entity_map.find(it->second) != conversion_entity_map.end())
			{
				UnipaxId target = conversion_entity_map[it->second];

				if (control_entity_map.find(it->first) != control_entity_map.end())
				{
					std::set<UnipaxId> & sources = control_entity_map[it->first];

					typename N::Node targetNode;

					if (!sources.empty())
					{
						if (regulatory.hasNode(target))
							targetNode = regulatory.getNode(target);
						else
							targetNode = regulatory.createNode(target);

						for (std::set<UnipaxId>::const_iterator sit = sources.begin(); sit != sources.end(); sit++)
						{
							UnipaxId source = *sit;

							typename N::Node sourceNode;

							if (regulatory.hasNode(source))
								sourceNode = regulatory.getNode(source);
							else
								sourceNode = regulatory.createNode(source);


							regulatory.createEdge(sourceNode, targetNode, it->first);
						}

						++c;
					}
				}
			}

		}

		return c;

	}

	template <typename N> int _addBiochemicalReactions(N & metabolic, const std::set<std::string> & physical_entities)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::addBiochemicalReactions: Failed to connect mysql with QT";
				return 0;
			}
		}

		std::multimap<UnipaxId, UnipaxId> biochemicalreaction_leftEntity_map;
		std::multimap<UnipaxId, UnipaxId> biochemicalreaction_rightEntity_map;

		UnipaxId biochemical_reaction_base = DBManager::getBase("BiochemicalReaction");

		// collect biochemical reactions and left- and rightEntities

		for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
		{
			if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId entity_base = DBManager::getBase(*it);

				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4 AND relation = \"leftEntity\"").arg(biochemical_reaction_base).arg(((biochemical_reaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						biochemicalreaction_leftEntity_map.insert(std::pair<UnipaxId, UnipaxId>(source, target));

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4 AND relation = \"rightEntity\"").arg(biochemical_reaction_base).arg(((biochemical_reaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						biochemicalreaction_rightEntity_map.insert(std::pair<UnipaxId, UnipaxId>(source, target));

					}
					query.finish();
				}
			}
		}

		std::cout << biochemicalreaction_leftEntity_map.size() << " " << biochemicalreaction_rightEntity_map.size() << std::endl;

		// alter network

		int c = 0;

		for (std::multimap<UnipaxId, UnipaxId>::const_iterator it = biochemicalreaction_leftEntity_map.begin(); it != biochemicalreaction_leftEntity_map.end(); it++)
		{
			// for leftEntities reaction is target
			UnipaxId target = it->first;

			typename N::Node targetNode;

			if (metabolic.hasNode(target))
				targetNode = metabolic.getNode(target);
			else
				targetNode = metabolic.createNode(target);

			// for leftEntities entities is source
			UnipaxId source = it->second;

			typename N::Node sourceNode;

			if (metabolic.hasNode(source))
				sourceNode = metabolic.getNode(source);
			else
				sourceNode = metabolic.createNode(source);

			metabolic.createArc(sourceNode, targetNode, "leftEntity");
			++c;

		}
		for (std::multimap<UnipaxId, UnipaxId>::const_iterator it = biochemicalreaction_rightEntity_map.begin(); it != biochemicalreaction_rightEntity_map.end(); it++)
		{
			// for rightEntities entity is target
			UnipaxId target = it->second;

			typename N::Node targetNode;

			if (metabolic.hasNode(target))
				targetNode = metabolic.getNode(target);
			else
				targetNode = metabolic.createNode(target);

			// for rightEntities reaction is source
			UnipaxId source = it->first;

			typename N::Node sourceNode;

			if (metabolic.hasNode(source))
				sourceNode = metabolic.getNode(source);
			else
				sourceNode = metabolic.createNode(source);

			metabolic.createArc(sourceNode, targetNode, "rightEntity");

			++c;

		}

		return c;

	}

	template <typename N> int _addBiochemicalReactions(N & metabolic, const std::set<std::string> & physical_entities, const ResultObject result_obj)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::addBiochemicalReactions: Failed to connect mysql with QT";
				return 0;
			}
		}

		std::multimap<UnipaxId, UnipaxId> biochemicalreaction_leftEntity_map;
		std::multimap<UnipaxId, UnipaxId> biochemicalreaction_rightEntity_map;

		UnipaxId biochemical_reaction_base = DBManager::getBase("BiochemicalReaction");

		// collect biochemical reactions and left- and rightEntities

		for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
		{
			if (UniPAX::Kernel::isType(*it))
			{
				UnipaxId entity_base = DBManager::getBase(*it);

				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4 AND relation = \"leftEntity\"").arg(biochemical_reaction_base).arg(((biochemical_reaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						biochemicalreaction_leftEntity_map.insert(std::pair<UnipaxId, UnipaxId>(source, target));

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4 AND relation = \"rightEntity\"").arg(biochemical_reaction_base).arg(((biochemical_reaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						biochemicalreaction_rightEntity_map.insert(std::pair<UnipaxId, UnipaxId>(source, target));

					}
					query.finish();
				}
			}
		}

		std::cout << biochemicalreaction_leftEntity_map.size() << " " << biochemicalreaction_rightEntity_map.size() << std::endl;

		// alter network

		int c = 0;
		std::set<UnipaxId> result_ids = result_obj.getObjectIds();
		for (std::multimap<UnipaxId, UnipaxId>::const_iterator it = biochemicalreaction_leftEntity_map.begin(); it != biochemicalreaction_leftEntity_map.end(); it++)
		{
			// for leftEntities reaction is target of the edge
			UnipaxId target = it->first;

			typename N::Node targetNode(lemon::INVALID);

			if (metabolic.hasNode(target))
				targetNode = metabolic.getNode(target);
			else
			{
				if (result_ids.find(target) != result_ids.end())
					targetNode = metabolic.createNode(target);
			}

			// for leftEntities entity is source of the edge
			UnipaxId source = it->second;

			typename N::Node sourceNode(lemon::INVALID);

			if (metabolic.hasNode(source))
				sourceNode = metabolic.getNode(source);
			else
			{
				if (result_ids.find(source) != result_ids.end())
					sourceNode = metabolic.createNode(source);
			}
			if ((targetNode != lemon::INVALID) && (sourceNode != lemon::INVALID))
				metabolic.createArc(sourceNode, targetNode, "leftEntity");

			++c;

		}
		for (std::multimap<UnipaxId, UnipaxId>::const_iterator it = biochemicalreaction_rightEntity_map.begin(); it != biochemicalreaction_rightEntity_map.end(); it++)
		{
			// for rightEntities entity is target of edge
			UnipaxId target = it->second;

			typename N::Node targetNode(lemon::INVALID);

			if (metabolic.hasNode(target))
				targetNode = metabolic.getNode(target);
			else
			{
				if (result_ids.find(target) != result_ids.end())
					targetNode = metabolic.createNode(target);
			}

			// for rightEntities reaction is source of edge
			UnipaxId source = it->first;

			typename N::Node sourceNode(lemon::INVALID);

			if (metabolic.hasNode(source))
				sourceNode = metabolic.getNode(source);
			else
			{
				if (result_ids.find(source) != result_ids.end())
					sourceNode = metabolic.createNode(source);
			}
			if ((targetNode != lemon::INVALID) && (sourceNode != lemon::INVALID))
				metabolic.createArc(sourceNode, targetNode, "rightEntity");

			++c;

		}

		return c;

	}


	template <typename N> int _addComplexAssemblies(N & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj, bool search_in_biochemicalreactions = false)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::alterByComplexAssemblies: Failed to connect mysql with QT";
				return 0;
			}
		}

		std::map<UnipaxId, std::set<UnipaxId> > complexassembly_left_map;
		std::map<UnipaxId, std::set<UnipaxId> > complexassembly_right_map;

		std::set<UnipaxId> complexassemblies;

		{
			UnipaxId complexassembly_base = DBManager::getBase("ComplexAssembly");

			UnipaxId complex_base = DBManager::getBase("Complex");

			{
				QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(complexassembly_base).arg(((complexassembly_base >> 24) + 1) << 24).arg(complex_base).arg(((complex_base >> 24) + 1) << 24));

				while (query.next())
				{
					UnipaxId source = query.value(0).toULongLong();
					UnipaxId target = query.value(1).toULongLong();
					QString relation = query.value(2).toString();

					if (relation == "leftEntity")
					{
						complexassembly_left_map[source].insert(target);
						complexassemblies.insert(source);
					}
					else if (relation == "rightEntity")
					{
						complexassembly_right_map[source].insert(target);
						complexassemblies.insert(source);
					}
				}
				query.finish();
			}

			for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
			{
				if (UniPAX::Kernel::isType(*it) && *it != "Complex")
				{
					UnipaxId entity_base = DBManager::getBase(*it);

					{
						QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(complexassembly_base).arg(((complexassembly_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

						while (query.next())
						{
							UnipaxId source = query.value(0).toULongLong();
							UnipaxId target = query.value(1).toULongLong();
							QString relation = query.value(2).toString();

							if (relation == "leftEntity")
							{
								complexassembly_left_map[source].insert(target);
								complexassemblies.insert(source);
							}
							else if (relation == "rightEntity")
							{
								complexassembly_right_map[source].insert(target);
								complexassemblies.insert(source);
							}
						}
						query.finish();
					}
				}
			}
		}

		if (search_in_biochemicalreactions)
		{
			UnipaxId biochemicalreaction_base = DBManager::getBase("BiochemicalReaction");

			UnipaxId complex_base = DBManager::getBase("Complex");


			// load only that biochemical reactions, which contain complexes

			std::set<UnipaxId> biochemicalreactions_containing_complexes;

			{
				QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(biochemicalreaction_base).arg(((biochemicalreaction_base >> 24) + 1) << 24).arg(complex_base).arg(((complex_base >> 24) + 1) << 24));

				while (query.next())
				{
					UnipaxId source = query.value(0).toULongLong();
					UnipaxId target = query.value(1).toULongLong();

					QString relation = query.value(2).toString();

					if (relation == "leftEntity")
					{
						complexassembly_left_map[source].insert(target);
						complexassemblies.insert(source);
						biochemicalreactions_containing_complexes.insert(source);
					}
					else if (relation == "rightEntity")
					{
						complexassembly_right_map[source].insert(target);
						complexassemblies.insert(source);
						biochemicalreactions_containing_complexes.insert(source);
					}
				}

				query.finish();
			}

			for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
			{
				if (UniPAX::Kernel::isType(*it) && *it != "Complex")
				{
					UnipaxId entity_base = DBManager::getBase(*it);

					{
						QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(biochemicalreaction_base).arg(((biochemicalreaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

						std::set<UnipaxId> sources, targets;

						while (query.next())
						{
							UnipaxId source = query.value(0).toULongLong();

							if (biochemicalreactions_containing_complexes.find(source) != biochemicalreactions_containing_complexes.end())
							{
								UnipaxId target = query.value(1).toULongLong();

								QString relation = query.value(2).toString();

								if (relation == "leftEntity")
								{
									complexassembly_left_map[source].insert(target);
									complexassemblies.insert(source);
								}
								else if (relation == "rightEntity")
								{
									complexassembly_right_map[source].insert(target);
									complexassemblies.insert(source);
								}
							}
						}
						query.finish();
					}
				}
			}
		}

		// alter network
		std::set<UnipaxId> result_ids = result_obj.getObjectIds();
		int c = 0;

		for (std::set<UnipaxId>::const_iterator it = complexassemblies.begin(); it != complexassemblies.end(); ++it)
		{
			UnipaxId complexassembly = *it;

			if (complexassembly_right_map.find(complexassembly) != complexassembly_right_map.end())
			{
				std::set<UnipaxId> & targets = complexassembly_right_map[complexassembly];

				if (complexassembly_left_map.find(complexassembly) != complexassembly_left_map.end())
				{
					std::set<UnipaxId> & sources = complexassembly_left_map[complexassembly];

					if (!sources.empty() && !targets.empty())
					{

						for (std::set<UnipaxId>::const_iterator tit = targets.begin(); tit != targets.end(); ++tit)
						{
							typename N::Node targetNode(lemon::INVALID);

							UnipaxId target = *tit;

							if (regulatory.hasNode(target))
								targetNode = regulatory.getNode(target);
							else
							{
								if (result_ids.find(target) != result_ids.end())
									targetNode = regulatory.createNode(target);
							}

							for (std::set<UnipaxId>::const_iterator sit = sources.begin(); sit != sources.end(); ++sit)
							{
								UnipaxId source = *sit;

								typename N::Node sourceNode(lemon::INVALID);

								if (regulatory.hasNode(source))
									sourceNode = regulatory.getNode(source);
								else
								{
									if (result_ids.find(source) != result_ids.end())
										sourceNode = regulatory.createNode(source);
								}

								if (targetNode != lemon::INVALID && sourceNode != lemon::INVALID && result_ids.find(complexassembly) != result_ids.end())
									regulatory.createEdge(sourceNode, targetNode, complexassembly);
							}
						}
						++c;
					}
				}
			}
		}
		return c;
	}

	template <typename N> int _addComplexAssemblies(N & regulatory, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions = false)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::alterByComplexAssemblies: Failed to connect mysql with QT";
				return 0;
			}
		}

		std::map<UnipaxId, std::set<UnipaxId> > complexassembly_left_map;
		std::map<UnipaxId, std::set<UnipaxId> > complexassembly_right_map;

		std::set<UnipaxId> complexassemblies;

		{
			UnipaxId complexassembly_base = DBManager::getBase("ComplexAssembly");

			UnipaxId complex_base = DBManager::getBase("Complex");

			{
				QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(complexassembly_base).arg(((complexassembly_base >> 24) + 1) << 24).arg(complex_base).arg(((complex_base >> 24) + 1) << 24));

				while (query.next())
				{
					UnipaxId source = query.value(0).toULongLong();
					UnipaxId target = query.value(1).toULongLong();
					QString relation = query.value(2).toString();

					if (relation == "leftEntity")
					{
						complexassembly_left_map[source].insert(target);
						complexassemblies.insert(source);
					}
					else if (relation == "rightEntity")
					{
						complexassembly_right_map[source].insert(target);
						complexassemblies.insert(source);
					}
				}
				query.finish();
			}

			for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
			{
				if (UniPAX::Kernel::isType(*it) && *it != "Complex")
				{
					UnipaxId entity_base = DBManager::getBase(*it);

					{
						QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(complexassembly_base).arg(((complexassembly_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

						while (query.next())
						{
							UnipaxId source = query.value(0).toULongLong();
							UnipaxId target = query.value(1).toULongLong();
							QString relation = query.value(2).toString();

							if (relation == "leftEntity")
							{
								complexassembly_left_map[source].insert(target);
								complexassemblies.insert(source);
							}
							else if (relation == "rightEntity")
							{
								complexassembly_right_map[source].insert(target);
								complexassemblies.insert(source);
							}
						}
						query.finish();
					}
				}
			}
		}

		if (search_in_biochemicalreactions)
		{
			UnipaxId biochemicalreaction_base = DBManager::getBase("BiochemicalReaction");

			UnipaxId complex_base = DBManager::getBase("Complex");


			// load only that biochemical reactions, which contain complexes

			std::set<UnipaxId> biochemicalreactions_containing_complexes;

			{
				QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(biochemicalreaction_base).arg(((biochemicalreaction_base >> 24) + 1) << 24).arg(complex_base).arg(((complex_base >> 24) + 1) << 24));

				while (query.next())
				{
					UnipaxId source = query.value(0).toULongLong();
					UnipaxId target = query.value(1).toULongLong();

					QString relation = query.value(2).toString();

					if (relation == "leftEntity")
					{
						complexassembly_left_map[source].insert(target);
						complexassemblies.insert(source);
						biochemicalreactions_containing_complexes.insert(source);
					}
					else if (relation == "rightEntity")
					{
						complexassembly_right_map[source].insert(target);
						complexassemblies.insert(source);
						biochemicalreactions_containing_complexes.insert(source);
					}
				}

				query.finish();
			}

			for (std::set<std::string>::const_iterator it = physical_entities.begin(); it != physical_entities.end(); it++)
			{
				if (UniPAX::Kernel::isType(*it) && *it != "Complex")
				{
					UnipaxId entity_base = DBManager::getBase(*it);

					{
						QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4").arg(biochemicalreaction_base).arg(((biochemicalreaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

						std::set<UnipaxId> sources, targets;

						while (query.next())
						{
							UnipaxId source = query.value(0).toULongLong();

							if (biochemicalreactions_containing_complexes.find(source) != biochemicalreactions_containing_complexes.end())
							{
								UnipaxId target = query.value(1).toULongLong();

								QString relation = query.value(2).toString();

								if (relation == "leftEntity")
								{
									complexassembly_left_map[source].insert(target);
									complexassemblies.insert(source);
								}
								else if (relation == "rightEntity")
								{
									complexassembly_right_map[source].insert(target);
									complexassemblies.insert(source);
								}
							}
						}
						query.finish();
					}
				}
			}
		}

		// alter network

		int c = 0;

		for (std::set<UnipaxId>::const_iterator it = complexassemblies.begin(); it != complexassemblies.end(); ++it)
		{
			UnipaxId complexassembly = *it;

			if (complexassembly_right_map.find(complexassembly) != complexassembly_right_map.end())
			{
				std::set<UnipaxId> & targets = complexassembly_right_map[complexassembly];

				if (complexassembly_left_map.find(complexassembly) != complexassembly_left_map.end())
				{
					std::set<UnipaxId> & sources = complexassembly_left_map[complexassembly];

					if (!sources.empty() && !targets.empty())
					{

						for (std::set<UnipaxId>::const_iterator tit = targets.begin(); tit != targets.end(); ++tit)
						{
							typename N::Node targetNode;

							UnipaxId target = *tit;

							if (regulatory.hasNode(target))
								targetNode = regulatory.getNode(target);
							else
								targetNode = regulatory.createNode(target);

							for (std::set<UnipaxId>::const_iterator sit = sources.begin(); sit != sources.end(); ++sit)
							{
								UnipaxId source = *sit;

								typename N::Node sourceNode;

								if (regulatory.hasNode(source))
									sourceNode = regulatory.getNode(source);
								else
									sourceNode = regulatory.createNode(source);


								regulatory.createEdge(sourceNode, targetNode, complexassembly);
							}
						}

						++c;
					}
				}
			}

		}

		return c;

	}

	template<class T> bool _filterByOrganism(T & network, std::set<UnipaxId> & organismIds)
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::_filterByOrganism: Failed to connect mysql with QT";
				return false;
			}
		}

		QStringList nodeIdList;
		for (typename std::map<UnipaxId, typename T::Graph::Node>::const_iterator it = network.id_node_map.begin(); it != network.id_node_map.end(); ++it)
		{
			nodeIdList.append(QVariant((qulonglong)it->first).toString());
		}

		QStringList organismIdList;
		organismIdList.append("-1");
		for (std::set<UnipaxId>::const_iterator it = organismIds.begin(); it != organismIds.end(); ++it)
		{
			organismIdList.append(QVariant((qulonglong)*it).toString());
		}

		QSqlQuery query = db->exec(QString("SELECT entityId FROM C_ENTITY_ORGANISM WHERE organismId IN (%1) AND entityId IN (%2)").arg(organismIdList.join(",")).arg(nodeIdList.join(",")));

		std::set<UnipaxId> organism_entities;
		while (query.next())
		{
			organism_entities.insert(query.value(0).toULongLong());
		}

		network.retainNodes(organism_entities);
		network.eraseDisconnectedNodes();

		return true;
	}

	template<class T> bool _filterByPathway(T & network, std::set<UnipaxId> & pathwayIds)
	{


		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::_filterByPathway: Failed to connect mysql with QT";
				return false;
			}
		}

		QStringList nodeIdList;
		std::cout << "NodeList is:" << std::endl;
		for (typename std::map<UnipaxId, typename T::Graph::Node>::const_iterator it = network.id_node_map.begin(); it != network.id_node_map.end(); ++it)
		{
			nodeIdList.append(QVariant((qulonglong)it->first).toString());
			std::cout << QVariant((qulonglong)it->first).toString().toStdString() << ", "; 
		}

		std::cout << std::endl;

		QStringList pathwayIdList;
		for (std::set<UnipaxId>::const_iterator it = pathwayIds.begin(); it != pathwayIds.end(); ++it)
		{
			pathwayIdList.append(QVariant((qulonglong)*it).toString());
		}

		QSqlQuery query = db->exec(QString("SELECT entityId FROM C_ENTITY_PATHWAY WHERE pathwayId IN (%1) AND entityId IN (%2)").arg(pathwayIdList.join(",")).arg(nodeIdList.join(",")));

		std::set<UnipaxId> pathway_entities;
		std::set<UnipaxId> pathway_arcs;
		while (query.next())
		{
			pathway_entities.insert(query.value(0).toULongLong());
			pathway_arcs.insert(query.value(1).toULongLong());
		}

		network.retainNodes(pathway_entities);
		network.retainArcs(pathway_arcs);
		network.eraseDisconnectedNodes();
	}

	template<class T> bool _mapXrefData(T & network, typename T::Graph::template NodeMap<std::string> & nodeMap, std::string external_db)
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::mapXrefData: Failed to connect mysql with QT";
				return false;
			}
		}

		QStringList l;
		for (typename std::map<UnipaxId, typename T::Graph::Node>::const_iterator it = network.id_node_map.begin(); it != network.id_node_map.end(); ++it)
		{
			l.append(QVariant((qulonglong)it->first).toString());
		}

		QSqlQuery query = db->exec(QString("SELECT entityId, id FROM C_ENTITY_DBKEY WHERE db = '%1' AND entityId IN (%2)").arg(QString::fromStdString(external_db)).arg(l.join(", ")));

		while (query.next())
		{
			UnipaxId entityId = query.value(0).toULongLong();
			std::string id = query.value(1).toString().toStdString();

			if (network.hasNode(entityId))
				nodeMap[network.getNode(entityId)] = id;

		}
		query.finish();

		return true;
	}

	template<class T> bool _mapXrefData(T & network, typename T::Graph::template ArcMap<std::string> & arcMap, std::string external_db)
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::mapXrefData: Failed to connect mysql with QT";
				return false;
			}
		}

		QSqlQuery query = db->exec(QString("SELECT entityId, id FROM C_ENTITY_DBKEY WHERE db = '%1'").arg(QString::fromStdString(external_db)));

		while (query.next())
		{
			UnipaxId entityId = query.value(0).toULongLong();
			std::string id = query.value(1).toString().toStdString();

			if (network.hasEdge(entityId))
			{
				std::vector<typename T::Edge> v = network.getEdges(entityId);


				for (typename std::vector<typename T::Edge>::iterator it = v.begin(); it != v.end(); ++it)
					arcMap[*it] = id;
			}
		}
		query.finish();

		return true;
	}

	template<class T> bool _mapXrefData(T & network, typename T::Graph::template EdgeMap<std::string> & edgeMap, std::string external_db)
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::mapXrefData: Failed to connect mysql with QT";
				return false;
			}
		}

		QSqlQuery query = db->exec(QString("SELECT entityId, id FROM C_ENTITY_DBKEY WHERE db = '%1'").arg(QString::fromStdString(external_db)));

		while (query.next())
		{
			UnipaxId entityId = query.value(0).toULongLong();
			std::string id = query.value(1).toString().toStdString();

			if (network.hasEdge(entityId))
			{
				std::vector<typename T::Edge> v = network.getEdges(entityId);


				for (typename std::vector<typename T::Edge>::iterator it = v.begin(); it != v.end(); ++it)
					edgeMap[*it] = id;
			}
		}
		query.finish();

		return true;
	}


	template<class T> bool _mapNames(T & network, typename T::Graph::template NodeMap<std::string> & nodeMap, std::string type = "")
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::_mapNames: Failed to connect mysql with QT";
				return false;
			}
		}

		if (type == "standard")
		{
			QSqlQuery query = db->exec("SELECT unipaxId, standardName FROM Entity");

			while (query.next())
			{
				UnipaxId unipaxId = query.value(0).toULongLong();
				std::string value = query.value(1).toString().toStdString();

				if (network.hasNode(unipaxId))
					nodeMap[network.getNode(unipaxId)] = value;

			}
			query.finish();

			query = db->exec("SELECT unipaxId, standardName FROM EntityReference");

			while (query.next())
			{
				UnipaxId unipaxId = query.value(0).toULongLong();
				std::string value = query.value(1).toString().toStdString();

				if (network.hasNode(unipaxId))
					nodeMap[network.getNode(unipaxId)] = value;

			}
			query.finish();
		}
		else if (type == "display")
		{
			QSqlQuery query = db->exec("SELECT unipaxId, displayName FROM Entity");

			while (query.next())
			{
				UnipaxId unipaxId = query.value(0).toULongLong();
				std::string value = query.value(1).toString().toStdString();

				if (network.hasNode(unipaxId))
					nodeMap[network.getNode(unipaxId)] = value;

			}
			query.finish();

			query = db->exec("SELECT unipaxId, displayName FROM EntityReference");

			while (query.next())
			{
				UnipaxId unipaxId = query.value(0).toULongLong();
				std::string value = query.value(1).toString().toStdString();

				if (network.hasNode(unipaxId))
					nodeMap[network.getNode(unipaxId)] = value;

			}
			query.finish();
		}
		else
		{
			QSqlQuery query = db->exec("SELECT object_id, GROUP_CONCAT(value SEPARATOR ', ') FROM Entity_name GROUP BY object_id");

			while (query.next())
			{
				UnipaxId unipaxId = query.value(0).toULongLong();
				std::string value = query.value(1).toString().toStdString();

				if (network.hasNode(unipaxId))
					nodeMap[network.getNode(unipaxId)] = value;

			}
			query.finish();

			query = db->exec("SELECT object_id, GROUP_CONCAT(value SEPARATOR ', ') FROM EntityReference_name GROUP BY object_id");

			while (query.next())
			{
				UnipaxId unipaxId = query.value(0).toULongLong();
				std::string value = query.value(1).toString().toStdString();

				if (network.hasNode(unipaxId))
					nodeMap[network.getNode(unipaxId)] = value;

			}
			query.finish();
		}
		return true;
	}

	template<class T> bool _mapFeatures(T & network, typename T::Graph::template NodeMap<std::string> & nodeMap, std::string type)
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "MySQLCache::_mapModificationFeatures: Failed to connect mysql with QT";
				return false;
			}
		}

		QSqlQuery query = db->exec(QString("SELECT unipaxId, value FROM C_ENTITY_FEATURES WHERE type = '%1'").arg(QString::fromStdString(type)));

		while (query.next())
		{
			UnipaxId unipaxId = query.value(0).toULongLong();
			std::string value = query.value(1).toString().toStdString();

			if (network.hasNode(unipaxId))
				nodeMap[network.getNode(unipaxId)] = value;

		}
		query.finish();

		return true;
	}

	template<class T> bool _mapSeriesData(T & network, std::vector<std::pair<std::string, typename TNodeMapPtr<T>::type> > & nodeMaps, UnipaxId result_id)
	{
		if (!db_manager->isValid(result_id))
		{
			std::cerr << "MySQLMappingEngine::_mapSeriesData: Invalid ResultObject ID: " << result_id << std::endl;
			return false;
		}
		UniPAX::ResultObjectPtr result = boost::dynamic_pointer_cast<UniPAX::ResultObject>(db_manager->getObjectByID(result_id));
		if (result->getDataSeries() == 0)
		{
			std::cerr << "MySQLMappingEngine::_mapSeriesData: ResultObject contains no data." << std::endl;
			return false;
		}
		UniPAX::SeriesPtr data_series = result->getDataSeries();
		UniPAX::IdMappingPtr id_mapping;
		// find mapping to UniPAX IDs
		for (std::vector<IdMappingPtr>::iterator it = data_series->getIdMappingList().begin(); it != data_series->getIdMappingList().end(); ++it)
		{
			if ((*it)->getDbName().compare("UniPAX") == 0)
			{
				id_mapping = *it;
				UniPAX::SamplePtr sample = data_series->getSampleList()[id_mapping->getSampleIndex()];
				// now we have the right sample and mapping
				// for all double columns in matrix of sample:

				std::string type = sample->getSampleData()->getValueType();

				if (type == "double")
				{
					DoubleSampleDataPtr doubleData = boost::dynamic_pointer_cast<DoubleSampleData>(sample->getSampleData());

					// construct a new NodeMap:
					typename TNodeMapPtr<T>::type nodeMap(new typename TNodeMap<T>::type(network.graph));
					// for all IDs in mapping look if ID is part of network:
					for (int row=0; row != id_mapping->getIds().size(); ++row)
					{
						// multiple ids! (multimap)
						std::pair<std::multimap<int, std::string>::iterator,std::multimap<int, std::string>::iterator> borders = id_mapping->getIds().equal_range(row);
						for (std::multimap<int, std::string>::iterator id_it = borders.first; id_it != borders.second; ++id_it)
						{
							UnipaxId uid = boost::lexical_cast<UnipaxId>(id_it->second);
							if (network.hasNode(uid))
							{
								// insert expression value into map:
								(*nodeMap)[network.getNode(uid)] = boost::lexical_cast<std::string>(doubleData->values[row]);
							}
						}
					}

					nodeMaps.push_back(std::pair<std::string, typename TNodeMapPtr<T>::type>(sample->getName(), nodeMap));
				}

				//
				//
				//				for (int col=0; col != sample->getSampleData()->.second; ++col)
				//				{
				//					// construct a new NodeMap:
				//					typename TNodeMapPtr<T>::type nodeMap(new typename TNodeMap<T>::type(network.graph));
				//					// for all IDs in mapping look if ID is part of network:
				//					for (int row=0; row != id_mapping->getIds().size(); ++row)
				//					{
				//						// multiple ids! (multimap)
				//						std::pair<std::multimap<int, std::string>::iterator,std::multimap<int, std::string>::iterator> borders = id_mapping->getIds().equal_range(row);
				//						for (std::multimap<int, std::string>::iterator id_it = borders.first; id_it != borders.second; ++id_it)
				//						{
				//							UnipaxId uid = boost::lexical_cast<UnipaxId>(id_it->second);
				//							if (network.hasNode(uid))
				//							{
				//								// insert expression value into map:
				//								(*nodeMap)[network.getNode(uid)] = boost::lexical_cast<std::string>(sample->getDataMatrix()->getDouble(row, col));
				//							}
				//						}
				//					}
				//					nodeMaps.push_back(std::pair<std::string, typename TNodeMapPtr<T>::type>(sample->getDataMatrix()->getColumnName(col), nodeMap));
				//				}
			}
		}
		if (id_mapping == 0)
		{
			std::cerr << "MySQLMappingEngine::_mapSeriesData: No mapping to UniPAX IDs available." << std::endl;
			return false;
		}

		return true;
	}
};

typedef UnipaxPtr<MySQLMappingEngine>::type MySQLMappingEnginePtr;

}

}

}


#endif /* MYSQLCACHE_H_ */

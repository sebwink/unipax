#ifndef ORACLECACHE_H_
#define ORACLECACHE_H_

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/GRAPH/MAPPING/MappingEngine.h>
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>

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

namespace oracle
{

class UNIPAX_EXPORT OracleMappingEngine : public UniPAX::GRAPH::MappingEngine
{

public:

	OracleMappingEngine(boost::shared_ptr<UniPAX::DBManager> _db_manager);

	~OracleMappingEngine()
	{

	}

	bool needsRebuildDatabaseCache();

	void rebuildDatabaseCache();

	boost::shared_ptr<RelationsGraph> createRelationsGraph();

	boost::shared_ptr<ProteinProteinInteractionNetwork> createProteinProteinInteractionNetwork(const std::set<std::string> & physical_entities);

	boost::shared_ptr<RegulatoryNetwork> createRegulatoryNetwork(const std::set<std::string> & physical_entities);

	boost::shared_ptr<MetabolicNetwork> createMetabolicNetwork(const std::set<std::string> & physical_entities);

	int addInteractions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities);

	int addTemplateRegulations(RegulatoryNetwork & network, const std::set<std::string> & physical_entities);

	int addControlOfBiochemicalReactions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities);

	int addControlOfConversions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities);

	int addComplexAssemblies(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions = false);

	int addInteractions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities);

	int addTemplateRegulations(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities);

	int addControlOfBiochemicalReactions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities);

	int addComplexAssemblies(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions = false);

	int addBiochemicalReactions(MetabolicNetwork & network, const std::set<std::string> & physical_entities);




	bool mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db);

	bool mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & arcMap, std::string external_db);

	bool mapNames(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "");

	bool mapFeatures(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type = "");

	bool mapRegulationTypes(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & regulation_type);

	bool filterByOrganisms(RegulatoryNetwork & network, std::set<UnipaxId> & organismIds);

	bool filterByPathway(RegulatoryNetwork & network, UnipaxId pathwayId);

	bool filterByPathways(RegulatoryNetwork & network, std::set<UnipaxId> & pathwayIds);



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

	bool filterByOrganisms(MetabolicNetwork & network, std::set<UnipaxId> & organismIds);

	bool filterByPathways(MetabolicNetwork & network, std::set<UnipaxId> & pathwayIds);



	bool getEntityIdsByOrganism(std::set<UnipaxId> & organism_entites, UnipaxId organismId);

	bool getEntityIdsByPathway(std::set<UnipaxId> & pathway_entites, UnipaxId pathwayId);



	std::string getName(UnipaxId unipaxId);
	std::string getPathwayName(UnipaxId unipaxId);
	std::string getPathwayDescription(UnipaxId unipaxId);

private :
	template <typename N> int _addInteractions(N & network, const std::set<std::string> & physical_entities)
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::alterByInteractions: Failed to connect oracle with QT";
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

	template <typename N> int _addTemplateRegulations(N & regulatory, const std::set<std::string> & physical_entities)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::alterByTemplateRegulations: Failed to connect oracle with QT";
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

	template <typename N> int _addControlOfBiochemicalReactions(N & regulatory, const std::set<std::string> & physical_entities)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::alterByControlOfBiochemicalReactions: Failed to connect oracle with QT";
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

	template <typename N> int _addControlOfConversions(N & regulatory, const std::set<std::string> & physical_entities)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleMappingEngine::_addControlOfConversions: Failed to connect oracle with QT";
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
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::addBiochemicalReactions: Failed to connect oracle with QT";
				return 0;
			}
		}

		std::map<UnipaxId, UnipaxId> biochemicalreaction_leftEntity_map;
		std::map<UnipaxId, UnipaxId> biochemicalreaction_rightEntity_map;
		
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

						biochemicalreaction_leftEntity_map[source] = target;

					}
					query.finish();
				}
				{
					QSqlQuery query = db->exec(QString("SELECT source, target, relation FROM C_RELATIONS WHERE source >= %1 AND source < %2 AND target >= %3 AND target < %4 AND relation = \"rightEntity\"").arg(biochemical_reaction_base).arg(((biochemical_reaction_base >> 24) + 1) << 24).arg(entity_base).arg(((entity_base >> 24) + 1) << 24));

					while (query.next())
					{
						UnipaxId source = query.value(0).toULongLong();
						UnipaxId target = query.value(1).toULongLong();

						biochemicalreaction_rightEntity_map[source] = target;

					}
					query.finish();
				}
			}
		}

		std::cout << biochemicalreaction_leftEntity_map.size() << " " << biochemicalreaction_rightEntity_map.size() << std::endl;

		// alter network

		int c = 0;

		for (std::map<UnipaxId, UnipaxId>::const_iterator it = biochemicalreaction_leftEntity_map.begin(); it != biochemicalreaction_leftEntity_map.end(); it++)
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
		for (std::map<UnipaxId, UnipaxId>::const_iterator it = biochemicalreaction_rightEntity_map.begin(); it != biochemicalreaction_rightEntity_map.end(); it++)
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


	template <typename N> int _addComplexAssemblies(N & regulatory, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions = false)
	{
		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::alterByComplexAssemblies: Failed to connect oracle with QT";
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

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::_filterByOrganism: Failed to connect oracle with QT";
				return false;
			}
		}

		QStringList nodeIdList;
		for (typename std::map<UnipaxId, typename T::Graph::Node>::const_iterator it = network.id_node_map.begin(); it != network.id_node_map.end(); ++it)
		{
			nodeIdList.append(QVariant(it->first).toString());
		}

		QStringList organismIdList;
		organismIdList.append("-1");
		for (std::set<UnipaxId>::const_iterator it = organismIds.begin(); it != organismIds.end(); ++it)
		{
			organismIdList.append(QVariant(*it).toString());
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

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::_filterByPathway: Failed to connect oracle with QT";
				return false;
			}
		}

		QStringList nodeIdList;
		for (typename std::map<UnipaxId, typename T::Graph::Node>::const_iterator it = network.id_node_map.begin(); it != network.id_node_map.end(); ++it)
		{
			nodeIdList.append(QVariant(it->first).toString());
		}

		QStringList pathwayIdList;
		for (std::set<UnipaxId>::const_iterator it = pathwayIds.begin(); it != pathwayIds.end(); ++it)
		{
			pathwayIdList.append(QVariant(*it).toString());
		}

		QSqlQuery query = db->exec(QString("SELECT entityId, interactionId FROM C_ENTITY_PATHWAY WHERE pathwayId IN (%1) AND entityId IN (%2)").arg(pathwayIdList.join(",")).arg(nodeIdList.join(",")));

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

		return true;
	}


	template<class T> bool _mapXrefData(T & network, typename T::Graph::template NodeMap<std::string> & nodeMap, std::string external_db)
	{

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::mapXrefData: Failed to connect oracle with QT";
				return false;
			}
		}

		QStringList l;
		for (typename std::map<UnipaxId, typename T::Graph::Node>::const_iterator it = network.id_node_map.begin(); it != network.id_node_map.end(); ++it)
		{
			l.append(QVariant(it->first).toString());
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

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::mapXrefData: Failed to connect oracle with QT";
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

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::mapXrefData: Failed to connect oracle with QT";
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

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::_mapNames: Failed to connect oracle with QT";
				return false;
			}
		}

		if (type == "standard")
		{
			QSqlQuery query = db->exec("SELECT unipaxId, value FROM C_NAMES WHERE standard = 1");

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
			QSqlQuery query = db->exec("SELECT unipaxId, value FROM C_NAMES WHERE display = 1");

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
			QSqlQuery query = db->exec("SELECT unipaxId, value FROM C_NAMES");

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

		QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

		if (!db->isOpen())
		{
			if (!db->open())
			{
				std::cerr << "OracleCache::_mapModificationFeatures: Failed to connect oracle with QT";
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

};

}

}

}



#endif /* ORACLECACHE_H_ */

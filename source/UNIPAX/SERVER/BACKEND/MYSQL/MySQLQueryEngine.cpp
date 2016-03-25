#include <UNIPAX/SERVER/BACKEND/MYSQL/MySQLQueryEngine.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>
#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#include <UNIPAX/IMPORT/BridgeDBWrapper.h>
#include <UNIPAX/IMPORT/BridgeDBLinkREST.h>

#include<UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#include<UNIPAX/KERNEL/Kernel.h>
#include<UNIPAX/KERNEL/ClassType.h>

#include <QtXml>
#include <QtSql>

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include<odb/transaction.hxx>
#include<odb/query.hxx>


UniPAX::SERVER::MySQLQueryEngine::MySQLQueryEngine(bool cached) : QueryEngine(), manager(new UniPAX::mysql::MySQLManager(cached))
{
}

UniPAX::SERVER::MySQLQueryEngine::~MySQLQueryEngine()
{

}

QSqlQuery UniPAX::SERVER::MySQLQueryEngine::exec(QSqlDatabase* db, QString sql, QString error)
{
	QSqlQuery q = db->exec(sql);
	QSqlError e = q.lastError();
	if (e.isValid())
	{
		throw std::runtime_error(error.toStdString() + ": " + e.text().toStdString() + " -- " + sql.toStdString());
	}

	return q;
}

void UniPAX::SERVER::MySQLQueryEngine::exec(QSqlQuery& query, QString error)
{
	query.exec();
	QSqlError e = query.lastError();
	if (e.isValid())
	{
		throw std::runtime_error(error.toStdString() + ": " + e.text().toStdString() + " -- " + query.lastQuery().toStdString());
	}
}

void UniPAX::SERVER::MySQLQueryEngine::createResultSetTables()
{
	checkDatabaseConnection();

	std::cout << "Creating result set tables... " << std::flush;

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "MySQLQueryEngine::createResultSetTables: Failed to connect mysql with QT";
	}


	db->exec(QString("DROP TABLE IF EXISTS Q_RESULTSETS"));
	db->exec(QString("CREATE TABLE Q_RESULTSETS (")
			.append("resultSetId BIGINT(20) UNSIGNED AUTO INCREMENT,")
			.append("value BLOB")
			.append(") ENGINE=MyISAM"));

	std::cout << "finished." << std::endl;
}


void UniPAX::SERVER::MySQLQueryEngine::checkIndexes()
{
	checkDatabaseConnection();

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "MySQLQueryEngine::checkIndexes: Failed to connect mysql with QT";
	}

	QSqlQuery q = db->exec(QString("SHOW TABLES LIKE 'Q_NAME_INDEX'"));
	if (!q.next())
		rebuildNameIndex();

	q = db->exec(QString("SHOW TABLES LIKE 'Q_ATTRIBUTE_INDEX'"));
	if (!q.next())
		rebuildAttributeIndex();

	if (!exec(db, "SHOW TABLES LIKE 'Q_PATHWAY_INDEX'", "Unable to check for tables").next() || !exec(db, "SHOW TABLES LIKE 'Q_PATHWAY_SIZE_INDEX'", "Unable to check for tables").next())
		rebuildPathwayIndex();

	q = db->exec(QString("SHOW TABLES LIKE 'Q_ID_MAPPING'"));
	if (!q.next())
		rebuildIdMapping();

}

void UniPAX::SERVER::MySQLQueryEngine::rebuildNameIndex()
{
	std::cout << "Rebuilding name index... " << std::flush;

	checkDatabaseConnection();

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "MySQLQueryEngine::rebuildNameIndex: Failed to connect mysql with QT";
	}

	exec(db, QString("DROP TABLE IF EXISTS Q_NAME_INDEX"), "Unable to drop table Q_NAME_INDEX.");

	exec(db, QString("CREATE TABLE Q_NAME_INDEX (")
			.append("unipaxId BIGINT(20) UNSIGNED,")
			.append("value TEXT")
			.append(") ENGINE=MyISAM"), "Unable to create table Q_NAME_INDEX");

	exec(db, "INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT object_id, value FROM `BioSource_name`", "Unable to fill Q_NAME_INDEX from BioSource");

	exec(db, "INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT object_id, value FROM `EntityReference_name`", "Unable to fill Q_NAME_INDEX from EntityReference");

	exec(db, "INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT object_id, value FROM `Entity_name`", "Unable to fill Q_NAME_INDEX from Entity");

	exec(db, "INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT object_id, value FROM `Provenance_name`", "Unable to fill Q_NAME_INDEX from Provenance");

	exec(db, QString("CREATE FULLTEXT INDEX q_name_value_index ON `Q_NAME_INDEX` (value)"), "Unable to create full text index on Q_NAME_INDEX");

	std::cout << "finished." << std::endl;
}

void UniPAX::SERVER::MySQLQueryEngine::rebuildAttributeIndex()
{
	std::cout << "Rebuilding attribute index... " << std::flush;

	checkDatabaseConnection();

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "MySQLQueryEngine::rebuildAttributeIndex: Failed to connect mysql with QT";
	}

	exec(db, "DROP TABLE IF EXISTS Q_ATTRIBUTE_INDEX", "Unable to drop table Q_ATTRIBUTE_INDEX");
	exec(db, QString("CREATE TABLE Q_ATTRIBUTE_INDEX (")
			.append("unipaxId BIGINT(20) UNSIGNED NOT NULL,")
			.append("type VARCHAR(40) NOT NULL,")
			.append("typeId INT UNSIGNED NOT NULL,")
			.append("standardName TEXT DEFAULT NULL,")
			.append("displayName TEXT DEFAULT NULL,")
			.append("organism BIGINT(20) UNSIGNED DEFAULT NULL,")
			.append("dataSource BIGINT(20) UNSIGNED DEFAULT NULL,")
			.append("entityModification TEXT DEFAULT NULL,")
			.append("PRIMARY KEY(unipaxId)")
			.append(") ENGINE=MyISAM"), "Unable to create table Q_ATTRIBUTE_INDEX");


	std::vector<std::string> sorted_classes = Kernel::sorted_children("UPBase", true);
	for (std::vector<std::string>::iterator it = sorted_classes.begin(); it != sorted_classes.end(); ++it)
	{
		if (Kernel::classType(*it) != ClassType::END_ENUM)
		{
			exec(db, QString("REPLACE INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT unipaxId, '%1', ")
					.append(QString::number(Kernel::classType(*it)))
					.append(", NULL, NULL, NULL, NULL FROM `%2`")
					.arg(QString::fromStdString(*it))
					.arg(QString::fromStdString(*it)), QString("Unable to fill Q_ATTRIBUTE_INDEX from `%1`").arg(QString::fromStdString(*it)));
		}
	}

	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN BioSource ON Q_ATTRIBUTE_INDEX.unipaxID = BioSource.unipaxId SET Q_ATTRIBUTE_INDEX.standardName = BioSource.standardName WHERE Q_ATTRIBUTE_INDEX.unipaxId = BioSource.unipaxId AND BioSource.standardName != ''", "Unable to insert standardName from BioSource into Q_ATTRIBUTE_INDEX");
	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN Entity ON Q_ATTRIBUTE_INDEX.unipaxID = Entity.unipaxId SET Q_ATTRIBUTE_INDEX.standardName = Entity.standardName WHERE Q_ATTRIBUTE_INDEX.unipaxId = Entity.unipaxId AND Entity.standardName != ''", "Unable to insert standardName from Entity into Q_ATTRIBUTE_INDEX");
	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN EntityReference ON Q_ATTRIBUTE_INDEX.unipaxID = EntityReference.unipaxId SET Q_ATTRIBUTE_INDEX.standardName = EntityReference.standardName WHERE Q_ATTRIBUTE_INDEX.unipaxId = EntityReference.unipaxId AND EntityReference.standardName != ''", "Unable to insert standardName from EntityReference into Q_ATTRIBUTE_INDEX");

	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN BioSource ON Q_ATTRIBUTE_INDEX.unipaxID = BioSource.unipaxId SET Q_ATTRIBUTE_INDEX.displayName = BioSource.displayName WHERE Q_ATTRIBUTE_INDEX.unipaxId = BioSource.unipaxId AND BioSource.displayName != ''", "Unable to insert displayName from BioSource into Q_ATTRIBUTE_INDEX");
	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN Entity ON Q_ATTRIBUTE_INDEX.unipaxID = Entity.unipaxId SET Q_ATTRIBUTE_INDEX.displayName = Entity.displayName WHERE Q_ATTRIBUTE_INDEX.unipaxId = Entity.unipaxId AND Entity.displayName != ''", "Unable to insert displayName from Entity into Q_ATTRIBUTE_INDEX");
	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN EntityReference ON Q_ATTRIBUTE_INDEX.unipaxID = EntityReference.unipaxId SET Q_ATTRIBUTE_INDEX.displayName = EntityReference.displayName WHERE Q_ATTRIBUTE_INDEX.unipaxId = EntityReference.unipaxId AND EntityReference.displayName != ''", "Unable to insert standardName from EntityReference into Q_ATTRIBUTE_INDEX");

	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN ProteinReference as ref ON Q_ATTRIBUTE_INDEX.unipaxID = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = ref.unipaxId AND ref.organism != ''", "Unable to insert organism of ProteinReference into Q_ATTRIBUTE_INDEX");
	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN Protein_entityReference as entity ON Q_ATTRIBUTE_INDEX.unipaxID = entity.object_id LEFT JOIN ProteinReference as ref ON entity.value = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = entity.object_id AND ref.organism != ''", "Unable to insert organism of Protein into Q_ATTRIBUTE_INDEX");

	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN RnaReference as ref ON Q_ATTRIBUTE_INDEX.unipaxID = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = ref.unipaxId AND ref.organism != ''", "Unable to insert organism of RnaReference into Q_ATTRIBUTE_INDEX");
	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN Rna_entityReference as entity ON Q_ATTRIBUTE_INDEX.unipaxID = entity.object_id LEFT JOIN RnaReference as ref ON entity.value = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = entity.object_id AND ref.organism != ''", "Unable to insert organism of Rna into Q_ATTRIBUTE_INDEX");

	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN RnaRegionReference as ref ON Q_ATTRIBUTE_INDEX.unipaxID = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = ref.unipaxId AND ref.organism != ''", "Unable to insert organism of RnaRegionReference into Q_ATTRIBUTE_INDEX");
	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN RnaRegion_entityReference as entity ON Q_ATTRIBUTE_INDEX.unipaxID = entity.object_id LEFT JOIN RnaRegionReference as ref ON entity.value = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = entity.object_id AND ref.organism != ''", "Unable to insert organism of RnaRegion into Q_ATTRIBUTE_INDEX");

	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN DnaReference as ref ON Q_ATTRIBUTE_INDEX.unipaxID = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = ref.unipaxId AND ref.organism != ''", "Unable to insert organism of DnaReference into Q_ATTRIBUTE_INDEX");
	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN Dna_entityReference as entity ON Q_ATTRIBUTE_INDEX.unipaxID = entity.object_id LEFT JOIN DnaReference as ref ON entity.value = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = entity.object_id AND ref.organism != ''", "Unable to insert organism of Dna into Q_ATTRIBUTE_INDEX");

	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN DnaRegionReference as ref ON Q_ATTRIBUTE_INDEX.unipaxID = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = ref.unipaxId AND ref.organism != ''", "Unable to insert organism of DnaRegionReference into Q_ATTRIBUTE_INDEX");
	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN DnaRegion_entityReference as entity ON Q_ATTRIBUTE_INDEX.unipaxID = entity.object_id LEFT JOIN DnaRegionReference as ref ON entity.value = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = entity.object_id AND ref.organism != ''", "Unable to insert organism of DnaRegion into Q_ATTRIBUTE_INDEX");

	exec(db, "UPDATE Q_ATTRIBUTE_INDEX LEFT JOIN Pathway as ref ON Q_ATTRIBUTE_INDEX.unipaxID = ref.unipaxId SET Q_ATTRIBUTE_INDEX.organism = ref.organism WHERE Q_ATTRIBUTE_INDEX.unipaxId = ref.unipaxId AND ref.organism != ''", "Unable to insert organism of Pathway into Q_ATTRIBUTE_INDEX");

	exec(db, "UPDATE Q_ATTRIBUTE_INDEX attr LEFT JOIN (SELECT object_id as id, GROUP_CONCAT( term ) as t FROM PhysicalEntity_feature pf LEFT OUTER JOIN ModificationFeature mf ON ( pf.value = mf.unipaxId ) LEFT OUTER JOIN ControlledVocabulary voc ON ( mf.modificationType = voc.unipaxId ) WHERE term IS NOT NULL GROUP BY object_id) AS join1 ON attr.unipaxId = join1.id SET attr.entityModification = join1.t WHERE 1", "Unable to add entity modifications to Q_ATTRIBUTE_INDEX");

	std::cout << "finished." << std::endl;
}



void UniPAX::SERVER::MySQLQueryEngine::rebuildPathwayIndex()
{
	std::cout << "Rebuilding pathway index... " << std::flush;

	checkDatabaseConnection();

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "MySQLQueryEngine::rebuildPathwayIndex: Failed to connect mysql with QT";
	}

	exec(db, "DROP TABLE IF EXISTS Q_PATHWAY_INDEX", "Unable to drop table Q_PATHWAY_INDEX");
	exec(db, QString("CREATE TABLE Q_PATHWAY_INDEX (")
			.append("unipaxId BIGINT(20) UNSIGNED NOT NULL,")
			.append("type VARCHAR(40) NOT NULL,")
			.append("pathway_unipaxId BIGINT(20) UNSIGNED NOT NULL,")
			.append("pathway_standardName text DEFAULT NULL,")
			.append("PRIMARY KEY(unipaxId, pathway_unipaxId)")
			.append(") ENGINE=MyISAM"), "Unable to create table Q_PATHWAY_INDEX");

	QSqlQuery query = exec(db, "SELECT p.unipaxId, e.standardName FROM Pathway p LEFT JOIN Entity e ON p.unipaxId = e.unipaxId", "Unable to get pathway ids and names.");
	UniPAX::UPBase* current_pathway;
	std::map<std::string, std::string> data_type;
	std::map<UnipaxId, std::string>::iterator map_it;
	std::map<std::string, std::string>::iterator map_it2;
	std::map<UnipaxId, std::string> pathway_map;

	while (query.next())
	{
		pathway_map[query.value(0).toLongLong()] = query.value(1).toString().toStdString();
	}

	QSqlQuery p(*db);
	p.prepare("INSERT INTO Q_PATHWAY_INDEX (unipaxId, type, pathway_unipaxId, pathway_standardName) VALUES (:1, :2, :3, :4)");


	for (map_it = pathway_map.begin(); map_it != pathway_map.end(); map_it++)
	{
		boost::shared_ptr<UniPAX::UPBase> current_pathway = getObject(map_it->first);

		if (current_pathway != 0)
		{
			UniPAX::KernelCollector collector;
			collector.skipPathwaySteps(true);
			collector.collect(current_pathway);

			data_type = collector.getIdToType();
			for (map_it2 = data_type.begin(); map_it2 != data_type.end(); map_it2++)
			{
				p.bindValue(":1", QString(map_it2->first.c_str()));
				p.bindValue(":2", QString(map_it2->second.c_str()));
				p.bindValue(":3", QString::number(map_it->first));
				p.bindValue(":4", QString(map_it->second.c_str()));

				exec(p, "Unable to insert data into Q_PATHWAY_INDEX");
			}
		}

	}

	exec(db, "DROP TABLE IF EXISTS Q_PATHWAY_SIZE_INDEX", "Unable to drop table Q_PATHWAY_SIZE_INDEX");
	exec(db, QString("CREATE TABLE Q_PATHWAY_SIZE_INDEX (")
			.append("unipaxId BIGINT(20) UNSIGNED NOT NULL,")
			.append("type VARCHAR(40) NOT NULL,")
			.append("size INTEGER UNSIGNED NOT NULL,")
			.append("PRIMARY KEY(unipaxId, type)")
			.append(") ENGINE=MyISAM"), "Unable to create table Q_PATHWAY_SIZE_INDEX");

	exec(db, "INSERT INTO Q_PATHWAY_SIZE_INDEX (unipaxId, type, size) SELECT pathway_unipaxId, type, COUNT(*) FROM Q_PATHWAY_INDEX GROUP BY pathway_unipaxId, type", "Unable to create pathway sizes table");

	std::cout << "finished." << std::endl;
}

void UniPAX::SERVER::MySQLQueryEngine::rebuildIdMapping()
{
	std::cout << "Rebuilding ID mapping... " << std::flush;

	checkDatabaseConnection();

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "MySQLQueryEngine::rebuildIdMapping: Failed to connect mysql with QT";
	}

	exec(db, "DROP TABLE IF EXISTS Q_ID_MAPPING", "Unable to drop table Q_ID_MAPPING");
	exec(db, QString("CREATE TABLE Q_ID_MAPPING (")
			.append("src_system VARCHAR(40) NOT NULL,")
			.append("src_id VARCHAR(40) NOT NULL,")
			.append("tgt_system VARCHAR(40) NOT NULL,")
			.append("tgt_id VARCHAR(40) NOT NULL,")
			.append("PRIMARY KEY(src_system, src_id, tgt_system, tgt_id)")
			.append(") ENGINE=MyISAM"), "Unable to create table Q_ID_MAPPING");

	// get all id systems from UnificationXref and RelationshipXref and IdMapping objects
	QSqlQuery query = exec(db, QString("SELECT DISTINCT `db` FROM `Xref`"), "Unable to fetch external database names from Xref.");
	std::set<std::string> id_systems;
	while (query.next())
	{
		id_systems.insert(query.value(0).toString().toStdString());
	}
	query.finish();
	query = exec(db, "SELECT DISTINCT `db_name` FROM `IdMapping`", "Unable to get db_name from IdMapping");
	while (query.next())
	{
		id_systems.insert(query.value(0).toString().toStdString());
	}
	query.finish();
	UniPAX::BridgeDBWrapper bridgeDb;
	// get all ids for a single id system and map them to all supported target systems (half matrix)
	for (std::set<std::string>::iterator src_it = id_systems.begin(); src_it != id_systems.end(); src_it++)
	{
		// build id list of src_type
		std::set<std::string> tmp_ids;
		query = exec(db, QString("SELECT `IdMapping_id_list`.`value` FROM `IdMapping_id_list`,`IdMapping` WHERE `IdMapping_id_list`.`object_id` = `IdMapping`.`unipaxId` AND `IdMapping`.`db_name` LIKE '%1'")
				.arg(QString(src_it->c_str())), "Unable to fetch values from IdMapping_id_list");
		while (query.next())
		{
			tmp_ids.insert(query.value(0).toString().toStdString());
		}
		query.finish();

		query = exec(db, QString("SELECT `id` FROM `Xref` WHERE `db` LIKE '%1'").arg(QString(src_it->c_str())), "Unable to fetch ids from Xref");
		while (query.next())
		{
			tmp_ids.insert(query.value(0).toString().toStdString());
		}
		query.finish();

		std::vector<std::string> src_ids(tmp_ids.begin(), tmp_ids.end());
		// for all combinations of id_systems (triangular matrix) try to map ids
		for (std::set<std::string>::iterator tgt_it = id_systems.begin(); tgt_it != src_it; tgt_it++)
		{
			// use BridgeDBWrapper for mapping if supported:
			if (bridgeDb.isMappingSupported(*src_it, *tgt_it))
			{
				// map ids
				std::cout << "Mapping IDs from '" << *src_it << "' to '" << *tgt_it << "'\n";
				std::multimap<std::string, std::string> id_mapping;
				bridgeDb.mapIds(*src_it, src_ids, *tgt_it, id_mapping);
				// insert mapped ids into Q_ID_MAPPING table
				for (std::multimap<std::string, std::string>::iterator it = id_mapping.begin(); it != id_mapping.end(); ++it)
				{
					// insert both directions
					exec(db, QString("INSERT INTO Q_ID_MAPPING (src_system, src_id, tgt_system, tgt_id) VALUES ('%1','%2','%3','%4')")
							.arg(QString(src_it->c_str()), QString(it->first.c_str()), QString(tgt_it->c_str()), QString(it->second.c_str())), "Unable to insert id mapping into Q_ID_MAPPING");
					exec(db, QString("INSERT INTO Q_ID_MAPPING (src_system, src_id, tgt_system, tgt_id) VALUES ('%1','%2','%3','%4')")
							.arg(QString(tgt_it->c_str()), QString(it->second.c_str()), QString(src_it->c_str()), QString(it->first.c_str())), "Unable to insert id mapping into Q_ID_MAPPING");
				}
			}
			else
			{
				std::cout << "Mapping of IDs from '" << *src_it << "' to '" << *tgt_it << "' is not supported.\n";
			}
		}
	}
}

boost::shared_ptr<UniPAX::DBManager> UniPAX::SERVER::MySQLQueryEngine::getDBManager()
{
	return manager;
}




UniPAX::u_map<QString, QString>::type & UniPAX::SERVER::MySQLQueryEngine::getOrganismMap()
{
	if (org_map.empty())
	{
		checkDatabaseConnection();
		QSqlQuery query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM BioSource");
		while (query.next())
		{
			org_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();
	}
	return org_map;
}

UniPAX::u_map<QString, QString>::type & UniPAX::SERVER::MySQLQueryEngine::getDataSourceMap()
{
	if (datasource_map.empty())
	{
		checkDatabaseConnection();
		QSqlQuery query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM Provenance");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();
	}
	return datasource_map;
}

UnipaxPtr<UniPAX::UPBase>::type UniPAX::SERVER::MySQLQueryEngine::getObject(UnipaxId id)
{
	checkDatabaseConnection();

	if (id > 0 && manager->isValid(id))
	{
		return boost::dynamic_pointer_cast<UniPAX::DBManager>(manager)->getObjectByID(id);
	}

	return boost::shared_ptr<UniPAX::UPBase>();
}

bool UniPAX::SERVER::MySQLQueryEngine::getObjects(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> ids)
{
	checkDatabaseConnection();

	if (!ids.empty())
	{
		std::vector<UnipaxId>::iterator it = ids.begin();
		while (it != ids.end())
		{
			if (*it > 0 && manager->isValid(*it))
			{
				it++;
			}
			else
			{
				it = ids.erase(it);
			}
		}
		return boost::dynamic_pointer_cast<UniPAX::DBManager>(manager)->getObjectsByIDs(result, ids);
	}

	return false;
}

void UniPAX::SERVER::MySQLQueryEngine::getUnipaxIdsByType(std::set<UnipaxId> & result, QString type)
{
	if (!checkDatabaseConnection())
	{
		throw std::runtime_error("No connection to database");
	}

	QSqlQuery query = exec(manager->getDatabase(), QString("SELECT DISTINCT unipaxId FROM `%1`").arg(type), QString("Unable to fetch ids of type %1").arg(type));
	while (query.next())
	{
		result.insert((UnipaxId) query.value(0).toULongLong());
	}
	query.finish();

}

void UniPAX::SERVER::MySQLQueryEngine::getUnipaxIdsByName(std::map<UnipaxId, std::string> & result, QString name)
{
	if (!checkDatabaseConnection())
	{
		throw std::runtime_error("No connection to database");
	}

	QStringList named_types;
	named_types.append("BioSource");
	named_types.append("Entity");
	named_types.append("EntityReference");
	named_types.append("Provenance");

	if (!name.contains("%"))
		name = "%" + name + "%";

	for (int i = 0; i < named_types.length(); ++i)
	{
		QSqlQuery query = exec(manager->getDatabase(), QString("SELECT DISTINCT object_id, value FROM `%1_name` WHERE value LIKE '%2'").arg(named_types.at(i)).arg(name), QString("Unable to fetch names from %1").arg(named_types.at(i)));
		while (query.next())
		{
			result.insert(std::make_pair((UnipaxId) query.value(0).toULongLong(), query.value(1).toString().toStdString()));
		}
		query.finish();
	}

}

std::vector<std::string> UniPAX::SERVER::MySQLQueryEngine::getReferenceIds(std::string uid)
{
	if (!checkDatabaseConnection())
	{
			throw std::runtime_error("No connection to database");
	}
	std::vector<std::string> result;
	QSqlQuery query = exec(manager->getDatabase(), QString("SELECT DISTINCT target FROM C_RELATIONS WHERE source=%1 AND relation='entityReference'").arg(QString::fromStdString(uid)), QString("Unable to fetch Reference ids for object %1").arg(QString::fromStdString(uid)));
	while (query.next())
	{
		result.push_back(query.value(0).toString().toStdString());
	}
	query.finish();
	return result;
}

std::vector<std::string> UniPAX::SERVER::MySQLQueryEngine::getUnificationXrefIds(UnipaxId uid, std::string id_type)
{
	if (!checkDatabaseConnection())
	{
		throw std::runtime_error("No connection to database");
	}
	std::vector<std::string> result;
	QSqlQuery query = exec(manager->getDatabase(), QString("SELECT DISTINCT id FROM C_ENTITY_DBKEY WHERE entityId=%1 AND db='%2'").arg(uid).arg(QString::fromStdString(id_type)), QString("Unable to fetch UnificationXref ids for object %1").arg(uid));
	while (query.next())
	{
		result.push_back(query.value(0).toString().toStdString());
	}
	query.finish();
	return result;
}

void UniPAX::SERVER::MySQLQueryEngine::getUnipaxIdsByXref(std::set<UnipaxId> & result, QString db, QString id)
{
	if (!checkDatabaseConnection())
	{
		throw std::runtime_error("No connection to database");
	}

	QStringList named_types;
	named_types.append("BioSource");
	named_types.append("ControlledVocabulary");
	named_types.append("Entity");
	named_types.append("EntityReference");
	named_types.append("Evidence");
	named_types.append("Provenance");
	named_types.append("Series");

	for (int i = 0; i < named_types.length(); ++i)
	{
		QSqlQuery query = exec(manager->getDatabase(), QString("SELECT DISTINCT object_id FROM `%1_xref` LEFT JOIN Xref ON (value = unipaxId) WHERE db = '%2' AND id = '%3'").arg(named_types.at(i), db, id), QString("Unable to fetch xrefs from %1").arg(named_types.at(i)));
		while (query.next())
		{
			result.insert((UnipaxId) query.value(0).toULongLong());
		}
		query.finish();
	}

}

void UniPAX::SERVER::MySQLQueryEngine::getAttributes(std::map<UnipaxId, Attributes> & result, std::set<UnipaxId> & ids)
{
	if (!checkDatabaseConnection())
	{
		throw std::runtime_error("No connection to database");
	}

	for (std::set<UnipaxId>::iterator it = ids.begin(); it != ids.end(); it++)
	{
		bool ok = true;

		Attributes attr = getAttributes(*it, ok);
		if (ok)
			result.insert(std::make_pair(*it, attr));
	}

}

UniPAX::SERVER::Attributes UniPAX::SERVER::MySQLQueryEngine::getAttributes(UnipaxId id, bool & ok)
{
	ok = false;

	if (attributes_map.find(id) != attributes_map.end())
	{
		ok = true;
		return attributes_map[id];
	}

	Attributes attr;
	checkDatabaseConnection();

	QSqlQuery query = exec(manager->getDatabase(), QString("SELECT DISTINCT unipaxId, type, standardName, displayName, organism, dataSource, entityModification FROM Q_ATTRIBUTE_INDEX WHERE unipaxId = %1  LIMIT 1").arg(id), QString("Unable to fetch attributes for %1").arg(id));
	if (query.next())
	{
		attr.id = id;
		attr.type = query.value(1).toString();
		attr.standardName = query.value(2).toString();
		attr.displayName = query.value(3).toString();
		attr.organism = query.value(4).toULongLong();
		attr.dataSource = query.value(5).toULongLong();
		attr.entityModification = query.value(6).toString();
		ok = true;
	}
	query.finish();
	if (ok)
	{
		attributes_map[id] = attr;
	}
	return attr;
}



bool UniPAX::SERVER::MySQLQueryEngine::getPathwaysOfAllGeneIDs(QByteArray& data)
{

	//	std::cout << "getPathwaysOfAllGeneIDs " << std::endl;

	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open()) std::cerr << "MySQLQueryEngine::getPathwaysOfAllGeneIDs: Failed to connect mysql with QT";
	}

	if (manager->getDatabase()->isValid())
	{
		if (datasource_map.empty())
		{
			QSqlQuery query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM Provenance");
			while (query.next())
			{
				datasource_map[query.value(0).toString()] = query.value(1).toString();
			}
			query.finish();
		}

		QSqlQuery query2; //, query3;
		QSqlQuery query = manager->getDatabase()->exec("select distinct r.id  from Q_PATHWAY_INDEX q, RelationshipXref r where q.type = 'RelationshipXref' and q.unipaxId = r.unipaxId and r.db = 'EntrezGene' order by r.id");
		while (query.next())
		{
			QString current_gene_id = query.value(0).toString().toUtf8();
			data.append(current_gene_id);
			std::cout << current_gene_id.toStdString() << std::endl;

			query2 = manager->getDatabase()->exec(QString("select DISTINCT q.pathway_unipaxId, q.pathway_standardName, a.dataSource "
					"from Q_PATHWAY_INDEX q, Q_ATTRIBUTE_INDEX a, RelationshipXref r where q.type = 'RelationshipXref' "
					"and q.unipaxId = r.unipaxId and r.db = 'EntrezGene' "
					"and r.id = '%1' and a.unipaxId = q.pathway_unipaxId ").arg(current_gene_id));
			while (query2.next())
			{
				//				QString unipax_id = query2.value(0).toString().toUtf8();
				//
				//				QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX WHERE Q_ATTRIBUTE_INDEX.unipaxId = '%1'").arg(unipax_id));
				//				query3 = manager->getDatabase()->exec(sql);
				//				while (query3.next())
				//				{
				data.append('\t');
				data.append(query2.value(1).toString().toUtf8());
				data.append(" | ");
				if (query2.value(2).isNull())
					data.append("NULL");
				else
				{
					if (datasource_map.find(query2.value(2).toString()) != datasource_map.end())
						data.append(datasource_map[query2.value(2).toString()]);
					else
						data.append(query2.value(2).toString().toUtf8());
				}
				data.append(" | ");
				data.append(query2.value(0).toString().toUtf8());
				//				}
			}
			data.append('\n');

		}
		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;

}



bool UniPAX::SERVER::MySQLQueryEngine::getPathwaysOfGeneID(QByteArray& data, QString id)
{

	std::cout << "getPathwaysOfGeneID: " << id.toStdString() << std::endl;

	//	data.append("% unipaxId\tstandardName\n");
	data.append("% unipaxId\ttype\tstandardName\tdisplayName\torganism\tname value\tdataSource\n");

	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open()) std::cerr << "MySQLQueryEngine::getPathwaysOfGeneID: Failed to connect mysql with QT";
	}


	if (manager->getDatabase()->isValid())
	{

		std::map<QString, QString> org_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM BioSource");
		while (query.next())
		{
			org_map[query.value(0).toString().toUtf8()] = query.value(1).toString().toUtf8();
		}
		query.finish();

		std::map<QString, QString> datasource_map;
		query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM Provenance");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();
		//
		//
		//		QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, "
		//				"Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value FROM Q_ATTRIBUTE_INDEX "
		//				"INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId "
		//				"WHERE Q_ATTRIBUTE_INDEX.unipaxId in (select distinct DISTINCT q.pathway_unipaxId "
		//				"from Q_PATHWAY_INDEX q, RelationshipXref r where q.type = 'RelationshipXref' "
		//				"and q.unipaxId = r.unipaxId and r.db = 'Entrez Gene' "
		//				"and r.id = '%1')").arg(id));
		//
		//		query = manager->getDatabase()->exec(sql);

		QSqlQuery query2;
		query = manager->getDatabase()->exec(QString("select distinct DISTINCT q.pathway_unipaxId, q.pathway_standardName "
				"from Q_PATHWAY_INDEX q, RelationshipXref r where q.type = 'RelationshipXref' "
				"and q.unipaxId = r.unipaxId and r.db = 'EntrezGene' "
				"and r.id = '%1'").arg(id));
		while (query.next())
		{
			QString unipax_id = query.value(0).toString().toUtf8();
			//			data.append(query.value(0).toString().toUtf8());
			//			data.append('\t');
			//			data.append(query.value(1).toString().toUtf8());
			//			data.append('\n');

			QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId WHERE Q_ATTRIBUTE_INDEX.unipaxId = '%1'").arg(unipax_id));
			query2 = manager->getDatabase()->exec(sql);
			while (query2.next())
			{
				data.append(query2.value(0).toString().toUtf8());
				data.append('\t');
				data.append(query2.value(1).toString().toUtf8());
				data.append('\t');
				if (query2.value(2).isNull())
					data.append("NULL");
				else
					data.append(query2.value(2).toString().toUtf8());
				data.append('\t');
				if (query2.value(3).isNull())
					data.append("NULL");
				else
					data.append(query2.value(3).toString().toUtf8());
				data.append('\t');
				if (query2.value(4).isNull())
					data.append("NULL");
				else
				{
					if (org_map.find(query2.value(4).toString().toUtf8()) != org_map.end())
						data.append(org_map[query2.value(4).toString().toUtf8()]);
					else
						data.append(query2.value(4).toString().toUtf8());
				}
				data.append('\t');
				if (query2.value(5).isNull())
					data.append("NULL");
				else
					data.append(query2.value(5).toString().toUtf8());
				data.append('\t');
				if (query2.value(6).isNull())
					data.append("NULL");
				else
				{
					if (datasource_map.find(query2.value(6).toString().toUtf8()) != datasource_map.end())
						data.append(datasource_map[query2.value(6).toString().toUtf8()]);
					else
						data.append(query2.value(6).toString().toUtf8());
				}

				data.append('\n');
			}
		}
		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;
}

bool UniPAX::SERVER::MySQLQueryEngine::getPathwaysOfGeneIDs(QByteArray& data, QStringList& ids)
{ //TODO
	//
	//	std::cout << "getPathwaysOfGeneIDs: " << id.toStdString() << std::endl;
	//
	////	data.append("% unipaxId\tstandardName\n");
	//	data.append("% unipaxId\ttype\tstandardName\tdisplayName\torganism\tname value\tdataSource\n");
	//
	//	checkDatabaseConnection();
	//	if (!manager->getDatabase()->isOpen())
	//	{
	//		if (!manager->getDatabase()->open()) std::cerr << "MySQLQueryEngine::getPathwaysOfGeneID: Failed to connect mysql with QT";
	//	}
	//
	//
	//	if (manager->getDatabase()->isValid())
	//	{
	//
	//		std::map<QString, QString> org_map;
	//		QSqlQuery query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM BioSource");
	//		while (query.next())
	//		{
	//			org_map[query.value(0).toString().toUtf8()] = query.value(1).toString().toUtf8();
	//		}
	//		query.finish();
	//
	//		std::map<QString, QString> datasource_map;
	//		query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM Provenance");
	//		while (query.next())
	//		{
	//			datasource_map[query.value(0).toString()] = query.value(1).toString();
	//		}
	//		query.finish();
	////
	////
	////		QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, "
	////				"Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value FROM Q_ATTRIBUTE_INDEX "
	////				"INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId "
	////				"WHERE Q_ATTRIBUTE_INDEX.unipaxId in (select distinct DISTINCT q.pathway_unipaxId "
	////				"from Q_PATHWAY_INDEX q, RelationshipXref r where q.type = 'RelationshipXref' "
	////				"and q.unipaxId = r.unipaxId and r.db = 'Entrez Gene' "
	////				"and r.id = '%1')").arg(id));
	////
	////		query = manager->getDatabase()->exec(sql);
	//
	//		QSqlQuery query2;
	//		query = manager->getDatabase()->exec(QString("select DISTINCT q.pathway_unipaxId, q.pathway_standardName "
	//				"from Q_PATHWAY_INDEX q, RelationshipXref r where q.type = 'RelationshipXref' "
	//				"and q.unipaxId = r.unipaxId and r.db = 'EntrezGene' "
	//				"and r.id = '%1'").arg(id));
	//		while (query.next())
	//		{
	//			QString unipax_id = query.value(0).toString().toUtf8();
	////			data.append(query.value(0).toString().toUtf8());
	////			data.append('\t');
	////			data.append(query.value(1).toString().toUtf8());
	////			data.append('\n');
	//
	//			QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId WHERE Q_ATTRIBUTE_INDEX.unipaxId = '%1'").arg(unipax_id));
	//			query2 = manager->getDatabase()->exec(sql);
	//			while (query2.next())
	//			{
	//				data.append(query2.value(0).toString().toUtf8());
	//				data.append('\t');
	//				data.append(query2.value(1).toString().toUtf8());
	//				data.append('\t');
	//				if (query2.value(2).isNull())
	//					data.append("NULL");
	//				else
	//					data.append(query2.value(2).toString().toUtf8());
	//				data.append('\t');
	//				if (query2.value(3).isNull())
	//					data.append("NULL");
	//				else
	//					data.append(query2.value(3).toString().toUtf8());
	//				data.append('\t');
	//				if (query2.value(4).isNull())
	//					data.append("NULL");
	//				else
	//				{
	//					if (org_map.find(query2.value(4).toString().toUtf8()) != org_map.end())
	//						data.append(org_map[query2.value(4).toString().toUtf8()]);
	//					else
	//						data.append(query2.value(4).toString().toUtf8());
	//				}
	//				data.append('\t');
	//				if (query2.value(5).isNull())
	//					data.append("NULL");
	//				else
	//					data.append(query2.value(5).toString().toUtf8());
	//				data.append('\t');
	//				if (query2.value(6).isNull())
	//					data.append("NULL");
	//				else
	//				{
	//					if (datasource_map.find(query2.value(6).toString().toUtf8()) != datasource_map.end())
	//						data.append(datasource_map[query2.value(6).toString().toUtf8()]);
	//					else
	//						data.append(query2.value(6).toString().toUtf8());
	//				}
	//
	//				data.append('\n');
	//			}
	//		}
	//		return true;
	//	}
	//	else
	//	{
	//		data.append("Database not available.\n");
	//	}

	return false;
}

bool UniPAX::SERVER::MySQLQueryEngine::getPathwayMapOfIds(std::multimap<UnipaxId, UnipaxId>& pw_id, const std::vector<UnipaxId> ids)
{
	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open()) std::cerr << "MySQLQueryEngine::getPathwayMapOfIds: Failed to connect mysql with QT";
	}
	if (manager->getDatabase()->isValid())
	{
		for (std::vector<UnipaxId>::const_iterator it = ids.begin(); it != ids.end(); ++it)
		{
			QSqlQuery query = manager->getDatabase()->exec(QString("SELECT DISTINCT pathwayId FROM C_ENTITY_PATHWAY WHERE entityId = '%1'").arg(*it));
			while (query.next())
			{
				pw_id.insert(std::pair<UnipaxId, UnipaxId>(query.value(0).toULongLong(), *it));
			}
		}
		return true;
	}
	return false;
}

bool UniPAX::SERVER::MySQLQueryEngine::getPathwaysOf(QByteArray& data, QString id)
{

	std::cout << "getPathwaysOf: " << id.toStdString() << std::endl;

	//	data.append("% unipaxId\tstandardName\n");
	data.append("% unipaxId\ttype\tstandardName\tdisplayName\torganism\tname value\tdataSource\n");

	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open()) std::cerr << "MySQLQueryEngine::getPathwaysOf: Failed to connect mysql with QT";
	}


	if (manager->getDatabase()->isValid())
	{

		std::map<QString, QString> org_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM BioSource");
		while (query.next())
		{
			org_map[query.value(0).toString().toUtf8()] = query.value(1).toString().toUtf8();
		}
		query.finish();

		std::map<QString, QString> datasource_map;
		query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM Provenance");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();

		QSqlQuery query2;
		query = manager->getDatabase()->exec(QString("SELECT DISTINCT pathway_unipaxId, pathway_standardName FROM Q_PATHWAY_INDEX WHERE unipaxId = %1").arg(id));
		while (query.next())
		{
			//			data.append(query.value(0).toString().toUtf8());
			//			data.append('\t');
			//			data.append(query.value(1).toString().toUtf8());
			//			data.append('\n');

			QString unipax_id = query.value(0).toString().toUtf8();
			QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId WHERE Q_ATTRIBUTE_INDEX.unipaxId = '%1'").arg(unipax_id));
			query2 = manager->getDatabase()->exec(sql);
			while (query2.next())
			{
				data.append(query2.value(0).toString().toUtf8());
				data.append('\t');
				data.append(query2.value(1).toString().toUtf8());
				data.append('\t');
				if (query2.value(2).isNull())
					data.append("NULL");
				else
					data.append(query2.value(2).toString().toUtf8());
				data.append('\t');
				if (query2.value(3).isNull())
					data.append("NULL");
				else
					data.append(query2.value(3).toString().toUtf8());
				data.append('\t');
				if (query2.value(4).isNull())
					data.append("NULL");
				else
				{
					if (org_map.find(query2.value(4).toString().toUtf8()) != org_map.end())
						data.append(org_map[query2.value(4).toString().toUtf8()]);
					else
						data.append(query2.value(4).toString().toUtf8());
				}
				data.append('\t');
				if (query2.value(5).isNull())
					data.append("NULL");
				else
					data.append(query2.value(5).toString().toUtf8());
				data.append('\t');
				if (query2.value(6).isNull())
					data.append("NULL");
				else
				{
					if (datasource_map.find(query2.value(6).toString().toUtf8()) != datasource_map.end())
						data.append(datasource_map[query2.value(6).toString().toUtf8()]);
					else
						data.append(query2.value(6).toString().toUtf8());
				}
				data.append('\n');
			}
		}
		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;
}

bool UniPAX::SERVER::MySQLQueryEngine::getPathwaysOfs(QByteArray& data, QStringList & ids)
{
	if (ids.isEmpty()) {
		data.append("At least one ID expected.\n");
		return false;
	}

	data.append("% unipaxId\tpathwayId\ttype\tstandardName\tdisplayName\torganism\tname value\tdataSource\tsize\n");

	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open()) std::cerr << "MySQLQueryEngine::getPathwaysOfs: Failed to connect mysql with QT";
	}


	if (manager->getDatabase()->isValid())
	{

		std::map<QString, QString> org_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM BioSource");
		while (query.next())
		{
			org_map[query.value(0).toString().toUtf8()] = query.value(1).toString().toUtf8();
		}
		query.finish();

		std::map<QString, QString> datasource_map;
		query = manager->getDatabase()->exec("SELECT unipaxId, standardName FROM Provenance");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();

		QSqlQuery query2;
		QString sql("SELECT DISTINCT unipaxId, pathway_unipaxId, pathway_size FROM Q_PATHWAY_INDEX WHERE ");
		for (unsigned int i = 0; i < ids.length(); ++i)
		{
			if (i > 0)
				sql.append(" OR ");
			sql.append(QString("unipaxId = %1").arg(ids.at(i)));
		}

		query = manager->getDatabase()->exec(sql);
		while (query.next())
		{
			QString unipax_id = query.value(0).toString().toUtf8();
			QString pathway_id = query.value(1).toString().toUtf8();
			QString pathway_size = query.value(3).toString().toUtf8();

			QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId WHERE Q_ATTRIBUTE_INDEX.unipaxId = '%1'").arg(pathway_id));
			query2 = manager->getDatabase()->exec(sql);
			if (query2.next())
			{
				data.append(unipax_id);
				data.append('\t');
				data.append(query2.value(0).toString().toUtf8());
				data.append('\t');
				data.append(query2.value(1).toString().toUtf8());
				data.append('\t');
				if (query2.value(2).isNull())
					data.append("NULL");
				else
					data.append(query2.value(2).toString().toUtf8());
				data.append('\t');
				if (query2.value(3).isNull())
					data.append("NULL");
				else
					data.append(query2.value(3).toString().toUtf8());
				data.append('\t');
				if (query2.value(4).isNull())
					data.append("NULL");
				else
				{
					if (org_map.find(query2.value(4).toString().toUtf8()) != org_map.end())
						data.append(org_map[query2.value(4).toString().toUtf8()]);
					else
						data.append(query2.value(4).toString().toUtf8());
				}
				data.append('\t');
				if (query2.value(5).isNull())
					data.append("NULL");
				else
					data.append(query2.value(5).toString().toUtf8());
				data.append('\t');
				if (query2.value(6).isNull())
					data.append("NULL");
				else
				{
					if (datasource_map.find(query2.value(6).toString().toUtf8()) != datasource_map.end())
						data.append(datasource_map[query2.value(6).toString().toUtf8()]);
					else
						data.append(query2.value(6).toString().toUtf8());
				}
				data.append(pathway_size);
				data.append('\n');
			}
		}
		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;
}

bool UniPAX::SERVER::MySQLQueryEngine::query(QByteArray& data, QString sql_query)
{
	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open()) std::cerr << "MySQLQueryEngine::query: Failed to connect mysql with QT";
	}
	if (manager->getDatabase()->isValid())
	{
		//std::cerr << "MySQLQueryEngine::query: executing query: " << sql_query.toStdString() << std::endl;
		QSqlQuery query = manager->getDatabase()->exec(sql_query);
		int cntlines = 0;
		while (query.next())
		{
			if (cntlines != 0) data.append('\n');
			for (int i=0; i != query.record().count(); i++)
			{
				//std::cerr << "MySQLQueryEngine::query: appending: " << query.value(i).toString().toStdString() << std::endl;

				if (i!=0) data.append('\t');
				data.append(query.value(i).toString().toUtf8());
			}
			cntlines++;
		}
		return true;
	}
	else
	{
		std::cerr << "MySQLQueryEngine::query: Database not available.\n";
	}
	return false;
}

bool UniPAX::SERVER::MySQLQueryEngine::search(QByteArray& data, const QUrl& url, QString resultID)
{

	std::cout << "search: " << url.toString().toStdString() << " " << resultID.toStdString() << std::endl;

	QString type = url.queryItemValue("type");

	std::cout << "Type: " << type.toStdString() << std::endl;

	if (type != "")
	{
		checkDatabaseConnection();
		if (!manager->getDatabase()->isOpen())
		{
			if (!manager->getDatabase()->open()) std::cerr << "MySQLQueryEngine::search: Failed to connect mysql with QT";
		}
		if (manager->getDatabase()->isValid())
		{
			QSqlQuery query = manager->getDatabase()->exec("SELECT * FROM " + type);
			while (query.next())
			{
				data.append(query.value(0).toString());
				data.append("\n");
			}

			return true;

		}
		else
		{
			data.append("Database not available.\n");
		}

	}
	else
	{
		data.append("Unknown filter.\n");
	}
	return false;
}

bool UniPAX::SERVER::MySQLQueryEngine::checkDatabaseConnection()
{
	QSqlDatabase* db = manager->getDatabase();


	if (!manager->getDatabase()->isOpen())
	{
		db->open();
	}

	QSqlQuery query = db->exec("SELECT 1 FROM DUAL");
	query.next();
	QSqlError error = query.lastError();

	if (error.type() > 0)
	{
		std::cout << "check connection (error code " << error.type() << ")" << std::endl;
		std::cout << "reconnect... ";
		db->open();
		std::cout << "done!" << std::endl;
	}
	return true;
}

void UniPAX::SERVER::MySQLQueryEngine::getXrefDbs(QStringList & list)
{
	checkDatabaseConnection();
	QSqlDatabase* db = manager->getDatabase();

	if (!manager->getDatabase()->isOpen())
	{
		throw std::runtime_error("Database not accessible.");
	}


	QSqlQuery query = db->exec("SELECT DISTINCT db FROM Xref");
	while (query.next())
	{
		list.append(query.value(0).toString());
	}

}

bool UniPAX::SERVER::MySQLQueryEngine::mapIds(std::string sourceIdSystem, std::vector<std::string> sourceIds, std::string targetIdSystem, std::multimap<std::string, std::string> & source_targetUnipaxIds)
{
	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open())
			std::cerr << "MySQLQueryEngine::mapIds: Failed to connect mysql with QT" << std::endl;
	}
	if (manager->getDatabase()->isValid())
	{
		{
			std::set<std::string> unique_ids(sourceIds.begin(), sourceIds.end());
			QSqlQuery query = manager->getDatabase()->exec(QString("SELECT * FROM Q_ID_MAPPING WHERE src_system = '%1' AND tgt_system = '%2'").arg(QString::fromStdString(sourceIdSystem)).arg(QString::fromStdString(targetIdSystem)));
			while (query.next())
			{
				std::string src_id = query.value(1).toString().toStdString();
				std::string trg_id = query.value(3).toString().toStdString();
				if (unique_ids.find(src_id) != unique_ids.end())
				{
					source_targetUnipaxIds.insert(std::pair<std::string, std::string>(src_id, trg_id));
				}
			}
		}
		if (source_targetUnipaxIds.empty())
		{
			//try to use BridgeDb
			QUrl endpoint;
			endpoint.setHost(QString("webservice.bridgedb.org"));
			endpoint.setPort(80);
			endpoint.setScheme(QString("http"));
			UniPAX::BridgeDBLink bridge(endpoint);
			std::map<std::string, std::string> e_s_names;
			if (bridge.contents(e_s_names))
			{
				manager->getDatabase()->transaction();
				QSqlQuery query(*manager->getDatabase());
				query.prepare("INSERT INTO Q_ID_MAPPING (src_system, src_id, tgt_system, tgt_id) VALUES (:src_sys, :src_id, :tgt_sys, :tgt_id)");
				query.bindValue(":src_sys", QString::fromStdString(sourceIdSystem));
				query.bindValue(":tgt_sys", QString::fromStdString(targetIdSystem));
				bool ok = false;
				for (std::map<std::string, std::string>::const_iterator it = e_s_names.begin(); it != e_s_names.end(); it++)
				{
					if (bridge.isMappingSupported(ok, it->second, sourceIdSystem, targetIdSystem))
					{
						if (ok)
						{
							// map all ids
							for (std::vector<std::string>::const_iterator sid = sourceIds.begin(); sid != sourceIds.end(); sid++)
							{
								std::multimap<std::string, std::string> id_system;
								if (bridge.mapXref(id_system, it->second, sourceIdSystem, *sid, targetIdSystem))
								{
									query.bindValue(":src_id", QString::fromStdString(*sid));
									for (std::multimap<std::string, std::string>::const_iterator hit = id_system.begin(); hit != id_system.end(); hit++)
									{
										query.bindValue(":tgt_id", QString::fromStdString(hit->first));
										query.exec();
										source_targetUnipaxIds.insert(std::pair<std::string, std::string>(*sid, hit->first));
									}
								}
							}
							//break; // return here because we want to skip other species
						}
					}
				}
				manager->getDatabase()->commit();
			}
		}
		return true;
	}
	else
	{
		std::cerr << "MySQLQueryEngine::mapIds: Database not available." << std::endl;
	}
	return false;
}

bool UniPAX::SERVER::MySQLQueryEngine::isMappingSupported(std::string sourceIdSystem, std::string targetIdSystem)
{
	// return if it is supported!!!
	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open())
			std::cerr << "MySQLQueryEngine::mapIds: Failed to connect mysql with QT" << std::endl;
	}
	if (manager->getDatabase()->isValid())
	{
		QSqlQuery query = manager->getDatabase()->exec(QString("SELECT * FROM Q_ID_MAPPING WHERE src_system = '%1' AND tgt_system = '%2'").arg(QString::fromStdString(sourceIdSystem)).arg(QString::fromStdString(targetIdSystem)));
		if (query.next())
		{
			return true;
		}
		else // try to map ids using BridgeDB webservice
		{
			QUrl endpoint;
			endpoint.setHost(QString("webservice.bridgedb.org"));
			endpoint.setPort(80);
			endpoint.setScheme(QString("http"));
			UniPAX::BridgeDBLink bridge(endpoint);
			std::map<std::string, std::string> e_s_names;
			if (bridge.contents(e_s_names))
			{
				bool ok = false;
				for (std::map<std::string, std::string>::const_iterator it = e_s_names.begin(); it != e_s_names.end(); it++)
				{
					if (bridge.isMappingSupported(ok, it->second, sourceIdSystem, targetIdSystem))
					{
						if (ok) return true;
					}
				}
			}
		}
	}
	else
	{
		std::cerr << "MySQLQueryEngine::mapIds: Database not available." << std::endl;
	}
	return false;
}

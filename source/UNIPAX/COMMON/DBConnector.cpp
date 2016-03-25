#include <UNIPAX/COMMON/DBConnector.h>

#include <UNIPAX/COMMON/KernelClassSet.h>
#include <UNIPAX/COMMON/OrganismSet.h>
#include <UNIPAX/COMMON/PathwaySet.h>

#include <stdexcept>
#include <UNIPAX/KERNEL/all.h>
#include <UNIPAX/KERNEL/EXT/ResultObject.h>
#ifdef ODB_MYSQL
#include <UNIPAX/SERVER/BACKEND/MYSQL/MySQLQueryEngine.h>
#include <UNIPAX/GRAPH/MAPPING/MYSQL/MySQLMappingEngine.h>
#elif defined ODB_ORACLE
#include <UNIPAX/SERVER/BACKEND/ORACLE/OracleQueryEngine.h>
#include <UNIPAX/GRAPH/MAPPING/ORACLE/OracleMappingEngine.h>
#endif

UniPAX::DBConnector::DBConnector()
{
}

/*#ifdef ODB_MYSQL
UniPAX::DBConnector::DBConnector(UniPAX::SERVER::MySQLQueryEnginePtr engine, UniPAX::GRAPH::mysql::MySQLMappingEnginePtr mapping_engine) :
				engine_(engine),
				mapping_engine_(mapping_engine)
{
}
#elif defined ODB_ORACLE
UniPAX::DBConnector::DBConnector(UniPAX::SERVER::OracleQueryEnginePtr engine, UniPAX::GRAPH::oracle::OracleMappingEnginePtr mapping_engine) :
				engine_(engine),
				mapping_engine_(mapping_engine)
{
}
#endif*/

UniPAX::DBConnector::DBConnector(UniPAX::SERVER::QueryEnginePtr engine, UniPAX::GRAPH::MappingEnginePtr mapping_engine) :
								engine_(engine),
								mapping_engine_(mapping_engine)
{
}

UniPAX::DBConnector::DBConnector(const UniPAX::DBConnector & arg) :
								engine_(arg.engine_),
								mapping_engine_(arg.mapping_engine_)
{
}

UniPAX::DBConnector & UniPAX::DBConnector::operator =(const UniPAX::DBConnector & arg)
{
	engine_ = arg.engine_;
	mapping_engine_ = arg.mapping_engine_;
	return *this;
}

UniPAX::DBConnector::~DBConnector()
{
}

UniPAX::DBConnector::DBConnector(std::string host, const int port, std::string user_name, const std::string passwd, std::string db_name)
{
#ifdef ODB_MYSQL
	engine_ = UnipaxPtr<UniPAX::SERVER::MySQLQueryEngine>::type(new UniPAX::SERVER::MySQLQueryEngine());
#elif defined ODB_ORACLE
	engine_ = UnipaxPtr<UniPAX::SERVER::OracleQueryEngine>::type(new UniPAX::SERVER::OracleQueryEngine());
#endif
	engine_->getDBManager()->setDBCredentials(user_name, passwd, host, port, db_name);
	if (!engine_->getDBManager()->initDatabase())
	{
		throw std::runtime_error("DBConnector: Unable to initialize database.");
	}
#ifdef ODB_MYSQL
	mapping_engine_ = UnipaxPtr<UniPAX::GRAPH::mysql::MySQLMappingEngine>::type(new UniPAX::GRAPH::mysql::MySQLMappingEngine(engine_->getDBManager()));
#elif defined ODB_ORACLE
	mapping_engine_ = UnipaxPtr<UniPAX::GRAPH::oracle::OracleMappingEngine>::type(new UniPAX::GRAPH::oracle::OracleMappingEngine(engine_->getDBManager()));
#endif
	if (mapping_engine_->needsRebuildDatabaseCache())
	{
		mapping_engine_->rebuildDatabaseCache();
	}
}

UnipaxPtr<UniPAX::SERVER::QueryEngine>::type UniPAX::DBConnector::getEngine() const
{
	return engine_;
}

void UniPAX::DBConnector::setEngine(UnipaxPtr<SERVER::QueryEngine>::type engine)
{
	engine_ = engine;
}

bool UniPAX::DBConnector::resultObjectExists(UniPAX::ResultObjectPtr & result, QString rest_query_str)
{
	QByteArray query_result;
	QString query = QString("SELECT unipaxId FROM ResultObject WHERE constituting_query = '%1' COLLATE latin1_general_cs").arg(rest_query_str);
	if (!engine_->query(query_result, query))
	{
		std::cerr << "ERROR: DBConnector::resultObjectExists: Engine query did not succeed." << std::endl;
		return false;
	}
	QList<QByteArray> lines = query_result.split('\n');
	if (query_result.isEmpty())
	{
		return false;
	}
	if (lines.size() > 1)
	{
		std::cerr << "Warning: DBConnector::resultObjectExists: Multiple identical result objects found." << std::endl;
	}
	UnipaxId result_id = lines.first().toULongLong();
	result = boost::dynamic_pointer_cast<UniPAX::ResultObject>(getEngine()->getDBManager()->getObjectByID(result_id));
	return true;
}

UniPAX::ResultObjectPtr UniPAX::DBConnector::query(UniPAX::OrganismSet orgs, UniPAX::PathwaySet pathws, UniPAX::KernelClassSet types)
{
	engine_->checkIndexes();

	QByteArray result;
	QString org_clause, pws_clause, typ_clause;
	std::vector<std::pair<int, QString> > resultSize_queryString; // number of results -> column=constraint
	if (!orgs.isEmpty()) // restriction of organism
	{

		org_clause.append("WHERE organism IS NULL");
		std::set<UnipaxId> hlp = orgs.getIds();
		for (std::set<UnipaxId>::const_iterator it = hlp.begin(); it != hlp.end(); ++it)
		{
			org_clause.append(" OR ");
			org_clause.append("organism = ");
			org_clause.append(QString::number(*it));
		}
		if (!engine_->query(result, QString("SELECT COUNT(*) FROM Q_ATTRIBUTE_INDEX ").append(org_clause)))
		{
			std::cerr << "DBConnector::query: Engine query did not succeed." << std::endl;
		}
		else
		{
			bool ok;
			int num = result.toInt(&ok);
			if (!ok)
			{
				std::cerr << "DBConnector::query: Can not convert " << result.constData() << " to int." << std::endl;
			}

			resultSize_queryString.push_back(std::pair<int, QString>(num, org_clause));
		}

	}
	result.clear();
	if (!types.isEmpty()) // restriction of type
	{

		std::set<UnipaxId> ids;


		typ_clause.append("WHERE ");
		std::set<UniPAX::ClassType::ID> hlp = types.getIds();
		for (std::set<UniPAX::ClassType::ID>::const_iterator it = hlp.begin(); it != hlp.end(); ++it)
		{
			if (it != hlp.begin()) typ_clause.append(" OR ");
			typ_clause.append("typeId = ");
			typ_clause.append(QString::number((int)*it));

			engine_->getUnipaxIdsByType(ids, QString::fromStdString(Kernel::classType(*it, "")));
		}

		resultSize_queryString.push_back(std::pair<int, QString>(ids.size(), typ_clause));

//		if (!engine_->query(result, QString("SELECT COUNT(*) FROM Q_ATTRIBUTE_INDEX ").append(typ_clause)))
//		{
//			std::cerr << "DBConnector::query: Engine query did not succeed." << std::endl;
//		}
//		else
//		{
//			bool ok;
//			int num = result.toInt(&ok);
//			if (!ok)
//			{
//				std::cerr << "DBConnector::query: Can not convert " << result.constData() << " to int." << std::endl;
//			}
//			resultSize_queryString.push_back(std::pair<int, QString>(num, typ_clause));
//		}
	}
	// sort queries to begin with the smallest one
	std::sort(resultSize_queryString.begin(), resultSize_queryString.end(), UniPAX::DBConnector::QueryPredicate());
	// build nested query
	QString select;
	int tables = 0;
	for (std::vector<std::pair<int, QString> >::const_iterator it = resultSize_queryString.begin(); it != resultSize_queryString.end(); ++it)
	{
		++tables;
		if (tables == 1)
		{
			select.append("(SELECT * FROM Q_ATTRIBUTE_INDEX ").append(it->second).append(QString(") AS tab%1").arg(tables));
		}
		else
		{
			select.prepend("(SELECT * FROM ").append(" ").append(it->second).append(QString(") AS tab%1").arg(tables));
		}
	}
	// join with Pathway
	if (!pathws.isEmpty()) // restriction of pathway
	{
		pws_clause.append("(SELECT unipaxId FROM Q_PATHWAY_INDEX WHERE ");
		std::set<UnipaxId> hlp = pathws.getIds();
		for (std::set<UnipaxId>::const_iterator it = hlp.begin(); it != hlp.end(); ++it)
		{
			if (it != hlp.begin()) pws_clause.append(" OR ");
			pws_clause.append("pathway_unipaxId = ");
			pws_clause.append(QString::number(*it));
		}
		pws_clause.append(") AS pws");
		select.append(" INNER JOIN ").append(pws_clause).append(QString(" ON tab%1.unipaxId = pws.unipaxId").arg(tables));
	}
	// request matching IDs
	QString query;
	// // special cases:

	if (tables != 0) // restriction of org or type
	{
		query = QString("SELECT tab%1.unipaxId FROM ").arg(tables).append(select).append(";");
	}
	else // no restriction of org or type
	{
		if (pathws.getIds().size() == 0) // no restriction of pathway => all IDs
		{
			query = QString("SELECT unipaxId FROM Q_ATTRIBUTE_INDEX;");
		}
		else // all IDs from pws_clause
		{
			query = QString("SELECT * FROM ").append(pws_clause).append(";");
		}
	}
	std::cerr << "DBConnector: query string: "
			<< query.toStdString()
			<< std::endl;
	UnipaxPtr<UniPAX::ResultObject>::type result_obj;
	result.clear();
	if (!engine_->query(result, query))
	{
		std::cerr << "DBConnector::query: Engine query did not succeed." << std::endl;
	}
	else
	{
		result_obj = boost::dynamic_pointer_cast<UniPAX::ResultObject>(UniPAX::ObjectFactory::getInstance(UniPAX::ClassType::idResultObject));
		bool created = true;
		if (created)
		{
			if(!result.isEmpty())
			{
				QList<QByteArray> lines = result.split('\n');
				std::set<UnipaxId> tmp;
				for (QList<QByteArray>::const_iterator it = lines.constBegin(); it !=lines.constEnd(); ++it)
				{
					tmp.insert(it->toULongLong());
				}
				result_obj->setObjectIds(tmp);
			}
			result_obj->setConstitutingQuery(query.toStdString());
			result_obj->setCreationTime(UnipaxTime(micro_sec::universal_time()));
			// assign Id
			engine_->getDBManager()->assignId(result_obj);
		}
		else
		{
			std::cerr << "DBConnector::query: ResultObject creation failed." << std::endl;
		}

	}
	return result_obj;

}

UniPAX::GRAPH::MetabolicNetworkPtr UniPAX::DBConnector::createMetabolicNetwork(UniPAX::ResultObject obj)
{
	return mapping_engine_->createMetabolicNetwork(UniPAX::Kernel::children("PhysicalEntity", true), obj);
}

UniPAX::GRAPH::RegulatoryNetworkPtr UniPAX::DBConnector::createRegulatoryNetwork(UniPAX::ResultObject obj)
{
	UniPAX::GRAPH::RegulatoryNetworkPtr network = mapping_engine_->createRegulatoryNetwork(UniPAX::Kernel::children("PhysicalEntity", true), obj);
	mapping_engine_->addComplexAssemblies(*network, UniPAX::Kernel::children("PhysicalEntity", true), obj, true);
	mapping_engine_->addInteractions(*network, obj);
	return network;
}

UniPAX::GRAPH::ProteinProteinInteractionNetworkPtr UniPAX::DBConnector::createPPINetwork(UniPAX::ResultObject obj)
{
	UniPAX::GRAPH::ProteinProteinInteractionNetworkPtr network = mapping_engine_->createProteinProteinInteractionNetwork(obj);
	/*mapping_engine_->addComplexAssemblies(*network, UniPAX::Kernel::children("PhysicalEntity", true), obj, true);
				mapping_engine_->addInteractions(*network, UniPAX::Kernel::children("PhysicalEntity", true), obj);
				mapping_engine_->addTemplateRegulations(*network, UniPAX::Kernel::children("PhysicalEntity", true), obj);
				mapping_engine_->addControlOfBiochemicalReactions(*network, UniPAX::Kernel::children("PhysicalEntity", true), obj);*/

	return network;
}

UniPAX::UPBasePtr UniPAX::DBConnector::getObject(UnipaxId id)
{
	return engine_->getObject(id);
}

bool UniPAX::DBConnector::getObjects(std::vector<UniPAX::UPBasePtr> & result, std::vector<UnipaxId> ids)
{
	return engine_->getObjects(result, ids);
}

void UniPAX::DBConnector::getUnipaxIdsByType(std::set<UnipaxId> & result, QString type)
{
	engine_->getUnipaxIdsByType(result, type);
}

void UniPAX::DBConnector::getUnipaxIdsByName(std::map<UnipaxId, std::string> & result, QString infix)
{
	engine_->getUnipaxIdsByName(result, infix);
}

std::vector<std::string> UniPAX::DBConnector::getUnificationXrefIds(UnipaxId uid, std::string id_type)
{
	return engine_->getUnificationXrefIds(uid, id_type);
}

std::vector<std::string> UniPAX::DBConnector::getReferenceIds(std::string uid)
{
	return engine_->getReferenceIds(uid);
}

void UniPAX::DBConnector::getUnipaxIdsByXref(std::set<UnipaxId> & result, QString db, QString id)
{
	engine_->getUnipaxIdsByXref(result, db, id);
}

bool UniPAX::DBConnector::getAttributes(SERVER::Attributes & attr, UnipaxId id)
{
	bool ok = false;
	attr = engine_->getAttributes(id, ok);
	return ok;
}

void UniPAX::DBConnector::getAttributes(std::map<UnipaxId, SERVER::Attributes> & result, std::set<UnipaxId> & ids)
{
	engine_->getAttributes(result, ids);
}

bool UniPAX::DBConnector::getPathwaysOf(QByteArray& data, QString id)
{
	return engine_->getPathwaysOf(data, id);
}

bool UniPAX::DBConnector::getPathwaysOfGeneID(QByteArray& data, QString id)
{
	return engine_->getPathwaysOfGeneID(data, id);
}

bool UniPAX::DBConnector::getPathwaysOfs(QByteArray& data, QStringList& ids)
{
	return engine_->getPathwaysOfs(data, ids);
}

bool UniPAX::DBConnector::getPathwayMapOfIds(std::multimap<UnipaxId, UnipaxId>& pw_id, const std::vector<UnipaxId> ids)
{
	return engine_->getPathwayMapOfIds(pw_id, ids);
}

bool UniPAX::DBConnector::getPathwaysOfAllGeneIDs(QByteArray& data)
{
	return engine_->getPathwaysOfAllGeneIDs(data);
}

void UniPAX::DBConnector::getXrefDbs(QStringList & list)
{
	engine_->getXrefDbs(list);
}

bool UniPAX::DBConnector::query(QByteArray& data, QString sql_query)
{
	return engine_->query(data, sql_query);
}

bool UniPAX::DBConnector::mapIds(std::string sourceIdSystem, std::vector<std::string> sourceIds, std::string targetIdSystem, std::multimap<std::string, std::string> & source_targetUnipaxIds)
{
	return engine_->mapIds(sourceIdSystem, sourceIds, targetIdSystem, source_targetUnipaxIds);
}

bool UniPAX::DBConnector::isMappingSupported(std::string sourceIdSystem, std::string targetIdSystem)
{
	return engine_->isMappingSupported(sourceIdSystem, targetIdSystem);
}

UniPAX::u_map<QString, QString>::type & UniPAX::DBConnector::getOrganismMap()
{
	return engine_->getOrganismMap();
}

UniPAX::u_map<QString, QString>::type & UniPAX::DBConnector::getDataSourceMap()
{
	return engine_->getDataSourceMap();
}

void UniPAX::DBConnector::setDBCredentials(const std::string host, const int port, const std::string user, const std::string password, const std::string db)
{
	engine_->getDBManager()->setDBCredentials(user, password, host, port, db);
}

bool UniPAX::DBConnector::removeObjectsFromCache(std::vector<UnipaxId> & ids)
{
	return engine_->getDBManager()->removeObjectsFromCache(ids);
}

bool UniPAX::DBConnector::persist(PersistenceManager& manager)
{
	return engine_->getDBManager()->persist(manager);
}

bool UniPAX::DBConnector::update(PersistenceManager& manager)
{
	return engine_->getDBManager()->update(manager);
}

bool UniPAX::DBConnector::persist(UPBasePtr object)
{
	return engine_->getDBManager()->persist(object);
}

//bool persist(SampleDataBasePtr object)
//{
//	engine_->getDBManager()->
//}

bool UniPAX::DBConnector::update(UPBasePtr object)
{
	return engine_->getDBManager()->update(object);
}

bool UniPAX::DBConnector::isValid(UnipaxId id)
{
	return engine_->getDBManager()->isValid(id);
}

bool UniPAX::DBConnector::assignIds(PersistenceManager& manager)
{
	return engine_->getDBManager()->assignIds(manager);
}

bool UniPAX::DBConnector::assignId(UPBasePtr obj)
{
	return engine_->getDBManager()->assignId(obj);
}

bool UniPAX::DBConnector::listPathways(std::multimap<std::string, std::string>& pathways)
{
	return engine_->getDBManager()->listPathways(pathways);
}

bool UniPAX::DBConnector::listPathwaysById(std::map<UnipaxId, std::vector<UnipaxId> >& pathways)
{
	return engine_->getDBManager()->listPathwaysById(pathways);
}

UniPAX::PathwayPtr UniPAX::DBConnector::getPathway(std::string db_name, std::string pathway_name)
{
	return engine_->getDBManager()->getPathway(db_name, pathway_name);
}

bool UniPAX::DBConnector::initDatabase()
{
	return engine_->getDBManager()->initDatabase();
}

std::string UniPAX::DBConnector::getType(UnipaxId id, std::string defaultValue)
{
	return engine_->getDBManager()->getType(id, defaultValue);
}

bool UniPAX::DBConnector::isType(UnipaxId id, ClassType::ID type)
{
	return engine_->getDBManager()->isType(id, type);
}

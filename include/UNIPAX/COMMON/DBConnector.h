#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>
#include <UNIPAX/GRAPH/MAPPING/MappingEngine.h>
#ifdef ODB_MYSQL
#include <UNIPAX/GRAPH/MAPPING/MYSQL/MySQLMappingEngine.h>
#include <UNIPAX/SERVER/BACKEND/MYSQL/MySQLQueryEngine.h>
#elif defined ODB_ORACLE
#include <UNIPAX/GRAPH/MAPPING/ORACLE/OracleMappingEngine.h>
#include <UNIPAX/SERVER/BACKEND/ORACLE/OracleQueryEngine.h>
#endif

#include <UNIPAX/GRAPH/MAPPING/MetabolicNetwork.h>
#include <UNIPAX/KERNEL/EXT/ResultObject.h>

#include <string>

namespace UniPAX
{

class OrganismSet;
class PathwaySet;
class KernelClassSet;

class UNIPAX_EXPORT DBConnector
{
public:
	DBConnector();
/*#ifdef ODB_MYSQL
	DBConnector(UniPAX::SERVER::MySQLQueryEnginePtr engine, UniPAX::GRAPH::mysql::MySQLMappingEnginePtr mapping_engine);
#elif defined ODB_ORACLE
	DBConnector(UniPAX::SERVER::OracleQueryEnginePtr engine, UniPAX::GRAPH::oracle::OracleMappingEnginePtr mapping_engine);
#endif*/

	/**
	 * \brief Constructs a DBConnector object.
	 *
	 * \param engine Pointer to an existing SERVER::QueryEngine object.
	 * \param mapping_engine Pointer to an existing GRAPH::MappingEngine object
	 */
	DBConnector(UniPAX::SERVER::QueryEnginePtr engine, UniPAX::GRAPH::MappingEnginePtr mapping_engine);

	/**
	 * \brief Constructs a DBConnector object from another one.
	 *
	 * \param arg An existing DBConnector object.
	 */
	DBConnector(const DBConnector & arg);

	/**
	 * \brief Assignment operator.
	 *
	 * \param arg An existing DBConnector object.
	 */
	DBConnector & operator =(const DBConnector & arg);

	/**
	 * \brief Constructs a DBConnector object.
	 *
	 * \param host host name of the db server
	 * \param port port number of the db server
	 * \param user_name user name for the db connection
	 * \param passwd password for the db connection
	 * \param db_name name of the db
	 */
	DBConnector(std::string host, int port, std::string user_name, std::string passwd, std::string db_name);

	/**
	 * \brief Destructor.
	 */
	virtual ~DBConnector();

	/**
	 * \brief Returs a pointer to the internal SERVER::QueryEngine object.
	 */
	SERVER::QueryEnginePtr getEngine() const;

	/**
	 * \brief Sets the internal SERVER::QueryEngine object.
	 *
	 * \param engine Pointer to an existing SERVER::QueryEngine object.
	 */
	void setEngine(SERVER::QueryEnginePtr engine);

	/**
	 * \brief Searches for matching objects in the db.
	 *
	 * \param orgs Organisms to be included
	 * \param pathws Pathways to be included
	 * \param types UniPAX kernel class types to be included
	 */
	ResultObjectPtr query(OrganismSet orgs, PathwaySet pathws, KernelClassSet types);

	/**
	 * \brief Checks whether a ResultObject to the given query already exists.
	 *
	 * \param[out] result Pointer to the existing object. Null pointer for non-existing object.
	 * \param[in] rest_query_str Query string send to the Server.
	 *
	 * \return true if matching object exists otherwise false.
	 */
	bool resultObjectExists(ResultObjectPtr & result, QString rest_query_str);

	/**
	 * \brief Creates a MetabolicNetwork object from the given ResultObject
	 */
	UniPAX::GRAPH::MetabolicNetworkPtr createMetabolicNetwork(UniPAX::ResultObject obj);

	/**
	 * \brief Creates a RegulatoryNetwork object from the given ResultObject
	 */
	UniPAX::GRAPH::RegulatoryNetworkPtr createRegulatoryNetwork(UniPAX::ResultObject obj);

	/**
	 * \brief Creates a ProteinProteinInteractionNetwork object from the given ResultObject
	 */
	UniPAX::GRAPH::ProteinProteinInteractionNetworkPtr createPPINetwork(UniPAX::ResultObject obj);

// *******************************
// newly added from QueryEngine.h:
// *******************************

	/**
	 * \brief Returns a pointer to the object with the given id if it exists or a Null pointer.
	 */
	UnipaxPtr<UniPAX::UPBase>::type getObject(UnipaxId id);

	/**
	 * \brief Returns a vector of pointers to the objects with the given ids if they exists or Null pointers.
	 *
	 * \return true if objects are loaded from the db otherwise false.
	 */
	bool getObjects(std::vector<boost::shared_ptr<UPBase> > & result, std::vector<UnipaxId> ids);

	/**
	 * \brief Returns all ids of a given UniPAX kernel class type.
	 */
	void getUnipaxIdsByType(std::set<UnipaxId> & result, QString type);

	/**
	 * \brief Returns all <UnipaxId, full-name> pairs to a given infix of a name.
	 */
	void getUnipaxIdsByName(std::map<UnipaxId, std::string> & result, QString infix);

	/**
	 * \brief Returns all External IDs from UnificationXrefs to an internal object for a given id system.
	 */
	std::vector<std::string> getUnificationXrefIds(UnipaxId uid, std::string id_type);

	/**
	 * \brief Returns all UnipaxIds of Reference objects for a given UnipaxId, e.g., ProteinReference ids of a given Protein id.
	 */
	std::vector<std::string> getReferenceIds(std::string uid);

	/**
	 * \brief Returns all UnipaxIds of Xrefs to an internal object for a given id system.
	 */
	void getUnipaxIdsByXref(std::set<UnipaxId> & result, QString db, QString id);

	/**
	 * \brief Returns the Attributes of an object with the given UnipaxId.
	 *
	 * \sa UniPAX::SERVER::Attributes
	 *
	 * \param[in] id UnipaxId of an object.
	 * \param[out] attr Attributes retrieved.
	 *
	 * \return true if Attributes could be retrieved otherwise false.
	 */
	bool getAttributes(SERVER::Attributes & attr, UnipaxId id);

	/**
	 * \brief Returns the Attributes of objects with the given UnipaxIds.
	 *
	 * \sa UniPAX::SERVER::Attributes
	 *
	 * \param[in] ids UnipaxIds of objects.
	 * \param[out] result Attributes retrieved for the given ids.
	 */
	void getAttributes(std::map<UnipaxId, SERVER::Attributes> & result, std::set<UnipaxId> & ids);

	/**
	 * \brief Constructs an info matrix of Pathway affiliation for a given UnipaxId.
	 *        columns: unipaxId, type, standardName, displayName, organism, name_value, dataSource
	 */
	bool getPathwaysOf(QByteArray& data, QString id);

	/**
	 * \brief Constructs an info matrix of Pathway affiliation for given UnipaxIds.
	 *        columns: unipaxId, type, standardName, displayName, organism, name_value, dataSource
	 */
	bool getPathwaysOfs(QByteArray& data, QStringList& ids);

	/**
	 * \brief Constructs an info matrix of Pathway affiliation for a given EntrezGene id.
	 *        columns: unipaxId, type, standardName, displayName, organism, name_value, dataSource
	 */
	bool getPathwaysOfGeneID(QByteArray& data, QString id);

	/**
	 * \brief Constructs an info matrix of Pathway affiliation for given EntrezGene ids.
	 *        columns: unipaxId, type, standardName, displayName, organism, name_value, dataSource
	 */
	//bool getPathwaysOfGeneIDs(QByteArray& data, QStringList& ids); // not implemented in MySQLQueryEngine.cpp

	/**
	 * \brief Maps ids of Pathway objects to ids of objects belonging to those pathways.
	 */
	bool getPathwayMapOfIds(std::multimap<UnipaxId, UnipaxId>& pw_id, const std::vector<UnipaxId> ids);

	/**
	 * \brief Constructs an info matrix of Pathway affiliation for all EntrezGene ids.
	 *        columns: unipaxId, type, standardName, displayName, organism, name_value, dataSource
	 */
	bool getPathwaysOfAllGeneIDs(QByteArray& data);

	/**
	 * \brief Returns a list of all external databases (Xref.db).
	 */
	void getXrefDbs(QStringList & list);

	/**
	 * \brief Constructs an info matrix with \tab separated fields containing the result of the sql_query.
	 */
	bool query(QByteArray& data, QString sql_query);

//	bool search(QByteArray& data, const  QUrl& url, QString resultID); // This Method is erroneous.

	/**
	 * \brief Maps the given ids from sourceIdSystem to all equivalent ones in targetIdSystem.
	 */
	bool mapIds(std::string sourceIdSystem, std::vector<std::string> sourceIds, std::string targetIdSystem, std::multimap<std::string, std::string> & source_targetUnipaxIds);

	/**
	 * \brief Checks whether the mapping from sourceIdSystem to targetIdSystem is possible.
	 */
	bool isMappingSupported(std::string sourceIdSystem, std::string targetIdSystem);

	/**
	 * \brief Returns UniPAX ids and standard names for all UniPAX::BioSource objects in the database.
	 */
	UniPAX::u_map<QString, QString>::type & getOrganismMap();

	/**
	 * \brief Returns UniPAX ids and standard names for all UniPAX::Provenance objects in the database.
	 */
	UniPAX::u_map<QString, QString>::type & getDataSourceMap();

// *******************************
// newly added from DBManager.h:
// *******************************

	/**
	 * \brief Sets the login credentials for the database. This has no effect before initDatabase() is called.
	 */
	void setDBCredentials(const std::string host, const int port, const std::string user, const std::string password, const std::string db);

//	UPBasePtr getObjectByID(UnipaxId id);
	// doublet to UniPAX::UPBasePtr getObject(UnipaxId id)

//	bool getObjectsByIDs(std::vector<UPBasePtr > & result, std::vector<UnipaxId> & ids);
	// doublet to bool getObjects(std::vector<UniPAX::UPBasePtr> & result, std::vector<UnipaxId> ids)

	/**
	 * \brief Removes objects with given ids from the UniPAX odb cache.
	 */
	bool removeObjectsFromCache(std::vector<UnipaxId> & ids);

	/**
	 * \brief Persists all objects registered in the given PersistenceManager to the db.
	 */
	bool persist(PersistenceManager& manager);

	/**
	 * \brief Updates all objects registered in the given PersistenceManager in the db.
	 */
	bool update(PersistenceManager& manager);

	/**
	 * \brief Persists the given object to the db.
	 */
	bool persist(UPBasePtr object);

	/**
	 * \brief Persists the given object to the db.
	 */
//	bool persist(SampleDataBasePtr object);

	/**
	 * \brief Updates the given object in the db.
	 */
	bool update(UPBasePtr object);

	/**
	 * \brief Updates the given object in the db.
	 */
//	bool update(SampleDataBasePtr object);

	/**
	 * \brief Checks if id is an existing id in the database.
	 */
	bool isValid(UnipaxId id);

	/**
	 * \brief Assigns UnipaxIds to all objects registered in the given PersistenceManager.
	 */
	bool assignIds(PersistenceManager& manager);

	/**
	 * \brief Assigns an UnipaxId to the given object.
	 */
	bool assignId(UPBasePtr obj);

	/**
	 * \brief Assigns an UnipaxId to the given object.
	 */
//	bool assignId(SampleDataBasePtr obj);

	/**
	 * \brief Lists Provenance.name and Pathway.standardName for all Pathways in the database.
	 */
	bool listPathways(std::multimap<std::string, std::string>& pathways);

	/**
	 * \brief Lists UnipaxIds of Provenance and Pathway for all Pathways in the database.
	 */
	bool listPathwaysById(std::map<UnipaxId, std::vector<UnipaxId> >& pathways);

	/**
	 * \brief Returns pointer to Pathway object of given Provenance.name and Pathway.name.
	 */
	PathwayPtr getPathway(std::string db_name, std::string pathway_name);

//	next two methods can be resembled using getUnipaxIdsByType() & getObjects():
//	bool getObjectsByType(std::vector<UPBasePtr > & result, std::string type, bool recursive = false);
//	bool getIdsByType(std::vector<UnipaxId> & result, std::string type, bool recursive = false);

	/**
	 * \brief Initializes the database with the credentials set by setDBCredentials(...)
	 */
	bool initDatabase();
//	next two methods are available via getEngine()->getDBManager():
//	UnipaxPtr<odb::database>::type getOdbDatabase();
//
//	UnipaxPtr<ODBWorker>::type getOdbWorker();

	/**
	 * \brief Returns the type of the object with the given UnipaxId. If not available, defaultValue is returned instead.
	 */
	std::string getType(UnipaxId id, std::string defaultValue);

	/**
	 * \brief Returns true if the type of the object with the given UnipaxId equals type otherwise false.
	 */
	bool isType(UnipaxId id, ClassType::ID type);

private:
	SERVER::QueryEnginePtr engine_;
	UniPAX::GRAPH::MappingEnginePtr mapping_engine_;
	//UnipaxPtr<UniPAX::PersistenceManager>::type manager_;

	class QueryPredicate
	{

		public:
    	bool operator () (const std::pair<int, QString>& a, const std::pair<int, QString>& b)
			{
	        return a.first < b.first;
			}
	};

};

typedef UnipaxPtr<DBConnector>::type DBConnectorPtr;

} // end namespace
#endif // DBCONNECTOR_H

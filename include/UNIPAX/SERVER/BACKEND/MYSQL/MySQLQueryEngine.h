#ifndef MYSQLQUERYENGINE_H
#define MYSQLQUERYENGINE_H


#include<UNIPAX/SERVER/BACKEND/QueryEngine.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/KernelCollector.h>
#include<UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>

#include<UNIPAX/KERNEL/BIOPAX/Protein.h>
#include<UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Protein-odb.hxx>

#include<memory>
#include<odb/database.hxx>
#include<odb/query.hxx>
#include<odb/result.hxx>
#include<odb/session.hxx>

#include <UNIPAX/COMMON/u_map.h>

#include<QtCore>


namespace UniPAX
{


namespace SERVER
{


class UNIPAX_EXPORT MySQLQueryEngine : public QueryEngine
{


public:
	MySQLQueryEngine(bool cached = true);
	virtual ~MySQLQueryEngine();

	UnipaxPtr<UniPAX::DBManager>::type getDBManager();

	void createResultSetTables();

	void checkIndexes();
	void rebuildAttributeIndex();
	void rebuildNameIndex();
	void rebuildPathwayIndex();
	void rebuildIdMapping();

//	bool getAttributes(UnipaxId id, const std::vector<QString> & attributes, std::vector<QString> & result );
//	bool getAttributesForType(QString type, const std::vector<QString> & attributes, std::map<UnipaxId, std::vector<QString> > & result, bool derived = false );

	UnipaxPtr<UPBase>::type getObject(UnipaxId id);

	bool getObjects(std::vector<boost::shared_ptr<UPBase> > & result, std::vector<UnipaxId> ids);

	//bool getObjectsByType(QByteArray& data, QString type);

	//bool getObjectsByName(QByteArray& data, QString expression);

	void getUnipaxIdsByType(std::set<UnipaxId> & result, QString type);
	void getUnipaxIdsByName(std::map<UnipaxId, std::string> & result, QString name);
	std::vector<std::string> getUnificationXrefIds(UnipaxId uid, std::string id_type);
	std::vector<std::string> getReferenceIds(std::string uid);
	void getUnipaxIdsByXref(std::set<UnipaxId> & result, QString db, QString id);
	void getAttributes(std::map<UnipaxId, Attributes> & result, std::set<UnipaxId> & ids);
	Attributes getAttributes(UnipaxId id, bool & ok = QueryEngine::unused_value);

//	bool getIDsByName(QByteArray& data, QString expression);
//	bool getIDsByType(QByteArray& data, QString type);
//	bool getIDsByXref(QByteArray& data, QString db, QString id);

	bool getPathwaysOf(QByteArray& data, QString id);
	bool getPathwaysOfGeneID(QByteArray& data, QString id);
	bool getPathwaysOfAllGeneIDs(QByteArray& data);
	bool getPathwayMapOfIds(std::multimap<UnipaxId, UnipaxId>& pw_id, const std::vector<UnipaxId> ids);


	bool getPathwaysOfs(QByteArray& data, QStringList& ids);
	bool getPathwaysOfGeneIDs(QByteArray& data, QStringList& ids);

  	void getXrefDbs(QStringList & list);

	bool search(QByteArray& data, const  QUrl& url, QString resultID);
  	
	bool query(QByteArray& data, QString sql_query);
	bool mapIds(std::string sourceIdSystem, std::vector<std::string> sourceIds, std::string targetIdSystem, std::multimap<std::string, std::string> & source_targetUnipaxIds);
	bool isMappingSupported(std::string sourceIdSystem, std::string targetIdSystem);

	bool checkDatabaseConnection();

	UniPAX::u_map<QString, QString>::type & getOrganismMap();

	UniPAX::u_map<QString, QString>::type & getDataSourceMap();

private:

	QSqlQuery exec(QSqlDatabase* db, QString qstring, QString error);

	void exec(QSqlQuery& query, QString error);

	UnipaxPtr<UniPAX::mysql::MySQLManager>::type manager;
	UniPAX::u_map<QString, QSqlQuery*>::type preparedQueries;
	UniPAX::u_map<QString, QString>::type org_map;
	UniPAX::u_map<QString, QString>::type datasource_map;
	UniPAX::u_map<QString, QString>::type datasource_version_map;
	UniPAX::u_map<QString, QString>::type datasource_date_map;
	UniPAX::u_map<UnipaxId, UniPAX::u_map<QString, QString>::type* >::type attributes_cache;

	UniPAX::u_map<UnipaxId, UniPAX::SERVER::Attributes>::type attributes_map;

};

typedef UnipaxPtr<MySQLQueryEngine>::type MySQLQueryEnginePtr;

}
}


#endif /* MYSQLQUERYENGINE_H */

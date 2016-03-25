#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/COMMON/KernelCollector.h>
#include <UNIPAX/COMMON/u_map.h>

#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Protein-odb.hxx>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Protein-odb.hxx>
#endif

#include <UNIPAX/KERNEL/BIOPAX/Protein.h>

#include <odb/database.hxx>
#include <odb/query.hxx>
#include <odb/result.hxx>
#include <odb/session.hxx>



#include <QtCore>

#include <memory>
#include <map>
#include <vector>
#include <string>

namespace UniPAX
{


namespace SERVER
{

struct Attributes
{
	UnipaxId id;
	QString type;
	QString standardName;
	QString displayName;
	UnipaxId organism;
	UnipaxId dataSource;
	QString dataSourceVersion;
	QString dataSourceDate;
	QString entityModification;
};


class UNIPAX_EXPORT QueryEngine
{

public:
	QueryEngine();
	virtual ~QueryEngine();

	virtual UnipaxPtr<UniPAX::DBManager>::type getDBManager() = 0;

	virtual void createResultSetTables() = 0;

	virtual void checkIndexes() = 0;

	void rebuildAllIndexes();

	virtual void rebuildAttributeIndex() = 0;
	virtual void rebuildNameIndex() = 0;
	virtual void rebuildPathwayIndex() = 0;
	virtual void rebuildIdMapping() = 0;

//	virtual bool getAttributes(UnipaxId id, const std::vector<QString> & attributes, std::vector<QString> & result ) = 0;
//	virtual bool getAttributesForType(QString type, const std::vector<QString> & attributes, std::map<UnipaxId, std::vector<QString> > & result, bool derived = false ) = 0;

	virtual UnipaxPtr<UniPAX::UPBase>::type getObject(UnipaxId id) = 0;

	virtual bool getObjects(std::vector<boost::shared_ptr<UPBase> > & result, std::vector<UnipaxId> ids) = 0;

	//virtual bool getObjectsByType(QByteArray& data, QString type) = 0;


	virtual void getUnipaxIdsByType(std::set<UnipaxId> & result, QString type) = 0;
	virtual void getUnipaxIdsByName(std::map<UnipaxId, std::string> & result, QString name) = 0;
	virtual std::vector<std::string> getUnificationXrefIds(UnipaxId uid, std::string id_type) = 0;
	virtual std::vector<std::string> getReferenceIds(std::string uid) = 0;
	virtual void getUnipaxIdsByXref(std::set<UnipaxId> & result, QString db, QString id) = 0;

	virtual Attributes getAttributes(UnipaxId id, bool & ok = unused_value) = 0;
	virtual void getAttributes(std::map<UnipaxId, Attributes> & result, std::set<UnipaxId> & ids) = 0;

//	virtual bool getIDsByName(QByteArray& data, QString expression) = 0;

//	virtual bool getIDsByType(QByteArray& data, QString type) = 0;

//	virtual bool getIDsByXref(QByteArray& data, QString db, QString id) = 0;

	virtual bool getPathwaysOf(QByteArray& data, QString id) = 0;

	virtual bool getPathwaysOfGeneID(QByteArray& data, QString id) = 0;

	virtual bool getPathwaysOfs(QByteArray& data, QStringList& ids) = 0;

	virtual bool getPathwaysOfGeneIDs(QByteArray& data, QStringList& ids) = 0;

	virtual bool getPathwayMapOfIds(std::multimap<UnipaxId, UnipaxId>& pw_id, const std::vector<UnipaxId> ids) = 0;

	virtual bool getPathwaysOfAllGeneIDs(QByteArray& data) = 0;

	virtual void getXrefDbs(QStringList & list) = 0;

    virtual bool query(QByteArray& data, QString sql_query) = 0;

	virtual bool search(QByteArray& data, const  QUrl& url, QString resultID) = 0;

	/**
	 * Maps Ids from the source id system to UniPAX objects that have the corresponding mapped ids in the target system.
	 */
	virtual bool mapIds(std::string sourceIdSystem, std::vector<std::string> sourceIds, std::string targetIdSystem, std::multimap<std::string, std::string> & source_targetUnipaxIds) = 0;

	virtual bool isMappingSupported(std::string sourceIdSystem, std::string targetIdSystem) = 0;

	virtual UniPAX::u_map<QString, QString>::type & getOrganismMap() = 0;

	virtual UniPAX::u_map<QString, QString>::type & getDataSourceMap() = 0;

protected:
	static bool unused_value;

private:

	odb::core::session session;

};

typedef UnipaxPtr<QueryEngine>::type QueryEnginePtr;

}
}


#endif /* QUERYENGINE_H */

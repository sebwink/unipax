#ifndef ORACLEQUERYENGINE_H
#define ORACLEQUERYENGINE_H


#include<UNIPAX/SERVER/BACKEND/QueryEngine.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/KernelCollector.h>
#include<UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>

#include<UNIPAX/KERNEL/BIOPAX/Protein.h>
#include<UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Protein-odb.hxx>

#include<memory>
#include<odb/database.hxx>
#include<odb/query.hxx>
#include<odb/result.hxx>
#include<odb/session.hxx>

#include<QtCore>


namespace UniPAX
{


namespace SERVER
{


class UNIPAX_EXPORT OracleQueryEngine : public QueryEngine
{


public:
	OracleQueryEngine();
	virtual ~OracleQueryEngine();

	boost::shared_ptr<UniPAX::DBManager> getDBManager();

	void createResultSetTables();

	void checkIndexes();
	void rebuildAttributeIndex();
	void rebuildNameIndex();
	void rebuildPathwayIndex();

	bool getAttributes(UnipaxId id, const std::vector<QString> & attributes, std::vector<QString> & result );
	bool getAttributesForType(QString type, const std::vector<QString> & attributes, std::map<UnipaxId, std::vector<QString> > & result, bool derived = false );

	boost::shared_ptr<UPBase> getObject(UnipaxId id);

	bool getObjects(std::vector<boost::shared_ptr<UPBase> > & result, std::vector<UnipaxId> ids);

	bool getObjectsByType(QByteArray& data, QString type);

	//bool getObjectsByName(QByteArray& data, QString expression);
	bool getIDsByName(QByteArray& data, QString expression);
	bool getIDsByType(QByteArray& data, QString type);


	bool getPathwaysOf(QByteArray& data, QString id);
	bool getPathwaysOfGeneID(QByteArray& data, QString id);
	bool getPathwaysOfAllGeneIDs(QByteArray& data);

	bool search(QByteArray& data, const  QUrl& url, QString resultID);

	bool checkDatabaseConnection();

private:

	boost::shared_ptr<UniPAX::oracle::OracleManager> manager;

};

}
}


#endif /* ORACLEQUERYENGINE_H */

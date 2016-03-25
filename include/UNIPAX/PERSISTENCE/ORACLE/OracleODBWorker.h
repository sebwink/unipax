#ifndef ORACLEODBWORKER_H
#define ORACLEODBWORKER_H

#include<UNIPAX/COMMON/common.h>

#include<UNIPAX/PERSISTENCE/ODBRunnable.h>
#include<UNIPAX/PERSISTENCE/ODBWorker.h>
#include<UNIPAX/PERSISTENCE/ORACLE/all.h>

#include<UNIPAX/PERSISTENCE/ORACLE/OracleODBLoadRunnable.h>
#include<UNIPAX/PERSISTENCE/ORACLE/OracleODBUpdateRunnable.h>
#include<UNIPAX/PERSISTENCE/ORACLE/OracleODBPersistRunnable.h>

#include<UNIPAX/KERNEL/EXT/UPBase.h>

#include<queue>
#include<odb/database.hxx>
#include<odb/oracle/database.hxx>

#include<QtCore>


namespace UniPAX
{

namespace oracle
{

class UNIPAX_EXPORT OracleODBWorker : public ODBWorker
{
	Q_OBJECT

public:
	OracleODBWorker(boost::shared_ptr<odb::database> _database);

	~OracleODBWorker();

protected:

    boost::shared_ptr<ODBLoadRunnable> createLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & ids);

    boost::shared_ptr<ODBUpdateRunnable> createUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> object);

	boost::shared_ptr<ODBUpdateRunnable> createUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects);

	boost::shared_ptr<ODBPersistRunnable> createPersistRunnable(boost::shared_ptr<UniPAX::UPBase> object);

	boost::shared_ptr<ODBPersistRunnable> createPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects);

private:
	typedef ODBWorker super;
};

}

}

#endif

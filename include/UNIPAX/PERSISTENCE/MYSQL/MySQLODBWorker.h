#ifndef MYSQLODBWORKER_H
#define MYSQLODBWORKER_H

#include<UNIPAX/COMMON/common.h>

#include<UNIPAX/PERSISTENCE/ODBRunnable.h>
#include<UNIPAX/PERSISTENCE/ODBWorker.h>
#include<UNIPAX/PERSISTENCE/MYSQL/all.h>

#include<UNIPAX/PERSISTENCE/MYSQL/MySQLODBLoadRunnable.h>
#include<UNIPAX/PERSISTENCE/MYSQL/MySQLODBUnloadRunnable.h>
#include<UNIPAX/PERSISTENCE/MYSQL/MySQLODBUpdateRunnable.h>
#include<UNIPAX/PERSISTENCE/MYSQL/MySQLODBPersistRunnable.h>

#include<UNIPAX/KERNEL/EXT/UPBase.h>

#include<queue>
#include<odb/database.hxx>
#include<odb/mysql/database.hxx>

#include<QtCore>


namespace UniPAX
{

namespace mysql
{

class UNIPAX_EXPORT MySQLODBWorker : public ODBWorker
{
	Q_OBJECT

public:
	MySQLODBWorker(boost::shared_ptr<odb::database> _database, bool cached = true);

	~MySQLODBWorker();

protected:

    boost::shared_ptr<ODBLoadRunnable> createLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & ids);

	boost::shared_ptr<ODBUnloadRunnable> createUnloadRunnable(std::vector<UnipaxId> & ids);

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

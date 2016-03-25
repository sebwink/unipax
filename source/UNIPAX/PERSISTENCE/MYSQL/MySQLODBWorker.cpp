#include <UNIPAX/PERSISTENCE/MYSQL/MySQLODBWorker.h>


UniPAX::mysql::MySQLODBWorker::MySQLODBWorker(boost::shared_ptr<odb::database> _database, bool cached) : UniPAX::ODBWorker(_database, cached)
{
}

UniPAX::mysql::MySQLODBWorker::~MySQLODBWorker()
{
}

boost::shared_ptr<UniPAX::ODBLoadRunnable> UniPAX::mysql::MySQLODBWorker::createLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & ids)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBLoadRunnable>(boost::shared_ptr<UniPAX::mysql::MySQLODBLoadRunnable>(new UniPAX::mysql::MySQLODBLoadRunnable(result, ids)));
}

boost::shared_ptr<UniPAX::ODBUnloadRunnable> UniPAX::mysql::MySQLODBWorker::createUnloadRunnable(std::vector<UnipaxId> & ids)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBUnloadRunnable>(boost::shared_ptr<UniPAX::mysql::MySQLODBUnloadRunnable>(new UniPAX::mysql::MySQLODBUnloadRunnable(ids)));
}

boost::shared_ptr<UniPAX::ODBUpdateRunnable> UniPAX::mysql::MySQLODBWorker::createUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> object)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBUpdateRunnable>(boost::shared_ptr<UniPAX::mysql::MySQLODBUpdateRunnable>(new UniPAX::mysql::MySQLODBUpdateRunnable(object)));
}

boost::shared_ptr<UniPAX::ODBUpdateRunnable> UniPAX::mysql::MySQLODBWorker::createUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBUpdateRunnable>(boost::shared_ptr<UniPAX::mysql::MySQLODBUpdateRunnable>(new UniPAX::mysql::MySQLODBUpdateRunnable(objects)));
}

boost::shared_ptr<UniPAX::ODBPersistRunnable> UniPAX::mysql::MySQLODBWorker::createPersistRunnable(boost::shared_ptr<UniPAX::UPBase> object)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBPersistRunnable>(boost::shared_ptr<UniPAX::mysql::MySQLODBPersistRunnable>(new UniPAX::mysql::MySQLODBPersistRunnable(object)));
}

boost::shared_ptr<UniPAX::ODBPersistRunnable> UniPAX::mysql::MySQLODBWorker::createPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBPersistRunnable>(boost::shared_ptr<UniPAX::mysql::MySQLODBPersistRunnable>(new UniPAX::mysql::MySQLODBPersistRunnable(objects)));
}




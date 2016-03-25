#include <UNIPAX/PERSISTENCE/ORACLE/OracleODBWorker.h>


UniPAX::oracle::OracleODBWorker::OracleODBWorker(boost::shared_ptr<odb::database> _database) : UniPAX::ODBWorker(_database)
{
}

UniPAX::oracle::OracleODBWorker::~OracleODBWorker()
{
}

boost::shared_ptr<UniPAX::ODBLoadRunnable> UniPAX::oracle::OracleODBWorker::createLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & ids)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBLoadRunnable>(boost::shared_ptr<UniPAX::oracle::OracleODBLoadRunnable>(new UniPAX::oracle::OracleODBLoadRunnable(result, ids)));
}

boost::shared_ptr<UniPAX::ODBUpdateRunnable> UniPAX::oracle::OracleODBWorker::createUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> object)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBUpdateRunnable>(boost::shared_ptr<UniPAX::oracle::OracleODBUpdateRunnable>(new UniPAX::oracle::OracleODBUpdateRunnable(object)));
}

boost::shared_ptr<UniPAX::ODBUpdateRunnable> UniPAX::oracle::OracleODBWorker::createUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBUpdateRunnable>(boost::shared_ptr<UniPAX::oracle::OracleODBUpdateRunnable>(new UniPAX::oracle::OracleODBUpdateRunnable(objects)));
}

boost::shared_ptr<UniPAX::ODBPersistRunnable> UniPAX::oracle::OracleODBWorker::createPersistRunnable(boost::shared_ptr<UniPAX::UPBase> object)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBPersistRunnable>(boost::shared_ptr<UniPAX::oracle::OracleODBPersistRunnable>(new UniPAX::oracle::OracleODBPersistRunnable(object)));
}

boost::shared_ptr<UniPAX::ODBPersistRunnable> UniPAX::oracle::OracleODBWorker::createPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects)
{
	return boost::dynamic_pointer_cast<UniPAX::ODBPersistRunnable>(boost::shared_ptr<UniPAX::oracle::OracleODBPersistRunnable>(new UniPAX::oracle::OracleODBPersistRunnable(objects)));
}




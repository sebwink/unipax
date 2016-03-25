#ifndef ODBWORKER_H
#define ODBWORKER_H

#include<UNIPAX/COMMON/common.h>

#include<UNIPAX/PERSISTENCE/ODBRunnable.h>
#include<UNIPAX/PERSISTENCE/ODBLoadRunnable.h>
#include<UNIPAX/PERSISTENCE/ODBUnloadRunnable.h>
#include<UNIPAX/PERSISTENCE/ODBUpdateRunnable.h>
#include<UNIPAX/PERSISTENCE/ODBPersistRunnable.h>

#include<UNIPAX/KERNEL/EXT/UPBase.h>

#include<queue>
#include<odb/database.hxx>

#include<QtCore>

#include <limits.h>


namespace UniPAX
{

class UNIPAX_EXPORT UncachedSession : public odb::session
{
public:
	template <typename T>
	odb::session::cache_position<T> cache_insert (odb::database&,
			const typename odb::object_traits<T>::id_type&,
			const typename odb::object_traits<T>::pointer_type&)
			{ return odb::session::cache_position<T>(); }
};

class UNIPAX_EXPORT ODBWorker : public QThread
{

	Q_OBJECT

public:

	ODBWorker(boost::shared_ptr<odb::database> _database, bool caching = true);

	virtual ~ODBWorker();

	boost::shared_ptr<UniPAX::UPBase> load(UnipaxId id);

	void unload(std::vector<UnipaxId> & ids);

	void load(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & ids);

	bool update(boost::shared_ptr<UniPAX::UPBase> object);

	std::vector<bool> update(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects);

	UnipaxId persist(boost::shared_ptr<UniPAX::UPBase> object);

	std::vector<UnipaxId> persist(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects);

	void stop();

protected:

	virtual void run();

	virtual boost::shared_ptr<ODBLoadRunnable> createLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & ids);

	virtual boost::shared_ptr<ODBUnloadRunnable> createUnloadRunnable(std::vector<UnipaxId> & ids);

	virtual boost::shared_ptr<ODBUpdateRunnable> createUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> object);

	virtual boost::shared_ptr<ODBUpdateRunnable> createUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects);

	virtual boost::shared_ptr<ODBPersistRunnable> createPersistRunnable(boost::shared_ptr<UniPAX::UPBase> object);

	virtual boost::shared_ptr<ODBPersistRunnable> createPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > ids);


private:
	bool stopped;
	bool caching;

	boost::shared_ptr<odb::database> database;

	QReadWriteLock lock;

	QWaitCondition wait;
	QMutex mutex;

	std::queue<boost::shared_ptr<ODBRunnable> > queue;

};

}

#endif

#include <UNIPAX/PERSISTENCE/ODBWorker.h>
#include <odb/session.hxx>

UniPAX::ODBWorker::ODBWorker(boost::shared_ptr<odb::database> _database, bool cache) : database(_database), stopped(false), caching(cache)
{
	start();
}

UniPAX::ODBWorker::~ODBWorker()
{
	if (isRunning())
		stop();
}

void UniPAX::ODBWorker::run() {
	boost::shared_ptr<odb::session> session;
	if (caching)
	{
			session.reset(new odb::session());
	}
	else
	{
			session.reset(new UniPAX::UncachedSession());
	}

	std::cerr << "Started ODB worker thread." << std::endl;

	while (!stopped) {
		lock.lockForRead();
		if (!queue.empty()) {
			lock.unlock();

			lock.lockForWrite();
			boost::shared_ptr<ODBRunnable> runnable = queue.front();
			queue.pop();
			lock.unlock();

			runnable->run(session, database);
			runnable->done();
		} else {
			lock.unlock();

			// wait for event
			mutex.lock();
			wait.wait(&mutex, 500);
			mutex.unlock();
		}
	}

	std::cerr << "stopped." << std::endl;
}

void UniPAX::ODBWorker::stop() {

	if (this->isFinished())
		return;

	std::cerr << "Stopping ODB worker thread..." << std::flush;

	stopped = true;
	wait.wakeAll();

	QThread::wait();
}

boost::shared_ptr<UniPAX::UPBase> UniPAX::ODBWorker::load(UnipaxId id)
{
	std::vector<boost::shared_ptr<UniPAX::UPBase> > v;
	std::vector<UnipaxId> ids;
	ids.push_back(id);

	boost::shared_ptr<ODBLoadRunnable> runnable(createLoadRunnable(v, ids));

	lock.lockForWrite();
	queue.push(runnable);
	lock.unlock();

	wait.wakeAll();

	while (!runnable->isProcessed())
	{
		runnable->waitFor();
	}

	if (!v.empty())
		return v[0];
	else
		return boost::shared_ptr<UniPAX::UPBase>();
}

void UniPAX::ODBWorker::load(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & ids)
{

	boost::shared_ptr<ODBLoadRunnable> runnable(createLoadRunnable(result, ids));
	lock.lockForWrite();
	queue.push(runnable);
	lock.unlock();

	wait.wakeAll();

	while (!runnable->isProcessed())
	{
		runnable->waitFor();
	}
}

void UniPAX::ODBWorker::unload(std::vector<UnipaxId> & ids)
{

	boost::shared_ptr<ODBUnloadRunnable> runnable(createUnloadRunnable(ids));
	lock.lockForWrite();
	queue.push(runnable);
	lock.unlock();

	wait.wakeAll();

	while (!runnable->isProcessed())
	{
		runnable->waitFor();
	}
}

bool UniPAX::ODBWorker::update(boost::shared_ptr<UniPAX::UPBase> object)
{

	boost::shared_ptr<ODBUpdateRunnable> runnable(createUpdateRunnable(object));
	lock.lockForWrite();
	queue.push(runnable);
	lock.unlock();

	wait.wakeAll();

	while (!runnable->isProcessed())
	{
		runnable->waitFor();
	}

	return runnable->getSuccessful()[0];

}

std::vector<bool> UniPAX::ODBWorker::update(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects)
{

	boost::shared_ptr<ODBUpdateRunnable> runnable(createUpdateRunnable(objects));
	lock.lockForWrite();
	queue.push(runnable);
	lock.unlock();

	wait.wakeAll();

	while (!runnable->isProcessed())
	{
		runnable->waitFor();
	}

	return runnable->getSuccessful();

}

UnipaxId UniPAX::ODBWorker::persist(boost::shared_ptr<UniPAX::UPBase> object)
{

	boost::shared_ptr<ODBPersistRunnable> runnable(createPersistRunnable(object));
	lock.lockForWrite();
	queue.push(runnable);
	lock.unlock();

	wait.wakeAll();

	while (!runnable->isProcessed())
	{
		runnable->waitFor();
	}

	return runnable->getIds()[0];

}

std::vector<UnipaxId> UniPAX::ODBWorker::persist(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects)
{

	boost::shared_ptr<ODBPersistRunnable> runnable(createPersistRunnable(objects));
	lock.lockForWrite();
	queue.push(runnable);
	lock.unlock();

	wait.wakeAll();

	while (!runnable->isProcessed())
	{
		runnable->waitFor();
	}

	return runnable->getIds();

}

boost::shared_ptr<UniPAX::ODBLoadRunnable> UniPAX::ODBWorker::createLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & ids)
{
	return boost::shared_ptr<UniPAX::ODBLoadRunnable>(new ODBLoadRunnable(result, ids));
}

boost::shared_ptr<UniPAX::ODBUnloadRunnable> UniPAX::ODBWorker::createUnloadRunnable(std::vector<UnipaxId> & ids)
{
	return boost::shared_ptr<UniPAX::ODBUnloadRunnable>(new ODBUnloadRunnable(ids));
}

boost::shared_ptr<UniPAX::ODBUpdateRunnable> UniPAX::ODBWorker::createUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> object)
{
	return boost::shared_ptr<UniPAX::ODBUpdateRunnable>(new ODBUpdateRunnable(object));
}

boost::shared_ptr<UniPAX::ODBUpdateRunnable> UniPAX::ODBWorker::createUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects)
{
	return boost::shared_ptr<UniPAX::ODBUpdateRunnable>(new ODBUpdateRunnable(objects));
}

boost::shared_ptr<UniPAX::ODBPersistRunnable> UniPAX::ODBWorker::createPersistRunnable(boost::shared_ptr<UniPAX::UPBase> object)
{
	return boost::shared_ptr<UniPAX::ODBPersistRunnable>(new ODBPersistRunnable(object));
}

boost::shared_ptr<UniPAX::ODBPersistRunnable> UniPAX::ODBWorker::createPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects)
{
	return boost::shared_ptr<UniPAX::ODBPersistRunnable>(new ODBPersistRunnable(objects));
}




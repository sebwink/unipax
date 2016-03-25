/*
 * ODBRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef ODBRUNNABLE_H_
#define ODBRUNNABLE_H_


#include <UNIPAX/COMMON/common.h>

//#include <UNIPAX/KERNEL/all.h>

#include <boost/shared_ptr.hpp>
#include <odb/database.hxx>

#include <QtCore>

namespace UniPAX
{

class UNIPAX_EXPORT ODBRunnable {

	friend class ODBWorker;

public:

	ODBRunnable();

	virtual ~ODBRunnable() { };

	virtual void run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database) { };

	bool isProcessed() { return processed; };

	void waitFor() {
		if (processed)
			return;

		_mutex.lock();
		_wait.wait(&_mutex);
		_mutex.unlock();
	}

protected:

	bool processed;

private:

	void done() {
		processed = true;

		_mutex.lock();
		_wait.wakeAll();
		_mutex.unlock();

	}

	QWaitCondition _wait;
	QMutex _mutex;
};

}


#endif /* ODBRUNNABLE_H_ */

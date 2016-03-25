/*
 * UnloadRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef MYSQLODBUNLOADRUNNABLE_H_
#define MYSQLODBUNLOADRUNNABLE_H_

#include <UNIPAX/COMMON/common.h>

#include <UNIPAX/PERSISTENCE/ODBUnloadRunnable.h>
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLODBWorker.h>

#include <odb/traits.hxx>
#include <odb/database.hxx>
#include <odb/mysql/database.hxx>
#include <odb/transaction.hxx>
#include <odb/session.hxx>


#include <boost/shared_ptr.hpp>
#include <vector>

namespace UniPAX
{

namespace mysql
{

class UNIPAX_EXPORT MySQLODBUnloadRunnable : public ODBUnloadRunnable
{

public:
	MySQLODBUnloadRunnable(std::vector<UnipaxId> & _ids);

	~MySQLODBUnloadRunnable();

	void run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database);

private:
	typedef ODBUnloadRunnable super;

};

}

}


#endif /* MYSQLODBUNLOADRUNNABLE_H_ */

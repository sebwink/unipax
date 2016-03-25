/*
 * LoadRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef MYSQLODBPERSISTRUNNABLE_H_
#define MYSQLODBPERSISTRUNNABLE_H_

#include <UNIPAX/COMMON/common.h>

#include <UNIPAX/PERSISTENCE/ODBPersistRunnable.h>
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLODBWorker.h>

#include <odb/traits.hxx>
#include <odb/database.hxx>
#include <odb/mysql/database.hxx>
#include <odb/transaction.hxx>


#include <boost/shared_ptr.hpp>
#include <vector>

namespace UniPAX
{

namespace mysql
{

class UNIPAX_EXPORT MySQLODBPersistRunnable : public ODBPersistRunnable
{

public:
	MySQLODBPersistRunnable(boost::shared_ptr<UniPAX::UPBase> _object);

	MySQLODBPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects);

	~MySQLODBPersistRunnable();

	void run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database);

private:
	typedef ODBPersistRunnable super;

};

}

}


#endif /* MYSQLODBPERSISTRUNNABLE_H_ */

/*
 * LoadRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef MYSQLODBUPDATERUNNABLE_H_
#define MYSQLODBUPDATERUNNABLE_H_

#include <UNIPAX/COMMON/common.h>

#include <UNIPAX/PERSISTENCE/ODBUpdateRunnable.h>
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

class UNIPAX_EXPORT MySQLODBUpdateRunnable : public ODBUpdateRunnable
{

public:
	MySQLODBUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> _object);

	MySQLODBUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects);

	~MySQLODBUpdateRunnable();

	void run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database);

private:
	typedef ODBUpdateRunnable super;

};

}

}


#endif /* MYSQLODBUPDATERUNNABLE_H_ */

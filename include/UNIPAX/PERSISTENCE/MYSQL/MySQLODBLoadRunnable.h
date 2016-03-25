/*
 * LoadRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef MYSQLODBLOADRUNNABLE_H_
#define MYSQLODBLOADRUNNABLE_H_

#include <UNIPAX/COMMON/common.h>

#include <UNIPAX/PERSISTENCE/ODBLoadRunnable.h>
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

class UNIPAX_EXPORT MySQLODBLoadRunnable : public ODBLoadRunnable
{

public:
	MySQLODBLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & _ids);

	~MySQLODBLoadRunnable();

	void run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database);

private:
	typedef ODBLoadRunnable super;

};

}

}


#endif /* MYSQLODBLOADRUNNABLE_H_ */

/*
 * LoadRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef ORACLEODBPERSISTRUNNABLE_H_
#define ORACLEODBPERSISTRUNNABLE_H_

#include <UNIPAX/COMMON/common.h>

#include <UNIPAX/PERSISTENCE/ODBPersistRunnable.h>
#include <UNIPAX/PERSISTENCE/ORACLE/OracleODBWorker.h>

#include <odb/traits.hxx>
#include <odb/database.hxx>
#include <odb/oracle/database.hxx>
#include <odb/transaction.hxx>


#include <boost/shared_ptr.hpp>
#include <vector>

namespace UniPAX
{

namespace oracle
{

class UNIPAX_EXPORT OracleODBPersistRunnable : public ODBPersistRunnable
{

public:
	OracleODBPersistRunnable(boost::shared_ptr<UniPAX::UPBase> _object);

	OracleODBPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects);

	~OracleODBPersistRunnable();

	void run(boost::shared_ptr<odb::database> database);

private:
	typedef ODBPersistRunnable super;

};

}

}


#endif /* ORACLEODBPERSISTRUNNABLE_H_ */

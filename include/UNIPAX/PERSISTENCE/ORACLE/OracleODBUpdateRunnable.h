/*
 * LoadRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef ORACLEODBUPDATERUNNABLE_H_
#define ORACLEODBUPDATERUNNABLE_H_

#include <UNIPAX/COMMON/common.h>

#include <UNIPAX/PERSISTENCE/ODBUpdateRunnable.h>
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

class UNIPAX_EXPORT OracleODBUpdateRunnable : public ODBUpdateRunnable
{

public:
	OracleODBUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> _object);

	OracleODBUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects);

	~OracleODBUpdateRunnable();

	void run(boost::shared_ptr<odb::database> database);

private:
	typedef ODBUpdateRunnable super;

};

}

}


#endif /* ORACLEODBUPDATERUNNABLE_H_ */

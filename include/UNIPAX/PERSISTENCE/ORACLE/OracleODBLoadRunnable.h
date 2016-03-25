/*
 * LoadRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef ORACLEODBLOADRUNNABLE_H_
#define ORACLEODBLOADRUNNABLE_H_

#include <UNIPAX/COMMON/common.h>

#include <UNIPAX/PERSISTENCE/ODBLoadRunnable.h>
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

class UNIPAX_EXPORT OracleODBLoadRunnable : public ODBLoadRunnable
{

public:
	OracleODBLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & _ids);

	~OracleODBLoadRunnable();

	void run(boost::shared_ptr<odb::database> database);

private:
	typedef ODBLoadRunnable super;

};

}

}


#endif /* ORACLEODBLOADRUNNABLE_H_ */

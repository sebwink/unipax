/*
 * UnloadRunnable.h
 *
 *  Created on: Oct 14, 2013
 *      Author: niermann
 */

#ifndef ODBUNLOADRUNNABLE_H_
#define ODBUNLOADRUNNABLE_H_

#include<UNIPAX/COMMON/common.h>

#include<UNIPAX/PERSISTENCE/ODBRunnable.h>

#include<UNIPAX/KERNEL/EXT/UPBase.h>

#include <odb/traits.hxx>
#include<odb/database.hxx>
#include<odb/transaction.hxx>
#include <odb/session.hxx>
#include<vector>

namespace UniPAX
{

class UNIPAX_EXPORT ODBUnloadRunnable : public ODBRunnable
{

public:
	ODBUnloadRunnable(std::vector<UnipaxId> & _ids);

	virtual ~ODBUnloadRunnable() { };

	virtual void run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database);

protected:

	std::vector<UnipaxId> & ids;

private:
	typedef ODBRunnable super;

};

}


#endif /* ODBUNLOADRUNNABLE_H_ */

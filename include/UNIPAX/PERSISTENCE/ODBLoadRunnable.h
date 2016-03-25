/*
 * LoadRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef ODBLOADRUNNABLE_H_
#define ODBLOADRUNNABLE_H_

#include<UNIPAX/COMMON/common.h>

#include<UNIPAX/PERSISTENCE/ODBRunnable.h>

#include<boost/shared_ptr.hpp>

#include<UNIPAX/KERNEL/EXT/UPBase.h>

#include <odb/traits.hxx>
#include<odb/database.hxx>
#include<odb/transaction.hxx>

#include<vector>

namespace UniPAX
{

class UNIPAX_EXPORT ODBLoadRunnable : public ODBRunnable
{

public:
	ODBLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & _ids);

	virtual ~ODBLoadRunnable() { };

	virtual void run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database) { };

protected:

	std::vector<boost::shared_ptr<UniPAX::UPBase> > & objects;

	std::vector<UnipaxId> & ids;

private:
	typedef ODBRunnable super;

};

}


#endif /* ODBLOADRUNNABLE_H_ */

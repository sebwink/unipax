/*
 * LoadRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef ODBUPDATERUNNABLE_H_
#define ODBUPDATERUNNABLE_H_

#include<UNIPAX/COMMON/common.h>

#include<UNIPAX/PERSISTENCE/ODBRunnable.h>

#include<boost/shared_ptr.hpp>

#include<UNIPAX/KERNEL/EXT/UPBase.h>

#include <odb/traits.hxx>
#include<odb/database.hxx>
#include<odb/transaction.hxx>



namespace UniPAX
{

class UNIPAX_EXPORT ODBUpdateRunnable : public ODBRunnable
{

public:
	ODBUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> _object);

	ODBUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects);

	virtual ~ODBUpdateRunnable() { };

	virtual void run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database) { };

	std::vector<bool> getSuccessful();

protected:

	std::vector<boost::shared_ptr<UniPAX::UPBase> > objects;

	std::vector<bool> successful;

private:
	typedef ODBRunnable super;
};

}


#endif /* ODBUPDATERUNNABLE_H_ */

/*
 * PersistRunnable.h
 *
 *  Created on: Feb 8, 2012
 *      Author: gerasch
 */

#ifndef ODBPERSISTRUNNABLE_H_
#define ODBPERSISTRUNNABLE_H_

#include <UNIPAX/COMMON/common.h>

#include <UNIPAX/PERSISTENCE/ODBRunnable.h>

#include <UNIPAX/KERNEL/EXT/UPBase.h>

#include <odb/traits.hxx>
#include <odb/database.hxx>
#include <odb/transaction.hxx>


#include <boost/shared_ptr.hpp>
#include <vector>

namespace UniPAX
{

class UNIPAX_EXPORT ODBPersistRunnable : public ODBRunnable
{

public:
	ODBPersistRunnable(boost::shared_ptr<UniPAX::UPBase> _object);

	ODBPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects);

	virtual ~ODBPersistRunnable() { };

	virtual void run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database) { };

	std::vector<UnipaxId> getIds();

protected:

	std::vector<boost::shared_ptr<UniPAX::UPBase> > objects;

	std::vector<UnipaxId> ids;

private:
	typedef ODBRunnable super;
};

}


#endif /* ODBPERSISTRUNNABLE_H_ */

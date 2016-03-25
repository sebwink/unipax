#ifndef UPBASE_H
#define UPBASE_H

/**
 * UPBase is base class for all UniPAX persistent objects.
 */

#include<string>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<odb/database.hxx>
#include<odb/callback.hxx>


#include<boost/shared_ptr.hpp>
#include<boost/weak_ptr.hpp>
#include<boost/operators.hpp>

#include<odb/pointer-traits.hxx>

//#include<UNIPAX/COMMON/PersistenceManager.h>
#include<UNIPAX/KERNEL/ClassType.h>

#include<iostream>
#include<vector>
#include<boost/algorithm/string.hpp>


namespace UniPAX {

class PersistenceManager;

#pragma db object abstract
class UNIPAX_EXPORT UPBase {

protected:

#pragma db id
	UnipaxId unipaxId;

	friend class odb::access;
	//virtual void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType();
//		return "UPBase";
//	}
//
//	static std::string type() {
//		return std::string("UPBase");
//	}
//
	virtual UniPAX::ClassType::ID getTypeID();
//		return UniPAX::ClassType::idUPBase;
//	}
//
//	static UniPAX::ClassType::ID typeID() {
//		return UniPAX::ClassType::idUPBase;
//	}

	UPBase();

	UPBase(const UPBase & arg);

	UPBase & operator =(const UPBase & arg);

	bool equals(UPBase & arg, PersistenceManager & manager);

	virtual ~UPBase();

	virtual bool merge(UPBase& object);

	virtual bool update(PersistenceManager& manager);

	const UnipaxId getUnipaxId() const;

	//get unipaxId
	UnipaxId getUnipaxId();

	//set unipaxId
	void setUnipaxId(UnipaxId unipaxId);

	virtual bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	virtual bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);


//	UnipaxPtr<UniPAX::UPBase>::type getObjectByID(odb::database& odb_db, UnipaxId id);

	UnipaxPtr<UniPAX::UPBase>::type dynamic_copy();

};  //end class UPBase

typedef UnipaxPtr<UPBase>::type UPBasePtr;

}//end namespace UniPAX

#endif

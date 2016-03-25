#ifndef UIBASE_H
#define UIBASE_H

/**
 * UIBase is base class for all imported objects (having an ImportSource)
 */

#include<string>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
//#include<odb/database.hxx>
//#include<odb/callback.hxx>


//#include<boost/shared_ptr.hpp>
//#include<boost/weak_ptr.hpp>
//#include<boost/operators.hpp>

//#include<odb/pointer-traits.hxx>

#include<UNIPAX/COMMON/PersistenceManager.h>
#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<UNIPAX/KERNEL/EXT/ImportSource.h>

#include<iostream>
#include<vector>
#include<boost/algorithm/string.hpp>


namespace UniPAX {

class PersistenceManager;
class ImportSource;

#pragma db object abstract
class UNIPAX_EXPORT UIBase :public UPBase {

protected:

	UnipaxPtr<ImportSource>::type unipaxSource;

	friend class odb::access;

public:

	//virtual std::string getType();
	//virtual UniPAX::ClassType::ID getTypeID();

	UIBase();

	UIBase(const UIBase & arg);

	UIBase & operator =(const UIBase & arg);

	//bool equals(UIBase & arg, PersistenceManager & manager);

	virtual ~UIBase();

	virtual bool merge(UIBase& object);

	virtual bool update(PersistenceManager& manager);

	//get unipaxSource
	const UnipaxPtr<ImportSource>::type getUnipaxSource() const;

	UnipaxPtr<ImportSource>::type getUnipaxSource();

	void setUnipaxSource(UnipaxPtr<ImportSource>::type _unipaxSource);

	virtual bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	virtual bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class UPBase

typedef UnipaxPtr<UIBase>::type UIBasePtr;

}//end namespace UniPAX

#endif

#ifndef THING_H
#define THING_H
//Begin section for file Thing.h
//TODO: Add definitions that you want preserved
//End section for file Thing.h
#include<UNIPAX/KERNEL/EXT/UIBase.h>
//#include<UNIPAX/KERNEL/EXT/ImportSource.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

//class ImportSource;

#pragma db object abstract
class UNIPAX_EXPORT Thing : public UIBase {

protected:

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

//	virtual std::string getType() {
//		return "Thing";
//	}
//
//	static std::string type() {
//		return std::string("Thing");
//	}
//
//	static UniPAX::ClassType::ID typeID() {
//		return UniPAX::ClassType::idThing;
//	}
//
//	virtual UniPAX::ClassType::ID getTypeID() {
//		return UniPAX::ClassType::idThing;
//	}

	Thing();

	Thing(const Thing & object);

	Thing & operator =(const Thing & arg);

	virtual ~Thing();

	bool merge(Thing& arg);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Thing

typedef UnipaxPtr<Thing>::type ThingPtr;

}//end namespace UniPAX

#endif

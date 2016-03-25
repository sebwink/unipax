#ifndef PRIORITY_H
#define PRIORITY_H
//Begin section for file Priority.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Priority.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/EXT/Math.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Priority : public SBase {

protected:

	UnipaxPtr<Math>::type math;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Priority";
	}

	static std::string type() {
		return std::string("Priority");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idPriority;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idPriority;
	}

	Priority();

	Priority(const Priority & arg);

	Priority & operator =(const Priority & arg);

	~Priority();

	bool merge(Priority& object);

	bool update(PersistenceManager& manager);

	const UnipaxPtr<Math>::type getMath() const;

	//get math
	UnipaxPtr<Math>::type getMath();

	//set math
	void setMath(UnipaxPtr<Math>::type _math);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Priority

typedef UnipaxPtr<Priority>::type PriorityPtr;

}//end namespace UniPAX

#endif

#ifndef EVENTASSIGNMENT_H
#define EVENTASSIGNMENT_H
//Begin section for file EventAssignment.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file EventAssignment.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/EXT/Math.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT EventAssignment : public SBase {

protected:

	std::string variable;

	boost::shared_ptr<UniPAX::Math > math;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "EventAssignment";
	}

	static std::string type() {
		return std::string("EventAssignment");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idEventAssignment;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idEventAssignment;
	}

	EventAssignment();

	EventAssignment(const EventAssignment & arg);

	EventAssignment & operator =(const EventAssignment & arg);

	~EventAssignment();

	bool merge(UniPAX::EventAssignment&);

	bool update(PersistenceManager& manager);

	//get variable
	const std::string & getVariable() const;

	std::string & getVariable();

	void setVariable(std::string _variable);


	const boost::shared_ptr<UniPAX::Math > getMath() const;

	boost::shared_ptr<UniPAX::Math > getMath();

	void setMath(boost::shared_ptr<UniPAX::Math > _math);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);


};  //end class EventAssignment

typedef UnipaxPtr<EventAssignment>::type EventAssignmentPtr;

}//end namespace UniPAX

#endif

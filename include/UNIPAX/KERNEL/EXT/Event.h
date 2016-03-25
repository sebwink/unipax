#ifndef EVENT_H
#define EVENT_H
//Begin section for file Event.h
//TODO: Add definitions that you want preserved
#include<string>
#include<vector>
//End section for file Event.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/EXT/Priority.h>
#include<UNIPAX/KERNEL/EXT/Delay.h>
#include<UNIPAX/KERNEL/EXT/Trigger.h>
#include<UNIPAX/KERNEL/EXT/EventAssignment.h>
#include<UNIPAX/KERNEL/BIOPAX/Interaction.h>
//#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Event : public SBase
{

protected:

	bool useValuesFromTriggerTime;

	std::string id;

	std::string name;

	UnipaxPtr<Priority>::type priority;

	UnipaxPtr<Delay>::type delay;

	UnipaxPtr<Trigger>::type trigger;

	std::vector<UnipaxPtr<EventAssignment>::type > eventAssignment;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Event";
	}

	static std::string type() {
		return std::string("Event");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idEvent;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idEvent;
	}


	Event();

	Event(const Event & arg);

	Event & operator =(const Event & arg);

	~Event();

	bool merge(Event& object);

	bool update (PersistenceManager& manager);

	//get useValuesFromTriggerTime
	bool getUseValuesFromTriggerTime();

	const bool getUseValuesFromTriggerTime() const;

	//set useValuesFromTriggerTime
	void setUseValuesFromTriggerTime(bool _useValuesFromTriggerTime);


	//get priority
	const boost::shared_ptr<Priority > getPriority() const;

	boost::shared_ptr<Priority > getPriority();

	void setPriority(boost::shared_ptr<Priority > _priority);


	//get delay
	const boost::shared_ptr<Delay > getDelay() const;

	boost::shared_ptr<Delay > getDelay();

	void setDelay(boost::shared_ptr<Delay > _delay);


	//get trigger
	const boost::shared_ptr<Trigger > getTrigger() const;

	boost::shared_ptr<Trigger > getTrigger();

	void setTrigger(boost::shared_ptr<Trigger > _trigger);


	//get id
	const std::string & getId() const;

	std::string & getId();

	void setId(std::string _id);


	//get name
	const std::string & getName() const;

	std::string & getName();

	void setName(std::string _name);


	//get listOfEventAssignments
	const std::vector<UnipaxPtr<EventAssignment>::type >& getEventAssignments() const;

	std::vector<UnipaxPtr<EventAssignment>::type >& getEventAssignments();

	void setEventAssignments(std::vector<UnipaxPtr<EventAssignment>::type > _listOfEventAssignments);

	void addEventAssignment(UnipaxPtr<EventAssignment>::type  _eventAssignment);


	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);
	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

};  //end class Event

typedef UnipaxPtr<Event>::type EventPtr;

}//end namespace UniPAX

#endif

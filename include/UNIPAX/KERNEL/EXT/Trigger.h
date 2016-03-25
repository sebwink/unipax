#ifndef TRIGGER_H
#define TRIGGER_H
//Begin section for file Trigger.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Trigger.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/EXT/Math.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Trigger : public SBase {

protected:

	double initialValue;

	bool persistent;

	UnipaxPtr<Math>::type math;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Trigger";
	}

	static std::string type() {
		return std::string("Trigger");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idTrigger;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idTrigger;
	}

	Trigger();

	Trigger(const Trigger & arg);

	Trigger & operator =(const Trigger & arg);

	~Trigger();

	bool merge(Trigger& object);

	bool update(PersistenceManager& manager);

	const double getInitialValue() const;

	//get initialValue
	double getInitialValue();

	//set initialValue
	void setInitialValue(double _initialValue);

	const bool getPersistent() const;

	//get persistent
	bool getPersistent();

	//set persistent
	void setPersistent(bool _persistent);

	const UnipaxPtr<Math>::type getMath() const;

	//get math
	UnipaxPtr<Math>::type getMath();

	//set math
	void setMath(UnipaxPtr<Math>::type _math);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Trigger

typedef UnipaxPtr<Trigger>::type TriggerPtr;

}//end namespace UniPAX

#endif

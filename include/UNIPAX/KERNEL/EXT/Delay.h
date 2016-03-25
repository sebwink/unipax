#ifndef DELAY_H
#define DELAY_H
//Begin section for file Delay.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Delay.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/EXT/Math.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Delay : public SBase {

protected:

	UnipaxPtr<Math>::type math;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Delay";
	}

	static std::string type() {
		return std::string("Delay");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idDelay;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idDelay;
	}

	Delay();

	Delay(const Delay & arg);

	Delay & operator =(const Delay & arg);

	~Delay();

	bool merge(Delay& object);

	bool update(PersistenceManager& manager);

	const boost::shared_ptr<Math > getMath() const;

	//get math
	boost::shared_ptr<Math > getMath();

	//set math
	void setMath(boost::shared_ptr<Math > _math);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Delay

typedef UnipaxPtr<Delay>::type DelayPtr;

}//end namespace UniPAX

#endif

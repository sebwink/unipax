#ifndef LOCALPARAMETER_H
#define LOCALPARAMETER_H
//Begin section for file LocalParameter.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file LocalParameter.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/EXT/KineticLaw.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

class KineticLaw;

#pragma db object polymorphic
class UNIPAX_EXPORT LocalParameter : public SBase {

protected:

	std::string id;

	std::string name;

	double value;

	std::string unit;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "LocalParameter";
	}

	static std::string type() {
		return std::string("LocalParameter");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idLocalParameter;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idLocalParameter;
	}

	LocalParameter();

	LocalParameter(const LocalParameter & arg);

	LocalParameter & operator =(const LocalParameter & arg);

	~LocalParameter();

	bool merge(LocalParameter& object);

	bool update(PersistenceManager& manager);

	//get id
	const std::string & getId() const;

	std::string & getId();

	void setId(std::string _id);

	//get name
	const std::string & getName() const;

	std::string & getName();

	void setName(std::string _name);

	const double getValue() const;

	//get value
	double getValue();

	//set value
	void setValue(double _value);

	//get unit
	const std::string & getUnit() const;

	std::string & getUnit();

	void setUnit(std::string _unit);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class LocalParameter

typedef UnipaxPtr<LocalParameter>::type LocalParameterPtr;

}//end namespace UniPAX

#endif

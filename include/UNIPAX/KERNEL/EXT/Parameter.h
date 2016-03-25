#ifndef PARAMETER_H
#define PARAMETER_H
//Begin section for file Parameter.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Parameter.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Parameter : public SBase {

protected:

	bool constant;

	std::string id;

	std::string name;

	double value;

	std::string units;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Parameter";
	}

	static std::string type() {
		return std::string("Parameter");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idParameter;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idParameter;
	}

	Parameter();

	Parameter(const Parameter & arg);

	Parameter & operator =(const Parameter & arg);

	~Parameter();

	bool merge(Parameter& object);

	bool update(PersistenceManager& manager);

	// constant
	const bool getConstant() const;

	bool getConstant();

	void setConstant(bool _constant);

	// id
	const std::string & getId() const;

	std::string & getId();

	void setId(std::string _id);

	// name
	const std::string & getName() const;

	std::string & getName();

	void setName(std::string _name);

	// value
	const double getValue() const;

	double getValue();

	void setValue(double _value);

	// units
	const std::string & getUnits() const;

	std::string & getUnits();

	void setUnits(std::string _units);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Parameter

typedef UnipaxPtr<Parameter>::type ParameterPtr;

}//end namespace UniPAX

#endif

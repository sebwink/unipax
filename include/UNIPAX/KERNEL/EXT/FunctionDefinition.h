#ifndef FUNCTIONDEFINITION_H
#define FUNCTIONDEFINITION_H
//Begin section for file FunctionDefinition.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file FunctionDefinition.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<UNIPAX/KERNEL/EXT/Math.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

class Pathway;

#pragma db object polymorphic
class UNIPAX_EXPORT FunctionDefinition : public SBase {

protected:

	std::string id;

	std::string name;

	UnipaxPtr<Math>::type math;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "FunctionDefinition";
	}

	static std::string type() {
		return std::string("FunctionDefinition");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idFunctionDefinition;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idFunctionDefinition;
	}

	FunctionDefinition();

	FunctionDefinition(const FunctionDefinition & arg);

	FunctionDefinition & operator =(const FunctionDefinition & arg);

	~FunctionDefinition();

	bool merge(UniPAX::FunctionDefinition&);

	bool update(PersistenceManager& manager);

	//get id
	const std::string & getId() const;

	std::string & getId();

	void setId(std::string _id);


	//get name
	const std::string & getName() const;

	std::string & getName();

	void setName(std::string _name);



	const UnipaxPtr<Math>::type getMath() const;

	//get math
	UnipaxPtr<Math>::type getMath();

	//set math
	void setMath(boost::shared_ptr<Math > _math);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class FunctionDefinition

typedef UnipaxPtr<FunctionDefinition>::type FunctionDefinitionPtr;

}//end namespace UniPAX

#endif

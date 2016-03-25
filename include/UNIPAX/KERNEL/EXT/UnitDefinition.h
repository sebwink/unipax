#ifndef UNITDEFINITION_H
#define UNITDEFINITION_H
//Begin section for file UnitDefinition.h
//TODO: Add definitions that you want preserved
#include<string>
#include<vector>
//End section for file UnitDefinition.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<UNIPAX/KERNEL/EXT/Unit.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

//class Pathway;
class Unit;

#pragma db object polymorphic
class UNIPAX_EXPORT UnitDefinition : public SBase {

protected:

	//	UnipaxPtr<Pathway>::type pathway;

	std::string id;

	std::string name;

	std::vector<UnipaxPtr<Unit>::type > unit;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "UnitDefinition";
	}

	static std::string type() {
		return std::string("UnitDefinition");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idUnitDefinition;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idUnitDefinition;
	}

	UnitDefinition();

	UnitDefinition(const UnitDefinition & arg);

	UnitDefinition & operator =(const UnitDefinition & arg);

	~UnitDefinition();

	bool merge(UnitDefinition& object);

	bool update(PersistenceManager& manager);

	// id
	const std::string & getId() const;

	std::string & getId();

	void setId(std::string _id);

	// name
	const std::string & getName() const;

	std::string & getName();

	void setName(std::string _name);

	// unit
	const std::vector<UnipaxPtr<Unit>::type > getUnits() const;

	std::vector<UnipaxPtr<Unit>::type > getUnits();

	void setUnits(std::vector<UnipaxPtr<Unit>::type > _units);

	void addUnit(UnipaxPtr<Unit>::type  _unit);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class UnitDefinition

typedef UnipaxPtr<UnitDefinition>::type UnitDefinitionPtr;

}//end namespace UniPAX

#endif

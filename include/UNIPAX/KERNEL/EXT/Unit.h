#ifndef UNIT_H
#define UNIT_H
//Begin section for file Unit.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Unit.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/EXT/UnitDefinition.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

class UnitDefinition;

#pragma db object polymorphic
class UNIPAX_EXPORT Unit : public SBase {

protected:

	int exponent;

	std::string kind;

	double multiplier;

	double scale;

	UnipaxPtr<UnitDefinition>::type unitDefinition;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Unit";
	}

	static std::string type() {
		return std::string("Unit");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idUnit;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idUnit;
	}

	Unit();

	Unit(const Unit & arg);

	Unit & operator =(const Unit & arg);

	~Unit();

	bool merge(Unit& object);

	bool update(PersistenceManager& manager);

	const int getExponent() const;

	//get exponent
	int getExponent();

	//set exponent
	void setExponent(int _exponent);

	//get kind
	const std::string & getKind() const;

	std::string & getKind();

	void setKind(std::string _kind);

	const double getMultiplier() const;

	//get multiplier
	double getMultiplier();

	//set multiplier
	void setMultiplier(double _multiplier);

	const double getScale() const;

	//get scale
	double getScale();

	//set scale
	void setScale(double _scale);

	const UnipaxPtr<UnitDefinition>::type getUnitDefinition() const;

	//get unitDefinition
	UnipaxPtr<UnitDefinition>::type getUnitDefinition();

	//set unitDefinition
	void setUnitDefinition(UnipaxPtr<UnitDefinition>::type _unitDefinition);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Unit

typedef UnipaxPtr<Unit>::type UnitPtr;

}//end namespace UniPAX

#endif

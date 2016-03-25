#ifndef DELTAG_H
#define DELTAG_H
//Begin section for file DeltaG.h
//TODO: Add definitions that you want preserved
//End section for file DeltaG.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT DeltaG : public UtilityClass {

	//Begin section for UniPAX::DeltaG
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::DeltaG

protected:

	double deltaGPrime0;

	double ionicStrength;

	double ph;

	double pMg;

	double temperature;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "DeltaG";
	}

	static std::string type() {
		return std::string("DeltaG");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idDeltaG;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idDeltaG;
	}

	DeltaG();

	DeltaG(const DeltaG & arg);

	DeltaG & operator =(const DeltaG & arg);

	~DeltaG();

	bool merge(DeltaG& object);
	bool update(PersistenceManager& manager);


	const double getDeltaGPrime0() const;

	//get deltaGPrime0
	double getDeltaGPrime0();

	//set deltaGPrime0
	void setDeltaGPrime0(double _deltaGPrime0);

	const double getIonicStrength() const;

	//get ionicStrength
	double getIonicStrength();

	//set ionicStrength
	void setIonicStrength(double _ionicStrength);

	const double getPh() const;

	//get ph
	double getPh();

	//set ph
	void setPh(double _ph);

	const double getPMg() const;

	//get pMg
	double getPMg();

	//set pMg
	void setPMg(double pMg);

	const double getTemperature() const;

	//get temperature
	double getTemperature();

	//set temperature
	void setTemperature(double temperature);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef UtilityClass super;

};  //end class DeltaG

typedef UnipaxPtr<DeltaG>::type DeltaGPtr;

}//end namespace UniPAX

#endif

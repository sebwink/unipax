#ifndef KPRIME_H
#define KPRIME_H
//Begin section for file KPrime.h
//TODO: Add definitions that you want preserved
//End section for file KPrime.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT KPrime : public UtilityClass {

protected:

	double ionicStrength;

	double kPrime;

	double ph;

	double pMg;

	double temperature;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "KPrime";
	}

	static std::string type() {
		return std::string("KPrime");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idKPrime;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idKPrime;
        }

        KPrime();

	KPrime(const KPrime & arg);

	KPrime & operator =(const KPrime & arg);

	~KPrime();

	bool merge(KPrime& object);
	bool update(PersistenceManager& manager);


	const double getIonicStrength() const;

	//get ionicStrength
	double getIonicStrength();

	//set ionicStrength
	void setIonicStrength(double _ionicStrength);

	const double getKPrime() const;

	//get kPrime
	double getKPrime();

	//set kPrime
	void setKPrime(double _kPrime);

	const double getPh() const;

	//get ph
	double getPh();

	//set ph
	void setPh(double _ph);

	const double getPMg() const;

	//get pMg
	double getPMg();

	//set pMg
	void setPMg(double _pMg);

	const double getTemperature() const;

	//get temperature
	double getTemperature();

	//set temperature
	void setTemperature(double _temperature);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef UtilityClass super;

};  //end class KPrime

typedef UnipaxPtr<KPrime>::type KPrimePtr;

}//end namespace UniPAX

#endif

#ifndef STOICHIOMETRY_H
#define STOICHIOMETRY_H
//Begin section for file Stoichiometry.h
//TODO: Add definitions that you want preserved
//End section for file Stoichiometry.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Stoichiometry : public UtilityClass {

protected:

	double stoichiometricCoefficient;

	//unsigned long long id_physicalEntity;

	//#pragma db transient
	UnipaxPtr<PhysicalEntity>::type physicalEntity;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Stoichiometry";
	}

	static std::string type() {
		return std::string("Stoichiometry");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idStoichiometry;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idStoichiometry;
	}

	Stoichiometry();

	Stoichiometry(const Stoichiometry & arg);

	Stoichiometry & operator =(const Stoichiometry & arg);

	~Stoichiometry();

	bool merge(Stoichiometry& object);
	bool update(PersistenceManager& manager);


	const double getStoichiometricCoefficient() const;

	//get stoichiometricCoefficient
	double getStoichiometricCoefficient();

	//set stoichiometricCoefficient
	void setStoichiometricCoefficient(double _stoichiometricCoefficient);

	//get physicalEntity
	const UnipaxPtr<PhysicalEntity>::type getPhysicalEntity() const;

	UnipaxPtr<PhysicalEntity>::type getPhysicalEntity();

	void setPhysicalEntity(UnipaxPtr<PhysicalEntity>::type _physicalEntity);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef UtilityClass super;

};  //end class Stoichiometry

typedef UnipaxPtr<Stoichiometry>::type StoichiometryPtr;

}//end namespace UniPAX

#endif

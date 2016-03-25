#ifndef SMALLMOLECULEREFERENCE_H
#define SMALLMOLECULEREFERENCE_H
//Begin section for file SmallMoleculeReference.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file SmallMoleculeReference.h
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/KERNEL/BIOPAX/ChemicalStructure.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT SmallMoleculeReference : public EntityReference {

protected:

	std::string chemicalFormula;

	double molecularWeight;

	UnipaxPtr<ChemicalStructure>::type structure;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "SmallMoleculeReference";
	}

	static std::string type() {
		return std::string("SmallMoleculeReference");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idSmallMoleculeReference;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idSmallMoleculeReference;
        }

        SmallMoleculeReference();

	SmallMoleculeReference(const SmallMoleculeReference & arg);

	SmallMoleculeReference & operator =(const SmallMoleculeReference & arg);

	~SmallMoleculeReference();

	bool merge(SmallMoleculeReference& object);
	bool update(PersistenceManager& manager);


	//get chemicalFormula
	const std::string & getChemicalFormula() const;

	std::string & getChemicalFormula();

	void setChemicalFormula(std::string _chemicalFormula);

	const double getMolecularWeight() const;

	//get molecularWeight
	double getMolecularWeight();

	//set molecularWeight
	void setMolecularWeight(double _molecularWeight);

	//get structure
	const UnipaxPtr<ChemicalStructure>::type getStructure() const;

	UnipaxPtr<ChemicalStructure>::type getStructure();

	void setStructure(UnipaxPtr<ChemicalStructure>::type _structure);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef EntityReference super;

};  //end class SmallMoleculeReference

typedef UnipaxPtr<SmallMoleculeReference>::type SmallMoleculeReferencePtr;

}//end namespace UniPAX

#endif

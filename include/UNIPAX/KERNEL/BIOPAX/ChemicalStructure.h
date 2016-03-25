#ifndef CHEMICALSTRUCTURE_H
#define CHEMICALSTRUCTURE_H
//Begin section for file ChemicalStructure.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file ChemicalStructure.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT ChemicalStructure : public UtilityClass {

	//Begin section for UniPAX::ChemicalStructure
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::ChemicalStructure

protected:

	std::string structureData;

	std::string structureFormat;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "ChemicalStructure";
	}

	static std::string type() {
		return std::string("ChemicalStructure");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idChemicalStructure;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idChemicalStructure;
        }

        ChemicalStructure();

	ChemicalStructure(const ChemicalStructure & arg);

	ChemicalStructure & operator =(const ChemicalStructure & arg);

	~ChemicalStructure();

	bool merge(ChemicalStructure& object);
	bool update(PersistenceManager& manager);


	//get structureData
	const std::string & getStructureData() const;

	std::string & getStructureData();

	void setStructureData(std::string _structureData);

	//get structureFormat
	const std::string & getStructureFormat() const;

	std::string & getStructureFormat();

	void setStructureFormat(std::string _structureFormat);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef UtilityClass super;

};  //end class ChemicalStructure

typedef UnipaxPtr<ChemicalStructure>::type ChemicalStructurePtr;

}//end namespace UniPAX

#endif

#ifndef MOLECULARINTERACTION_H
#define MOLECULARINTERACTION_H
//Begin section for file MolecularInteraction.h
//TODO: Add definitions that you want preserved
//End section for file MolecularInteraction.h
#include<UNIPAX/KERNEL/BIOPAX/Interaction.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT MolecularInteraction : public Interaction {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "MolecularInteraction";
	}

	static std::string type() {
		return std::string("MolecularInteraction");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idMolecularInteraction;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idMolecularInteraction;
        }

        MolecularInteraction();

	MolecularInteraction(const MolecularInteraction & arg);

	MolecularInteraction & operator =(const MolecularInteraction & arg);

	~MolecularInteraction();

	bool merge(MolecularInteraction& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Interaction super;

};  //end class MolecularInteraction

typedef UnipaxPtr<MolecularInteraction>::type MolecularInteractionPtr;

}//end namespace UniPAX

#endif

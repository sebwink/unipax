#ifndef SMALLMOLECULE_H
#define SMALLMOLECULE_H
//Begin section for file SmallMolecule.h
//TODO: Add definitions that you want preserved
//End section for file SmallMolecule.h
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT SmallMolecule : public PhysicalEntity {

protected:

	// std::vector<unsigned long long> id_entityReference;
//#pragma db transient
	std::vector<UnipaxPtr<EntityReference>::type > entityReference;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "SmallMolecule";
	}

	static std::string type() {
		return std::string("SmallMolecule");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idSmallMolecule;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idSmallMolecule;
        }

        SmallMolecule();

	SmallMolecule(const SmallMolecule & arg);

	SmallMolecule & operator =(const SmallMolecule & arg);

	~SmallMolecule();

	bool merge(SmallMolecule& object);
	bool update(PersistenceManager& manager);


	//get entityReference
	const std::vector<UnipaxPtr<EntityReference>::type > & getEntityReferences() const;

	std::vector<UnipaxPtr<EntityReference>::type > & getEntityReferences();

	void setEntityReferences(std::vector<UnipaxPtr<EntityReference>::type > _entityReferences);

	void addEntityReference(UnipaxPtr<EntityReference>::type  _entityReference);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef PhysicalEntity super;

};  //end class SmallMolecule

typedef UnipaxPtr<SmallMolecule>::type SmallMoleculePtr;

}//end namespace UniPAX

#endif

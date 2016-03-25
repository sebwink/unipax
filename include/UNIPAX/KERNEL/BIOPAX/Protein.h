#ifndef PROTEIN_H
#define PROTEIN_H
//Begin section for file Protein.h
//TODO: Add definitions that you want preserved
//End section for file Protein.h
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Protein : public PhysicalEntity {

protected:


	/* The entity reference stores
	 * the non‐changing aspects of this protein, such as the name, sequence, organism,
	 * database cross‐references or evidence.
	 */
	// std::vector<unsigned long long> id_entityReference;

//#pragma db transient
	std::vector<UnipaxPtr<EntityReference>::type > entityReference;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Protein";
	}

	static std::string type() {
		return std::string("Protein");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idProtein;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idProtein;
        }

        Protein();

	Protein(const Protein & arg);

	Protein & operator =(const Protein & arg);

	~Protein();

	bool merge(Protein& object);
	bool update(PersistenceManager& manager);


	//get entityReference
	const std::vector<UnipaxPtr<EntityReference>::type > & getEntityReferences() const;

	std::vector<UnipaxPtr<EntityReference>::type > & getEntityReferences();

	void addEntityReference(UnipaxPtr<EntityReference>::type _entityReference);
	void setEntityReferences(std::vector<UnipaxPtr<EntityReference>::type > _entityReferences);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef PhysicalEntity super;

};  //end class Protein

typedef UnipaxPtr<Protein>::type ProteinPtr;

}//end namespace UniPAX

#endif

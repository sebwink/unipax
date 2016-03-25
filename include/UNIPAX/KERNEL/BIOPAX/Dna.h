#ifndef DNA_H
#define DNA_H
//Begin section for file Dna.h
//TODO: Add definitions that you want preserved
//End section for file Dna.h
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Dna : public PhysicalEntity {

	//Begin section for UniPAX::Dna
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::Dna

protected:

	// std::vector<unsigned long long> id_entityReference;
//#pragma db transient
	std::vector<UnipaxPtr<EntityReference>::type > entityReference;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Dna";
	}

	static std::string type() {
		return std::string("Dna");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idDna;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idDna;
        }

        Dna();

	Dna(const Dna & arg);

	Dna & operator =(const Dna & arg);

	~Dna();

	bool merge(Dna& object);
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

};  //end class Dna

typedef UnipaxPtr<Dna>::type DnaPtr;

}//end namespace UniPAX

#endif

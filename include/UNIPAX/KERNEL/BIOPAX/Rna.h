#ifndef RNA_H
#define RNA_H
//Begin section for file Rna.h
//TODO: Add definitions that you want preserved
//End section for file Rna.h
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Rna : public PhysicalEntity {

protected:

	// std::vector<unsigned long long> id_entityReference;

//#pragma db transient
	std::vector<UnipaxPtr<EntityReference>::type > entityReference;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Rna";
	}

	static std::string type() {
		return std::string("Rna");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idRna;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idRna;
        }

        Rna();

	Rna(const Rna & arg);

	Rna & operator =(const Rna & arg);

	~Rna();

	bool merge(Rna& object);
	bool update(PersistenceManager& manager);


	//get entityReference
	const std::vector<UnipaxPtr<EntityReference>::type > & getEntityReferences() const;

	std::vector<UnipaxPtr<EntityReference>::type > & getEntityReferences();

	void addEntityReference(UnipaxPtr<EntityReference>::type  _entityReference);

	void setEntityReferences(std::vector<UnipaxPtr<EntityReference>::type > _entityReferences);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef PhysicalEntity super;

};  //end class Rna

typedef UnipaxPtr<Rna>::type RnaPtr;

}//end namespace UniPAX

#endif

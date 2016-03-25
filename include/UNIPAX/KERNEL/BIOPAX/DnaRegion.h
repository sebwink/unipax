#ifndef DNAREGION_H
#define DNAREGION_H
//Begin section for file DnaRegion.h
//TODO: Add definitions that you want preserved
//End section for file DnaRegion.h
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT DnaRegion : public PhysicalEntity {

	//Begin section for UniPAX::DnaRegion
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::DnaRegion

protected:

	// std::vector<unsigned long long> id_entityReference;
//#pragma db transient
	std::vector<UnipaxPtr<EntityReference>::type > entityReference;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "DnaRegion";
	}

	static std::string type() {
		return std::string("DnaRegion");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idDnaRegion;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idDnaRegion;
        }

        DnaRegion();

	DnaRegion(const DnaRegion & arg);

	DnaRegion & operator =(const DnaRegion & arg);

	~DnaRegion();

	bool merge(DnaRegion& object);
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

};  //end class DnaRegion

typedef UnipaxPtr<DnaRegion>::type DnaRegionPtr;

}//end namespace UniPAX

#endif

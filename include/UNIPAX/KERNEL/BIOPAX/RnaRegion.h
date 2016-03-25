#ifndef RNAREGION_H
#define RNAREGION_H
//Begin section for file RnaRegion.h
//TODO: Add definitions that you want preserved
//End section for file RnaRegion.h
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {



#pragma db object
class UNIPAX_EXPORT RnaRegion : public PhysicalEntity {

protected:


	// std::vector<unsigned long long> id_entityReference;
//#pragma db transient
	std::vector<UnipaxPtr<EntityReference>::type > entityReference;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "RnaRegion";
	}

	static std::string type() {
		return std::string("RnaRegion");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idRnaRegion;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idRnaRegion;
        }

        RnaRegion();

	RnaRegion(const RnaRegion & arg);

	RnaRegion & operator =(const RnaRegion & arg);

	~RnaRegion();

	bool merge(RnaRegion& object);
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

};  //end class RnaRegion

typedef UnipaxPtr<RnaRegion>::type RnaRegionPtr;

}//end namespace UniPAX

#endif

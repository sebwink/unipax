#ifndef RNAREFERENCE_H
#define RNAREFERENCE_H
//Begin section for file RnaReference.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file RnaReference.h
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT RnaReference : public EntityReference {

protected:

	std::string sequence;

	//unsigned long long id_subRegion;

//#pragma db transient
	UnipaxPtr<EntityReference>::type subRegion;

	UnipaxPtr<BioSource>::type organism;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "RnaReference";
	}

	static std::string type() {
		return std::string("RnaReference");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idRnaReference;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idRnaReference;
        }

        RnaReference();

	RnaReference(const RnaReference & arg);

	RnaReference & operator =(const RnaReference & arg);

	~RnaReference();

	bool merge(RnaReference& object);
	bool update(PersistenceManager& manager);


	//get sequence
	const std::string & getSequence() const;

	std::string & getSequence();

	void setSequence(std::string _sequence);

	//get organism
	const UnipaxPtr<BioSource>::type getOrganism() const;

	UnipaxPtr<BioSource>::type getOrganism();

	void setOrganism(UnipaxPtr<BioSource>::type _organism);

	const UnipaxPtr<EntityReference>::type getSubRegion() const;

	//get subRegion
	UnipaxPtr<EntityReference>::type getSubRegion();

	//set subRegion
	void setSubRegion(UnipaxPtr<EntityReference>::type _subRegion);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef EntityReference super;

};  //end class RnaReference

typedef UnipaxPtr<RnaReference>::type RnaReferencePtr;

}//end namespace UniPAX

#endif

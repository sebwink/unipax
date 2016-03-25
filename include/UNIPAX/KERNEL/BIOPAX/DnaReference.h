#ifndef DNAREFERENCE_H
#define DNAREFERENCE_H
//Begin section for file DnaReference.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file DnaReference.h
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT DnaReference : public EntityReference {

	//Begin section for UniPAX::DnaReference
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::DnaReference

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
		return "DnaReference";
	}

	static std::string type() {
		return std::string("DnaReference");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idDnaReference;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idDnaReference;
        }

        DnaReference();

	DnaReference(const DnaReference & arg);

	DnaReference & operator =(const DnaReference & arg);

	~DnaReference();

	bool merge(DnaReference& object);
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

};  //end class DnaReference

typedef UnipaxPtr<DnaReference>::type DnaReferencePtr;

}//end namespace UniPAX

#endif

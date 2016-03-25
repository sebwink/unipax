#ifndef RNAREGIONREFERENCE_H
#define RNAREGIONREFERENCE_H
//Begin section for file RnaRegionReference.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file RnaRegionReference.h
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/KERNEL/BIOPAX/SequenceLocation.h>
#include<UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include<UNIPAX/KERNEL/BIOPAX/SequenceRegionVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT RnaRegionReference : public EntityReference {

protected:

	std::string sequence;

	//unsigned long long id_subRegion;

//#pragma db transient
	UnipaxPtr<EntityReference>::type subRegion;

	//unsigned long long id_absoluteRegion;

//#pragma db transient
	UnipaxPtr<SequenceLocation>::type absoluteRegion;

	UnipaxPtr<BioSource>::type organism;

	UnipaxPtr<SequenceRegionVocabulary>::type regionType;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "RnaRegionReference";
	}

	static std::string type() {
		return std::string("RnaRegionReference");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idRnaRegionReference;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idRnaRegionReference;
        }

        RnaRegionReference();

	RnaRegionReference(const RnaRegionReference & arg);

	RnaRegionReference & operator =(const RnaRegionReference & arg);

	~RnaRegionReference();

	bool merge(RnaRegionReference& object);
	bool update(PersistenceManager& manager);


	//get sequence
	const std::string & getSequence() const;

	std::string & getSequence();

	void setSequence(std::string _sequence);

	//get absoluteRegion
	const UnipaxPtr<SequenceLocation>::type getAbsoluteRegion() const;

	UnipaxPtr<SequenceLocation>::type getAbsoluteRegion();

	void setAbsoluteRegion(UnipaxPtr<SequenceLocation>::type _absoluteRegion);

	//get organism
	const UnipaxPtr<BioSource>::type getOrganism() const;

	UnipaxPtr<BioSource>::type getOrganism();

	void setOrganism(UnipaxPtr<BioSource>::type _organism);

	//get regionType
	const UnipaxPtr<SequenceRegionVocabulary>::type getRegionType() const;

	UnipaxPtr<SequenceRegionVocabulary>::type getRegionType();

	void setRegionType(UnipaxPtr<SequenceRegionVocabulary>::type _regionType);

	const UnipaxPtr<EntityReference>::type getSubRegion() const;

	//get subRegion
	UnipaxPtr<EntityReference>::type getSubRegion();

	//set subRegion
	void setSubRegion(UnipaxPtr<EntityReference>::type _subRegion);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef EntityReference super;

};  //end class RnaRegionReference

typedef UnipaxPtr<RnaRegionReference>::type RnaRegionReferencePtr;

}//end namespace UniPAX

#endif

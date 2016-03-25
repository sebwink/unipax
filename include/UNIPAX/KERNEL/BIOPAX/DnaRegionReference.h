#ifndef DNAREGIONREFERENCE_H
#define DNAREGIONREFERENCE_H
//Begin section for file DnaRegionReference.h
//TODO: Add definitions that you want preserved
#include<string>
#include<string>
//End section for file DnaRegionReference.h
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/KERNEL/BIOPAX/SequenceRegionVocabulary.h>
#include<UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include<UNIPAX/KERNEL/BIOPAX/SequenceLocation.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT DnaRegionReference : public EntityReference {

	//Begin section for UniPAX::DnaRegionReference
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::DnaRegionReference

protected:

	std::string sequence;

	//unsigned long long id_subRegion;
//#pragma db transient
	UnipaxPtr<EntityReference>::type subRegion;

	UnipaxPtr<SequenceRegionVocabulary>::type regionType;

	UnipaxPtr<BioSource>::type organism;

	//unsigned long long id_absoluteRegion;
//#pragma db transient
	UnipaxPtr<SequenceLocation>::type absoluteRegion;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "DnaRegionReference";
	}

	static std::string type() {
		return std::string("DnaRegionReference");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idDnaRegionReference;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idDnaRegionReference;
        }

        DnaRegionReference();

	DnaRegionReference(const DnaRegionReference & arg);

	DnaRegionReference & operator =(const DnaRegionReference & arg);

	~DnaRegionReference();

	bool merge(DnaRegionReference& object);
	bool update(PersistenceManager& manager);


	//get sequence
	const std::string & getSequence() const;

	std::string & getSequence();

	void setSequence(std::string _sequence);

	//get regionType
	const UnipaxPtr<SequenceRegionVocabulary>::type getRegionType() const;
	UnipaxPtr<SequenceRegionVocabulary>::type getRegionType();
	void setRegionType(UnipaxPtr<SequenceRegionVocabulary>::type _regionType);

	//get organism
	const UnipaxPtr<BioSource>::type getOrganism() const;

	UnipaxPtr<BioSource>::type getOrganism();

	void setOrganism(UnipaxPtr<BioSource>::type _organism);

	//get absoluteRegion
	const UnipaxPtr<SequenceLocation>::type getAbsoluteRegion() const;

	UnipaxPtr<SequenceLocation>::type getAbsoluteRegion();

	void setAbsoluteRegion(UnipaxPtr<SequenceLocation>::type _absoluteRegion);

	const UnipaxPtr<EntityReference>::type getSubRegion() const;

	//get subRegion
	UnipaxPtr<EntityReference>::type getSubRegion();

	//set subRegion
	void setSubRegion(UnipaxPtr<EntityReference>::type _subRegion);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef EntityReference super;

};  //end class DnaRegionReference

typedef UnipaxPtr<DnaRegionReference>::type DnaRegionReferencePtr;

}//end namespace UniPAX

#endif

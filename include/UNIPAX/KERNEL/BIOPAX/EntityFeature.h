#ifndef ENTITYFEATURE_H
#define ENTITYFEATURE_H
//Begin section for file EntityFeature.h
//TODO: Add definitions that you want preserved
//End section for file EntityFeature.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/Evidence.h>
#include<UNIPAX/KERNEL/BIOPAX/SequenceLocation.h>
#include<UNIPAX/KERNEL/BIOPAX/SequenceRegionVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

class Evidence;
class EntityFeature;
class SequenceLocation;
class SequenceRegionVocabulary;

#pragma db object polymorphic
class UNIPAX_EXPORT EntityFeature : public UtilityClass {

protected:

	std::vector<UnipaxPtr<Evidence>::type > evidence;

	//	//UnipaxPtr<EntityFeature>::type memberFeature;
	//	// std::vector<unsigned long long> id_memberFeature;
	////#pragma db transient
	std::vector<UnipaxPtr<EntityFeature>::type > memberFeature;

	//	//UnipaxPtr<SequenceLocation>::type featureLocation;
	//	// std::vector<unsigned long long> id_featureLocation;
	////#pragma db transient
	std::vector<UnipaxPtr<SequenceLocation>::type > featureLocation;

	//UnipaxPtr<SequenceRegionVocabulary>::type featureLocationType;
	std::vector<UnipaxPtr<SequenceRegionVocabulary>::type > featureLocationType;

	friend class odb::access;
	//	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "EntityFeature";
	}

	static std::string type() {
		return std::string("EntityFeature");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idEntityFeature;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idEntityFeature;
	}

	EntityFeature();

	EntityFeature(const EntityFeature & arg);

	EntityFeature & operator =(const EntityFeature & arg);

	~EntityFeature();

	bool merge(EntityFeature& object);
	bool update(PersistenceManager& manager);


	//get evidence
	const std::vector<UnipaxPtr<Evidence>::type > & getEvidences() const;

	std::vector<UnipaxPtr<Evidence>::type > & getEvidences();

	//void setEvidence(const Evidence& evidence);

	void setEvidences(std::vector<UnipaxPtr<Evidence>::type > _evidences);

	void addEvidence(UnipaxPtr<Evidence>::type  _evidence);


	//get memberFeature
	const std::vector<UnipaxPtr<EntityFeature>::type > & getMemberFeatures() const;

	std::vector<UnipaxPtr<EntityFeature>::type > & getMemberFeatures();

	//void setMemberFeature(const EntityFeature& memberFeature);

	void setMemberFeatures(std::vector<UnipaxPtr<EntityFeature>::type > _memberFeatures);

	void addMemberFeature(UnipaxPtr<EntityFeature>::type  _memberFeatures);


	//get featureLocation
	const std::vector<UnipaxPtr<SequenceLocation>::type > & getFeatureLocations() const;

	std::vector<UnipaxPtr<SequenceLocation>::type > & getFeatureLocations();

	//void setFeatureLocation(const SequenceLocation& featureLocation);

	void setFeatureLocations(std::vector<UnipaxPtr<SequenceLocation>::type > _featureLocations);

	void addFeatureLocation(UnipaxPtr<SequenceLocation>::type  _featureLocation);


	//get featureLocationType
	const std::vector<UnipaxPtr<SequenceRegionVocabulary>::type > & getFeatureLocationTypes() const;

	std::vector<UnipaxPtr<SequenceRegionVocabulary>::type > & getFeatureLocationTypes();

	//void setFeatureLocationType(const SequenceRegionVocabulary& featureLocationType);

	void setFeatureLocationTypes(std::vector<UnipaxPtr<SequenceRegionVocabulary>::type > _featureLocationTypes);

	void addFeatureLocationType(UnipaxPtr<SequenceRegionVocabulary>::type  _featureLocationType);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef UtilityClass super;

};  //end class EntityFeature

typedef UnipaxPtr<EntityFeature>::type EntityFeaturePtr;

}//end namespace UniPAX

#endif

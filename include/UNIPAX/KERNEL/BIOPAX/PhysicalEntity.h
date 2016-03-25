#ifndef PHYSICALENTITY_H
#define PHYSICALENTITY_H
//Begin section for file PhysicalEntity.h
//TODO: Add definitions that you want preserved
//End section for file PhysicalEntity.h
#include<UNIPAX/KERNEL/BIOPAX/Entity.h>
#include<UNIPAX/KERNEL/BIOPAX/EntityFeature.h>
#include<UNIPAX/KERNEL/BIOPAX/CellularLocationVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT PhysicalEntity : public Entity {

protected:

	// std::vector<unsigned long long> id_feature;

//#pragma db transient
	std::vector<UnipaxPtr<EntityFeature>::type > feature;

	// std::vector<unsigned long long> id_memberPhysicalEntity;

//#pragma db transient
	std::vector<UnipaxPtr<PhysicalEntity>::type > memberPhysicalEntity;

	// std::vector<unsigned long long> id_notFeature;

//#pragma db transient
	std::vector<UnipaxPtr<EntityFeature>::type > notFeature;

	UnipaxPtr<CellularLocationVocabulary>::type cellularLocation;


friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "PhysicalEntity";
	}

	static std::string type() {
		return std::string("PhysicalEntity");
	}


        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idPhysicalEntity;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idPhysicalEntity;
        }

        PhysicalEntity();

	PhysicalEntity(const PhysicalEntity & arg);

	PhysicalEntity & operator =(const PhysicalEntity & arg);

	~PhysicalEntity();

	bool merge(PhysicalEntity& object);
	bool update(PersistenceManager& manager);


	//get feature
	const std::vector<UnipaxPtr<EntityFeature>::type > & getFeatures() const;

	std::vector<UnipaxPtr<EntityFeature>::type > & getFeatures();

	void addFeature(UnipaxPtr<EntityFeature>::type  _feature);

	void setFeatures(std::vector<UnipaxPtr<EntityFeature>::type >  _features);


	//get memberPhysicalEntity
	const std::vector<UnipaxPtr<PhysicalEntity>::type > & getMemberPhysicalEntities() const;

	std::vector<UnipaxPtr<PhysicalEntity>::type > & getMemberPhysicalEntities();

	void addMemberPhysicalEntity(UnipaxPtr<PhysicalEntity>::type  _memberPhysicalEntity);

	void setMemberPhysicalEntities(std::vector<UnipaxPtr<PhysicalEntity>::type > _memberPhysicalEntities);


	//get notFeature
	const std::vector<UnipaxPtr<EntityFeature>::type >& getNotFeatures() const;

	std::vector<UnipaxPtr<EntityFeature>::type > & getNotFeatures();

	void addNotFeature(UnipaxPtr<EntityFeature>::type  _notFeature);

	void setNotFeatures(std::vector<UnipaxPtr<EntityFeature>::type >  _notFeatures);


	//get cellularLocation
	const UnipaxPtr<CellularLocationVocabulary>::type getCellularLocation() const;

	UnipaxPtr<CellularLocationVocabulary>::type getCellularLocation();

	void setCellularLocation(boost::shared_ptr<CellularLocationVocabulary > _cellularLocation);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Entity super;

};  //end class PhysicalEntity

typedef UnipaxPtr<PhysicalEntity>::type PhysicalEntityPtr;

}//end namespace UniPAX

#endif

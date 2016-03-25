#ifndef ENTITYREFERENCE_H
#define ENTITYREFERENCE_H
//Begin section for file EntityReference.h
//TODO: Add definitions that you want preserved
//End section for file EntityReference.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/Evidence.h>
#include<UNIPAX/KERNEL/BIOPAX/EntityReferenceTypeVocabulary.h>
#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT EntityReference : public UtilityClass {

protected:

	// std::vector<unsigned long long> id_memberEntityReferences;
	//#pragma db transient
	std::vector<UnipaxPtr<EntityReference>::type > memberEntityReferences;

	std::vector<UnipaxPtr<Evidence>::type > evidence;

	UnipaxPtr<EntityReferenceTypeVocabulary>::type entityReferenceType;

	//unsigned long long id_entityFeature;
	//#pragma db transient
	UnipaxPtr<EntityFeature>::type entityFeature;

	// std::vector<unsigned long long> id_xref;
	//#pragma db transient
	std::vector<UnipaxPtr<Xref>::type > xref;

	std::vector<std::string> name;

	std::string standardName;

	std::string displayName;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "EntityReference";
	}

	static std::string type() {
		return std::string("EntityReference");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idEntityReference;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idEntityReference;
	}

	EntityReference();

	EntityReference(const EntityReference & arg);

	EntityReference & operator =(const EntityReference & arg);

	~EntityReference();

	bool merge(EntityReference& object);
	bool update(PersistenceManager& manager);

	//get memberEntityReference
	const std::vector<UnipaxPtr<EntityReference>::type > getMemberEntityReferences() const;

	std::vector<UnipaxPtr<EntityReference>::type > getMemberEntityReferences();

	void setMemberEntityReferences(std::vector<UnipaxPtr<EntityReference>::type > _memberEntityReferences);

	void addMemberEntityReference(UnipaxPtr<EntityReference>::type _memberEntityReference);

	//get evidence
	const std::vector<UnipaxPtr<Evidence>::type > & getEvidences() const;

	std::vector<UnipaxPtr<Evidence>::type > & getEvidences();

	//void setEvidence(const Evidence& evidence);

	void setEvidences(std::vector<UnipaxPtr<Evidence>::type > _evidences);

	void addEvidence(UnipaxPtr<Evidence>::type  _evidence);

	//get entityReferenceType
	const UnipaxPtr<EntityReferenceTypeVocabulary>::type getEntityReferenceType() const;

	UnipaxPtr<EntityReferenceTypeVocabulary>::type getEntityReferenceType();

	void setEntityReferenceType(UnipaxPtr<EntityReferenceTypeVocabulary>::type _entityReferenceType);

	//get entityFeature
	const UnipaxPtr<EntityFeature>::type getEntityFeature() const;

	UnipaxPtr<EntityFeature>::type getEntityFeature();

	void setEntityFeature(UnipaxPtr<EntityFeature>::type _entityFeature);

	//get xref
	const std::vector<UnipaxPtr<Xref>::type > & getXrefs() const;

	std::vector<UnipaxPtr<Xref>::type > & getXrefs();

	void addXref(UnipaxPtr<Xref>::type  _xref);

	void setXrefs(std::vector<UnipaxPtr<Xref>::type > _xrefs);


	std::vector<std::string>& getNames();

	const std::vector<std::string>& getNames() const;

	std::string getFirstName();

	//set name
	void setNames(std::vector<std::string>& names);
	void addName(std::string name);


	const std::string & getStandardName() const;
	std::string & getStandardName();
	void setStandardName(std::string _name);


	const std::string & getDisplayName() const;
	std::string & getDisplayName();
	void setDisplayName(std::string _name);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef UtilityClass super;

};  //end class EntityReference

typedef UnipaxPtr<EntityReference>::type EntityReferencePtr;

}//end namespace UniPAX

#endif

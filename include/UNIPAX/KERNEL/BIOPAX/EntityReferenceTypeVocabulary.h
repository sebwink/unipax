#ifndef ENTITYREFERENCETYPEVOCABULARY_H
#define ENTITYREFERENCETYPEVOCABULARY_H
//Begin section for file EntityReferenceTypeVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file EntityReferenceTypeVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT EntityReferenceTypeVocabulary : public ControlledVocabulary {

	//Begin section for UniPAX::EntityReferenceTypeVocabulary
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::EntityReferenceTypeVocabulary

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "EntityReferenceTypeVocabulary";
	}

	static std::string type() {
		return std::string("EntityReferenceTypeVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idEntityReferenceTypeVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idEntityReferenceTypeVocabulary;
        }

        EntityReferenceTypeVocabulary();

	EntityReferenceTypeVocabulary(const EntityReferenceTypeVocabulary & arg);

	EntityReferenceTypeVocabulary & operator =(const EntityReferenceTypeVocabulary & arg);

	~EntityReferenceTypeVocabulary();

	bool merge(EntityReferenceTypeVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class EntityReferenceTypeVocabulary

typedef UnipaxPtr<EntityReferenceTypeVocabulary>::type EntityReferenceTypeVocabularyPtr;

}//end namespace UniPAX

#endif

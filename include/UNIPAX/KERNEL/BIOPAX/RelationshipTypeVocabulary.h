#ifndef RELATIONSHIPTYPEVOCABULARY_H
#define RELATIONSHIPTYPEVOCABULARY_H
//Begin section for file RelationshipTypeVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file RelationshipTypeVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT RelationshipTypeVocabulary : public ControlledVocabulary {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "RelationshipTypeVocabulary";
	}

	static std::string type() {
		return std::string("RelationshipTypeVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idRelationshipTypeVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idRelationshipTypeVocabulary;
        }

        RelationshipTypeVocabulary();

	RelationshipTypeVocabulary(const RelationshipTypeVocabulary & arg);

	RelationshipTypeVocabulary & operator =(const RelationshipTypeVocabulary & arg);

	~RelationshipTypeVocabulary();

	bool merge(RelationshipTypeVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class RelationshipTypeVocabulary

typedef UnipaxPtr<RelationshipTypeVocabulary>::type RelationshipTypeVocabularyPtr;

}//end namespace UniPAX

#endif

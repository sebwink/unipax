#ifndef RELATIONSHIPXREF_H
#define RELATIONSHIPXREF_H
//Begin section for file RelationshipXref.h
//TODO: Add definitions that you want preserved
//End section for file RelationshipXref.h
#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<UNIPAX/KERNEL/BIOPAX/RelationshipTypeVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT RelationshipXref : public Xref {

protected:

	std::vector<UnipaxPtr<RelationshipTypeVocabulary>::type > relationshipType;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "RelationshipXref";
	}

	static std::string type() {
		return std::string("RelationshipXref");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idRelationshipXref;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idRelationshipXref;
        }

        RelationshipXref();

	RelationshipXref(const RelationshipXref & arg);

	RelationshipXref & operator =(const RelationshipXref & arg);

	~RelationshipXref();

	bool merge(RelationshipXref& object);
	bool update(PersistenceManager& manager);


	//get relationshipType
	const std::vector<UnipaxPtr<RelationshipTypeVocabulary>::type > getRelationshipTypes() const;

	std::vector<UnipaxPtr<RelationshipTypeVocabulary>::type > getRelationshipTypes();

	void setRelationshipTypes(std::vector<UnipaxPtr<RelationshipTypeVocabulary>::type > _relationshipTypes);

	void addRelationshipType(UnipaxPtr<RelationshipTypeVocabulary>::type  _relationshipType);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Xref super;

};  //end class RelationshipXref

typedef UnipaxPtr<RelationshipXref>::type RelationshipXrefPtr;

}//end namespace UniPAX

#endif

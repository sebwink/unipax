#ifndef INTERACTIONVOCABULARY_H
#define INTERACTIONVOCABULARY_H
//Begin section for file InteractionVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file InteractionVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT InteractionVocabulary : public ControlledVocabulary {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "InteractionVocabulary";
	}

	static std::string type() {
		return std::string("InteractionVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idInteractionVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idInteractionVocabulary;
        }

        InteractionVocabulary();

	InteractionVocabulary(const InteractionVocabulary & arg);

	InteractionVocabulary & operator =(const InteractionVocabulary & arg);

	~InteractionVocabulary();

	bool merge(InteractionVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class InteractionVocabulary

typedef UnipaxPtr<InteractionVocabulary>::type InteractionVocabularyPtr;

}//end namespace UniPAX

#endif

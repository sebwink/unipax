#ifndef SEQUENCEMODIFICATIONVOCABULARY_H
#define SEQUENCEMODIFICATIONVOCABULARY_H
//Begin section for file SequenceModificationVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file SequenceModificationVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT SequenceModificationVocabulary : public ControlledVocabulary {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "SequenceModificationVocabulary";
	}

	static std::string type() {
		return std::string("SequenceModificationVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idSequenceModificationVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idSequenceModificationVocabulary;
        }

        SequenceModificationVocabulary();

	SequenceModificationVocabulary(const SequenceModificationVocabulary & arg);

	SequenceModificationVocabulary & operator =(const SequenceModificationVocabulary & arg);

	~SequenceModificationVocabulary();

	bool merge(SequenceModificationVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class SequenceModificationVocabulary

typedef UnipaxPtr<SequenceModificationVocabulary>::type SequenceModificationVocabularyPtr;

}//end namespace UniPAX

#endif

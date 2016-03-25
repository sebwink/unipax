#ifndef SEQUENCEREGIONVOCABULARY_H
#define SEQUENCEREGIONVOCABULARY_H
//Begin section for file SequenceRegionVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file SequenceRegionVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT SequenceRegionVocabulary : public ControlledVocabulary {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "SequenceRegionVocabulary";
	}

	static std::string type() {
		return std::string("SequenceRegionVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idSequenceRegionVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idSequenceRegionVocabulary;
        }

        SequenceRegionVocabulary();

	SequenceRegionVocabulary(const SequenceRegionVocabulary & arg);

	SequenceRegionVocabulary & operator =(const SequenceRegionVocabulary & arg);

	~SequenceRegionVocabulary();

	bool merge(SequenceRegionVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class SequenceRegionVocabulary

typedef UnipaxPtr<SequenceRegionVocabulary>::type SequenceRegionVocabularyPtr;

}//end namespace UniPAX

#endif

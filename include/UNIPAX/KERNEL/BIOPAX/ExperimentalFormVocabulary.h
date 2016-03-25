#ifndef EXPERIMENTALFORMVOCABULARY_H
#define EXPERIMENTALFORMVOCABULARY_H
//Begin section for file ExperimentalFormVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file ExperimentalFormVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT ExperimentalFormVocabulary : public ControlledVocabulary {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "ExperimentalFormVocabulary";
	}

	static std::string type() {
		return std::string("ExperimentalFormVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idExperimentalFormVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idExperimentalFormVocabulary;
        }

        ExperimentalFormVocabulary();

	ExperimentalFormVocabulary(const ExperimentalFormVocabulary & arg);

	ExperimentalFormVocabulary & operator =(const ExperimentalFormVocabulary & arg);

	~ExperimentalFormVocabulary();

	bool merge(ExperimentalFormVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class ExperimentalFormVocabulary

typedef UnipaxPtr<ExperimentalFormVocabulary>::type ExperimentalFormVocabularyPtr;

}//end namespace UniPAX

#endif

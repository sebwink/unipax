#ifndef TISSUEVOCABULARY_H
#define TISSUEVOCABULARY_H
//Begin section for file TissueVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file TissueVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT TissueVocabulary : public ControlledVocabulary {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "TissueVocabulary";
	}

	static std::string type() {
		return std::string("TissueVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idTissueVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idTissueVocabulary;
        }

        TissueVocabulary();

	TissueVocabulary(const TissueVocabulary & arg);

	TissueVocabulary & operator =(const TissueVocabulary & arg);

	~TissueVocabulary();

	bool merge(TissueVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class TissueVocabulary

typedef UnipaxPtr<TissueVocabulary>::type TissueVocabularyPtr;

}//end namespace UniPAX

#endif

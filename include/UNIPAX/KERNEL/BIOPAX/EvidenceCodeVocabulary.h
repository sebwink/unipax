#ifndef EVIDENCECODEVOCABULARY_H
#define EVIDENCECODEVOCABULARY_H
//Begin section for file EvidenceCodeVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file EvidenceCodeVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

class ControlledVocabulary;

#pragma db object
class UNIPAX_EXPORT EvidenceCodeVocabulary : public ControlledVocabulary {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "EvidenceCodeVocabulary";
	}

	static std::string type() {
		return std::string("EvidenceCodeVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idEvidenceCodeVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idEvidenceCodeVocabulary;
        }

        EvidenceCodeVocabulary();

	EvidenceCodeVocabulary(const EvidenceCodeVocabulary & arg);

	EvidenceCodeVocabulary & operator =(const EvidenceCodeVocabulary & arg);

	~EvidenceCodeVocabulary();

	bool merge(EvidenceCodeVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class EvidenceCodeVocabulary

typedef UnipaxPtr<EvidenceCodeVocabulary>::type EvidenceCodeVocabularyPtr;

}//end namespace UniPAX

#endif

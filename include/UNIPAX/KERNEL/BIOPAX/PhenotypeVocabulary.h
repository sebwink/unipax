#ifndef PHENOTYPEVOCABULARY_H
#define PHENOTYPEVOCABULARY_H
//Begin section for file PhenotypeVocabulary.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file PhenotypeVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT PhenotypeVocabulary : public ControlledVocabulary {

protected:

	std::string patoData;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "PhenotypeVocabulary";
	}

	static std::string type() {
		return std::string("PhenotypeVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idPhenotypeVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idPhenotypeVocabulary;
        }

        PhenotypeVocabulary();

	PhenotypeVocabulary(const PhenotypeVocabulary & arg);

	PhenotypeVocabulary & operator =(const PhenotypeVocabulary & arg);

	~PhenotypeVocabulary();

	bool merge(PhenotypeVocabulary& object);
	bool update(PersistenceManager& manager);

	//get patoData
	const std::string & getPatoData() const;

	std::string & getPatoData();

	void setPatoData(std::string _patoData);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class PhenotypeVocabulary

typedef UnipaxPtr<PhenotypeVocabulary>::type PhenotypeVocabularyPtr;

}//end namespace UniPAX

#endif

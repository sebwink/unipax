#ifndef CELLULARLOCATIONVOCABULARY_H
#define CELLULARLOCATIONVOCABULARY_H
//Begin section for file CellularLocationVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file CellularLocationVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT CellularLocationVocabulary : public ControlledVocabulary {

	//Begin section for UniPAX::CellularLocationVocabulary
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::CellularLocationVocabulary

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "CellularLocationVocabulary";
	}

	static std::string type() {
		return std::string("CellularLocationVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idCellularLocationVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idCellularLocationVocabulary;
        }

        CellularLocationVocabulary();

	CellularLocationVocabulary(const CellularLocationVocabulary & arg);

	CellularLocationVocabulary & operator =(const CellularLocationVocabulary & arg);

	~CellularLocationVocabulary();

	bool merge(CellularLocationVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class CellularLocationVocabulary

typedef UnipaxPtr<CellularLocationVocabulary>::type CellularLocationVocabularyPtr;

}//end namespace UniPAX

#endif

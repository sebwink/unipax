#ifndef CELLVOCABULARY_H
#define CELLVOCABULARY_H
//Begin section for file CellVocabulary.h
//TODO: Add definitions that you want preserved
//End section for file CellVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT CellVocabulary : public ControlledVocabulary {

	//Begin section for UniPAX::CellVocabulary
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::CellVocabulary

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "CellVocabulary";
	}

	static std::string type() {
		return std::string("CellVocabulary");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idCellVocabulary;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idCellVocabulary;
        }

        CellVocabulary();

	CellVocabulary(const CellVocabulary & arg);

	CellVocabulary & operator =(const CellVocabulary & arg);

	~CellVocabulary();

	bool merge(CellVocabulary& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef ControlledVocabulary super;

};  //end class CellVocabulary

typedef UnipaxPtr<CellVocabulary>::type CellVocabularyPtr;

}//end namespace UniPAX


#endif

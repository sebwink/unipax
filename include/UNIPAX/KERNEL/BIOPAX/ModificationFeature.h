#ifndef MODIFICATIONFEATURE_H
#define MODIFICATIONFEATURE_H
//Begin section for file ModificationFeature.h
//TODO: Add definitions that you want preserved
//End section for file ModificationFeature.h
#include<UNIPAX/KERNEL/BIOPAX/EntityFeature.h>
#include<UNIPAX/KERNEL/BIOPAX/SequenceModificationVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT ModificationFeature : public EntityFeature {

protected:

	UnipaxPtr<SequenceModificationVocabulary>::type modificationType;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "ModificationFeature";
	}

	static std::string type() {
		return std::string("ModificationFeature");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idModificationFeature;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idModificationFeature;
        }

        ModificationFeature();

	ModificationFeature(const ModificationFeature & arg);

	ModificationFeature & operator =(const ModificationFeature & arg);

	~ModificationFeature();

	bool merge(ModificationFeature& object);
	bool update(PersistenceManager& manager);


	//get modificationType
	const UnipaxPtr<SequenceModificationVocabulary>::type getModificationType() const;

	UnipaxPtr<SequenceModificationVocabulary>::type getModificationType();

	void setModificationType(UnipaxPtr<SequenceModificationVocabulary>::type _modificationType);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef EntityFeature super;

};  //end class ModificationFeature

typedef UnipaxPtr<ModificationFeature>::type ModificationFeaturePtr;

}//end namespace UniPAX

#endif

#ifndef COVALENTBINDINGFEATURE_H
#define COVALENTBINDINGFEATURE_H
//Begin section for file CovalentBindingFeature.h
//TODO: Add definitions that you want preserved
//End section for file CovalentBindingFeature.h
#include<UNIPAX/KERNEL/BIOPAX/ModificationFeature.h>
#include<UNIPAX/KERNEL/BIOPAX/BindingFeature.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT CovalentBindingFeature : public BindingFeature
//#ifndef ODB_COMPILE     // exclude the next line for odb compiler
//, virtual public ModificationFeature
//#endif
{

	//Begin section for UniPAX::CovalentBindingFeature
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::CovalentBindingFeature

	//// uncomment for odb code generation !!!!
	//private:
	//	boost::shared_ptr<	SequenceModificationVocabulary> modificationType;

protected:

	UnipaxPtr<SequenceModificationVocabulary>::type modificationType;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "CovalentBindingFeature";
	}

	static std::string type() {
		return std::string("CovalentBindingFeature");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idCovalentBindingFeature;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idCovalentBindingFeature;
	}

	CovalentBindingFeature();

	CovalentBindingFeature(const CovalentBindingFeature & arg);

	CovalentBindingFeature & operator =(const CovalentBindingFeature & arg);

	~CovalentBindingFeature();

	bool merge(CovalentBindingFeature& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

	const UnipaxPtr<SequenceModificationVocabulary>::type getModificationType() const;

	UnipaxPtr<SequenceModificationVocabulary>::type getModificationType();

	void setModificationType(UnipaxPtr<SequenceModificationVocabulary>::type _modificationType);

private:
	typedef struct {
		typedef BindingFeature bindingFeature;
		//typedef ModificationFeature modificationFeature;
	} super;

};  //end class CovalentBindingFeature

typedef UnipaxPtr<CovalentBindingFeature>::type CovalentBindingFeaturePtr;

}//end namespace UniPAX

#endif

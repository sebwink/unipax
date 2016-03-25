#ifndef CONTROLLEDVOCABULARY_H
#define CONTROLLEDVOCABULARY_H
//Begin section for file ControlledVocabulary.h
//TODO: Add definitions that you want preserved
#include<string>
#include<vector>
//End section for file ControlledVocabulary.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT ControlledVocabulary : public UtilityClass {

	//Begin section for UniPAX::ControlledVocabulary
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::ControlledVocabulary

protected:

	std::string term;

	// std::vector<unsigned long long> id_xref;
	//#pragma db transient
	std::vector<UnipaxPtr<Xref>::type > xref;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "ControlledVocabulary";
	}

	static std::string type() {
		return std::string("ControlledVocabulary");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idControlledVocabulary;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idControlledVocabulary;
	}

	ControlledVocabulary();

	ControlledVocabulary(const ControlledVocabulary & arg);

	ControlledVocabulary & operator =(const ControlledVocabulary & arg);

	~ControlledVocabulary();

	bool merge(ControlledVocabulary& object);
	bool update(PersistenceManager& manager);


	//get term
	const std::string & getTerm() const;

	std::string & getTerm();

	void setTerm(std::string _term);


	//get xref
	const std::vector<UnipaxPtr<Xref>::type > & getXrefs() const;

	std::vector<UnipaxPtr<Xref>::type > & getXrefs();

	void setXrefs(std::vector<UnipaxPtr<Xref>::type > _xrefs);

	void addXref(UnipaxPtr<Xref>::type  _xref);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef UtilityClass super;

};  //end class ControlledVocabulary

typedef UnipaxPtr<ControlledVocabulary>::type ControlledVocabularyPtr;

}//end namespace UniPAX

#endif

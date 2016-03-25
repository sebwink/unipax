#ifndef SBASE_H
#define SBASE_H
//Begin section for file SBase.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file SBase.h
#include<UNIPAX/KERNEL/EXT/UIBase.h>
//#include<UNIPAX/KERNEL/EXT/ImportSource.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object abstract
class UNIPAX_EXPORT SBase : public UIBase {

protected:

	std::string metaId;

	std::string sboTerm;

	std::string notes;

	std::string annotation;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

//	virtual std::string getType() {
//		return "SBase";
//	}
//
//	static std::string type() {
//		return std::string("SBase");
//	}
//
//	virtual UniPAX::ClassType::ID getTypeID() {
//		return UniPAX::ClassType::idSBase;
//	}
//
//	static UniPAX::ClassType::ID typeID() {
//		return UniPAX::ClassType::idSBase;
//	}

	SBase();

	SBase(const SBase & arg);

	SBase & operator =(const SBase & arg);

	virtual ~SBase();

	bool merge(SBase& object);

	bool update(PersistenceManager& manager);

	//get metaId
	const std::string & getMetaId() const;

	std::string & getMetaId();

	void setMetaId(std::string _metaId);

	//get sboTerm
	const std::string & getSboTerm() const;

	std::string & getSboTerm();

	void setSboTerm(std::string _sboTerm);

	//get Notes
	const std::string & getNotes() const;

	std::string & getNotes();

	void setNotes(std::string _notes);

	//get Annotation
	const std::string & getAnnotation() const;

	std::string & getAnnotation();

	void setAnnotation(std::string _annotation);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class SBase

typedef UnipaxPtr<SBase>::type SBasePtr;

}//end namespace UniPAX

#endif

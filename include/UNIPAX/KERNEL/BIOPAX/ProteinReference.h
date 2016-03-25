#ifndef PROTEINREFERENCE_H
#define PROTEINREFERENCE_H
//Begin section for file ProteinReference.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file ProteinReference.h
#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT ProteinReference : public EntityReference {

protected:

	std::string sequence;

	UnipaxPtr<BioSource>::type organism;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "ProteinReference";
	}

	static std::string type() {
		return std::string("ProteinReference");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idProteinReference;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idProteinReference;
	}

	ProteinReference();

	ProteinReference(const ProteinReference & arg);

	ProteinReference & operator =(const ProteinReference & arg);

	~ProteinReference();

	bool merge(ProteinReference& object);
	bool update(PersistenceManager& manager);


	//get sequence
	const std::string & getSequence() const;

	std::string & getSequence();

	void setSequence(std::string _sequence);

	//get organism
	const UnipaxPtr<BioSource>::type getOrganism() const;

	UnipaxPtr<BioSource>::type getOrganism();

	void setOrganism(UnipaxPtr<BioSource>::type _organism);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef EntityReference super;

};  //end class ProteinReference

typedef UnipaxPtr<ProteinReference>::type ProteinReferencePtr;

}//end namespace UniPAX

#endif

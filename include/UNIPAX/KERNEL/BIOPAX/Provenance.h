#ifndef PROVENANCE_H
#define PROVENANCE_H

#include<vector>
#include<string>

#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>


namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Provenance : public UtilityClass {

protected:

	// std::vector<unsigned long long> id_xref;

//#pragma db transient
	std::vector<UnipaxPtr<UniPAX::Xref>::type > xref;

	std::vector<std::string> name;
	std::string standardName;
	std::string displayName;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Provenance";
	}

	static std::string type() {
		return std::string("Provenance");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idProvenance;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idProvenance;
        }

        Provenance();

	Provenance(const Provenance & arg);

	Provenance & operator =(const Provenance & arg);

	~Provenance();

	bool merge(Provenance& object);
	bool update(PersistenceManager& manager);


	//get xref
	const std::vector<UnipaxPtr<UniPAX::Xref>::type > & getXrefs() const;

	std::vector<UnipaxPtr<UniPAX::Xref>::type > & getXrefs();

	void addXref(UnipaxPtr<UniPAX::Xref>::type  _xref);

	void setXrefs(std::vector<UnipaxPtr<UniPAX::Xref>::type > _xrefs);


	std::vector<std::string>& getNames();

	const std::vector<std::string>& getNames() const;

	std::string getFirstName();

	void setNames(std::vector<std::string>& names);

	void addName(std::string name);


	const std::string & getStandardName() const;

	std::string & getStandardName();

	void setStandardName(std::string _name);


	const std::string & getDisplayName() const;

	std::string & getDisplayName();

	void setDisplayName(std::string _name);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef UtilityClass super;

};  //end class Provenance

typedef UnipaxPtr<Provenance>::type ProvenancePtr;

}//end namespace UniPAX

#endif

#ifndef UNIFICATIONXREF_H
#define UNIFICATIONXREF_H
//Begin section for file UnificationXref.h
//TODO: Add definitions that you want preserved
//End section for file UnificationXref.h
#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<string>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT UnificationXref : public Xref {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "UnificationXref";
	}

	static std::string type() {
		return std::string("UnificationXref");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idUnificationXref;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idUnificationXref;
        }

        UnificationXref();

	UnificationXref(const UnificationXref & arg);

	UnificationXref & operator =(const UnificationXref & arg);

	~UnificationXref();

	bool merge(UnificationXref& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Xref super;

};  //end class UnificationXref

typedef UnipaxPtr<UnificationXref>::type UnificationXrefPtr;

}//end namespace UniPAX

#endif

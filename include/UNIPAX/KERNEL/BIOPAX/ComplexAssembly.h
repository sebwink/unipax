#ifndef COMPLEXASSEMBLY_H
#define COMPLEXASSEMBLY_H
//Begin section for file ComplexAssembly.h
//TODO: Add definitions that you want preserved
//End section for file ComplexAssembly.h
#include<UNIPAX/KERNEL/BIOPAX/Conversion.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT ComplexAssembly : public Conversion {

	//Begin section for UniPAX::ComplexAssembly
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::ComplexAssembly

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "ComplexAssembly";
	}

	static std::string type() {
		return std::string("ComplexAssembly");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idComplexAssembly;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idComplexAssembly;
        }

        ComplexAssembly();

	ComplexAssembly(const ComplexAssembly & arg);

	ComplexAssembly & operator =(const ComplexAssembly & arg);

	~ComplexAssembly();

	bool merge(ComplexAssembly& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Conversion super;

};  //end class ComplexAssembly

typedef UnipaxPtr<ComplexAssembly>::type ComplexAssemblyPtr;

}//end namespace UniPAX

#endif

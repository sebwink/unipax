#ifndef SEQUENCELOCATION_H
#define SEQUENCELOCATION_H
//Begin section for file SequenceLocation.h
//TODO: Add definitions that you want preserved
//End section for file SequenceLocation.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT SequenceLocation : public UtilityClass {

protected:

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "SequenceLocation";
	}

	static std::string type() {
		return std::string("SequenceLocation");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idSequenceLocation;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idSequenceLocation;
        }

        SequenceLocation();

	SequenceLocation(const SequenceLocation & arg);

	SequenceLocation & operator =(const SequenceLocation & arg);

	~SequenceLocation();

	bool merge(SequenceLocation& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef UtilityClass super;

};  //end class SequenceLocation

typedef UnipaxPtr<SequenceLocation>::type SequenceLocationPtr;

}//end namespace UniPAX

#endif

#ifndef DEGRADATION_H
#define DEGRADATION_H
//Begin section for file Degradation.h
//TODO: Add definitions that you want preserved
//End section for file Degradation.h
#include<UNIPAX/KERNEL/BIOPAX/Conversion.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Degradation : public Conversion {

	//Begin section for UniPAX::Degradation
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::Degradation

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Degradation";
	}

	static std::string type() {
		return std::string("Degradation");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idDegradation;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idDegradation;
        }

        Degradation();

	Degradation(const Degradation & arg);

	Degradation & operator =(const Degradation & arg);

	~Degradation();

	bool merge(Degradation& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Conversion super;

};  //end class Degradation

typedef UnipaxPtr<Degradation>::type DegradationPtr;

}//end namespace UniPAX

#endif

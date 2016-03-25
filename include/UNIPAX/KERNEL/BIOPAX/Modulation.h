#ifndef MODULATION_H
#define MODULATION_H
//Begin section for file Modulation.h
//TODO: Add definitions that you want preserved
//End section for file Modulation.h
#include<UNIPAX/KERNEL/BIOPAX/Control.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Modulation : public Control {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Modulation";
	}

	static std::string type() {
		return std::string("Modulation");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idModulation;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idModulation;
        }

        Modulation();

	Modulation(const Modulation & arg);

	Modulation & operator =(const Modulation & arg);

	~Modulation();

	bool merge(Modulation& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);
private:
    typedef Control super;
};  //end class Modulation

typedef UnipaxPtr<Modulation>::type ModulationPtr;

}//end namespace UniPAX

#endif

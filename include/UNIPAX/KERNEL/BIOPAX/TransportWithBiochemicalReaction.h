#ifndef TRANSPORTWITHBIOCHEMICALREACTION_H
#define TRANSPORTWITHBIOCHEMICALREACTION_H
//Begin section for file TransportWithBiochemicalReaction.h
//TODO: Add definitions that you want preserved
//End section for file TransportWithBiochemicalReaction.h
//#include<UNIPAX/KERNEL/BIOPAX/Transport.h>
#include<UNIPAX/KERNEL/BIOPAX/BiochemicalReaction.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT TransportWithBiochemicalReaction : public BiochemicalReaction
{

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "TransportWithBiochemicalReaction";
	}

	static std::string type() {
		return std::string("TransportWithBiochemicalReaction");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idTransportWithBiochemicalReaction;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idTransportWithBiochemicalReaction;
        }

        TransportWithBiochemicalReaction();

	TransportWithBiochemicalReaction(const TransportWithBiochemicalReaction & arg);

	TransportWithBiochemicalReaction & operator =(const TransportWithBiochemicalReaction & arg);

	~TransportWithBiochemicalReaction();

	bool merge(TransportWithBiochemicalReaction& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef struct {
//		typedef Transport transport;
		typedef BiochemicalReaction biochemicalReaction;
	} super;

};  //end class TransportWithBiochemicalReaction

typedef UnipaxPtr<TransportWithBiochemicalReaction>::type TransportWithBiochemicalReactionPtr;

}//end namespace UniPAX

#endif

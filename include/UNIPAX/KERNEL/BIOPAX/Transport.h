#ifndef TRANSPORT_H
#define TRANSPORT_H
//Begin section for file Transport.h
//TODO: Add definitions that you want preserved
//End section for file Transport.h
#include<UNIPAX/KERNEL/BIOPAX/Conversion.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Transport : public Conversion {

protected:

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Transport";
	}

	static std::string type() {
		return std::string("Transport");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idTransport;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idTransport;
        }

        Transport();

	Transport(const Transport & arg);

	Transport & operator =(const Transport & arg);

	~Transport();

	bool merge(Transport& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Conversion super;

};  //end class Transport

typedef UnipaxPtr<Transport>::type TransportPtr;

}//end namespace UniPAX

#endif

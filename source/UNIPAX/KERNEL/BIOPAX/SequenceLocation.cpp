#include<UNIPAX/KERNEL/BIOPAX/SequenceLocation.h>
#include<set>
//Begin section for file SequenceLocation.cpp
//TODO: Add definitions that you want preserved
//End section for file SequenceLocation.cpp

UniPAX::SequenceLocation::SequenceLocation() :UniPAX::UtilityClass()  {
    }

UniPAX::SequenceLocation::SequenceLocation(const SequenceLocation& arg) : UniPAX::UtilityClass(arg) {
    }

UniPAX::SequenceLocation & UniPAX::SequenceLocation::operator =(const SequenceLocation & arg)  {
	UniPAX::UtilityClass::operator=(arg);

	return *this;
}

UniPAX::SequenceLocation::~SequenceLocation()  {
    }

bool UniPAX::SequenceLocation::merge(SequenceLocation& object)
{
	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::SequenceLocation::update(PersistenceManager& manager)
{
	return UniPAX::UtilityClass::update(manager);
}

bool UniPAX::SequenceLocation::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	return false;

}



bool UniPAX::SequenceLocation::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::SequenceLocation::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	return;
//}

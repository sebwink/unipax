#include<UNIPAX/KERNEL/BIOPAX/Degradation.h>
#include<set>
//Begin section for file Degradation.cpp
//TODO: Add definitions that you want preserved
//End section for file Degradation.cpp

UniPAX::Degradation::Degradation() : UniPAX::Conversion() {
    }

UniPAX::Degradation::Degradation(const Degradation& arg) : UniPAX::Conversion(arg) {
    }

UniPAX::Degradation & UniPAX::Degradation::operator =(const Degradation & arg)  {
	UniPAX::Conversion::operator=(arg);

	return *this;
}

UniPAX::Degradation::~Degradation()  {
    }

bool UniPAX::Degradation::merge(Degradation& object)
{
	return UniPAX::Conversion::merge(object);
}

bool UniPAX::Degradation::update(PersistenceManager& manager)
{
	return UniPAX::Conversion::update(manager);
}

bool UniPAX::Degradation::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Conversion::setAttribute(attribute, value, manager))
		return true;

	// to handle non consistency in databases
	if (boost::iequals(attribute,"eCNumber"))
	{
		std::cout << "wrong eCNumber found - ignore" << std::endl;
		return true;
	}

	return false;

}

bool UniPAX::Degradation::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Conversion::getAttribute(value, manager))
		return false;

	return true;

}


//void UniPAX::Degradation::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Conversion::init(e,db);
//
//	return;
//}

#include<UNIPAX/KERNEL/BIOPAX/Modulation.h>
#include<set>
//Begin section for file Modulation.cpp
//TODO: Add definitions that you want preserved
//End section for file Modulation.cpp

UniPAX::Modulation::Modulation() : UniPAX::Control()  {
    }

UniPAX::Modulation::Modulation(const Modulation& arg) : UniPAX::Control(arg) {
    }

UniPAX::Modulation & UniPAX::Modulation::operator =(const Modulation & arg)  {
	UniPAX::Control::operator=(arg);

	return *this;
}

UniPAX::Modulation::~Modulation()  {
    }

bool UniPAX::Modulation::merge(Modulation& object)
{
	return UniPAX::Control::merge(object);
}

bool UniPAX::Modulation::update(PersistenceManager& manager)
{
	return UniPAX::Control::update(manager);
}


bool UniPAX::Modulation::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Control::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::Modulation::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Control::getAttribute(value, manager))
		return false;

	return false;
}

//void UniPAX::Modulation::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Control::init(e,db);
//
//	return;
//}

#include<UNIPAX/KERNEL/BIOPAX/Transport.h>
//Begin section for file Transport.cpp
//TODO: Add definitions that you want preserved
//End section for file Transport.cpp

UniPAX::Transport::Transport() : UniPAX::Conversion() {
    }

UniPAX::Transport::Transport(const Transport& arg) : UniPAX::Conversion(arg) {
    }

UniPAX::Transport & UniPAX::Transport::operator =(const Transport & arg)  {
	UniPAX::Conversion::operator=(arg);

	return *this;
}

UniPAX::Transport::~Transport()  {
    }

bool UniPAX::Transport::merge(Transport& object)
{
	return UniPAX::Conversion::merge(object);
}

bool UniPAX::Transport::update(PersistenceManager& manager)
{
	return UniPAX::Conversion::update(manager);
}


bool UniPAX::Transport::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Conversion::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::Transport::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Conversion::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::Transport::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Conversion::init(e,db);
//
//	return;
//}

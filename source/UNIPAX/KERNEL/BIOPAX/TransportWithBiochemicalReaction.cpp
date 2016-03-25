#include<UNIPAX/KERNEL/BIOPAX/TransportWithBiochemicalReaction.h>
//Begin section for file TransportWithBiochemicalReaction.cpp
//TODO: Add definitions that you want preserved
//End section for file TransportWithBiochemicalReaction.cpp

UniPAX::TransportWithBiochemicalReaction::TransportWithBiochemicalReaction() : UniPAX::BiochemicalReaction() {
}

UniPAX::TransportWithBiochemicalReaction::TransportWithBiochemicalReaction(const TransportWithBiochemicalReaction& arg) : UniPAX::BiochemicalReaction(arg)
{
}

UniPAX::TransportWithBiochemicalReaction & UniPAX::TransportWithBiochemicalReaction::operator =(const TransportWithBiochemicalReaction & arg)  {
	UniPAX::BiochemicalReaction::operator=(arg);
	//	UniPAX::Transport::operator=(arg);

	return *this;
}

UniPAX::TransportWithBiochemicalReaction::~TransportWithBiochemicalReaction()  {
}

bool UniPAX::TransportWithBiochemicalReaction::merge(TransportWithBiochemicalReaction& object)
{
	return UniPAX::BiochemicalReaction::merge(object);
}

bool UniPAX::TransportWithBiochemicalReaction::update(PersistenceManager& manager)
{
	return UniPAX::BiochemicalReaction::update(manager);
}


bool UniPAX::TransportWithBiochemicalReaction::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::BiochemicalReaction::setAttribute(attribute, value, manager))
		return true;
	//	if (UniPAX::Transport::setAttribute(attribute, value, manager))
	//		return true;


	return false;

}

bool UniPAX::TransportWithBiochemicalReaction::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::BiochemicalReaction::getAttribute(value, manager))
		return false;
	//	if (!UniPAX::Transport::getAttribute(value, manager))
	//		return false;

	return true;

}

//void UniPAX::TransportWithBiochemicalReaction::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::BiochemicalReaction::init(e,db);
//	UniPAX::Transport::init(e,db);
//
//	return;
//}

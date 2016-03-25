#include<UNIPAX/KERNEL/BIOPAX/MolecularInteraction.h>
#include<set>
//Begin section for file MolecularInteraction.cpp
//TODO: Add definitions that you want preserved
//End section for file MolecularInteraction.cpp

UniPAX::MolecularInteraction::MolecularInteraction() : UniPAX::Interaction() {
    }

UniPAX::MolecularInteraction::MolecularInteraction(const MolecularInteraction& arg) : UniPAX::Interaction(arg) {
    }

UniPAX::MolecularInteraction & UniPAX::MolecularInteraction::operator =(const MolecularInteraction & arg)  {
	UniPAX::Interaction::operator=(arg);

	return *this;
}

UniPAX::MolecularInteraction::~MolecularInteraction()  {
    }

bool UniPAX::MolecularInteraction::merge(MolecularInteraction& object)
{
	return UniPAX::Interaction::merge(object);
}

bool UniPAX::MolecularInteraction::update(PersistenceManager& manager)
{
	return UniPAX::Interaction::update(manager);
}


bool UniPAX::MolecularInteraction::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Interaction::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::MolecularInteraction::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Interaction::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::MolecularInteraction::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Interaction::init(e,db);
//
//	return;
//}

#include<UNIPAX/KERNEL/BIOPAX/InteractionVocabulary.h>
#include<set>
//Begin section for file InteractionVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file InteractionVocabulary.cpp

UniPAX::InteractionVocabulary::InteractionVocabulary() : UniPAX::ControlledVocabulary() {
    }

UniPAX::InteractionVocabulary::InteractionVocabulary(const InteractionVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    }

UniPAX::InteractionVocabulary & UniPAX::InteractionVocabulary::operator =(const InteractionVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::InteractionVocabulary::~InteractionVocabulary()  {
    }

bool UniPAX::InteractionVocabulary::merge(InteractionVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::InteractionVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}


bool UniPAX::InteractionVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::InteractionVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	return true;

}


//void UniPAX::InteractionVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

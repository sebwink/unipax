#include<UNIPAX/KERNEL/BIOPAX/RelationshipTypeVocabulary.h>
#include<set>
//Begin section for file RelationshipTypeVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file RelationshipTypeVocabulary.cpp

UniPAX::RelationshipTypeVocabulary::RelationshipTypeVocabulary() : UniPAX::ControlledVocabulary() {
    }

UniPAX::RelationshipTypeVocabulary::RelationshipTypeVocabulary(const RelationshipTypeVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    }

UniPAX::RelationshipTypeVocabulary & UniPAX::RelationshipTypeVocabulary::operator =(const RelationshipTypeVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::RelationshipTypeVocabulary::~RelationshipTypeVocabulary()  {
    }

bool UniPAX::RelationshipTypeVocabulary::merge(RelationshipTypeVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::RelationshipTypeVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}


bool UniPAX::RelationshipTypeVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}


bool UniPAX::RelationshipTypeVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::RelationshipTypeVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

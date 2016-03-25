#include<UNIPAX/KERNEL/BIOPAX/EntityReferenceTypeVocabulary.h>
#include<set>
//Begin section for file EntityReferenceTypeVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file EntityReferenceTypeVocabulary.cpp

UniPAX::EntityReferenceTypeVocabulary::EntityReferenceTypeVocabulary() :
UniPAX::ControlledVocabulary() {
    }

UniPAX::EntityReferenceTypeVocabulary::EntityReferenceTypeVocabulary(const EntityReferenceTypeVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    }

UniPAX::EntityReferenceTypeVocabulary & UniPAX::EntityReferenceTypeVocabulary::operator =(const EntityReferenceTypeVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::EntityReferenceTypeVocabulary::~EntityReferenceTypeVocabulary()  {
    }

bool UniPAX::EntityReferenceTypeVocabulary::merge(EntityReferenceTypeVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::EntityReferenceTypeVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}

bool UniPAX::EntityReferenceTypeVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::EntityReferenceTypeVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	return true;

}


//void UniPAX::EntityReferenceTypeVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

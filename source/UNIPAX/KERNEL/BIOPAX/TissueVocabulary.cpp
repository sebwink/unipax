#include<UNIPAX/KERNEL/BIOPAX/TissueVocabulary.h>
//Begin section for file TissueVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file TissueVocabulary.cpp

UniPAX::TissueVocabulary::TissueVocabulary() : UniPAX::ControlledVocabulary() {
    }

UniPAX::TissueVocabulary::TissueVocabulary(const TissueVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    }

UniPAX::TissueVocabulary & UniPAX::TissueVocabulary::operator =(const TissueVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::TissueVocabulary::~TissueVocabulary()  {
    }

bool UniPAX::TissueVocabulary::merge(TissueVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::TissueVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}

bool UniPAX::TissueVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::TissueVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::TissueVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

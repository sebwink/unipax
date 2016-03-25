#include<UNIPAX/KERNEL/BIOPAX/CellVocabulary.h>
#include<set>
//Begin section for file CellVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file CellVocabulary.cpp

UniPAX::CellVocabulary::CellVocabulary() : UniPAX::ControlledVocabulary() {
    }

UniPAX::CellVocabulary::CellVocabulary(const CellVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    }

UniPAX::CellVocabulary & UniPAX::CellVocabulary::operator =(const CellVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::CellVocabulary::~CellVocabulary()  {
    }



bool UniPAX::CellVocabulary::merge(CellVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}


bool UniPAX::CellVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}


bool UniPAX::CellVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}


bool UniPAX::CellVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::CellVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

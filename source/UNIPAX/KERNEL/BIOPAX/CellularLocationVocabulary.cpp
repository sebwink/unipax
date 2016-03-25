#include<UNIPAX/KERNEL/BIOPAX/CellularLocationVocabulary.h>
#include<set>
//Begin section for file CellularLocationVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file CellularLocationVocabulary.cpp

UniPAX::CellularLocationVocabulary::CellularLocationVocabulary() : UniPAX::ControlledVocabulary() {
}

UniPAX::CellularLocationVocabulary::CellularLocationVocabulary(const CellularLocationVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
}

UniPAX::CellularLocationVocabulary & UniPAX::CellularLocationVocabulary::operator =(const CellularLocationVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::CellularLocationVocabulary::~CellularLocationVocabulary()  {
}



bool UniPAX::CellularLocationVocabulary::merge(CellularLocationVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::CellularLocationVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}

bool UniPAX::CellularLocationVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}


bool UniPAX::CellularLocationVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;


	return true;

}

//void UniPAX::CellularLocationVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

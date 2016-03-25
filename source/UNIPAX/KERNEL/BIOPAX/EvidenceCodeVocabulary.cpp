#include<UNIPAX/KERNEL/BIOPAX/EvidenceCodeVocabulary.h>
#include<set>
//Begin section for file EvidenceCodeVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file EvidenceCodeVocabulary.cpp

UniPAX::EvidenceCodeVocabulary::EvidenceCodeVocabulary() : UniPAX::ControlledVocabulary() {
    }

UniPAX::EvidenceCodeVocabulary::EvidenceCodeVocabulary(const EvidenceCodeVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    }

UniPAX::EvidenceCodeVocabulary & UniPAX::EvidenceCodeVocabulary::operator =(const EvidenceCodeVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::EvidenceCodeVocabulary::~EvidenceCodeVocabulary()  {
    }

bool UniPAX::EvidenceCodeVocabulary::merge(EvidenceCodeVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::EvidenceCodeVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}


bool UniPAX::EvidenceCodeVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::EvidenceCodeVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::EvidenceCodeVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

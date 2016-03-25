#include<UNIPAX/KERNEL/BIOPAX/SequenceRegionVocabulary.h>
#include<set>
//Begin section for file SequenceRegionVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file SequenceRegionVocabulary.cpp

UniPAX::SequenceRegionVocabulary::SequenceRegionVocabulary() : UniPAX::ControlledVocabulary() {
    }

UniPAX::SequenceRegionVocabulary::SequenceRegionVocabulary(const SequenceRegionVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    }

UniPAX::SequenceRegionVocabulary & UniPAX::SequenceRegionVocabulary::operator =(const SequenceRegionVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::SequenceRegionVocabulary::~SequenceRegionVocabulary()  {
    }

bool UniPAX::SequenceRegionVocabulary::merge(SequenceRegionVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::SequenceRegionVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}

bool UniPAX::SequenceRegionVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}



bool UniPAX::SequenceRegionVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::SequenceRegionVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

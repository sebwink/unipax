#include<UNIPAX/KERNEL/BIOPAX/SequenceModificationVocabulary.h>
#include<set>
//Begin section for file SequenceModificationVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file SequenceModificationVocabulary.cpp

UniPAX::SequenceModificationVocabulary::SequenceModificationVocabulary() : UniPAX::ControlledVocabulary() {
    }

UniPAX::SequenceModificationVocabulary::SequenceModificationVocabulary(const SequenceModificationVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    }

UniPAX::SequenceModificationVocabulary & UniPAX::SequenceModificationVocabulary::operator =(const SequenceModificationVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::SequenceModificationVocabulary::~SequenceModificationVocabulary()  {
    }

bool UniPAX::SequenceModificationVocabulary::merge(SequenceModificationVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::SequenceModificationVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}

bool UniPAX::SequenceModificationVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::SequenceModificationVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::SequenceModificationVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

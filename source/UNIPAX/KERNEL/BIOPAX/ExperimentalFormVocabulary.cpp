#include<UNIPAX/KERNEL/BIOPAX/ExperimentalFormVocabulary.h>
#include<set>
//Begin section for file ExperimentalFormVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file ExperimentalFormVocabulary.cpp

UniPAX::ExperimentalFormVocabulary::ExperimentalFormVocabulary() :
UniPAX::ControlledVocabulary() {
    }

UniPAX::ExperimentalFormVocabulary::ExperimentalFormVocabulary(const ExperimentalFormVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    }

UniPAX::ExperimentalFormVocabulary & UniPAX::ExperimentalFormVocabulary::operator =(const ExperimentalFormVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);

	return *this;
}

UniPAX::ExperimentalFormVocabulary::~ExperimentalFormVocabulary()  {
    }

bool UniPAX::ExperimentalFormVocabulary::merge(ExperimentalFormVocabulary& object)
{
	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::ExperimentalFormVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}

bool UniPAX::ExperimentalFormVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::ExperimentalFormVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::ExperimentalFormVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}


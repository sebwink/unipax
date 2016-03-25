#include<UNIPAX/KERNEL/BIOPAX/TemplateReactionRegulation.h>
#include<set>
//Begin section for file TemplateReactionRegulation.cpp
//TODO: Add definitions that you want preserved
//End section for file TemplateReactionRegulation.cpp

UniPAX::TemplateReactionRegulation::TemplateReactionRegulation() : UniPAX::Control() {
    }

UniPAX::TemplateReactionRegulation::TemplateReactionRegulation(const TemplateReactionRegulation& arg) : UniPAX::Control(arg) {
    }

UniPAX::TemplateReactionRegulation & UniPAX::TemplateReactionRegulation::operator =(const TemplateReactionRegulation & arg)  {
	UniPAX::Control::operator=(arg);

	return *this;
}

UniPAX::TemplateReactionRegulation::~TemplateReactionRegulation()  {
    }

bool UniPAX::TemplateReactionRegulation::merge(TemplateReactionRegulation& object)
{
	return UniPAX::Control::merge(object);
}

bool UniPAX::TemplateReactionRegulation::update(PersistenceManager& manager)
{
	return UniPAX::Control::update(manager);
}

bool UniPAX::TemplateReactionRegulation::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Control::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::TemplateReactionRegulation::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Control::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::TemplateReactionRegulation::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Control::init(e,db);
//
//	return;
//}

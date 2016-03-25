#include<UNIPAX/KERNEL/BIOPAX/CovalentBindingFeature.h>
#include<set>
//Begin section for file CovalentBindingFeature.cpp
//TODO: Add definitions that you want preserved
//End section for file CovalentBindingFeature.cpp

UniPAX::CovalentBindingFeature::CovalentBindingFeature() : UniPAX::BindingFeature() {
    }

UniPAX::CovalentBindingFeature::CovalentBindingFeature(const CovalentBindingFeature& arg) : UniPAX::BindingFeature(arg)
{
    }

UniPAX::CovalentBindingFeature & UniPAX::CovalentBindingFeature::operator =(const CovalentBindingFeature & arg)  {
//	UniPAX::ModificationFeature::operator=(arg);
	UniPAX::BindingFeature::operator=(arg);

	return *this;
}

UniPAX::CovalentBindingFeature::~CovalentBindingFeature()  {
    }

bool UniPAX::CovalentBindingFeature::merge(CovalentBindingFeature& object)
{
	return UniPAX::BindingFeature::merge(object);
}


bool UniPAX::CovalentBindingFeature::update(PersistenceManager& manager)
{
	return UniPAX::BindingFeature::update(manager);
}


const boost::shared_ptr<UniPAX::SequenceModificationVocabulary> UniPAX::CovalentBindingFeature::getModificationType() const {
        return modificationType;
}

boost::shared_ptr<UniPAX::SequenceModificationVocabulary> UniPAX::CovalentBindingFeature::getModificationType() {
	return modificationType;
}

void UniPAX::CovalentBindingFeature::setModificationType(boost::shared_ptr<UniPAX::SequenceModificationVocabulary> _modificationType) {
	modificationType = _modificationType;
}

bool UniPAX::CovalentBindingFeature::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::BindingFeature::setAttribute(attribute, value, manager))
		return true;


	if (boost::iequals(attribute,"modificationType"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "ModificationFeature::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		modificationType = boost::dynamic_pointer_cast<UniPAX::SequenceModificationVocabulary>(object);
		return true;
	}

	return false;

}

bool UniPAX::CovalentBindingFeature::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::BindingFeature::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (modificationType == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#modificationType", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(modificationType,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#modificationType", tmp));

	}

	return true;

}

//void UniPAX::CovalentBindingFeature::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ModificationFeature::init(e,db);
//	UniPAX::BindingFeature::init(e,db);
//
//	return;
//}

#include<UNIPAX/KERNEL/BIOPAX/ModificationFeature.h>
#include<set>
//Begin section for file ModificationFeature.cpp
//TODO: Add definitions that you want preserved
//End section for file ModificationFeature.cpp

UniPAX::ModificationFeature::ModificationFeature() :
UniPAX::EntityFeature()
//, modificationType(0)
{
    }

UniPAX::ModificationFeature::ModificationFeature(const ModificationFeature & arg) : UniPAX::EntityFeature(arg) ,
    modificationType(arg.modificationType)
{}

UniPAX::ModificationFeature & UniPAX::ModificationFeature::operator =(const ModificationFeature & arg)  {
	UniPAX::EntityFeature::operator=(arg);
	modificationType = arg.modificationType;

	return *this;
}

UniPAX::ModificationFeature::~ModificationFeature()  {
    }

bool UniPAX::ModificationFeature::merge(ModificationFeature& object)
{
	if (modificationType != 0)
	{
		if (object.getModificationType() != 0)
		{
			if (modificationType->getUnipaxId() != object.getModificationType()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::ModificationFeature::modificationType not equal ..."
						<< modificationType->getUnipaxId() << " != " << object.getModificationType()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setModificationType(object.getModificationType());
	}

	return UniPAX::EntityFeature::merge(object);
}

bool UniPAX::ModificationFeature::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getModificationType()))
	{
		setModificationType(boost::dynamic_pointer_cast<SequenceModificationVocabulary>(manager.getMergedObject(getModificationType())));
	}

	return UniPAX::EntityFeature::update(manager);
}


const boost::shared_ptr<UniPAX::SequenceModificationVocabulary> UniPAX::ModificationFeature::getModificationType() const {
        return modificationType;
}

boost::shared_ptr<UniPAX::SequenceModificationVocabulary> UniPAX::ModificationFeature::getModificationType() {
	return modificationType;
}

void UniPAX::ModificationFeature::setModificationType(boost::shared_ptr<UniPAX::SequenceModificationVocabulary> _modificationType) {
	modificationType = _modificationType;
}

bool UniPAX::ModificationFeature::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::EntityFeature::setAttribute(attribute, value, manager))
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

bool UniPAX::ModificationFeature::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::EntityFeature::getAttribute(value, manager))
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


//void UniPAX::ModificationFeature::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::EntityFeature::init(e,db);
//
//	return;
//}

#include<UNIPAX/KERNEL/BIOPAX/RnaReference.h>
#include<set>
//Begin section for file RnaReference.cpp
//TODO: Add definitions that you want preserved
//End section for file RnaReference.cpp

UniPAX::RnaReference::RnaReference() : UniPAX::EntityReference()
//	subRegion(0),
//	organism(0),
//	id_subRegion(0)
{
    }

UniPAX::RnaReference::RnaReference(const RnaReference & arg) : UniPAX::EntityReference(arg) ,
    sequence(arg.sequence),
	subRegion(arg.subRegion),
	organism(arg.organism)
//	id_subRegion(arg.id_subRegion)
{}

UniPAX::RnaReference & UniPAX::RnaReference::operator =(const RnaReference & arg)  {
	UniPAX::EntityReference::operator=(arg);
   	sequence = arg.sequence;
	subRegion = arg.subRegion;
	organism = arg.organism;
//	id_subRegion = arg.id_subRegion;

	return *this;
}

UniPAX::RnaReference::~RnaReference()  {
    }

bool UniPAX::RnaReference::merge(RnaReference& object)
{
	if (subRegion != 0)
	{
		if (object.getSubRegion() != 0)
		{
			if (subRegion->getUnipaxId() != object.getSubRegion()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::RnaReference::subRegion not equal ..."
						<< subRegion->getUnipaxId() << " != " << object.getSubRegion()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setSubRegion(object.getSubRegion());
	}

	if (organism != 0)
	{
		if (object.getOrganism() != 0)
		{
			if (organism->getUnipaxId() != object.getOrganism()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::RnaReference::organism not equal ..."
						<< organism->getUnipaxId() << " != " << object.getOrganism()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setOrganism(object.getOrganism());
	}
	if (!object.getSequence().empty())
	{
		if (!getSequence().empty())
		{
			if (getSequence() != object.getSequence())
			{
				std::cerr << "Error during merging: UniPAX::RnaReference::sequence not equal ..."
						<< getSequence() << " != " << object.getSequence() << std::endl;
				return false;
			}
		}
		else
			setSequence(object.getSequence());
	}


	return UniPAX::EntityReference::merge(object);
}

bool UniPAX::RnaReference::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getOrganism()))
	{
		setOrganism(boost::dynamic_pointer_cast<BioSource>(manager.getMergedObject(getOrganism())));
	}
	if (manager.isMerged(getSubRegion()))
	{
		setSubRegion(boost::dynamic_pointer_cast<EntityReference>(manager.getMergedObject(getSubRegion())));
	}

	return UniPAX::EntityReference::update(manager);
}

const std::string & UniPAX::RnaReference::getSequence() const {
        return sequence;
}

std::string & UniPAX::RnaReference::getSequence() {
	return sequence;
}

void UniPAX::RnaReference::setSequence(std::string _sequence) {
	sequence = _sequence;
}

const boost::shared_ptr<UniPAX::BioSource> UniPAX::RnaReference::getOrganism() const {
        return organism;
}

boost::shared_ptr<UniPAX::BioSource> UniPAX::RnaReference::getOrganism() {
	return organism;
}

void UniPAX::RnaReference::setOrganism(boost::shared_ptr<UniPAX::BioSource> _organism) {
	organism = _organism;
}

const boost::shared_ptr<UniPAX::EntityReference> UniPAX::RnaReference::getSubRegion() const {
	return subRegion;
}

boost::shared_ptr<UniPAX::EntityReference> UniPAX::RnaReference::getSubRegion() {
        return subRegion;
}

void UniPAX::RnaReference::setSubRegion(boost::shared_ptr<UniPAX::EntityReference> _subRegion) {
    	subRegion = _subRegion;
}

bool UniPAX::RnaReference::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::EntityReference::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"subRegion"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "RnaReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		subRegion = boost::dynamic_pointer_cast<UniPAX::EntityReference>(object);
		return true;
	}
	if (boost::iequals(attribute,"organism"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "RnaReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		organism = boost::dynamic_pointer_cast<UniPAX::BioSource>(object);
		return true;
	}
	if (boost::iequals(attribute,"sequence"))
	{
		setSequence(value);
		return true;
	}

	return false;

}



bool UniPAX::RnaReference::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::EntityReference::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (subRegion == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#subRegion", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(subRegion,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#subRegion", tmp));

	}
	tmp.clear();
	if (organism == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#organism", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(organism,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#organism", tmp));

	}
	if (!getSequence().empty())
		value.push_back(std::pair<std::string,std::string>("sequence", getSequence()));

	return true;

}

//void UniPAX::RnaReference::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::EntityReference::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		subRegion = boost::dynamic_pointer_cast<UniPAX::EntityReference>(getObjectByID(db, id_subRegion));
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		if (subRegion != 0)
//			id_subRegion = subRegion->getUnipaxId();
//
//	}
//
//	return;
//}

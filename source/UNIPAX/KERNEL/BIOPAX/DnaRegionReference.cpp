#include<UNIPAX/KERNEL/BIOPAX/DnaRegionReference.h>
#include<set>
//Begin section for file DnaRegionReference.cpp
//TODO: Add definitions that you want preserved
//End section for file DnaRegionReference.cpp

UniPAX::DnaRegionReference::DnaRegionReference() : UniPAX::EntityReference()
//	regionType(0),
//	organism(0),
//	absoluteRegion(0),
//	subRegion(0),
//	id_absoluteRegion(0),
//	id_subRegion(0)
{
    }

UniPAX::DnaRegionReference::DnaRegionReference(const DnaRegionReference& arg) : UniPAX::EntityReference(arg) ,
			regionType(arg.regionType),
			organism(arg.organism),
			absoluteRegion(arg.absoluteRegion),
			subRegion(arg.subRegion)
//			id_absoluteRegion(arg.id_absoluteRegion),
//			id_subRegion(arg.id_subRegion)
{
}

UniPAX::DnaRegionReference & UniPAX::DnaRegionReference::operator =(const DnaRegionReference & arg)  {
	UniPAX::EntityReference::operator=(arg);
    sequence = arg.sequence;
	regionType = arg.regionType;
	organism = arg.organism;
	absoluteRegion = arg.absoluteRegion;
    subRegion = arg.subRegion;
//    id_absoluteRegion = arg.id_absoluteRegion;
//    id_subRegion = arg.id_subRegion;

	return *this;
}

UniPAX::DnaRegionReference::~DnaRegionReference()  {
    }

bool UniPAX::DnaRegionReference::merge(DnaRegionReference& object)
{
	if (subRegion != 0)
	{
		if (object.getSubRegion() != 0)
		{
			if (subRegion->getUnipaxId() != object.getSubRegion()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::DnaRegionReference::subRegion not equal ..."
						<< subRegion->getUnipaxId() << " != " << object.getSubRegion()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setSubRegion(object.getSubRegion());
	}
	if (regionType != 0)
	{
		if (object.getRegionType() != 0)
		{
			if (regionType->getUnipaxId() != object.getRegionType()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::DnaRegionReference::regionType not equal ..."
						<< regionType->getUnipaxId() << " != " << object.getRegionType()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setRegionType(object.getRegionType());
	}

	if (organism != 0)
	{
		if (object.getOrganism() != 0)
		{
			if (organism->getUnipaxId() != object.getOrganism()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::DnaRegionReference::organism not equal ..."
						<< organism->getUnipaxId() << " != " << object.getOrganism()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setOrganism(object.getOrganism());
	}
	if (absoluteRegion != 0)
	{
		if (object.getAbsoluteRegion() != 0)
		{
			if (absoluteRegion->getUnipaxId() != object.getAbsoluteRegion()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::DnaRegionReference::absoluteRegion not equal ..."
						<< absoluteRegion->getUnipaxId() << " != " << object.getAbsoluteRegion()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setAbsoluteRegion(object.getAbsoluteRegion());
	}

	if (!object.getSequence().empty())
	{
		if (!getSequence().empty())
		{
			if (getSequence() != object.getSequence())
			{
				std::cerr << "Error during merging: UniPAX::DnaRegionReference::sequence not equal ..."
						<< getSequence() << " != " << object.getSequence() << std::endl;
				return false;
			}
		}
		else
			setSequence(object.getSequence());
	}

	return UniPAX::EntityReference::merge(object);
}

bool UniPAX::DnaRegionReference::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getRegionType()))
	{
		setRegionType(boost::dynamic_pointer_cast<SequenceRegionVocabulary>(manager.getMergedObject(getRegionType())));
	}
	if (manager.isMerged(getOrganism()))
	{
		setOrganism(boost::dynamic_pointer_cast<BioSource>(manager.getMergedObject(getOrganism())));
	}
	if (manager.isMerged(getAbsoluteRegion()))
	{
		setAbsoluteRegion(boost::dynamic_pointer_cast<SequenceLocation>(manager.getMergedObject(getAbsoluteRegion())));
	}
	if (manager.isMerged(getSubRegion()))
	{
		setSubRegion(boost::dynamic_pointer_cast<EntityReference>(manager.getMergedObject(getSubRegion())));
	}

	return UniPAX::EntityReference::update(manager);
}


const std::string & UniPAX::DnaRegionReference::getSequence() const {
        return sequence;
}

std::string & UniPAX::DnaRegionReference::getSequence() {
	return sequence;
}

void UniPAX::DnaRegionReference::setSequence(std::string _sequence) {
	sequence = _sequence;
}

const boost::shared_ptr<UniPAX::SequenceRegionVocabulary> UniPAX::DnaRegionReference::getRegionType() const {
        return regionType;
}

boost::shared_ptr<UniPAX::SequenceRegionVocabulary> UniPAX::DnaRegionReference::getRegionType() {
	return regionType;
}

void UniPAX::DnaRegionReference::setRegionType(boost::shared_ptr<UniPAX::SequenceRegionVocabulary> _regionType) {
	regionType = _regionType;
}

const boost::shared_ptr<UniPAX::BioSource> UniPAX::DnaRegionReference::getOrganism() const {
        return organism;
}

boost::shared_ptr<UniPAX::BioSource> UniPAX::DnaRegionReference::getOrganism() {
	return organism;
}

void UniPAX::DnaRegionReference::setOrganism(boost::shared_ptr<UniPAX::BioSource> _organism) {
	organism = _organism;
}

const boost::shared_ptr<UniPAX::SequenceLocation> UniPAX::DnaRegionReference::getAbsoluteRegion() const {
        return absoluteRegion;
}

boost::shared_ptr<UniPAX::SequenceLocation> UniPAX::DnaRegionReference::getAbsoluteRegion() {
	return absoluteRegion;
}

void UniPAX::DnaRegionReference::setAbsoluteRegion(boost::shared_ptr<UniPAX::SequenceLocation> _absoluteRegion) {
	absoluteRegion = _absoluteRegion;
}

const boost::shared_ptr<UniPAX::EntityReference> UniPAX::DnaRegionReference::getSubRegion() const {
	return subRegion;
}

boost::shared_ptr<UniPAX::EntityReference> UniPAX::DnaRegionReference::getSubRegion()  {
        return subRegion;
}

void UniPAX::DnaRegionReference::setSubRegion(boost::shared_ptr<UniPAX::EntityReference> _subRegion)  {
    	subRegion = _subRegion;
}

bool UniPAX::DnaRegionReference::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

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
			std::cerr << "DnaRegionReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		subRegion = boost::dynamic_pointer_cast<UniPAX::EntityReference>(object);
		return true;
	}

	if (boost::iequals(attribute,"regionType"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "DnaRegionReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		regionType = boost::dynamic_pointer_cast<UniPAX::SequenceRegionVocabulary>(object);
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
			std::cerr << "DnaRegionReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		organism = boost::dynamic_pointer_cast<UniPAX::BioSource>(object);
		return true;
	}

	if (boost::iequals(attribute,"absoluteRegion"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "DnaRegionReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		absoluteRegion = boost::dynamic_pointer_cast<UniPAX::SequenceLocation>(object);
		return true;
	}
	if (boost::iequals(attribute,"sequence"))
	{
		setSequence(value);
		return true;
	}

	return false;

}

bool UniPAX::DnaRegionReference::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

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
	if (regionType == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#regionType", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(regionType,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#regionType", tmp));

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
	tmp.clear();
	if (absoluteRegion == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#absoluteRegion", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(absoluteRegion,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#absoluteRegion", tmp));

	}
	if (!getSequence().empty())
		value.push_back(std::pair<std::string,std::string>("sequence", getSequence()));

	return true;

}


//void UniPAX::DnaRegionReference::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::EntityReference::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		subRegion = boost::dynamic_pointer_cast<UniPAX::EntityReference>(getObjectByID(db, id_subRegion));
//		absoluteRegion = boost::dynamic_pointer_cast<UniPAX::SequenceLocation>(getObjectByID(db, id_absoluteRegion));
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		if (subRegion != 0)
//			id_subRegion = subRegion->getUnipaxId();
//
//		if (absoluteRegion != 0)
//			id_absoluteRegion = absoluteRegion->getUnipaxId();
//
//	}
//
//	return;
//}

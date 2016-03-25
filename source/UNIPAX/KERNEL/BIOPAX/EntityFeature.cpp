#include<UNIPAX/KERNEL/BIOPAX/EntityFeature.h>
#include<set>
//Begin section for file EntityFeature.cpp
//TODO: Add definitions that you want preserved
//End section for file EntityFeature.cpp

UniPAX::EntityFeature::EntityFeature() : UniPAX::UtilityClass()
//	memberFeature(0),
//	featureLocation(0),
//	featureLocationType(0)
{
}

UniPAX::EntityFeature::EntityFeature(const UniPAX::EntityFeature& arg) : UniPAX::UtilityClass(arg) ,
	evidence(arg.evidence),
	memberFeature(arg.memberFeature),
	featureLocation(arg.featureLocation),
	featureLocationType(arg.featureLocationType)
//	id_featureLocation(arg.id_featureLocation),
//	id_memberFeature(arg.id_memberFeature)
{
}

UniPAX::EntityFeature & UniPAX::EntityFeature::operator =(const UniPAX::EntityFeature & arg)  {
	UniPAX::UtilityClass::operator=(arg);
	evidence = arg.evidence;
	memberFeature = arg.memberFeature;
	featureLocation = arg.featureLocation;
	featureLocationType = arg.featureLocationType;
//	id_memberFeature = arg.id_memberFeature;
//	id_featureLocation = arg.id_featureLocation;

	return *this;
}

UniPAX::EntityFeature::~EntityFeature()  {
}

bool UniPAX::EntityFeature::merge(EntityFeature& object)
{
	{
		std::set<UniPAX::EvidencePtr> tmp(getEvidences().begin(), getEvidences().end());
		for (std::vector<UniPAX::EvidencePtr>::iterator it = object.getEvidences().begin(); it != object.getEvidences().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getEvidences().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::EntityFeaturePtr> tmp(getMemberFeatures().begin(), getMemberFeatures().end());
		for (std::vector<UniPAX::EntityFeaturePtr>::iterator it = object.getMemberFeatures().begin(); it != object.getMemberFeatures().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getMemberFeatures().assign(tmp.begin(), tmp.end());
	}

	{
		std::set<UniPAX::SequenceLocationPtr> tmp(getFeatureLocations().begin(), getFeatureLocations().end());
		for (std::vector<UniPAX::SequenceLocationPtr>::iterator it = object.getFeatureLocations().begin(); it != object.getFeatureLocations().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getFeatureLocations().assign(tmp.begin(), tmp.end());
	}

	{
		std::set<UniPAX::SequenceRegionVocabularyPtr> tmp(getFeatureLocationTypes().begin(), getFeatureLocationTypes().end());
		for (std::vector<UniPAX::SequenceRegionVocabularyPtr>::iterator it = object.getFeatureLocationTypes().begin(); it != object.getFeatureLocationTypes().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getFeatureLocationTypes().assign(tmp.begin(), tmp.end());
	}

	return UniPAX::UtilityClass::merge(object);
}


bool UniPAX::EntityFeature::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::Evidence> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Evidence> >::iterator it;
		for (it = evidence.begin(); it != evidence.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Evidence>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setEvidences(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> >::iterator it;
		for (it = memberFeature.begin(); it != memberFeature.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<EntityFeature>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setMemberFeatures(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::SequenceLocation> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::SequenceLocation> >::iterator it;
		for (it = featureLocation.begin(); it != featureLocation.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<SequenceLocation>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setFeatureLocations(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::SequenceRegionVocabulary> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::SequenceRegionVocabulary> >::iterator it;
		for (it = featureLocationType.begin(); it != featureLocationType.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<SequenceRegionVocabulary>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setFeatureLocationTypes(tmp_vec);
	}


	return UniPAX::UtilityClass::update(manager);
}

const std::vector<boost::shared_ptr<UniPAX::Evidence> > & UniPAX::EntityFeature::getEvidences() const {
        return evidence;
}

std::vector<boost::shared_ptr<UniPAX::Evidence> > & UniPAX::EntityFeature::getEvidences()  {
        return evidence;
}


void UniPAX::EntityFeature::setEvidences(std::vector<boost::shared_ptr<UniPAX::Evidence> > _evidences)  {
	evidence = _evidences;
}

void UniPAX::EntityFeature::addEvidence(boost::shared_ptr<UniPAX::Evidence>  _evidence) {
	evidence.push_back(_evidence);
}


const std::vector<boost::shared_ptr<UniPAX::EntityFeature> > & UniPAX::EntityFeature::getMemberFeatures() const {
        return memberFeature;
}

std::vector<boost::shared_ptr<UniPAX::EntityFeature> > & UniPAX::EntityFeature::getMemberFeatures()  {
        return memberFeature;
}


void UniPAX::EntityFeature::setMemberFeatures(std::vector<boost::shared_ptr<UniPAX::EntityFeature> > _memberFeatures) {
	memberFeature = _memberFeatures;
}

void UniPAX::EntityFeature::addMemberFeature(boost::shared_ptr<UniPAX::EntityFeature>  _memberFeatures) {
	memberFeature.push_back(_memberFeatures);
}


const std::vector<boost::shared_ptr<UniPAX::SequenceLocation> > & UniPAX::EntityFeature::getFeatureLocations() const {
        return featureLocation;
}

std::vector<boost::shared_ptr<UniPAX::SequenceLocation> > & UniPAX::EntityFeature::getFeatureLocations()  {
        return featureLocation;
}

//void UniPAX::EntityFeature::setFeatureLocation(const SequenceLocation& _featureLocation) {
//	featureLocation = &_featureLocation;
//}

void UniPAX::EntityFeature::setFeatureLocations(std::vector<boost::shared_ptr<UniPAX::SequenceLocation> > _featureLocations) {
	featureLocation = _featureLocations;
}

void UniPAX::EntityFeature::addFeatureLocation(boost::shared_ptr<UniPAX::SequenceLocation>  _featureLocation) {
	featureLocation.push_back(_featureLocation);
}


const std::vector<boost::shared_ptr<UniPAX::SequenceRegionVocabulary> > & UniPAX::EntityFeature::getFeatureLocationTypes() const {
        return featureLocationType;
}

std::vector<boost::shared_ptr<UniPAX::SequenceRegionVocabulary> > & UniPAX::EntityFeature::getFeatureLocationTypes()  {
        return featureLocationType;
}

//void UniPAX::EntityFeature::setFeatureLocationType(const SequenceRegionVocabulary& _featureLocationType) {
//	featureLocationType = &_featureLocationType;
//}

void UniPAX::EntityFeature::setFeatureLocationTypes(std::vector<boost::shared_ptr<UniPAX::SequenceRegionVocabulary> > _featureLocationTypes) {
	featureLocationType = _featureLocationTypes;
}

void UniPAX::EntityFeature::addFeatureLocationType(boost::shared_ptr<UniPAX::SequenceRegionVocabulary>  _featureLocationType) {
	featureLocationType.push_back(_featureLocationType);
}


bool UniPAX::EntityFeature::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"evidence"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "EntityFeature::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		evidence.push_back(boost::dynamic_pointer_cast<UniPAX::Evidence>(object));
		return true;
	}

	if (boost::iequals(attribute,"memberFeature"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "EntityFeature::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		memberFeature.push_back(boost::dynamic_pointer_cast<UniPAX::EntityFeature>(object));
		return true;
	}

	if (boost::iequals(attribute,"featureLocation"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "EntityFeature::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		featureLocation.push_back(boost::dynamic_pointer_cast<UniPAX::SequenceLocation>(object));
		return true;
	}

	if (boost::iequals(attribute,"featureLocationType"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "EntityFeature::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		featureLocationType.push_back(boost::dynamic_pointer_cast<UniPAX::SequenceRegionVocabulary>(object));
		return true;
	}

	return false;

}

bool UniPAX::EntityFeature::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::Evidence> >::iterator it;
		for (it = evidence.begin(); it != evidence.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#entityReference", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#evidence", tmp));

			}
		}
	}

	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> >::iterator it;
		for (it = memberFeature.begin(); it != memberFeature.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#memberFeature", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#memberFeature", tmp));

			}
		}
	}

	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::SequenceLocation> >::iterator it;
		for (it = featureLocation.begin(); it != featureLocation.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#featureLocation", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#featureLocation", tmp));

			}
		}
	}

	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::SequenceRegionVocabulary> >::iterator it;
		for (it = featureLocationType.begin(); it != featureLocationType.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#featureLocationType", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#featureLocationType", tmp));

			}
		}
	}


	return true;

}

//void UniPAX::EntityFeature::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		{
//			memberFeature.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_memberFeature.begin(); it != id_memberFeature.end(); it++)
//			{
//				memberFeature.push_back(boost::dynamic_pointer_cast<UniPAX::EntityFeature>(getObjectByID(db, *it)));
//			}
//		}
//		{
//			featureLocation.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_featureLocation.begin(); it != id_featureLocation.end(); it++)
//			{
//				featureLocation.push_back(boost::dynamic_pointer_cast<UniPAX::SequenceLocation>(getObjectByID(db, *it)));
//			}
//		}
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		{
//			id_memberFeature.clear();
//			std::vector<boost::shared_ptr<EntityFeature> >::iterator it;
//			for (it = memberFeature.begin(); it != memberFeature.end(); it++)
//			{
//				if (*it != 0)
//					id_memberFeature.push_back((*it)->getUnipaxId());
//			}
//		}
//		{
//			id_featureLocation.clear();
//			std::vector<boost::shared_ptr<SequenceLocation> >::iterator it;
//			for (it = featureLocation.begin(); it != featureLocation.end(); it++)
//			{
//				if (*it != 0)
//					id_featureLocation.push_back((*it)->getUnipaxId());
//			}
//		}
//	}
//
//	return;
//}


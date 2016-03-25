#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<set>
//Begin section for file PhysicalEntity.cpp
//TODO: Add definitions that you want preserved
//End section for file PhysicalEntity.cpp

UniPAX::PhysicalEntity::PhysicalEntity() : UniPAX::Entity()
//, cellularLocation(0)
{
    }

UniPAX::PhysicalEntity::PhysicalEntity(const PhysicalEntity & arg) : UniPAX::Entity(arg),
	feature(arg.feature),
	memberPhysicalEntity(arg.memberPhysicalEntity),
	notFeature(arg.notFeature),
	cellularLocation(arg.cellularLocation)
//	id_feature(arg.id_feature),
//	id_memberPhysicalEntity(arg.id_memberPhysicalEntity),
//	id_notFeature(arg.id_notFeature)
{
    }

UniPAX::PhysicalEntity & UniPAX::PhysicalEntity::operator =(const PhysicalEntity & arg)  {
	UniPAX::Entity::operator=(arg);
	feature = arg.feature;
	memberPhysicalEntity = arg.memberPhysicalEntity;
	notFeature = arg.notFeature;
	cellularLocation = arg.cellularLocation;
//	id_feature = arg.id_feature;
//	id_memberPhysicalEntity = arg.id_memberPhysicalEntity;
//	id_notFeature = arg.id_notFeature;

	return *this;
}

UniPAX::PhysicalEntity::~PhysicalEntity()  {
    }

bool UniPAX::PhysicalEntity::merge(PhysicalEntity& object)
{
	{
		std::set<UniPAX::EntityFeaturePtr> tmp(getFeatures().begin(), getFeatures().end());
		for (std::vector<UniPAX::EntityFeaturePtr>::iterator it = object.getFeatures().begin(); it != object.getFeatures().end(); it++)
		{
			if (*it)
			{
				tmp.insert(*it);
			}
		}
		getFeatures().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::PhysicalEntityPtr> tmp(getMemberPhysicalEntities().begin(), getMemberPhysicalEntities().end());
		for (std::vector<UniPAX::PhysicalEntityPtr>::iterator it = object.getMemberPhysicalEntities().begin(); it != object.getMemberPhysicalEntities().end(); it++)
		{
			if (*it)
			{
				tmp.insert(*it);
			}
		}
		getMemberPhysicalEntities().assign(tmp.begin(), tmp.end());
	}
	if (cellularLocation != 0)
	{
		if (object.getCellularLocation() != 0)
		{
			if (cellularLocation->getUnipaxId() != object.getCellularLocation()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::PhysicalEntity::cellularLocation not equal ..."
						<< cellularLocation->getUnipaxId() << " != " << object.getCellularLocation()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setCellularLocation(object.getCellularLocation());
	}
	{
		std::set<UniPAX::EntityFeaturePtr> tmp(getNotFeatures().begin(), getNotFeatures().end());
		for (std::vector<UniPAX::EntityFeaturePtr>::iterator it = object.getNotFeatures().begin(); it != object.getNotFeatures().end(); it++)
		{
			if (*it)
			{
				tmp.insert(*it);
			}
		}
		getNotFeatures().assign(tmp.begin(), tmp.end());
	}

	return UniPAX::Entity::merge(object);
}

bool UniPAX::PhysicalEntity::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getCellularLocation()))
	{
		setCellularLocation(boost::dynamic_pointer_cast<CellularLocationVocabulary>(manager.getMergedObject(getCellularLocation())));
	}
	{
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> >::iterator it;
		for (it = feature.begin(); it != feature.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<EntityFeature>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setFeatures(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator it;
		for (it = memberPhysicalEntity.begin(); it != memberPhysicalEntity.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<PhysicalEntity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setMemberPhysicalEntities(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> >::iterator it;
		for (it = notFeature.begin(); it != notFeature.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<EntityFeature>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setNotFeatures(tmp_vec);
	}

	return UniPAX::Entity::update(manager);
}


const std::vector<boost::shared_ptr<UniPAX::EntityFeature> > & UniPAX::PhysicalEntity::getFeatures() const {
        return feature;
}

std::vector<boost::shared_ptr<UniPAX::EntityFeature> > & UniPAX::PhysicalEntity::getFeatures() {
	return feature;
}

void UniPAX::PhysicalEntity::addFeature(boost::shared_ptr<UniPAX::EntityFeature>  _feature) {
	feature.push_back(_feature);
}

void UniPAX::PhysicalEntity::setFeatures(std::vector<boost::shared_ptr<UniPAX::EntityFeature> > _features) {
	feature = _features;
}


const std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::PhysicalEntity::getMemberPhysicalEntities() const {
        return memberPhysicalEntity;
}

std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::PhysicalEntity::getMemberPhysicalEntities() {
	return memberPhysicalEntity;
}

void UniPAX::PhysicalEntity::addMemberPhysicalEntity(boost::shared_ptr<UniPAX::PhysicalEntity>  _memberPhysicalEntity) {
	memberPhysicalEntity.push_back(_memberPhysicalEntity);
}

void UniPAX::PhysicalEntity::setMemberPhysicalEntities(std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > _memberPhysicalEntities) {
	memberPhysicalEntity = _memberPhysicalEntities;
}


const std::vector<boost::shared_ptr<UniPAX::EntityFeature> > & UniPAX::PhysicalEntity::getNotFeatures() const {
        return notFeature;
}

std::vector<boost::shared_ptr<UniPAX::EntityFeature> > & UniPAX::PhysicalEntity::getNotFeatures() {
	return notFeature;
}

void UniPAX::PhysicalEntity::addNotFeature(boost::shared_ptr<UniPAX::EntityFeature>  _notFeature) {
	notFeature.push_back(_notFeature);
}

void UniPAX::PhysicalEntity::setNotFeatures(std::vector<boost::shared_ptr<UniPAX::EntityFeature> > _notFeatures) {
	notFeature = _notFeatures;
}


const boost::shared_ptr<UniPAX::CellularLocationVocabulary> UniPAX::PhysicalEntity::getCellularLocation() const {
        return cellularLocation;
}

boost::shared_ptr<UniPAX::CellularLocationVocabulary> UniPAX::PhysicalEntity::getCellularLocation() {
	return cellularLocation;
}

void UniPAX::PhysicalEntity::setCellularLocation(boost::shared_ptr<UniPAX::CellularLocationVocabulary> _cellularLocation) {
	cellularLocation = _cellularLocation;
}


bool UniPAX::PhysicalEntity::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Entity::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"cellularLocation"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "PhysicalEntity::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		cellularLocation = boost::dynamic_pointer_cast<UniPAX::CellularLocationVocabulary>(object);
		return true;
	}
	if (boost::iequals(attribute,"notFeature"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "PhysicalEntity::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		notFeature.push_back(boost::dynamic_pointer_cast<UniPAX::EntityFeature>(object));
		return true;
	}
	if (boost::iequals(attribute,"memberPhysicalEntity"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "PhysicalEntity::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		memberPhysicalEntity.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object));
		return true;
	}
	if (boost::iequals(attribute,"feature"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "PhysicalEntity::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		feature.push_back(boost::dynamic_pointer_cast<UniPAX::EntityFeature>(object));
		return true;
	}


	return false;

}

bool UniPAX::PhysicalEntity::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Entity::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> >::iterator it;
		for (it = feature.begin(); it != feature.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#feature", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#feature", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator it;
		for (it = memberPhysicalEntity.begin(); it != memberPhysicalEntity.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#memberPhysicalEntity", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#memberPhysicalEntity", tmp));

			}
		}
	}
	tmp.clear();
	if (cellularLocation == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#cellularLocation", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(cellularLocation,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#cellularLocation", tmp));

	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> >::iterator it;
		for (it = notFeature.begin(); it != notFeature.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#notFeature", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#notFeature", tmp));

			}
		}
	}

	return true;

}


//void UniPAX::PhysicalEntity::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Entity::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		{
//			feature.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_feature.begin(); it != id_feature.end(); it++)
//			{
//				feature.push_back(boost::dynamic_pointer_cast<UniPAX::EntityFeature>(getObjectByID(db, *it)));
//			}
//		}
//		{
//			memberPhysicalEntity.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_memberPhysicalEntity.begin(); it != id_memberPhysicalEntity.end(); it++)
//			{
//				memberPhysicalEntity.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(getObjectByID(db, *it)));
//			}
//		}
//		{
//			notFeature.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_notFeature.begin(); it != id_notFeature.end(); it++)
//			{
//				notFeature.push_back(boost::dynamic_pointer_cast<UniPAX::EntityFeature>(getObjectByID(db, *it)));
//			}
//		}
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		{
//			id_feature.clear();
//			std::vector<boost::shared_ptr<EntityFeature> >::iterator it;
//			for (it = feature.begin(); it != feature.end(); it++)
//			{
//				if (*it != 0)
//					id_feature.push_back((*it)->getUnipaxId());
//			}
//		}
//		{
//			id_memberPhysicalEntity.clear();
//			std::vector<boost::shared_ptr<PhysicalEntity> >::iterator it;
//			for (it = memberPhysicalEntity.begin(); it != memberPhysicalEntity.end(); it++)
//			{
//				if (*it != 0)
//					id_memberPhysicalEntity.push_back((*it)->getUnipaxId());
//			}
//		}
//		{
//			id_notFeature.clear();
//			std::vector<boost::shared_ptr<EntityFeature> >::iterator it;
//			for (it = notFeature.begin(); it != notFeature.end(); it++)
//			{
//				if (*it != 0)
//					id_notFeature.push_back((*it)->getUnipaxId());
//			}
//		}
//	}
//
//	return;
//}


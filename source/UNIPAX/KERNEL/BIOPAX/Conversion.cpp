#include<UNIPAX/KERNEL/BIOPAX/Conversion.h>
#include<set>
//Begin section for file Conversion.cpp
//TODO: Add definitions that you want preserved
//End section for file Conversion.cpp

UniPAX::Conversion::Conversion() : UniPAX::Interaction()
   , spontaneous(false)
// ,kineticLaw(0)
{
    }

UniPAX::Conversion::Conversion(const Conversion& arg) : UniPAX::Interaction(arg) ,
	kineticLaw(arg.kineticLaw),
	conversionDirection (arg.conversionDirection),
	spontaneous(arg.spontaneous),
	participantStoichiometry(arg.participantStoichiometry),
	leftEntity(arg.leftEntity),
	rightEntity(arg.rightEntity)
//	id_leftEntity(arg.id_leftEntity),
//	id_rightEntity(arg.id_rightEntity)
{
}

UniPAX::Conversion & UniPAX::Conversion::operator =(const Conversion & arg)  {
	UniPAX::Interaction::operator=(arg);
    conversionDirection = arg.conversionDirection;
	spontaneous = arg.spontaneous;
	participantStoichiometry = arg.participantStoichiometry;
	leftEntity = arg.leftEntity;
	rightEntity = arg.rightEntity;
    kineticLaw = arg.kineticLaw;
//    id_leftEntity = arg.id_leftEntity;
//    id_rightEntity = arg.id_rightEntity;

	return *this;
}

UniPAX::Conversion::~Conversion()  {
    }

bool UniPAX::Conversion::merge(Conversion& object)
{
	{
		std::set<UniPAX::StoichiometryPtr> tmp(getParticipantStoichiometries().begin(), getParticipantStoichiometries().end());
		for (std::vector<UniPAX::StoichiometryPtr>::iterator it = object.getParticipantStoichiometries().begin(); it != object.getParticipantStoichiometries().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getParticipantStoichiometries().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::PhysicalEntityPtr> tmp(getLefts().begin(), getLefts().end());
		for (std::vector<UniPAX::PhysicalEntityPtr>::iterator it = object.getLefts().begin(); it != object.getLefts().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getLefts().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::PhysicalEntityPtr> tmp(getRights().begin(), getRights().end());
		for (std::vector<UniPAX::PhysicalEntityPtr>::iterator it = object.getRights().begin(); it != object.getRights().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getRights().assign(tmp.begin(), tmp.end());
	}

	if (kineticLaw != 0)
	{
		if (object.getKineticLaw() != 0)
		{
			if (kineticLaw->getUnipaxId() != object.getKineticLaw()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::Conversion::kineticLaw not equal ..."
						<< kineticLaw->getUnipaxId() << " != " << object.getKineticLaw()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setKineticLaw(object.getKineticLaw());
	}

	if (getSpontaneous() != object.getSpontaneous())
	{
		std::cerr << "Error during merging: UniPAX::Conversion::spontaneous not equal ..."
				<< getSpontaneous() << " != " << object.getSpontaneous() << std::endl;
		return false;
	}

	if (!object.getConversionDirection().empty())
	{
		if (!getConversionDirection().empty())
		{
			if (getConversionDirection() != object.getConversionDirection())
			{
				std::cerr << "Error during merging: UniPAX::Conversion::conversionDirection not equal ..."
						<< getConversionDirection() << " != " << object.getConversionDirection() << std::endl;
				return false;
			}
		}
		else
			setConversionDirection(object.getConversionDirection());
	}

	return UniPAX::Interaction::merge(object);
}

bool UniPAX::Conversion::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getKineticLaw()))
	{
		setKineticLaw(boost::dynamic_pointer_cast<KineticLaw>(manager.getMergedObject(getKineticLaw())));
	}
	{
		std::vector<boost::shared_ptr<UniPAX::Stoichiometry> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Stoichiometry> >::iterator it;
		for (it = participantStoichiometry.begin(); it != participantStoichiometry.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Stoichiometry>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setParticipantStoichiometries(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator it;
		for (it = leftEntity.begin(); it != leftEntity.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<PhysicalEntity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setLefts(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator it;
		for (it = rightEntity.begin(); it != rightEntity.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<PhysicalEntity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setRights(tmp_vec);
	}

	return UniPAX::Interaction::update(manager);
}


const std::string & UniPAX::Conversion::getConversionDirection() const {
        return conversionDirection;
}

std::string & UniPAX::Conversion::getConversionDirection() {
    return conversionDirection;
}

void UniPAX::Conversion::setConversionDirection(std::string _conversionDirection) {
    conversionDirection = _conversionDirection;
}

const bool & UniPAX::Conversion::getSpontaneous() const {
        return spontaneous;
}

bool & UniPAX::Conversion::getSpontaneous() {
    return spontaneous;
}

void UniPAX::Conversion::setSpontaneous(bool _spontaneous) {
    spontaneous = _spontaneous;
}


const std::vector<boost::shared_ptr<UniPAX::Stoichiometry> > & UniPAX::Conversion::getParticipantStoichiometries() const {
    return participantStoichiometry;
}

std::vector<boost::shared_ptr<UniPAX::Stoichiometry> > & UniPAX::Conversion::getParticipantStoichiometries() {
    return participantStoichiometry;
}

void UniPAX::Conversion::setParticipantStoichiometries(std::vector<boost::shared_ptr<UniPAX::Stoichiometry> > _participantStoichiometries) {
    participantStoichiometry = _participantStoichiometries;
}

void UniPAX::Conversion::addParticipantStoichiometry(boost::shared_ptr<UniPAX::Stoichiometry>  _participantStoichiometries) {
    participantStoichiometry.push_back(_participantStoichiometries);
}



const std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::Conversion::getLefts() const {
    return leftEntity;
}

std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::Conversion::getLefts() {
    return leftEntity;
}

void UniPAX::Conversion::addLeft(boost::shared_ptr<UniPAX::PhysicalEntity>  _left) {
    leftEntity.push_back(_left);
}

void UniPAX::Conversion::setLefts(std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > _lefts) {
    leftEntity = _lefts;
}



const std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::Conversion::getRights() const {
    return rightEntity;
}

std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::Conversion::getRights() {
    return rightEntity;
}

void UniPAX::Conversion::addRight(boost::shared_ptr<UniPAX::PhysicalEntity>  _right) {
	rightEntity.push_back(_right);
}

void UniPAX::Conversion::setRights(std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > _rights) {
	rightEntity = _rights;
}



const boost::shared_ptr<UniPAX::KineticLaw> UniPAX::Conversion::getKineticLaw() const {
    return kineticLaw;
}

boost::shared_ptr<UniPAX::KineticLaw> UniPAX::Conversion::getKineticLaw()  {
        return kineticLaw;
}

void UniPAX::Conversion::setKineticLaw(boost::shared_ptr<UniPAX::KineticLaw> _kineticLaw)  {
        kineticLaw = _kineticLaw;
}


const std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::Conversion::getParticipants() const {
	std::vector<boost::shared_ptr<UniPAX::Entity> > _participants(super::getParticipants());
	_participants.insert(_participants.end(), leftEntity.begin(), leftEntity.end());
	_participants.insert(_participants.end(), rightEntity.begin(), rightEntity.end());
	return _participants;
}

std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::Conversion::getParticipants()
{
	std::vector<boost::shared_ptr<UniPAX::Entity> > _participants(super::getParticipants());
	_participants.insert(_participants.end(), leftEntity.begin(), leftEntity.end());
	_participants.insert(_participants.end(), rightEntity.begin(), rightEntity.end());
	return _participants;
}



bool UniPAX::Conversion::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Interaction::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"kineticLaw"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Conversion::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		kineticLaw = boost::dynamic_pointer_cast<UniPAX::KineticLaw>(object);
		return true;
	}
	if (boost::iequals(attribute,"participantStoichiometry"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Conversion::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		participantStoichiometry.push_back(boost::dynamic_pointer_cast<UniPAX::Stoichiometry>(object));
		return true;
	}
	if (boost::iequals(attribute,"left"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Conversion::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		leftEntity.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object));
		return true;
	}
	if (boost::iequals(attribute,"right"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Conversion::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		rightEntity.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object));
		return true;
	}
	if (boost::iequals(attribute,"conversionDirection"))
	{
		setConversionDirection(value);
		return true;
	}
	if (boost::iequals(attribute,"spontaneous"))
	{
		// if the attribute is not boolean simply ignore it
		PersistenceManager::convertAttribute(value,spontaneous);
		return true;
	}

	return false;

}




bool UniPAX::Conversion::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Interaction::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::Stoichiometry> >::iterator it;
		for (it = participantStoichiometry.begin(); it != participantStoichiometry.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#participantStoichiometry", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#participantStoichiometry", tmp));

			}
		}
	}
	std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator it;
	for (it = leftEntity.begin(); it != leftEntity.end(); it++)
	{
		if (*it == 0)
		{
//			value.push_back(std::pair<std::string,std::string>("#left", "NIL"));
		}
		else
		{
			tmp.clear();
			if (!manager.getId(*it,tmp))
			{
				return false;
			}
			value.push_back(std::pair<std::string,std::string>("#left", tmp));

		}
	}
	for (it = rightEntity.begin(); it != rightEntity.end(); it++)
	{
		if (*it == 0)
		{
//			value.push_back(std::pair<std::string,std::string>("#right", "NIL"));
		}
		else
		{
			tmp.clear();
			if (!manager.getId(*it,tmp))
			{
				return false;
			}
			value.push_back(std::pair<std::string,std::string>("#right", tmp));

		}
	}

	tmp.clear();
	if (kineticLaw == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#kineticLaw", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(kineticLaw,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#kineticLaw", tmp));

	}
	tmp.clear();
	if (!PersistenceManager::convertAttribute(spontaneous, tmp))
	{
		return false;
	}
	value.push_back(std::pair<std::string,std::string>("spontaneous", tmp));

	if (!getConversionDirection().empty())
		value.push_back(std::pair<std::string,std::string>("conversionDirection", getConversionDirection()));

	return true;

}


//void UniPAX::Conversion::init (odb::callback_event e, odb::database& db) const
//{
//	std::cout << "Init Conversion... " << std::endl;
//
//	UniPAX::Interaction::init(e,db);
//
//	switch (e)
//	{
//	case odb::callback_event::post_load:
//		// load the object pointer
//	{
//		leftEntity.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_leftEntity.begin(); it != id_leftEntity.end(); it++)
//		{
//			leftEntity.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(getObjectByID(db, *it)));
//		}
//	}
//	{
//		rightEntity.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_rightEntity.begin(); it != id_rightEntity.end(); it++)
//		{
//			rightEntity.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(getObjectByID(db, *it)));
//		}
//	}
//	break;
//	case odb::callback_event::pre_persist:
//	case odb::callback_event::pre_update:
//		// set the object ids
//	{
//		id_leftEntity.clear();
//		std::vector<boost::shared_ptr<PhysicalEntity> >::iterator it;
//		for (it = leftEntity.begin(); it != leftEntity.end(); it++)
//		{
//			if (*it != 0)
//				id_leftEntity.push_back((*it)->getUnipaxId());
//		}
//	}
//	{
//		id_rightEntity.clear();
//		std::vector<boost::shared_ptr<PhysicalEntity> >::iterator it;
//		for (it = rightEntity.begin(); it != rightEntity.end(); it++)
//		{
//			if (*it != 0)
//				id_rightEntity.push_back((*it)->getUnipaxId());
//		}
//	}
//	break;
//	}
//
//	return;
//}

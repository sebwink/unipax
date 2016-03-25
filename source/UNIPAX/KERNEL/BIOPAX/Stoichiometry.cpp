#include<UNIPAX/KERNEL/BIOPAX/Stoichiometry.h>
#include<set>
//Begin section for file Stoichiometry.cpp
//TODO: Add definitions that you want preserved
//End section for file Stoichiometry.cpp

UniPAX::Stoichiometry::Stoichiometry() : UniPAX::UtilityClass(),
		stoichiometricCoefficient(0)
//	physicalEntity(0),
//	id_physicalEntity(0)
{
}

UniPAX::Stoichiometry::Stoichiometry(const Stoichiometry& arg) : UniPAX::UtilityClass(arg) ,
		stoichiometricCoefficient(arg.stoichiometricCoefficient),
		physicalEntity(arg.physicalEntity)
//		id_physicalEntity(arg.id_physicalEntity)
{}

UniPAX::Stoichiometry & UniPAX::Stoichiometry::operator =(const Stoichiometry & arg)  {
	UniPAX::UtilityClass::operator=(arg);
	stoichiometricCoefficient = arg.stoichiometricCoefficient;
	physicalEntity = arg.physicalEntity;
//	id_physicalEntity = arg.id_physicalEntity;

	return *this;
}

UniPAX::Stoichiometry::~Stoichiometry()  {
}

bool UniPAX::Stoichiometry::merge(Stoichiometry& object)
{

	if (physicalEntity != 0)
	{
		if (object.getPhysicalEntity() != 0)
		{
			if (physicalEntity->getUnipaxId() != object.getPhysicalEntity()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::Stoichiometry::physicalEntity not equal ..."
						<< physicalEntity->getUnipaxId() << " != " << object.getPhysicalEntity()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setPhysicalEntity(object.getPhysicalEntity());
	}

	if (!object.getStoichiometricCoefficient() != 0.)
	{
		if (!getStoichiometricCoefficient() != 0.)
		{
			if (getStoichiometricCoefficient() != object.getStoichiometricCoefficient())
			{
				std::cerr << "Error during merging: UniPAX::Stoichiometry::stoichiometricCoefficient not equal ..."
						<< getStoichiometricCoefficient() << " != " << object.getStoichiometricCoefficient() << std::endl;
				return false;
			}
		}
		else
			setStoichiometricCoefficient(object.getStoichiometricCoefficient());
	}

	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::Stoichiometry::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getPhysicalEntity()))
	{
		setPhysicalEntity(boost::dynamic_pointer_cast<PhysicalEntity>(manager.getMergedObject(getPhysicalEntity())));
	}

	return UniPAX::UtilityClass::update(manager);
}

const double UniPAX::Stoichiometry::getStoichiometricCoefficient() const {
	return stoichiometricCoefficient;
}

double UniPAX::Stoichiometry::getStoichiometricCoefficient()  {
	return stoichiometricCoefficient;
}

void UniPAX::Stoichiometry::setStoichiometricCoefficient(double _stoichiometricCoefficient)  {
	stoichiometricCoefficient = _stoichiometricCoefficient;
}

const boost::shared_ptr<UniPAX::PhysicalEntity> UniPAX::Stoichiometry::getPhysicalEntity() const {
	return physicalEntity;
}

boost::shared_ptr<UniPAX::PhysicalEntity> UniPAX::Stoichiometry::getPhysicalEntity() {
	return physicalEntity;
}

void UniPAX::Stoichiometry::setPhysicalEntity(boost::shared_ptr<UniPAX::PhysicalEntity> _physicalEntity) {
	physicalEntity = _physicalEntity;
}

bool UniPAX::Stoichiometry::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"physicalEntity"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value);
		if (object == 0)
		{
			std::cerr << "Stoichiometry::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		physicalEntity = boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object);
		return true;
	}
	if (boost::iequals(attribute,"stoichiometricCoefficient"))
	{
		return PersistenceManager::convertAttribute(value,stoichiometricCoefficient);
	}

	return false;

}

bool UniPAX::Stoichiometry::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	std::string tmp = "";

	if (physicalEntity == 0)
	{
		//		value.push_back(std::pair<std::string,std::string>("#physicalEntity", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(physicalEntity,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#physicalEntity", tmp));

	}


	tmp.clear();
	if (!PersistenceManager::convertAttribute(stoichiometricCoefficient, tmp))
	{
		return false;
	}
	if (stoichiometricCoefficient != 0)
		value.push_back(std::pair<std::string,std::string>("stoichiometricCoefficient", tmp));


	return true;

}

//void UniPAX::Stoichiometry::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		physicalEntity = boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(getObjectByID(db, id_physicalEntity));
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		if (physicalEntity != 0)
//			id_physicalEntity = physicalEntity->getUnipaxId();
//	}
//
//	return;
//}

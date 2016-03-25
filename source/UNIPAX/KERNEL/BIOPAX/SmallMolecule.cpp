#include<UNIPAX/KERNEL/BIOPAX/SmallMolecule.h>
#include<set>
//Begin section for file SmallMolecule.cpp
//TODO: Add definitions that you want preserved
//End section for file SmallMolecule.cpp

UniPAX::SmallMolecule::SmallMolecule() : UniPAX::PhysicalEntity()
//		entityReference(0),
//		id_entityReference(0)
{
}

UniPAX::SmallMolecule::SmallMolecule(const SmallMolecule & arg)  : UniPAX::PhysicalEntity(arg),
		entityReference(arg.entityReference)
//		id_entityReference(arg.id_entityReference)
{}

UniPAX::SmallMolecule & UniPAX::SmallMolecule::operator =(const SmallMolecule & arg)  {
	UniPAX::PhysicalEntity::operator=(arg);
	entityReference = arg.entityReference;
//	id_entityReference = arg.id_entityReference;

	return *this;
}

UniPAX::SmallMolecule::~SmallMolecule()  {
}

bool UniPAX::SmallMolecule::merge(SmallMolecule& object)
{

	{
		std::set<UniPAX::EntityReferencePtr> tmp(getEntityReferences().begin(), getEntityReferences().end());
		for (std::vector<UniPAX::EntityReferencePtr>::iterator it = object.getEntityReferences().begin(); it != object.getEntityReferences().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getEntityReferences().assign(tmp.begin(), tmp.end());
	}
	return UniPAX::PhysicalEntity::merge(object);
}

bool UniPAX::SmallMolecule::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::EntityReference> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::EntityReference> >::iterator it;
		for (it = entityReference.begin(); it != entityReference.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<EntityReference>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setEntityReferences(tmp_vec);
	}

	return UniPAX::PhysicalEntity::update(manager);
}


const std::vector<boost::shared_ptr<UniPAX::EntityReference> > & UniPAX::SmallMolecule::getEntityReferences() const {
	return entityReference;
}

std::vector<boost::shared_ptr<UniPAX::EntityReference> > & UniPAX::SmallMolecule::getEntityReferences() {
	return entityReference;
}

void UniPAX::SmallMolecule::setEntityReferences(std::vector<boost::shared_ptr<UniPAX::EntityReference> > _entityReferences) {
	entityReference = _entityReferences;
}

void UniPAX::SmallMolecule::addEntityReference(boost::shared_ptr<UniPAX::EntityReference>  _entityReference) {
	entityReference.push_back(_entityReference);
}

bool UniPAX::SmallMolecule::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::PhysicalEntity::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"entityReference"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "SmallMolecule::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		entityReference.push_back(boost::dynamic_pointer_cast<UniPAX::EntityReference>(object));
		return true;
	}

	return false;

}



bool UniPAX::SmallMolecule::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::PhysicalEntity::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::EntityReference> >::iterator it;
		for (it = entityReference.begin(); it != entityReference.end(); it++)
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
				value.push_back(std::pair<std::string,std::string>("#entityReference", tmp));

			}
		}
	}

	return true;

}

//void UniPAX::SmallMolecule::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::PhysicalEntity::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		entityReference.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_entityReference.begin(); it != id_entityReference.end(); it++)
//		{
//			entityReference.push_back(boost::dynamic_pointer_cast<UniPAX::EntityReference>(getObjectByID(db, *it)));
//		}
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		id_entityReference.clear();
//		std::vector<boost::shared_ptr<EntityReference> >::iterator it;
//		for (it = entityReference.begin(); it != entityReference.end(); it++)
//		{
//			if (*it != 0)
//				id_entityReference.push_back((*it)->getUnipaxId());
//		}
//
//	}
//
//	return;
//}

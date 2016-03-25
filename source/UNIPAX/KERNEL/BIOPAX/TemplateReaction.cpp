#include<UNIPAX/KERNEL/BIOPAX/TemplateReaction.h>
#include<set>

//Begin section for file TemplateReaction.cpp
//TODO: Add definitions that you want preserved
//End section for file TemplateReaction.cpp

UniPAX::TemplateReaction::TemplateReaction() : UniPAX::Interaction()
//	templateEntity(0),
//	id_templateEntity(0)
{
}

UniPAX::TemplateReaction::TemplateReaction(const TemplateReaction& arg) : UniPAX::Interaction(arg) ,
		templateDirection(arg.templateDirection),
		templateEntity(arg.templateEntity),
		product(arg.product)
//		id_templateEntity(arg.id_templateEntity),
//		id_product(arg.id_product)
{
}

UniPAX::TemplateReaction & UniPAX::TemplateReaction::operator =(const TemplateReaction & arg)  {
	UniPAX::Interaction::operator=(arg);
	templateDirection = arg.templateDirection;
	templateEntity = arg.templateEntity;
	product = arg.product;
//	id_templateEntity = arg.id_templateEntity;
//	id_product = arg.id_product;

	return *this;
}

UniPAX::TemplateReaction::~TemplateReaction()  {
}

bool UniPAX::TemplateReaction::merge(TemplateReaction& object)
{
	{
		std::set<UniPAX::PhysicalEntityPtr> tmp(getProducts().begin(), getProducts().end());
		for (std::vector<UniPAX::PhysicalEntityPtr>::iterator it = object.getProducts().begin(); it != object.getProducts().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getProducts().assign(tmp.begin(), tmp.end());
	}
	if (templateEntity != 0)
	{
		if (object.getTemplateEntity() != 0)
		{
			if (templateEntity->getUnipaxId() != object.getTemplateEntity()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::TemplateReaction::templateEntity not equal ..."
						<< templateEntity->getUnipaxId() << " != " << object.getTemplateEntity()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setTemplateEntity(object.getTemplateEntity());
	}

	if (!object.getTemplateDirection().empty())
	{
		if (!getTemplateDirection().empty())
		{
			if (getTemplateDirection() != object.getTemplateDirection())
			{
				std::cerr << "Error during merging: UniPAX::TemplateReaction::templateDirection not equal ..."
						<< getTemplateDirection() << " != " << object.getTemplateDirection() << std::endl;
				return false;
			}
		}
		else
			setTemplateDirection(object.getTemplateDirection());
	}

	return UniPAX::Interaction::merge(object);
}

bool UniPAX::TemplateReaction::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getTemplateEntity()))
	{
		setTemplateEntity(boost::dynamic_pointer_cast<PhysicalEntity>(manager.getMergedObject(getTemplateEntity())));
	}
	{
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator it;
		for (it = product.begin(); it != product.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<PhysicalEntity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setProducts(tmp_vec);
	}

	return UniPAX::Interaction::update(manager);
}


const std::string & UniPAX::TemplateReaction::getTemplateDirection() const {
	return templateDirection;
}

std::string & UniPAX::TemplateReaction::getTemplateDirection() {
	return templateDirection;
}

void UniPAX::TemplateReaction::setTemplateDirection(std::string & _templateDirection) {
	templateDirection = _templateDirection;
}

const boost::shared_ptr<UniPAX::PhysicalEntity> UniPAX::TemplateReaction::getTemplateEntity() const {
	return templateEntity;
}

boost::shared_ptr<UniPAX::PhysicalEntity> UniPAX::TemplateReaction::getTemplateEntity()  {
	return templateEntity;
}

void UniPAX::TemplateReaction::setTemplateEntity(boost::shared_ptr<UniPAX::PhysicalEntity> _templateEntity)  {
	templateEntity = _templateEntity;
}

const std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::TemplateReaction::getProducts() const {
	return product;
}

std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::TemplateReaction::getProducts()  {
	return product;
}

void UniPAX::TemplateReaction::setProducts(std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > _products)  {
	product = _products;
}

void UniPAX::TemplateReaction::addProduct(boost::shared_ptr<UniPAX::PhysicalEntity>  _product) {
	product.push_back(_product);
}

const std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::TemplateReaction::getParticipants() const {
	std::vector<boost::shared_ptr<UniPAX::Entity> > _participants(super::getParticipants());
	_participants.push_back(templateEntity);
	_participants.insert(_participants.end(), product.begin(), product.end());
	return _participants;
}

std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::TemplateReaction::getParticipants()
{
	std::vector<boost::shared_ptr<UniPAX::Entity> > _participants(super::getParticipants());
	_participants.push_back(templateEntity);
	_participants.insert(_participants.end(), product.begin(), product.end());
	return _participants;
}

bool UniPAX::TemplateReaction::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Interaction::setAttribute(attribute, value, manager))
		return true;


	if (boost::iequals(attribute,"product"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "TemplateReaction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		product.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object));
		return true;
	}
	if (boost::iequals(attribute,"templateentity"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;
		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "TemplateReaction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		templateEntity = boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object);
		return true;
	}
	if (boost::iequals(attribute,"templatedirection"))
	{
		setTemplateDirection(value);
		return true;
	}

	return false;

}

bool UniPAX::TemplateReaction::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Interaction::getAttribute(value, manager))
		return false;

	{
		std::string tmp = "";
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator it;
		for (it = product.begin(); it != product.end(); it++)
		{
			if (*it == 0)
			{
				//				value.push_back(std::pair<std::string,std::string>("#product", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#product", tmp));
			}
		}
	}

	if (templateEntity == 0)
	{
		//		value.push_back(std::pair<std::string,std::string>("#templateEntity", "NIL"));
	}
	else
	{
		std::string tmp = "";
		if (!manager.getId(templateEntity,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#template", tmp));

	}
	if (!getTemplateDirection().empty())
		value.push_back(std::pair<std::string,std::string>("templateDirection", getTemplateDirection()));

	return true;

}

//void UniPAX::TemplateReaction::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Interaction::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		templateEntity = boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(getObjectByID(db, id_templateEntity));
//
//		// load the object pointer
//		product.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_product.begin(); it != id_product.end(); it++)
//		{
//			product.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(getObjectByID(db, *it)));
//		}
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		if (templateEntity != 0)
//			id_templateEntity = templateEntity->getUnipaxId();
//
//		// set the object ids
//		id_product.clear();
//		std::vector<boost::shared_ptr<PhysicalEntity> >::iterator it;
//		for (it = product.begin(); it != product.end(); it++)
//		{
//			if (*it != 0)
//				id_product.push_back((*it)->getUnipaxId());
//		}
//
//	}
//
//	return;
//}

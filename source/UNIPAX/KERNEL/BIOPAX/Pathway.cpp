#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<set>
//Begin section for file Pathway.cpp
//TODO: Add definitions that you want preserved
//End section for file Pathway.cpp


UniPAX::Pathway::Pathway() : UniPAX::Entity()
//	id_pathwayOrder(0),
//	id_pathwayComponent(0),
//	id_modelExtensions(0)
//, organism(0)
{
}

UniPAX::Pathway::Pathway(const Pathway & arg) : UniPAX::Entity(arg),
		pathwayComponent(arg.pathwayComponent),
		pathwayOrder(arg.pathwayOrder),
		organism(arg.organism)
//		id_modelExtensions(arg.id_modelExtensions),
//		id_pathwayComponent(arg.id_pathwayComponent),
//		id_pathwayOrder(arg.id_pathwayOrder)
{
}

UniPAX::Pathway & UniPAX::Pathway::operator =(const Pathway & arg)  {
	UniPAX::Entity::operator=(arg);
	modelExtensions = arg.modelExtensions;
	pathwayComponent = arg.pathwayComponent;
	pathwayOrder = arg.pathwayOrder;
	organism = arg.organism;
//	id_modelExtensions = arg.id_modelExtensions;
//	id_pathwayComponent = arg.id_pathwayComponent;
//	id_pathwayOrder = arg.id_pathwayOrder;

	return *this;
}

UniPAX::Pathway::~Pathway()  {
}

bool UniPAX::Pathway::merge(Pathway& object)
{
	{
		std::set<UniPAX::ModelPtr> tmp(getModelExtensions().begin(), getModelExtensions().end());
		for (std::vector<UniPAX::ModelPtr>::iterator it = object.getModelExtensions().begin(); it != object.getModelExtensions().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getModelExtensions().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::EntityPtr> tmp(getPathwayComponents().begin(), getPathwayComponents().end());
		for (std::vector<UniPAX::EntityPtr>::iterator it = object.getPathwayComponents().begin(); it != object.getPathwayComponents().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getPathwayComponents().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::PathwayStepPtr> tmp(getPathwayOrders().begin(), getPathwayOrders().end());
		for (std::vector<UniPAX::PathwayStepPtr>::iterator it = object.getPathwayOrders().begin(); it != object.getPathwayOrders().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getPathwayOrders().assign(tmp.begin(), tmp.end());
	}
	if (organism != 0)
	{
		if (object.getOrganism() != 0)
		{
			if (organism->getUnipaxId() != object.getOrganism()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::Pathway::organism not equal ..."
						<< organism->getUnipaxId() << " != " << object.getOrganism()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setOrganism(object.getOrganism());
	}

	return UniPAX::Entity::merge(object);
}

bool UniPAX::Pathway::update(PersistenceManager& manager)
{
	if (manager.isMerged(getOrganism()))
	{
		setOrganism(boost::dynamic_pointer_cast<BioSource>(manager.getMergedObject(getOrganism())));
	}
	{
		std::vector<boost::shared_ptr<UniPAX::PathwayStep> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::PathwayStep> >::iterator it;
		for (it = pathwayOrder.begin(); it != pathwayOrder.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<PathwayStep>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setPathwayOrders(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::Model> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Model> >::iterator it;
		for (it = modelExtensions.begin(); it != modelExtensions.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Model>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setModelExtensions(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::Entity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
		for (it = pathwayComponent.begin(); it != pathwayComponent.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Entity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setPathwayComponents(tmp_vec);
	}

	return UniPAX::Entity::update(manager);
}


const std::vector<boost::shared_ptr<UniPAX::PathwayStep> > & UniPAX::Pathway::getPathwayOrders() const {
	return pathwayOrder;
}

std::vector<boost::shared_ptr<UniPAX::PathwayStep> > & UniPAX::Pathway::getPathwayOrders() {
	return pathwayOrder;
}

void UniPAX::Pathway::addPathwayOrder(boost::shared_ptr<UniPAX::PathwayStep>  _pathwayOrder) {
	pathwayOrder.push_back(_pathwayOrder);
}

void UniPAX::Pathway::setPathwayOrders(std::vector<boost::shared_ptr<UniPAX::PathwayStep> > _pathwayOrders) {
	pathwayOrder = _pathwayOrders;
}


const boost::shared_ptr<UniPAX::BioSource> UniPAX::Pathway::getOrganism() const {
	return organism;
}

boost::shared_ptr<UniPAX::BioSource> UniPAX::Pathway::getOrganism() {
	return organism;
}

void UniPAX::Pathway::setOrganism(boost::shared_ptr<UniPAX::BioSource> _organism) {
	organism = _organism;
}

// modelExtensions
std::vector<boost::shared_ptr<UniPAX::Model> > & UniPAX::Pathway::getModelExtensions()
{
	return modelExtensions;
}

const std::vector<boost::shared_ptr<UniPAX::Model> > & UniPAX::Pathway::getModelExtensions() const
{
	return modelExtensions;
}

void UniPAX::Pathway::setModelExtensions(std::vector<boost::shared_ptr<UniPAX::Model> > _modelExtensions)
{
	modelExtensions = _modelExtensions;
}

void UniPAX::Pathway::addModelExtension(boost::shared_ptr<UniPAX::Model>  _modelExtension)
{
	modelExtensions.push_back(_modelExtension);
}

std::vector<boost::shared_ptr<UniPAX::Entity> > & UniPAX::Pathway::getPathwayComponents()  {
	return pathwayComponent;
}

const std::vector<boost::shared_ptr<UniPAX::Entity> > & UniPAX::Pathway::getPathwayComponents() const {
	return pathwayComponent;
}

void UniPAX::Pathway::addPathwayComponent(boost::shared_ptr<UniPAX::Entity>  _pathwayComponent)  {
	pathwayComponent.push_back(_pathwayComponent);
}

void UniPAX::Pathway::setPathwayComponents(std::vector<boost::shared_ptr<UniPAX::Entity> > _pathwayComponents)  {
	pathwayComponent = _pathwayComponents;
}


bool UniPAX::Pathway::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Entity::setAttribute(attribute, value, manager))
		return true;


	if (boost::iequals(attribute,"modelExtensions"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Pathway::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		modelExtensions.push_back(boost::dynamic_pointer_cast<UniPAX::Model>(object));
		return true;
	}

	if (boost::iequals(attribute,"pathwayComponent") || boost::iequals(attribute,"component"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Pathway::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		pathwayComponent.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(object));
		return true;
	}
	if (boost::iequals(attribute,"pathwayOrder"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Pathway::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		pathwayOrder.push_back(boost::dynamic_pointer_cast<UniPAX::PathwayStep>(object));
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
			std::cerr << "Pathway::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		organism = boost::dynamic_pointer_cast<UniPAX::BioSource>(object);
		return true;
	}

	return false;

}


bool UniPAX::Pathway::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Entity::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::Model> >::iterator it;
		for (it = modelExtensions.begin(); it != modelExtensions.end(); it++)
		{
			if (!(*it))
			{
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					manager.setError(this->type() + ":modelExtensions contains unknown reference.");
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#modelExtensions", tmp));

			}
		}
	}
	tmp.clear();

	{
		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
		for (it = pathwayComponent.begin(); it != pathwayComponent.end(); it++)
		{
			if (!(*it))
			{
				//				value.push_back(std::pair<std::string,std::string>("#pathwayComponent", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					manager.setError(this->type() + ":pathwayComponents contains unknown reference.");
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#pathwayComponent", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::PathwayStep> >::iterator it;
		for (it = pathwayOrder.begin(); it != pathwayOrder.end(); it++)
		{
			if (!(*it))
			{
				//				value.push_back(std::pair<std::string,std::string>("#pathwayOrder", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					// due to a misuse in reactome database
					if (manager.pathwayStepsSkipped())
						return true;

					manager.setError(this->type() + ":pathwayOrder contains unknown reference.");
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#pathwayOrder", tmp));

			}
		}
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
			manager.setError(this->type() + ":organism contains unknown reference.");
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#organism", tmp));

	}

	return true;

}


//void UniPAX::Pathway::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Entity::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		{
//			modelExtensions.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_modelExtensions.begin(); it != id_modelExtensions.end(); it++)
//			{
//				modelExtensions.push_back(boost::dynamic_pointer_cast<UniPAX::Model>(getObjectByID(db, *it)));
//			}
//		}
//		{
//			pathwayComponent.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_pathwayComponent.begin(); it != id_pathwayComponent.end(); it++)
//			{
//				pathwayComponent.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(getObjectByID(db, *it)));
//			}
//		}
//		{
//			pathwayOrder.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_pathwayOrder.begin(); it != id_pathwayOrder.end(); it++)
//			{
//				pathwayOrder.push_back(boost::dynamic_pointer_cast<UniPAX::PathwayStep>(getObjectByID(db, *it)));
//			}
//		}
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		{
//			id_modelExtensions.clear();
//			std::vector<boost::shared_ptr<Model> >::iterator it;
//			for (it = modelExtensions.begin(); it != modelExtensions.end(); it++)
//			{
//				if (*it != 0)
//					id_modelExtensions.push_back((*it)->getUnipaxId());
//			}
//		}
//		{
//			id_pathwayComponent.clear();
//			std::vector<boost::shared_ptr<Entity> >::iterator it;
//			for (it = pathwayComponent.begin(); it != pathwayComponent.end(); it++)
//			{
//				if (*it != 0)
//					id_pathwayComponent.push_back((*it)->getUnipaxId());
//			}
//		}
//		{
//			id_pathwayOrder.clear();
//			std::vector<boost::shared_ptr<PathwayStep> >::iterator it;
//			for (it = pathwayOrder.begin(); it != pathwayOrder.end(); it++)
//			{
//				if (*it != 0)
//					id_pathwayOrder.push_back((*it)->getUnipaxId());
//			}
//		}
//	}
//
//	return;
//}

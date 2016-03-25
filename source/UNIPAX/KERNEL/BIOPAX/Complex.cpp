#include<UNIPAX/KERNEL/BIOPAX/Complex.h>
#include<set>
//Begin section for file Complex.cpp
//TODO: Add definitions that you want preserved
//End section for file Complex.cpp

UniPAX::Complex::Complex() : UniPAX::PhysicalEntity(),
	component(0),
	componentStoichiometry(0)
{
    }

UniPAX::Complex::Complex(const Complex & arg) : UniPAX::PhysicalEntity(arg),
	component(arg.component),
	componentStoichiometry(arg.componentStoichiometry)
//	id_component(arg.id_component)
{
    }

UniPAX::Complex & UniPAX::Complex::operator =(const Complex & arg)  {
	UniPAX::PhysicalEntity::operator=(arg);
	component = arg.component;
	componentStoichiometry = arg.componentStoichiometry;
	component = arg.component;
	componentStoichiometry = arg.componentStoichiometry;
//	id_component = arg.id_component;

	return *this;
}

UniPAX::Complex::~Complex()  {
    }

bool UniPAX::Complex::merge(Complex& object)
{

	{
		std::set<UniPAX::PhysicalEntityPtr> tmp(getComponents().begin(), getComponents().end());
		for (std::vector<UniPAX::PhysicalEntityPtr>::iterator pit = object.getComponents().begin(); pit != object.getComponents().end(); pit++)
		{
			if (*pit == 0)
			{
				tmp.insert(*pit);
			}
		}
		getComponents().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::StoichiometryPtr>tmp(getComponentStoichiometrys().begin(),getComponentStoichiometrys().end());
		for (std::vector<UniPAX::StoichiometryPtr>::iterator sit = object.getComponentStoichiometrys().begin(); sit != object.getComponentStoichiometrys().end(); sit++)
		{
			if (*sit == 0)
			{
				tmp.insert(*sit);
			}
		}
		getComponentStoichiometrys().assign(tmp.begin(), tmp.end());
	}

	return UniPAX::PhysicalEntity::merge(object);
}

bool UniPAX::Complex::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator it;
		for (it = component.begin(); it != component.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<PhysicalEntity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setComponents(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::Stoichiometry> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Stoichiometry> >::iterator it;
		for (it = componentStoichiometry.begin(); it != componentStoichiometry.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Stoichiometry>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setComponentStoichiometrys(tmp_vec);
	}

	return UniPAX::PhysicalEntity::update(manager);
}

const std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::Complex::getComponents() const {
        return component;
}

std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::Complex::getComponents() {
	return component;
}

void UniPAX::Complex::setComponents(std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > _components) {
	component = _components;
}

void UniPAX::Complex::addComponent(boost::shared_ptr<UniPAX::PhysicalEntity>  _component) {
	component.push_back(_component);
}

const std::vector<boost::shared_ptr<UniPAX::Stoichiometry> > & UniPAX::Complex::getComponentStoichiometrys() const {
        return componentStoichiometry;
}

std::vector<boost::shared_ptr<UniPAX::Stoichiometry> > & UniPAX::Complex::getComponentStoichiometrys() {
	return componentStoichiometry;
}

void UniPAX::Complex::setComponentStoichiometrys(std::vector<boost::shared_ptr<UniPAX::Stoichiometry> > _componentStoichiometrys) {
	componentStoichiometry = _componentStoichiometrys;
}

void UniPAX::Complex::addComponentStoichiometry(boost::shared_ptr<UniPAX::Stoichiometry>  _componentStoichiometry) {
	componentStoichiometry.push_back(_componentStoichiometry);
}

bool UniPAX::Complex::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::PhysicalEntity::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"component"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Complex::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		component.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object));
		return true;
	}

	if (boost::iequals(attribute,"componentStoichiometry"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Complex::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		componentStoichiometry.push_back(boost::dynamic_pointer_cast<UniPAX::Stoichiometry>(object));
		return true;
	}

	return false;

}


bool UniPAX::Complex::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::PhysicalEntity::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator pit;	
		for (pit = component.begin(); pit != component.end(); pit++)
		{
			if (*pit == 0)
			{
				// value.push_back(std::pair<std::string,std::string>("#component", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*pit,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#component", tmp));
			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::Stoichiometry> >::iterator sit;	
		for (sit = componentStoichiometry.begin(); sit != componentStoichiometry.end(); sit++)
		{
			if (*sit == 0)
			{
				// value.push_back(std::pair<std::string,std::string>("#componentStoichiometry", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*sit,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#componentStoichiometry", tmp));
			}
		}
	}


	return true;

}


//void UniPAX::Complex::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::PhysicalEntity::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		component.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_component.begin(); it != id_component.end(); it++)
//		{
//			component.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(getObjectByID(db, *it)));
//		}
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		id_component.clear();
//		std::vector<boost::shared_ptr<PhysicalEntity> >::iterator it;
//		for (it = component.begin(); it != component.end(); it++)
//		{
//			if (*it != 0)
//				id_component.push_back((*it)->getUnipaxId());
//		}
//
//	}
//
//	return;
//}

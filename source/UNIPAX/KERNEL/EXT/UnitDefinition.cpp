#include<UNIPAX/KERNEL/EXT/UnitDefinition.h>
#include <set>
//Begin section for file UnitDefinition.cpp
//TODO: Add definitions that you want preserved
//End section for file UnitDefinition.cpp

UniPAX::UnitDefinition::UnitDefinition() : UniPAX::SBase()//, pathway(0)
{
}

UniPAX::UnitDefinition::UnitDefinition(const UnitDefinition & arg) : UniPAX::SBase(arg) ,
		id(arg.id),
		name(arg.name),
		//pathway(arg.pathway),
		unit(arg.unit)
{}

UniPAX::UnitDefinition & UniPAX::UnitDefinition::operator =(const UnitDefinition & arg)  {
	UniPAX::SBase::operator=(arg);
	id = arg.id;
	name = arg.name;
	//pathway = arg.pathway;
	unit = arg.unit;

	return *this;
}

UniPAX::UnitDefinition::~UnitDefinition()  {
}

bool UniPAX::UnitDefinition::merge(UnitDefinition& object)
{
	if (id.empty())
	{
		id = object.getId();
	}
	else
	{
		if (id.compare(object.getId()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::Model::id not equal ..."
					<< id << " != " << object.getId() << std::endl;
			return false;
		}
	}

	if (name.empty())
	{
		name = object.getName();
	}
	else
	{
		if (name.compare(object.getName()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::Model::name not equal ..."
					<< name << " != " << object.getName() << std::endl;
			return false;
		}
	}

	{
			std::set<UniPAX::UnitPtr> tmp(getUnits().begin(), getUnits().end());
			for (std::vector<UniPAX::UnitPtr>::iterator it = object.getUnits().begin(); it != object.getUnits().end(); it++)
			{
				if (*it != 0)
				{
					tmp.insert(*it);
				}
			}
			getUnits().assign(tmp.begin(), tmp.end());
		}

	return UniPAX::SBase::merge(object);
}

bool UniPAX::UnitDefinition::update(PersistenceManager& manager)
{

	{
		std::vector<boost::shared_ptr<UniPAX::Unit> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Unit> >::iterator it;
		for (it = unit.begin(); it != unit.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Unit>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setUnits(tmp_vec);
	}

	return UniPAX::SBase::update(manager);
}

/*const boost::shared_ptr<UniPAX::Pathway> UniPAX::UnitDefinition::getPathway() const {
  return pathway;
  }

  boost::shared_ptr<UniPAX::Pathway> UniPAX::UnitDefinition::getPathway()  {
  return pathway;
  }

  void boost::shared_ptr<UniPAX::UnitDefinition::setPathway(UniPAX::Pathway> _pathway)  {
  pathway = _pathway;
  }*/

const std::string & UniPAX::UnitDefinition::getId() const {
	return id;
}

std::string & UniPAX::UnitDefinition::getId() {
	return id;
}

void UniPAX::UnitDefinition::setId(std::string _id) {
	id = _id;
}

const std::string & UniPAX::UnitDefinition::getName() const {
	return name;
}

std::string & UniPAX::UnitDefinition::getName() {
	return name;
}

void UniPAX::UnitDefinition::setName(std::string _name) {
	name = _name;
}

const std::vector<boost::shared_ptr<UniPAX::Unit> > UniPAX::UnitDefinition::getUnits() const {
	return unit;
}

std::vector<boost::shared_ptr<UniPAX::Unit> > UniPAX::UnitDefinition::getUnits()  {
	return unit;
}
void UniPAX::UnitDefinition::setUnits(std::vector<boost::shared_ptr<UniPAX::Unit> > _units)  {
	unit = _units;
}
void UniPAX::UnitDefinition::addUnit(boost::shared_ptr<UniPAX::Unit>  _unit)
{
	unit.push_back(_unit);
}


bool UniPAX::UnitDefinition::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {
	if (UniPAX::SBase::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"id"))
	{
		setId(value);
		return true;
	}
	if (boost::iequals(attribute,"name"))
	{
		setName(value);
		return true;
	}
	/*if (boost::iequals(attribute,"pathway"))
				  {
				  if (value == "NIL" || value.empty())
				  return true;
				  boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				  if (object == 0)
				  {
				  std::cerr << "UnitDefinition::setAttribute - object not known (value = " << value << ")" << std::endl;
				  return false;
				  }

				  pathway = boost::dynamic_pointer_cast<UniPAX::Pathway>(object);
				  return true;

				  }*/
	if (boost::iequals(attribute,"unit"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "UnitDefinition::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		unit.push_back(boost::dynamic_pointer_cast<UniPAX::Unit>(object));
		return true;
	}

	return false;
}


bool UniPAX::UnitDefinition::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
	if (!UniPAX::SBase::getAttribute(value, manager))
		return false;
	{
		if (! getId().empty())
			value.push_back(std::pair<std::string,std::string>("id", getId()));
	}
	{
		if (! getName().empty())
			value.push_back(std::pair<std::string,std::string>("name", getName()));
	}
	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::Unit> >::iterator it;
		for (it = unit.begin(); it != unit.end(); it++)
		{
			if (*it == 0)
			{
			}
			else
			{
				if (!manager.getId(*it,tmp))
				{
					manager.setError(this->type() + ":unit contains unknown reference.");
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#unit", tmp));

			}
		}
	}
	tmp.clear();
	/*{
				  if (*pathway == 0)
				  {
				  }
				  else
				  {
				  if (!manager.getId(*pathway,tmp))
				  {
				  manager.setError(this->type() + ":pathway contains unknown reference.");
				  return false;
				  }
				  value.push_back(std::pair<std::string,std::string>("#pathway", tmp));

				  }

				  }*/

	return true;

}


//void UniPAX::UnitDefinition::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::SBase::init(e,db);
//
//	return;
//}

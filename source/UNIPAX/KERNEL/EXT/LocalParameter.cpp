#include<UNIPAX/KERNEL/EXT/LocalParameter.h>
//Begin section for file LocalParameter.cpp
//TODO: Add definitions that you want preserved
//End section for file LocalParameter.cpp

UniPAX::LocalParameter::LocalParameter() : UniPAX::SBase()
										   //, kineticLaw(0)
										   , value(0.)
{
}

UniPAX::LocalParameter::LocalParameter(const LocalParameter& arg) : UniPAX::SBase(arg) ,
		id(arg.id),
		name(arg.name),
		value(arg.value),
		unit(arg.unit)
{}

UniPAX::LocalParameter & UniPAX::LocalParameter::operator =(const LocalParameter & arg)  {
		UniPAX::SBase::operator=(arg);
		id = arg.id;
		name = arg.name;
		value = arg.value;
		unit = arg.unit;

		return *this;
}

UniPAX::LocalParameter::~LocalParameter()  {
}

bool UniPAX::LocalParameter::merge(LocalParameter& object)
{
		if (!id.empty())
		{
				if (id.compare(object.getId()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::LocalParameter::id not equal ..."
								<< id << " != " << object.getId() << std::endl;
						return false;
				}
		}
		else
		{
				id = object.getId();
		}

		if (!name.empty())
		{
				if (name.compare(object.getName()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::LocalParameter::name not equal ..."
								<< name << " != " << object.getName() << std::endl;
						return false;
				}
		}
		else
		{
				name = object.getName();
		}

		if (!unit.empty())
		{
				if (unit.compare(object.getUnit()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::LocalParameter::unit not equal ..."
								<< unit << " != " << object.getUnit() << std::endl;
						return false;
				}
		}
		else
		{
				unit = object.getUnit();
		}

		value = object.getValue();

		return UniPAX::SBase::merge(object);
}

bool UniPAX::LocalParameter::update(PersistenceManager& manager)
{
		return UniPAX::SBase::update(manager);	
}

const std::string & UniPAX::LocalParameter::getId() const {
		return id;
}

std::string & UniPAX::LocalParameter::getId() {
		return id;
}

void UniPAX::LocalParameter::setId(std::string _id) {
		id = _id;
}

const std::string & UniPAX::LocalParameter::getName() const {
		return name;
}

std::string & UniPAX::LocalParameter::getName() {
		return name;
}

void UniPAX::LocalParameter::setName(std::string _name) {
		name = _name;
}

const double UniPAX::LocalParameter::getValue() const {
		return value;
}

double UniPAX::LocalParameter::getValue()  {
		return value;
}

void UniPAX::LocalParameter::setValue(double _value)  {
		value = _value;
}

const std::string & UniPAX::LocalParameter::getUnit() const {
		return unit;
}

std::string & UniPAX::LocalParameter::getUnit() {
		return unit;
}

void UniPAX::LocalParameter::setUnit(std::string _unit) {
		unit = _unit;
}

bool UniPAX::LocalParameter::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

		if (UniPAX::SBase::setAttribute(attribute, value, manager))
				return true;

		if (boost::iequals(attribute,"id"))
		{
				id = value;
				return true;
		}

		if (boost::iequals(attribute,"name"))
		{
				name = value;
				return true;
		}

		if (boost::iequals(attribute,"unit"))
		{
				unit = value;
				return true;
		}

		if (boost::iequals(attribute,"value"))
		{
				double tmp;
				if (manager.convertAttribute(value, tmp))
				{
						setValue(tmp);
						return true;
				}
				else
				{
						manager.setError(this->type() + ":value could not be converted from std::string.");
						return false;
				}
		}

		return false;
}

bool UniPAX::LocalParameter::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

		if (!UniPAX::SBase::getAttribute(value, manager))
				return false;

		if (!id.empty())
		{
				value.push_back(std::pair<std::string,std::string>("#id", id));
		}

		if (!name.empty())
		{
				value.push_back(std::pair<std::string,std::string>("#name", name));
		}

		if (!unit.empty())
		{
				value.push_back(std::pair<std::string,std::string>("#unit", unit));
		}
		std::string tmp;
		if (manager.convertAttribute(getValue(), tmp))
		{
				value.push_back(std::pair<std::string,std::string>("#value", tmp));
		}
		else
		{
				manager.setError(this->type() + ":value could not be converted to std::string.");
				return false;
		}

		return true;
}

//void UniPAX::LocalParameter::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		return;
//}

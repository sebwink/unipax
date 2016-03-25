#include<UNIPAX/KERNEL/EXT/Parameter.h>
//Begin section for file Parameter.cpp
//TODO: Add definitions that you want preserved
//End section for file Parameter.cpp

UniPAX::Parameter::Parameter() : UniPAX::SBase(), value(0.), constant(false)//, pathway(0)
{
}

UniPAX::Parameter::Parameter(const Parameter & arg) : UniPAX::SBase(arg) ,
    constant(arg.constant),
	id(arg.id),
	name(arg.name),
    value(arg.value),
	units(arg.units)
    //pathway(arg.pathway)
{}
UniPAX::Parameter & UniPAX::Parameter::operator =(const Parameter & arg)  {
	UniPAX::SBase::operator=(arg);
	constant = arg.constant;
	id = arg.id;
	name = arg.name;
    value = arg.value;
	units = arg.units;
    //pathway = arg.pathway;

	return *this;
}

UniPAX::Parameter::~Parameter()  {
    }

bool UniPAX::Parameter::merge(Parameter& object)
{
		if (constant != object.getConstant())
		{
			std::cerr << "Error during merging: UniPAX::Parameter::constant not equal ..."
					<< constant << " != " << object.getConstant() << std::endl;
			return false;
		}

		if (value != object.getValue())
		{
			std::cerr << "Error during merging: UniPAX::Parameter::value not equal ..."
					<< value << " != " << object.getValue() << std::endl;
			return false;
		}

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

		if (units.empty())
		{
			units = object.getUnits();
		}
		else
		{
			if (units.compare(object.getUnits()) != 0)
			{
				std::cerr << "Error during merging: UniPAX::Model::units not equal ..."
						<< units << " != " << object.getUnits() << std::endl;
				return false;
			}
		}

	return UniPAX::SBase::merge(object);
}

bool UniPAX::Parameter::update(PersistenceManager& manager)
{
	return UniPAX::SBase::update(manager);
}

const bool UniPAX::Parameter::getConstant() const {
	return constant;
}

bool UniPAX::Parameter::getConstant()  {
        return constant;
}
void UniPAX::Parameter::setConstant(bool _constant)  {
        constant = _constant;
}

const std::string & UniPAX::Parameter::getId() const {
        return id;
}

std::string & UniPAX::Parameter::getId() {
	return id;
}

void UniPAX::Parameter::setId(std::string _id) {
	id = _id;
}

const std::string & UniPAX::Parameter::getName() const {
        return name;
}

std::string & UniPAX::Parameter::getName() {
	return name;
}

void UniPAX::Parameter::setName(std::string _name) {
	name = _name;
}

const double UniPAX::Parameter::getValue() const {
	return value;
}

double UniPAX::Parameter::getValue()  {
        return value;
}

void UniPAX::Parameter::setValue(double _value)  {
        value = _value;
}

const std::string & UniPAX::Parameter::getUnits() const {
        return units;
}

std::string & UniPAX::Parameter::getUnits() {
	return units;
}

void UniPAX::Parameter::setUnits(std::string _units) {
	units = _units;
}

/*const boost::shared_ptr<UniPAX::Pathway> UniPAX::Parameter::getPathway() const {
	return pathway;
}

boost::shared_ptr<UniPAX::Pathway> UniPAX::Parameter::getPathway()  {
        return pathway;
}

void boost::shared_ptr<UniPAX::Parameter::setPathway(UniPAX::Pathway> _pathway)  {
    	pathway = _pathway;
}*/

bool UniPAX::Parameter::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {
	if (UniPAX::SBase::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"constant"))
	{
		return (PersistenceManager::convertAttribute(value, constant));
	}
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
	if (boost::iequals(attribute,"value"))
	{
		return (PersistenceManager::convertAttribute(value, this->value));
	}
	if (boost::iequals(attribute,"units"))
	{
		setUnits(value);
		return true;
	}

	return false;
}

bool UniPAX::Parameter::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
	if (!UniPAX::SBase::getAttribute(value, manager))
		return false;

	if (!getId().empty())
		value.push_back(std::pair<std::string,std::string>("id", getId()));
	if (!getName().empty())
		value.push_back(std::pair<std::string,std::string>("name", getName()));
	if (!getUnits().empty())
		value.push_back(std::pair<std::string,std::string>("units", getName()));

	std::string tmp = "";
	/*if (pathway == 0)
	{
	}
	else
	{
		tmp.clear();
		if (!manager.getId(pathway,tmp))
		{
			manager.setError(this->type() + ":pathway contains unknown reference.");
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#pathway", tmp));

	}
	tmp.clear();
	if (!PersistenceManager::convertAttribute(getValue(), tmp))
	{
		return false;
	}*/
	if (getValue() != 0.)
		value.push_back(std::pair<std::string,std::string>("value", tmp));
	tmp.clear();
	if (!PersistenceManager::convertAttribute(constant, tmp))
	{
		return false;
	}
	value.push_back(std::pair<std::string,std::string>("constant", tmp));

	return true;
}

//void UniPAX::Parameter::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::SBase::init(e,db);
//
//	return;
//}

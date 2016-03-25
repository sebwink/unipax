#include<UNIPAX/KERNEL/EXT/Unit.h>
//Begin section for file Unit.cpp
//TODO: Add definitions that you want preserved
//End section for file Unit.cpp

UniPAX::Unit::Unit() : UniPAX::SBase(), multiplier(0.), scale(0.), exponent(0)
// , unitDefinition(0)
{
}

UniPAX::Unit::Unit(const Unit & arg) : UniPAX::SBase(arg) ,
		exponent(arg.exponent),
		kind(arg.kind),
		multiplier(arg.multiplier),
		scale(arg.scale),
		unitDefinition(arg.unitDefinition)
{}

UniPAX::Unit & UniPAX::Unit::operator =(const Unit & arg)  {
	UniPAX::SBase::operator=(arg);
	exponent = arg.exponent;
	kind = arg.kind;
	multiplier = arg.multiplier;
	scale = arg.scale;
	unitDefinition = arg.unitDefinition;

	return *this;
}

UniPAX::Unit::~Unit()  {
}

bool UniPAX::Unit::merge(UniPAX::Unit& object)
{
	if (exponent != object.getExponent())
	{
		std::cerr << "Error during merging: UniPAX::Unit::exponent not equal ..."
				<< exponent << " != " << object.getExponent() << std::endl;
		return false;
	}

	if (kind.empty())
	{
		kind = object.getKind();
	}
	else
	{
		if (kind.compare(object.getKind()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::Unit::kind not equal ..."
					<< kind << " != " << object.getKind() << std::endl;
			return false;
		}
	}

	if (multiplier != object.getMultiplier())
	{
		std::cerr << "Error during merging: UniPAX::Unit::multiplier not equal ..."
				<< multiplier << " != " << object.getMultiplier() << std::endl;
		return false;
	}

	if (scale != object.getScale())
	{
		std::cerr << "Error during merging: UniPAX::Unit::scale not equal ..."
				<< scale << " != " << object.getScale() << std::endl;
		return false;
	}

	if (unitDefinition == 0)
	{
		unitDefinition = object.getUnitDefinition();
	}
	else
	{
		if (object.getUnitDefinition() != 0)
		{
			if (unitDefinition->getUnipaxId() != object.getUnitDefinition()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::Unit::unitDefinition not equal ..."
						<< unitDefinition->getUnipaxId() << " != " << object.getUnitDefinition()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}

	return SBase::merge(object);
}

bool UniPAX::Unit::update(PersistenceManager& manager)
{

	// check single pointer if object was merged
	if (manager.isMerged(getUnitDefinition()))
	{
		setUnitDefinition(boost::dynamic_pointer_cast<UnitDefinition>(manager.getMergedObject(getUnitDefinition())));
	}

	return UniPAX::SBase::update(manager);
}

const int UniPAX::Unit::getExponent() const {
	return exponent;
}

int UniPAX::Unit::getExponent()  {
	return exponent;
}

void UniPAX::Unit::setExponent(int _exponent)  {
	exponent = _exponent;
}

const std::string & UniPAX::Unit::getKind() const {
	return kind;
}

std::string & UniPAX::Unit::getKind() {
	return kind;
}

void UniPAX::Unit::setKind(std::string _kind) {
	kind = _kind;
}

const double UniPAX::Unit::getMultiplier() const {
	return multiplier;
}

double UniPAX::Unit::getMultiplier()  {
	return multiplier;
}

void UniPAX::Unit::setMultiplier(double _multiplier)  {
	multiplier = _multiplier;
}

const double UniPAX::Unit::getScale() const {
	return scale;
}

double UniPAX::Unit::getScale()  {
	return scale;
}

void UniPAX::Unit::setScale(double _scale)  {
	scale = _scale;
}

const boost::shared_ptr<UniPAX::UnitDefinition> UniPAX::Unit::getUnitDefinition() const {
	return unitDefinition;
}

boost::shared_ptr<UniPAX::UnitDefinition> UniPAX::Unit::getUnitDefinition()  {
	return unitDefinition;
}
void UniPAX::Unit::setUnitDefinition(boost::shared_ptr<UniPAX::UnitDefinition> _unitDefinition)  {
	unitDefinition = _unitDefinition;
}


bool UniPAX::Unit::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::SBase::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"exponent"))
	{
		double tmp;
		if (manager.convertAttribute(value, tmp))
		{
			setExponent(tmp);
			return true;
		}
		else
		{
			manager.setError(this->type() + ":exponent could not be converted from std::string.");
			return false;
		}
	}

	if (boost::iequals(attribute,"kind"))
	{
		kind = value;
		return true;
	}

	if (boost::iequals(attribute,"multiplier"))
	{
		double tmp;
		if (manager.convertAttribute(value, tmp))
		{
			setMultiplier(tmp);
			return true;
		}
		else
		{
			manager.setError(this->type() + ":multiplier could not be converted from std::string.");
			return false;
		}
	}

	if (boost::iequals(attribute,"scale"))
	{
		double tmp;
		if (manager.convertAttribute(value, tmp))
		{
			setScale(tmp);
			return true;
		}
		else
		{
			manager.setError(this->type() + ":scale could not be converted from std::string.");
			return false;
		}
	}

	if (boost::iequals(attribute,"unitDefinition"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Unit::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		setUnitDefinition(boost::dynamic_pointer_cast<UniPAX::UnitDefinition>(object));
		return true;
	}
	return false;

}


bool UniPAX::Unit::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::SBase::getAttribute(value, manager))
		return false;

	std::string tmp;
	if (manager.convertAttribute(getExponent(), tmp))
	{
		value.push_back(std::pair<std::string,std::string>("#exponent", tmp));
	}
	else
	{
		manager.setError(this->type() + ":exponent could not be converted to std::string.");
		return false;
	}

	if (!kind.empty())
	{
		value.push_back(std::pair<std::string,std::string>("kind", getKind()));
	}

	tmp.clear();
	if (manager.convertAttribute(getMultiplier(), tmp))
	{
		value.push_back(std::pair<std::string,std::string>("multiplier", tmp));
	}
	else
	{
		manager.setError(this->type() + ":multiplier could not be converted to std::string.");
		return false;
	}

	tmp.clear();
	if (manager.convertAttribute(getScale(), tmp))
	{
		value.push_back(std::pair<std::string,std::string>("scale", tmp));
	}
	else
	{
		manager.setError(this->type() + ":scale could not be converted to std::string.");
		return false;
	}

	{
		if (unitDefinition == 0)
		{
		}
		else
		{
			tmp.clear();
			if (!manager.getId(unitDefinition,tmp))
			{
				manager.setError(this->type() + ":unitDefinition contains unknown reference.");
				return false;
			}
			value.push_back(std::pair<std::string,std::string>("#unitDefinition", tmp));

		}
		return true;
	}
}

//void UniPAX::Unit::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::SBase::init(e,db);
//
//	return;
//}

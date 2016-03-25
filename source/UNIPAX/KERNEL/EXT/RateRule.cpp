#include<UNIPAX/KERNEL/EXT/RateRule.h>
//Begin section for file RateRule.cpp
//TODO: Add definitions that you want preserved
//End section for file RateRule.cpp

UniPAX::RateRule::RateRule() : UniPAX::Rule() {
}

UniPAX::RateRule::RateRule(const RateRule & arg) : UniPAX::Rule(arg) ,
		variable(arg.variable)
{}

UniPAX::RateRule & UniPAX::RateRule::operator =(const RateRule & arg)  {
	UniPAX::Rule::operator=(arg);
	variable = arg.variable;

	return *this;
}

UniPAX::RateRule::~RateRule()  {
}

bool UniPAX::RateRule::merge(RateRule& object)
{
	if (variable.empty())
	{
		variable = object.getVariable();
	}
	else
	{
		if (variable.compare(object.getVariable()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::RateRule::variable not equal ..."
					<< variable << " != " << object.getVariable() << std::endl;
			return false;
		}
	}

	return UniPAX::Rule::merge(object);
}

bool UniPAX::RateRule::update(PersistenceManager& manager)
{
	return UniPAX::Rule::update(manager);
}

const std::string & UniPAX::RateRule::getVariable() const {
	return variable;
}

std::string & UniPAX::RateRule::getVariable() {
	return variable;
}

void UniPAX::RateRule::setVariable(std::string _variable) {
	variable = _variable;
}

bool UniPAX::RateRule::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {
	if (UniPAX::Rule::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"variable"))
	{
		setVariable(value);
		return true;
	}


	return false;
}

bool UniPAX::RateRule::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
	if (!UniPAX::Rule::getAttribute(value, manager))
		return false;
	if (!getVariable().empty())
		value.push_back(std::pair<std::string,std::string>("#variable", getVariable()));


	return true;
}


//void UniPAX::RateRule::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::Rule::init(e,db);
//
//		return;
//}

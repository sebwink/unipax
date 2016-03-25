#include<UNIPAX/KERNEL/EXT/AssignmentRule.h>
//Begin section for file AssignmentRule.cpp
//TODO: Add definitions that you want preserved
//End section for file AssignmentRule.cpp

UniPAX::AssignmentRule::AssignmentRule() : UniPAX::Rule() {
}

UniPAX::AssignmentRule::AssignmentRule(const AssignmentRule & arg) : UniPAX::Rule(arg) ,
		variable(arg.variable)
{}

UniPAX::AssignmentRule & UniPAX::AssignmentRule::operator =(const AssignmentRule & arg)  {
	UniPAX::Rule::operator=(arg);
	variable = arg.variable;

	return *this;
}

UniPAX::AssignmentRule::~AssignmentRule()  {
}

bool UniPAX::AssignmentRule::merge(AssignmentRule& object)
{
	if (!variable.empty())
	{
		if (variable.compare(object.getVariable()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::AssignmentRule::variable not equal ..."
					<< variable << " != " << object.getVariable() << std::endl;
			return false;
		}
	}
	else
	{
		setVariable(object.getVariable());
	}

	return UniPAX::Rule::merge(object);

}

bool UniPAX::AssignmentRule::update(PersistenceManager& manager)
{
	return UniPAX::Rule::update(manager);
}


const std::string & UniPAX::AssignmentRule::getVariable() const {
	return variable;
}

std::string & UniPAX::AssignmentRule::getVariable() {
	return variable;
}

void UniPAX::AssignmentRule::setVariable(std::string _variable) {
	variable = _variable;
}

bool UniPAX::AssignmentRule::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {
	if (UniPAX::Rule::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"variable"))
	{
		setVariable(value);
		return true;
	}

	return false;
}

bool UniPAX::AssignmentRule::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
	if (!UniPAX::Rule::getAttribute(value, manager))
		return false;
	if (!getVariable().empty())
		value.push_back(std::pair<std::string,std::string>("#variable", getVariable()));

	return true;
}


//void UniPAX::AssignmentRule::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::Rule::init(e,db);
//
//		return;
//}

#include<UNIPAX/KERNEL/EXT/AlgebraicRule.h>
//Begin section for file AlgebraicRule.cpp
//TODO: Add definitions that you want preserved
//End section for file AlgebraicRule.cpp

UniPAX::AlgebraicRule::AlgebraicRule() : UniPAX::Rule() {
}

UniPAX::AlgebraicRule::AlgebraicRule(const AlgebraicRule & arg) : UniPAX::Rule(arg)
{
}

UniPAX::AlgebraicRule & UniPAX::AlgebraicRule::operator =(const AlgebraicRule & arg)  {
		UniPAX::Rule::operator=(arg);

		return *this;
}

UniPAX::AlgebraicRule::~AlgebraicRule()  {
}

bool UniPAX::AlgebraicRule::merge(AlgebraicRule& object)
{
		return UniPAX::Rule::merge(object);
}

bool UniPAX::AlgebraicRule::update(PersistenceManager& manager)
{
		return UniPAX::Rule::update(manager);
}

bool UniPAX::AlgebraicRule::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager)
{
		if (UniPAX::Rule::setAttribute(attribute, value, manager))
				return true;

		return false;
}

bool UniPAX::AlgebraicRule::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager)
{
		if (!UniPAX::Rule::getAttribute(value, manager))
				return false;

		return true;
}


//void UniPAX::AlgebraicRule::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::Rule::init(e,db);
//
//		return;
//}

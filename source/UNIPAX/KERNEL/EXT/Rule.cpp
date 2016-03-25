#include<UNIPAX/KERNEL/EXT/Rule.h>
//Begin section for file Rule.cpp
//TODO: Add definitions that you want preserved
//End section for file Rule.cpp

UniPAX::Rule::Rule() : UniPAX::SBase()
//, math(0)//, pathway(0)
{
}

UniPAX::Rule::Rule(const Rule & arg) : UniPAX::SBase(arg) ,
		//pathway(arg.pathway),
		math(arg.math)
{}
UniPAX::Rule & UniPAX::Rule::operator =(const Rule & arg)  {
	UniPAX::SBase::operator=(arg);
	//pathway = arg.pathway;
	math = arg.math;

	return *this;
}

UniPAX::Rule::~Rule()  {
}

bool UniPAX::Rule::merge(Rule& object)
{

	if (math != 0)
	{
		if (object.getMath() != 0)
		{
			if (math->getMathML().compare(object.getMath()->getMathML()) != 0)
			{
				std::cerr << "Error during merging: UniPAX::Rule::math not equal ..."
						<< math->getMathML() << " != " << object.getMath()->getMathML() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setMath(object.getMath());
	}

	return UniPAX::SBase::merge(object);

}

bool UniPAX::Rule::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getMath()))
	{
		setMath(boost::dynamic_pointer_cast<Math>(manager.getMergedObject(getMath())));
	}

	return UniPAX::SBase::update(manager);
}

/*const boost::shared_ptr<UniPAX::Pathway> UniPAX::Rule::getPathway() const {
  return pathway;
  }

  boost::shared_ptr<UniPAX::Pathway> UniPAX::Rule::getPathway()  {
  return pathway;
  }

  void boost::shared_ptr<UniPAX::Rule::setPathway(UniPAX::Pathway> _pathway)  {
  pathway = _pathway;
  }*/

const boost::shared_ptr<UniPAX::Math> UniPAX::Rule::getMath() const {
	return math;
}

boost::shared_ptr<UniPAX::Math> UniPAX::Rule::getMath()  {
	return math;
}
void UniPAX::Rule::setMath(boost::shared_ptr<UniPAX::Math> _math)  {
	math = _math;
}

bool UniPAX::Rule::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {
	if (UniPAX::SBase::setAttribute(attribute, value, manager))
		return true;
	if (boost::iequals(attribute,"math"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Math::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		math = boost::dynamic_pointer_cast<UniPAX::Math>(object);
		return true;
	}

	return false;
}

bool UniPAX::Rule::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
	if (!UniPAX::SBase::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (math == 0)
	{
		//		value.push_back(std::pair<std::string,std::string>("#math", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(math,tmp))
		{
			manager.setError(this->type() + ":math contains unknown reference.");
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#math", tmp));

	}

	return true;
}

//void UniPAX::Rule::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::SBase::init(e,db);
//
//	return;
//}

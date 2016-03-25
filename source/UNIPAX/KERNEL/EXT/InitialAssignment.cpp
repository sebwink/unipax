#include<UNIPAX/KERNEL/EXT/InitialAssignment.h>
//Begin section for file InitialAssignment.cpp
//TODO: Add definitions that you want preserved
//End section for file InitialAssignment.cpp

UniPAX::InitialAssignment::InitialAssignment() : UniPAX::SBase()
												 //, math(0)//, pathway(0)
{
}

UniPAX::InitialAssignment::InitialAssignment(const InitialAssignment& arg) : UniPAX::SBase(arg) ,
		symbol(arg.symbol),
		//pathway(arg.pathway),
		math(arg.math)
{
}

UniPAX::InitialAssignment & UniPAX::InitialAssignment::operator =(const InitialAssignment & arg)  {
		UniPAX::SBase::operator=(arg);
		symbol = arg.symbol;
		//pathway = arg.pathway;
		math = arg.math;

		return *this;
}

UniPAX::InitialAssignment::~InitialAssignment()  {
}

bool UniPAX::InitialAssignment::merge(InitialAssignment& object)
{
		if (math != 0)
		{
				if (object.getMath() != 0)
				{
						if (math->getMathML().compare(object.getMath()->getMathML()) != 0)
						{
								std::cerr << "Error during merging: UniPAX::Constraint::math not equal ..."
										<< math->getMathML() << " != " << object.getMath()->getMathML() << std::endl;
								return false;
						}
				}
		}
		else
		{
				setMath(object.getMath());
		}

		if (!symbol.empty())
		{
				if (symbol.compare(object.getSymbol()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Constraint::symbol not equal ..."
								<< symbol << " != " << object.getSymbol() << std::endl;
						return false;
				}
		}
		else
		{
				setSymbol(object.getSymbol());
		}

		return UniPAX::SBase::merge(object);

}

bool UniPAX::InitialAssignment::update(UniPAX::PersistenceManager& manager)
{
		// check single pointer if object was merged
		if (manager.isMerged(getMath()))
		{
				setMath(boost::dynamic_pointer_cast<UniPAX::Math>(manager.getMergedObject(getMath())));
		}
		return UniPAX::SBase::update(manager);
}

const std::string & UniPAX::InitialAssignment::getSymbol() const {
		return symbol;
}

std::string & UniPAX::InitialAssignment::getSymbol() {
		return symbol;
}

void UniPAX::InitialAssignment::setSymbol(std::string _symbol) {
		symbol = _symbol;
}

/*const UniPAX::Pathway * UniPAX::InitialAssignment::getPathway() const {
  return pathway;
  }

  UniPAX::Pathway * UniPAX::InitialAssignment::getPathway()  {
  return pathway;
  }

  void UniPAX::InitialAssignment::setPathway(UniPAX::Pathway * _pathway)  {
  pathway = _pathway;
  }*/


const boost::shared_ptr<UniPAX::Math> UniPAX::InitialAssignment::getMath() const {
		return math;
}

boost::shared_ptr<UniPAX::Math> UniPAX::InitialAssignment::getMath()  {
		return math;
}

void UniPAX::InitialAssignment::setMath(boost::shared_ptr<UniPAX::Math> _math)  {
		math = _math;
}


bool UniPAX::InitialAssignment::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

		if (UniPAX::SBase::setAttribute(attribute, value, manager))
				return true;

		if (boost::iequals(attribute,"symbol"))
		{
				setSymbol(value);
				return true;
		}

		/*if (boost::iequals(attribute,"pathway"))
		  {
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
		return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
		std::cerr << "InitialAssignment::setAttribute - object not known (value = " << value << ")" << std::endl;
		return false;
		}

		pathway = boost::dynamic_pointer_cast<UniPAX::Pathway>(object);
		return true;
		}*/

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

bool UniPAX::InitialAssignment::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

		if (!UniPAX::SBase::getAttribute(value, manager))
				return false;

		std::string tmp = "";
		/*if (pathway == 0)
		  {
		//		value.push_back(std::pair<std::string,std::string>("#pathway", "NIL"));
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
		tmp.clear();*/

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

		if (!getSymbol().empty())
				value.push_back(std::pair<std::string,std::string>("#symbol", getSymbol()));

		return true;

}


//void UniPAX::InitialAssignment::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		return;
//}

#include<UNIPAX/KERNEL/EXT/EventAssignment.h>
//Begin section for file EventAssignment.cpp
//TODO: Add definitions that you want preserved
//End section for file EventAssignment.cpp

UniPAX::EventAssignment::EventAssignment() : UniPAX::SBase()
											 //, math(0)
{
}

UniPAX::EventAssignment::EventAssignment(const EventAssignment& arg) : UniPAX::SBase(arg) ,
		variable(arg.variable),
		math(arg.math)
{
}

UniPAX::EventAssignment & UniPAX::EventAssignment::operator =(const EventAssignment & arg)  {
		UniPAX::SBase::operator=(arg);
		variable = arg.variable;
		math = arg.math;

		return *this;
}

UniPAX::EventAssignment::~EventAssignment()  {
}

bool UniPAX::EventAssignment::merge(UniPAX::EventAssignment& object)
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


		if (!variable.empty())
		{
				if (variable.compare(object.getVariable()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Constraint::variable not equal ..."
								<< variable << " != " << object.getVariable() << std::endl;
						return false;
				}
		}
		else
		{
				setVariable(object.getVariable());
		}

		return UniPAX::SBase::merge(object);
}

bool UniPAX::EventAssignment::update(PersistenceManager& manager)
{
		// check single pointer if object was merged
		if (manager.isMerged(getMath()))
		{
				setMath(boost::dynamic_pointer_cast<UniPAX::Math>(manager.getMergedObject(getMath())));
		}

		return UniPAX::SBase::update(manager);
}

const std::string & UniPAX::EventAssignment::getVariable() const {
		return variable;
}

std::string & UniPAX::EventAssignment::getVariable() {
		return variable;
}

void UniPAX::EventAssignment::setVariable(std::string _variable) {
		variable = _variable;
}


const boost::shared_ptr<UniPAX::Math> UniPAX::EventAssignment::getMath() const {
		return math;
}

boost::shared_ptr<UniPAX::Math> UniPAX::EventAssignment::getMath() {
		return math;
}

void UniPAX::EventAssignment::setMath(boost::shared_ptr<UniPAX::Math> _math) {
		math = _math;
}


bool UniPAX::EventAssignment::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

		if (UniPAX::SBase::setAttribute(attribute, value, manager))
				return true;

		if (boost::iequals(attribute,"variable"))
		{
				setVariable(value);
				return true;
		}
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

		bool UniPAX::EventAssignment::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
				if (!UniPAX::SBase::getAttribute(value, manager))
						return false;

				value.push_back(std::pair<std::string,std::string>("variable", getVariable()));

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


//void UniPAX::EventAssignment::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		return;
//}

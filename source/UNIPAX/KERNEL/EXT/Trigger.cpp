#include<UNIPAX/KERNEL/EXT/Trigger.h>
//Begin section for file Trigger.cpp
//TODO: Add definitions that you want preserved
//End section for file Trigger.cpp

UniPAX::Trigger::Trigger() : UniPAX::SBase(), initialValue(0.)
, persistent(false)
							 //, math(0)
{
}

UniPAX::Trigger::Trigger(const Trigger & arg) : UniPAX::SBase(arg) ,
		initialValue(arg.initialValue),
		persistent(arg.persistent),
		math(arg.math)
{}

UniPAX::Trigger & UniPAX::Trigger::operator =(const Trigger & arg)  {
		UniPAX::SBase::operator=(arg);
		initialValue = arg.initialValue;
		persistent = arg.persistent;
		math = arg.math;

		return *this;
}

UniPAX::Trigger::~Trigger()  {
}

bool UniPAX::Trigger::merge(Trigger& object)
{
		if (initialValue != object.getInitialValue())
		{
				std::cerr << "Error during merging: UniPAX::Trigger::initialValue not equal ..."
						<< initialValue << " != " << object.getInitialValue() << std::endl;
				return false;
		}

		if (persistent != object.getPersistent())
		{
				std::cerr << "Error during merging: UniPAX::Trigger::persistent not equal ..."
						<< persistent << " != " << object.getPersistent() << std::endl;
				return false;
		}
		if (math != 0)
		{
				if (object.getMath() != 0)
				{
						if (math->getMathML().compare(object.getMath()->getMathML()) != 0)
						{
								std::cerr << "Error during merging: UniPAX::Trigger::math not equal ..."
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

bool UniPAX::Trigger::update(PersistenceManager& manager)
{
		// check single pointer if object was merged
		if (manager.isMerged(getMath()))
		{
				setMath(boost::dynamic_pointer_cast<UniPAX::Math>(manager.getMergedObject(getMath())));
		}
		return UniPAX::SBase::update(manager);
}

const double UniPAX::Trigger::getInitialValue() const {
		return initialValue;
}

double UniPAX::Trigger::getInitialValue()  {
		return initialValue;
}

void UniPAX::Trigger::setInitialValue(double _initialValue)  {
		initialValue = _initialValue;
}

const bool UniPAX::Trigger::getPersistent() const {
		return persistent;
}

bool UniPAX::Trigger::getPersistent()  {
		return persistent;
}

void UniPAX::Trigger::setPersistent(bool _persistent)  {
		persistent = _persistent;
}

const boost::shared_ptr<UniPAX::Math> UniPAX::Trigger::getMath() const {
		return math;
}

boost::shared_ptr<UniPAX::Math> UniPAX::Trigger::getMath()  {
		return math;
}

void UniPAX::Trigger::setMath(boost::shared_ptr<UniPAX::Math> _math)  {
		math = _math;
}

bool UniPAX::Trigger::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

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
						std::cerr << "Trigger::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				math = boost::dynamic_pointer_cast<UniPAX::Math>(object);
				return true;
		}
		if (boost::iequals(attribute,"initialValue"))
		{
				return (PersistenceManager::convertAttribute(value,initialValue));
		}
		if (boost::iequals(attribute,"persistent"))
		{
				return (PersistenceManager::convertAttribute(value,persistent));
		}

		return false;
}


		bool UniPAX::Trigger::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
				if (!UniPAX::SBase::getAttribute(value, manager))
						return false;
				std::string tmp = "";
				if (!PersistenceManager::convertAttribute(initialValue, tmp)) {
						return false;
				}
				value.push_back(std::pair<std::string,std::string>("initialValue", tmp));
				tmp.clear();
				if (!PersistenceManager::convertAttribute(persistent, tmp)) {
						return false;
				}
				value.push_back(std::pair<std::string,std::string>("persistent", tmp));
				if (math == 0)
				{
						manager.setError(this->type() + ":math is null pointer.");
						return false;
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

//void UniPAX::Trigger::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		return;
//}

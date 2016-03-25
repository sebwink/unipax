#include<UNIPAX/KERNEL/EXT/Delay.h>
//Begin section for file Delay.cpp
//TODO: Add definitions that you want preserved
//End section for file Delay.cpp

UniPAX::Delay::Delay() : UniPAX::SBase()
						 //, math(0)
{
}

UniPAX::Delay::Delay(const Delay& arg) : UniPAX::SBase(arg) ,
		math(arg.math)
{
}

UniPAX::Delay & UniPAX::Delay::operator =(const Delay & arg)  {
		UniPAX::SBase::operator=(arg);
		math = arg.math;

		return *this;
}

UniPAX::Delay::~Delay()  {
}

bool UniPAX::Delay::merge(Delay& object)
{

		if (math != 0)
		{
				if (object.getMath() != 0)
				{
						if (math->getMathML().compare(object.getMath()->getMathML()) != 0)
						{
								std::cerr << "Error during merging: UniPAX::Delay::math not equal ..."
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

bool UniPAX::Delay::update(PersistenceManager& manager)
{
		// check single pointer if object was merged
		if (manager.isMerged(getMath()))
		{
				setMath(boost::dynamic_pointer_cast<UniPAX::Math>(manager.getMergedObject(getMath())));
		}
		return UniPAX::SBase::update(manager);
}

const boost::shared_ptr<UniPAX::Math> UniPAX::Delay::getMath() const {
		return math;
}

boost::shared_ptr<UniPAX::Math> UniPAX::Delay::getMath()  {
		return math;
}

void UniPAX::Delay::setMath(boost::shared_ptr<UniPAX::Math> _math)  {
		math = _math;
}


bool UniPAX::Delay::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

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

bool UniPAX::Delay::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

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



//void UniPAX::Delay::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		return;
//}

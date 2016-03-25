#include<UNIPAX/KERNEL/EXT/Priority.h>
//Begin section for file Priority.cpp
//TODO: Add definitions that you want preserved
//End section for file Priority.cpp

UniPAX::Priority::Priority() : UniPAX::SBase()
							   //, math(0)
{
}

UniPAX::Priority::Priority(const Priority & arg) : UniPAX::SBase(arg) ,
		math(arg.math)
{}

UniPAX::Priority & UniPAX::Priority::operator =(const Priority & arg)  {
		UniPAX::SBase::operator=(arg);
		math = arg.math;

		return *this;
}

UniPAX::Priority::~Priority()  {
}

bool UniPAX::Priority::merge(Priority& object)
{

		if (math != 0)
		{
				if (object.getMath() != 0)
				{
						if (math->getMathML().compare(object.getMath()->getMathML()) != 0)
						{
								std::cerr << "Error during merging: UniPAX::Priority::math not equal ..."
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

bool UniPAX::Priority::update(PersistenceManager& manager)
{
		// check single pointer if object was merged
		if (manager.isMerged(getMath()))
		{
				setMath(boost::dynamic_pointer_cast<UniPAX::Math>(manager.getMergedObject(getMath())));
		}
		return UniPAX::SBase::update(manager);
}

const boost::shared_ptr<UniPAX::Math> UniPAX::Priority::getMath() const {
		return math;
}

boost::shared_ptr<UniPAX::Math> UniPAX::Priority::getMath()  {
		return math;
}

void UniPAX::Priority::setMath(boost::shared_ptr<UniPAX::Math> _math)  {
		math = _math;
}

		bool UniPAX::Priority::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {
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
								std::cerr << "priority::setAttribute - object not known (value = " << value << ")" << std::endl;
								return false;
						}

						math = boost::dynamic_pointer_cast<UniPAX::Math>(object);
						return true;
				}

				return false;
		}

		bool UniPAX::Priority::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
				if (!UniPAX::SBase::getAttribute(value, manager))
						return false;
				std::string tmp = "";
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

//void UniPAX::Priority::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		return;
//}

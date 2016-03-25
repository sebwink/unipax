#include<UNIPAX/KERNEL/EXT/Constraint.h>
//Begin section for file Constraint.cpp
//TODO: Add definitions that you want preserved
//End section for file Constraint.cpp

UniPAX::Constraint::Constraint() : UniPAX::SBase()
//,
//math(0)
{
}

UniPAX::Constraint::Constraint(const Constraint& arg) : UniPAX::SBase(arg) ,
		math(arg.math),
		message(arg.message)
{
}

UniPAX::Constraint & UniPAX::Constraint::operator =(const Constraint & arg)  {
	UniPAX::SBase::operator=(arg);
	math = arg.math;
	message = arg.message;

	return *this;
}

UniPAX::Constraint::~Constraint()  {
}

bool UniPAX::Constraint::merge(Constraint& object)
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


	if (!message.empty())
	{
		if (message.compare(object.getMessage()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::Constraint::message not equal ..."
					<< message << " != " << object.getMessage() << std::endl;
			return false;
		}
	}
	else
	{
		setMessage(object.getMessage());
	}

	return UniPAX::SBase::merge(object);

}

bool UniPAX::Constraint::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getMath()))
	{
		setMath(boost::dynamic_pointer_cast<UniPAX::Math>(manager.getMergedObject(getMath())));
	}
	return UniPAX::SBase::update(manager);
}

const std::string UniPAX::Constraint::getMessage() const {
	return message;
}

std::string UniPAX::Constraint::getMessage() {
	return message;
}

void UniPAX::Constraint::setMessage(std::string _message) {
	message = _message;
}

/*
   const UniPAX::Pathway * UniPAX::Constraint::getPathway() const {
   return pathway;
   }

   UniPAX::Pathway * UniPAX::Constraint::getPathway()  {
   return pathway;
   }

   void UniPAX::Constraint::setPathway(UniPAX::Pathway * _pathway)  {
   pathway = _pathway;
   }
 */

const boost::shared_ptr<UniPAX::Math> UniPAX::Constraint::getMath() const {
	return math;
}

boost::shared_ptr<UniPAX::Math> UniPAX::Constraint::getMath()  {
	return math;
}

void UniPAX::Constraint::setMath(boost::shared_ptr<UniPAX::Math> _math)  {
	math = _math;
}


bool UniPAX::Constraint::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::SBase::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"id"))
	{
		setMessage(value);
		return true;
	}
	/*	if (boost::iequals(attribute,"pathway"))
			{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
		return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
		std::cerr << "Constraint::setAttribute - object not known (value = " << value << ")" << std::endl;
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

bool UniPAX::Constraint::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
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

				}*/
	tmp.clear();
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
	tmp.clear();
	if (!getMessage().empty())
		value.push_back(std::pair<std::string,std::string>("message", getMessage()));

	return false;
}



//void UniPAX::Constraint::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::SBase::init(e,db);
//
//	return;
//}

#include<UNIPAX/KERNEL/EXT/FunctionDefinition.h>
//Begin section for file FunctionDefinition.cpp
//TODO: Add definitions that you want preserved
//End section for file FunctionDefinition.cpp


UniPAX::FunctionDefinition::FunctionDefinition() : UniPAX::SBase()
												   //, math(0)
{
}

UniPAX::FunctionDefinition::FunctionDefinition(const FunctionDefinition& arg) : UniPAX::SBase(arg) ,
		id(arg.id),
		name(arg.name),
		//    pathway(arg.pathway),
		math(arg.math)
{
}

UniPAX::FunctionDefinition & UniPAX::FunctionDefinition::operator =(const FunctionDefinition & arg)  {
		UniPAX::SBase::operator=(arg);
		id = arg.id;
		name = arg.name;
		//    pathway = arg.pathway;
		math = arg.math;

		return *this;
}

UniPAX::FunctionDefinition::~FunctionDefinition()  {
}

bool UniPAX::FunctionDefinition::merge(FunctionDefinition& object)
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

		if (!id.empty())
		{
				if (id.compare(object.getId()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Constraint::id not equal ..."
								<< id << " != " << object.getId() << std::endl;
						return false;
				}
		}
		else
		{
				setId(object.getId());
		}

		if (!name.empty())
		{
				if (name.compare(object.getName()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Constraint::name not equal ..."
								<< name << " != " << object.getName() << std::endl;
						return false;
				}
		}
		else
		{
				setName(object.getName());
		}

		return UniPAX::SBase::merge(object);

}

bool UniPAX::FunctionDefinition::update(PersistenceManager& manager)
{
		// check single pointer if object was merged
		if (manager.isMerged(getMath()))
		{
				setMath(boost::dynamic_pointer_cast<UniPAX::Math>(manager.getMergedObject(getMath())));
		}
		return UniPAX::SBase::update(manager);
}

const std::string & UniPAX::FunctionDefinition::getId() const {
		return id;
}

std::string & UniPAX::FunctionDefinition::getId() {
		return id;
}

void UniPAX::FunctionDefinition::setId(std::string _id) {
		id = _id;
}


const std::string & UniPAX::FunctionDefinition::getName() const {
		return name;
}

std::string & UniPAX::FunctionDefinition::getName() {
		return name;
}

void UniPAX::FunctionDefinition::setName(std::string _name) {
		name = _name;
}

boost::shared_ptr<UniPAX::Math> UniPAX::FunctionDefinition::getMath()  {
		return math;
}

const boost::shared_ptr<UniPAX::Math> UniPAX::FunctionDefinition::getMath() const {
		return math;
}

void UniPAX::FunctionDefinition::setMath(boost::shared_ptr<UniPAX::Math> _math)  {
		math = _math;
}


		bool UniPAX::FunctionDefinition::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {
				if (UniPAX::SBase::setAttribute(attribute, value, manager))
						return true;

				/*if (boost::iequals(attribute,"pathway"))
				  {
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
				return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
				std::cerr << "FunctionDefinition::setAttribute - object not known (value = " << value << ")" << std::endl;
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
								std::cerr << "FunctionDefinition::setAttribute - object not known (value = " << value << ")" << std::endl;
								return false;
						}

						math = boost::dynamic_pointer_cast<UniPAX::Math>(object);
						return true;
				}
				if (boost::iequals(attribute,"id"))
				{
						setId(value);
						return true;
				}
				if (boost::iequals(attribute,"name"))
				{
						setName(value);
						return true;
				}

				return false;

		}

bool UniPAX::FunctionDefinition::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

		if (!UniPAX::SBase::getAttribute(value, manager))
				return false;

		if (!getId().empty())
				value.push_back(std::pair<std::string,std::string>("id", getId()));
		if (!getName().empty())
				value.push_back(std::pair<std::string,std::string>("name", getName()));

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

		return true;


}


//void UniPAX::FunctionDefinition::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		return;
//}

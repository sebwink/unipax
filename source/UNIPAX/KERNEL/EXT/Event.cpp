#include<UNIPAX/KERNEL/EXT/Event.h>
#include<set>
//Begin section for file Event.cpp
//TODO: Add definitions that you want preserved
//End section for file Event.cpp

UniPAX::Event::Event() : UniPAX::SBase()
, useValuesFromTriggerTime(false)
						 //	, priority(0)
						 //	, delay(0)
						 //	, trigger(0)
{
}

UniPAX::Event::Event(const Event& arg) : UniPAX::SBase(arg) ,
		useValuesFromTriggerTime(arg.useValuesFromTriggerTime),
		priority(arg.priority),
		delay(arg.delay),
		trigger(arg.trigger),
		id(arg.id),
		name(arg.name),
		eventAssignment(arg.eventAssignment)
{
}

UniPAX::Event & UniPAX::Event::operator =(const Event & arg)  {
		UniPAX::SBase::operator=(arg);
		useValuesFromTriggerTime = arg.useValuesFromTriggerTime;
		priority = arg.priority;
		delay = arg.delay;
		trigger = arg.trigger;
		id = arg.id;
		name = arg.name;
		eventAssignment = arg.eventAssignment;

		return *this;
}

UniPAX::Event::~Event()  {
}

bool UniPAX::Event::merge(Event& object)
{

		if (useValuesFromTriggerTime != object.getUseValuesFromTriggerTime())
		{
				std::cerr << "Error during merging: UniPAX::Event::useValuesFromTriggerTime not equal ..."
						<< useValuesFromTriggerTime << " != " << object.getUseValuesFromTriggerTime() <<std::endl;
		}

		if (!id.empty())
		{
				if (id.compare(object.getId()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Event::id not equal ..."
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
						std::cerr << "Error during merging: UniPAX::Event::name not equal ..."
								<< name << " != " << object.getName() << std::endl;
						return false;
				}
		}
		else
		{
				setName(object.getName());
		}

		if (priority != 0)
		{
				if (object.getPriority() != 0)
				{
						if (priority->getMetaId() != object.getPriority()->getMetaId())
						{
								std::cerr << "Error during merging: UniPAX::Event::priority not equal ..."
										<< priority->getMetaId() << " != " << object.getPriority()->getMetaId() << std::endl;
								return false;
						}
				}
		}
		else
		{
				setPriority(object.getPriority());
		}

		if (delay != 0)
		{
				if (object.getDelay() != 0)
				{
						if (delay->getMetaId() != object.getDelay()->getMetaId())
						{
								std::cerr << "Error during merging: UniPAX::Event::delay not equal ..."
										<< delay->getMetaId() << " != " << object.getDelay()->getMetaId() << std::endl;
								return false;
						}
				}
		}
		else
		{
				setDelay(object.getDelay());
		}

		if (trigger != 0)
		{
				if (object.getTrigger() != 0)
				{
						if (trigger->getMetaId() != object.getTrigger()->getMetaId())
						{
								std::cerr << "Error during merging: UniPAX::Event::trigger not equal ..."
										<< trigger->getMetaId() << " != " << object.getTrigger()->getMetaId() << std::endl;
								return false;
						}
				}
		}
		else
		{
				setTrigger(object.getTrigger());
		}
		// merge EventAssignments
		{
			std::set<UniPAX::EventAssignmentPtr> tmp(getEventAssignments().begin(), getEventAssignments().end());
			for (std::vector<UniPAX::EventAssignmentPtr>::iterator it = object.getEventAssignments().begin(); it != object.getEventAssignments().end(); it++)
			{
				if (*it != 0)
				{
					tmp.insert(*it);
				}
			}
			getEventAssignments().assign(tmp.begin(), tmp.end());
		}

		return UniPAX::SBase::merge(object);
}

bool UniPAX::Event::update(PersistenceManager& manager)
{
		// check single pointer if object was merged
		if (manager.isMerged(getPriority()))
		{
				setPriority(boost::dynamic_pointer_cast<UniPAX::Priority>(manager.getMergedObject(getPriority())));
		}
		if (manager.isMerged(getDelay()))
		{
				setDelay(boost::dynamic_pointer_cast<UniPAX::Delay>(manager.getMergedObject(getDelay())));
		}
		if (manager.isMerged(getTrigger()))
		{
				setTrigger(boost::dynamic_pointer_cast<UniPAX::Trigger>(manager.getMergedObject(getTrigger())));
		}
		{
				// run through vector to check each pointer
				std::vector<boost::shared_ptr<UniPAX::EventAssignment> > tmp_vec;
				std::vector<boost::shared_ptr<UniPAX::EventAssignment> >::iterator it;
				for (it = eventAssignment.begin(); it != eventAssignment.end(); it++)
				{
						if (manager.isMerged(*it))
								tmp_vec.push_back(boost::dynamic_pointer_cast<EventAssignment>(manager.getMergedObject(*it)));
						else
								tmp_vec.push_back(*it);
				}
				setEventAssignments(tmp_vec);
		}

		return UniPAX::SBase::update(manager);
}

bool UniPAX::Event::getUseValuesFromTriggerTime()  {
		return useValuesFromTriggerTime;
}

const bool UniPAX::Event::getUseValuesFromTriggerTime() const {
		return useValuesFromTriggerTime;
}

void UniPAX::Event::setUseValuesFromTriggerTime(bool _useValuesFromTriggerTime)  {
		useValuesFromTriggerTime = _useValuesFromTriggerTime;
}


const boost::shared_ptr<UniPAX::Priority> UniPAX::Event::getPriority() const {
		return priority;
}

boost::shared_ptr<UniPAX::Priority> UniPAX::Event::getPriority() {
		return priority;
}

void UniPAX::Event::setPriority(boost::shared_ptr<UniPAX::Priority> _priority) {
		priority = _priority;
}


const boost::shared_ptr<UniPAX::Delay> UniPAX::Event::getDelay() const {
		return delay;
}

boost::shared_ptr<UniPAX::Delay> UniPAX::Event::getDelay() {
		return delay;
}

void UniPAX::Event::setDelay(boost::shared_ptr<UniPAX::Delay> _delay) {
		delay = _delay;
}


const boost::shared_ptr<UniPAX::Trigger> UniPAX::Event::getTrigger() const {
		return trigger;
}

boost::shared_ptr<UniPAX::Trigger> UniPAX::Event::getTrigger() {
		return trigger;
}

void UniPAX::Event::setTrigger(boost::shared_ptr<UniPAX::Trigger> _trigger) {
		trigger = _trigger;
}


const std::string & UniPAX::Event::getId() const {
		return id;
}

std::string & UniPAX::Event::getId() {
		return id;
}

void UniPAX::Event::setId(std::string _id) {
		id = _id;
}


const std::string & UniPAX::Event::getName() const {
		return name;
}

std::string & UniPAX::Event::getName() {
		return name;
}

void UniPAX::Event::setName(std::string _name) {
		name = _name; 
}


const std::vector<boost::shared_ptr<UniPAX::EventAssignment> > & UniPAX::Event::getEventAssignments() const {
		return eventAssignment;
}

std::vector<boost::shared_ptr<UniPAX::EventAssignment> >& UniPAX::Event::getEventAssignments() {
		return eventAssignment;
}

void UniPAX::Event::setEventAssignments(std::vector<boost::shared_ptr<UniPAX::EventAssignment> > _eventAssignments) {
		eventAssignment = _eventAssignments;
}

void UniPAX::Event::addEventAssignment(boost::shared_ptr<UniPAX::EventAssignment>  _eventAssignment) {
		eventAssignment.push_back(_eventAssignment);
}


/*UniPAX::Pathway * UniPAX::Event::getPathway()  {
  return pathway;
  }

  const UniPAX::Pathway * UniPAX::Event::getPathway() const {
  return pathway;
  }

  void UniPAX::Event::setPathway(UniPAX::Pathway * _pathway)  {
  pathway = _pathway;
  }*/


		bool UniPAX::Event::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {
				if (!UniPAX::SBase::getAttribute(value, manager))
						return false;

				std::string tmp = "";
				if (!PersistenceManager::convertAttribute(useValuesFromTriggerTime, tmp)) {
						return false;
				}
				value.push_back(std::pair<std::string,std::string>("useValuesFromTriggerTime", tmp));

				if (!getId().empty())
						value.push_back(std::pair<std::string,std::string>("id", getId()));

				if (!getName().empty())
						value.push_back(std::pair<std::string,std::string>("name", getName()));

				/*if (pathway == 0)
				  {
				//		value.push_back(std::pair<std::string,std::string>("#evidence", "NIL"));
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
				if (priority == 0)
				{
						//		value.push_back(std::pair<std::string,std::string>("#dataSource", "NIL"));
				}
				else
				{
						tmp.clear();
						if (!manager.getId(priority,tmp))
						{
								manager.setError(this->type() + ":priority contains unknown reference.");
								return false;
						}
						value.push_back(std::pair<std::string,std::string>("#priority", tmp));

				}
				tmp.clear();
				if (delay == 0)
				{
						//		value.push_back(std::pair<std::string,std::string>("#delay", "NIL"));
				}
				else
				{
						tmp.clear();
						if (!manager.getId(delay,tmp))
						{
								manager.setError(this->type() + ":delay contains unknown reference.");
								return false;
						}
						value.push_back(std::pair<std::string,std::string>("#delay", tmp));

				}
				tmp.clear();
				if (trigger == 0)
				{
						//		value.push_back(std::pair<std::string,std::string>("#trigger", "NIL"));
				}
				else
				{
						tmp.clear();
						if (!manager.getId(trigger,tmp))
						{
								manager.setError(this->type() + ":trigger contains unknown reference.");
								return false;
						}
						value.push_back(std::pair<std::string,std::string>("#trigger", tmp));

				}
				{
						std::vector<boost::shared_ptr<UniPAX::EventAssignment> >::iterator it;
						for (it = eventAssignment.begin(); it != eventAssignment.end(); it++)
						{
								if (*it == 0)
								{
										//			value.push_back(std::pair<std::string,std::string>("#eventAssignment", "NIL"));
								}
								else
								{
										tmp.clear();
										if (!manager.getId(*it,tmp))
										{
												manager.setError(this->type() + ":eventAssignment contains unknown reference.");
												return false;
										}
										value.push_back(std::pair<std::string,std::string>("#eventAssignment", tmp));
								}
						}
				}

				return false;
		}

bool UniPAX::Event::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

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
		std::cerr << "Event::setAttribute - object not known (value = " << value << ")" << std::endl;
		return false;
		}

		pathway = boost::dynamic_pointer_cast<UniPAX::Pathway>(object);
		return true;
		}*/
		if (boost::iequals(attribute,"priority"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Event::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				priority = boost::dynamic_pointer_cast<UniPAX::Priority>(object);
				return true;
		}
		if (boost::iequals(attribute,"trigger"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Event::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				trigger = boost::dynamic_pointer_cast<UniPAX::Trigger>(object);
				return true;
		}
		if (boost::iequals(attribute,"delay"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Event::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				delay = boost::dynamic_pointer_cast<UniPAX::Delay>(object);
				return true;
		}
		if (boost::iequals(attribute,"eventAssignment"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Event::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				eventAssignment.push_back(boost::dynamic_pointer_cast<UniPAX::EventAssignment>(object));
				return true;
		}
		if (boost::iequals(attribute,"useValuesFromTriggerTime"))
		{
				return (PersistenceManager::convertAttribute(value,useValuesFromTriggerTime));
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


//void UniPAX::Event::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		return;
//}

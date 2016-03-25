#include<UNIPAX/KERNEL/BIOPAX/Control.h>
#include<set>
//Begin section for file Control.cpp
//TODO: Add definitions that you want preserved
//End section for file Control.cpp


UniPAX::Control::Control() : UniPAX::Interaction()
//controlled(0),
//id_controlled(0)
{
}

UniPAX::Control::Control(const Control& arg) : UniPAX::Interaction(arg) ,
		controlType(arg.controlType),
		controller(arg.controller),
		controlled(arg.controlled)
//		id_controller(arg.id_controller),
//		id_controlled(arg.id_controlled)
{
}

UniPAX::Control & UniPAX::Control::operator =(const Control & arg)  {
	UniPAX::Interaction::operator=(arg);
	controlType = arg.controlType;
	controller = arg.controller;
	controlled = arg.controlled;
//	id_controller = arg.id_controller;
//	id_controlled = arg.id_controlled;

	return *this;
}

UniPAX::Control::~Control()  {
}

bool UniPAX::Control::merge(Control& object)
{
	if (controlled != 0)
	{
		if (object.getControlled() != 0)
		{
			if (controlled->getUnipaxId() != object.getControlled()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::Control::controlled not equal ..."
						<< controlled->getUnipaxId() << " != " << object.getControlled()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		if (boost::dynamic_pointer_cast<Interaction>(object.getControlled()))
			setControlled(boost::dynamic_pointer_cast<Interaction>(object.getControlled()));
		else if (boost::dynamic_pointer_cast<Pathway>(object.getControlled()))
			setControlled(boost::dynamic_pointer_cast<Pathway>(object.getControlled()));
	}
	{
		std::set<UniPAX::EntityPtr> tmp(getControllers().begin(), getControllers().end());
		for (std::vector<UniPAX::EntityPtr>::iterator it = object.getControllers().begin(); it != object.getControllers().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getControllers().assign(tmp.begin(), tmp.end());
	}
	if (!object.getControlType().empty())
	{
		if (!getControlType().empty())
		{
			if (getControlType() != object.getControlType())
			{
				std::cerr << "Error during merging: UniPAX::Control::controlType not equal ..."
						<< getControlType() << " != " << object.getControlType() << std::endl;
				return false;
			}
		}
		else
			setControlType(object.getControlType());
	}

	return UniPAX::Interaction::merge(object);
}

bool UniPAX::Control::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getControlled()))
	{
		boost::shared_ptr<UPBase> merged_controlled = manager.getMergedObject(getControlled());
		if (boost::dynamic_pointer_cast<Interaction>(merged_controlled))
			setControlled(boost::dynamic_pointer_cast<Interaction>(merged_controlled));
		else if (boost::dynamic_pointer_cast<Pathway>(merged_controlled))
			setControlled(boost::dynamic_pointer_cast<Pathway>(merged_controlled));
	}
	{
		std::vector<boost::shared_ptr<UniPAX::Entity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
		for (it = controller.begin(); it != controller.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Entity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setControllers(tmp_vec);
	}

	return UniPAX::Interaction::update(manager);
}

const std::string & UniPAX::Control::getControlType() const {
	return controlType;
}

std::string & UniPAX::Control::getControlType() {
	return controlType;
}

void UniPAX::Control::setControlType(std::string _controlType) {
	controlType = _controlType;
}

std::vector<boost::shared_ptr<UniPAX::Entity> >& UniPAX::Control::getControllers()  {
	return controller;
}

const std::vector<boost::shared_ptr<UniPAX::Entity> >& UniPAX::Control::getControllers() const {
	return controller;
}

void UniPAX::Control::setControllers(std::vector<boost::shared_ptr<UniPAX::Entity> > _controllers)  {
	controller = _controllers;
}
void UniPAX::Control::addController(boost::shared_ptr<UniPAX::Entity>  _controller)  {
	controller.push_back(_controller);
}

boost::shared_ptr<UniPAX::Entity> UniPAX::Control::getControlled()  {
	return controlled;
}

const boost::shared_ptr<UniPAX::Entity> UniPAX::Control::getControlled() const {
	return controlled;
}

void UniPAX::Control::setControlled(boost::shared_ptr<UniPAX::Interaction> _controlled)  {
	controlled = _controlled;
}

void UniPAX::Control::setControlled(boost::shared_ptr<UniPAX::Pathway> _controlled)  {
	controlled = _controlled;
}


const std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::Control::getParticipants() const {
	std::vector<boost::shared_ptr<UniPAX::Entity> > _participants(super::getParticipants());
	_participants.push_back(controlled);
	_participants.insert(_participants.end(), controller.begin(), controller.end());
	return _participants;
}

std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::Control::getParticipants()
{
	std::vector<boost::shared_ptr<UniPAX::Entity> > _participants(super::getParticipants());
	_participants.push_back(controlled);
	_participants.insert(_participants.end(), controller.begin(), controller.end());
	return _participants;
}


bool UniPAX::Control::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Interaction::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"controlled"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Control::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		controlled = boost::dynamic_pointer_cast<UniPAX::Entity>(object);
		return true;
	}
	if (boost::iequals(attribute,"controller"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Control::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		controller.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(object));
		return true;
	}
	if (boost::iequals(attribute,"controlType"))
	{
		setControlType(value);
		return true;
	}

	return false;

}


bool UniPAX::Control::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Interaction::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (controlled == 0)
	{
		//		value.push_back(std::pair<std::string,std::string>("#controlled", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(controlled,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#controlled", tmp));

	}
	tmp.clear();
	std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
	for (it = controller.begin(); it != controller.end(); it++)
	{
		if (*it == 0)
		{
			//			value.push_back(std::pair<std::string,std::string>("#controller", "NIL"));
		}
		else
		{
			tmp.clear();
			if (!manager.getId(*it,tmp))
			{
				return false;
			}
			value.push_back(std::pair<std::string,std::string>("#controller", tmp));

		}
	}

	if (!getControlType().empty())
		value.push_back(std::pair<std::string,std::string>("controlType", getControlType()));

	return true;

}


//void UniPAX::Control::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Interaction::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		controlled = boost::dynamic_pointer_cast<UniPAX::Entity>(getObjectByID(db, id_controlled));
//
//		// load the object pointer
//		controller.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_controller.begin(); it != id_controller.end(); it++)
//		{
//			controller.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(getObjectByID(db, *it)));
//		}
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		if (controlled != 0)
//			id_controlled = controlled->getUnipaxId();
//
//		// set the object ids
//		id_controller.clear();
//		std::vector<boost::shared_ptr<Entity> >::iterator it;
//		for (it = controller.begin(); it != controller.end(); it++)
//		{
//			if (*it != 0)
//				id_controller.push_back((*it)->getUnipaxId());
//		}
//
//	}
//
//	return;
//}

#include<UNIPAX/KERNEL/BIOPAX/Catalysis.h>
#include<set>
//Begin section for file Catalysis.cpp
//TODO: Add definitions that you want preserved
//End section for file Catalysis.cpp

UniPAX::Catalysis::Catalysis() : UniPAX::Control() {
    }

UniPAX::Catalysis::Catalysis(const Catalysis & arg) : UniPAX::Control(arg),
	catalysisDirection(arg.catalysisDirection),
	cofactor(arg.cofactor)
//	id_cofactor(arg.id_cofactor)
{
    }

UniPAX::Catalysis & UniPAX::Catalysis::operator =(const Catalysis & arg)  {
	UniPAX::Control::operator=(arg);
	catalysisDirection = arg.catalysisDirection;
	cofactor = arg.cofactor;
//	id_cofactor = arg.id_cofactor;

	return *this;
}

UniPAX::Catalysis::~Catalysis()  {
    }



bool UniPAX::Catalysis::merge(Catalysis& object)
{
	{
		std::set<UniPAX::PhysicalEntityPtr> tmp(getCofactors().begin(), getCofactors().end());
		for (std::vector<UniPAX::PhysicalEntityPtr>::iterator it = object.getCofactors().begin(); it != object.getCofactors().end(); it++)
		{
			if (*it == 0)
			{
				tmp.insert(*it);
			}
		}
		getCofactors().assign(tmp.begin(), tmp.end());
	}
	if (!object.getCatalysisDirection().empty())
	{
		if (!getCatalysisDirection().empty())
		{
			if (getCatalysisDirection() != object.getCatalysisDirection())
			{
				std::cerr << "Error during merging: UniPAX::Catalysis::catalysisDirection not equal ..."
						<< getCatalysisDirection() << " != " << object.getCatalysisDirection() << std::endl;
				return false;
			}
		}
		else
			setCatalysisDirection(object.getCatalysisDirection());
	}

	return UniPAX::Control::merge(object);
}

bool UniPAX::Catalysis::update(PersistenceManager& manager)
{
	return UniPAX::Control::update(manager);
}

const std::string & UniPAX::Catalysis::getCatalysisDirection() const {
        return catalysisDirection;
}

std::string & UniPAX::Catalysis::getCatalysisDirection() {
	return catalysisDirection;
}

void UniPAX::Catalysis::setCatalysisDirection(std::string _catalysisDirection) {
	catalysisDirection = _catalysisDirection;
}

const std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::Catalysis::getCofactors() const {
    return cofactor;
}

std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > & UniPAX::Catalysis::getCofactors() {
	return cofactor;
}

void UniPAX::Catalysis::addCofactor(boost::shared_ptr<UniPAX::PhysicalEntity>  _cofactor) {
	cofactor.push_back(_cofactor);
}

void UniPAX::Catalysis::setCofactors(std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > _cofactors) {
	cofactor = _cofactors;
}


const std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::Catalysis::getParticipants() const {
	std::vector<boost::shared_ptr<UniPAX::Entity> > _participants(super::getParticipants());
	_participants.insert(_participants.end(), cofactor.begin(), cofactor.end());
	return _participants;
}

std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::Catalysis::getParticipants()
{
	std::vector<boost::shared_ptr<UniPAX::Entity> > _participants(super::getParticipants());
	_participants.insert(_participants.end(), cofactor.begin(), cofactor.end());
	return _participants;
}

bool UniPAX::Catalysis::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Control::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"cofactor"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Catalysis::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		cofactor.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(object));
		return true;
	}
	if (boost::iequals(attribute,"catalysisDirection"))
	{
		setCatalysisDirection(value);
		return true;
	}
	return false;

}


bool UniPAX::Catalysis::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Control::getAttribute(value, manager))
		return false;

	std::string tmp = "";

	std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::iterator it;
	for (it = cofactor.begin(); it != cofactor.end(); it++)
	{
		if (*it == 0)
		{
//			value.push_back(std::pair<std::string,std::string>("#cofactor", "NIL"));
		}
		else
		{
			tmp.clear();
			if (!manager.getId(*it,tmp))
			{
				return false;
			}
			value.push_back(std::pair<std::string,std::string>("#cofactor", tmp));

		}
	}

	if (!getCatalysisDirection().empty())
		value.push_back(std::pair<std::string,std::string>("catalysisDirection", getCatalysisDirection()));

	return true;

}


//void UniPAX::Catalysis::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Control::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		cofactor.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_cofactor.begin(); it != id_cofactor.end(); it++)
//		{
//			cofactor.push_back(boost::dynamic_pointer_cast<UniPAX::PhysicalEntity>(getObjectByID(db, *it)));
//		}
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		id_cofactor.clear();
//		std::vector<boost::shared_ptr<PhysicalEntity> >::iterator it;
//		for (it = cofactor.begin(); it != cofactor.end(); it++)
//		{
//			if (*it != 0)
//				id_cofactor.push_back((*it)->getUnipaxId());
//		}
//
//	}
//
//	return;
//}

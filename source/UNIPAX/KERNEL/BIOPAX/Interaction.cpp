#include<UNIPAX/KERNEL/BIOPAX/Interaction.h>
#include<set>
//Begin section for file Interaction.cpp
//TODO: Add definitions that you want preserved
//End section for file Interaction.cpp

UniPAX::Interaction::Interaction() :UniPAX::Entity()  {
    }

UniPAX::Interaction::Interaction(const Interaction& arg) : UniPAX::Entity(arg) ,
	participant(arg.participant),
	interactionType(arg.interactionType)
//	id_participant(arg.id_participant)
{
    }

UniPAX::Interaction & UniPAX::Interaction::operator =(const Interaction & arg)  {
	UniPAX::Entity::operator=(arg);
	participant = arg.participant;
	interactionType = arg.interactionType;
//	id_participant = arg.id_participant;

	return *this;
}

UniPAX::Interaction::~Interaction()  {
    }

bool UniPAX::Interaction::merge(Interaction& object)
{

	{
		std::set<UniPAX::EntityPtr> tmp(getParticipants().begin(), getParticipants().end());
		for (std::vector<UniPAX::EntityPtr>::iterator it = object.getParticipants().begin(); it != object.getParticipants().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getParticipants().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::InteractionVocabularyPtr> tmp(getInteractionTypes().begin(), getInteractionTypes().end());
		for (std::vector<UniPAX::InteractionVocabularyPtr>::iterator it = object.getInteractionTypes().begin(); it != object.getInteractionTypes().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getInteractionTypes().assign(tmp.begin(), tmp.end());
	}
	return UniPAX::Entity::merge(object);
}

bool UniPAX::Interaction::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::Entity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
		for (it = participant.begin(); it != participant.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Entity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setParticipants(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::InteractionVocabulary> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::InteractionVocabulary> >::iterator it;
		for (it = interactionType.begin(); it != interactionType.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<InteractionVocabulary>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setInteractionTypes(tmp_vec);
	}

	return UniPAX::Entity::update(manager);
}


const std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::Interaction::getParticipants() const {
    return participant;
}

std::vector<boost::shared_ptr<UniPAX::Entity> > UniPAX::Interaction::getParticipants() {
	return participant;
}

void UniPAX::Interaction::setParticipants(std::vector<boost::shared_ptr<UniPAX::Entity> > _participants) {
 	participant = _participants;
}

void UniPAX::Interaction::addParticipant(boost::shared_ptr<UniPAX::Entity>  _entity) {
	participant.push_back(_entity);
}

const std::vector<boost::shared_ptr<UniPAX::InteractionVocabulary> > & UniPAX::Interaction::getInteractionTypes() const {
        return interactionType;
}

std::vector<boost::shared_ptr<UniPAX::InteractionVocabulary> > & UniPAX::Interaction::getInteractionTypes() {
	return interactionType;
}

void UniPAX::Interaction::setInteractionTypes(std::vector<boost::shared_ptr<UniPAX::InteractionVocabulary> > _interactionTypes) {
	interactionType = _interactionTypes;
}

void UniPAX::Interaction::addInteractionType(boost::shared_ptr<UniPAX::InteractionVocabulary>  _voc) {
	interactionType.push_back(_voc);
}

bool UniPAX::Interaction::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Entity::setAttribute(attribute, value, manager))
		return true;


	if (boost::iequals(attribute,"participant"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Interaction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		participant.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(object));
		return true;
	}
	if (boost::iequals(attribute,"interactionType"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Interaction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		interactionType.push_back(boost::dynamic_pointer_cast<UniPAX::InteractionVocabulary>(object));
		return true;
	}
	return false;

}

bool UniPAX::Interaction::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Entity::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;

		for (it = participant.begin(); it != participant.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#participant", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#participant", tmp));

			}
		}
	}
	std::vector<boost::shared_ptr<UniPAX::InteractionVocabulary> >::iterator it;
	for (it = interactionType.begin(); it != interactionType.end(); it++)
	{
		if (*it == 0)
		{
//			value.push_back(std::pair<std::string,std::string>("#interactionType", "NIL"));
		}
		else
		{
			tmp.clear();
			if (!manager.getId(*it,tmp))
			{
				return false;
			}
			value.push_back(std::pair<std::string,std::string>("#interactionType", tmp));

		}
	}

	return true;

}

//void UniPAX::Interaction::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Entity::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		participant.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_participant.begin(); it != id_participant.end(); it++)
//		{
//			participant.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(getObjectByID(db, *it)));
//		}
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		id_participant.clear();
//		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
//		for (it = participant.begin(); it != participant.end(); it++)
//		{
//			if (*it != 0)
//				id_participant.push_back((*it)->getUnipaxId());
//		}
//
//	}
//
//	return;
//}

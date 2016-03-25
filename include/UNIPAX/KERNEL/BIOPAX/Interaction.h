#ifndef INTERACTION_H
#define INTERACTION_H
//Begin section for file Interaction.h
//TODO: Add definitions that you want preserved
//End section for file Interaction.h
#include<UNIPAX/KERNEL/BIOPAX/Entity.h>
#include<UNIPAX/KERNEL/BIOPAX/InteractionVocabulary.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Interaction : public Entity {

protected:

	// std::vector<unsigned long long> id_participant;
//#pragma db transient
	std::vector<UnipaxPtr<Entity>::type > participant;

	std::vector<UnipaxPtr<InteractionVocabulary>::type > interactionType;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Interaction";
	}

	static std::string type() {
		return std::string("Interaction");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idInteraction;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idInteraction;
        }

        Interaction();

	Interaction(const Interaction & arg);

	Interaction & operator =(const Interaction & arg);

	~Interaction();

	bool merge(Interaction& object);
	bool update(PersistenceManager& manager);


	//get participant
	virtual const std::vector<UnipaxPtr<Entity>::type > getParticipants() const;

	virtual std::vector<UnipaxPtr<Entity>::type > getParticipants();

	void setParticipants(std::vector<UnipaxPtr<Entity>::type > _participants);

	void addParticipant(UnipaxPtr<Entity>::type  _entity);

	//get interactionType
	const std::vector<UnipaxPtr<InteractionVocabulary>::type > & getInteractionTypes() const;

	std::vector<UnipaxPtr<InteractionVocabulary>::type > & getInteractionTypes();

	void setInteractionTypes(std::vector<UnipaxPtr<InteractionVocabulary>::type > _interactionTypes);

	void addInteractionType(UnipaxPtr<InteractionVocabulary>::type  _voc);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Entity super;

};  //end class Interaction

typedef UnipaxPtr<Interaction>::type InteractionPtr;

}//end namespace UniPAX

#endif

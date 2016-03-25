#ifndef CONVERSION_H
#define CONVERSION_H
//Begin section for file Conversion.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Conversion.h
#include<UNIPAX/KERNEL/BIOPAX/Interaction.h>
#include<UNIPAX/KERNEL/BIOPAX/Stoichiometry.h>
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/KERNEL/EXT/KineticLaw.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

class KineticLaw;

#pragma db object
class UNIPAX_EXPORT Conversion : public Interaction {

	//Begin section for UniPAX::Conversion
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::Conversion

protected:

	std::string conversionDirection;

	bool spontaneous;

	UnipaxPtr<KineticLaw>::type kineticLaw;

	std::vector<UnipaxPtr<Stoichiometry>::type > participantStoichiometry;

	// std::vector<unsigned long long> id_leftEntity;
//#pragma db transient
	std::vector<UnipaxPtr<PhysicalEntity>::type > leftEntity;

	// std::vector<unsigned long long> id_rightEntity;
//#pragma db transient
	std::vector<UnipaxPtr<PhysicalEntity>::type > rightEntity;



friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Conversion";
	}

	static std::string type() {
		return std::string("Conversion");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idConversion;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idConversion;
        }

        Conversion();

	Conversion(const Conversion & arg);

	Conversion & operator =(const Conversion & arg);

	~Conversion();

	bool merge(Conversion& object);
	bool update(PersistenceManager& manager);


	//get conversionDirection
	const std::string & getConversionDirection() const;

	std::string & getConversionDirection();

	void setConversionDirection(std::string _conversionDirection);

	//get spontaneous
	const bool & getSpontaneous() const;

	bool & getSpontaneous();

	void setSpontaneous(bool _spontaneous);


	const std::vector<UnipaxPtr<Stoichiometry>::type > & getParticipantStoichiometries() const;

	std::vector<UnipaxPtr<Stoichiometry>::type > & getParticipantStoichiometries();

	void addParticipantStoichiometry(UnipaxPtr<Stoichiometry>::type  _participantStoichiometry);

	void setParticipantStoichiometries(std::vector<UnipaxPtr<Stoichiometry>::type > _participantStoichiometries);



	const std::vector<UnipaxPtr<PhysicalEntity>::type > & getLefts() const;

	std::vector<UnipaxPtr<PhysicalEntity>::type > & getLefts();

	void addLeft(UnipaxPtr<PhysicalEntity>::type  _left);

	void setLefts(std::vector<UnipaxPtr<PhysicalEntity>::type > _left);



	const std::vector<UnipaxPtr<PhysicalEntity>::type > & getRights() const;

	std::vector<UnipaxPtr<PhysicalEntity>::type > & getRights();

	void addRight(UnipaxPtr<PhysicalEntity>::type  _right);

	void setRights(std::vector<UnipaxPtr<PhysicalEntity>::type > _right);



	const UnipaxPtr<KineticLaw>::type getKineticLaw() const;

	//get kineticLaw
	UnipaxPtr<KineticLaw>::type getKineticLaw();

	//set kineticLaw
	void setKineticLaw(UnipaxPtr<KineticLaw>::type _kineticLaw);

	virtual const std::vector<UnipaxPtr<Entity>::type > getParticipants() const;

	virtual std::vector<UnipaxPtr<Entity>::type > getParticipants();

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Interaction super;
};  //end class Conversion

typedef UnipaxPtr<Conversion>::type ConversionPtr;

}//end namespace UniPAX

#endif

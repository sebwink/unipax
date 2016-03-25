#ifndef CATALYSIS_H
#define CATALYSIS_H
//Begin section for file Catalysis.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Catalysis.h
#include<UNIPAX/KERNEL/BIOPAX/Control.h>
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Catalysis : public Control {

	//Begin section for UniPAX::Catalysis
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::Catalysis

protected:

	std::string catalysisDirection;
	// std::vector<unsigned long long> id_cofactor;
//#pragma db transient
	std::vector<UnipaxPtr<PhysicalEntity>::type > cofactor;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Catalysis";
	}

	static std::string type() {
		return std::string("Catalysis");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idCatalysis;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idCatalysis;
        }

        Catalysis();

	Catalysis(const Catalysis & arg);

	Catalysis & operator =(const Catalysis & arg);

	~Catalysis();

	bool merge(Catalysis& object);
	bool update(PersistenceManager& manager);


	//get catalysisDirection
	const std::string & getCatalysisDirection() const;

	std::string & getCatalysisDirection();

	void setCatalysisDirection(std::string _catalysisDirection);


	//get cofactor
	const std::vector<UnipaxPtr<PhysicalEntity>::type > & getCofactors() const;

	std::vector<UnipaxPtr<PhysicalEntity>::type > & getCofactors();

	void addCofactor(UnipaxPtr<PhysicalEntity>::type  _cofactor);

	void setCofactors(std::vector<UnipaxPtr<PhysicalEntity>::type > _cofactors);

	virtual const std::vector<UnipaxPtr<Entity>::type > getParticipants() const;
	virtual std::vector<UnipaxPtr<Entity>::type > getParticipants();

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Control super;
};  //end class Catalysis

typedef UnipaxPtr<Catalysis>::type CatalysisPtr;

}//end namespace UniPAX

#endif

#ifndef BIOCHEMICALREACTION_H
#define BIOCHEMICALREACTION_H
//Begin section for file BiochemicalReaction.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file BiochemicalReaction.h
#include<UNIPAX/KERNEL/BIOPAX/Conversion.h>
#include<UNIPAX/KERNEL/BIOPAX/DeltaG.h>
#include<UNIPAX/KERNEL/BIOPAX/KPrime.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT BiochemicalReaction : public Conversion {

	//Begin section for UniPAX::BiochemicalReaction
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::BiochemicalReaction

protected:

	double deltaH;

	double deltaS;

	std::string eCNumber;

	std::vector<UnipaxPtr<DeltaG>::type > deltaG;

	std::vector<UnipaxPtr<KPrime>::type > kEQ;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "BiochemicalReaction";
	}

	static std::string type() {
		return std::string("BiochemicalReaction");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idBiochemicalReaction;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idBiochemicalReaction;
        }

        BiochemicalReaction();

	BiochemicalReaction(const BiochemicalReaction & arg);

	BiochemicalReaction & operator =(const BiochemicalReaction & arg);

	~BiochemicalReaction();

	bool merge(BiochemicalReaction& object);
	bool update(PersistenceManager& manager);


	//get deltaH
	const double getDeltaH() const;

	double getDeltaH();

	//set deltaH
	void setDeltaH(double _deltaH);

	const double getDeltaS()	const;

	//get deltaS
	double getDeltaS();

	//set deltaS
	void setDeltaS(double _deltaS);

	//get eCNumber
	const std::string & getECNumber() const;

	std::string & getECNumber();

	void setECNumber(std::string _eCNumber);

	//get deltaG
	const std::vector<UnipaxPtr<DeltaG>::type > & getDeltaGs() const;

	std::vector<UnipaxPtr<DeltaG>::type > & getDeltaGs();

	void setDeltaGs(std::vector<UnipaxPtr<DeltaG>::type > _deltaGs);

	void addDeltaG(UnipaxPtr<DeltaG>::type  _deltaG);

	//get kEQ
	const std::vector<UnipaxPtr<KPrime>::type > & getKEQs() const;

	std::vector<UnipaxPtr<KPrime>::type > & getKEQs();

	void setKEQs(std::vector<UnipaxPtr<KPrime>::type > _kEQs);

	void addKEQ(UnipaxPtr<KPrime>::type  _kEQ);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Conversion super;

};  //end class BiochemicalReaction

typedef UnipaxPtr<BiochemicalReaction>::type BiochemicalReactionPtr;

}//end namespace UniPAX

#endif

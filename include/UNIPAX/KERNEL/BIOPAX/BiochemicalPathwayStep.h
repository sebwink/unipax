#ifndef BIOCHEMICALPATHWAYSTEP_H
#define BIOCHEMICALPATHWAYSTEP_H
//Begin section for file BiochemicalPathwayStep.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file BiochemicalPathwayStep.h
#include<UNIPAX/KERNEL/BIOPAX/PathwayStep.h>
#include<UNIPAX/KERNEL/BIOPAX/Conversion.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<odb/callback.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT BiochemicalPathwayStep : public PathwayStep {

        //Begin section for UniPAX::BiochemicalPathwayStep
        //TODO: Add attributes that you want preserved
        //End section for UniPAX::BiochemicalPathwayStep

protected:

	std::string stepDirection;

	//unsigned long long id_stepConversion;

//#pragma db transient
	UnipaxPtr<Conversion>::type stepConversion;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "BiochemicalPathwayStep";
	}

	static std::string type() {
		return std::string("BiochemicalPathwayStep");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idBiochemicalPathwayStep;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idBiochemicalPathwayStep;
        }

        BiochemicalPathwayStep();

	BiochemicalPathwayStep(const BiochemicalPathwayStep & arg);

	BiochemicalPathwayStep & operator =(const BiochemicalPathwayStep & arg);

	~BiochemicalPathwayStep();

	bool merge(BiochemicalPathwayStep& object);
	bool update(PersistenceManager& manager);


	//get stepDirection
	const std::string & getStepDirection() const;

	std::string & getStepDirection();

	void setStepDirection(std::string _stepDirection);

	//get stepConversion
	const UnipaxPtr<Conversion>::type getStepConversion() const;

	UnipaxPtr<Conversion>::type getStepConversion();

	void setStepConversion(UnipaxPtr<Conversion>::type _stepConversion);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef PathwayStep super;

};  //end class BiochemicalPathwayStep

typedef UnipaxPtr<BiochemicalPathwayStep>::type BiochemicalPathwayStepPtr;

}//end namespace UniPAX

#endif

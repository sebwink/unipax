#ifndef PATHWAYSTEP_H
#define PATHWAYSTEP_H
//Begin section for file PathwayStep.h
//TODO: Add definitions that you want preserved
//End section for file PathwayStep.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/Evidence.h>
#include<UNIPAX/KERNEL/BIOPAX/Entity.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT PathwayStep : public UtilityClass {

protected:


	// std::vector<unsigned long long> id_stepProcess;
//#pragma db transient
	std::vector<UnipaxPtr<Entity>::type > stepProcess;

	std::vector<UnipaxPtr<Evidence>::type > evidence;

	// std::vector<unsigned long long> id_nextStep;
//#pragma db transient
	std::vector<UnipaxPtr<PathwayStep>::type > nextStep;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "PathwayStep";
	}

	static std::string type() {
		return std::string("PathwayStep");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idPathwayStep;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idPathwayStep;
        }

        PathwayStep();

	PathwayStep(const PathwayStep & arg);

	PathwayStep & operator =(const PathwayStep & arg);

	~PathwayStep();

	bool merge(PathwayStep& object);
	bool update(PersistenceManager& manager);


	//get evidence
	const std::vector<UnipaxPtr<Evidence>::type > & getEvidences() const;

	std::vector<UnipaxPtr<Evidence>::type > & getEvidences();

	void setEvidences(std::vector<UnipaxPtr<Evidence>::type > _evidences);

	void addEvidence(UnipaxPtr<Evidence>::type  _evidence);


	//get nextStep
	const std::vector<UnipaxPtr<PathwayStep>::type > & getNextSteps() const;

	std::vector<UnipaxPtr<PathwayStep>::type > & getNextSteps();

	void setNextSteps(std::vector<UnipaxPtr<PathwayStep>::type > _nextSteps);

	void addNextStep(UnipaxPtr<PathwayStep>::type  _nextStep);


	const std::vector<UnipaxPtr<Entity>::type > & getStepProcesses() const;

	//get processStep
	std::vector<UnipaxPtr<Entity>::type > & getStepProcesses();

	//set processStep
	void setStepProcesses(std::vector<UnipaxPtr<Entity>::type > _stepProcesss);

	void addStepProcess(UnipaxPtr<Entity>::type  _stepProcess);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef UtilityClass super;

};  //end class PathwayStep

typedef UnipaxPtr<PathwayStep>::type PathwayStepPtr;

}//end namespace UniPAX

#endif

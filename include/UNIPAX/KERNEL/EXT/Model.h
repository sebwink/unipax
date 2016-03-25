#ifndef UNIPAX_MODEL_H
#define UNIPAX_MODEL_H

#include<vector>
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/EXT/FunctionDefinition.h>
#include<UNIPAX/KERNEL/EXT/UnitDefinition.h>
#include<UNIPAX/KERNEL/EXT/Parameter.h>
#include<UNIPAX/KERNEL/EXT/InitialAssignment.h>
#include<UNIPAX/KERNEL/EXT/Rule.h>
#include<UNIPAX/KERNEL/EXT/Constraint.h>
#include<UNIPAX/KERNEL/EXT/Event.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

class Rule;
class Constraint;
class FunctionDefinition;
class InitialAssignment;
class Parameter;
class UnitDefinition;
class SBase;

#pragma db object polymorphic
class UNIPAX_EXPORT Model : public SBase {

protected:

	//#pragma db inverse(model)
	// std::vector<unsigned long long> id_functionDefinition;
	//#pragma db transient
	std::vector<UnipaxPtr<FunctionDefinition>::type > functionDefinition;

	//#pragma db inverse(model)
	// std::vector<unsigned long long> id_unitDefinition;
	//#pragma db transient
	std::vector<UnipaxPtr<UnitDefinition>::type > unitDefinition;

	//#pragma db inverse(model)
	// std::vector<unsigned long long> id_parameter;
	//#pragma db transient
	std::vector<UnipaxPtr<Parameter>::type > parameter;

	//#pragma db inverse(model)
	// std::vector<unsigned long long> id_initialAssignment;
	//#pragma db transient
	std::vector<UnipaxPtr<InitialAssignment>::type > initialAssignment;

	//#pragma db inverse(model)
	// std::vector<unsigned long long> id_rule;
	//#pragma db transient
	std::vector<UnipaxPtr<Rule>::type > rule;

	//#pragma db inverse(model)
	// std::vector<unsigned long long> id_constraint;
	//#pragma db transient
	std::vector<UnipaxPtr<Constraint>::type > constraint;
	//#pragma db inverse(model)
	// std::vector<unsigned long long> id_event;
	//#pragma db transient
	std::vector<UnipaxPtr<Event>::type > event;

	std::string id;

	std::string name;

	std::string substanceUnits;

	std::string timeUnits;

	std::string volumeUnits;

	std::string areaUnits;

	std::string lengthUnits;

	std::string extentUnit;

	std::string conversionFactor;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Model";
	}

	static std::string type() {
		return std::string("Model");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idModel;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idModel;
	}

	Model();

	Model(const Model & arg);

	Model & operator =(const Model & arg);

	~Model();

	bool merge(Model& object);

	bool update(PersistenceManager& manager);

	// id
	std::string getId();

	const std::string getId() const;

	void setId(std::string _id);

	// name
	std::string getName();

	const std::string getName() const;

	void setName(std::string _name);

	// substanceUnits
	std::string getSubstanceUnits();

	const std::string getSubstanceUnits() const;

	void setSubstanceUnits(std::string _substanceUnits);

	// timeUnits
	std::string getTimeUnits();

	const std::string getTimeUnits() const;

	void setTimeUnits(std::string _timeUnits);

	// volumeUnits
	std::string getVolumeUnits();

	const std::string getVolumeUnits() const;

	void setVolumeUnits(std::string _volumeUnits);

	// areaUnits
	std::string getAreaUnits();

	const std::string getAreaUnits() const;

	void setAreaUnits(std::string _areaUnits);

	// lengthUnits
	std::string getLengthUnits();

	const std::string getLengthUnits() const;

	void setLengthUnits(std::string _lengthUnits);

	// extentUnit
	std::string getExtentUnit();

	const std::string getExtentUnit() const;

	void setExtentUnit(std::string _extentUnit);

	// conversionFactor
	std::string getConversionFactor();

	const std::string getConversionFactor() const;

	void setConversionFactor(std::string _conversionFactor);


	// functionDefinition
	std::vector<UnipaxPtr<FunctionDefinition>::type > & getFunctionDefinitions();

	const std::vector<UnipaxPtr<FunctionDefinition>::type > & getFunctionDefinitions() const;

	void setFunctionDefinitions(std::vector<UnipaxPtr<FunctionDefinition>::type > _functionDefinitions);

	void addFunctionDefinition(UnipaxPtr<FunctionDefinition>::type  _functionDefinition);


	// unitDefinition
	std::vector<UnipaxPtr<UnitDefinition>::type > & getUnitDefinitions();

	const std::vector<UnipaxPtr<UnitDefinition>::type > & getUnitDefinitions() const;

	void setUnitDefinitions(std::vector<UnipaxPtr<UnitDefinition>::type > _unitDefinitions);

	void addUnitDefinition(UnipaxPtr<UnitDefinition>::type  _unitDefinition);


	// parameter
	std::vector<UnipaxPtr<Parameter>::type > & getParameters();

	const std::vector<UnipaxPtr<Parameter>::type > & getParameters() const;

	void setParameters(std::vector<UnipaxPtr<Parameter>::type > _parameters);

	void addParameter(UnipaxPtr<Parameter>::type  _parameter);


	// initialAssignment
	std::vector<UnipaxPtr<InitialAssignment>::type > & getInitialAssignments();

	const std::vector<UnipaxPtr<InitialAssignment>::type > & getInitialAssignments() const;

	void setInitialAssignments(std::vector<UnipaxPtr<InitialAssignment>::type >_initialAssignments);

	void addInitialAssignment(UnipaxPtr<InitialAssignment>::type  _initialAssignment);


	// rule
	std::vector<UnipaxPtr<Rule>::type > & getRules();

	const std::vector<UnipaxPtr<Rule>::type > & getRules() const;

	void setRules(std::vector<UnipaxPtr<Rule>::type > _rules);

	void addRule(UnipaxPtr<Rule>::type  _rule);


	// constraint
	std::vector<UnipaxPtr<Constraint>::type > & getConstraints();

	const std::vector<UnipaxPtr<Constraint>::type > & getConstraints() const;

	void setConstraints(std::vector<UnipaxPtr<Constraint>::type > _constraints);

	void addConstraint(UnipaxPtr<Constraint>::type  _constraint);
	// event
	std::vector<UnipaxPtr<Event>::type > & getEvents();

	const std::vector<UnipaxPtr<Event>::type > & getEvents() const;

	void setEvents(std::vector<UnipaxPtr<Event>::type > _events);

	void addEvent(UnipaxPtr<Event>::type  _event);




	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Model

typedef UnipaxPtr<Model>::type ModelPtr;

}
#endif

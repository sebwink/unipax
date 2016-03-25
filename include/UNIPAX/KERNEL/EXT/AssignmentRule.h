#ifndef ASSIGNMENTRULE_H
#define ASSIGNMENTRULE_H
//Begin section for file AssignmentRule.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file AssignmentRule.h
#include<UNIPAX/KERNEL/EXT/Rule.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT AssignmentRule : public Rule {

protected:

	std::string variable;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "AssignmentRule";
	}

	static std::string type() {
		return std::string("AssignmentRule");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idAssignmentRule;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idAssignmentRule;
	}

	AssignmentRule();

	AssignmentRule(const AssignmentRule & arg);

	AssignmentRule & operator =(const AssignmentRule & arg);

	~AssignmentRule();

	bool merge(AssignmentRule& object);

	bool update(PersistenceManager& manager);

	//get variable
	const std::string & getVariable() const;

	std::string & getVariable();

	void setVariable(std::string _variable);

	//set attribute
	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class AssignmentRule

typedef UnipaxPtr<AssignmentRule>::type AssignmentRulePtr;

}//end namespace UniPAX

#endif

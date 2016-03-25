#ifndef UNIPAX_RULE_H
#define UNIPAX_RULE_H
//Begin section for file Rule.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Rule.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<UNIPAX/KERNEL/EXT/Math.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Rule : public SBase {

protected:


	UnipaxPtr<Math>::type math;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Rule";
	}

	static std::string type() {
		return std::string("Rule");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idRule;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idRule;
	}

	Rule();

	Rule(const Rule & arg);

	Rule & operator =(const Rule & arg);

	~Rule();

	bool merge(Rule& object);

	bool update(PersistenceManager& manager);

	// math
	const UnipaxPtr<Math>::type getMath() const;

	UnipaxPtr<Math>::type getMath();

	void setMath(UnipaxPtr<Math>::type math);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Rule

typedef UnipaxPtr<Rule>::type RulePtr;

}//end namespace UniPAX

#endif

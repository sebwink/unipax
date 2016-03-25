#ifndef ALGEBRAICRULE_H
#define ALGEBRAICRULE_H
//Begin section for file AlgebraicRule.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file AlgebraicRule.h
#include<UNIPAX/KERNEL/EXT/Rule.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT AlgebraicRule : public Rule {

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "AlgebraicRule";
	}

	static std::string type() {
		return std::string("AlgebraicRule");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idAlgebraicRule;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idAlgebraicRule;
	}

	AlgebraicRule();

	AlgebraicRule(const AlgebraicRule & arg);

	AlgebraicRule & operator =(const AlgebraicRule & arg);

	~AlgebraicRule();

	bool merge(AlgebraicRule& object);

	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class AlgebraicRule

typedef UnipaxPtr<AlgebraicRule>::type AlgebraicRulePtr;

}//end namespace UniPAX

#endif

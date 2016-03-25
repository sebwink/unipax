#ifndef RATERULE_H
#define RATERULE_H
//Begin section for file RateRule.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file RateRule.h
#include<UNIPAX/KERNEL/EXT/Rule.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
				class UNIPAX_EXPORT RateRule : public Rule {

								protected:

												std::string variable;

												friend class odb::access;
												//void init (odb::callback_event e, odb::database& db) const;

								public:

												virtual std::string getType() {
																return "RateRule";
												}

												static std::string type() {
																return std::string("RateRule");
												}

												virtual UniPAX::ClassType::ID getTypeID() {
																return UniPAX::ClassType::idRateRule;
												}

												static UniPAX::ClassType::ID typeID() {
																return UniPAX::ClassType::idRateRule;
												}

												RateRule();

												RateRule(const RateRule & arg);

												RateRule & operator =(const RateRule & arg);

												~RateRule();

												bool merge(RateRule& object);

												bool update(PersistenceManager& manager);

												//get variable
												const std::string & getVariable() const;

												std::string & getVariable();

												void setVariable(std::string _variable);

												bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
												bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

				};  //end class RateRule

				typedef UnipaxPtr<RateRule>::type RateRulePtr;

}//end namespace UniPAX

#endif

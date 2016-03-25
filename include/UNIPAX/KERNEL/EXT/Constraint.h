#ifndef CONSTRAINT_H
#define CONSTRAINT_H
//Begin section for file Constraint.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Constraint.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<UNIPAX/KERNEL/EXT/Math.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include<boost/algorithm/string.hpp>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Constraint : public SBase {

protected:

	UnipaxPtr<Math>::type math;

	std::string message;


	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Constraint";
	}

	static std::string type() {
		return std::string("Constraint");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idConstraint;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idConstraint;
	}

	Constraint();

	Constraint(const Constraint & arg);

	Constraint & operator =(const Constraint & arg);

	~Constraint();

	bool merge(UniPAX::Constraint&);

	bool update(PersistenceManager& manager);

	//get message
	const std::string getMessage() const;

	std::string getMessage();

	void setMessage(std::string _message);


	const boost::shared_ptr<Math > getMath() const;

	//get math
	boost::shared_ptr<Math > getMath();

	//set math
	void setMath(boost::shared_ptr<Math > _math);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Constraint

typedef UnipaxPtr<Constraint>::type ConstraintPtr;

}//end namespace UniPAX

#endif

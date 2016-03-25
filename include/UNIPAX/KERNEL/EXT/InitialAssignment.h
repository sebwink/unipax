#ifndef INITIALASSIGNMENT_H
#define INITIALASSIGNMENT_H
//Begin section for file InitialAssignment.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file InitialAssignment.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<UNIPAX/KERNEL/EXT/Math.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT InitialAssignment : public SBase {

protected:

	std::string symbol;

	UnipaxPtr<Math>::type math;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "InitialAssignment";
	}

	static std::string type() {
		return std::string("InitialAssignment");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idInitialAssignment;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idInitialAssignment;
	}

	InitialAssignment();

	InitialAssignment(const InitialAssignment & arg);

	InitialAssignment & operator =(const InitialAssignment & arg);

	~InitialAssignment();

	bool merge(UniPAX::InitialAssignment&);

	bool update(UniPAX::PersistenceManager& manager);

	// symbol
	const std::string & getSymbol() const;

	std::string & getSymbol();

	void setSymbol(std::string _symbol);


	// math
	const boost::shared_ptr<Math > getMath() const;

	boost::shared_ptr<Math > getMath();

	void setMath(boost::shared_ptr<Math > _math);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class InitialAssignment

typedef UnipaxPtr<InitialAssignment>::type InitialAssignmentPtr;

}//end namespace UniPAX

#endif

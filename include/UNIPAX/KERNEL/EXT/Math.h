#ifndef MATH_H
#define MATH_H
//Begin section for file Math.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Math.h
#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Math : public UPBase {

protected:

	std::string mathML;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Math";
	}

	static std::string type() {
		return std::string("Math");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idMath;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idMath;
	}

	Math();

	Math(const Math & arg);

	Math & operator =(const Math & arg);

	~Math();

	bool merge(Math& object);

	bool update(PersistenceManager& manager);

	//get mathML
	const std::string & getMathML() const;

	std::string & getMathML();

	void setMathML(std::string _mathML);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Math

typedef UnipaxPtr<Math>::type MathPtr;

}//end namespace UniPAX

#endif

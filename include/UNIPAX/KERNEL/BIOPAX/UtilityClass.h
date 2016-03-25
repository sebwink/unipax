#ifndef UTILITYCLASS_H
#define UTILITYCLASS_H
//Begin section for file UtilityClass.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file UtilityClass.h
#include<UNIPAX/KERNEL/BIOPAX/Thing.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

class Thing;

#pragma db object abstract
class UNIPAX_EXPORT UtilityClass : public Thing {

protected:

	std::vector<std::string> comment;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

//	virtual std::string getType() {
//		return "UtilityClass";
//	}
//
//	static std::string type() {
//		return std::string("UtilityClass");
//	}
//
//	static UniPAX::ClassType::ID typeID() {
//		return UniPAX::ClassType::idUtilityClass;
//	}
//
//	virtual UniPAX::ClassType::ID getTypeID() {
//		return UniPAX::ClassType::idUtilityClass;
//	}

	UtilityClass();

	UtilityClass(const UtilityClass & arg);

	UtilityClass & operator =(const UtilityClass & arg);

	virtual ~UtilityClass();

	bool merge(UtilityClass& object);
	bool update(PersistenceManager& manager);

	//get comment
	const std::vector<std::string> & getComments() const;

	std::vector<std::string> & getComments();

	void setComments(std::vector<std::string> _comments);

	void addComment(std::string _comment);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef Thing super;

};  //end class UtilityClass

typedef UnipaxPtr<UtilityClass>::type UtilityClassPtr;

}//end namespace UniPAX

#endif

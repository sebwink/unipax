#ifndef XREF_H_
#define XREF_H_
//Begin section for file Xref.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file Xref.h
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>

#include<string>

namespace UniPAX {

class UtilityClass;

#pragma db object polymorphic
class UNIPAX_EXPORT Xref : public UtilityClass {

protected:

	std::string idVersion;

	std::string id;

	std::string dbVersion;

	std::string db;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Xref";
	}

	static std::string type() {
		return std::string("Xref");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idXref;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idXref;
	}

	Xref();

	Xref(const Xref & arg);

	Xref & operator =(const Xref & arg);

	~Xref();

	bool merge(Xref& object);
	bool update(PersistenceManager& manager);


	//get idVersion
	const std::string& getIdVersion() const;

	std::string& getIdVersion();

	void setIdVersion(std::string _idVersion);

	//get id
	const std::string& getId() const;

	std::string& getId();

	void setId(std::string _id);

	//get dbVersion
	const std::string& getDbVersion() const;

	std::string& getDbVersion();

	void setDbVersion(std::string _dbVersion);

	//get db
	const std::string& getDb() const;

	std::string& getDb();

	void setDb(std::string _db);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef UtilityClass super;

};  //end class Xref

typedef UnipaxPtr<Xref>::type XrefPtr;

}//end namespace UniPAX

#endif

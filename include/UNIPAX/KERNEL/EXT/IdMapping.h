#ifndef IDMAPPING_H
#define IDMAPPING_H
//Begin section for file IdMapping.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file IdMapping.h
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<odb/core.hxx>

namespace UniPAX {

class PersistenceManager;

#pragma db object polymorphic
class UNIPAX_EXPORT IdMapping : public UPBase {

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

private:
	int sample_index;
	std::string db_name;
	std::string db_version;
	std::multimap<int, std::string> id_list;

public:
	virtual std::string getType() {
		return "IdMapping";
	}

	static std::string type() {
		return std::string("IdMapping");
	}


	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idIdMapping;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idIdMapping;
	}

	IdMapping();

	IdMapping(const IdMapping & arg);

	IdMapping & operator =(const IdMapping & arg);

	~IdMapping();

	bool merge(IdMapping& object);

	bool update(PersistenceManager& manager);

	//sample_index
	const int getSampleIndex() const;

	int getSampleIndex();

	void setSampleIndex(int index);

	//db_name
	const std::string & getDbName() const;

	std::string & getDbName();

	void setDbName(std::string name_);

	//db_version
	const std::string & getDbVersion() const;

	std::string & getDbVersion();

	void setDbVersion(std::string version_);

	// id_map
	const std::multimap<int, std::string> & getIds() const;

	std::multimap<int, std::string> & getIds();

	void setIds(std::multimap<int, std::string> _ids);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class IdMapping

typedef UnipaxPtr<IdMapping>::type IdMappingPtr;

}//end namespace UniPAX

#endif

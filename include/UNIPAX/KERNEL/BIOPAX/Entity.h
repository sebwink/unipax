#ifndef ENTITY_H
#define ENTITY_H
//Begin section for file Entity.h
//TODO: Add definitions that you want preserved
#include<string>
#include<vector>
//End section for file Entity.h
#include<UNIPAX/KERNEL/BIOPAX/Thing.h>
#include<UNIPAX/KERNEL/BIOPAX/Evidence.h>
#include<UNIPAX/KERNEL/BIOPAX/Provenance.h>
#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

class Evidence;
class Provenance;
class Xref;

#pragma db object polymorphic
class UNIPAX_EXPORT Entity : public Thing {

	//Begin section for UniPAX::Entity
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::Entity

protected:

	std::string availability;

	std::vector<std::string> comments;

	std::vector<std::string> name;

	std::string standardName;

	std::string displayName;

	UnipaxPtr<Evidence>::type evidence;

	UnipaxPtr<Provenance>::type dataSource;

	// std::vector<unsigned long long> id_xref;
	//#pragma db transient
	std::vector<UnipaxPtr<Xref>::type > xref;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Entity";
	}

	static std::string type() {
		return std::string("Entity");
	}


	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idEntity;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idEntity;
	}

	Entity();

	Entity(const Entity & arg);

	Entity & operator =(const Entity & arg);

	~Entity();

	bool merge(Entity& object);
	bool update(PersistenceManager& manager);


	//get availability
	const std::string & getAvailability() const;

	std::string & getAvailability();

	void setAvailability(std::string _availability);

	//get comment
	const std::vector<std::string> & getComments() const;

	std::vector<std::string> & getComments();

	void setComments(std::vector<std::string> _comments);

	void addComment(std::string _comment);


	//get evidence
	const UnipaxPtr<Evidence>::type getEvidence() const;

	UnipaxPtr<Evidence>::type getEvidence();

	//void setEvidence(const Evidence& _evidence);

	void setEvidence(UnipaxPtr<Evidence>::type _evidence);

	//get dataSource
	const UnipaxPtr<Provenance>::type getDataSource() const;

	UnipaxPtr<Provenance>::type getDataSource();

	//void setDataSource(const Provenance& _dataSource);

	void setDataSource(UnipaxPtr<Provenance>::type _dataSource);

	//get xref
	const std::vector<UnipaxPtr<Xref>::type > & getXrefs() const;

	std::vector<UnipaxPtr<Xref>::type > & getXrefs();

	void addXref(UnipaxPtr<Xref>::type  _xref);

	void setXrefs(std::vector<UnipaxPtr<Xref>::type > _xrefs);

	//get name
	std::vector<std::string>& getNames();

	const std::vector<std::string>& getNames() const;

	std::string getFirstName();

	//set name
	void setNames(std::vector<std::string>& names);
	void addName(std::string name);


	const std::string & getStandardName() const;
	std::string & getStandardName();
	void setStandardName(std::string _name);


	const std::string & getDisplayName() const;
	std::string & getDisplayName();
	void setDisplayName(std::string _name);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef Thing super;

};  //end class Entity

typedef UnipaxPtr<Entity>::type EntityPtr;


}//end namespace UniPAX


#endif

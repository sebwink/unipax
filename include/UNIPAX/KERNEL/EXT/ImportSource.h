#ifndef IMPORTSOURCE_H
#define IMPORTSOURCE_H

#include<string>

#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT ImportSource : public UPBase {

protected:

	std::string name;
	std::string version;

	UnipaxPtr<ImportSource>::type successor;

#pragma db inverse(successor)
	boost::weak_ptr<ImportSource> predecessor;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "ImportSource";
	}

	static std::string type() {
		return std::string("ImportSource");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idImportSource;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idImportSource;
	}

	ImportSource();

	ImportSource(const ImportSource & arg);

	ImportSource & operator =(const ImportSource & arg);

	~ImportSource();

	bool merge(UniPAX::ImportSource&);

	bool update(UniPAX::PersistenceManager& manager);

	const std::string & getName() const;
	std::string & getName();
	void setName(std::string _name);

	const std::string & getVersion() const;
	std::string & getVersion();
	void setVersion(std::string _version);

	//get successor
	const UnipaxPtr<ImportSource>::type getSuccessor() const;

	UnipaxPtr<ImportSource>::type getSuccessor();

	void setSuccessor(UnipaxPtr<ImportSource>::type _successor);

	//get predecessor
	const boost::weak_ptr<ImportSource> getPredecessor() const;

	boost::weak_ptr<ImportSource> getPredecessor();

	void setPredecessor(boost::weak_ptr<ImportSource> _predecessor);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class ImportSource

typedef UnipaxPtr<ImportSource>::type ImportSourcePtr;

}//end namespace UniPAX

#endif

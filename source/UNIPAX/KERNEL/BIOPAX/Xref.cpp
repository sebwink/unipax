#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<iostream>
//Begin section for file Xref.cpp
//TODO: Add definitions that you want preserved
//End section for file Xref.cpp

UniPAX::Xref::Xref() :UniPAX::UtilityClass()  {
    }

UniPAX::Xref::Xref(const Xref& arg) : UniPAX::UtilityClass(arg) ,
	idVersion(arg.idVersion),
	id(arg.id),
	dbVersion(arg.dbVersion),
	db(arg.db)
{}

UniPAX::Xref & UniPAX::Xref::operator =(const Xref & arg)  {
	UniPAX::UtilityClass::operator=(arg);
	idVersion = arg.idVersion;
	id = arg.id;
	dbVersion = arg.dbVersion;
	db = arg.db;

	return *this;
}

UniPAX::Xref::~Xref()  {
    }


bool UniPAX::Xref::merge(Xref& object)
{
	if (!object.getDb().empty())
	{
		if (!getDb().empty())
		{
			if (getDb() != object.getDb())
			{
				std::cerr << "Error during merging: UniPAX::Xref::db not equal ..."
						<< getDb() << " != " << object.getDb() << std::endl;
				return false;
			}
		}
		else
			setDb(object.getDb());
	}
	if (!object.getDbVersion().empty())
	{
		if (!getDbVersion().empty())
		{
			if (getDbVersion() != object.getDbVersion())
			{
				std::cerr << "Error during merging: UniPAX::Xref::dbVersion not equal ..."
						<< getDbVersion() << " != " << object.getDbVersion() << std::endl;
				return false;
			}
		}
		else
			setDbVersion(object.getDbVersion());
	}
	if (!object.getId().empty())
	{
		if (!getId().empty())
		{
			if (getId() != object.getId())
			{
				std::cerr << "Error during merging: UniPAX::Xref::id not equal ..."
						<< getId() << " != " << object.getId() << std::endl;
				return false;
			}
		}
		else
			setId(object.getId());
	}
	if (!object.getIdVersion().empty())
	{
		if (!getIdVersion().empty())
		{
			if (getIdVersion() != object.getIdVersion())
			{
				std::cerr << "Error during merging: UniPAX::Xref::idVersion not equal ..."
						<< getIdVersion() << " != " << object.getIdVersion() << std::endl;
				return false;
			}
		}
		else
			setIdVersion(object.getIdVersion());
	}

	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::Xref::update(PersistenceManager& manager)
{
	return UniPAX::UtilityClass::update(manager);
}


const std::string & UniPAX::Xref::getIdVersion() const {
        return idVersion;
}

std::string & UniPAX::Xref::getIdVersion() {
	return idVersion;
}

void UniPAX::Xref::setIdVersion(std::string _idVersion) {
	idVersion = _idVersion;
}

const std::string & UniPAX::Xref::getId() const {
        return id;
}

std::string & UniPAX::Xref::getId() {
	return id;
}

void UniPAX::Xref::setId(std::string _id) {
	id = _id;
}

const std::string & UniPAX::Xref::getDbVersion() const {
        return dbVersion;
}

std::string & UniPAX::Xref::getDbVersion() {
	return dbVersion;
}

void UniPAX::Xref::setDbVersion(std::string _dbVersion) {
	dbVersion = _dbVersion;
}

const std::string & UniPAX::Xref::getDb() const {
        return db;
}

std::string & UniPAX::Xref::getDb() {
	return db;
}

void UniPAX::Xref::setDb(std::string _db) {
	db = _db;
}

bool UniPAX::Xref::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;


	if (boost::iequals(attribute,"db"))
	{
		setDb(value);
		return true;
	}
	if (boost::iequals(attribute,"dbversion"))
	{
		setDbVersion(value);
		return true;
	}
	if (boost::iequals(attribute,"id"))
	{
		setId(value);
		return true;
	}
	if (boost::iequals(attribute,"idversion"))
	{
		setIdVersion(value);
		return true;
	}

	return false;

}


bool UniPAX::Xref::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	if (!getDb().empty())
		value.push_back(std::pair<std::string,std::string>("db", getDb()));
	if (!getDbVersion().empty())
		value.push_back(std::pair<std::string,std::string>("dbVersion", getDbVersion()));
	if (!getId().empty())
		value.push_back(std::pair<std::string,std::string>("id", getId()));
	if (!getIdVersion().empty())
		value.push_back(std::pair<std::string,std::string>("idVersion", getIdVersion()));

	return true;

}

//void UniPAX::Xref::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	return;
//}

#include<UNIPAX/KERNEL/EXT/IdMapping.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include<sstream>
//Begin section for file IdMapping.cpp
//TODO: Add definitions that you want preserved
//End section for file IdMapping.cpp

UniPAX::IdMapping::IdMapping() : UniPAX::UPBase(),
sample_index(0)
{
}

UniPAX::IdMapping::IdMapping(const IdMapping & arg)  : UniPAX::UPBase(arg),
db_name(arg.db_name),
db_version(arg.db_version),
id_list(arg.id_list),
sample_index(arg.sample_index)
{}

UniPAX::IdMapping & UniPAX::IdMapping::operator =(const IdMapping & arg)  {
    UniPAX::UPBase::operator=(arg);
    db_name = arg.db_name;
		db_version = arg.db_version;
    id_list = arg.id_list;
		sample_index = arg.sample_index;

    return *this;
}

UniPAX::IdMapping::~IdMapping()  {
}

bool UniPAX::IdMapping::merge(UniPAX::IdMapping& object)
{
    std::cerr << "Error during merging: UniPAX::IdMapping should not be merged." << std::endl;
    return false;
}

bool UniPAX::IdMapping::update(PersistenceManager& manager)
{
    return UniPAX::UPBase::update(manager);
}


const int UniPAX::IdMapping::getSampleIndex() const
{
	return sample_index;
}

int UniPAX::IdMapping::getSampleIndex()
{
  return sample_index;
}

void UniPAX::IdMapping::setSampleIndex(int index)
{
	sample_index = index;
}

const std::string & UniPAX::IdMapping::getDbName() const
{
    return db_name;
}

std::string & UniPAX::IdMapping::getDbName()
{
    return db_name;
}

void UniPAX::IdMapping::setDbName(std::string db_name_) {
    db_name = db_name_;
}

const std::string & UniPAX::IdMapping::getDbVersion() const {
    return db_version;
}

std::string & UniPAX::IdMapping::getDbVersion() {
    return db_version;
}

void UniPAX::IdMapping::setDbVersion(std::string db_version_) {
    db_version = db_version_;
}

const std::multimap<int, std::string> & UniPAX::IdMapping::getIds() const {
    return id_list;
}

std::multimap<int, std::string> & UniPAX::IdMapping::getIds() {
    return id_list;
}

void UniPAX::IdMapping::setIds(std::multimap<int, std::string> id_list_) {
    id_list = id_list_;
}


bool UniPAX::IdMapping::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

    if (UniPAX::UPBase::setAttribute(attribute, value, manager))
        return true;
    if (boost::iequals(attribute, "sample_index"))
    {
        return manager.convertAttribute(value, sample_index);
    }
    if (boost::iequals(attribute, "db_name"))
    {
        db_name = value;
        return true;
    }
    if (boost::iequals(attribute, "db_version"))
    {
        db_version = value;
        return true;
    }
    if (boost::iequals(attribute, "id_list"))
    {
				std::stringstream ss;
				ss.str(value);
				int index;
				std::string id;
				ss >> index >> id;
        id_list.insert(std::pair<int, std::string>(index, id));
        return true;
    }
    return false;
}

bool UniPAX::IdMapping::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

    if (!UniPAX::UPBase::getAttribute(value, manager))
        return false;

		std::string tmp;
		if (!manager.convertAttribute(sample_index, tmp))
		{
				return false;
		}
		value.push_back(std::pair<std::string,std::string>("sample_index", tmp));
    value.push_back(std::pair<std::string,std::string>("db_name", db_name));
    value.push_back(std::pair<std::string,std::string>("db_version", db_version));
		std::stringstream ss;

    for (std::multimap<int, std::string>::const_iterator it = id_list.begin(); it != id_list.end(); it++)
    {
				ss.str("");
				ss << it->first << "\t" << it->second;
        value.push_back(std::pair<std::string, std::string>("id_list", ss.str()));
    }
    return true;
}

//void UniPAX::IdMapping::init (odb::callback_event e, odb::database& db) const
//{
//    UniPAX::UPBase::init(e,db);
//    // no object pointer to set
//}

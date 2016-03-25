#include<UNIPAX/KERNEL/EXT/ImportSource.h>
//Begin section for file ImportSource.cpp
//TODO: Add definitions that you want preserved
//End section for file ImportSource.cpp

UniPAX::ImportSource::ImportSource() : UniPAX::UPBase()
	, name ("")
	, version("")
//, successor(0)
//, predecessor(0)
{
}

UniPAX::ImportSource::ImportSource(const ImportSource & arg)  : UniPAX::UPBase(arg),
		name(arg.name),
		version(arg.version),
		successor(arg.successor),
		predecessor(arg.predecessor)
{
}

UniPAX::ImportSource & UniPAX::ImportSource::operator =(const ImportSource & arg)  {
	UniPAX::UPBase::operator=(arg);
	name = arg.name;
	version = arg.version;
	successor = arg.successor;
	predecessor = arg.predecessor;

	return *this;
}

UniPAX::ImportSource::~ImportSource()  {
}

bool UniPAX::ImportSource::merge(ImportSource& object)
{
		std::cerr << "Error during merging: UniPAX::ImportSource should not be merged." << std::endl;
		return UniPAX::UPBase::merge(object);
}

bool UniPAX::ImportSource::update(PersistenceManager& manager)
{
		return UniPAX::UPBase::update(manager);
}

const std::string & UniPAX::ImportSource::getName() const
{
	return name;
}

std::string & UniPAX::ImportSource::getName()
{
	return name;
}

void UniPAX::ImportSource::setName(std::string _name)
{
	name = _name;
}

const std::string & UniPAX::ImportSource::getVersion() const
{
	return version;
}

std::string & UniPAX::ImportSource::getVersion()
{
	return version;
}

void UniPAX::ImportSource::setVersion(std::string _version)
{
	version = _version;
}


const boost::shared_ptr<UniPAX::ImportSource> UniPAX::ImportSource::getSuccessor() const {
	return successor;
}

boost::shared_ptr<UniPAX::ImportSource> UniPAX::ImportSource::getSuccessor() {
	return successor;
}

void UniPAX::ImportSource::setSuccessor(boost::shared_ptr<UniPAX::ImportSource> _successor) {
	successor = _successor;
}

const boost::weak_ptr<UniPAX::ImportSource> UniPAX::ImportSource::getPredecessor() const {
	return predecessor;
}

boost::weak_ptr<UniPAX::ImportSource> UniPAX::ImportSource::getPredecessor() {
	return predecessor;
}

void UniPAX::ImportSource::setPredecessor(boost::weak_ptr<UniPAX::ImportSource> _predecessor) {
	predecessor = _predecessor;
}


bool UniPAX::ImportSource::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	return false;
}

bool UniPAX::ImportSource::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	return true;
}

//void UniPAX::ImportSource::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UPBase::init(e,db);
//
//	return;
//}

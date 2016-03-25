#include <UNIPAX/COMMON/OrganismSet.h>

UniPAX::OrganismSet::OrganismSet(DBConnectorPtr dbConnector)
{
	dbConnector_ = dbConnector;
}

UniPAX::OrganismSet::OrganismSet(const OrganismSet & ors) :
        		ids_(ors.ids_), dbConnector_(ors.dbConnector_)
{
}

UniPAX::OrganismSet & UniPAX::OrganismSet::operator =(const OrganismSet & rhs)
{
	ids_ = rhs.ids_;
	dbConnector_ = rhs.dbConnector_;
	return *this;
}

UniPAX::OrganismSet::~OrganismSet()
{
}

const std::set<UnipaxId> UniPAX::OrganismSet::getIds() const
{
	return ids_;
}

std::set<UnipaxId> UniPAX::OrganismSet::getIds()
{
	return ids_;
}

void UniPAX::OrganismSet::setIds(std::set<UnipaxId> ids)
{
	ids_ = ids;
}

bool UniPAX::OrganismSet::isEmpty()
{
	return ids_.empty();
}


bool UniPAX::OrganismSet::addById(UnipaxId id)
{
	if (UniPAX::OrganismSet::isValidOrganismId(id))
	{
		return ids_.insert(id).second;
	}
	return false;
}

bool UniPAX::OrganismSet::isValidOrganismId(UnipaxId id)
{
	return DBManager::isType(id, UniPAX::ClassType::idBioSource);
}

#include <UNIPAX/COMMON/PathwaySet.h>

UniPAX::PathwaySet::PathwaySet(DBConnectorPtr dbConnector)
{
	dbConnector_ = dbConnector;
}

UniPAX::PathwaySet::PathwaySet(const PathwaySet & pws) :
        ids_(pws.ids_),
				dbConnector_(pws.dbConnector_)
{
}

UniPAX::PathwaySet & UniPAX::PathwaySet::operator =(const PathwaySet & rhs)
{
    ids_ = rhs.ids_;
		dbConnector_ = rhs.dbConnector_;
    return *this;
}

UniPAX::PathwaySet::~PathwaySet()
{
}

const std::set<UnipaxId> & UniPAX::PathwaySet::getIds() const
{
    return ids_;
}

std::set<UnipaxId> & UniPAX::PathwaySet::getIds()
{
    return ids_;
}

void UniPAX::PathwaySet::setIds(std::set<UnipaxId> ids)
{
    ids_ = ids;
}

bool UniPAX::PathwaySet::isEmpty()
{
    return ids_.empty();
}

bool UniPAX::PathwaySet::addById(UnipaxId id)
{
    if (UniPAX::PathwaySet::isValidPathwayId(id))
    {
				return ids_.insert(id).second;
    }
    return false;
}

bool UniPAX::PathwaySet::isValidPathwayId(UnipaxId id)
{
	return DBManager::isType(id, ClassType::idPathway);
}

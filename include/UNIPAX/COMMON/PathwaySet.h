#ifndef PATHWAYSET_H
#define PATHWAYSET_H

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/COMMON/DBConnector.h>
#include <set>

namespace UniPAX
{

class UNIPAX_EXPORT PathwaySet
{
public:

	PathwaySet(DBConnectorPtr dbConnector);
	PathwaySet(const PathwaySet & pws);
	PathwaySet & operator =(const PathwaySet & rhs);
	virtual ~PathwaySet();

	const std::set<UnipaxId> & getIds() const;
	std::set<UnipaxId> & getIds();
	void setIds(std::set<UnipaxId> ids);

	bool isEmpty();

	bool addById(UnipaxId id);

	bool isValidPathwayId(UnipaxId id);

private:

	std::set<UnipaxId> ids_;
	DBConnectorPtr dbConnector_;

};

typedef UnipaxPtr<PathwaySet>::type PathwaySetPtr;

} // end namespace

#endif // PATHWAYSET_H

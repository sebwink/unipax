#ifndef ORGANISMSET_H
#define ORGANISMSET_H

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/COMMON/DBConnector.h>
#include <set>

namespace UniPAX
{

class UNIPAX_EXPORT OrganismSet
{
public:

	OrganismSet(DBConnectorPtr dbConnector);
	OrganismSet(const OrganismSet & ors);
	OrganismSet & operator =(const OrganismSet & rhs);
	virtual ~OrganismSet();

	const std::set<UnipaxId> getIds() const;
	std::set<UnipaxId> getIds();
	void setIds(std::set<UnipaxId> ids);

	bool isEmpty();

	bool addById(UnipaxId id);

	bool isValidOrganismId(UnipaxId id);

private:
	std::set<UnipaxId> ids_;
	DBConnectorPtr dbConnector_;

};

typedef UnipaxPtr<OrganismSet>::type OrganismSetPtr;

} // end namespace

#endif // ORGANISMSET_H

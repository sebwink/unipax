#include<UNIPAX/PERSISTENCE/ODBPersistRunnable.h>

UniPAX::ODBPersistRunnable::ODBPersistRunnable(boost::shared_ptr<UniPAX::UPBase> _object) : UniPAX::ODBRunnable()
{
	objects.push_back(_object);
	ids.push_back(0);
}

UniPAX::ODBPersistRunnable::ODBPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects) : UniPAX::ODBRunnable(), objects(_objects)
{
	for (int i = 0; i < _objects.size(); ++i)
		ids.push_back(0);
}

std::vector<UnipaxId> UniPAX::ODBPersistRunnable::getIds()
{
	return ids;
}

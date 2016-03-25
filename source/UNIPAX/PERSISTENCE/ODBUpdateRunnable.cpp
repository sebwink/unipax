#include<UNIPAX/PERSISTENCE/ODBUpdateRunnable.h>


UniPAX::ODBUpdateRunnable::ODBUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> _object) : UniPAX::ODBRunnable()
{
	objects.push_back(_object);
	successful.push_back(false);
}

UniPAX::ODBUpdateRunnable::ODBUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects) : UniPAX::ODBRunnable(), objects(_objects)
{
	for (int i = 0; i < _objects.size(); ++i)
		successful.push_back(false);
}

std::vector<bool> UniPAX::ODBUpdateRunnable::getSuccessful()
{
	return successful;
}


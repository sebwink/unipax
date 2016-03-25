#include<UNIPAX/PERSISTENCE/ODBLoadRunnable.h>


UniPAX::ODBLoadRunnable::ODBLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> &_ids)
	: UniPAX::ODBRunnable(), objects(result), ids(_ids)
{

}

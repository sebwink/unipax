#include<UNIPAX/PERSISTENCE/ODBUnloadRunnable.h>
#include<UNIPAX/KERNEL/BIOPAX/BiochemicalReaction.h>
#include<UNIPAX/PERSISTENCE/MYSQL/EXT/UPBase-odb.hxx>

UniPAX::ODBUnloadRunnable::ODBUnloadRunnable(std::vector<UnipaxId> &_ids)
	: UniPAX::ODBRunnable(), ids(_ids)
{

}

void UniPAX::ODBUnloadRunnable::run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database)
{
}

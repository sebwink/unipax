#include <UNIPAX/COMMON/KernelClassSet.h>

UniPAX::KernelClassSet::KernelClassSet(DBConnectorPtr dbConnector)
{
	dbConnector_ = dbConnector;
}

UniPAX::KernelClassSet::KernelClassSet(const KernelClassSet & kcs) :
        		types_(kcs.types_),
        		dbConnector_(kcs.dbConnector_)
{
}

UniPAX::KernelClassSet & UniPAX::KernelClassSet::operator =(const KernelClassSet & rhs)
{
	types_ = rhs.types_;
	dbConnector_ = rhs.dbConnector_;
	return *this;
}

UniPAX::KernelClassSet::~KernelClassSet()
{
}

const std::set<UniPAX::ClassType::ID> UniPAX::KernelClassSet::getIds() const
{
	return types_;
}
std::set<UniPAX::ClassType::ID> UniPAX::KernelClassSet::getIds()
{
	return types_;
}

void UniPAX::KernelClassSet::setIds(std::set<UniPAX::ClassType::ID> types)
{
	types_ = types;
}

bool UniPAX::KernelClassSet::isEmpty()
{
	return types_.empty();
}

bool UniPAX::KernelClassSet::addById(UniPAX::ClassType::ID type)
{
	if (UniPAX::Kernel::isClassType(type))
	{
		return types_.insert(type).second;
	}
	return false;
}

bool UniPAX::KernelClassSet::addByName(std::string name)
{
	UniPAX::ClassType::ID id = Kernel::classType(name);

	if (id != UniPAX::ClassType::END_ENUM)
	{
		return addById(id);
	}
	return false;
}


#ifndef KERNELCLASSSET_H
#define KERNELCLASSSET_H

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/COMMON/DBConnector.h>
#include <UNIPAX/KERNEL/ClassType.h>
#include <set>

namespace UniPAX
{

class UNIPAX_EXPORT KernelClassSet
{
public:

	KernelClassSet(DBConnectorPtr dbConnector);
	KernelClassSet(const KernelClassSet & kcs);
	KernelClassSet & operator =(const KernelClassSet & rhs);
	virtual ~KernelClassSet();

	const std::set<ClassType::ID> getIds() const;
	std::set<ClassType::ID> getIds();
	void setIds(std::set<ClassType::ID> types);

	bool isEmpty();

	bool addById(ClassType::ID type);
	bool addByName(std::string name);

private:

	std::set<ClassType::ID> types_;
	DBConnectorPtr dbConnector_;

};

typedef UnipaxPtr<KernelClassSet>::type KernelClassSetPtr;

} // end namespace

#endif // KERNELCLASSSET_H

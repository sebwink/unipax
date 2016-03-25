#include <UNIPAX/COMMON/MergerInputAdapter.h>
#include <UNIPAX/KERNEL/Kernel.h>
#include <iostream>

namespace UniPAX
{

MergerInputAdapter::MergerInputAdapter() : nextId(0)
{
	input_type = MergerInput::NONE;
}

MergerInputAdapter::MergerInputAdapter(UnipaxPtr<UniPAX::PersistenceManager>::type manager, MergerInputAdapter::idGenFuncPtr ptr) :
						nextId(ptr),
						input_type(MergerInput::PERSISTENCE_MANAGER),
						pm(manager)
{
}

MergerInputAdapter::MergerInputAdapter(UniPAX::DBManager manager, MergerInputAdapter::idGenFuncPtr ptr) :
							nextId(ptr),
							input_type(MergerInput::DB_MANAGER),
							dm(manager)
{
}

MergerInputAdapter::MergerInputAdapter(const MergerInputAdapter & m)
{
	nextId = m.nextId;
	input_type = m.input_type;
	pm = m.pm;
	dm = m.dm;
	pointer_id = m.pointer_id;
}

MergerInputAdapter & MergerInputAdapter::operator=(const MergerInputAdapter & arg)
{
	nextId = arg.nextId;
	input_type = arg.input_type;
	pm = arg.pm;
	dm = arg.dm;
	pointer_id = arg.pointer_id;
	return *this;
}

//UniPAX::PersistenceManager

MergerInputAdapter::~MergerInputAdapter() {}

MergerInputAdapter::idGenFuncPtr MergerInputAdapter::getIdGenFunction()
{
	return nextId;
}

bool MergerInputAdapter::removeInstance(UniPAX::UPBasePtr ptr)
{
	if (input_type != MergerInput::NONE && pointer_id.empty())
	{
		if (!fillPtrIdMap())
		{
			std::cerr << "MergerInputAdapter::getPtrIdMap: failed." << std::endl;
			return false;
		}
	}
	if (!pm->remove(ptr))
	{
		return false;
	}
	pointer_id.erase(ptr);
	return true;
}

void MergerInputAdapter::setIdGenFunction(MergerInputAdapter::idGenFuncPtr ptr)
{
	nextId = ptr;
}

bool MergerInputAdapter::fillPtrIdMap()
{
	if (input_type != MergerInput::NONE)
	{
		std::vector< boost::shared_ptr<UniPAX::UPBase> > dummy;
		return getObjectsByType(dummy, "UPBase", true);
	}
	return true;
}

std::map<UniPAX::UPBasePtr, UnipaxId> & MergerInputAdapter::getPtrIdMap()
{
	if (input_type != MergerInput::NONE && pointer_id.empty())
	{
		if (!fillPtrIdMap()) std::cerr << "MergerInputAdapter::getPtrIdMap: failed." << std::endl;
	}
	return pointer_id;
}

UnipaxPtr<UniPAX::PersistenceManager>::type & MergerInputAdapter::getPersistenceManager()
{
	if (input_type == MergerInput::DB_MANAGER)
	{
		//TODO handle this
	}
	return pm;
}

bool MergerInputAdapter::getObjectsByType(std::vector< boost::shared_ptr<UniPAX::UPBase> >& result, std::string type, bool recursive)
{
	if (input_type == MergerInput::DB_MANAGER)
	{
		if (!dm.getObjectsByType(result, type, recursive)) return false;
	}
	if (input_type == MergerInput::PERSISTENCE_MANAGER)
	{
		std::set<std::string> children = UniPAX::Kernel::children(type, recursive);
		children.insert(type);
		for (std::map<std::string, std::string>::const_iterator it = pm->getIdToType().begin(); it != pm->getIdToType().end(); it++)
		{
			if (children.find(it->second) != children.end())
			{
				std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator help = pm->getData().find(it->first);
				if (help == pm->getData().end())
				{
					std::cerr << "Error in PersistenceManager" << std::endl;
					return false;
				}
				result.push_back(help->second);
			}
		}
	}
	for (std::vector<UniPAX::UPBasePtr>::iterator it = result.begin(); it != result.end(); ++it)
	{
		if (pointer_id.find(*it) == pointer_id.end())
		{
			UnipaxId newId = (*nextId)();
			pointer_id.insert(std::pair<UniPAX::UPBasePtr, UnipaxId>(*it, newId));
			(*it)->setUnipaxId(newId);
		}
		else
		{
			(*it)->setUnipaxId(pointer_id.at(*it));
		}
		if (input_type == MergerInput::PERSISTENCE_MANAGER)
		{
			pm->update(*it);
		}
	}
	return true;
}

}


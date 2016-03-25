#include<UNIPAX/KERNEL/EXT/UIBase.h>

UniPAX::UIBase::UIBase() : UniPAX::UPBase()
//, unipaxSource(0)
{
}

UniPAX::UIBase::UIBase(const UniPAX::UIBase & arg) : UniPAX::UPBase(arg),
		unipaxSource(arg.unipaxSource)
{
}

UniPAX::UIBase & UniPAX::UIBase::operator =(const UniPAX::UIBase & arg) {
	unipaxSource = arg.unipaxSource;
	return *this;
}

UniPAX::UIBase::~UIBase()  {
}

//get unipaxSource
const boost::shared_ptr<UniPAX::ImportSource> UniPAX::UIBase::getUnipaxSource() const
{
	return unipaxSource;
}

boost::shared_ptr<UniPAX::ImportSource> UniPAX::UIBase::getUnipaxSource()
{
	return unipaxSource;
}

void UniPAX::UIBase::setUnipaxSource(boost::shared_ptr<UniPAX::ImportSource> _unipaxSource)
{
	unipaxSource = _unipaxSource;
}

bool UniPAX::UIBase::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {
	if(UniPAX::UPBase::setAttribute(attribute, value, manager))
		return true;

		if (boost::iequals(attribute,"unipaxSource"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value);
		if (object == 0)
		{
			std::cerr << "SBase::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		unipaxSource = boost::dynamic_pointer_cast<UniPAX::ImportSource>(object);
		return true;
	}

	return false;
}


bool UniPAX::UIBase::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UPBase::getAttribute(value, manager))
		return false;

	if (unipaxSource == 0)
	{
		//		value.push_back(std::pair<std::string,std::string>("#unipaxSource", "NIL"));
	}
	else
	{
		std::string tmp;
		//tmp.clear();
		if (!manager.getId(unipaxSource,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#unipaxSource", tmp));

	}

	return true;

}


bool UniPAX::UIBase::merge(UIBase& object)
{
//	if (unipaxSource != 0)
//	{
//		if (object.getUnipaxSource() != 0)
//		{
//
//			if (unipaxSource->getUnipaxId() != object.getUnipaxSource()->getUnipaxId())
//			{
//				std::cerr << "Error during merging: UniPAX::SBase::unipaxSource not equal ..."
//						<< unipaxSource->getUnipaxId() << " != " << object.getUnipaxSource()->getUnipaxId() << std::endl;
//				return false;
//			}
//		}
//	}
//	else
//	{
//		unipaxSource = object.getUnipaxSource();
//	}

	return UniPAX::UPBase::merge(object);
}

bool UniPAX::UIBase::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
//	if (manager.isMerged(getUnipaxSource()))
//	{
//		setUnipaxSource(boost::dynamic_pointer_cast<ImportSource>(manager.getMergedObject(getUnipaxSource())));
//	}

	return UniPAX::UPBase::update(manager);
}


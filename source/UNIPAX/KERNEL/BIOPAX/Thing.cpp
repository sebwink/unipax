#include<UNIPAX/KERNEL/BIOPAX/Thing.h>
#include<set>
//Begin section for file Thing.cpp
//TODO: Add definitions that you want preserved
//End section for file Thing.cpp

UniPAX::Thing::Thing() : UniPAX::UIBase()
//  ,
//	unipaxSource(0)
{
    }

UniPAX::Thing::Thing(const UniPAX::Thing & arg) : UniPAX::UIBase(arg)
{
}

UniPAX::Thing & UniPAX::Thing::operator =(const UniPAX::Thing & arg)  {
	UniPAX::UIBase::operator=(arg);
	return *this;
}

UniPAX::Thing::~Thing()  {
    }


bool UniPAX::Thing::merge(Thing& object)
{
	return UniPAX::UPBase::merge(object);
}

bool UniPAX::Thing::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
//	if (manager.isMerged(getUnipaxSource()))
//	{
//		setUnipaxSource(boost::dynamic_pointer_cast<ImportSource>(manager.getMergedObject(getUnipaxSource())));
//	}

	return UniPAX::UIBase::update(manager);
}
//
////get unipaxSource
//const boost::shared_ptr<UniPAX::ImportSource> UniPAX::Thing::getUnipaxSource() const
//{
//	return unipaxSource;
//}
//
//boost::shared_ptr<UniPAX::ImportSource> UniPAX::Thing::getUnipaxSource()
//{
//	return unipaxSource;
//}
//
//void UniPAX::Thing::setUnipaxSource(boost::shared_ptr<UniPAX::ImportSource> _unipaxSource)
//{
//	unipaxSource = _unipaxSource;
//}


bool UniPAX::Thing::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UIBase::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"unipaxSource"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value);
		if (object == 0)
		{
			std::cerr << "Thing::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		//unipaxSource = boost::dynamic_pointer_cast<UniPAX::ImportSource>(object);
		return true;
	}

	return false;

}

bool UniPAX::Thing::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UIBase::getAttribute(value, manager))
		return false;

//	std::string tmp = "";
//
//	if (unipaxSource == 0)
//	{
////		value.push_back(std::pair<std::string,std::string>("#unipaxSource", "NIL"));
//	}
//	else
//	{
//		tmp.clear();
//		if (!manager.getId(unipaxSource,tmp))
//		{
//			return false;
//		}
//		value.push_back(std::pair<std::string,std::string>("#unipaxSource", tmp));
//
//	}

	return true;

}

//void UniPAX::Thing::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UPBase::init(e,db);
//
//	return;
//}

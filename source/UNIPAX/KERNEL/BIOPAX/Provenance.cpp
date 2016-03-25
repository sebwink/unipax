#include<UNIPAX/KERNEL/BIOPAX/Provenance.h>
#include<set>
//Begin section for file Provenance.cpp
//TODO: Add definitions that you want preserved
//End section for file Provenance.cpp

UniPAX::Provenance::Provenance() : UniPAX::UtilityClass() {
    }

UniPAX::Provenance::Provenance(const Provenance & arg) : UniPAX::UtilityClass(arg) ,
    	    	    	    standardName(arg.standardName),
    	    	    	    displayName(arg.displayName),
    	    	    	    name(arg.name)
//    	    	    	    id_xref(arg.id_xref)
{
    }

UniPAX::Provenance & UniPAX::Provenance::operator =(const Provenance & arg)
{
	UniPAX::UtilityClass::operator=(arg);
    standardName = arg.standardName;
    displayName = arg.displayName;
    name = arg.name;
//    id_xref = arg.id_xref;

	return *this;
}

UniPAX::Provenance::~Provenance()  {
    }

bool UniPAX::Provenance::merge(Provenance& object)
{
	{
		std::set<UniPAX::XrefPtr> tmp(getXrefs().begin(), getXrefs().end());
		for (std::vector<UniPAX::XrefPtr>::iterator it = object.getXrefs().begin(); it != object.getXrefs().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getXrefs().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<std::string> tmp(getNames().begin(), getNames().end());
		for (std::vector<std::string>::iterator it = object.getNames().begin(); it != object.getNames().end(); it++)
		{
			tmp.insert(*it);
		}
		if (!object.getStandardName().empty())
		{
			if (getStandardName().empty())
				setStandardName(object.getStandardName());
			tmp.insert(object.getStandardName());
		}
		if (!object.getDisplayName().empty())
		{
			if (getDisplayName().empty())
				setDisplayName(object.getStandardName());
			tmp.insert(object.getDisplayName());
		}
		getNames().assign(tmp.begin(), tmp.end());
	}

	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::Provenance::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::Xref> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Xref> >::iterator it;
		for (it = xref.begin(); it != xref.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Xref>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setXrefs(tmp_vec);
	}

	return UniPAX::UtilityClass::update(manager);
}



const std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::Provenance::getXrefs() const {
    return xref;
}

std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::Provenance::getXrefs() {
	return xref;
}

void UniPAX::Provenance::addXref(boost::shared_ptr<UniPAX::Xref>  _xref) {
	xref.push_back(_xref);
}

void UniPAX::Provenance::setXrefs(std::vector<boost::shared_ptr<UniPAX::Xref> > _xrefs) {
	xref = _xrefs;
}



std::vector<std::string> & UniPAX::Provenance::getNames()  {
    return name;
}

const std::vector<std::string>& UniPAX::Provenance::getNames() const {
	return name;
}

std::string UniPAX::Provenance::getFirstName()  {
	if (!name.empty())
		return name[0];
    return "";
}

void UniPAX::Provenance::setNames(std::vector<std::string>& _names)  {
	name = _names;
}

void UniPAX::Provenance::addName(std::string _name)  {
	name.push_back(_name);
}


const std::string & UniPAX::Provenance::getStandardName() const
{
	return standardName;
}

std::string & UniPAX::Provenance::getStandardName()
{
	return standardName;
}

void UniPAX::Provenance::setStandardName(std::string _name)
{
	standardName = _name;

	std::vector<std::string>::iterator it;

	for (it = name.begin(); it != name.end(); it++)
	{
		if (_name == *it)
			return;
	}
	name.push_back(_name);
}

const std::string & UniPAX::Provenance::getDisplayName() const
{
	return displayName;
}

std::string & UniPAX::Provenance::getDisplayName()
{
	return displayName;
}

void UniPAX::Provenance::setDisplayName(std::string _name)
{
	displayName = _name;

	std::vector<std::string>::iterator it;

	for (it = name.begin(); it != name.end(); it++)
	{
		if (_name == *it)
			return;
	}
	name.push_back(_name);
}





bool UniPAX::Provenance::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"xref"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Provenance::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		xref.push_back(boost::dynamic_pointer_cast<UniPAX::Xref>(object));
		return true;
	}
	if (boost::iequals(attribute,"name"))
	{
		name.push_back(value);
		if (getDisplayName().empty())
			setDisplayName(value);
		if (getStandardName().empty())
			setStandardName(value);
		return true;
	}
	if (boost::iequals(attribute,"standardName"))
	{
		setStandardName(value);
		if (getDisplayName().empty())
			setDisplayName(value);
		return true;
	}
	if (boost::iequals(attribute,"displayName"))
	{
		setDisplayName(value);
		if (getStandardName().empty())
			setStandardName(value);
		return true;
	}

	return false;

}



bool UniPAX::Provenance::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	std::vector<boost::shared_ptr<UniPAX::Xref> >::iterator it;
	for (it = xref.begin(); it != xref.end(); it++)
	{
		if (*it == 0)
		{
//			value.push_back(std::pair<std::string,std::string>("#xref", "NIL"));
		}
		else
		{
			tmp.clear();
			if (!manager.getId(*it,tmp))
			{
				return false;
			}
			value.push_back(std::pair<std::string,std::string>("#xref", tmp));

		}
	}

	std::vector<std::string>::iterator nit;
	for (nit = name.begin(); nit != name.end(); nit++)
		value.push_back(std::pair<std::string,std::string>("name", *nit));
	if (!getStandardName().empty())
		value.push_back(std::pair<std::string,std::string>("standardName", getStandardName()));
	if (!getDisplayName().empty())
		value.push_back(std::pair<std::string,std::string>("displayName", getDisplayName()));

	return true;

}

//void UniPAX::Provenance::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		xref.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_xref.begin(); it != id_xref.end(); it++)
//		{
//			xref.push_back(boost::dynamic_pointer_cast<UniPAX::Xref>(getObjectByID(db, *it)));
//		}
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		id_xref.clear();
//		std::vector<boost::shared_ptr<Xref> >::iterator it;
//		for (it = xref.begin(); it != xref.end(); it++)
//		{
//			if (*it != 0)
//				id_xref.push_back((*it)->getUnipaxId());
//		}
//
//	}
//
//	return;
//}

#include <UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include <set>
//Begin section for file BioSource.cpp
//TODO: Add definitions that you want preserved
//End section for file BioSource.cpp

UniPAX::BioSource::BioSource() : UniPAX::UtilityClass()
{
    }

UniPAX::BioSource::BioSource(const UniPAX::BioSource & arg) : UniPAX::UtilityClass(arg),
		    standardName(arg.standardName),
    	    displayName(arg.displayName),
    	    name(arg.name),
			tissue(arg.tissue),
			cellType(arg.cellType),
			xref(arg.xref)
//			id_xref(arg.id_xref)
{

	std::cout << "BioSource: Created copy of " << arg.unipaxId << std::endl;
    }

UniPAX::BioSource & UniPAX::BioSource::operator =(const UniPAX::BioSource & arg)
{
	UniPAX::UtilityClass::operator=(arg);
    standardName = arg.standardName;
    displayName = arg.displayName;
    name = arg.name;
	tissue = arg.tissue;
	cellType = arg.cellType;
	xref = arg.xref;
//	id_xref = arg.id_xref;

	return *this;

    }

UniPAX::BioSource::~BioSource()  {
    }

bool UniPAX::BioSource::merge(BioSource& object)
{
	if (tissue != 0)
	{
		if (object.getTissue() != 0)
		{
			if (tissue->getUnipaxId() != object.getTissue()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::BioSource::tissue not equal ..."
						<< tissue->getUnipaxId() << " != " << object.getTissue()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setTissue(object.getTissue());
	}
	{
		std::set<UniPAX::CellVocabularyPtr> tmp(getCellTypes().begin(), getCellTypes().end());
		for (std::vector<UniPAX::CellVocabularyPtr>::iterator it = object.getCellTypes().begin(); it != object.getCellTypes().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getCellTypes().assign(tmp.begin(), tmp.end());
	}
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


bool UniPAX::BioSource::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getTissue()))
	{
		setTissue(boost::dynamic_pointer_cast<TissueVocabulary>(manager.getMergedObject(getTissue())));
	}
	{
		// run through vector to check each pointer
		std::vector<boost::shared_ptr<UniPAX::CellVocabulary> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::CellVocabulary> >::iterator it;
		for (it = cellType.begin(); it != cellType.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<CellVocabulary>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setCellTypes(tmp_vec);
	}
	{
		std::set<boost::shared_ptr<UniPAX::Xref> > tmp_set;
		std::vector<boost::shared_ptr<UniPAX::Xref> >::iterator it;
		for (it = xref.begin(); it != xref.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_set.insert(boost::dynamic_pointer_cast<Xref>(manager.getMergedObject(*it)));
			else
				tmp_set.insert(*it);
		}
		setXrefs(std::vector<boost::shared_ptr<UniPAX::Xref> >(tmp_set.begin(), tmp_set.end()));
	}

	return UniPAX::UtilityClass::update(manager);
}

const boost::shared_ptr<UniPAX::TissueVocabulary> UniPAX::BioSource::getTissue() const {
    return tissue;
}

boost::shared_ptr<UniPAX::TissueVocabulary> UniPAX::BioSource::getTissue() {
	return tissue;
}

void UniPAX::BioSource::setTissue(boost::shared_ptr<UniPAX::TissueVocabulary> _tissue) {
	tissue = _tissue;
}

const std::vector<boost::shared_ptr<UniPAX::CellVocabulary> > & UniPAX::BioSource::getCellTypes() const {
        return cellType;
}

std::vector<boost::shared_ptr<UniPAX::CellVocabulary> > & UniPAX::BioSource::getCellTypes() {
	return cellType;
}

void UniPAX::BioSource::setCellTypes(std::vector<boost::shared_ptr<UniPAX::CellVocabulary> > _cellTypes) {
	cellType = _cellTypes;
}

void UniPAX::BioSource::addCellType(boost::shared_ptr<UniPAX::CellVocabulary>  _cellType) {
	cellType.push_back(_cellType);
}


const std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::BioSource::getXrefs() const {
        return xref;
}

std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::BioSource::getXrefs() {
	return xref;
}

void UniPAX::BioSource::setXrefs(std::vector<boost::shared_ptr<UniPAX::Xref> > _xrefs) {
	xref = _xrefs;
}

void UniPAX::BioSource::addXref(boost::shared_ptr<UniPAX::Xref>  _xref) {
	xref.push_back(_xref);
}


const std::vector<std::string> & UniPAX::BioSource::getNames() const
{
	return name;
}

std::vector<std::string> & UniPAX::BioSource::getNames()
{
	return name;
}

void UniPAX::BioSource::setNames(std::vector<std::string> _names)
{
	name = _names;
}

void UniPAX::BioSource::addName(std::string _name) {
	std::vector<std::string>::iterator it;

	for (it = name.begin(); it != name.end(); it++)
	{
		if (_name == *it)
			return;
	}
	name.push_back(_name);
}


const std::string & UniPAX::BioSource::getStandardName() const
{
	return standardName;
}

std::string & UniPAX::BioSource::getStandardName()
{
	return standardName;
}

void UniPAX::BioSource::setStandardName(std::string _name)
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

const std::string & UniPAX::BioSource::getDisplayName() const
{
	return displayName;
}

std::string & UniPAX::BioSource::getDisplayName()
{
	return displayName;
}

void UniPAX::BioSource::setDisplayName(std::string _name)
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



bool UniPAX::BioSource::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	// specification gives it two names
	if (boost::iequals(attribute,"taxonXref") || boost::iequals(attribute,"xref") || boost::iequals(attribute,"taxon-xref"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "BioSource::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		xref.push_back(boost::dynamic_pointer_cast<UniPAX::Xref>(object));
		return true;
	}
	if (boost::iequals(attribute,"cellType"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "BioSource::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		cellType.push_back(boost::dynamic_pointer_cast<UniPAX::CellVocabulary>(object));
		return true;
	}
	if (boost::iequals(attribute,"tissue"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "BioSource::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		tissue = boost::dynamic_pointer_cast<UniPAX::TissueVocabulary>(object);
		return true;
	}
	if (boost::iequals(attribute,"name"))
	{
		addName(value);
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


bool UniPAX::BioSource::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

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
	tmp.clear();
	std::vector<boost::shared_ptr<UniPAX::CellVocabulary> >::iterator cit;
	for (cit = cellType.begin(); cit != cellType.end(); cit++)
	{
		if (*cit == 0)
		{
//			value.push_back(std::pair<std::string,std::string>("#xref", "NIL"));
		}
		else
		{
			tmp.clear();
			if (!manager.getId(*cit,tmp))
			{
				return false;
			}
			value.push_back(std::pair<std::string,std::string>("#cellType", tmp));

		}
	}
	tmp.clear();
	if (tissue == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#tissue", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(tissue,tmp))
		{
			std::cerr << "BioSource: tissue instance not found" << std::endl;
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#tissue", tmp));

	}

	/*if (!getNames().empty())
		value.push_back(std::pair<std::string,std::string>("name", getName()));*/
	std::vector<std::string>::iterator nit;
	for (nit = name.begin(); nit != name.end(); nit++)
        value.push_back(std::pair<std::string,std::string>("name", *nit));
	if (!getStandardName().empty())
		value.push_back(std::pair<std::string,std::string>("standardName", getStandardName()));
	if (!getDisplayName().empty())
		value.push_back(std::pair<std::string,std::string>("displayName", getDisplayName()));

	return true;

}


//void UniPAX::BioSource::init (odb::callback_event e, odb::database& db) const
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

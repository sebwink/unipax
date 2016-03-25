#include<UNIPAX/KERNEL/BIOPAX/Entity.h>
#include<set>
//Begin section for file Entity.cpp
//TODO: Add definitions that you want preserved
//End section for file Entity.cpp


UniPAX::Entity::Entity() : UniPAX::Thing()
//	evidence(0),
//	dataSource(0)
{
}

UniPAX::Entity::Entity(const Entity& arg) : UniPAX::Thing(arg) ,
		evidence(arg.evidence),
		dataSource(arg.dataSource),
		xref(arg.xref),
		availability(arg.availability),
		comments(arg.comments),
		name(arg.name),
		standardName(arg.standardName),
		displayName(arg.displayName)
//		id_xref(arg.id_xref)
{
}

UniPAX::Entity & UniPAX::Entity::operator =(const Entity & arg)  {
	UniPAX::Thing::operator=(arg);
	availability = arg.availability;
	comments = arg.comments;
	name = arg.name;
	standardName = arg.standardName;
	displayName = arg.displayName;
	evidence = arg.evidence;
	dataSource = arg.dataSource;
	xref = arg.xref;
//	id_xref = arg.id_xref;

	return *this;
}

UniPAX::Entity::~Entity()  {
}

bool UniPAX::Entity::merge(Entity& object)
{
	if (evidence != 0)
	{
		if (object.getEvidence() != 0)
		{
			if (evidence->getUnipaxId() != object.getEvidence()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::Entity::evidence not equal ..."
						<< evidence->getUnipaxId() << " != " << object.getEvidence()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setEvidence(object.getEvidence());
	}
	if (dataSource != 0)
	{
		if (object.getDataSource() != 0)
		{
			if (dataSource->getUnipaxId() != object.getDataSource()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::Entity::dataSource not equal ..."
						<< dataSource->getUnipaxId() << " != " << object.getDataSource()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setDataSource(object.getDataSource());
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
		std::set<std::string> tmp(getComments().begin(), getComments().end());
		for (std::vector<std::string>::iterator it = object.getComments().begin(); it != object.getComments().end(); it++)
		{
			tmp.insert(*it);
		}
		getComments().assign(tmp.begin(), tmp.end());
	}
	if (!object.getAvailability().empty())
		setAvailability(getAvailability() + "\n" + object.getAvailability());

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

	return UniPAX::Thing::merge(object);
}

bool UniPAX::Entity::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getEvidence()))
	{
		setEvidence(boost::dynamic_pointer_cast<Evidence>(manager.getMergedObject(getEvidence())));
	}
	if (manager.isMerged(getDataSource()))
	{
		setDataSource(boost::dynamic_pointer_cast<Provenance>(manager.getMergedObject(getDataSource())));
	}
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

	return UniPAX::Thing::update(manager);
}

const std::string& UniPAX::Entity::getAvailability() const {
	return availability;
}

std::string& UniPAX::Entity::getAvailability() {
	return availability;
}

void UniPAX::Entity::setAvailability(std::string _availability) {
	availability = _availability;
}

const std::vector<std::string> & UniPAX::Entity::getComments() const {
	return comments;
}

std::vector<std::string> & UniPAX::Entity::getComments() {
	return comments;
}

void UniPAX::Entity::setComments(std::vector<std::string> _comments) {
	comments = _comments;
}

void UniPAX::Entity::addComment(std::string _comment) {
	comments.push_back(_comment);
}

const boost::shared_ptr<UniPAX::Evidence> UniPAX::Entity::getEvidence() const {
	return evidence;
}

boost::shared_ptr<UniPAX::Evidence> UniPAX::Entity::getEvidence()  {
	return evidence;
}

void UniPAX::Entity::setEvidence(boost::shared_ptr<UniPAX::Evidence> _evidence) {
	evidence = _evidence;
}

const boost::shared_ptr<UniPAX::Provenance> UniPAX::Entity::getDataSource() const {
	return dataSource;
}

boost::shared_ptr<UniPAX::Provenance> UniPAX::Entity::getDataSource() {
	return dataSource;
}

void UniPAX::Entity::setDataSource(boost::shared_ptr<UniPAX::Provenance> _dataSource) {
	dataSource = _dataSource;
}

const std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::Entity::getXrefs() const {
	return xref;
}

std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::Entity::getXrefs() {
	return xref;
}

void UniPAX::Entity::addXref(boost::shared_ptr<UniPAX::Xref>  _xref) {
	xref.push_back(_xref);
}

void UniPAX::Entity::setXrefs(std::vector<boost::shared_ptr<Xref> > _xrefs) {
	xref = _xrefs;
}

std::vector<std::string> & UniPAX::Entity::getNames()  {
	return name;
}

const std::vector<std::string>& UniPAX::Entity::getNames() const {
	return name;
}

std::string UniPAX::Entity::getFirstName()  {
	if (!name.empty())
		return name[0];
	return "";
}

void UniPAX::Entity::setNames(std::vector<std::string>& _names)
{
	name = _names;
}

void UniPAX::Entity::addName(std::string _name)
{
	if (_name == "")
		return;

	std::vector<std::string>::iterator it;

	for (it = name.begin(); it != name.end(); it++)
	{
		if (_name == *it)
			return;
	}
	name.push_back(_name);
}





const std::string & UniPAX::Entity::getStandardName() const
{
	return standardName;
}

std::string & UniPAX::Entity::getStandardName()
{
	return standardName;
}

void UniPAX::Entity::setStandardName(std::string _name)
{
	standardName = _name;

	if (_name == "")
		return;

	std::vector<std::string>::iterator it;

	for (it = name.begin(); it != name.end(); it++)
	{
		if (_name == *it)
			return;
	}
	name.push_back(_name);
}

const std::string & UniPAX::Entity::getDisplayName() const
{
	return displayName;
}

std::string & UniPAX::Entity::getDisplayName()
{
	return displayName;
}

void UniPAX::Entity::setDisplayName(std::string _name)
{
	displayName = _name;

	if (_name == "")
		return;

	std::vector<std::string>::iterator it;

	for (it = name.begin(); it != name.end(); it++)
	{
		if (_name == *it)
			return;
	}
	name.push_back(_name);
}






//void UniPAX::Entity::setName(const std::vector<std::string>& name) {
//	name = _name;
//}

bool UniPAX::Entity::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Thing::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"evidence"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Entity::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		evidence = boost::dynamic_pointer_cast<UniPAX::Evidence>(object);
		return true;
	}

	if (boost::iequals(attribute,"dataSource"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Entity::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		dataSource = boost::dynamic_pointer_cast<UniPAX::Provenance>(object);
		return true;
	}

	if (boost::iequals(attribute,"Xref"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Entity::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		xref.push_back(boost::dynamic_pointer_cast<UniPAX::Xref>(object));
		return true;
	}
	if (boost::iequals(attribute,"comment"))
	{
		addComment(value);
		return true;
	}
	if (boost::iequals(attribute,"availability"))
	{
		setAvailability(value);
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

bool UniPAX::Entity::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Thing::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (evidence == 0)
	{
		//		value.push_back(std::pair<std::string,std::string>("#evidence", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(evidence,tmp))
		{
			manager.setError(this->type() + ":evidence contains unknown reference.");
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#evidence", tmp));

	}
	tmp.clear();
	if (dataSource == 0)
	{
		//		value.push_back(std::pair<std::string,std::string>("#dataSource", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(dataSource,tmp))
		{
			manager.setError(this->type() + ":dataSource contains unknown reference.");
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#dataSource", tmp));

	}
	tmp.clear();
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
				manager.setError(this->type() + ":xrefs contains unknown reference.");
				return false;
			}
			value.push_back(std::pair<std::string,std::string>("#xref", tmp));

		}
	}

	{
		std::vector<std::string>::iterator it;
		for (it = comments.begin(); it != comments.end(); it++)
			value.push_back(std::pair<std::string,std::string>("comment", *it));
	}

	if (!getAvailability().empty())
		value.push_back(std::pair<std::string,std::string>("availability", getAvailability()));


	std::vector<std::string>::iterator nit;
	for (nit = name.begin(); nit != name.end(); nit++)
		value.push_back(std::pair<std::string,std::string>("name", *nit));
	if (!getStandardName().empty())
		value.push_back(std::pair<std::string,std::string>("standardName", getStandardName()));
	if (!getDisplayName().empty())
		value.push_back(std::pair<std::string,std::string>("displayName", getDisplayName()));

	return true;

}

//void UniPAX::Entity::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Thing::init(e,db);
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
//			{
//				id_xref.push_back((*it)->getUnipaxId());
//			}
//		}
//
//	}
//
//	return;
//}


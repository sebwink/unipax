#include<UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include<set>
//Begin section for file EntityReference.cpp
//TODO: Add definitions that you want preserved
//End section for file EntityReference.cpp


UniPAX::EntityReference::EntityReference() : UniPAX::UtilityClass()
//id_memberEntityReferences(), id_entityFeature(0)
{
}

UniPAX::EntityReference::EntityReference(const EntityReference& arg) : UniPAX::UtilityClass(arg) ,
		standardName(arg.standardName),
		displayName(arg.displayName),
		name(arg.name),
		memberEntityReferences(arg.memberEntityReferences),
		evidence(arg.evidence),
		entityReferenceType(arg.entityReferenceType),
		entityFeature(arg.entityFeature),
		xref(arg.xref)
//		id_memberEntityReferences(arg.id_memberEntityReferences),
//		id_entityFeature(arg.id_entityFeature),
//		id_xref(arg.id_xref)
{
}

UniPAX::EntityReference & UniPAX::EntityReference::operator =(const EntityReference & arg)  {
	UniPAX::UtilityClass::operator=(arg);
	memberEntityReferences = arg.memberEntityReferences;
	evidence = arg.evidence;
	entityReferenceType = arg.entityReferenceType;
	entityFeature = arg.entityFeature;
	xref = arg.xref;
	standardName = arg.standardName;
	displayName = arg.displayName;
	name = arg.name;
//	id_memberEntityReferences = arg.id_memberEntityReferences;
//	id_entityFeature = arg.id_entityFeature;
//	id_xref = arg.id_xref;

	return *this;
}

UniPAX::EntityReference::~EntityReference()  {
}

bool UniPAX::EntityReference::merge(EntityReference& object)
{
	{
		std::set<UniPAX::EntityReferencePtr> tmp(getMemberEntityReferences().begin(), getMemberEntityReferences().end());
		for (std::vector<UniPAX::EntityReferencePtr>::iterator it = object.getMemberEntityReferences().begin(); it != object.getMemberEntityReferences().end(); it++)
		{
			if (*it)
			{
				tmp.insert(*it);
			}
		}
		getMemberEntityReferences().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::EvidencePtr> tmp(getEvidences().begin(), getEvidences().end());
		for (std::vector<UniPAX::EvidencePtr>::iterator it = object.getEvidences().begin(); it != object.getEvidences().end(); it++)
		{
			if (*it)
			{
				tmp.insert(*it);
			}
		}
		getEvidences().assign(tmp.begin(), tmp.end());
	}
	if (entityReferenceType)
	{
		if (entityReferenceType->getUnipaxId() != object.getEntityReferenceType()->getUnipaxId())
		{
			std::cerr << "Error during merging: UniPAX::EntityReference::entityReferenceType not equal ..."
					<< entityReferenceType->getUnipaxId() << " != " << object.getEntityReferenceType()->getUnipaxId() << std::endl;
			return false;
		}

	}
	else
	{
		setEntityReferenceType(object.getEntityReferenceType());
	}

	if (entityFeature)
	{
		if (entityFeature->getUnipaxId() != object.getEntityFeature()->getUnipaxId())
		{
			std::cerr << "Error during merging: UniPAX::EntityReference::entityFeature not equal ..."
					<< entityFeature->getUnipaxId() << " != " << object.getEntityFeature()->getUnipaxId() << std::endl;
			return false;
		}
	}
	else
	{
		setEntityFeature(object.getEntityFeature());
	}
	{
		std::set<UniPAX::XrefPtr> tmp(xref.begin(), xref.end());
		for (std::vector<UniPAX::XrefPtr>::iterator it = object.getXrefs().begin(); it != object.getXrefs().end(); it++)
		{
			if (*it)
			{
				tmp.insert(*it);
			}
		}
		xref.assign(tmp.begin(), tmp.end());
	}
	{
		std::set<std::string> tmp(name.begin(), name.end());
		for (std::vector<std::string>::iterator it = object.getNames().begin(); it != object.getNames().end(); it++)
		{
			tmp.insert(*it);
		}
		if (!object.getStandardName().empty())
			tmp.insert(object.getStandardName());
		if (!object.getDisplayName().empty())
			tmp.insert(object.getDisplayName());
		name.assign(tmp.begin(), tmp.end());
	}

	return UniPAX::UtilityClass::merge(object);
}



bool UniPAX::EntityReference::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getEntityFeature()))
	{
		setEntityFeature(boost::dynamic_pointer_cast<EntityFeature>(manager.getMergedObject(getEntityFeature())));
	}

	{
		std::vector<boost::shared_ptr<UniPAX::EntityReference> > tmp_vec;
		for (std::vector<boost::shared_ptr<UniPAX::EntityReference> >::iterator it = memberEntityReferences.begin(); it != memberEntityReferences.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<EntityReference>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setMemberEntityReferences(tmp_vec);
	}


	if (manager.isMerged(getEntityReferenceType()))
	{
		setEntityReferenceType(boost::dynamic_pointer_cast<EntityReferenceTypeVocabulary>(manager.getMergedObject(getEntityReferenceType())));
	}
	{
		std::vector<boost::shared_ptr<UniPAX::Evidence> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Evidence> >::iterator it;
		for (it = evidence.begin(); it != evidence.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Evidence>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setEvidences(tmp_vec);
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

	return UniPAX::UtilityClass::update(manager);
}


const std::vector<boost::shared_ptr<UniPAX::EntityReference> > UniPAX::EntityReference::getMemberEntityReferences() const {
	return memberEntityReferences;
}

std::vector<boost::shared_ptr<UniPAX::EntityReference> > UniPAX::EntityReference::getMemberEntityReferences() {
	return memberEntityReferences;
}

void UniPAX::EntityReference::setMemberEntityReferences(std::vector<boost::shared_ptr<UniPAX::EntityReference> > _memberEntityReferences) {
	memberEntityReferences = _memberEntityReferences;
}

void UniPAX::EntityReference::addMemberEntityReference(boost::shared_ptr<UniPAX::EntityReference> _memberEntityReference) {
	memberEntityReferences.push_back(_memberEntityReference);
}


const std::vector<boost::shared_ptr<UniPAX::Evidence> > & UniPAX::EntityReference::getEvidences() const {
	return evidence;
}

std::vector<boost::shared_ptr<UniPAX::Evidence> > & UniPAX::EntityReference::getEvidences()  {
	return evidence;
}


void UniPAX::EntityReference::setEvidences(std::vector<boost::shared_ptr<UniPAX::Evidence> > _evidences)  {
	evidence = _evidences;
}

void UniPAX::EntityReference::addEvidence(boost::shared_ptr<UniPAX::Evidence>  _evidence) {
	evidence.push_back(_evidence);
}

const boost::shared_ptr<UniPAX::EntityReferenceTypeVocabulary> UniPAX::EntityReference::getEntityReferenceType() const {
	return entityReferenceType;
}

boost::shared_ptr<UniPAX::EntityReferenceTypeVocabulary> UniPAX::EntityReference::getEntityReferenceType() {
	return entityReferenceType;
}

void UniPAX::EntityReference::setEntityReferenceType(boost::shared_ptr<UniPAX::EntityReferenceTypeVocabulary> _entityReferenceType) {
	entityReferenceType = _entityReferenceType;
}

const boost::shared_ptr<UniPAX::EntityFeature> UniPAX::EntityReference::getEntityFeature() const {
	return entityFeature;
}

boost::shared_ptr<UniPAX::EntityFeature> UniPAX::EntityReference::getEntityFeature() {
	return entityFeature;
}

void UniPAX::EntityReference::setEntityFeature(boost::shared_ptr<UniPAX::EntityFeature> _entityFeature) {
	entityFeature = _entityFeature;
}

const std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::EntityReference::getXrefs() const {
	return xref;
}

std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::EntityReference::getXrefs() {
	return xref;
}

void UniPAX::EntityReference::addXref(boost::shared_ptr<UniPAX::Xref>  _xref) {
	xref.push_back(_xref);
}

void UniPAX::EntityReference::setXrefs(std::vector<boost::shared_ptr<Xref> > _xrefs) {
	xref = _xrefs;
}



std::vector<std::string> & UniPAX::EntityReference::getNames()
{
	return name;
}

const std::vector<std::string>& UniPAX::EntityReference::getNames() const
{
	return name;
}

std::string UniPAX::EntityReference::getFirstName()
{
	if (!name.empty())
		return name[0];
	return "";
}

void UniPAX::EntityReference::setNames(std::vector<std::string>& _names)
{
	name = _names;
}

void UniPAX::EntityReference::addName(std::string _name)
{
	if (_name == "")
		return;

	name.push_back(_name);
}

const std::string & UniPAX::EntityReference::getStandardName() const
{
	return standardName;
}

std::string & UniPAX::EntityReference::getStandardName()
{
	return standardName;
}

void UniPAX::EntityReference::setStandardName(std::string _name)
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

const std::string & UniPAX::EntityReference::getDisplayName() const
{
	return displayName;
}

std::string & UniPAX::EntityReference::getDisplayName()
{
	return displayName;
}

void UniPAX::EntityReference::setDisplayName(std::string _name)
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


bool UniPAX::EntityReference::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"memberEntityReference"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		memberEntityReferences.push_back(boost::dynamic_pointer_cast<UniPAX::EntityReference>(object));
		return true;
	}

	if (boost::iequals(attribute,"evidence"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		evidence.push_back(boost::dynamic_pointer_cast<UniPAX::Evidence>(object));
		return true;
	}

	if (boost::iequals(attribute,"entityReferenceType"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		entityReferenceType = boost::dynamic_pointer_cast<UniPAX::EntityReferenceTypeVocabulary>(object);
		return true;
	}

	if (boost::iequals(attribute,"entityFeature"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		entityFeature = boost::dynamic_pointer_cast<UniPAX::EntityFeature>(object);
		return true;
	}

	if (boost::iequals(attribute,"Xref"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (!object)
		{
			std::cerr << "EntityReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		xref.push_back(boost::dynamic_pointer_cast<UniPAX::Xref>(object));
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

bool UniPAX::EntityReference::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::EntityReference> >::iterator it;
		for (it = memberEntityReferences.begin(); it != memberEntityReferences.end(); it++)
		{
			if (!*it)
			{
				//		value.push_back(std::pair<std::string,std::string>("#memberEntityReference", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#memberEntityReference", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::Evidence> >::iterator it;
		for (it = evidence.begin(); it != evidence.end(); it++)
		{
			if (!*it)
			{
				//				value.push_back(std::pair<std::string,std::string>("#entityReference", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#evidence", tmp));

			}
		}
	}
	tmp.clear();
	if (!entityReferenceType)
	{
		//		value.push_back(std::pair<std::string,std::string>("#entityReferenceType", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(entityReferenceType,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#entityReferenceType", tmp));

	}
	tmp.clear();
	if (!entityFeature)
	{
		//		value.push_back(std::pair<std::string,std::string>("#entityFeature", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(entityFeature,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#entityFeature", tmp));

	}
	tmp.clear();

	{
		std::vector<boost::shared_ptr<UniPAX::Xref> >::iterator it;
		for (it = xref.begin(); it != xref.end(); it++)
		{
			if (!*it)
			{
				//				value.push_back(std::pair<std::string,std::string>("#xref", "NIL"));
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

//void UniPAX::EntityReference::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		memberEntityReferences.clear();
//		for (std::vector<unsigned long long>::iterator it = id_memberEntityReferences.begin(); it != id_memberEntityReferences.end(); it++)
//		{
//			memberEntityReferences.push_back(boost::dynamic_pointer_cast<EntityReference>(getObjectByID(db, *it)));
//		}
//
//
//		entityFeature = boost::dynamic_pointer_cast<UniPAX::EntityFeature>(getObjectByID(db, id_entityFeature));
//
//		// load the object pointer
//		xref.clear();
//		for (std::vector<unsigned long long>::iterator it = id_xref.begin(); it != id_xref.end(); it++)
//		{
//			xref.push_back(boost::dynamic_pointer_cast<UniPAX::Xref>(getObjectByID(db, *it)));
//		}
//
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		id_memberEntityReferences.clear();
//		for (std::vector<boost::shared_ptr<EntityReference> >::iterator it = memberEntityReferences.begin(); it != memberEntityReferences.end(); it++)
//		{
//			if (*it)
//				id_memberEntityReferences.push_back((*it)->getUnipaxId());
//		}
//
//
//		if (entityFeature)
//			id_entityFeature = entityFeature->getUnipaxId();
//
//		// set the object ids
//		id_xref.clear();
//		for (std::vector<boost::shared_ptr<Xref> >::iterator it = xref.begin(); it != xref.end(); it++)
//		{
//			if (*it)
//				id_xref.push_back((*it)->getUnipaxId());
//		}
//
//	}
//
//	return;
//}


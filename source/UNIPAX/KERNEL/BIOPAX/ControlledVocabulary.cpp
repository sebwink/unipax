#include<UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include<set>
//Begin section for file ControlledVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file ControlledVocabulary.cpp

UniPAX::ControlledVocabulary::ControlledVocabulary() : UniPAX::UtilityClass() {
    }

UniPAX::ControlledVocabulary::ControlledVocabulary(const ControlledVocabulary& arg) : UniPAX::UtilityClass(arg) ,
	term(arg.term),
	xref(arg.xref)
//	id_xref(arg.id_xref)
{
    }

UniPAX::ControlledVocabulary & UniPAX::ControlledVocabulary::operator =(const ControlledVocabulary & arg)
{
	UniPAX::UtilityClass::operator=(arg);
	term = arg.term;
	xref = arg.xref;
//	id_xref = arg.id_xref;

	return *this;
}

UniPAX::ControlledVocabulary::~ControlledVocabulary()  {
    }

bool UniPAX::ControlledVocabulary::merge(ControlledVocabulary& object)
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
	if (!object.getTerm().empty())
	{
		if (!getTerm().empty())
		{
			if (getTerm() != object.getTerm())
			{
				std::cerr << "Error during merging: UniPAX::ControlledVocabulary::term not equal ..."
						<< getTerm() << " != " << object.getTerm() << std::endl;
				return false;
			}
		}
		else
			setTerm(object.getTerm());
	}

	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::ControlledVocabulary::update(PersistenceManager& manager)
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


const std::string & UniPAX::ControlledVocabulary::getTerm() const {
        return term;
}

std::string & UniPAX::ControlledVocabulary::getTerm() {
	return term;
}

void UniPAX::ControlledVocabulary::setTerm(std::string _term) {
	term = _term;
}


const std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::ControlledVocabulary::getXrefs() const {
        return xref;
}

std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::ControlledVocabulary::getXrefs() {
	return xref;
}

void UniPAX::ControlledVocabulary::setXrefs(std::vector<boost::shared_ptr<UniPAX::Xref> > _xrefs) {
	xref = _xrefs;
}

void UniPAX::ControlledVocabulary::addXref(boost::shared_ptr<UniPAX::Xref>  _xref) {
	xref.push_back(_xref);
}


bool UniPAX::ControlledVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

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
			std::cerr << "Entity::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		xref.push_back(boost::dynamic_pointer_cast<UniPAX::Xref>(object));
		return true;
	}
	if (boost::iequals(attribute,"term"))
	{
		setTerm(value);
		return true;
	}

	return false;

}


bool UniPAX::ControlledVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

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
	if (!getTerm().empty())
		value.push_back(std::pair<std::string,std::string>("term", getTerm()));

	return true;

}

//void UniPAX::ControlledVocabulary::init (odb::callback_event e, odb::database& db) const
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

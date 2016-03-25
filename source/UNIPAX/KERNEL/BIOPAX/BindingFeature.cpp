#include<UNIPAX/KERNEL/BIOPAX/BindingFeature.h>
#include<set>

UniPAX::BindingFeature::BindingFeature() : UniPAX::EntityFeature(),
		intraMolecular(false)
{
}

UniPAX::BindingFeature::BindingFeature(const BindingFeature & arg)  : UniPAX::EntityFeature(arg),
		intraMolecular(arg.intraMolecular),
		bindsTo(arg.bindsTo)
//		id_bindsTo(arg.id_bindsTo)
{
}

UniPAX::BindingFeature & UniPAX::BindingFeature::operator =(const UniPAX::BindingFeature & arg)  {

	UniPAX::EntityFeature::operator=(arg);

	intraMolecular = arg.intraMolecular;
	bindsTo = arg.bindsTo;
//	id_bindsTo = arg.id_bindsTo;

	return *this;
}

UniPAX::BindingFeature::~BindingFeature()  {
}


bool UniPAX::BindingFeature::merge(BindingFeature& object)
{
	{
		std::set<UniPAX::BindingFeaturePtr> tmp(getBindsTos().begin(), getBindsTos().end());
		for (std::vector<UniPAX::BindingFeaturePtr>::iterator it = object.getBindsTos().begin(); it != object.getBindsTos().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getBindsTos().assign(tmp.begin(), tmp.end());
	}

	if (getIntraMolecular() != object.getIntraMolecular())
	{
		std::cerr << "Error during merging: UniPAX::ChemicalStructure::structureData not equal ..."
				<< getIntraMolecular() << " != " << object.getIntraMolecular() << std::endl;
		return false;
	}

	return UniPAX::EntityFeature::merge(object);
}


bool UniPAX::BindingFeature::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::BindingFeature> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::BindingFeature> >::iterator it;
		for (it = bindsTo.begin(); it != bindsTo.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<BindingFeature>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setBindsTos(tmp_vec);
	}

	return UniPAX::EntityFeature::update(manager);
}


bool UniPAX::BindingFeature::getIntraMolecular()  {
	return intraMolecular;
}

const bool UniPAX::BindingFeature::getIntraMolecular() const {
	return intraMolecular;
}

void UniPAX::BindingFeature::setIntraMolecular(bool _intraMolecular)  {
	intraMolecular = _intraMolecular;
}


const std::vector<boost::shared_ptr<UniPAX::BindingFeature> > & UniPAX::BindingFeature::getBindsTos() const {
	return bindsTo;
}

std::vector<boost::shared_ptr<UniPAX::BindingFeature> > UniPAX::BindingFeature::getBindsTos() {
	return bindsTo;
}

void UniPAX::BindingFeature::setBindsTos(std::vector<boost::shared_ptr<UniPAX::BindingFeature> > _bindsTos) {
	bindsTo = _bindsTos;
}


void UniPAX::BindingFeature::addBindsTo(boost::shared_ptr<UniPAX::BindingFeature> _bindsTo) {
	bindsTo.push_back(_bindsTo);
}


bool UniPAX::BindingFeature::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::EntityFeature::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"bindsTo"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "BindingFeature::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		bindsTo.push_back(boost::dynamic_pointer_cast<UniPAX::BindingFeature>(object));
		return true;
	}
	if (boost::iequals(attribute,"intraMolecular"))
	{
		return (PersistenceManager::convertAttribute(value,intraMolecular));
	}

	return false;

}


bool UniPAX::BindingFeature::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::EntityFeature::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::BindingFeature> >::iterator it;
		for (it = bindsTo.begin(); it != bindsTo.end(); it++)
		{
			if (*it == 0)
			{
				//			value.push_back(std::pair<std::string,std::string>("#bindsTo", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#bindsTo", tmp));

			}
		}
	}
	tmp.clear();
	if (!PersistenceManager::convertAttribute(intraMolecular, tmp))
	{
		return false;
	}
	value.push_back(std::pair<std::string,std::string>("intraMolecular", tmp));

	return true;

}


//void UniPAX::BindingFeature::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::EntityFeature::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		bindsTo.clear();
//		std::vector<unsigned long long>::iterator it;
//		for (it = id_bindsTo.begin(); it != id_bindsTo.end(); it++)
//		{
//			bindsTo.push_back(boost::dynamic_pointer_cast<UniPAX::BindingFeature>(getObjectByID(db, *it)));
//		}
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		id_bindsTo.clear();
//		std::vector<boost::shared_ptr<UniPAX::BindingFeature> >::iterator it;
//		for (it = bindsTo.begin(); it != bindsTo.end(); it++)
//		{
//			if (*it)
//				id_bindsTo.push_back((*it)->getUnipaxId());
//		}
//
//	}
//}

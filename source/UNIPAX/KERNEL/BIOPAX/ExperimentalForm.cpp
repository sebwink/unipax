#include<UNIPAX/KERNEL/BIOPAX/ExperimentalForm.h>
#include<set>
//Begin section for file ExperimentalForm.cpp
//TODO: Add definitions that you want preserved
//End section for file ExperimentalForm.cpp

UniPAX::ExperimentalForm::ExperimentalForm() : UniPAX::UtilityClass()
//	experimentalFeature(0),
//	experimentalFormEntity(0),
//	experimentalFormDescription(0)
{
    }

UniPAX::ExperimentalForm::ExperimentalForm(const ExperimentalForm& arg) : UniPAX::UtilityClass(arg) ,
	experimentalFormEntity(arg.experimentalFormEntity),
	experimentalFeature(arg.experimentalFeature),
	experimentalFormDescription(arg.experimentalFormDescription)
//	id_experimentalFormEntity(arg.id_experimentalFormEntity),
//	id_experimentalFeature(arg.id_experimentalFeature)
{
    }

UniPAX::ExperimentalForm & UniPAX::ExperimentalForm::operator =(const ExperimentalForm & arg) {
	UniPAX::UtilityClass::operator=(arg);
	experimentalFormEntity = arg.experimentalFormEntity;
	experimentalFeature = arg.experimentalFeature;
	experimentalFormDescription = arg.experimentalFormDescription;
//	id_experimentalFormEntity = arg.id_experimentalFormEntity;
//	id_experimentalFeature = arg.id_experimentalFeature;

	return *this;
}

UniPAX::ExperimentalForm::~ExperimentalForm()  {
    }

bool UniPAX::ExperimentalForm::merge(ExperimentalForm& object)
{
	{
		std::set<UniPAX::ExperimentalFormVocabularyPtr> tmp(getExperimentalFormDescriptions().begin(), getExperimentalFormDescriptions().end());
		for (std::vector<UniPAX::ExperimentalFormVocabularyPtr>::iterator it = object.getExperimentalFormDescriptions().begin(); it != object.getExperimentalFormDescriptions().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getExperimentalFormDescriptions().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::EntityFeaturePtr> tmp(getExperimentalFeatures().begin(), getExperimentalFeatures().end());
		for (std::vector<UniPAX::EntityFeaturePtr>::iterator it = object.getExperimentalFeatures().begin(); it != object.getExperimentalFeatures().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getExperimentalFeatures().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::EntityPtr> tmp(getExperimentalFormEntitys().begin(), getExperimentalFormEntitys().end());
		for (std::vector<UniPAX::EntityPtr>::iterator it = object.getExperimentalFormEntitys().begin(); it != object.getExperimentalFormEntitys().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getExperimentalFormEntitys().assign(tmp.begin(), tmp.end());
	}
	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::ExperimentalForm::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::ExperimentalFormVocabulary> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::ExperimentalFormVocabulary> >::iterator it;
		for (it = experimentalFormDescription.begin(); it != experimentalFormDescription.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<ExperimentalFormVocabulary>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setExperimentalFormDescriptions(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> >::iterator it;
		for (it = experimentalFeature.begin(); it != experimentalFeature.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<EntityFeature>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setExperimentalFeatures(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::Entity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
		for (it = experimentalFormEntity.begin(); it != experimentalFormEntity.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Entity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setExperimentalFormEntitys(tmp_vec);
	}

	return UniPAX::UtilityClass::update(manager);
}


const std::vector<boost::shared_ptr<UniPAX::EntityFeature> > & UniPAX::ExperimentalForm::getExperimentalFeatures() const {
        return experimentalFeature;
}

std::vector<boost::shared_ptr<UniPAX::EntityFeature> > & UniPAX::ExperimentalForm::getExperimentalFeatures() {
	return experimentalFeature;
}

void UniPAX::ExperimentalForm::setExperimentalFeatures(std::vector<boost::shared_ptr<UniPAX::EntityFeature> > _experimentalFeatures) {
	experimentalFeature = _experimentalFeatures;
}

void UniPAX::ExperimentalForm::addExperimentalFeature(boost::shared_ptr<UniPAX::EntityFeature>  _experimentalFeature) {
	experimentalFeature.push_back(_experimentalFeature);
}


const std::vector<boost::shared_ptr<UniPAX::ExperimentalFormVocabulary> > & UniPAX::ExperimentalForm::getExperimentalFormDescriptions() const {
        return experimentalFormDescription;
}

std::vector<boost::shared_ptr<UniPAX::ExperimentalFormVocabulary> > & UniPAX::ExperimentalForm::getExperimentalFormDescriptions() {
	return experimentalFormDescription;
}

void UniPAX::ExperimentalForm::setExperimentalFormDescriptions(std::vector<boost::shared_ptr<UniPAX::ExperimentalFormVocabulary> > _experimentalFormDescriptions) {
	experimentalFormDescription = _experimentalFormDescriptions;
}

void UniPAX::ExperimentalForm::addExperimentalFormDescription(boost::shared_ptr<UniPAX::ExperimentalFormVocabulary>  _experimentalFormDescription) {
	experimentalFormDescription.push_back(_experimentalFormDescription);
}


std::vector<boost::shared_ptr<UniPAX::Entity> > & UniPAX::ExperimentalForm::getExperimentalFormEntitys()  {
        return experimentalFormEntity;
}

const std::vector<boost::shared_ptr<UniPAX::Entity> > & UniPAX::ExperimentalForm::getExperimentalFormEntitys() const {
	return experimentalFormEntity;
}

void UniPAX::ExperimentalForm::setExperimentalFormEntitys(std::vector<boost::shared_ptr<UniPAX::Entity> > _experimentalFormEntitys)  {
    	experimentalFormEntity = _experimentalFormEntitys;
}

void UniPAX::ExperimentalForm::addExperimentalFormEntity(boost::shared_ptr<UniPAX::Entity>  _experimentalFormEntity) {
	experimentalFormEntity.push_back(_experimentalFormEntity);
}


bool UniPAX::ExperimentalForm::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"experimentalFormDescription"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "ExperimentalForm::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		experimentalFormDescription.push_back(boost::dynamic_pointer_cast<UniPAX::ExperimentalFormVocabulary>(object));
		return true;
	}

	if (boost::iequals(attribute,"experimentalFeature"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "ExperimentalForm::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		experimentalFeature.push_back(boost::dynamic_pointer_cast<UniPAX::EntityFeature>(object));
		return true;
	}

	if (boost::iequals(attribute,"experimentalFormEntity"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "ExperimentalForm::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		experimentalFormEntity.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(object));
		return true;
	}

	return false;

}

bool UniPAX::ExperimentalForm::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::ExperimentalFormVocabulary> >::iterator it;
		for (it = experimentalFormDescription.begin(); it != experimentalFormDescription.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#experimentalFormDescription", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#experimentalFormDescription", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::EntityFeature> >::iterator it;
		for (it = experimentalFeature.begin(); it != experimentalFeature.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#experimentalFeature", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#experimentalFeature", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
		for (it = experimentalFormEntity.begin(); it != experimentalFormEntity.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#experimentalFormEntity", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#experimentalFormEntity", tmp));

			}
		}
	}
	tmp.clear();

	return true;

}

//void UniPAX::ExperimentalForm::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		{
//			experimentalFormEntity.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_experimentalFormEntity.begin(); it != id_experimentalFormEntity.end(); it++)
//			{
//				experimentalFormEntity.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(getObjectByID(db, *it)));
//			}
//		}
//		{
//			experimentalFeature.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_experimentalFeature.begin(); it != id_experimentalFeature.end(); it++)
//			{
//				experimentalFeature.push_back(boost::dynamic_pointer_cast<UniPAX::EntityFeature>(getObjectByID(db, *it)));
//			}
//		}
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		{
//			id_experimentalFormEntity.clear();
//			std::vector<boost::shared_ptr<Entity> >::iterator it;
//			for (it = experimentalFormEntity.begin(); it != experimentalFormEntity.end(); it++)
//			{
//				if (*it != 0)
//					id_experimentalFormEntity.push_back((*it)->getUnipaxId());
//			}
//		}
//		{
//			id_experimentalFeature.clear();
//			std::vector<boost::shared_ptr<EntityFeature> >::iterator it;
//			for (it = experimentalFeature.begin(); it != experimentalFeature.end(); it++)
//			{
//				if (*it != 0)
//					id_experimentalFeature.push_back((*it)->getUnipaxId());
//			}
//		}
//	}
//
//	return;
//}

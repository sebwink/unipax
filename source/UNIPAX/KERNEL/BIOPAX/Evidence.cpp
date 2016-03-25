#include<UNIPAX/KERNEL/BIOPAX/Evidence.h>
#include<set>
//Begin section for file Evidence.cpp
//TODO: Add definitions that you want preserved
//End section for file Evidence.cpp


UniPAX::Evidence::Evidence() : UniPAX::UtilityClass()
//		, evidenceCode(0),
//		experimentalForm(0),
//		confidence(0)
{
    }

UniPAX::Evidence::Evidence(const Evidence& arg) : UniPAX::UtilityClass(arg) ,
	evidenceCode(arg.evidenceCode),
	experimentalForm(arg.experimentalForm),
	confidence(arg.confidence),
	xref(arg.xref)
//	id_xref(arg.id_xref)
{
    }

UniPAX::Evidence & UniPAX::Evidence::operator =(const Evidence & arg)  {
	UniPAX::UtilityClass::operator=(arg);
	evidenceCode = arg.evidenceCode;
	experimentalForm = arg.experimentalForm;
	confidence = arg.confidence;
	xref = arg.xref;
//	id_xref = arg.id_xref;

	return *this;
}

UniPAX::Evidence::~Evidence()  {
    }

bool UniPAX::Evidence::merge(Evidence& object)
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
		std::set<UniPAX::ScorePtr> tmp(getConfidences().begin(), getConfidences().end());
		for (std::vector<UniPAX::ScorePtr>::iterator it = object.getConfidences().begin(); it != object.getConfidences().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getConfidences().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::ExperimentalFormPtr> tmp(getExperimentalForms().begin(), getExperimentalForms().end());
		for (std::vector<UniPAX::ExperimentalFormPtr>::iterator it = object.getExperimentalForms().begin(); it != object.getExperimentalForms().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getExperimentalForms().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::EvidenceCodeVocabularyPtr> tmp(getEvidenceCodes().begin(), getEvidenceCodes().end());
		for (std::vector<UniPAX::EvidenceCodeVocabularyPtr>::iterator it = object.getEvidenceCodes().begin(); it != object.getEvidenceCodes().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getEvidenceCodes().assign(tmp.begin(), tmp.end());
	}

	return UniPAX::UtilityClass::merge(object);
}


bool UniPAX::Evidence::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::EvidenceCodeVocabulary> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::EvidenceCodeVocabulary> >::iterator it;
		for (it = evidenceCode.begin(); it != evidenceCode.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<EvidenceCodeVocabulary>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setEvidenceCodes(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::ExperimentalForm> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::ExperimentalForm> >::iterator it;
		for (it = experimentalForm.begin(); it != experimentalForm.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<ExperimentalForm>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setExperimentalForms(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::Score> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Score> >::iterator it;
		for (it = confidence.begin(); it != confidence.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Score>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setConfidences(tmp_vec);
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

const std::vector<boost::shared_ptr<UniPAX::EvidenceCodeVocabulary> > & UniPAX::Evidence::getEvidenceCodes() const {
        return evidenceCode;
}

std::vector<boost::shared_ptr<UniPAX::EvidenceCodeVocabulary> > & UniPAX::Evidence::getEvidenceCodes() {
	return evidenceCode;
}

void UniPAX::Evidence::setEvidenceCodes(std::vector<boost::shared_ptr<UniPAX::EvidenceCodeVocabulary> > _evidenceCodes) {
	evidenceCode = _evidenceCodes;
}

void UniPAX::Evidence::addEvidenceCode(boost::shared_ptr<UniPAX::EvidenceCodeVocabulary>  _evidenceCode) {
	evidenceCode.push_back(_evidenceCode);
}


const std::vector<boost::shared_ptr<UniPAX::ExperimentalForm> > & UniPAX::Evidence::getExperimentalForms() const {
        return experimentalForm;
}

std::vector<boost::shared_ptr<UniPAX::ExperimentalForm> > & UniPAX::Evidence::getExperimentalForms() {
	return experimentalForm;
}

void UniPAX::Evidence::setExperimentalForms(std::vector<boost::shared_ptr<UniPAX::ExperimentalForm> > _experimentalForms) {
	experimentalForm = _experimentalForms;
}

void UniPAX::Evidence::addExperimentalForm(boost::shared_ptr<UniPAX::ExperimentalForm>  _experimentalForm) {
	experimentalForm.push_back(_experimentalForm);
}


const std::vector<boost::shared_ptr<UniPAX::Score> > & UniPAX::Evidence::getConfidences() const {
        return confidence;
}

std::vector<boost::shared_ptr<UniPAX::Score> > & UniPAX::Evidence::getConfidences() {
	return confidence;
}

void UniPAX::Evidence::setConfidences(std::vector<boost::shared_ptr<UniPAX::Score> > _confidences) {
	confidence = _confidences;
}

void  UniPAX::Evidence::addConfidence(boost::shared_ptr<UniPAX::Score>  _confidence) {
	confidence.push_back(_confidence);
}


const std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::Evidence::getXrefs() const {
    return xref;
}

std::vector<boost::shared_ptr<UniPAX::Xref> > & UniPAX::Evidence::getXrefs() {
	return xref;
}

void UniPAX::Evidence::addXref(boost::shared_ptr<UniPAX::Xref>  _xref) {
	xref.push_back(_xref);
}

void UniPAX::Evidence::setXrefs(std::vector<boost::shared_ptr<Xref> > _xrefs) {
	xref = _xrefs;
}

bool UniPAX::Evidence::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

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
			std::cerr << "Evidence::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		xref.push_back(boost::dynamic_pointer_cast<UniPAX::Xref>(object));
		return true;
	}

	if (boost::iequals(attribute,"confidence"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Evidence::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		confidence.push_back(boost::dynamic_pointer_cast<UniPAX::Score>(object));
		return true;
	}

	if (boost::iequals(attribute,"experimentalForm"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Evidence::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		experimentalForm.push_back(boost::dynamic_pointer_cast<UniPAX::ExperimentalForm>(object));
		return true;
	}

	if (boost::iequals(attribute,"evidenceCode"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Evidence::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		evidenceCode.push_back(boost::dynamic_pointer_cast<UniPAX::EvidenceCodeVocabulary>(object));
		return true;
	}


	return false;

}

bool UniPAX::Evidence::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::Xref> >::iterator it;
		for (it = xref.begin(); it != xref.end(); it++)
		{
			if (*it == 0)
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
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::Score> >::iterator it;
		for (it = confidence.begin(); it != confidence.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#confidence", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#confidence", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::ExperimentalForm> >::iterator it;
		for (it = experimentalForm.begin(); it != experimentalForm.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#experimentalForm", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#experimentalForm", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::EvidenceCodeVocabulary> >::iterator it;
		for (it = evidenceCode.begin(); it != evidenceCode.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#evidenceCode", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#evidenceCode", tmp));

			}
		}
	}

	return true;

}

//void UniPAX::Evidence::init (odb::callback_event e, odb::database& db) const
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

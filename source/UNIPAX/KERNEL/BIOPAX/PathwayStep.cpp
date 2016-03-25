#include<UNIPAX/KERNEL/BIOPAX/PathwayStep.h>
#include<set>
//Begin section for file PathwayStep.cpp
//TODO: Add definitions that you want preserved
//End section for file PathwayStep.cpp


UniPAX::PathwayStep::PathwayStep() :
UniPAX::UtilityClass()
//, stepProcess(0)
//, evidence(0)
//, nextStep(0)
{
    }

UniPAX::PathwayStep::PathwayStep(const PathwayStep& arg) : UniPAX::UtilityClass(arg) ,
	stepProcess(arg.stepProcess),
	evidence(arg.evidence),
	nextStep(arg.nextStep)
//	id_stepProcess(arg.id_stepProcess),
//	id_nextStep(arg.id_nextStep)
{
    }

UniPAX::PathwayStep & UniPAX::PathwayStep::operator =(const PathwayStep & arg)  {
	UniPAX::UtilityClass::operator=(arg);
	stepProcess = arg.stepProcess;
	evidence = arg.evidence;
	nextStep = arg.nextStep;
//	id_stepProcess = arg.id_stepProcess;
//	id_nextStep = arg.id_nextStep;

	return *this;
}

UniPAX::PathwayStep::~PathwayStep()  {
    }

bool UniPAX::PathwayStep::merge(PathwayStep& object)
{
	{
		std::set<UniPAX::EntityPtr> tmp(getStepProcesses().begin(), getStepProcesses().end());
		for (std::vector<UniPAX::EntityPtr>::iterator it = object.getStepProcesses().begin(); it != object.getStepProcesses().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getStepProcesses().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::PathwayStepPtr> tmp(getNextSteps().begin(), getNextSteps().end());
		for (std::vector<UniPAX::PathwayStepPtr>::iterator it = object.getNextSteps().begin(); it != object.getNextSteps().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getNextSteps().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::EvidencePtr> tmp(evidence.begin(), evidence.end());
		for (std::vector<UniPAX::EvidencePtr>::iterator it = object.getEvidences().begin(); it != object.getEvidences().end(); it++)
		{
			if (*it)
			{
				tmp.insert(*it);
			}
		}
		evidence.assign(tmp.begin(), tmp.end());
	}

	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::PathwayStep::update(PersistenceManager& manager)
{
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
		std::vector<boost::shared_ptr<UniPAX::PathwayStep> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::PathwayStep> >::iterator it;
		for (it = nextStep.begin(); it != nextStep.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<PathwayStep>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setNextSteps(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::Entity> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
		for (it = stepProcess.begin(); it != stepProcess.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Entity>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setStepProcesses(tmp_vec);
	}

	return UniPAX::UtilityClass::update(manager);
}


const std::vector<boost::shared_ptr<UniPAX::Evidence> > & UniPAX::PathwayStep::getEvidences() const {
        return evidence;
}

std::vector<boost::shared_ptr<UniPAX::Evidence> > & UniPAX::PathwayStep::getEvidences() {
	return evidence; 
}

void UniPAX::PathwayStep::setEvidences(std::vector<boost::shared_ptr<UniPAX::Evidence> > _evidences) {
	evidence = _evidences;
}

void UniPAX::PathwayStep::addEvidence(boost::shared_ptr<UniPAX::Evidence>  _evidence) {
	evidence.push_back(_evidence);
}


const std::vector<boost::shared_ptr<UniPAX::PathwayStep> > & UniPAX::PathwayStep::getNextSteps() const {
        return nextStep;
}

std::vector<boost::shared_ptr<UniPAX::PathwayStep> > & UniPAX::PathwayStep::getNextSteps() {
	return nextStep;
}

void UniPAX::PathwayStep::setNextSteps(std::vector<boost::shared_ptr<UniPAX::PathwayStep> > _nextSteps) {
	nextStep = _nextSteps;
}

void UniPAX::PathwayStep::addNextStep(boost::shared_ptr<UniPAX::PathwayStep>  _nextStep) {
	nextStep.push_back(_nextStep);
}


const std::vector<boost::shared_ptr<UniPAX::Entity> > & UniPAX::PathwayStep::getStepProcesses() const {
	return stepProcess;
}

std::vector<boost::shared_ptr<UniPAX::Entity> > & UniPAX::PathwayStep::getStepProcesses()  {
        return stepProcess;
}

void UniPAX::PathwayStep::setStepProcesses(std::vector<boost::shared_ptr<UniPAX::Entity> > _stepProcesss)  {
    	stepProcess = _stepProcesss;
}

void UniPAX::PathwayStep::addStepProcess(boost::shared_ptr<UniPAX::Entity>  _stepProcess) {
	stepProcess.push_back(_stepProcess);
}


bool UniPAX::PathwayStep::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"stepProcess"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "PathwayStep::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		stepProcess.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(object));
		return true;
	}
	if (boost::iequals(attribute,"nextStep"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "PathwayStep::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		nextStep.push_back(boost::dynamic_pointer_cast<UniPAX::PathwayStep>(object));
		return true;
	}
	if (boost::iequals(attribute,"evidence"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "PathwayStep::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		evidence.push_back(boost::dynamic_pointer_cast<UniPAX::Evidence>(object));
		return true;
	}

	return false;

}

bool UniPAX::PathwayStep::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::Entity> >::iterator it;
		for (it = stepProcess.begin(); it != stepProcess.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#stepProcess", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#stepProcess", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::PathwayStep> >::iterator it;
		for (it = nextStep.begin(); it != nextStep.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#nextStep", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#nextStep", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::Evidence> >::iterator it;
		for (it = evidence.begin(); it != evidence.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#evidence", "NIL"));
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

	return true;

}


//void UniPAX::PathwayStep::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		{
//			stepProcess.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_stepProcess.begin(); it != id_stepProcess.end(); it++)
//			{
//				stepProcess.push_back(boost::dynamic_pointer_cast<UniPAX::Entity>(getObjectByID(db, *it)));
//			}
//		}
//		{
//			nextStep.clear();
//			std::vector<unsigned long long>::iterator it;
//			for (it = id_nextStep.begin(); it != id_nextStep.end(); it++)
//			{
//				nextStep.push_back(boost::dynamic_pointer_cast<UniPAX::PathwayStep>(getObjectByID(db, *it)));
//			}
//		}
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		{
//			id_stepProcess.clear();
//			std::vector<boost::shared_ptr<Entity> >::iterator it;
//			for (it = stepProcess.begin(); it != stepProcess.end(); it++)
//			{
//				if (*it != 0)
//					id_stepProcess.push_back((*it)->getUnipaxId());
//			}
//		}
//		{
//			id_nextStep.clear();
//			std::vector<boost::shared_ptr<PathwayStep> >::iterator it;
//			for (it = nextStep.begin(); it != nextStep.end(); it++)
//			{
//				if (*it != 0)
//					id_nextStep.push_back((*it)->getUnipaxId());
//			}
//		}
//	}
//
//	return;
//}

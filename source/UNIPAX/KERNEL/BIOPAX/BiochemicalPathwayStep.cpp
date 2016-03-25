#include<UNIPAX/KERNEL/BIOPAX/BiochemicalPathwayStep.h>
#include<set>

UniPAX::BiochemicalPathwayStep::BiochemicalPathwayStep() : UniPAX::PathwayStep()
//stepConversion(0),
//id_stepConversion(0)
{
}

UniPAX::BiochemicalPathwayStep::BiochemicalPathwayStep(const BiochemicalPathwayStep& arg) : UniPAX::PathwayStep(arg) ,
	stepDirection(arg.stepDirection),
	stepConversion(arg.stepConversion)
//	id_stepConversion(arg.id_stepConversion)
{
}

UniPAX::BiochemicalPathwayStep & UniPAX::BiochemicalPathwayStep::operator =(const BiochemicalPathwayStep & arg)  {
	UniPAX::PathwayStep::operator=(arg);
	stepDirection = arg.stepDirection;
	stepConversion = arg.stepConversion;
//	id_stepConversion = arg.id_stepConversion;

	return *this;
}

UniPAX::BiochemicalPathwayStep::~BiochemicalPathwayStep()  {
    }


bool UniPAX::BiochemicalPathwayStep::merge(BiochemicalPathwayStep& object)
{
	if (stepConversion != 0)
	{
		if (object.getStepConversion() != 0)
		{
			if (stepConversion->getUnipaxId() != object.getStepConversion()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::BiochemicalPathwayStep::stepConversion not equal ..."
						<< stepConversion->getUnipaxId() << " != " << object.getStepConversion()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setStepConversion(object.getStepConversion());
	}


	if (!object.getStepDirection().empty())
	{
		if (!getStepDirection().empty())
		{
			if (getStepDirection() != object.getStepDirection())
			{
				std::cerr << "Error during merging: UniPAX::BiochemicalPathwayStep::stepDirection not equal ..."
						<< getStepDirection() << " != " << object.getStepDirection() << std::endl;
				return false;
			}
		}
		else
			setStepDirection(object.getStepDirection());
	}

	return UniPAX::PathwayStep::merge(object);

}


bool UniPAX::BiochemicalPathwayStep::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getStepConversion()))
	{
		setStepConversion(boost::dynamic_pointer_cast<Conversion>(manager.getMergedObject(getStepConversion())));
	}

	return UniPAX::PathwayStep::update(manager);
}

const std::string & UniPAX::BiochemicalPathwayStep::getStepDirection() const {
        return stepDirection;
}

std::string & UniPAX::BiochemicalPathwayStep::getStepDirection() {
	return stepDirection;
}

void UniPAX::BiochemicalPathwayStep::setStepDirection(std::string _stepDirection) {
	stepDirection = _stepDirection;
}

const boost::shared_ptr<UniPAX::Conversion> UniPAX::BiochemicalPathwayStep::getStepConversion() const {
        return stepConversion;
}

boost::shared_ptr<UniPAX::Conversion> UniPAX::BiochemicalPathwayStep::getStepConversion() {
	return stepConversion;
}

void UniPAX::BiochemicalPathwayStep::setStepConversion(boost::shared_ptr<UniPAX::Conversion> _stepConversion) {
	stepConversion = _stepConversion;
}

bool UniPAX::BiochemicalPathwayStep::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::PathwayStep::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"stepConversion"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "BiochemicalPathwayStep::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		stepConversion = boost::dynamic_pointer_cast<UniPAX::Conversion>(object);
		return true;
	}
	if (boost::iequals(attribute,"stepDirection"))
	{
		setStepDirection(value);
		return true;
	}

	return false;

}


bool UniPAX::BiochemicalPathwayStep::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::PathwayStep::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (stepConversion == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#stepConversion", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(stepConversion,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#stepConversion", tmp));

	}

	if (!getStepDirection().empty())
		value.push_back(std::pair<std::string,std::string>("stepDirection", getStepDirection()));

	return true;

}

//void UniPAX::BiochemicalPathwayStep::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::PathwayStep::init(e,db);
//
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		stepConversion = boost::dynamic_pointer_cast<UniPAX::Conversion>(getObjectByID(db, id_stepConversion));
//	}
//	else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//	{
//		// set the object ids
//		if (stepConversion != 0)
//			id_stepConversion = stepConversion->getUnipaxId();
//	}
//}


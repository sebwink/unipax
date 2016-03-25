#include<UNIPAX/KERNEL/EXT/Model.h>
#include<set>
//Begin section for file Model.cpp
//TODO: Add definitions that you want preserved
//End section for file Model.cpp


UniPAX::Model::Model() : UniPAX::SBase() {
}

UniPAX::Model::Model(const Model& arg) : UniPAX::SBase(arg) ,
//		id_functionDefinition(arg.id_functionDefinition),
//		id_unitDefinition(arg.id_unitDefinition),
//		id_parameter(arg.id_parameter),
//		id_initialAssignment(arg.id_initialAssignment),
//		id_rule(arg.id_rule),
//		id_constraint(arg.id_constraint),
//		id_event(arg.id_event),
		functionDefinition(arg.functionDefinition),
		unitDefinition(arg.unitDefinition),
		parameter(arg.parameter),
		initialAssignment(arg.initialAssignment),
		rule(arg.rule),
		constraint(arg.constraint),
		id(arg.id),
		name(arg.name),
		substanceUnits(arg.substanceUnits),
		timeUnits(arg.timeUnits),
		volumeUnits(arg.volumeUnits),
		areaUnits(arg.areaUnits),
		lengthUnits(arg.lengthUnits),
		extentUnit(arg.extentUnit),
		conversionFactor(arg.conversionFactor),
		event(arg.event)
{
}

UniPAX::Model & UniPAX::Model::operator =(const Model & arg)  {
		UniPAX::SBase::operator=(arg);
		functionDefinition = arg.functionDefinition;
		unitDefinition = arg.unitDefinition;
		parameter = arg.parameter;
		initialAssignment = arg.initialAssignment;
		rule = arg.rule;
		constraint = arg.constraint;
		id = arg.id;
		name = arg.name;
		substanceUnits = arg.substanceUnits;
		timeUnits = arg.timeUnits;
		volumeUnits = arg.volumeUnits;
		areaUnits = arg.areaUnits;
		lengthUnits = arg.lengthUnits;
		extentUnit = arg.extentUnit;
		conversionFactor = arg.conversionFactor;
		event = arg.event;
		return *this;
}

UniPAX::Model::~Model()  {
}

bool UniPAX::Model::merge(Model& object)
{
		if (id.empty())
		{
				id = object.getId();
		}
		else
		{
				if (id.compare(object.getId()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Model::id not equal ..."
								<< id << " != " << object.getId() << std::endl;
						return false;
				}
		}

		if (name.empty())
		{
				name = object.getName();
		}
		else
		{
				if (name.compare(object.getName()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Model::name not equal ..."
								<< name << " != " << object.getName() << std::endl;
						return false;
				}
		}

		if (substanceUnits.empty())
		{
				substanceUnits = object.getSubstanceUnits();
		}
		else
		{
				if (substanceUnits.compare(object.getSubstanceUnits()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Model::substanceUnits not equal ..."
								<< substanceUnits << " != " << object.getSubstanceUnits() << std::endl;
						return false;
				}
		}

		if (timeUnits.empty())
		{
				timeUnits = object.getTimeUnits();
		}
		else
		{
				if (timeUnits.compare(object.getTimeUnits()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Model::timeUnits not equal ..."
								<< timeUnits << " != " << object.getTimeUnits() << std::endl;
						return false;
				}
		}

		if (volumeUnits.empty())
		{
				volumeUnits = object.getVolumeUnits();
		}
		else
		{
				if (volumeUnits.compare(object.getVolumeUnits()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Model::volumeUnits not equal ..."
								<< volumeUnits << " != " << object.getVolumeUnits() << std::endl;
						return false;
				}
		}

		if (areaUnits.empty())
		{
				areaUnits = object.getAreaUnits();
		}
		else
		{
				if (areaUnits.compare(object.getAreaUnits()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Model::areaUnits not equal ..."
								<< areaUnits << " != " << object.getAreaUnits() << std::endl;
						return false;
				}
		}

		if (lengthUnits.empty())
		{
				lengthUnits = object.getLengthUnits();
		}
		else
		{
				if (lengthUnits.compare(object.getLengthUnits()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Model::lengthUnits not equal ..."
								<< lengthUnits << " != " << object.getLengthUnits() << std::endl;
						return false;
				}
		}

		if (extentUnit.empty())
		{
				extentUnit = object.getExtentUnit();
		}
		else
		{
				if (extentUnit.compare(object.getExtentUnit()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Model::extentUnit not equal ..."
								<< extentUnit << " != " << object.getExtentUnit() << std::endl;
						return false;
				}
		}

		if (conversionFactor.empty())
		{
				conversionFactor = object.getConversionFactor();
		}
		else
		{
				if (conversionFactor.compare(object.getConversionFactor()) != 0)
				{
						std::cerr << "Error during merging: UniPAX::Model::conversionFactor not equal ..."
								<< conversionFactor << " != " << object.getConversionFactor() << std::endl;
						return false;
				}
		}

		// merge FunctionDefinitions
		{
			std::set<UniPAX::FunctionDefinitionPtr> tmp(getFunctionDefinitions().begin(), getFunctionDefinitions().end());
			for (std::vector<UniPAX::FunctionDefinitionPtr>::iterator it = object.getFunctionDefinitions().begin(); it != object.getFunctionDefinitions().end(); it++)
			{
				if (*it)
				{
					tmp.insert(*it);
				}
			}
			getFunctionDefinitions().assign(tmp.begin(), tmp.end());
		}
		// merge UnitDefinitions
		{
			std::set<UniPAX::UnitDefinitionPtr> tmp(getUnitDefinitions().begin(), getUnitDefinitions().end());
			for (std::vector<UniPAX::UnitDefinitionPtr>::iterator it = object.getUnitDefinitions().begin(); it != object.getUnitDefinitions().end(); it++)
			{
				if (*it)
				{
					tmp.insert(*it);
				}
			}
			getUnitDefinitions().assign(tmp.begin(), tmp.end());
		}
		// merge Parameters
		{
			std::set<UniPAX::ParameterPtr> tmp(getParameters().begin(), getParameters().end());
			for (std::vector<UniPAX::ParameterPtr>::iterator it = object.getParameters().begin(); it != object.getParameters().end(); it++)
			{
				if (*it)
				{
					tmp.insert(*it);
				}
			}
			getParameters().assign(tmp.begin(), tmp.end());
		}
		// merge InitialAssignments
		{
			std::set<UniPAX::InitialAssignmentPtr> tmp(getInitialAssignments().begin(), getInitialAssignments().end());
			for (std::vector<UniPAX::InitialAssignmentPtr>::iterator it = object.getInitialAssignments().begin(); it != object.getInitialAssignments().end(); it++)
			{
				if (*it)
				{
					tmp.insert(*it);
				}
			}
			getInitialAssignments().assign(tmp.begin(), tmp.end());
		}
		// merge Rules
		{
			std::set<UniPAX::RulePtr> tmp(getRules().begin(), getRules().end());
			for (std::vector<UniPAX::RulePtr>::iterator it = object.getRules().begin(); it != object.getRules().end(); it++)
			{
				if (*it)
				{
					tmp.insert(*it);
				}
			}
			getRules().assign(tmp.begin(), tmp.end());
		}
		// merge Constraints
		{
			std::set<UniPAX::ConstraintPtr> tmp(getConstraints().begin(), getConstraints().end());
			for (std::vector<UniPAX::ConstraintPtr>::iterator it = object.getConstraints().begin(); it != object.getConstraints().end(); it++)
			{
				if (*it)
				{
					tmp.insert(*it);
				}
			}
			getConstraints().assign(tmp.begin(), tmp.end());
		}
		// merge Events
		{
			std::set<UniPAX::EventPtr> tmp(getEvents().begin(), getEvents().end());
			for (std::vector<UniPAX::EventPtr>::iterator it = object.getEvents().begin(); it != object.getEvents().end(); it++)
			{
				if (*it)
				{
					tmp.insert(*it);
				}
			}
			getEvents().assign(tmp.begin(), tmp.end());
		}

		return UniPAX::SBase::merge(object);
}

bool UniPAX::Model::update(PersistenceManager& manager)
{
		{
				// run through vector to check each pointer
				std::vector<boost::shared_ptr<UniPAX::FunctionDefinition> > tmp_vec;
				std::vector<boost::shared_ptr<UniPAX::FunctionDefinition> >::iterator it;
				for (it = functionDefinition.begin(); it != functionDefinition.end(); it++)
				{
						if (manager.isMerged(*it))
								tmp_vec.push_back(boost::dynamic_pointer_cast<FunctionDefinition>(manager.getMergedObject(*it)));
						else
								tmp_vec.push_back(*it);
				}
				setFunctionDefinitions(tmp_vec);
		}
		{
				// run through vector to check each pointer
				std::vector<boost::shared_ptr<UniPAX::UnitDefinition> > tmp_vec;
				std::vector<boost::shared_ptr<UniPAX::UnitDefinition> >::iterator it;
				for (it = unitDefinition.begin(); it != unitDefinition.end(); it++)
				{
						if (manager.isMerged(*it))
								tmp_vec.push_back(boost::dynamic_pointer_cast<UnitDefinition>(manager.getMergedObject(*it)));
						else
								tmp_vec.push_back(*it);
				}
				setUnitDefinitions(tmp_vec);
		}
		{
				// run through vector to check each pointer
				std::vector<boost::shared_ptr<UniPAX::Parameter> > tmp_vec;
				std::vector<boost::shared_ptr<UniPAX::Parameter> >::iterator it;
				for (it = parameter.begin(); it != parameter.end(); it++)
				{
						if (manager.isMerged(*it))
								tmp_vec.push_back(boost::dynamic_pointer_cast<Parameter>(manager.getMergedObject(*it)));
						else
								tmp_vec.push_back(*it);
				}
				setParameters(tmp_vec);
		}
		{
				// run through vector to check each pointer
				std::vector<boost::shared_ptr<UniPAX::InitialAssignment> > tmp_vec;
				std::vector<boost::shared_ptr<UniPAX::InitialAssignment> >::iterator it;
				for (it = initialAssignment.begin(); it != initialAssignment.end(); it++)
				{
						if (manager.isMerged(*it))
								tmp_vec.push_back(boost::dynamic_pointer_cast<InitialAssignment>(manager.getMergedObject(*it)));
						else
								tmp_vec.push_back(*it);
				}
				setInitialAssignments(tmp_vec);
		}
		{
				// run through vector to check each pointer
				std::vector<boost::shared_ptr<UniPAX::Rule> > tmp_vec;
				std::vector<boost::shared_ptr<UniPAX::Rule> >::iterator it;
				for (it = rule.begin(); it != rule.end(); it++)
				{
						if (manager.isMerged(*it))
								tmp_vec.push_back(boost::dynamic_pointer_cast<Rule>(manager.getMergedObject(*it)));
						else
								tmp_vec.push_back(*it);
				}
				setRules(tmp_vec);
		}
		{
				// run through vector to check each pointer
				std::vector<boost::shared_ptr<UniPAX::Constraint> > tmp_vec;
				std::vector<boost::shared_ptr<UniPAX::Constraint> >::iterator it;
				for (it = constraint.begin(); it != constraint.end(); it++)
				{
						if (manager.isMerged(*it))
								tmp_vec.push_back(boost::dynamic_pointer_cast<Constraint>(manager.getMergedObject(*it)));
						else
								tmp_vec.push_back(*it);
				}
				setConstraints(tmp_vec);
		}
		{
				// run through vector to check each pointer
				std::vector<boost::shared_ptr<UniPAX::Event> > tmp_vec;
				std::vector<boost::shared_ptr<UniPAX::Event> >::iterator it;
				for (it = event.begin(); it != event.end(); it++)
				{
						if (manager.isMerged(*it))
								tmp_vec.push_back(boost::dynamic_pointer_cast<Event>(manager.getMergedObject(*it)));
						else
								tmp_vec.push_back(*it);
				}
				setEvents(tmp_vec);
		}

		return UniPAX::SBase::update(manager);
}

// id
std::string UniPAX::Model::getId()
{
		return id;
}

const std::string UniPAX::Model::getId() const
{
		return id;
}

void UniPAX::Model::setId(std::string _id)
{
		id = _id;
}

// name
std::string UniPAX::Model::getName()
{
		return name;
}

const std::string UniPAX::Model::getName() const
{
		return name;
}

void UniPAX::Model::setName(std::string _name)
{
		name = _name;
}

// substanceUnits
std::string UniPAX::Model::getSubstanceUnits()
{
		return substanceUnits;
}

const std::string UniPAX::Model::getSubstanceUnits() const
{
		return substanceUnits;
}

void UniPAX::Model::setSubstanceUnits(std::string _substanceUnits)
{
		substanceUnits = _substanceUnits;
}

// timeUnits
std::string UniPAX::Model::getTimeUnits()
{
		return timeUnits;
}

const std::string UniPAX::Model::getTimeUnits() const
{
		return timeUnits;
}

void UniPAX::Model::setTimeUnits(std::string _timeUnits)
{
		timeUnits = _timeUnits;
}

// volumeUnits
std::string UniPAX::Model::getVolumeUnits()
{
		return volumeUnits;
}

const std::string UniPAX::Model::getVolumeUnits() const
{
		return volumeUnits;
}

void UniPAX::Model::setVolumeUnits(std::string _volumeUnits)
{
		volumeUnits = _volumeUnits;
}

// areaUnits
std::string UniPAX::Model::getAreaUnits()
{
		return areaUnits;
}

const std::string UniPAX::Model::getAreaUnits() const
{
		return areaUnits;
}

void UniPAX::Model::setAreaUnits(std::string _areaUnits)
{
		areaUnits = _areaUnits;
}

// lengthUnits
std::string UniPAX::Model::getLengthUnits()
{
		return lengthUnits;
}

const std::string UniPAX::Model::getLengthUnits() const
{
		return lengthUnits;
}

void UniPAX::Model::setLengthUnits(std::string _lengthUnits)
{
		lengthUnits = _lengthUnits;
}

// extentUnit
std::string UniPAX::Model::getExtentUnit()
{
		return extentUnit;
}

const std::string UniPAX::Model::getExtentUnit() const
{
		return extentUnit;
}

void UniPAX::Model::setExtentUnit(std::string _extentUnit)
{
		extentUnit = _extentUnit;
}

// conversionFactor
std::string UniPAX::Model::getConversionFactor()
{
		return conversionFactor;
}

const std::string UniPAX::Model::getConversionFactor() const
{
		return conversionFactor;
}

void UniPAX::Model::setConversionFactor(std::string _conversionFactor)
{
		conversionFactor = _conversionFactor;
}



std::vector<boost::shared_ptr<UniPAX::FunctionDefinition> > & UniPAX::Model::getFunctionDefinitions()  {
		return functionDefinition;
}

const std::vector<boost::shared_ptr<UniPAX::FunctionDefinition> > & UniPAX::Model::getFunctionDefinitions() const {
		return functionDefinition;
}

void UniPAX::Model::setFunctionDefinitions(std::vector<boost::shared_ptr<UniPAX::FunctionDefinition> > _functionDefinitions)  {
		functionDefinition = _functionDefinitions;
}
void UniPAX::Model::addFunctionDefinition(boost::shared_ptr<UniPAX::FunctionDefinition>  _functionDefinition)  {
		functionDefinition.push_back(_functionDefinition);
}


std::vector<boost::shared_ptr<UniPAX::UnitDefinition> > & UniPAX::Model::getUnitDefinitions()  {
		return unitDefinition;
}

const std::vector<boost::shared_ptr<UniPAX::UnitDefinition> > & UniPAX::Model::getUnitDefinitions() const {
		return unitDefinition;
}

void UniPAX::Model::setUnitDefinitions(std::vector<boost::shared_ptr<UniPAX::UnitDefinition> > _unitDefinitions)  {
		unitDefinition = _unitDefinitions;
}

void UniPAX::Model::addUnitDefinition(boost::shared_ptr<UnitDefinition>  _unitDefinition)  {
		unitDefinition.push_back(_unitDefinition);
}


std::vector<boost::shared_ptr<UniPAX::Parameter> > & UniPAX::Model::getParameters()  {
		return parameter;
}

const std::vector<boost::shared_ptr<UniPAX::Parameter> > & UniPAX::Model::getParameters() const {
		return parameter;
}

void UniPAX::Model::setParameters(std::vector<boost::shared_ptr<UniPAX::Parameter> > _parameters)  {
		parameter = _parameters;
}
void UniPAX::Model::addParameter(boost::shared_ptr<UniPAX::Parameter>  _parameter)  {
		parameter.push_back(_parameter);
}


std::vector<boost::shared_ptr<UniPAX::InitialAssignment> > & UniPAX::Model::getInitialAssignments()  {
		return initialAssignment;
}

const std::vector<boost::shared_ptr<UniPAX::InitialAssignment> > & UniPAX::Model::getInitialAssignments() const {
		return initialAssignment;
}

void UniPAX::Model::setInitialAssignments(std::vector<boost::shared_ptr<UniPAX::InitialAssignment> > _initialAssignments)  {
		initialAssignment = _initialAssignments;
}

void UniPAX::Model::addInitialAssignment(boost::shared_ptr<UniPAX::InitialAssignment>  _initialAssignment)  {
		initialAssignment.push_back(_initialAssignment);
}


std::vector<boost::shared_ptr<UniPAX::Rule> > & UniPAX::Model::getRules()  {
		return rule;
}

const std::vector<boost::shared_ptr<UniPAX::Rule> > & UniPAX::Model::getRules() const {
		return rule;
}

void UniPAX::Model::setRules(std::vector<boost::shared_ptr<UniPAX::Rule> > _rules)  {
		rule = _rules;
}

void UniPAX::Model::addRule(boost::shared_ptr<UniPAX::Rule>  _rule)  {
		rule.push_back(_rule);
}


std::vector<boost::shared_ptr<UniPAX::Constraint> > & UniPAX::Model::getConstraints()  {
		return constraint;
}

const std::vector<boost::shared_ptr<UniPAX::Constraint> > & UniPAX::Model::getConstraints() const {
		return constraint;
}

void UniPAX::Model::setConstraints(std::vector<boost::shared_ptr<UniPAX::Constraint> > _constraints)  {
		constraint = _constraints;
}

void UniPAX::Model::addConstraint(boost::shared_ptr<UniPAX::Constraint>  _constraint)  {
		constraint.push_back(_constraint);
}

std::vector<boost::shared_ptr<UniPAX::Event> > & UniPAX::Model::getEvents()  {
		return event;
}

const std::vector<boost::shared_ptr<UniPAX::Event> > & UniPAX::Model::getEvents() const {
		return event;
}

void UniPAX::Model::setEvents(std::vector<boost::shared_ptr<UniPAX::Event> > _events)  {
		event = _events;
}

void UniPAX::Model::addEvent(boost::shared_ptr<UniPAX::Event>  _event)  {
		event.push_back(_event);
}

bool UniPAX::Model::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

		if (UniPAX::SBase::setAttribute(attribute, value, manager))
				return true;

		if (boost::iequals(attribute,"id"))
		{
				setId(value);
				return true;
		}
		if (boost::iequals(attribute,"name"))
		{
				setName(value);
				return true;
		}
		if (boost::iequals(attribute,"substanceUnits"))
		{
				setSubstanceUnits(value);
				return true;
		}
		if (boost::iequals(attribute,"timeUnits"))
		{
				setTimeUnits(value);
				return true;
		}
		if (boost::iequals(attribute,"volumeUnits"))
		{
				setVolumeUnits(value);
				return true;
		}
		if (boost::iequals(attribute,"areaUnits"))
		{
				setAreaUnits(value);
				return true;
		}
		if (boost::iequals(attribute,"lengthUnits"))
		{
				setLengthUnits(value);
				return true;
		}
		if (boost::iequals(attribute,"extentUnit"))
		{
				setExtentUnit(value);
				return true;
		}
		if (boost::iequals(attribute,"conversionFactor"))
		{
				setConversionFactor(value);
				return true;
		}

		if (boost::iequals(attribute,"functionDefinition"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Model::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				functionDefinition.push_back(boost::dynamic_pointer_cast<UniPAX::FunctionDefinition>(object));
				return true;
		}
		if (boost::iequals(attribute,"unitDefinition"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Model::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				unitDefinition.push_back(boost::dynamic_pointer_cast<UniPAX::UnitDefinition>(object));
				return true;
		}
		if (boost::iequals(attribute,"parameter"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Model::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				parameter.push_back(boost::dynamic_pointer_cast<UniPAX::Parameter>(object));
				return true;
		}
		if (boost::iequals(attribute,"initialAssignment"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Model::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				initialAssignment.push_back(boost::dynamic_pointer_cast<UniPAX::InitialAssignment>(object));
				return true;
		}
		if (boost::iequals(attribute,"rule"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Model::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				rule.push_back(boost::dynamic_pointer_cast<UniPAX::Rule>(object));
				return true;
		}
		if (boost::iequals(attribute,"constraint"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Model::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				constraint.push_back(boost::dynamic_pointer_cast<UniPAX::Constraint>(object));
				return true;
		}
		if (boost::iequals(attribute,"event"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "Model::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				event.push_back(boost::dynamic_pointer_cast<UniPAX::Event>(object));
				return true;
		}

		return false;

}


bool UniPAX::Model::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

		if (!UniPAX::SBase::getAttribute(value, manager))
				return false;
		{
				if (! getName().empty())
						value.push_back(std::pair<std::string,std::string>("name", getName()));
		}
		{
				if (! getId().empty())
						value.push_back(std::pair<std::string,std::string>("id", getId()));
		}
		{
				if (! getSubstanceUnits().empty())
						value.push_back(std::pair<std::string,std::string>("substanceUnits", getSubstanceUnits()));
		}
		{
				if (! getTimeUnits().empty())
						value.push_back(std::pair<std::string,std::string>("timeUnits", getTimeUnits()));
		}
		{
				if (! getVolumeUnits().empty())
						value.push_back(std::pair<std::string,std::string>("volumeUnits", getVolumeUnits()));
		}
		{
				if (! getAreaUnits().empty())
						value.push_back(std::pair<std::string,std::string>("areaUnits", getAreaUnits()));
		}
		{
				if (! getLengthUnits().empty())
						value.push_back(std::pair<std::string,std::string>("lengthUnits", getLengthUnits()));
		}
		{
				if (! getExtentUnit().empty())
						value.push_back(std::pair<std::string,std::string>("extentUnit", getExtentUnit()));
		}
		{
				if (! getConversionFactor().empty())
						value.push_back(std::pair<std::string,std::string>("conversionFactor", getConversionFactor()));
		}

		std::string tmp = "";
		{
				std::vector<boost::shared_ptr<UniPAX::FunctionDefinition> >::iterator it;
				for (it = functionDefinition.begin(); it != functionDefinition.end(); it++)
				{
						if (*it == 0)
						{
								//				value.push_back(std::pair<std::string,std::string>("#functionDefinition", "NIL"));
						}
						else
						{
								tmp.clear();
								if (!manager.getId(*it,tmp))
								{
										manager.setError(this->type() + ":functionDefinition contains unknown reference.");
										return false;
								}
								value.push_back(std::pair<std::string,std::string>("#functionDefinition", tmp));

						}
				}
		}
		tmp.clear();
		{
				std::vector<boost::shared_ptr<UniPAX::UnitDefinition> >::iterator it;
				for (it = unitDefinition.begin(); it != unitDefinition.end(); it++)
				{
						if (*it == 0)
						{
								//				value.push_back(std::pair<std::string,std::string>("#unitDefinition", "NIL"));
						}
						else
						{
								tmp.clear();
								if (!manager.getId(*it,tmp))
								{
										manager.setError(this->type() + ":unitDefinition contains unknown reference.");
										return false;
								}
								value.push_back(std::pair<std::string,std::string>("#unitDefinition", tmp));

						}
				}
		}
		tmp.clear();
		{
				std::vector<boost::shared_ptr<UniPAX::Parameter> >::iterator it;
				for (it = parameter.begin(); it != parameter.end(); it++)
				{
						if (*it == 0)
						{
								//				value.push_back(std::pair<std::string,std::string>("#parameter", "NIL"));
						}
						else
						{
								tmp.clear();
								if (!manager.getId(*it,tmp))
								{
										manager.setError(this->type() + ":parameter contains unknown reference.");
										return false;
								}
								value.push_back(std::pair<std::string,std::string>("#parameter", tmp));

						}
				}
		}
		tmp.clear();
		{
				std::vector<boost::shared_ptr<UniPAX::InitialAssignment> >::iterator it;
				for (it = initialAssignment.begin(); it != initialAssignment.end(); it++)
				{
						if (*it == 0)
						{
								//				value.push_back(std::pair<std::string,std::string>("#initialAssignment", "NIL"));
						}
						else
						{
								tmp.clear();
								if (!manager.getId(*it,tmp))
								{
										manager.setError(this->type() + ":initialAssignment contains unknown reference.");
										return false;
								}
								value.push_back(std::pair<std::string,std::string>("#initialAssignment", tmp));

						}
				}
		}
		tmp.clear();
		{
				std::vector<boost::shared_ptr<UniPAX::Rule> >::iterator it;
				for (it = rule.begin(); it != rule.end(); it++)
				{
						if (*it == 0)
						{
								//				value.push_back(std::pair<std::string,std::string>("#rule", "NIL"));
						}
						else
						{
								tmp.clear();
								if (!manager.getId(*it,tmp))
								{
										manager.setError(this->type() + ":rule contains unknown reference.");
										return false;
								}
								value.push_back(std::pair<std::string,std::string>("#rule", tmp));

						}
				}
		}
		tmp.clear();
		{
				std::vector<boost::shared_ptr<UniPAX::Constraint> >::iterator it;
				for (it = constraint.begin(); it != constraint.end(); it++)
				{
						if (*it == 0)
						{
								//				value.push_back(std::pair<std::string,std::string>("#constraint", "NIL"));
						}
						else
						{
								tmp.clear();
								if (!manager.getId(*it,tmp))
								{
										manager.setError(this->type() + ":constraint contains unknown reference.");
										return false;
								}
								value.push_back(std::pair<std::string,std::string>("#constraint", tmp));

						}
				}
		}
		tmp.clear();
		{
				std::vector<boost::shared_ptr<UniPAX::Event> >::iterator it;
				for (it = event.begin(); it != event.end(); it++)
				{
						if (*it == 0)
						{
								//				value.push_back(std::pair<std::string,std::string>("#event", "NIL"));
						}
						else
						{
								tmp.clear();
								if (!manager.getId(*it,tmp))
								{
										manager.setError(this->type() + ":event contains unknown reference.");
										return false;
								}
								value.push_back(std::pair<std::string,std::string>("#event", tmp));

						}
				}
		}

		return true;

}

//void UniPAX::Model::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		if (e == odb::callback_event::post_load)
//		{
//				// load the object pointer
//				{
//						functionDefinition.clear();
//						std::vector<unsigned long long>::iterator it;
//						for (it = id_functionDefinition.begin(); it != id_functionDefinition.end(); it++)
//						{
//								functionDefinition.push_back(boost::dynamic_pointer_cast<UniPAX::FunctionDefinition>(getObjectByID(db, *it)));
//						}
//				}
//				{
//						unitDefinition.clear();
//						std::vector<unsigned long long>::iterator it;
//						for (it = id_unitDefinition.begin(); it != id_unitDefinition.end(); it++)
//						{
//								unitDefinition.push_back(boost::dynamic_pointer_cast<UniPAX::UnitDefinition>(getObjectByID(db, *it)));
//						}
//				}
//				{
//						parameter.clear();
//						std::vector<unsigned long long>::iterator it;
//						for (it = id_parameter.begin(); it != id_parameter.end(); it++)
//						{
//								parameter.push_back(boost::dynamic_pointer_cast<UniPAX::Parameter>(getObjectByID(db, *it)));
//						}
//				}
//				{
//						initialAssignment.clear();
//						std::vector<unsigned long long>::iterator it;
//						for (it = id_initialAssignment.begin(); it != id_initialAssignment.end(); it++)
//						{
//								initialAssignment.push_back(boost::dynamic_pointer_cast<UniPAX::InitialAssignment>(getObjectByID(db, *it)));
//						}
//				}
//				{
//						rule.clear();
//						std::vector<unsigned long long>::iterator it;
//						for (it = id_rule.begin(); it != id_rule.end(); it++)
//						{
//								rule.push_back(boost::dynamic_pointer_cast<UniPAX::Rule>(getObjectByID(db, *it)));
//						}
//				}
//				{
//						constraint.clear();
//						std::vector<unsigned long long>::iterator it;
//						for (it = id_constraint.begin(); it != id_constraint.end(); it++)
//						{
//								constraint.push_back(boost::dynamic_pointer_cast<UniPAX::Constraint>(getObjectByID(db, *it)));
//						}
//				}
//				{
//						event.clear();
//						std::vector<unsigned long long>::iterator it;
//						for (it = id_event.begin(); it != id_event.end(); it++)
//						{
//								event.push_back(boost::dynamic_pointer_cast<UniPAX::Event>(getObjectByID(db, *it)));
//						}
//				}
//		}
//		else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//		{
//				// set the object ids
//				{
//						id_functionDefinition.clear();
//						std::vector<boost::shared_ptr<FunctionDefinition> >::iterator it;
//						for (it = functionDefinition.begin(); it != functionDefinition.end(); it++)
//						{
//								if (*it != 0)
//										id_functionDefinition.push_back((*it)->getUnipaxId());
//						}
//				}
//				{
//						id_unitDefinition.clear();
//						std::vector<boost::shared_ptr<UnitDefinition> >::iterator it;
//						for (it = unitDefinition.begin(); it != unitDefinition.end(); it++)
//						{
//								if (*it != 0)
//										id_unitDefinition.push_back((*it)->getUnipaxId());
//						}
//				}
//				{
//						id_parameter.clear();
//						std::vector<boost::shared_ptr<Parameter> >::iterator it;
//						for (it = parameter.begin(); it != parameter.end(); it++)
//						{
//								if (*it != 0)
//										id_parameter.push_back((*it)->getUnipaxId());
//						}
//				}
//				{
//						id_initialAssignment.clear();
//						std::vector<boost::shared_ptr<InitialAssignment> >::iterator it;
//						for (it = initialAssignment.begin(); it != initialAssignment.end(); it++)
//						{
//								if (*it != 0)
//										id_initialAssignment.push_back((*it)->getUnipaxId());
//						}
//				}
//				{
//						id_rule.clear();
//						std::vector<boost::shared_ptr<Rule> >::iterator it;
//						for (it = rule.begin(); it != rule.end(); it++)
//						{
//								if (*it != 0)
//										id_rule.push_back((*it)->getUnipaxId());
//						}
//				}
//				{
//						id_constraint.clear();
//						std::vector<boost::shared_ptr<Constraint> >::iterator it;
//						for (it = constraint.begin(); it != constraint.end(); it++)
//						{
//								if (*it != 0)
//										id_constraint.push_back((*it)->getUnipaxId());
//						}
//				}
//				{
//						id_event.clear();
//						std::vector<boost::shared_ptr<Event> >::iterator it;
//						for (it = event.begin(); it != event.end(); it++)
//						{
//								if (*it != 0)
//										id_event.push_back((*it)->getUnipaxId());
//						}
//				}
//		}
//
//		return;
//}

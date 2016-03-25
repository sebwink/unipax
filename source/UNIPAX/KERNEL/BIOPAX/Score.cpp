#include<UNIPAX/KERNEL/BIOPAX/Score.h>
#include<set>
//Begin section for file Score.cpp
//TODO: Add definitions that you want preserved
//End section for file Score.cpp

UniPAX::Score::Score() : UniPAX::UtilityClass()
//, scoreSource(0)
{
    }

UniPAX::Score::Score(const Score& arg) : UniPAX::UtilityClass(arg) {
    }

UniPAX::Score & UniPAX::Score::operator =(const Score & arg)  {
	UniPAX::UtilityClass::operator=(arg);
	scoreSource = arg.scoreSource;
	value = arg.value;

	return *this;
}

UniPAX::Score::~Score()  {
    }

bool UniPAX::Score::merge(Score& object)
{
	if (scoreSource != 0)
	{
		if (object.getScoreSource() != 0)
		{
			if (scoreSource->getUnipaxId() != object.getScoreSource()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::Score::scoreSource not equal ..."
						<< scoreSource->getUnipaxId() << " != " << object.getScoreSource()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setScoreSource(object.getScoreSource());
	}
	if (!object.getValue().empty())
	{
		if (!getValue().empty())
		{
			if (getValue() != object.getValue())
			{
				std::cerr << "Error during merging: UniPAX::Score::value not equal ..."
						<< getValue() << " != " << object.getValue() << std::endl;
				return false;
			}
		}
		else
			setValue(object.getValue());
	}

	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::Score::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getScoreSource()))
	{
		setScoreSource(boost::dynamic_pointer_cast<Provenance>(manager.getMergedObject(getScoreSource())));
	}

	return UniPAX::UtilityClass::update(manager);
}


const boost::shared_ptr<UniPAX::Provenance> UniPAX::Score::getScoreSource() const {
        return scoreSource;
}

boost::shared_ptr<UniPAX::Provenance> UniPAX::Score::getScoreSource() {
	return scoreSource;
}

void UniPAX::Score::setScoreSource(boost::shared_ptr<UniPAX::Provenance> _scoreSource) {
	scoreSource = _scoreSource;
}

const std::string UniPAX::Score::getValue() const {
	return value;
}

std::string UniPAX::Score::getValue() {
	return value;
}

void UniPAX::Score::setValue(std::string _value) {
	value = _value;
}

bool UniPAX::Score::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"scoreSource"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Score::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		scoreSource = boost::dynamic_pointer_cast<UniPAX::Provenance>(object);
		return true;
	}

	if (boost::iequals(attribute,"value"))
	{
		setValue(value);
		return true;
	}

	return false;

}



bool UniPAX::Score::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (scoreSource == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#scoreSource", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(scoreSource,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#scoreSource", tmp));

	}

	if (!getValue().empty())
		value.push_back(std::pair<std::string,std::string>("value", getValue()));

	return true;

}

//void UniPAX::Score::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	return;
//}

#include<UNIPAX/KERNEL/BIOPAX/SequenceInterval.h>
#include<set>
//Begin section for file SequenceInterval.cpp
//TODO: Add definitions that you want preserved
//End section for file SequenceInterval.cpp

UniPAX::SequenceInterval::SequenceInterval() : UniPAX::SequenceLocation()
//	, sequenceIntervalBegin(0)
//	, sequenceIntervalEnd(0)
{
    }

UniPAX::SequenceInterval::SequenceInterval(const SequenceInterval& arg) : UniPAX::SequenceLocation(arg) ,
		sequenceIntervalBegin(arg.sequenceIntervalBegin),
		sequenceIntervalEnd(arg.sequenceIntervalEnd)
{
    }

UniPAX::SequenceInterval & UniPAX::SequenceInterval::operator =(const SequenceInterval & arg)  {
	UniPAX::SequenceLocation::operator=(arg);
	sequenceIntervalBegin = arg.sequenceIntervalBegin;
	sequenceIntervalEnd = arg.sequenceIntervalEnd;

	return *this;
}

UniPAX::SequenceInterval::~SequenceInterval()  {
    }

bool UniPAX::SequenceInterval::merge(SequenceInterval& object)
{

	if (sequenceIntervalEnd != 0)
	{
		if (object.getSequenceIntervalEnd() != 0)
		{
			if (sequenceIntervalEnd->getUnipaxId() != object.getSequenceIntervalEnd()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::SequenceInterval::sequenceIntervalEnd not equal ..."
						<< sequenceIntervalEnd->getUnipaxId() << " != " << object.getSequenceIntervalEnd()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setSequenceIntervalEnd(object.getSequenceIntervalEnd());
	}
	if (sequenceIntervalBegin != 0)
	{
		if (object.getSequenceIntervalBegin() != 0)
		{
			if (sequenceIntervalBegin->getUnipaxId() != object.getSequenceIntervalBegin()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::SequenceInterval::sequenceIntervalBegin not equal ..."
						<< sequenceIntervalBegin->getUnipaxId() << " != " << object.getSequenceIntervalBegin()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setSequenceIntervalBegin(object.getSequenceIntervalBegin());
	}

	return UniPAX::SequenceLocation::merge(object);
}


bool UniPAX::SequenceInterval::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getSequenceIntervalBegin()))
	{
		setSequenceIntervalBegin(boost::dynamic_pointer_cast<SequenceSite>(manager.getMergedObject(getSequenceIntervalBegin())));
	}
	if (manager.isMerged(getSequenceIntervalEnd()))
	{
		setSequenceIntervalEnd(boost::dynamic_pointer_cast<SequenceSite>(manager.getMergedObject(getSequenceIntervalEnd())));
	}

	return UniPAX::SequenceLocation::update(manager);
}

const boost::shared_ptr<UniPAX::SequenceSite> UniPAX::SequenceInterval::getSequenceIntervalBegin() const {
        return sequenceIntervalBegin;
}

boost::shared_ptr<UniPAX::SequenceSite> UniPAX::SequenceInterval::getSequenceIntervalBegin() {
	return sequenceIntervalBegin;
}

void UniPAX::SequenceInterval::setSequenceIntervalBegin(boost::shared_ptr<UniPAX::SequenceSite> _sequenceIntervalBegin) {
	sequenceIntervalBegin = _sequenceIntervalBegin;
}

const boost::shared_ptr<UniPAX::SequenceSite> UniPAX::SequenceInterval::getSequenceIntervalEnd() const {
        return sequenceIntervalEnd;
}

boost::shared_ptr<UniPAX::SequenceSite> UniPAX::SequenceInterval::getSequenceIntervalEnd() {
	return sequenceIntervalEnd;
}

void UniPAX::SequenceInterval::setSequenceIntervalEnd(boost::shared_ptr<UniPAX::SequenceSite> _sequenceIntervalEnd) {
	sequenceIntervalEnd = _sequenceIntervalEnd;
}

bool UniPAX::SequenceInterval::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::SequenceLocation::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"sequenceIntervalEnd"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "SequenceInterval::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		sequenceIntervalEnd = boost::dynamic_pointer_cast<UniPAX::SequenceSite>(object);
		return true;
	}
	if (boost::iequals(attribute,"sequenceIntervalBegin"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "SequenceInterval::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		sequenceIntervalBegin = boost::dynamic_pointer_cast<UniPAX::SequenceSite>(object);
		return true;
	}

	return false;

}



bool UniPAX::SequenceInterval::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::SequenceLocation::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (sequenceIntervalEnd == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#sequenceIntervalEnd", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(sequenceIntervalEnd,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#sequenceIntervalEnd", tmp));

	}
	tmp.clear();
	if (sequenceIntervalBegin == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#sequenceIntervalBegin", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(sequenceIntervalBegin,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#sequenceIntervalBegin", tmp));

	}

	return true;

}

//void UniPAX::SequenceInterval::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::SequenceLocation::init(e,db);
//
//	return;
//}

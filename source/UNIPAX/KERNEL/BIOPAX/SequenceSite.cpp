#include<UNIPAX/KERNEL/BIOPAX/SequenceSite.h>
#include<set>
//Begin section for file SequenceSite.cpp
//TODO: Add definitions that you want preserved
//End section for file SequenceSite.cpp

UniPAX::SequenceSite::SequenceSite() : UniPAX::SequenceLocation(),
		sequencePosition(0)
{
}

UniPAX::SequenceSite::SequenceSite(const SequenceSite& arg) : UniPAX::SequenceLocation(arg) ,
		sequencePosition(arg.sequencePosition),
		positionStatus(arg.positionStatus)
{}

UniPAX::SequenceSite & UniPAX::SequenceSite::operator =(const SequenceSite & arg)  {
	UniPAX::SequenceLocation::operator=(arg);
	sequencePosition = arg.sequencePosition;
	positionStatus = arg.positionStatus;

	return *this;
}

UniPAX::SequenceSite::~SequenceSite()  {
}

bool UniPAX::SequenceSite::merge(SequenceSite& object)
{
	if (!object.getSequencePosition() != 0)
	{
		if (!getSequencePosition() != 0)
		{
			if (getSequencePosition() != object.getSequencePosition())
			{
				std::cerr << "Error during merging: UniPAX::SequenceSite::sequencePosition not equal ..."
						<< getSequencePosition() << " != " << object.getSequencePosition() << std::endl;
				return false;
			}
		}
		else
			setSequencePosition(object.getSequencePosition());
	}

	if (!object.getPositionStatus().empty())
	{
		if (!getPositionStatus().empty())
		{
			if (getPositionStatus() != object.getPositionStatus())
			{
				std::cerr << "Error during merging: UniPAX::SequenceSite::positionStatus not equal ..."
						<< getPositionStatus() << " != " << object.getPositionStatus() << std::endl;
				return false;
			}
		}
		else
			setPositionStatus(object.getPositionStatus());
	}

	return UniPAX::SequenceLocation::merge(object);
}

bool UniPAX::SequenceSite::update(PersistenceManager& manager)
{
	return UniPAX::SequenceLocation::update(manager);
}


const std::string & UniPAX::SequenceSite::getPositionStatus() const {
	return positionStatus;
}

std::string & UniPAX::SequenceSite::getPositionStatus() {
	return positionStatus;
}

void UniPAX::SequenceSite::setPositionStatus(std::string _positionStatus) {
	positionStatus = _positionStatus;
}

const int UniPAX::SequenceSite::getSequencePosition() const {
	return sequencePosition;
}

int UniPAX::SequenceSite::getSequencePosition()  {
	return sequencePosition;
}

void UniPAX::SequenceSite::setSequencePosition(int _sequencePosition)  {
	sequencePosition = _sequencePosition;
}

bool UniPAX::SequenceSite::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::SequenceLocation::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"sequencePosition"))
	{
		return (PersistenceManager::convertAttribute(value,sequencePosition));
	}
	if (boost::iequals(attribute,"positionStatus"))
	{
		setPositionStatus(value);
		return true;
	}

	return false;

}



bool UniPAX::SequenceSite::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::SequenceLocation::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (!PersistenceManager::convertAttribute(sequencePosition, tmp))
	{
		return false;
	}
	if (sequencePosition != 0)
		value.push_back(std::pair<std::string,std::string>("sequencePosition", tmp));


	if (!getPositionStatus().empty())
		value.push_back(std::pair<std::string,std::string>("positionStatus", getPositionStatus()));

	return true;

}

//void UniPAX::SequenceSite::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::SequenceLocation::init(e,db);
//
//	return;
//}

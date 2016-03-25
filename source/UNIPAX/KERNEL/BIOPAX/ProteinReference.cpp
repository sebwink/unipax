#include<UNIPAX/KERNEL/BIOPAX/ProteinReference.h>
#include<set>
//Begin section for file ProteinReference.cpp
//TODO: Add definitions that you want preserved
//End section for file ProteinReference.cpp

UniPAX::ProteinReference::ProteinReference() : UniPAX::EntityReference()
//, organism(0)
{
    }

UniPAX::ProteinReference::ProteinReference(const ProteinReference & arg) : UniPAX::EntityReference(arg) ,
    sequence(arg.sequence),
	organism(arg.organism)
{}

UniPAX::ProteinReference & UniPAX::ProteinReference::operator =(const ProteinReference & arg)  {
	UniPAX::EntityReference::operator=(arg);
	sequence = arg.sequence;
	organism = arg.organism;

	return *this;
}

UniPAX::ProteinReference::~ProteinReference()  {
    }


bool UniPAX::ProteinReference::merge(ProteinReference& object)
{
	if (organism != 0)
	{
		if (organism->getUnipaxId() != object.getOrganism()->getUnipaxId())
		{
			std::cerr << "Error during merging: UniPAX::ProteinReference::organism not equal ..."
					<< organism->getUnipaxId() << " != " << object.getOrganism()->getUnipaxId() << std::endl;
//			return false;
		}
	}
	else
	{
		setOrganism(object.getOrganism());
	}
	if (!object.getSequence().empty())
	{
		if (!getSequence().empty())
		{
			if (getSequence() != object.getSequence())
			{
				std::cerr << "Error during merging: UniPAX::ProteinReference::sequence not equal ..."
						<< getSequence() << " != " << object.getSequence() << std::endl;
				return false;
			}
		}
		else
			setSequence(object.getSequence());
	}

	return UniPAX::EntityReference::merge(object);

}

bool UniPAX::ProteinReference::update(PersistenceManager& manager)
{
	std::cout << "check org" << std::endl;
	if (getOrganism() != 0)
	{
		// check single pointer if object was merged
		if (manager.isMerged(getOrganism()))
		{
			std::cout << "org was merged\told id: " << getOrganism()->getUnipaxId() << "\tnew id: " << manager.getMergedObject(getOrganism())->getUnipaxId() << std::endl;

		setOrganism(boost::dynamic_pointer_cast<BioSource>(manager.getMergedObject(getOrganism())));
			std::cout << "updated org" << std::endl;
		}

		else
			std::cout << "org was not merged\told id: " << getOrganism()->getUnipaxId() << std::endl;
	}

	return UniPAX::EntityReference::update(manager);
}


const std::string & UniPAX::ProteinReference::getSequence() const {
        return sequence;
}

std::string & UniPAX::ProteinReference::getSequence() {
	return sequence;
}

void UniPAX::ProteinReference::setSequence(std::string _sequence) {
	sequence = _sequence;
}

const boost::shared_ptr<UniPAX::BioSource> UniPAX::ProteinReference::getOrganism() const {
        return organism;
}

boost::shared_ptr<UniPAX::BioSource> UniPAX::ProteinReference::getOrganism() {
	return organism;
}

void UniPAX::ProteinReference::setOrganism(boost::shared_ptr<UniPAX::BioSource> _organism) {
	organism = _organism;
}

bool UniPAX::ProteinReference::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::EntityReference::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"organism"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "ProteinReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		organism = boost::dynamic_pointer_cast<UniPAX::BioSource>(object);
		return true;
	}
	if (boost::iequals(attribute,"sequence"))
	{
		setSequence(value);
		return true;
	}

	return false;

}


bool UniPAX::ProteinReference::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::EntityReference::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (organism == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#organism", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(organism,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#organism", tmp));

	}
	if (!getSequence().empty())
		value.push_back(std::pair<std::string,std::string>("sequence", getSequence()));

	return true;

}

//void UniPAX::ProteinReference::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::EntityReference::init(e,db);
//
//	return;
//}

#include<UNIPAX/KERNEL/BIOPAX/Gene.h>
#include<set>
//Begin section for file Gene.cpp
//TODO: Add definitions that you want preserved
//End section for file Gene.cpp

UniPAX::Gene::Gene() : UniPAX::Entity()
//, organism(0)
{
    }

UniPAX::Gene::Gene(const Gene& arg) : UniPAX::Entity(arg) ,
	organism(arg.organism)
{}

UniPAX::Gene & UniPAX::Gene::operator =(const Gene & arg)  {
	UniPAX::Entity::operator=(arg);
	organism = arg.organism;

	return *this;
}

UniPAX::Gene::~Gene()  {
    }

bool UniPAX::Gene::merge(Gene& object)
{
	if (organism != 0)
	{
		if (object.getOrganism() != 0)
		{
			if (organism->getUnipaxId() != object.getOrganism()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::Gene::organism not equal ..."
						<< organism->getUnipaxId() << " != " << object.getOrganism()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setOrganism(object.getOrganism());
	}

	return UniPAX::Entity::merge(object);
}

bool UniPAX::Gene::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getOrganism()))
	{
		setOrganism(boost::dynamic_pointer_cast<BioSource>(manager.getMergedObject(getOrganism())));
	}

	return UniPAX::Entity::update(manager);
}

const boost::shared_ptr<UniPAX::BioSource> UniPAX::Gene::getOrganism() const {
        return organism;
}

boost::shared_ptr<UniPAX::BioSource> UniPAX::Gene::getOrganism() {
	return organism;
}

void UniPAX::Gene::setOrganism(boost::shared_ptr<UniPAX::BioSource> _organism) {
	organism = _organism;
}

bool UniPAX::Gene::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Entity::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"organism"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "Gene::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		organism = boost::dynamic_pointer_cast<UniPAX::BioSource>(object);
		return true;
	}

	return false;

}

bool UniPAX::Gene::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Entity::getAttribute(value, manager))
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

	return true;

}

//void UniPAX::Gene::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Entity::init(e,db);
//
//	return;
//}


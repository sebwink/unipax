#include<UNIPAX/KERNEL/BIOPAX/PhenotypeVocabulary.h>
#include<set>
//Begin section for file PhenotypeVocabulary.cpp
//TODO: Add definitions that you want preserved
//End section for file PhenotypeVocabulary.cpp

UniPAX::PhenotypeVocabulary::PhenotypeVocabulary() : UniPAX::ControlledVocabulary() {
    }

UniPAX::PhenotypeVocabulary::PhenotypeVocabulary(const PhenotypeVocabulary& arg) : UniPAX::ControlledVocabulary(arg) {
    	patoData = arg.patoData;
}

UniPAX::PhenotypeVocabulary & UniPAX::PhenotypeVocabulary::operator =(const PhenotypeVocabulary & arg)  {
	UniPAX::ControlledVocabulary::operator=(arg);
	patoData = arg.patoData;

	return *this;
}

UniPAX::PhenotypeVocabulary::~PhenotypeVocabulary()  {
    }

bool UniPAX::PhenotypeVocabulary::merge(PhenotypeVocabulary& object)
{
	if (!object.getPatoData().empty())
	{
		if (!getPatoData().empty())
		{
			if (getPatoData() != object.getPatoData())
			{
				std::cerr << "Error during merging: UniPAX::PhenotypeVocabulary::patoData not equal ..."
						<< getPatoData() << " != " << object.getPatoData() << std::endl;
				return false;
			}
		}
		else
			setPatoData(object.getPatoData());
	}

	return UniPAX::ControlledVocabulary::merge(object);
}

bool UniPAX::PhenotypeVocabulary::update(PersistenceManager& manager)
{
	return UniPAX::ControlledVocabulary::update(manager);
}


const std::string & UniPAX::PhenotypeVocabulary::getPatoData() const {
        return patoData;
}

std::string & UniPAX::PhenotypeVocabulary::getPatoData() {
	return patoData;
}

void UniPAX::PhenotypeVocabulary::setPatoData(std::string _patoData) {
	patoData = _patoData;
}

bool UniPAX::PhenotypeVocabulary::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::ControlledVocabulary::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"patoData"))
	{
		setPatoData(value);
		return true;
	}

	return false;

}


bool UniPAX::PhenotypeVocabulary::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::ControlledVocabulary::getAttribute(value, manager))
		return false;

	if (!getPatoData().empty())
		value.push_back(std::pair<std::string,std::string>("patoData", getPatoData()));

	return true;

}

//void UniPAX::PhenotypeVocabulary::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::ControlledVocabulary::init(e,db);
//
//	return;
//}

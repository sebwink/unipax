#include<UNIPAX/KERNEL/BIOPAX/SmallMoleculeReference.h>
#include<set>
//Begin section for file SmallMoleculeReference.cpp
//TODO: Add definitions that you want preserved
//End section for file SmallMoleculeReference.cpp

UniPAX::SmallMoleculeReference::SmallMoleculeReference() : UniPAX::EntityReference(),
		molecularWeight(0)
//	structure(0) ,
//	molecularWeight(0.)
{
}

UniPAX::SmallMoleculeReference::SmallMoleculeReference(const SmallMoleculeReference& arg) : UniPAX::EntityReference(arg) ,
		chemicalFormula(arg.chemicalFormula),
		molecularWeight(arg.molecularWeight),
		structure(arg.structure)
{
}

UniPAX::SmallMoleculeReference & UniPAX::SmallMoleculeReference::operator =(const SmallMoleculeReference & arg)  {
	UniPAX::EntityReference::operator=(arg);
	chemicalFormula = arg.chemicalFormula;
	molecularWeight = arg.molecularWeight;
	structure = arg.structure;

	return *this;
}

UniPAX::SmallMoleculeReference::~SmallMoleculeReference()  {
}

bool UniPAX::SmallMoleculeReference::merge(SmallMoleculeReference& object)
{

	if (structure != 0)
	{
		if (object.getStructure() != 0)
		{
			if (structure->getUnipaxId() != object.getStructure()->getUnipaxId())
			{
				std::cerr << "Error during merging: UniPAX::SmallMoleculeReference::structure not equal ..."
						<< structure->getUnipaxId() << " != " << object.getStructure()->getUnipaxId() << std::endl;
				return false;
			}
		}
	}
	else
	{
		setStructure(object.getStructure());
	}

	if (!object.getMolecularWeight() != 0.)
	{
		if (!getMolecularWeight() != 0.)
		{
			if (getMolecularWeight() != object.getMolecularWeight())
			{
				std::cerr << "Error during merging: UniPAX::SmallMoleculeReference::molecularWeight not equal ..."
						<< getMolecularWeight() << " != " << object.getMolecularWeight() << std::endl;
				return false;
			}
		}
		else
			setMolecularWeight(object.getMolecularWeight());
	}

	if (!object.getChemicalFormula().empty())
	{
		if (!getChemicalFormula().empty())
		{
			if (getChemicalFormula() != object.getChemicalFormula())
			{
				std::cerr << "Error during merging: UniPAX::SmallMoleculeReference::chemicalFormula not equal ..."
						<< getChemicalFormula() << " != " << object.getChemicalFormula() << std::endl;
				return false;
			}
		}
		else
			setChemicalFormula(object.getChemicalFormula());
	}

	return UniPAX::EntityReference::merge(object);
}

bool UniPAX::SmallMoleculeReference::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
	if (manager.isMerged(getStructure()))
	{
		setStructure(boost::dynamic_pointer_cast<ChemicalStructure>(manager.getMergedObject(getStructure())));
	}

	return UniPAX::EntityReference::update(manager);
}


const std::string & UniPAX::SmallMoleculeReference::getChemicalFormula() const {
	return chemicalFormula;
}

std::string & UniPAX::SmallMoleculeReference::getChemicalFormula() {
	return chemicalFormula;
}

void UniPAX::SmallMoleculeReference::setChemicalFormula(std::string _chemicalFormula) {
	chemicalFormula = _chemicalFormula;
}

const double UniPAX::SmallMoleculeReference::getMolecularWeight() const {
	return molecularWeight;
}

double UniPAX::SmallMoleculeReference::getMolecularWeight()  {
	return molecularWeight;
}

void UniPAX::SmallMoleculeReference::setMolecularWeight(double _molecularWeight)  {
	molecularWeight = _molecularWeight;
}

const boost::shared_ptr<UniPAX::ChemicalStructure> UniPAX::SmallMoleculeReference::getStructure() const {
	return structure;
}

boost::shared_ptr<UniPAX::ChemicalStructure> UniPAX::SmallMoleculeReference::getStructure() {
	return structure;
}

void UniPAX::SmallMoleculeReference::setStructure(boost::shared_ptr<UniPAX::ChemicalStructure> _structure) {
	structure = _structure;
}

bool UniPAX::SmallMoleculeReference::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::EntityReference::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"structure"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "SmallMoleculeReference::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		structure = boost::dynamic_pointer_cast<UniPAX::ChemicalStructure>(object);
		return true;
	}
	if (boost::iequals(attribute,"molecularWeight"))
	{
		return (PersistenceManager::convertAttribute(value,molecularWeight));
	}
	if (boost::iequals(attribute,"chemicalFormula"))
	{
		setChemicalFormula(value);
		return true;
	}


	return false;

}


bool UniPAX::SmallMoleculeReference::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::EntityReference::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (structure == 0)
	{
		//		value.push_back(std::pair<std::string,std::string>("#structure", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(structure,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#structure", tmp));

	}
	tmp.clear();
	if (!PersistenceManager::convertAttribute(molecularWeight, tmp))
	{
		return false;
	}
	if (molecularWeight != 0.)
		value.push_back(std::pair<std::string,std::string>("molecularWeight", tmp));


	if (!getChemicalFormula().empty())
		value.push_back(std::pair<std::string,std::string>("chemicalFormula", getChemicalFormula()));

	return true;

}

//void UniPAX::SmallMoleculeReference::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::EntityReference::init(e,db);
//	return;
//}

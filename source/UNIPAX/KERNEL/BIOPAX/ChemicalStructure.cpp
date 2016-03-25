#include<UNIPAX/KERNEL/BIOPAX/ChemicalStructure.h>
#include<set>
//Begin section for file ChemicalStructure.cpp
//TODO: Add definitions that you want preserved
//End section for file ChemicalStructure.cpp

UniPAX::ChemicalStructure::ChemicalStructure() : UniPAX::UtilityClass() {
    }

UniPAX::ChemicalStructure::ChemicalStructure(const ChemicalStructure& arg) : UniPAX::UtilityClass(arg) ,
	structureData(arg.structureData),
	structureFormat(arg.structureFormat)
{
    }

UniPAX::ChemicalStructure & UniPAX::ChemicalStructure::operator =(const ChemicalStructure & arg)  {
	UniPAX::UtilityClass::operator=(arg);
	structureData = arg.structureData;
	structureFormat = arg.structureFormat;

	return *this;
}

UniPAX::ChemicalStructure::~ChemicalStructure()  {
    }



bool UniPAX::ChemicalStructure::merge(ChemicalStructure& object)
{
	if (!object.getStructureFormat().empty())
	{
		if (!getStructureFormat().empty())
		{
			if (getStructureFormat() != object.getStructureFormat())
			{
				std::cerr << "Error during merging: UniPAX::ChemicalStructure::structureFormat not equal ..."
						<< getStructureFormat() << " != " << object.getStructureFormat() << std::endl;
				return false;
			}
		}
		else
			setStructureFormat(object.getStructureFormat());
	}
	if (!object.getStructureData().empty())
	{
		if (!getStructureData().empty())
		{
			if (getStructureData() != object.getStructureData())
			{
				std::cerr << "Error during merging: UniPAX::ChemicalStructure::structureData not equal ..."
						<< getStructureData() << " != " << object.getStructureData() << std::endl;
				return false;
			}
		}
		else
			setStructureData(object.getStructureData());
	}

	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::ChemicalStructure::update(PersistenceManager& manager)
{
	return UniPAX::UtilityClass::update(manager);
}


const std::string & UniPAX::ChemicalStructure::getStructureData() const {
        return structureData;
}

std::string & UniPAX::ChemicalStructure::getStructureData() {
	return structureData;
}

void UniPAX::ChemicalStructure::setStructureData(std::string _structureData) {
	structureData = _structureData;
}

const std::string & UniPAX::ChemicalStructure::getStructureFormat() const {
        return structureFormat;
}

std::string & UniPAX::ChemicalStructure::getStructureFormat() {
	return structureFormat;
}

void UniPAX::ChemicalStructure::setStructureFormat(std::string _structureFormat) {
	structureFormat = _structureFormat;
}

bool UniPAX::ChemicalStructure::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"structureData"))
	{
		setStructureData(value);
		return true;
	}
	if (boost::iequals(attribute,"structureFormat"))
	{
		setStructureFormat(value);
		return true;
	}

	return false;

}


bool UniPAX::ChemicalStructure::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;


	if (!getStructureFormat().empty())
		value.push_back(std::pair<std::string,std::string>("structureFormat", getStructureFormat()));
	if (!getStructureData().empty())
		value.push_back(std::pair<std::string,std::string>("structureData", getStructureData()));

	return true;

}


//void UniPAX::ChemicalStructure::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	return;
//}

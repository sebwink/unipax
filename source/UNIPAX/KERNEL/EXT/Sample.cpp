#include<UNIPAX/KERNEL/EXT/Sample.h>

#include <odb/traits.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/SampleData-odb.hxx>

#include <QtCore/qstring.h>

UniPAX::Sample::Sample() : UniPAX::UIBase()
{
}
UniPAX::Sample::Sample(const Sample & arg)  : UniPAX::UIBase(arg),
		name(arg.name),
		description_tags(arg.description_tags)
{
}

UniPAX::Sample & UniPAX::Sample::operator =(const Sample & arg)  {
	UniPAX::UIBase::operator=(arg);

	name = arg.name;
	description_tags = arg.description_tags;

	return *this;
}

UniPAX::Sample::~Sample()  {
}

bool UniPAX::Sample::merge(Sample& object)
{
	std::cerr << "Error during merging: UniPAX::Sample should not be merged." << std::endl;
	return false;
}

bool UniPAX::Sample::update(PersistenceManager& manager)
{
	return UniPAX::UPBase::update(manager);
}

// name
const std::string UniPAX::Sample::getName() const
{
	return name;
}
std::string UniPAX::Sample::getName()
{
	return name;
}

void UniPAX::Sample::setName(std::string _name)
{
	name = _name;
}

// description_tags
const std::map<std::string, std::string> & UniPAX::Sample::getDescriptionTags() const
{
	return description_tags;
}

std::map<std::string, std::string> & UniPAX::Sample::getDescriptionTags()
{
	return description_tags;
}

void UniPAX::Sample::setDescriptionTags(std::map<std::string, std::string> _description_tags)
{
	description_tags = _description_tags;
}

void UniPAX::Sample::setDescriptionTag(std::string tag, std::string value)
{
	description_tags[tag] = value;
}

const UniPAX::SampleDataPtr UniPAX::Sample::getSampleData() const
{
	return data;
}

UniPAX::SampleDataPtr UniPAX::Sample::getSampleData()
{
	return data;
}

void UniPAX::Sample::setSampleData(SampleDataPtr _data)
{
	data = _data;
}

//// unit
//const UnipaxPtr<UniPAX::UnitDefinition>::type & UniPAX::Sample::getUnit() const
//{
//	return unit;
//}
//
//UnipaxPtr<UniPAX::UnitDefinition>::type & UniPAX::Sample::getUnit()
//{
//	return unit;
//}
//
//void UniPAX::Sample::setUnit(UnipaxPtr<UniPAX::UnitDefinition>::type _unit)
//{
//	unit = _unit;
//}
//
//// error
//const double UniPAX::Sample::getError() const
//{
//	return error;
//}
//
//double UniPAX::Sample::getError()
//{
//	return error;
//}
//
//void UniPAX::Sample::setError(double _error)
//{
//	error = _error;
//}

bool UniPAX::Sample::setAttribute(std::string& attribute, std::string& value, UniPAX::PersistenceManager& manager) {

	if(UniPAX::UIBase::setAttribute(attribute, value, manager))
		return true;

	if(boost::iequals(attribute, "name"))
	{
		name = value;
		return true;
	}
	if (boost::iequals(attribute,"description_tags"))
	{
		int pos = value.find("=");
		if (pos == -1)
		{
			std::cerr << "Sample::setAttribute - invalid tag (value = " << value << ")" << std::endl;
			return false;
		}
		description_tags[value.substr(0, pos)] = value.substr(pos);
		return true;
	}
//	if (boost::iequals(attribute,"dataMatrix"))
//	{
//		if (dataMatrix == 0)
//		{
//			QByteArray array;
//			array.append(value.c_str());
//
//			dataMatrix = UnipaxPtr<UniPAX::DataMatrix>::type(new UniPAX::DataMatrix(array)); // dataMatrix is not persistend!
//			return true;
//		}
//		else
//		{
//			std::cerr << "Sample::setAttribute - dataMatrix not null." << std::endl;
//			return false;
//		}
//	}
	/*    if (boost::iequals(attribute,"matrix_column_names"))
		{
        if (dataMatrix == 0)
        {
            std::cerr << "Sample::setAttribute - dataMatrix not initialized." << std::endl;
            return false;
        }

		}*/
//	if (boost::iequals(attribute,"#unit"))
//	{
//		// if sometimes set to NIL or empty string neglect
//		if (value == "NIL" || value.empty())
//			return true;
//
//		UnipaxPtr<UniPAX::UPBase>::type object = manager.getInstance(value,"");
//		if (object == 0)
//		{
//			std::cerr << "Sample::setAttribute - object not known (value = " << value << ")" << std::endl;
//			return false;
//		}
//
//		unit = boost::dynamic_pointer_cast<UniPAX::UnitDefinition>(object);
//		return true;
//	}
//	if (boost::iequals(attribute,"error"))
//	{
//		if (!UniPAX::PersistenceManager::convertAttribute(value, error))
//		{
//			std::cerr << "Sample::setAttribute - could not convert to Sample::error (value = " << value << ")" << std::endl;
//		}
//		return true;
//	}
	return false;
}

bool UniPAX::Sample::getAttribute(std::vector<std::pair<std::string,std::string> >& value, UniPAX::PersistenceManager& manager) {

	if (!UniPAX::UIBase::getAttribute(value, manager))
		return false;

	value.push_back(std::pair<std::string,std::string>("name", name));

	std::stringstream ss;
	for (std::map<std::string, std::string>::const_iterator it = description_tags.begin(); it != description_tags.end(); it++)
	{
		ss.str("");
		ss << it->first << "=" << it->second;
		value.push_back(std::pair<std::string, std::string>("description_tags", ss.str()));
	}

//	value.push_back(std::pair<std::string, std::string>("dataMatrix", QString(dataMatrix->getData()).toStdString()));

	/*    for (std::vector<std::string>::const_iterator it = dataMatrix.getColumnNames().begin(); it != dataMatrix.getColumnNames().end(); it++)
    {
        value.push_back(std::pair<std::string, std::string>("matrix_column_names", *it));
    }*/
//	std::string tmp;
//	if (unit == 0)
//	{
//	}
//	else
//	{
//		tmp.clear();
//		if (!manager.getId(unit, tmp))
//		{
//			manager.setError(this->type() + ":unit contains unknown reference.");
//			return false;
//		}
//		value.push_back(std::pair<std::string, std::string>("#unit", tmp));
//	}
//	tmp.clear();
//	if (!UniPAX::PersistenceManager::convertAttribute(error, tmp))
//		return false;
//	value.push_back(std::pair<std::string, std::string>("error", tmp));
	return true;
}


//void UniPAX::Sample::init (odb::callback_event e, odb::database& db)
//{
//	// set pointer!
//	if (e == odb::callback_event::post_load)
//	{
//		// load the object pointer
//		// set the matrix data
//		//dataMatrix = UniPAX::DataMatrixPtr(new UniPAX::DataMatrix(data_matrix));
//		//data = db.load<SampleDataBase>();
//	}
//
//}
//
void UniPAX::Sample::init (odb::callback_event e, odb::database& db) const
{

	if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
	{
		// get the data from matrix
//		if (dataMatrix != 0) {
//			const_cast<QByteArray&>(data_matrix) = dataMatrix->getData();
//		}
		if (data->getValueType().compare("string") == 0)
		{
			db.persist(boost::dynamic_pointer_cast<UniPAX::StringSampleData>(data));
		}
		else if (data->getValueType().compare("bool") == 0)
		{
			db.persist(boost::dynamic_pointer_cast<UniPAX::BoolSampleData>(data));
		}
		else if (data->getValueType().compare("double") == 0)
		{
			db.persist(boost::dynamic_pointer_cast<UniPAX::DoubleSampleData>(data));
		}
		else if (data->getValueType().compare("double-matrix") == 0)
		{
			db.persist(boost::dynamic_pointer_cast<UniPAX::DoubleMatrixSampleData>(data));
		}
		//db.persist<UniPAX::SampleData>(*data);
//		odb::transaction t (db.begin ());
//		db.persist(*data);
//		t.commit ();
	}
}

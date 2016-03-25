#include <UNIPAX/KERNEL/EXT/ResultObject.h>
#include <iterator>
#include<set>
#include <algorithm>
#include <odb/mysql/database.hxx>

UniPAX::IDSetBlob::IDSetBlob()
{
}

UniPAX::IDSetBlob::IDSetBlob(const UniPAX::IDSetBlob & arg) :
		  ids(arg.ids)
{
}

UniPAX::IDSetBlob & UniPAX::IDSetBlob::operator =(const UniPAX::IDSetBlob & arg)
{
	ids	= arg.ids;
	return *this;
}

UniPAX::IDSetBlob::IDSetBlob(const std::vector<UnipaxId> & v)
{
	*this =v;
}

UniPAX::IDSetBlob & UniPAX::IDSetBlob::operator =(const std::vector<UnipaxId> & v)
{
	std::cerr << "UniPAX::IDSetBlob: Serializing vector<UnipaxId> of size: " << v.size() << std::endl;
	ids.resize((BlobBuffer::size_type) sizeof(UnipaxId) * v.size());
	std::memcpy(ids.data(), v.data(), sizeof(UnipaxId) * v.size());
	std::cerr << "UniPAX::IDSetBlob: to vector<char> of size: " << ids.size() << std::endl;
	return *this;
}

UniPAX::IDSetBlob::~IDSetBlob()
{
}

std::vector<UnipaxId> UniPAX::IDSetBlob::inflate() const
{
	std::cout << "UniPAX::IDSetBlob: Deserializing vector<char> of size: " << ids.size() << std::endl;
	std::vector<UnipaxId> v(ids.size()/sizeof(UnipaxId));
	std::memcpy(v.data(), ids.data(), sizeof(UnipaxId) * v.size());
	std::cout << "UniPAX::IDSetBlob: to vector<UnipaxId> of size: " << v.size() << std::endl;
	return v;
}

const UniPAX::IDSetBlob::BlobBuffer & UniPAX::IDSetBlob::getBlob() const
{
	return ids;
}

void UniPAX::IDSetBlob::setBlob(UniPAX::IDSetBlob::BlobBuffer blob)
{
	ids = blob;
}

UniPAX::ResultObject::ResultObject(std::string _constituting_query, UnipaxTime _creation_time) : UniPAX::UPBase(),
		//result_id(_result_id),
		constituting_query(_constituting_query),
		creation_time(_creation_time),
		size(0)
{
}

UniPAX::ResultObject::ResultObject(const UniPAX::ResultObject & arg) : UniPAX::UPBase(arg),
		description(arg.description),
		constituting_query(arg.constituting_query),
		creation_time(arg.creation_time),
		data_series(arg.data_series),
		//		id_data_series(arg.id_data_series),
		//graph(arg.graph),
		object_ids(arg.object_ids),
		size(arg.size)
{
}

UniPAX::ResultObject & UniPAX::ResultObject::operator =(const UniPAX::ResultObject & arg)
{
	UniPAX::UPBase::operator =(arg);
	description = arg.description;
	constituting_query = arg.constituting_query;
	creation_time = arg.creation_time;
	data_series = arg.data_series;
//	id_data_series = arg.id_data_series;
	//    graph(arg.graph);
	object_ids = arg.object_ids;
	size = arg.size;

	return *this;
}

UniPAX::ResultObject::~ResultObject()
{
}

UniPAX::ResultObject UniPAX::ResultObject::union_(const UniPAX::ResultObject & arg)
{
	std::stringstream ss;
	ss << "union(" << getUnipaxId() << "," << arg.getUnipaxId() << ")";
	UniPAX::ResultObject result(ss.str() , boost::posix_time::ptime(micro_sec::universal_time()));
	//result.data_series = arg.data_series;
	//result.graph = ... ;
	result.object_ids = object_ids;
	for (std::set<UnipaxId>::const_iterator it = arg.object_ids.begin(); it != arg.object_ids.end(); ++it)
	{
		result.object_ids.insert(*it);
	}
	result.size = result.object_ids.size();
	return result;
}

UniPAX::ResultObject UniPAX::ResultObject::operator +(const UniPAX::ResultObject & arg)
{
	return this->union_(arg);
}

UniPAX::ResultObject UniPAX::ResultObject::intersection_(const UniPAX::ResultObject & arg)
{
	std::stringstream ss;
	ss << "intersection(" << getUnipaxId() << "," << arg.getUnipaxId() << ")";
	UniPAX::ResultObject result(ss.str() , boost::posix_time::ptime(micro_sec::universal_time()));
	//result.data_series = arg.data_series;
	//result.graph = ... ;

	for (std::set<UnipaxId>::const_iterator it = arg.object_ids.begin(); it != arg.object_ids.end(); ++it)
	{
		if (object_ids.find(*it) != object_ids.end())
			result.object_ids.insert(*it);
	}
	result.size = result.object_ids.size();
	return result;
}

UniPAX::ResultObject UniPAX::ResultObject::operator &&(const UniPAX::ResultObject & arg)
{
	return this->intersection_(arg);
}

UniPAX::ResultObject UniPAX::ResultObject::difference_(const UniPAX::ResultObject & arg)
{
	std::stringstream ss;
	ss << "difference(" << getUnipaxId() << "," << arg.getUnipaxId() << ")";
	UniPAX::ResultObject result(ss.str() , boost::posix_time::ptime(micro_sec::universal_time()));
	//result.data_series = arg.data_series;
	//result.graph = ... ;

	for (std::set<UnipaxId>::const_iterator it = object_ids.begin(); it != object_ids.end(); ++it)
	{
		if (arg.object_ids.find(*it) == arg.object_ids.end())
			result.object_ids.insert(*it);
	}

	result.size = result.object_ids.size();

	return result;
}

UniPAX::ResultObjectPtr UniPAX::ResultObject::clone()
{
	UniPAX::ResultObjectPtr lhv(new UniPAX::ResultObject(*this));
	//lhv.creation_time(micro_sec::universal_time());
	return lhv;
}

UniPAX::ResultObject UniPAX::ResultObject::operator -(const UniPAX::ResultObject & arg)
{
	return this->difference_(arg);
}

void UniPAX::ResultObject::setConstitutingQuery(std::string query)
{
	constituting_query = query;
}

void UniPAX::ResultObject::setCreationTime(UnipaxTime time)
{
	creation_time = time;
}

const std::string UniPAX::ResultObject::getDescription() const
{
	return description;
}

std::string UniPAX::ResultObject::getDescription()
{
	return description;
}
void UniPAX::ResultObject::setDescription(std::string _description)
{
	description = _description;
}

const unsigned long UniPAX::ResultObject::getSize() const
{
	return size;
}

unsigned long UniPAX::ResultObject::getSize()
{
	return size;
}

const std::string UniPAX::ResultObject::getConstitutingQuery() const
{
	return constituting_query;
}

const UnipaxTime UniPAX::ResultObject::getCreationTime() const
{
	return creation_time;
}

const UnipaxPtr<UniPAX::Series>::type UniPAX::ResultObject::getDataSeries() const
{
	return data_series;
}

UnipaxPtr<UniPAX::Series>::type UniPAX::ResultObject::getDataSeries()
{
	return data_series;
}

void UniPAX::ResultObject::setDataSeries(UnipaxPtr<UniPAX::Series>::type _data_series)
{
	data_series = _data_series;
}

const std::set<UnipaxId> & UniPAX::ResultObject::getObjectIds() const
{
	return object_ids;
}

std::set<UnipaxId> & UniPAX::ResultObject::getObjectIds()
{
	return object_ids;
}

void UniPAX::ResultObject::setObjectIds(std::set<UnipaxId> _object_ids)
{
	object_ids = _object_ids;
	size = object_ids.size();
}

void UniPAX::ResultObject::init (odb::callback_event e, odb::database& db)
{
	std::cout << "init ResultObject" << std::endl;
	if (e == odb::callback_event::post_load)
	{
		object_ids.clear();

		UniPAX::IDSetBlob blob;
		std::vector<UnipaxId> tmp;
		for (std::vector<UniPAX::IDSetBlob::BlobBuffer>::iterator it = object_ids_blobs.begin(); it != object_ids_blobs.end(); ++it)
		{
			blob.setBlob(*it);
			tmp = blob.inflate();
			for (std::vector<UnipaxId>::iterator it2 = tmp.begin(); it2 != tmp.end(); ++it2)
			{
				if (!object_ids.insert(*it2).second)
					std::cerr << "ResultObject::blobsToIds: ID already in set: " << *it2 << std::endl;
			}
			//object_ids.insert(tmp.begin(), tmp.end());
		}

		size = object_ids.size();
	}

}

void UniPAX::ResultObject::init (odb::callback_event e, odb::database& db) const
{
	std::cout << "init const ResultObject" << std::endl;
	if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
	{

		int ids_per_blob = 8000;

		const_cast<std::vector<IDSetBlob::BlobBuffer>& >(object_ids_blobs).clear();
		std::vector<UnipaxId> v(object_ids.begin(), object_ids.end());
		std::vector<UnipaxId>::size_type chunks = v.size() / ids_per_blob;
		const_cast<std::vector<IDSetBlob::BlobBuffer>& >(object_ids_blobs).reserve(chunks+1);
		for (std::vector<UnipaxId>::size_type i=0; i != chunks; ++i)
		{
			const_cast<std::vector<IDSetBlob::BlobBuffer>& >(object_ids_blobs).push_back(UniPAX::IDSetBlob(std::vector<UnipaxId>(v.begin()+i*ids_per_blob,
					v.begin()+(i+1)*ids_per_blob)).getBlob());
		}
		if (chunks * ids_per_blob < v.size())
		{
			const_cast<std::vector<IDSetBlob::BlobBuffer>& >(object_ids_blobs).push_back(UniPAX::IDSetBlob(std::vector<UnipaxId>(v.begin()+chunks*ids_per_blob,
					v.end())).getBlob());
		}

	}
}

bool UniPAX::ResultObject::isEmpty()
{
	return object_ids.empty();
}

bool UniPAX::ResultObject::merge(UniPAX::ResultObject& object)
{
	return false;
}

bool UniPAX::ResultObject::update(UniPAX::PersistenceManager& manager)
{
	return true;
}

bool UniPAX::ResultObject::setAttribute(std::string& attribute, std::string& value, UniPAX::PersistenceManager& manager)
{
	if (UniPAX::UPBase::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute, "constituting_query"))
	{
		constituting_query = value;
		return true;
	}

	if (boost::iequals(attribute, "creation_time"))
	{
		creation_time = boost::posix_time::from_iso_string(value);
		return true;
	}

	if (boost::iequals(attribute, "description"))
	{
		description = value;
		return true;
	}

	if (boost::iequals(attribute, "object_ids"))
	{
		UnipaxId tmp;
		if (!UniPAX::PersistenceManager::convertAttribute(value,tmp))
			return false;
		object_ids.insert(tmp);
		size = object_ids.size();
		return true;
	}

	if (boost::iequals(attribute,"#data_series"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		UnipaxPtr<UniPAX::UPBase>::type object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "ResultObject::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		data_series = boost::dynamic_pointer_cast<UniPAX::Series>(object);
		return true;
	}

	return false;
}

bool UniPAX::ResultObject::getAttribute(std::vector<std::pair<std::string,std::string> >& value, UniPAX::PersistenceManager& manager)
{
	if (!UniPAX::UPBase::getAttribute(value, manager))
		return false;

	value.push_back(std::pair<std::string,std::string>("constituting_query", constituting_query));
	value.push_back(std::pair<std::string,std::string>("creation_time", boost::posix_time::to_iso_string(creation_time)));
	value.push_back(std::pair<std::string,std::string>("description", this->description));
	std::string tmp;
	for (std::set<UnipaxId>::const_iterator it = object_ids.begin(); it != object_ids.end(); it++)
	{
		if (!UniPAX::PersistenceManager::convertAttribute(*it, tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("object_ids", tmp));
		tmp.clear();
	}
	if (data_series == 0)
	{
		value.push_back(std::pair<std::string,std::string>("#data_series", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(data_series, tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#data_series", tmp));

	}

	return true;
}

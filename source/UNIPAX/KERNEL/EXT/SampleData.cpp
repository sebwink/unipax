#include<UNIPAX/KERNEL/EXT/SampleData.h>

#include <QtCore/qstring.h>


const size_t UniPAX::SampleDataBase::max_chars;

UniPAX::SampleDataBase::SampleDataBase() : id_(), blob()
{
}

UniPAX::SampleDataBase::SampleDataBase(const UniPAX::SampleDataBase & arg) : id_(arg.id_), blob(arg.blob)
{
}

UniPAX::SampleDataBase::~SampleDataBase()
{
}

UniPAX::SampleData::SampleData() : SampleDataBase()
{
}

UniPAX::SampleData::SampleData(const UniPAX::SampleData & arg) : SampleDataBase(arg)
{
}

UniPAX::SampleData::~SampleData()
{
}

UniPAX::StringSampleData::StringSampleData() : UniPAX::SampleData(), values()
{

}

UniPAX::StringSampleData::StringSampleData(std::vector<SampleDataType> & _data) : UniPAX::SampleData(), values(_data)
{

}

UniPAX::StringSampleData::StringSampleData(const StringSampleData & arg) : UniPAX::SampleData(arg), values(arg.values)
{
}

UniPAX::StringSampleData::~StringSampleData()
{
}

void UniPAX::StringSampleData::init(odb::callback_event e, odb::database& db)
{
	if (e == odb::callback_event::post_load)
	{
		// blobs of max_package_size
		std::stringstream ss;
		for (const_blob_it it = blob.begin(); it != blob.end(); it++)
		{
			ss << it->data();
		}
		boost::archive::text_iarchive ia(ss);
		ia >> *this;
	}
}

void UniPAX::StringSampleData::init(odb::callback_event e, odb::database& db) const
{
	if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
	{
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa << *this;

		std::string data(ss.str());

		const_cast<StringSampleData*>(this)->blob.clear();
		Blob buffer(max_chars);
		for (int i=0; i*max_chars < data.size(); i++)
		{
			int range = std::min(max_chars, data.size() - i*max_chars); // range is either max_chars or rest of data
			std::memcpy(buffer.data(), data.c_str() + i*max_chars, range);
			const_cast<StringSampleData*>(this)->blob.push_back(buffer);
		}
	}

}

UniPAX::BoolSampleData::BoolSampleData() : UniPAX::SampleData(), values()
{

}

UniPAX::BoolSampleData::BoolSampleData(std::vector<SampleDataType> & _data) : UniPAX::SampleData(), values(_data)
{

}

UniPAX::BoolSampleData::BoolSampleData(const BoolSampleData & arg) : UniPAX::SampleData(arg), values(arg.values)
{
}

UniPAX::BoolSampleData::~BoolSampleData()
{

}


void UniPAX::BoolSampleData::init(odb::callback_event e, odb::database& db)
{
	if (e == odb::callback_event::post_load)
	{
		// blobs of max_package_size
		std::stringstream ss;
		for (const_blob_it it = blob.begin(); it != blob.end(); it++)
		{
			ss << it->data();
		}
		boost::archive::text_iarchive ia(ss);
		ia >> *this;
	}
}

void UniPAX::BoolSampleData::init(odb::callback_event e, odb::database& db) const
{
	if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
	{
//		std::stringstream ss;
//		boost::archive::text_oarchive oa(ss);
//		oa << *this;
//
//		std::string data = ss.str();
//
//		const_cast<BoolSampleData*>(this)->blob.clear();
//		const_cast<BoolSampleData*>(this)->blob.resize(data.size());
//
//		std::memcpy(const_cast<BoolSampleData*>(this)->blob.data(), data.c_str(), data.size());
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa << *this;

		std::string data(ss.str());

		const_cast<BoolSampleData*>(this)->blob.clear();
		Blob buffer(max_chars);
		for (int i=0; i*max_chars < data.size(); i++)
		{
			int range = std::min(max_chars, data.size() - i*max_chars); // range is either max_chars or rest of data
			std::memcpy(buffer.data(), data.c_str() + i*max_chars, range);
			const_cast<BoolSampleData*>(this)->blob.push_back(buffer);
		}
	}

}

UniPAX::DoubleSampleData::DoubleSampleData() : UniPAX::SampleData(), values()
{

}

UniPAX::DoubleSampleData::DoubleSampleData(std::vector<SampleDataType> & _data) : UniPAX::SampleData(), values(_data)
{

}

UniPAX::DoubleSampleData::DoubleSampleData(const DoubleSampleData & arg) : UniPAX::SampleData(arg), values(arg.values)
{
}

UniPAX::DoubleSampleData::~DoubleSampleData()
{

}


void UniPAX::DoubleSampleData::init(odb::callback_event e, odb::database& db)
{
	if (e == odb::callback_event::post_load)
	{
		// blobs of max_package_size
		std::stringstream ss;
		for (const_blob_it it = blob.begin(); it != blob.end(); it++)
		{
			ss << it->data();
		}
		boost::archive::text_iarchive ia(ss);
		ia >> *this;

//		std::stringstream ss(blob.data());
//		boost::archive::text_iarchive ia(ss);
//		ia >> *this;
	}
}

void UniPAX::DoubleSampleData::init(odb::callback_event e, odb::database& db) const
{
	if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
	{
//		std::stringstream ss;
//		boost::archive::text_oarchive oa(ss);
//		oa << *this;
//
//		std::string data = ss.str();
//
//		const_cast<DoubleSampleData*>(this)->blob.clear();
//		const_cast<DoubleSampleData*>(this)->blob.resize(data.size());
//
//		std::memcpy(const_cast<DoubleSampleData*>(this)->blob.data(), data.c_str(), data.size());
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa << *this;

		std::string data(ss.str());

		const_cast<DoubleSampleData*>(this)->blob.clear();
		Blob buffer(max_chars);
		for (int i=0; i*max_chars < data.size(); i++)
		{
			int range = std::min(max_chars, data.size() - i*max_chars); // range is either max_chars or rest of data
			std::memcpy(buffer.data(), data.c_str() + i*max_chars, range);
			const_cast<DoubleSampleData*>(this)->blob.push_back(buffer);
		}
	}
}


UniPAX::DoubleMatrixSampleData::DoubleMatrixSampleData() : UniPAX::SampleData(), values(), column_names()
{

}

UniPAX::DoubleMatrixSampleData::DoubleMatrixSampleData(int rows, int cols) : UniPAX::SampleData(), values(rows), column_names(cols)
{
	for (int i = 0; i < rows; ++i)
		values.push_back(SampleDataType());
}

UniPAX::DoubleMatrixSampleData::DoubleMatrixSampleData(std::vector<SampleDataType> & _data, std::vector<std::string> & _column_names) : UniPAX::SampleData(), values(_data), column_names(_column_names)
{

}

UniPAX::DoubleMatrixSampleData::DoubleMatrixSampleData(const DoubleMatrixSampleData & arg) : UniPAX::SampleData(arg), values(arg.values)
{
}

UniPAX::DoubleMatrixSampleData::~DoubleMatrixSampleData()
{

}


void UniPAX::DoubleMatrixSampleData::init(odb::callback_event e, odb::database& db)
{
	if (e == odb::callback_event::post_load)
	{
		// blobs of max_package_size
		std::stringstream ss;
		for (const_blob_it it = blob.begin(); it != blob.end(); it++)
		{
			ss << it->data();
		}
		boost::archive::text_iarchive ia(ss);
		ia >> *this;
//		std::stringstream ss(blob.data());
//		boost::archive::text_iarchive ia(ss);
//		ia >> *this;
	}
}

void UniPAX::DoubleMatrixSampleData::init(odb::callback_event e, odb::database& db) const
{
	if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
	{
//		std::stringstream ss;
//		boost::archive::text_oarchive oa(ss);
//		oa << *this;
//
//		std::string data = ss.str();
//
//		const_cast<DoubleMatrixSampleData*>(this)->blob.clear();
//		const_cast<DoubleMatrixSampleData*>(this)->blob.resize(data.size());
//
//		std::memcpy(const_cast<DoubleMatrixSampleData*>(this)->blob.data(), data.c_str(), data.size());
		std::stringstream ss;
		boost::archive::text_oarchive oa(ss);
		oa << *this;

		std::string data(ss.str());

		const_cast<DoubleMatrixSampleData*>(this)->blob.clear();
		Blob buffer(max_chars);
		for (int i=0; i*max_chars < data.size(); i++)
		{
			int range = std::min(max_chars, data.size() - i*max_chars); // range is either max_chars or rest of data
			std::memcpy(buffer.data(), data.c_str() + i*max_chars, range);
			const_cast<DoubleMatrixSampleData*>(this)->blob.push_back(buffer);
		}
	}

}



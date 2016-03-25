// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                               UNIPAX
// --------------------------------------------------------------------------
//  Copyright (C) 2011 -- Oliver Kohlbacher, Hans-Peter Lenhof
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 3 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Id:$
// $Author:$
// $Maintainer:$
// --------------------------------------------------------------------------
//
#ifndef SAMPLEDATA_H
#define SAMPLEDATA_H

#include<string>
#include <UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include <UNIPAX/KERNEL/EXT/UPBase.h>
#include <UNIPAX/KERNEL/EXT/UnitDefinition.h>
#include <odb/core.hxx>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

//#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


namespace UniPAX {

typedef std::vector<unsigned long> Dimension;

#pragma db object polymorphic callback(init)
class UNIPAX_EXPORT SampleDataBase
{
	friend class odb::access;
	friend class boost::serialization::access;

protected:

#pragma db id auto
	UnipaxId id_;

	typedef std::vector<char> Blob;

#pragma db value(SampleDataBase::Blob) type("LONGBLOB")
	std::vector<Blob> blob;
	typedef std::vector<Blob>::iterator blob_it;
	typedef std::vector<Blob>::const_iterator const_blob_it;

	virtual void init (odb::callback_event e, odb::database& db) = 0;
	virtual void init (odb::callback_event e, odb::database& db) const = 0;

public:

	static const size_t max_chars = 8000* sizeof(UnipaxId);

	SampleDataBase();

	SampleDataBase(const UniPAX::SampleDataBase & arg);

	virtual ~SampleDataBase() = 0;

	virtual std::string getValueType() = 0;

	//virtual bool isNumeric() = 0;

	//virtual Dimension getDimension() = 0;
};

//typedef UnipaxPtr<SampleDataBase>::type SampleDataBasePtr;

//#pragma db object callback(init)
#pragma db object abstract
class UNIPAX_EXPORT SampleData : public SampleDataBase
{
	friend class odb::access;
	friend class boost::serialization::access;

//protected:


//	virtual void init (odb::callback_event e, odb::database& db) = 0;
//	virtual void init (odb::callback_event e, odb::database& db) const = 0;


public:

	SampleData();

	SampleData(const SampleData & arg);

	virtual ~SampleData() = 0;

};

typedef UnipaxPtr<SampleDataBase>::type SampleDataPtr;

#pragma db object
class UNIPAX_EXPORT StringSampleData : public SampleData
{

	friend class odb::access;
	friend class boost::serialization::access;

public:
	typedef std::string SampleDataType;

protected:

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & values;
	}



	void init (odb::callback_event e, odb::database& db);
	void init (odb::callback_event e, odb::database& db) const;

public:

	StringSampleData();

	StringSampleData(std::vector<SampleDataType> & _data);

	StringSampleData(const StringSampleData & arg);

	~StringSampleData();

	std::string getValueType()
	{
		return "string";
	}


#pragma db transient
	std::vector<SampleDataType> values;
};

typedef UnipaxPtr<StringSampleData>::type StringSampleDataPtr;


#pragma db object
class UNIPAX_EXPORT BoolSampleData : public SampleData
{

	friend class odb::access;
	friend class boost::serialization::access;

public:
	typedef char SampleDataType;

protected:

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & values;
	}

	void init (odb::callback_event e, odb::database& db);
	void init (odb::callback_event e, odb::database& db) const;

public:

	BoolSampleData();

	BoolSampleData(std::vector<SampleDataType> & _data);

	BoolSampleData(const BoolSampleData & arg);

	~BoolSampleData();

	std::string getValueType()
	{
		return "bool";
	}


#pragma db transient
	std::vector<SampleDataType> values;
};

typedef UnipaxPtr<BoolSampleData>::type BoolSampleDataPtr;

#pragma db object
class UNIPAX_EXPORT DoubleSampleData : public SampleData
{

	friend class odb::access;
	friend class boost::serialization::access;

public:
	typedef double SampleDataType;

protected:
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & values;
	}



	void init (odb::callback_event e, odb::database& db);
	void init (odb::callback_event e, odb::database& db) const;

public:


	DoubleSampleData();

	DoubleSampleData(std::vector<SampleDataType> & _data);

	DoubleSampleData(const DoubleSampleData & arg);

	~DoubleSampleData();

	std::string getValueType()
	{
		return "double";
	}

#pragma db transient
	std::vector<SampleDataType> values;
};

typedef UnipaxPtr<DoubleSampleData>::type DoubleSampleDataPtr;



#pragma db object
class UNIPAX_EXPORT DoubleMatrixSampleData : public SampleData
{

	friend class odb::access;
	friend class boost::serialization::access;

public:
	typedef std::vector<double> SampleDataType;

protected:

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & column_names;
		ar & values;
	}



	void init (odb::callback_event e, odb::database& db);
	void init (odb::callback_event e, odb::database& db) const;

public:


	DoubleMatrixSampleData();

	DoubleMatrixSampleData(int rows, int cols);

	DoubleMatrixSampleData(std::vector<SampleDataType> & _data, std::vector<std::string> & _column_names);

	DoubleMatrixSampleData(const DoubleMatrixSampleData & arg);

	~DoubleMatrixSampleData();

	std::string getValueType()
	{
		return "double-matrix";
	}

#pragma db transient
	std::vector<std::string> column_names;

#pragma db transient
	std::vector<SampleDataType> values;
};

typedef UnipaxPtr<DoubleMatrixSampleData>::type DoubleMatrixSampleDataPtr;


}//end namespace UniPAX


#endif

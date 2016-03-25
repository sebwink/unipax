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
#ifndef SAMPLE_H
#define SAMPLE_H

#include<string>
#include <UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include <UNIPAX/KERNEL/EXT/UIBase.h>
#include <UNIPAX/KERNEL/EXT/UnitDefinition.h>
#include <UNIPAX/KERNEL/EXT/SampleData.h>
#include <odb/core.hxx>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <vector>

namespace UniPAX {

#pragma db object polymorphic callback(init)
class UNIPAX_EXPORT Sample : public UIBase
{

protected:

	std::string name;
	std::map<std::string, std::string> description_tags;

	#pragma db not_null
	SampleDataPtr data;


	//#pragma	 db type("LONGBLOB")
	//	QByteArray data_matrix;
	//
	//#pragma db transient
	//	UnipaxPtr<DataMatrix>::type dataMatrix;

	//	//#pragma db transient
	//	UnipaxPtr<UnitDefinition>::type unit;
	//	double error;

	friend class odb::access;
//		void init (odb::callback_event e, odb::database& db);
		void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Sample";
	}

	static std::string type() {
		return std::string("Sample");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idSample;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idSample;
	}

	Sample();

	Sample(const Sample & arg);

	Sample & operator =(const Sample & arg);

	virtual ~Sample();


	bool merge(Sample& object);

	bool update(PersistenceManager& manager);


	// name
	const std::string getName() const;
	std::string getName();
	void setName(std::string name);

	// description_tags
	const std::map<std::string, std::string> & getDescriptionTags() const;
	std::map<std::string, std::string> & getDescriptionTags();
	void setDescriptionTags(std::map<std::string, std::string> _description_tags);
	void setDescriptionTag(std::string tag, std::string value);

	//	// data_matrix
	//	const UnipaxPtr<DataMatrix>::type & getDataMatrix() const;
	//	UnipaxPtr<DataMatrix>::type & getDataMatrix();
	//	void setDataMatrix(UnipaxPtr<DataMatrix>::type _dataMatrix);

	// data_matrix
	const SampleDataPtr getSampleData() const;

	SampleDataPtr getSampleData();

	void setSampleData(SampleDataPtr _data);

	//	// unit
	//	const UnipaxPtr<UnitDefinition>::type & getUnit() const;
	//	UnipaxPtr<UnitDefinition>::type & getUnit();
	//	void setUnit(UnipaxPtr<UnitDefinition>::type _unit);

	//	// error
	//	const double getError() const;
	//	double getError();
	//	void setError(double _error);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Sample

typedef UnipaxPtr<Sample>::type SamplePtr;


}//end namespace UniPAX


#endif

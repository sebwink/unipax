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
#ifndef UNIPAX_KERNEL_EXT_RESULTOBJECT_H
#define UNIPAX_KERNEL_EXT_RESULTOBJECT_H

#include <UNIPAX/KERNEL/EXT/UPBase.h>
#include <UNIPAX/KERNEL/EXT/Series.h>
#include <UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h> 

#include <odb/core.hxx>
#include <odb/callback.hxx>
#include <odb/boost/date-time/exceptions.hxx>

#include <set>
#include <string>

namespace UniPAX {

class UNIPAX_EXPORT IDSetBlob
{
	friend class odb::access;
public:
	IDSetBlob();
	IDSetBlob(const IDSetBlob & arg);
	IDSetBlob & operator =(const IDSetBlob & arg);
	IDSetBlob(const std::vector<UnipaxId> & v);
	IDSetBlob & operator =(const std::vector<UnipaxId> & v);
	virtual ~IDSetBlob();

	std::vector<UnipaxId> inflate() const;

	typedef std::vector<char> BlobBuffer;

	const BlobBuffer & getBlob() const;

	void setBlob(BlobBuffer blob);

protected:

	BlobBuffer ids;
};

typedef UnipaxPtr<IDSetBlob>::type IDSetBlobPtr;

class ResultObject;
typedef UnipaxPtr<ResultObject>::type ResultObjectPtr;

#pragma db object polymorphic callback(init)
class UNIPAX_EXPORT ResultObject : public UPBase {

	friend class odb::access;
	friend class ObjectFactory;
	friend class PersistenceManager;
	friend class DBConnector;
	friend class ResultObjectServerHandler;

	void init(odb::callback_event e, odb::database& db);
	void init(odb::callback_event e, odb::database& db) const;

protected:

	ResultObject() {
	}

	// member variables

	std::string description; // optional
	std::string constituting_query; // required, set during creation

#pragma db type("TIMESTAMP") not_null
	UnipaxTime creation_time; // required, set during creation

	// one out of the following must not be a NULL pointer:

	//	#pragma db load(lazy) update(always)
	//	odb::section data_;

	//	UnipaxId id_data_series;
	//	#pragma db section(data_)
	UnipaxPtr<UniPAX::Series>::type data_series; // series data

#pragma db transient
	std::set<UnipaxId> object_ids; // ids of the contained objects / objects processed

	unsigned long size;

#pragma db value(IDSetBlob::BlobBuffer) type("BLOB")
	std::vector<IDSetBlob::BlobBuffer> object_ids_blobs;


	void setCreationTime(UnipaxTime time);

public:

	virtual std::string getType() {
		return "ResultObject";
	}

	static std::string type() {
		return "ResultObject";
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idResultObject;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idResultObject;
	}

	ResultObject(std::string constituting_query,
			UnipaxTime creation_time);
	ResultObject(const ResultObject & arg);
	ResultObject & operator =(const ResultObject & arg);
	virtual ~ResultObject();

	ResultObject union_(const ResultObject & arg);
	ResultObject operator +(const ResultObject & arg);

	ResultObject intersection_(const ResultObject & arg);
	ResultObject operator &&(const ResultObject & arg);

	ResultObject difference_(const ResultObject & arg);
	ResultObject operator -(const ResultObject & arg);

	ResultObjectPtr clone();

	const std::string getDescription() const;
	std::string getDescription();
	void setDescription(std::string desc);

	const unsigned long getSize() const;
	unsigned long getSize();

	void setConstitutingQuery(std::string query);
	const std::string getConstitutingQuery() const;

	const UnipaxTime getCreationTime() const;

	const UnipaxPtr<UniPAX::Series>::type getDataSeries() const;
	UnipaxPtr<UniPAX::Series>::type getDataSeries();
	void setDataSeries(UnipaxPtr<UniPAX::Series>::type _data_series);

	/*const UnipaxPtr<UniPAX::Graph>::type getGraph() const;
	 UnipaxPtr<UniPAX::Graph>::type getGraph();
	 void setGraph(UnipaxPtr<UniPAX::Graph>::type _graph);*/




	const std::set<UnipaxId> & getObjectIds() const;
	std::set<UnipaxId> & getObjectIds();
	void setObjectIds(std::set<UnipaxId> _object_ids);

	bool isEmpty();

	virtual bool merge(ResultObject& object);
	virtual bool update(PersistenceManager& manager);
	virtual bool setAttribute(std::string& attribute, std::string& value,
			PersistenceManager& manager);
	virtual bool getAttribute(
			std::vector<std::pair<std::string, std::string> >& value,
			PersistenceManager& manager);

};

} // end namespace
#endif          // UNIPAX_KERNEL_EXT_RESULTOBJECT_H

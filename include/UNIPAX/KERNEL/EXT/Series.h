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
#ifndef UNIPAX_SERIES_H
#define UNIPAX_SERIES_H

#include <UNIPAX/KERNEL/BIOPAX/Entity.h>
#include <UNIPAX/KERNEL/EXT/UIBase.h>
#include <UNIPAX/KERNEL/EXT/Sample.h>
#include <UNIPAX/KERNEL/EXT/IdMapping.h>
#include <UNIPAX/COMMON/PersistenceManager.h>
#include <UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>

#include <odb/core.hxx>
#include <odb/callback.hxx>

#include <map>
#include <vector>
#include <string>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Series : public UIBase {

protected:

	std::map<std::string, std::string> description_tags;

	//std::vector<UnipaxId> id_idMapping_list;
	//#pragma db transient
	std::vector<UnipaxPtr<IdMapping>::type > idMapping_list;

	//std::vector<UnipaxId> id_sample_list;
	//#pragma db transient
	std::vector<UnipaxPtr<Sample>::type > sample_list;

	std::string name;
	std::string description;

	std::vector<UnipaxPtr<Xref>::type > xref;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Series";
	}

	static std::string type() {
		return std::string("Series");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idSeries;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idSeries;
	}

	Series();

	Series(const Series & arg);

	Series & operator =(const Series & arg);

	virtual ~Series();

	virtual bool merge(Series& object);
	virtual bool update(PersistenceManager& manager);

	// description_tags
	virtual std::map<std::string, std::string> & getDescriptionTags();

	virtual const std::map<std::string, std::string> & getDescriptionTags() const;

	virtual void setDescriptionTags(std::map<std::string, std::string> _description_tags);

	virtual void setDescriptionTag(std::string tag, std::string value);

	// idMapping_list
	virtual std::vector<UnipaxPtr<IdMapping>::type > & getIdMappingList();

	virtual const std::vector<UnipaxPtr<IdMapping>::type > & getIdMappingList() const;

	virtual void setIdMappingList(std::vector<UnipaxPtr<IdMapping>::type > _idMapping_list);

	virtual void addIdMapping(UnipaxPtr<IdMapping>::type _idMapping);

	// sample_list
	virtual const std::vector<UnipaxPtr<Sample>::type > & getSampleList() const;

	virtual std::vector<UnipaxPtr<Sample>::type > & getSampleList();

	virtual void setSampleList(std::vector<UnipaxPtr<Sample>::type > _sample_list);

	virtual void addSample(UnipaxPtr<Sample>::type _sample);


	virtual bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	virtual bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

	const std::vector<UnipaxPtr<Xref>::type > & getXrefs() const;
	std::vector<UnipaxPtr<Xref>::type > & getXrefs();
	void addXref(UnipaxPtr<Xref>::type  _xref);
	void setXrefs(std::vector<UnipaxPtr<Xref>::type > _xrefs);

	const std::string & getName() const;
	std::string & getName();
	void setName(std::string _name);

	const std::string & getDescription() const;
	std::string & getDescription();
	void setDescription(std::string _desc);

private:
	typedef UPBase super;

};  //end class Series

typedef UnipaxPtr<Series>::type SeriesPtr;


}//end namespace UniPAX


#endif // UNIPAX_SERIES_H

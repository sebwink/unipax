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
#ifndef BINDINGFEATURE_H
#define BINDINGFEATURE_H
//Begin section for file BindingFeature.h
//TODO: Add definitions that you want preserved
//End section for file BindingFeature.h
#include<UNIPAX/KERNEL/BIOPAX/EntityFeature.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<odb/callback.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT BindingFeature : public EntityFeature {

protected:

	bool intraMolecular;

//	// std::vector<unsigned long long> id_bindsTo;
////#pragma db transient
	std::vector<UnipaxPtr<BindingFeature>::type> bindsTo;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "BindingFeature";
	}

	static std::string type() {
		return std::string("BindingFeature");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idBindingFeature;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idBindingFeature;
	}

	BindingFeature();

	BindingFeature(const BindingFeature & arg);

	BindingFeature & operator =(const BindingFeature & arg);

	virtual ~BindingFeature();

	virtual bool merge(BindingFeature& object);
	virtual bool update(PersistenceManager& manager);

	//get intraMolecular
	virtual bool getIntraMolecular();

	virtual const bool getIntraMolecular() const;

	//set intraMolecular
	virtual void setIntraMolecular(bool _intraMolecular);


	//get bindsTo
	virtual const std::vector<UnipaxPtr<BindingFeature>::type> & getBindsTos() const;

	virtual std::vector<UnipaxPtr<BindingFeature>::type> getBindsTos();

	virtual void setBindsTos(std::vector<UnipaxPtr<BindingFeature>::type> _bindsTos);

	virtual void addBindsTo(UnipaxPtr<BindingFeature>::type _bindsTo);



	virtual bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	virtual bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef EntityFeature super;

};  //end class BindingFeature

typedef UnipaxPtr<BindingFeature>::type BindingFeaturePtr;


}//end namespace UniPAX


#endif

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


#ifndef UNIPAX_COMMON_KERNELCOLLECTOR_H
#define UNIPAX_COMMON_KERNELCOLLECTOR_H

#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
//#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<string>
#include<vector>
#include<map>
#include<iostream>


namespace UniPAX
{

class UNIPAX_EXPORT KernelCollector : virtual public PersistenceManager {

public:

	KernelCollector();

	KernelCollector(const KernelCollector & arg);

	KernelCollector & operator =(const KernelCollector & arg);

	~KernelCollector();

	// get the id of the object
	bool getId(boost::shared_ptr<UniPAX::UPBase> object, std::string& id);

	// collect all object instances linked to object
	bool collect(boost::shared_ptr<UniPAX::UPBase> object);

	bool collect(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects);


};  //end class KernelCollector

}//end namespace UniPAX

#endif

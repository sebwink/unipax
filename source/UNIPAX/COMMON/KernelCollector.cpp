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


#include<UNIPAX/COMMON/KernelCollector.h>
#include<iostream>
#include<sstream>
#include<boost/algorithm/string.hpp>
#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<UNIPAX/KERNEL/BIOPAX/PathwayStep.h>
#include<UNIPAX/KERNEL/BIOPAX/BiochemicalPathwayStep.h>


UniPAX::KernelCollector::KernelCollector() : UniPAX::PersistenceManager()  {
}

UniPAX::KernelCollector::KernelCollector(const KernelCollector & arg) : UniPAX::PersistenceManager(arg)
{
}

UniPAX::KernelCollector & UniPAX::KernelCollector::operator =(const KernelCollector & arg)
{
	UniPAX::PersistenceManager::operator=(arg);

	return *this;
}

UniPAX::KernelCollector::~KernelCollector()  {
}

bool UniPAX::KernelCollector::collect(boost::shared_ptr<UniPAX::UPBase> object)
{
	std::string value;
	return getId(object, value);
}

bool UniPAX::KernelCollector::collect(std::vector<boost::shared_ptr<UniPAX::UPBase> > objects)
{
	bool okay = true;

	for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::const_iterator it(objects.begin()); it != objects.end(); it++)
	{
		std::string value;
		okay &= getId(*it, value);
	}

	return okay;
}

bool UniPAX::KernelCollector::getId(boost::shared_ptr<UniPAX::UPBase> object, std::string& id)
{
	std::vector<std::pair<std::string,std::string> > value;
	std::map<boost::shared_ptr<UniPAX::UPBase>, std::string>::iterator object_search = pointer_id_.find(object);


	if (object_search == pointer_id_.end())
	{
		// this is due to the misuse of pathwayOrder attribute in pathways by external data provider Reactome
		if (skip_PathwaySteps && object->getType() == "PathwayStep")
		{
			return true;
		}
		else if (skip_PathwaySteps && object->getType() == "BiochemicalPathwayStep")
		{
			return true;
		}

//		std::cout << "object: " << object << std::endl;
//		std::cout << "type: " << object->getType() << std::endl;
		std::stringstream ss;
		ss << object->getUnipaxId();
		ss >> id;
//		std::cout << "id: " << id << std::endl;
		pointer_id_[object] = id;
		pointer_map_[id] = object;
		pointer_type_map_[id] = object->getType();

		object->getAttribute(value,*this);
	}
	else
	{
		id = object_search->second;
	}

	return true;
}

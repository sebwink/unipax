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


#ifndef UNIPAX_PERSISTENCE_DBMANAGER_H
#define UNIPAX_PERSISTENCE_DBMANAGER_H

#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include<UNIPAX/COMMON/KernelCollector.h>

#include<UNIPAX/PERSISTENCE/ODBWorker.h>

#include<UNIPAX/IMPORT/UniProtReader.h>
#include<UNIPAX/KERNEL/Kernel.h>
#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<string>
#include<memory>
#include<map>

#include<odb/database.hxx>
#include<odb/transaction.hxx>

namespace UniPAX
{

class UNIPAX_EXPORT DBManager
{

public:

	DBManager(bool cached = true);

	DBManager(const DBManager & arg);

	DBManager & operator =(const DBManager & arg);

	virtual ~DBManager();

	void setDBCredentials(const std::string user, const std::string password, const std::string host, const int port, const std::string db);

	UPBasePtr getObjectByID(UnipaxId id);

	bool getObjectsByIDs(std::vector<UPBasePtr > & result, std::vector<UnipaxId> & ids);

	bool removeObjectsFromCache(std::vector<UnipaxId> & ids);

	bool persist(PersistenceManager& manager);
	bool update(PersistenceManager& manager);

	bool persist(UPBasePtr object);
	bool update(UPBasePtr object);

	virtual bool isValid(UnipaxId id);

	virtual bool assignIds(PersistenceManager& manager);
	virtual bool assignId(UPBasePtr obj);

	virtual bool listPathways(std::multimap<std::string, std::string>& pathways);
	virtual bool listPathwaysById(std::map<UnipaxId, std::vector<UnipaxId> >& pathways);
	virtual PathwayPtr getPathway(std::string db_name, std::string pathway_name);

	virtual bool getObjectsByType(std::vector<UPBasePtr > & result, std::string type, bool recursive = false);
	virtual bool getIdsByType(std::vector<UnipaxId> & result, std::string type, bool recursive = false);

	bool initDatabase();

	UnipaxPtr<odb::database>::type getOdbDatabase();

	UnipaxPtr<ODBWorker>::type getOdbWorker();

	static std::string getType(UnipaxId id, std::string defaultValue)
	{
		return UniPAX::Kernel::classType((UniPAX::ClassType::ID) (id >> 24), defaultValue);
	}

	static bool isType(UnipaxId id, ClassType::ID type)
	{
		return (id >> 24) == type;
	}

	static UnipaxId getBase(std::string type)
	{
		UniPAX::ClassType::ID id = UniPAX::Kernel::classType(type);
		if (id != UniPAX::ClassType::END_ENUM)
		{
			return id << 24;
		}
		else
		{
			return ULLONG_MAX;
		}
	}

protected:

	virtual bool createDatabase(UnipaxPtr<odb::database>::type& database);

	virtual bool updateMaxIds();

	UnipaxPtr<ODBWorker>::type odb_worker;

	UnipaxPtr<odb::database>::type odb_db;

	std::string user;
	std::string password;
	std::string host;
	int port;
	std::string db;

	bool cache_enabled;

	std::map<std::string, UnipaxId> db_ids;

};  //end class MySQLManager

typedef UnipaxPtr<DBManager>::type DBManagerPtr;

}//end namespace UniPAX

#endif          // UNIPAX_PERSISTENCE_DBMANAGER_H

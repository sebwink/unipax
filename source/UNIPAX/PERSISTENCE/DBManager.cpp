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


#include<UNIPAX/PERSISTENCE/DBManager.h>
#include<map>
#include<iostream>
#include<odb/exceptions.hxx>
#include<boost/algorithm/string.hpp>

#include<memory>


UniPAX::DBManager::DBManager(bool cached) : cache_enabled(cached), port(0)  {
}

UniPAX::DBManager::DBManager(const DBManager & arg) : user(arg.user), password(arg.password), db(arg.db), port(arg.port), host(arg.host), cache_enabled(arg.cache_enabled)
{
}

UniPAX::DBManager & UniPAX::DBManager::operator =(const DBManager & arg)
{
				user = arg.user;
				password = arg.password;
				port = arg.port;
				db = arg.db;
				host = arg.host;
				cache_enabled = arg.cache_enabled;

				return *this;
}

UniPAX::DBManager::~DBManager()
{
}

void UniPAX::DBManager::setDBCredentials(const std::string user_, const std::string password_, const std::string host_, const int port_, const std::string db_)
{
				user = user_;
				password = password_;
				db = db_;
				host = host_;
				port = port_;

				return;
}


bool UniPAX::DBManager::createDatabase(boost::shared_ptr<odb::database>& database)
{
				std::cerr << "DBManager: Cannot create generic database. " << std::endl;

				return false;
}

bool UniPAX::DBManager::initDatabase()
{
        const unsigned short max_retry = 5;
				for (unsigned short retry_cnt=0; ; retry_cnt++)
				{
								try {
												if (odb_db.get() == 0)
												{
																if (createDatabase(odb_db))
																{
																				return true;
																}
																else
																				return false;
												}

												return true;
								}
								catch (const odb::recoverable& e)
								{
												if (retry_cnt == max_retry)
												{
												    std::cerr << "DBManager: Retry limit exceeded for odb_exception - " << e.what() << std::endl;  
												}
												std::cerr << "DBManager: odb_exception - " << e.what() << "\nRetrying..." << std::endl;
								}
				}
				return false;
}

bool UniPAX::DBManager::updateMaxIds()
{
				return false;
}

boost::shared_ptr<odb::database> UniPAX::DBManager::getOdbDatabase()
{
				return odb_db;
}

boost::shared_ptr<UniPAX::ODBWorker> UniPAX::DBManager::getOdbWorker()
{
				return odb_worker;
}

boost::shared_ptr<UniPAX::UPBase> UniPAX::DBManager::getObjectByID(UnipaxId id)
{
				if (initDatabase())
				{
								return odb_worker->load(id);
				}

				return boost::shared_ptr<UniPAX::UPBase>();
}

bool UniPAX::DBManager::getObjectsByIDs(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & ids)
{

				if (initDatabase())
				{
								odb_worker->load(result, ids);

								return true;
				}

				return false;
}

bool UniPAX::DBManager::removeObjectsFromCache(std::vector<UnipaxId> & ids)
{

				if (initDatabase())
				{
								odb_worker->unload(ids);

								return true;
				}

				return false;
}


bool UniPAX::DBManager::update(PersistenceManager& manager)
{

				if (initDatabase())
				{
								// workaround for ODB persistence
								if (!assignIds(manager))
												return 0;

								std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > data = manager.getData();
								std::map<std::string, std::string> pointer_type_map_ = manager.getIdToType();
								std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator it;
								std::map<std::string, std::string>::iterator type_search;

								// update the objects

								std::vector<boost::shared_ptr<UniPAX::UPBase> > objects;
								for (it = data.begin(); it != data.end(); it++)
								{
												objects.push_back(it->second);
								}

								std::vector<bool> result = odb_worker->update(objects);
								for (unsigned int i = 0; i < result.size(); ++i) {
												if (result[i] == false)
																return false;
								}


								return true;
				}
				else
				{
								return false;
				}
}

bool UniPAX::DBManager::persist(boost::shared_ptr<UniPAX::UPBase> object)
{
				if (initDatabase())
				{
								if (odb_worker->persist(object) > 0)
												return true;
				}

				return false;
}

bool UniPAX::DBManager::persist(PersistenceManager& manager)
{
				if (initDatabase())
				{
								// workaround for ODB persistence
								if (!assignIds(manager))
												return 0;

								std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > data = manager.getData();
								std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator it;

								// make the objects persistent

								std::vector<boost::shared_ptr<UniPAX::UPBase> > objects;
								for (it = data.begin(); it != data.end(); it++)
								{
												objects.push_back(it->second);
								}

								std::vector<UnipaxId> ids = odb_worker->persist(objects);
								for (unsigned int i = 0; i < ids.size(); ++i) {
												if (ids[i] == 0)
																return false;
								}

								return true;
				}
				else
				{
								return false;
				}

}

bool UniPAX::DBManager::update(boost::shared_ptr<UniPAX::UPBase> object)
{
				if (initDatabase())
				{
								return odb_worker->update(object);
				}
				else
				{
								return false;
				}

}

bool UniPAX::DBManager::isValid(UnipaxId id)
{
				std::cerr << "UniPAX::DBManager::isValid is a basis class method." << std::endl;
				return false;
}

bool UniPAX::DBManager::assignIds(PersistenceManager& manager)
{
				return false;
}

bool UniPAX::DBManager::assignId(boost::shared_ptr<UniPAX::UPBase> manager)
{
				return false;
}

bool UniPAX::DBManager::listPathways(std::multimap<std::string, std::string>& pathways)
{
				return false;
}

bool UniPAX::DBManager::listPathwaysById(std::map<UnipaxId, std::vector<UnipaxId> >& pathways)
{
				return false;
}

boost::shared_ptr<UniPAX::Pathway> UniPAX::DBManager::getPathway(std::string db_name, std::string pathway_name)
{
				return boost::shared_ptr<UniPAX::Pathway>();

}

bool UniPAX::DBManager::getObjectsByType(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::string type, bool recursive)
{
				return false;
}

bool UniPAX::DBManager::getIdsByType(std::vector<UnipaxId> & ids, std::string type, bool recursive)
{
				return false;
}


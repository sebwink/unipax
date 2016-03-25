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


#ifndef UNIPAX_COMMON_PERSISTENCEMANAGER_H
#define UNIPAX_COMMON_PERSISTENCEMANAGER_H

#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<string>
#include<vector>
#include<map>
#include<iostream>

namespace UniPAX
{

class UPBase;
class ImportSource;
class DBManager;

class UNIPAX_EXPORT PersistenceManager {

public:

	PersistenceManager();

	PersistenceManager(const PersistenceManager & arg);

	PersistenceManager & operator =(const PersistenceManager & arg);

	virtual ~PersistenceManager();

	friend std::ostream& operator<<(std::ostream& os, const PersistenceManager& manager);


	/*
	 * \brief returns pointer to instance of id <id> (and type <type>) if existent or null pointer.
	 */
	virtual boost::shared_ptr<UniPAX::UPBase> getInstance(std::string id, std::string type = "");
	/*
	 * \brief returns type to instance of id <id>.
	 */
	const std::string getInstanceType(const std::string id);

	// instance management
	boost::shared_ptr<UniPAX::UPBase> createInstance(std::string id, std::string type);
	boost::shared_ptr<UniPAX::UPBase> createInstance(std::string id, std::string type, bool& created);

	template<class T> boost::shared_ptr<T> createInstance(std::string id, bool& created) {
		// check if object already exists
		std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator object_search = pointer_map_.find(id);
		std::map<std::string, std::string>::iterator type_search = pointer_type_map_.find(id);

		created = false;

		if (object_search != pointer_map_.end())
		{
			if (type_search != pointer_type_map_.end())
			{
				if (type_search->second == T::type())
				{
					// found object of correct type
					return boost::dynamic_pointer_cast<T>(object_search->second);
				}
				else
				{
					// found object with this id but wrong type
					std::cerr << "PersistenceManager: Object (" << T::type() << ":" << id << ") already registered with for type " << type_search->second << "." << std::endl;
					return boost::shared_ptr<T>();
				}
			}
			// found object but no type !
			std::cerr << "PersistenceManager: Object (" << T::type() << ":" << id << ") already registered with no type." << std::endl;
			return boost::shared_ptr<T>();
		}

		created = true;

		boost::shared_ptr<T> instance = boost::shared_ptr<T>(new T);
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = T::type();

		return instance;
	}

	template<class T> bool registerInstance(std::string id, boost::shared_ptr<UniPAX::UPBase> object) {
		// check if object already exists
		std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator object_search = pointer_map_.find(id);
		std::map<std::string, std::string>::iterator type_search = pointer_type_map_.find(id);

		if (object_search == pointer_map_.end())
		{
			if (type_search == pointer_type_map_.end())
			{
				pointer_map_[id] = object;
				pointer_id_[object] = id;
				pointer_type_map_[id] = T::type();

				return true;
			}
		}

		return false;
	}

	// set attribute of an instance
	bool setAttribute(std::string id, std::string attribute, std::string value);
	// get attribute of an instance
	bool getAttribute(std::string id, std::vector<std::pair<std::string,std::string> >& value);

	// get the id of the object
	virtual bool getId(boost::shared_ptr<UniPAX::UPBase> object, std::string& id);

	// adds the object to manager
	bool add(boost::shared_ptr<UniPAX::UPBase> object, UniPAX::DBManager* db);
	bool update(boost::shared_ptr<UniPAX::UPBase> object);
	bool updateAll();

	// remove the object from manager
	bool remove(boost::shared_ptr<UniPAX::UPBase> object);

	// helper methods
	static bool convertAttribute(const std::string& value, UnipaxId& new_value);
	static bool convertAttribute(const std::string& value, int& new_value);
	static bool convertAttribute(const std::string& value, double& new_value);
	static bool convertAttribute(const std::string& value, bool& new_value);

	static bool convertAttribute(const UnipaxId& value, std::string& new_value);
	static bool convertAttribute(const int& value, std::string& new_value);
	static bool convertAttribute(const double& value, std::string& new_value);
	static bool convertAttribute(const bool& value, std::string& new_value);

	void skipPathwaySteps(bool flag);
	bool pathwayStepsSkipped();

	void setError(std::string msg);
	std::vector<std::string> getErrors();
	void clearErrors();
	void printErrors(std::ostream& out, bool clear);


	virtual int getInstanceCount();

	/*
	 * \brief returns a map of id to pointer of all objects registered in the PersistenceManager.
	 */
	std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >& getData();

	/*
	 * \brief returns a map of id to pointer of all objects registered in the PersistenceManager.
	 */
	const std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >& getData() const;

	/*
	 * \brief returns a map of pointer to id of all objects registered in the PersistenceManager.
	 */
	std::map<boost::shared_ptr<UniPAX::UPBase>, std::string>& getPointerId();

	/*
	 * \brief returns a map of pointer to id of all objects registered in the PersistenceManager.
	 */
	const std::map<boost::shared_ptr<UniPAX::UPBase>, std::string>& getPointerId() const;

	/*
	 * \brief returns a map with ids and the type of the object with this id.
	 */
	std::map<std::string, std::string>& getIdToType();

	/*
	 * \brief returns a map with ids and the type of the object with this id.
	 */
	const std::map<std::string, std::string>& getIdToType() const;

	/**
	 * \brief registers the relationship between pre-merge and post-merge objects.
	 */
	void addMerge(boost::shared_ptr<UniPAX::UPBase> old_object, boost::shared_ptr<UniPAX::UPBase> new_object);

	/**
	 * \brief returns true if object has been registered as merged before.
	 */
	virtual bool isMerged(boost::shared_ptr<UniPAX::UPBase> object);

	/**
	 * \brief returns the merged object to an merged version of an object.
	 */
	virtual boost::shared_ptr<UniPAX::UPBase> getMergedObject(boost::shared_ptr<UniPAX::UPBase> object);

	/**
	 * \brief removes all objects from the manager
	 */
	bool clear();

	/**
	 * \brief assigns an ImportSource to all registered objects in the manager
	 * the ImportSource object will be automatically registered in the manager
	 * returns true if ImportSource has been registered
	 */
	virtual bool assignImportSource(UnipaxPtr<UniPAX::ImportSource>::type data_source);

protected:
	std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > pointer_map_;
	std::map<boost::shared_ptr<UniPAX::UPBase>, std::string> pointer_id_;
	std::map<std::string, std::string> pointer_type_map_;

	std::map<std::string, std::string> pointer_merged_map_;

	std::vector<std::string> errorMsgs;

	bool skip_PathwaySteps;

};  //end class PersistenceManager

}//end namespace UniPAX

#endif

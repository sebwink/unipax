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


#include<UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#include<UNIPAX/PERSISTENCE/MYSQL/MySQLODBWorker.h>
#include<UNIPAX/PERSISTENCE/MYSQL/all.h>
#include<UNIPAX/KERNEL/all.h>
#include<UNIPAX/KERNEL/Kernel.h>
#include<map>
#include<iostream>

#include<boost/algorithm/string.hpp>

#include<memory>
#include<odb/database.hxx>
#include<odb/session.hxx>
#include<odb/transaction.hxx>
#include<odb/mysql/database.hxx>

#include <QtSql>
#include <QVariant>

#include <QtCore>

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>

// **************** MySQLManager ****************************************************

UniPAX::mysql::MySQLManager::MySQLManager(bool cache_enabled) : super(cache_enabled)
{
}

UniPAX::mysql::MySQLManager::MySQLManager(const MySQLManager & arg) : super(arg)
{
}

UniPAX::mysql::MySQLManager::~MySQLManager()
{
	if (odb_worker)
		odb_worker->stop();

	qdatabase.close();
}

bool UniPAX::mysql::MySQLManager::createDatabase(boost::shared_ptr<odb::database>& database)
{
	try
	{
		std::cerr << "Opening connection to " << user << "@" << host << ":" << port << "/" << db << "..." << std::flush;

		qdatabase = QSqlDatabase::addDatabase("QMYSQL");
		qdatabase.setHostName(host.c_str());
		qdatabase.setPort(port);
		qdatabase.setDatabaseName(db.c_str());
		qdatabase.setUserName(user.c_str());
		qdatabase.setPassword(password.c_str());
		if (!qdatabase.open())
		{

			std::cerr << "failed. - Unable to connect to database " << user << "@" << host << ":" << port << "/" << db << std::endl;
			std::cerr << "Error from MySQL:" << std::endl;
			std::cerr << qdatabase.lastError().text().toStdString() << std::endl;
			return false;
		}

		std::cerr << "done." << std::endl;

		// set UTF8 character set
		qdatabase.exec("SET NAMES utf8");

		odb::mysql::database* _db = new odb::mysql::database(user, password, db, host, port, 0, "utf8");
		database.reset(_db);
		odb_worker.reset(new UniPAX::mysql::MySQLODBWorker(database, cache_enabled));

		updateMaxIds();

		return true;
	}
	catch (const odb::exception& e)
	{
		std::cerr << "MySQLManager::createDatabase: odb_exception - " << e.what() << std::endl;
	}

	return false;
}

bool UniPAX::mysql::MySQLManager::updateMaxIds()
{
	// fill once the map with the max ids
	std::set<std::string> all_classes = Kernel::classes();

	for (std::set<std::string>::iterator it = all_classes.begin(); it != all_classes.end(); it++)
	{

		// only those which have a database table
		if (Kernel::classType(*it) != ClassType::END_ENUM)
		{
			QSqlQuery query = exec(QString("SELECT MAX(unipaxId) FROM `%1`").arg(UniPAX::mysql::DBTable::ofClass(*it)), QString("Unable to update max ids of class %1").arg(QString::fromStdString(*it)));
			if (query.next())
			{
				db_ids[*it] = (DBManager::getBase(*it) | (query.value(0).toULongLong() & 0x00FFFFFFUL));
			} else
			{
				throw std::runtime_error("MySQLManager::updateMaxIds:Unable to query for max of " + *it);
			}
		}
	}

	return true;
}

QSqlQuery UniPAX::mysql::MySQLManager::exec(QString sql, QString error)
{
	QSqlQuery q = qdatabase.exec(sql);
	QSqlError e = q.lastError();
	if (e.isValid())
	{
		throw std::runtime_error(error.toStdString() + ": " + e.text().toStdString() + " -- " + sql.toStdString());
	}

	return q;
}

void UniPAX::mysql::MySQLManager::exec(QSqlQuery& query, QString error)
{
	query.exec();
	QSqlError e = query.lastError();
	if (e.isValid())
	{
		throw std::runtime_error(error.toStdString() + ": " + e.text().toStdString() + " -- " + query.lastQuery().toStdString());
	}
}

bool UniPAX::mysql::MySQLManager::assignId(boost::shared_ptr<UniPAX::UPBase> object)
{
	return assignId(object, true);
}

bool UniPAX::mysql::MySQLManager::assignId(boost::shared_ptr<UniPAX::UPBase> object, bool check_db)
{
	if (check_db)
	{
		updateMaxIds();
	}

	std::string type = object->getType();
	UnipaxId help;

	if (object->getUnipaxId() == 0.)
	{
		help = db_ids[type];
		help++;
		db_ids[type] = help;
		object->setUnipaxId(help);
	}

	return 1;
}



bool UniPAX::mysql::MySQLManager::assignIds(PersistenceManager& manager)
{
	return assignIds(manager, false);
}

bool UniPAX::mysql::MySQLManager::assignIds(PersistenceManager& manager, bool force)
{

	updateMaxIds();

	std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > data = manager.getData();
	std::map<std::string, std::string> pointer_type_map_ = manager.getIdToType();
	std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator it;
	std::map<std::string, std::string>::iterator type_search;

	// create unipaxId for each object
	for (it = data.begin(); it != data.end(); it++)
	{
		std::map<std::string, std::string>::iterator type_search = pointer_type_map_.find(it->first);

		if (type_search == pointer_type_map_.end())
		{
			// no type available
			std::cerr << "MySQLManager::assignIds: no type for object with id " << it->first << std::endl;
			return 0;
		}

		std::string type = it->second->getType();
		UnipaxId help;

		if (it->second->getUnipaxId() == 0. || force)
		{
			help = db_ids[type];
			help++;
			db_ids[type] = help;
			it->second->setUnipaxId(help);
		}
	}

	//	// update the manager ... we have new ids
	//	manager.updateAll();

	return 1;
}


// add GeneId as RelationshipXref to Protein or ProteinReference with unipax_id id
bool UniPAX::mysql::MySQLManager::addGeneId(UnipaxId id, std::string external_protein_id,
		std::map<std::string, boost::shared_ptr<UniPAX::RelationshipXref> > & rxref_map,
		KernelCollector& manager, UniProtReader& reader)
{

    if (DBManager::isType(id, UniPAX::ClassType::idProtein)) //UniPAX::Protein
	{
		boost::shared_ptr<UniPAX::Protein> protein = boost::dynamic_pointer_cast<UniPAX::Protein>(super::getObjectByID(id));

		std::string::size_type found = external_protein_id.find("-");
		if (found != std::string::npos)
		{
			std::cout << "shorten id '" << external_protein_id << "' to '" << external_protein_id.substr(0,found) << "'" << std::endl;
			external_protein_id = external_protein_id.substr(0, found);
		}

		std::vector<std::string> ids;
		// change standardName of Protein
		ids = reader.getMappedId(external_protein_id,"UniProtKB-ID");
		if (!ids.empty())
		{
			protein->setStandardName(ids[0]);
		}

		ids.clear();
		ids = reader.getMappedId(external_protein_id,"GeneID");

		// if no corresponding GeneId found ... continue
		if (ids.empty())
		{
			std::cout << "no corresponding GeneId found for '" << external_protein_id << "'" << std::endl;
			return false;
		}

		std::string search_string = std::string("EntrezGene")+"||"+ids[0];

		boost::shared_ptr<UniPAX::RelationshipXref> rxref;
		UnipaxId rxid = getRelationshipXrefId("EntrezGene", ids[0]);

		UnipaxId help = db_ids["RelationshipTypeVocabulary"];
		help++;


		if (rxid == 0)
		{
			if (rxref_map.find(search_string) == rxref_map.end())
			{
				rxref = boost::shared_ptr<UniPAX::RelationshipXref>(new UniPAX::RelationshipXref());
				rxref->setDb("EntrezGene");
				rxref->setId(ids[0]);
				assignId(rxref, false);
				boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> rtv = boost::shared_ptr<UniPAX::RelationshipTypeVocabulary>(new UniPAX::RelationshipTypeVocabulary);
				rtv->setTerm("Coding gene");
				rxref->addRelationshipType(rtv);
				rtv->setUnipaxId(help);

				rxref_map[search_string] = rxref;
			}
			else
			{
				rxref = rxref_map.find(search_string)->second;
			}
		}
		else
		{
			rxref = boost::dynamic_pointer_cast<UniPAX::RelationshipXref>(super::getObjectByID(rxid));
		}
		protein->addXref(rxref);

		manager.collect(protein);

	}
    else if (DBManager::isType(id, UniPAX::ClassType::idProteinReference)) //UniPAX::ProteinReference
	{

		boost::shared_ptr<UniPAX::ProteinReference> proteinref = boost::dynamic_pointer_cast<UniPAX::ProteinReference>(super::getObjectByID(id));

		size_t found = external_protein_id.find("-");
		if (found != std::string::npos)
		{
			std::cout << "shorten id '" << external_protein_id << "' to '" << external_protein_id.substr(0,found) << "'" << std::endl;
			external_protein_id = external_protein_id.substr(0,found);
		}

		std::vector<std::string> ids;

		// change standardName of ProteinReference
		ids = reader.getMappedId(external_protein_id,"UniProtKB-ID");
		if (!ids.empty())
		{
			proteinref->setStandardName(ids[0]);
		}

		ids.clear();
		ids = reader.getMappedId(external_protein_id,"GeneID");

		// if no corresponding GeneId found ... continue
		if (ids.empty())
		{
			std::cout << "no corresponding GeneId found for '" << external_protein_id << "'" << std::endl;
			return false;
		}

		std::string search_string = std::string("EntrezGene")+"||"+ids[0];

		boost::shared_ptr<UniPAX::RelationshipXref> rxref;
		UnipaxId rxid = getRelationshipXrefId("EntrezGene", ids[0]);

		UnipaxId help = db_ids["RelationshipTypeVocabulary"];
		help++;


		if (rxid == 0)
		{
			if (rxref_map.find(search_string) == rxref_map.end())
			{
				rxref = boost::shared_ptr<UniPAX::RelationshipXref>(new UniPAX::RelationshipXref());
				rxref->setDb("EntrezGene");
				rxref->setId(ids[0]);
				assignId(rxref, false);
				boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> rtv = boost::shared_ptr<UniPAX::RelationshipTypeVocabulary>(new UniPAX::RelationshipTypeVocabulary);
				rtv->setTerm("Coding gene");
				rxref->addRelationshipType(rtv);
				rtv->setUnipaxId(help);

				rxref_map[search_string] = rxref;
			}
			else
			{
				rxref = rxref_map.find(search_string)->second;
			}
		}
		else
		{
			rxref = boost::dynamic_pointer_cast<UniPAX::RelationshipXref>(super::getObjectByID(rxid));
		}
		proteinref->addXref(rxref);

		manager.collect(proteinref);
	}

	return true;
}


UnipaxId UniPAX::mysql::MySQLManager::getRelationshipXrefId(std::string db, std::string id)
{
	if (initDatabase())
	{
		try
		{
			odb::session s;
			odb::transaction t (odb_db->begin ());

			odb::result< ::UniPAX::RelationshipXref> rx (odb_db->query< ::UniPAX::RelationshipXref> (odb::query< ::UniPAX::RelationshipXref>::db == odb::query< ::UniPAX::RelationshipXref>::_val(db)
					&& odb::query< ::UniPAX::RelationshipXref>::id == odb::query< ::UniPAX::RelationshipXref>::_val(id)));
			for (odb::result< ::UniPAX::RelationshipXref>::iterator rx_it (rx.begin ()); rx_it != rx.end (); ++rx_it)
			{
				return rx_it->getUnipaxId();
			}
		}
		catch (const odb::exception& e)
		{
			std::cerr << "MySQLManager::getRelationshipXrefId: odb_exception - " << e.what() << std::endl;
			return 0;
		}
	}

	return 0;

}

bool UniPAX::mysql::MySQLManager::getProteinIds(std::map<UnipaxId, std::string>& protein_ids)
{
	if (initDatabase())
	{
		try
		{
			odb::session s;
			odb::transaction t (odb_db->begin ());

			std::vector<boost::shared_ptr<Xref> >::iterator xref_it;
			odb::result< ::UniPAX::Protein> r (odb_db->query< ::UniPAX::Protein> ());
			for (odb::result< ::UniPAX::Protein>::iterator prot_it (r.begin ()); prot_it != r.end (); ++prot_it)
			{
				for (xref_it = prot_it->getXrefs().begin(); (xref_it != prot_it->getXrefs().end()); xref_it++)
				{
					if (((*xref_it)->getDb() == "UniProt") || ((*xref_it)->getDb() == "UniProtKB"))
					{
						protein_ids[prot_it->getUnipaxId()] = (*xref_it)->getId();
					}
				}
			}

			return true;
		}
		catch (const odb::exception& e)
		{
			std::cerr << "MySQLManager::getProteinIds: odb_exception - " << e.what() << std::endl;
			return false;
		}
	}

	return false;

}


bool UniPAX::mysql::MySQLManager::getProteinReferenceIds(std::map<UnipaxId, std::string>& proteinref_ids)
{
	if (initDatabase())
	{
		try
		{
			odb::session s;
			odb::transaction t (odb_db->begin ());

			std::vector<boost::shared_ptr<Xref> >::iterator xref_it;
			odb::result< ::UniPAX::ProteinReference> r (odb_db->query< ::UniPAX::ProteinReference> ());
			for (odb::result< ::UniPAX::ProteinReference>::iterator prot_it (r.begin ()); prot_it != r.end (); ++prot_it)
			{
				for (xref_it = prot_it->getXrefs().begin(); (xref_it != prot_it->getXrefs().end()); xref_it++)
				{
					if (((*xref_it)->getDb() == "UniProt") || ((*xref_it)->getDb() == "UniProtKB"))
					{
						proteinref_ids[prot_it->getUnipaxId()] = (*xref_it)->getId();
					}
				}
			}

			return true;
		}
		catch (const odb::exception& e)
		{
			std::cerr << "MySQLManager::getProteinReferenceIds: odb_exception - " << e.what() << std::endl;
			return false;
		}
	}

	return false;

}

bool UniPAX::mysql::MySQLManager::listPathways(std::multimap<std::string, std::string>& pathways)
{

	if (initDatabase())
	{
		QSqlQuery query = exec("SELECT pn.value, p.standardName, p.displayName FROM Entity p, Provenance_name pn WHERE p.typeid='UniPAX::Pathway' AND p.dataSource = pn.object_id AND pn.index = 0", "Unable to list pathways from database.");
		while (query.next())
		{
			//			if (query.value(1).isNull() || query.value(1).toString().isEmpty())
			//			{
			//				pathways.insert(std::pair<std::string, std::string>(query.value(0).toString().toStdString(),query.value(2).toString().toStdString()));
			//			}
			//			else
			//			{
			pathways.insert(std::pair<std::string, std::string>(query.value(0).toString().toStdString(),query.value(1).toString().toStdString()));
			//			}

		}
		return true;
	}

	return false;
}


bool UniPAX::mysql::MySQLManager::listPathwaysById(std::map<UnipaxId, std::vector<UnipaxId> >& pathways)
{
	if (initDatabase())
	{
		QSqlQuery query = exec("SELECT dataSource, unipaxId FROM Entity WHERE typeid='UniPAX::Pathway' AND dataSource IS NOT NULL", "Unable to list pathways by id");
		while (query.next())
		{
			if (pathways.find(query.value(0).toULongLong()) != pathways.end())
				pathways[query.value(0).toULongLong()].push_back(query.value(1).toULongLong());
			else
			{
				std::vector<UnipaxId> tmp;
				pathways[query.value(0).toULongLong()] = tmp;
				pathways[query.value(0).toULongLong()].push_back(query.value(1).toULongLong());
			}
		}
		return true;
	}

	return false;
}


boost::shared_ptr<UniPAX::Pathway> UniPAX::mysql::MySQLManager::getPathway(std::string db_name, std::string pathway_name)
{
	if (initDatabase())
	{
		// this version with qt sql is faster and needs less memory ....
		UnipaxId internal_id = 0;

		QSqlQuery query = exec(QString("SELECT p.unipaxId FROM Entity p, Provenance_name pn WHERE p.standardName = '%1' and pn.value = '%2' and p.dataSource = pn.object_id and pn.index = 0").arg(QString::fromStdString(pathway_name)).arg(QString::fromStdString(db_name)), QString("Unable to get pathway '%1' of '%2").arg(QString::fromStdString(pathway_name)).arg(QString::fromStdString(db_name)));
		if (query.next())
		{
			internal_id = query.value(0).toLongLong();
		}

		try
		{
			if (internal_id == 0)
				return boost::shared_ptr<UniPAX::Pathway>();

			return boost::dynamic_pointer_cast<UniPAX::Pathway>(odb_worker->load(internal_id));

		}
		catch (const odb::exception& e)
		{
			std::cerr << "MySQLManager::getPathway: odb_exception - " << e.what() << std::endl;
			return boost::shared_ptr<UniPAX::Pathway>();
		}
	}

	return boost::shared_ptr<UniPAX::Pathway>();


	//	if (initDatabase())
	//	{
	//		UnipaxId internal_id = 0;
	//
	//		try
	//		{
	//			odb::transaction t (odb_db->begin ());
	//
	//			odb::result< ::UniPAX::Pathway> p (odb_db->query< ::UniPAX::Pathway> (odb::query< ::UniPAX::Pathway>::standardName == odb::query< ::UniPAX::Pathway>::_val(pathway_name)));
	//			for (odb::result< ::UniPAX::Pathway>::iterator it (p.begin ()); it != p.end (); ++it)
	//			{
	//				std::cout << it->getUnipaxId() << std::endl;
	//				if (it->getDataSource() != 0)
	//				{
	//					if (it->getDataSource()->getFirstName() == db_name)
	//					{
	//						internal_id = it->getUnipaxId();
	//						break;
	//					}
	//				}
	//				else
	//				{
	//					if ("UDIS" == db_name)
	//					{
	//						internal_id = it->getUnipaxId();
	//						break;
	//					}
	//				}
	//
	//			}
	//
	//			if (internal_id == 0)
	//				return boost::shared_ptr<UniPAX::Pathway>();
	//
	//			return boost::dynamic_pointer_cast<UniPAX::Pathway>(odb_worker->load(internal_id));
	//
	//		}
	//		catch (const odb::exception& e)
	//		{
	//			std::cerr << "DBManager::getPathway: odb_exception - " << e.what() << std::endl;
	//			return boost::shared_ptr<UniPAX::Pathway>();
	//		}
	//	}

}

bool UniPAX::mysql::MySQLManager::getObjectsByType(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::string type, bool recursive)
{
	if (initDatabase())
	{
		std::set<std::string> children = UniPAX::Kernel::children(type, recursive);
		children.insert(type);

		std::vector<UnipaxId> ids;

		for (std::set<std::string>::iterator it = children.begin(); it != children.end(); ++it)
		{

			QSqlQuery query = exec(QString("SELECT unipaxId FROM `%1`").arg(QString::fromStdString(*it)), QString("Unable to get objects of type %1").arg(QString::fromStdString(*it)));
			while (query.next())
			{
				UnipaxId id = query.value(0).toULongLong();
				ids.push_back(id);
			}
		}

		return getObjectsByIDs(result, ids);
	}

	return false;
}

bool UniPAX::mysql::MySQLManager::getIdsByType(std::vector<UnipaxId> & ids, std::string type, bool recursive)
{
	if (initDatabase())
	{
		std::set<std::string> children = UniPAX::Kernel::children(type, recursive);
		children.insert(type);

		ids.clear();

		for (std::set<std::string>::iterator it = children.begin(); it != children.end(); ++it)
		{
			QSqlQuery query = exec(QString("SELECT unipaxId FROM `%1`").arg(QString::fromStdString(*it)), QString("Unable to get ids by type for %1").arg(QString::fromStdString(*it)));

			while (query.next())
			{
				UnipaxId id = query.value(0).toULongLong();
				ids.push_back(id);
			}
		}

		return true;
	}

	return false;
}

bool UniPAX::mysql::MySQLManager::isValid(UnipaxId id)
{

	std::string type = DBManager::getType(id, "");
	if (type.length() > 0)
	{
		if (initDatabase())
		{
			QSqlQuery q = exec(QString("SELECT * FROM %1 WHERE unipaxId = %2 LIMIT 1 ").arg(QString::fromStdString(type), QString::number(id)), QString("Unable to check if %1 is of type %2").arg(id).arg(QString::fromStdString(type)));
			if (q.next()) {
				return true;
			}
		}
	}

	return false;
}


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


#include<UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#include<UNIPAX/PERSISTENCE/ORACLE/OracleODBWorker.h>
#include<UNIPAX/PERSISTENCE/ORACLE/all.h>
#include<UNIPAX/KERNEL/all.h>
#include<UNIPAX/KERNEL/Kernel.h>
#include<map>
#include<iostream>

#include<boost/algorithm/string.hpp>

#include<memory>
#include<odb/database.hxx>
#include<odb/oracle/database.hxx>
#include <QtSql>
#include <QVariant>

#include <QtCore>

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>


UniPAX::oracle::OracleManager::OracleManager() {
}

UniPAX::oracle::OracleManager::OracleManager(const OracleManager & arg) : super(arg), service_name(arg.service_name)
{
}

UniPAX::oracle::OracleManager::~OracleManager()
{
	if (odb_worker)
		odb_worker->stop();

	qdatabase.close();
}

bool UniPAX::oracle::OracleManager::setServiceName(std::string s_name)
{
	service_name = s_name;

	return true;
}

bool UniPAX::oracle::OracleManager::createDatabase(boost::shared_ptr<odb::database>& database)
{
	try
	{
		std::cerr << "Opening connection to " << user << "@" << host << ":" << port << "/" << db << "..." << std::flush;

		qdatabase = QSqlDatabase::addDatabase("QOCI");
		qdatabase.setHostName(host.c_str());
		qdatabase.setPort(port);
		qdatabase.setDatabaseName(db.c_str());
		qdatabase.setUserName(user.c_str());
		qdatabase.setPassword(password.c_str());

		if (!qdatabase.open())
		{

			std::cerr << "failed. - Unable to connect to database " << user << "@" << host << ":" << port << "/" << db << std::endl;
			std::cerr << "Error from Oracle:" << std::endl;
			std::cerr << qdatabase.lastError().text().toStdString() << std::endl;
			return false;
		}

		std::cerr << "done." << std::endl;

		// set UTF8 character set
		qdatabase.exec("SET NAMES utf8");

		if (service_name.empty())
		{
			service_name = db;
		}
		odb::oracle::database* _db = new odb::oracle::database(user, password, service_name, host, port);
		database.reset(_db);
		odb_worker.reset(new UniPAX::oracle::OracleODBWorker(database));

		updateMaxIds();

		return true;
	}
	catch (const odb::exception& e)
	{
		std::cerr << "OracleManager::createDatabase: odb_exception - " << e.what() << std::endl;
	}

	return false;
}

bool UniPAX::oracle::OracleManager::updateMaxIds()
{
	// fill once the map with the max ids
	std::set<std::string> & all_classes = Kernel::classes();

	for (std::set<std::string>::iterator it = all_classes.begin(); it != all_classes.end(); it++)
	{
		QSqlQuery query = qdatabase.exec(QString("SELECT MAX(\"unipaxId\") FROM \"%1\"").arg(QString::fromStdString(UniPAX::Kernel::shortType(*it))));
		if (query.isActive())
		{
			if (query.next())
			{
				db_ids[*it] = (DBManager::getBase(*it) | (query.value(0).toULongLong() & 0x00FFFFFFUL));

			} else
			{
				std::cerr << "OracleManager::updateMaxIds: Error with query: " << query.executedQuery().toStdString() << std::endl;
				return false;
			}
		}
		else
		{
			std::cerr << "OracleManager::updateMaxIds: Unable to query for max of " << *it << std::endl;
			return false;
		}
	}

	return true;
}

bool UniPAX::oracle::OracleManager::assignId(boost::shared_ptr<UniPAX::UPBase> object)
{
	return assignId(object, true);
}

bool UniPAX::oracle::OracleManager::assignId(boost::shared_ptr<UniPAX::UPBase> object, bool check_db)
{
	if (check_db)
	{
		updateMaxIds();
	}

	std::string type = object->get_type();
	UnipaxId help;

	if (object->get_unipaxId() == 0.)
	{
		help = db_ids[type];
		help++;
		db_ids[type] = help;
		object->set_unipaxId(help);
	}

	return 1;
}



bool UniPAX::oracle::OracleManager::assignIds(PersistenceManager& manager)
{
	return assignIds(manager, false);
}

bool UniPAX::oracle::OracleManager::assignIds(PersistenceManager& manager, bool force)
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
			std::cerr << "OracleManager::assignIds: no type for object with id " << it->first << std::endl;
			return 0;
		}

		std::string type = it->second->get_type();
		UnipaxId help;

		if (it->second->get_unipaxId() == 0. || force)
		{
			help = db_ids[type];
			help++;
			db_ids[type] = help;
			it->second->set_unipaxId(help);
		}
	}

	//	// update the manager ... we have new ids
	//	manager.updateAll();

	return 1;
}


// add GeneId as RelationshipXref to Protein or ProteinReference with unipax_id id
bool UniPAX::oracle::OracleManager::addGeneId(UnipaxId id, std::string external_protein_id,
		std::map<std::string, boost::shared_ptr<UniPAX::RelationshipXref> > & rxref_map,
		KernelCollector& manager, UniProtReader& reader)
{

    if ((id >> 24) == UniPAX::ClassType::Protein) //UniPAX::Protein
	{
		boost::shared_ptr<UniPAX::Protein> protein = boost::dynamic_pointer_cast<UniPAX::Protein>(super::getObjectByID(id));

		size_t found = external_protein_id.find("-");
		if (found != std::string::npos)
		{
			std::cout << "shorten id '" << external_protein_id << "' to '" << external_protein_id.substr(0,found) << "'" << std::endl;
			external_protein_id = external_protein_id.substr(0,found);
		}

		std::vector<std::string> ids;
		// change standardName of Protein
		ids = reader.getMappedId(external_protein_id,"UniProtKB-ID");
		if (!ids.empty())
		{
			protein->set_standardName(ids[0]);
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
				rxref->set_db("EntrezGene");
				rxref->set_id(ids[0]);
				assignId(rxref, false);
				boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> rtv = boost::shared_ptr<UniPAX::RelationshipTypeVocabulary>(new UniPAX::RelationshipTypeVocabulary);
				rtv->set_term("Coding gene");
				rxref->add_relationshipType(rtv);
				rtv->set_unipaxId(help);

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
		protein->add_xref(rxref);

		manager.collect(protein);

	}
    else if ((id >> 24) == UniPAX::ClassType::ProteinReference) //UniPAX::ProteinReference
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
			proteinref->set_standardName(ids[0]);
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
				rxref->set_db("EntrezGene");
				rxref->set_id(ids[0]);
				assignId(rxref, false);
				boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> rtv = boost::shared_ptr<UniPAX::RelationshipTypeVocabulary>(new UniPAX::RelationshipTypeVocabulary);
				rtv->set_term("Coding gene");
				rxref->add_relationshipType(rtv);
				rtv->set_unipaxId(help);

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
		proteinref->add_xref(rxref);

		manager.collect(proteinref);
	}

	return true;
}


UnipaxId UniPAX::oracle::OracleManager::getRelationshipXrefId(std::string db, std::string id)
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
				return rx_it->get_unipaxId();
			}
		}
		catch (const odb::exception& e)
		{
			std::cerr << "OracleManager::getRelationshipXrefId: odb_exception - " << e.what() << std::endl;
			return 0;
		}
	}

	return 0;

}

bool UniPAX::oracle::OracleManager::getProteinIds(std::map<UnipaxId, std::string>& protein_ids)
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
				for (xref_it = prot_it->get_xrefs().begin(); (xref_it != prot_it->get_xrefs().end()); xref_it++)
				{
					if (((*xref_it)->get_db() == "UniProt") || ((*xref_it)->get_db() == "UniProtKB"))
					{
						protein_ids[prot_it->get_unipaxId()] = (*xref_it)->get_id();
					}
				}
			}

			return true;
		}
		catch (const odb::exception& e)
		{
			std::cerr << "OracleManager::getProteinIds: odb_exception - " << e.what() << std::endl;
			return false;
		}
	}

	return false;

}


bool UniPAX::oracle::OracleManager::getProteinReferenceIds(std::map<UnipaxId, std::string>& proteinref_ids)
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
				for (xref_it = prot_it->get_xrefs().begin(); (xref_it != prot_it->get_xrefs().end()); xref_it++)
				{
					if (((*xref_it)->get_db() == "UniProt") || ((*xref_it)->get_db() == "UniProtKB"))
					{
						proteinref_ids[prot_it->get_unipaxId()] = (*xref_it)->get_id();
					}
				}
			}

			return true;
		}
		catch (const odb::exception& e)
		{
			std::cerr << "OracleManager::getProteinReferenceIds: odb_exception - " << e.what() << std::endl;
			return false;
		}
	}

	return false;

}

bool UniPAX::oracle::OracleManager::listPathways(std::multimap<std::string, std::string>& pathways)
{

	if (initDatabase())
	{
		QSqlQuery query;
		std::string sql_string;

		sql_string = "select pn.\"value\", p.\"standardName\", p.\"displayName\" from \"Pathway\" p, \"Provenance_name\" pn where p.\"dataSource\" = pn.\"object_id\" and pn.\"index\" = 0";
		query.exec(sql_string.c_str());
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

	}

	return false;
}


bool UniPAX::oracle::OracleManager::listPathwaysById(std::map<UnipaxId, std::vector<UnipaxId> >& pathways)
{
	if (initDatabase())
	{
		QSqlQuery query;
		std::string sql_string;

		sql_string = "select \"dataSource\", \"unipaxId\" from \"Pathway\" where \"dataSource\" is not null";
		query.exec(sql_string.c_str());
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


boost::shared_ptr<UniPAX::Pathway> UniPAX::oracle::OracleManager::getPathway(std::string db_name, std::string pathway_name)
{
	if (initDatabase())
	{
		// this version with qt sql is faster and needs less memory ....
		UnipaxId internal_id = 0;
		QSqlQuery query;
		std::string sql_string;

		sql_string = "select p.\"unipaxId\" from \"Pathway\" p, \"Provenance_name\" pn where p.\"standardName\" = '"+pathway_name+"' and pn.\"value\" = '"+db_name+"' and p.\"dataSource\" = pn.\"object_id\" and pn.\"index\" = 0";
		query.exec(sql_string.c_str());
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
			std::cerr << "OracleManager::getPathway: odb_exception - " << e.what() << std::endl;
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
	//				std::cout << it->get_unipaxId() << std::endl;
	//				if (it->get_dataSource() != 0)
	//				{
	//					if (it->get_dataSource()->get_firstName() == db_name)
	//					{
	//						internal_id = it->get_unipaxId();
	//						break;
	//					}
	//				}
	//				else
	//				{
	//					if ("UDIS" == db_name)
	//					{
	//						internal_id = it->get_unipaxId();
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

bool UniPAX::oracle::OracleManager::getObjectsByType(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::string type, bool recursive)
{
	std::string shortType;
	if (initDatabase())
	{
		std::set<std::string> children = UniPAX::Kernel::children(type, recursive);
		children.insert(type);

		std::vector<UnipaxId> ids;

		for (std::set<std::string>::iterator it = children.begin(); it != children.end(); ++it)
		{
			// need to shorten the type due to Oracle specifications for table names
			shortType = UniPAX::Kernel::shortType(*it);
			QSqlQuery query = qdatabase.exec(QString("SELECT \"unipaxId\" FROM \"%1\"").arg(QString::fromStdString(*it)));

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

bool UniPAX::oracle::OracleManager::getIdsByType(std::vector<UnipaxId> & ids, std::string type, bool recursive)
{
	std::string shortType;
	if (initDatabase())
	{
		std::set<std::string> children = UniPAX::Kernel::children(type, recursive);
		children.insert(type);

		ids.clear();

		for (std::set<std::string>::iterator it = children.begin(); it != children.end(); ++it)
		{
			// need to shorten the type due to Oracle specifications for table names
			shortType = UniPAX::Kernel::shortType(*it);
			QSqlQuery query = qdatabase.exec(QString("SELECT \"unipaxId\" FROM \"%1\"").arg(QString::fromStdString(shortType)));

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

bool UniPAX::oracle::OracleManager::isValid(UnipaxId id)
{

	std::string type = ODBWorker::getType(id);
	// need to shorten the type due to Oracle specifications for table names
	type = UniPAX::Kernel::shortType(type);
	if (type.length() > 0)
	{
		if (initDatabase())
		{
			QSqlQuery q = qdatabase.exec(QString("SELECT * FROM \"%1\" WHERE \"unipaxId\" = %2 and ROWNUM = 1").arg(QString::fromStdString(type), QString::number(id)));
			if (q.next()) {
				return true;

			}
		}
	}

	return false;
}


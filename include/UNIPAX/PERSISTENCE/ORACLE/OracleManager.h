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


#ifndef UNIPAX_PERSISTENCE_ORACLE_ORACLEMANAGER_H
#define UNIPAX_PERSISTENCE_ORACLE_ORACLEMANAGER_H

#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/PERSISTENCE/DBManager.h>
#include<UNIPAX/KERNEL/BIOPAX/RelationshipXref.h>
#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<string>
#include<map>
#include<memory>
#include <QtSql/QSqlDatabase>


namespace UniPAX {

namespace oracle
{

class UNIPAX_EXPORT OracleManager : public DBManager {

public:

	OracleManager();

	OracleManager(const OracleManager & arg);

	OracleManager & operator =(const OracleManager & arg);

	~OracleManager();

	bool setServiceName(std::string service_name);

	bool isValid(UnipaxId id);

	UnipaxId getRelationshipXrefId(std::string db, std::string id);
	bool getProteinIds(std::map<UnipaxId, std::string>& protein_ids);
	bool getProteinReferenceIds(std::map<UnipaxId, std::string>& proteinref_ids);
	bool addGeneId(UnipaxId id, std::string external_protein_id, std::map<std::string, boost::shared_ptr<UniPAX::RelationshipXref> >& rxref_map, KernelCollector& manager, UniProtReader& reader);

	bool listPathways(std::multimap<std::string, std::string>& pathways);
	bool listPathwaysById(std::map<UnipaxId, std::vector<UnipaxId> >& pathways);
	boost::shared_ptr<UniPAX::Pathway> getPathway(std::string db_name, std::string pathway_name);

	bool getObjectsByType(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::string type, bool recursive = false);
	bool getIdsByType(std::vector<UnipaxId> & ids, std::string type, bool recursive = false);

	bool assignIds(PersistenceManager& manager);
	bool assignIds(PersistenceManager& manager, bool force);
	bool assignId(boost::shared_ptr<UniPAX::UPBase> object);

	QSqlDatabase* getDatabase() { return &qdatabase; };

protected:

	bool assignId(boost::shared_ptr<UniPAX::UPBase> object, bool check_db);

	virtual bool createDatabase(boost::shared_ptr<odb::database>& database);

	virtual bool updateMaxIds();

	QSqlDatabase qdatabase;

	// if sid is different from service name
	std::string service_name;


private:

	typedef DBManager super;

};  //end class OracleManager

}

} //end namespace UniPAX

#endif          // UNIPAX_PERSISTENCE_ORACLE_ORACLEMANAGER_H

// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                               UniPAX 
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


#ifndef UNIPAX_IMPORT_GENESET_GeneSetWriter_H
#define UNIPAX_IMPORT_GENESET_GeneSetWriter_H

#include<string>
#include<map>
#include<set>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include <QtCore/QTextStream>

namespace UniPAX
{
	class UNIPAX_EXPORT GeneSetWriter
	{
	public:
		GeneSetWriter();
		GeneSetWriter(const std::string& filename);
		GeneSetWriter(const GeneSetWriter& to_copy);
		~GeneSetWriter();
		GeneSetWriter& operator=(const GeneSetWriter& assign);

		bool setFilename(const std::string& filename);
		bool setTitle(const std::string& title);
		bool setDescription(const std::string& description);

		bool write();
		bool write(bool use_gene_ids);
		bool write(const std::string& filename);
		bool write(const std::string& filename, bool use_gene_ids);
		bool write(const std::string& filename, bool use_gene_ids, bool gmx_format);

		bool write(QTextStream& out);
		bool write(QTextStream& out, bool use_gene_ids);
		bool write(QTextStream& out, bool use_gene_ids, bool gmx_format);

		std::set<std::string> getAvailableIdTypes();
		bool write(QTextStream& out, std::string id_type);
		bool write(QTextStream& out, std::string id_type, bool gmx_format);

		void setPersistenceManager(PersistenceManager& manager_);

		void setDebug(bool debug);

	private:
		std::string filename;
		std::string title;
		std::string description;
		PersistenceManager manager;
		bool debug;
		bool gmx_format;

	};

}
#endif

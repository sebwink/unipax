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


#ifndef UNIPAX_IMPORT_UNIPROTREADER_H
#define UNIPAX_IMPORT_UNIPROTREADER_H

#include<UNIPAX/COMMON/common.h>
#include<string>
#include<vector>
#include<map>

namespace UniPAX
{

	/** \brief class for reading the UniProt id mapping dat format.

		  \ingroup Importer
	 */
	class UNIPAX_EXPORT UniProtReader
	{
	public:

		UniProtReader();

		UniProtReader(const std::string& filename);

		UniProtReader(const UniProtReader& to_copy);

		~UniProtReader();

		UniProtReader& operator=(const UniProtReader& assign);

		bool setFilename(const std::string& filename);

		bool parse();

		bool parse(const std::string& filename);

		bool parseSecondaryAccs(const std::string& sec_filename);

		std::vector<std::string> getMappedId(std::string swissprot_id, std::string database);
		std::map<std::string, std::vector<std::string> > getMappedId(std::string swissprot_id);


		std::map<std::string, std::map<std::string, std::vector<std::string> > > getIdMapping();


	private:
		std::string filename;
		std::map<std::string, std::map<std::string, std::vector<std::string> > > data;
		std::map<std::string, std::string> secondary_accession_map;
	};

}
#endif

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


#ifndef UNIPAX_IMPORT_TFENCYCLOPEDIA_TFENCYCLOPEDIAREADER_H
#define UNIPAX_IMPORT_TFENCYCLOPEDIA_TFENCYCLOPEDIAREADER_H

#include<UNIPAX/COMMON/common.h>
#include <UNIPAX/COMMON/PersistenceManager.h>
#include<string>
#include<vector>
#include<map>

namespace UniPAX
{

	/** \brief class for reading the TFEncyclopedia .

		  \ingroup Importer
	 */
	class UNIPAX_EXPORT TFEncyclopediaReader
	{
	public:

		TFEncyclopediaReader();

		TFEncyclopediaReader(const std::string& filename);

		TFEncyclopediaReader(const TFEncyclopediaReader& to_copy);

		~TFEncyclopediaReader();

		TFEncyclopediaReader& operator=(const TFEncyclopediaReader& assign);

		bool setFilename(const std::string& filename);

		bool parse();

		bool parse(const std::string& filename);

		void setPersistenceManager(PersistenceManager& manager);

		PersistenceManager& getPersistenceManager();

		const PersistenceManager& getPersistenceManager() const;

		void setDebug(bool debug);


	private:
		std::string filename;
		PersistenceManager manager;
		bool debug;
	};

}
#endif

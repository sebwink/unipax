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


#ifndef UNIPAX_IMPORT_BIOPAX_BIOPAXREADER_H
#define UNIPAX_IMPORT_BIOPAX_BIOPAXREADER_H

#include<string>
#include<vector>
#include<UNIPAX/IMPORT/BIOPAX/BIOPAXReaderHandler.h>
#include<UNIPAX/COMMON/common.h>

namespace UniPAX
{

	/** \brief class for reading the BioPAX Level 3 format.

		  \ingroup Importer
	 */
	class UNIPAX_EXPORT BIOPAXReader
	{
	public:

		/**	@name	standard methods
		 */
		//@{
		/// \brief a standard Constructor
		BIOPAXReader();
		/// \brief a standard Constructor with filename parameter
		BIOPAXReader(const std::string& filename);
		/// \brief copy constructor
		BIOPAXReader(const BIOPAXReader& to_copy);
		/// \brief a standard destructor
		~BIOPAXReader();
		/// \brief an assignment operator
		BIOPAXReader& operator=(const BIOPAXReader& assign);
		//@}

		/**	@name miscellaneous
		 */
		//@{

		/// \brief set file for reading
		bool setFilename(const std::string& filename);

		/// \brief parse file */
		bool parse();

		/// \brief parse file */
		bool parse(const std::string& filename);
		void setDebug(bool debug);
		void setErrorOnInconsistentData(bool errorOnInconsistentData);

		void createObjectsOnly(bool onlyObjects);
		std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > getData();

		PersistenceManager& getPersistenceManager();
		const PersistenceManager& getPersistenceManager() const;

		//@}

	private:
		std::string xmlfilename;
		BIOPAXReaderHandler xmlhandler;
	};

}
#endif

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


#ifndef UNIPAX_IMPORT_BIOPAX_BIOPAXWriter_H
#define UNIPAX_IMPORT_BIOPAX_BIOPAXWriter_H

#include<string>
#include<map>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include <QtXml/QXmlStreamWriter>

namespace UniPAX
{

	/** \brief class for reading the BioPAX Level 3 format.

		  \ingroup Importer
	 */
	class UNIPAX_EXPORT BIOPAXWriter
	{
	public:

		static const int SERIAL_EXPORT = 0;
		static const int INTEGRATIVE_EXPORT = 1;


		/**	@name	standard methods
		 */
		//@{
		/// \brief a standard Constructor
		BIOPAXWriter();
		/// \brief a standard Constructor with filename parameter
		BIOPAXWriter(const std::string& filename);
		/// \brief copy constructor
		BIOPAXWriter(const BIOPAXWriter& to_copy);
		/// \brief a standard destructor
		~BIOPAXWriter();
		/// \brief an assignment operator
		BIOPAXWriter& operator=(const BIOPAXWriter& assign);
		//@}

		/**	@name miscellaneous
		 */
		//@{

		/// \brief set file for reading
		bool setFilename(const std::string& filename);

		/// \brief parse file */
		bool write();
		bool write(QXmlStreamWriter& out);
		bool write(const std::string& filename);

		void openDocument(QXmlStreamWriter& out);
		void writeHeader(QXmlStreamWriter& out);
		void writeOntology(QXmlStreamWriter& out);
		void writeFooter(QXmlStreamWriter& out);
		void closeDocument(QXmlStreamWriter& out);

		void writeObject(std::string id, std::string type,QXmlStreamWriter& out);
		void setDebug(bool debug);

		// use BIOPAXWriter::SERIAL_EXPORT or BIOPAXWriter::INTEGRATIVE_EXPORT
		void setExportType(int export_type);

		void setPersistenceManager(PersistenceManager& manager_);

		//@}

	private:
		bool debug;
		int export_type;
		std::string xmlfilename;
		PersistenceManager manager;

		std::map<std::string, bool> objects_written;

	};

}
#endif

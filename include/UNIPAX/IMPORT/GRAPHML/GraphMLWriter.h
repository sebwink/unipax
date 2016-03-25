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


#ifndef UNIPAX_IMPORT_GRAPHML_GraphMLWriter_H
#define UNIPAX_IMPORT_GRAPHML_GraphMLWriter_H

#include<string>
#include<set>
#include<map>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include <QtXml/QXmlStreamWriter>

namespace UniPAX
{

	/** \brief class for writing the GraphML format.

		  \ingroup Importer
	 */
	class UNIPAX_EXPORT GraphMLWriter
	{
	public:

		/**	@name	standard methods
		 */
		//@{
		/// \brief a standard Constructor
		GraphMLWriter();
		/// \brief a standard Constructor with filename parameter
		GraphMLWriter(const std::string& filename);
		/// \brief copy constructor
		GraphMLWriter(const GraphMLWriter& to_copy);
		/// \brief a standard destructor
		~GraphMLWriter();
		/// \brief an assignment operator
		GraphMLWriter& operator=(const GraphMLWriter& assign);
		//@}

		/**	@name miscellaneous
		 */
		//@{

		void init();

		/// \brief set file for reading
		bool setFilename(const std::string& filename);

		/// \brief parse file */
		bool write();
		bool write(QXmlStreamWriter& out);
		bool write(const std::string& filename);
		/// \brief set ids of objects to write out
		void restrictToObjects(std::set<UnipaxId> toWrite);
		/// \brief write out only objects from the path
		bool writePath(QXmlStreamWriter& out, std::vector<UnipaxId> ordered_path_nodes);

		void openDocument(QXmlStreamWriter& out);
		void writeHeader(QXmlStreamWriter& out);
		void writeFooter(QXmlStreamWriter& out);
		void closeDocument(QXmlStreamWriter& out);

		void setDebug(bool debug);

		void setPersistenceManager(PersistenceManager& manager_);

		//@}

	private:
		bool debug;
		int export_type;
		std::string xmlfilename;
		PersistenceManager manager;

		std::map<std::string, std::string> object_type;
		std::map<std::string, bool> objects_written;

		std::set<UnipaxId> objectsToWrite;
	};

}
#endif

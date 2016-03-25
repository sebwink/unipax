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


#ifndef UNIPAX_IMPORT_SBML_SBMLREADER_H
#define UNIPAX_IMPORT_SBML_SBMLREADER_H

#include<string>
#include<vector>
#include<sbml/SBMLDocument.h>
#include<sbml/Reaction.h>
#include<sbml/SBMLTypes.h>
#include<boost/algorithm/string_regex.hpp>
#include<boost/lexical_cast.hpp>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include<UNIPAX/IMPORT/SBML/SBMLConfigHandler.h>
#include<UNIPAX/IMPORT/SBML/MiriamLinkREST.h>
#include<UNIPAX/KERNEL/all.h>

namespace UniPAX
{

	/** \brief class for reading the BioPAX Level 3 format.

		  \ingroup Importer
	 */
	class UNIPAX_EXPORT SBMLReader
	{
	public:

		/**	@name	standard methods
		 */
		//@{
		/// \brief a standard Constructor
		SBMLReader();
		/// \brief a standard Constructor with filename parameter
		SBMLReader(const std::string& filename);
		/// \brief copy constructor
		SBMLReader(const SBMLReader& to_copy);
		/// \brief a standard destructor
		~SBMLReader();
		/// \brief an assignment operator
		SBMLReader& operator=(const SBMLReader& assign);
		//@}

		/**	@name miscellaneous
		 */
		//@{

		/// \brief set file for reading
		bool setFilename(const std::string& filename);

		/// \brief init reader before parse of file
		bool init(std::string proxy_host, int proxy_port, std::string config_file_path);

		/// \brief parse file */
		bool parse();

		/// \brief parse file */
		bool parse(const std::string& filename);
		void setDebug(bool debug);
		void createObjectsOnly(bool onlyObjects);
		std::map<std::string, boost::shared_ptr<UPBase> > getData();

		PersistenceManager& getPersistenceManager();
		const PersistenceManager& getPersistenceManager() const;

		//@}

	private:

		bool parseConfigFile(std::string mapping_filename);

		SBMLConfigHandler configHandler;
		/// \returns true if mapping was successful */
		bool mapToUniPAX(libsbml::SBMLDocument* document, PersistenceManager& manager);

		//std::string createId(const ::SBase* object);
		//std::string createId(const ASTNode* object);
		std::string createId(const std::string unique);
		unsigned long int object_counter;
		std::map<std::string, std::string> object_id;

		std::vector<std::string> annotation_types;

		std::string xmlfilename;
		PersistenceManager manager;
		UniPAX::MiriamLink * miriamLink;

		std::pair<std::string, std::string> parseMiriamAnnotation(std::string annotation);
		std::vector<std::string> parseURIs(std::string annotation);

		bool debug;
		bool objects_only;

		enum ReactionType { TRANSPORT, COMPLEX_ASSEMBLY, COMPLEX_DISASSEMBLY, BIOCHEMICAL_REACTION };
		enum ControlType { CONTROL, CATALYSIS };

		ReactionType getReactionType(libsbml::Reaction* reaction);
	};

}
#endif

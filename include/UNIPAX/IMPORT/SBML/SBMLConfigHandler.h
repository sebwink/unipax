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

#ifndef UNIPAX_IMPORT_SBML_SBMLCONFIGHANDLER_H
#define UNIPAX_IMPORT_SBML_SBMLCONFIGHANDLER_H

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include <QtXml/QXmlDefaultHandler>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include<UNIPAX/IMPORT/SBML/MiriamLinkREST.h>

namespace UniPAX
{

  /** \brief Handler class for the mapping file.

	    This class intends to be the handler class for SAX-parsing of the mapping file which maps Miriam URIs to BioPAX PhysicalEntity subclasses.
      
      \ingroup Importer
  */
	class UNIPAX_EXPORT SBMLConfigHandler : public QXmlDefaultHandler {

	public:

		/**	@name	Constructors and Destructors
		 */
		//@{
		/// \brief a standard Constructor
		SBMLConfigHandler();

		/// \brief a standard destructor
		~SBMLConfigHandler();

		SBMLConfigHandler(const SBMLConfigHandler & arg);

		SBMLConfigHandler & operator =(const SBMLConfigHandler & arg);
		//@}

		/**	@name SAX methods
		 */
		//@{
		/// reading start tag
		bool startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts);
		/// character reading
		bool characters(const QString & ch);	
		/// reading end tag
		bool endElement(const QString & namespaceURI, const QString & localName, const QString & qName);
		/// finish document reading
		bool endDocument();
		//@}

		/**	@name SAX ErrorHandler interface
		 */
		//@{	
		/// \brief handles warning messages
		bool warning(const QXmlParseException & exception);
		/// \brief handles error messages
		bool error(const QXmlParseException & exception);
		/// \brief handles fatal error messages
		bool fatalError(const QXmlParseException & exception);
		//@}

		/**	@name miscellaneous
		 */
		//@{
		void setDebug(bool debug);
		void createObjectsOnly(bool onlyObjects);
		PersistenceManager& getPersistenceManager();
		const PersistenceManager& getPersistenceManager() const;
		//@}
		UniPAX::MiriamLink * getMiriamLink();

		void setMiriamLink(UniPAX::MiriamLink * _miriamLink);

		std::map<std::string, std::string> getPublicationModel();
		std::map<std::string, std::string> getAnnotationSpecies();
		std::map<std::string, std::string> getSpeciesAnnotationMap();
		std::map<std::string, std::string> getTaxonomyMap();

	private:

		bool ignore_rest;
		void annotationMIRIAM(std::string uri, std::map<std::string, std::string> & table, std::string type);

		std::vector<std::string> tree_structure;
		std::vector<std::string> id_structure;
		std::vector<std::string> attribute_structure;
		std::vector<std::string> object_tree_structure;

		std::string current_data;
		std::string last_id;
		std::string species_type; // actual species type (mapping target)

		UniPAX::MiriamLink * miriamLink;

		std::map<std::string, std::string> * map_pointer; // points always to the actual map to be filled
		std::map<std::string, std::string> publicationModel; // <URI_database_Publication, official_Name>
		std::map<std::string, std::string> annotationSpecies; // <DB_URI, BioPAX_subclass_of_physicalEntity>
		std::map<std::string, std::string> speciesAnnotationMap; // <URI_database_Species, official_Name>
		std::map<std::string, std::string> taxonomyMap; // <?>

		bool debug;
		bool objects_only;

		//some helper functions
		/*! \brief Remove not unprintable characters at the end and beginning of a string*/
		std::string cleanString(std::string s);
		/*! \brief Convert a string to a long number*/
		unsigned long string_to_long(std::string text);

	};
}

#endif


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

#include <UNIPAX/IMPORT/SBML/SBMLConfigHandler.h>
#include <QtCore/QString>
#include <sstream>

namespace UniPAX
{
/*!
					\brief the implementation of our file parser
 */


/*! \brief a standard ctor */
SBMLConfigHandler::SBMLConfigHandler() : debug(false), objects_only(false), publicationModel(), annotationSpecies(), speciesAnnotationMap(), taxonomyMap(), ignore_rest(false)
{
	//miriamLink = new MiriamWS::MiriamLink();
	//miriamLink->setProxy("www-cache.informatik.uni-tuebingen.de", 3128);
}

/*! \brief destructor */
SBMLConfigHandler::~SBMLConfigHandler()
{
}


UniPAX::SBMLConfigHandler::SBMLConfigHandler(const SBMLConfigHandler & arg)  :
										tree_structure(arg.tree_structure),
										object_tree_structure(arg.object_tree_structure),
										attribute_structure(arg.attribute_structure),
										id_structure(arg.id_structure),
										current_data(arg.current_data),
										last_id(arg.last_id),
										debug(arg.debug),
										objects_only(arg.objects_only),
										publicationModel(arg.publicationModel),
										annotationSpecies(arg.annotationSpecies),
										speciesAnnotationMap(arg.speciesAnnotationMap),
										taxonomyMap(arg.taxonomyMap),
										miriamLink(arg.miriamLink),
										ignore_rest(arg.ignore_rest)
{
}

UniPAX::SBMLConfigHandler & UniPAX::SBMLConfigHandler::operator =(const SBMLConfigHandler & arg)
{
	tree_structure = arg.tree_structure;
	object_tree_structure = arg.object_tree_structure;
	attribute_structure = arg.attribute_structure;
	id_structure = arg.id_structure;
	current_data = arg.current_data;
	last_id = arg.last_id;
	debug = arg.debug;
	objects_only = arg.objects_only;
	miriamLink = arg.miriamLink;
	publicationModel = arg.publicationModel;
	annotationSpecies = arg.annotationSpecies;
	speciesAnnotationMap = arg.speciesAnnotationMap;
	taxonomyMap = arg.taxonomyMap;
	ignore_rest =arg.ignore_rest;

	return *this;
}

// -----------------------------------------------------------------------
//  Implementations of the SAX DocumentHandler interface
// -----------------------------------------------------------------------

bool SBMLConfigHandler::startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & attributes)
{
	if (!ignore_rest)
	{
		std::string current_full_tag(qName.toStdString());
		std::string current_tag(localName.toStdString());
		std::string attr_name;
		std::string attr_value;

		if (debug)
			std::cout << "startElement : " << current_full_tag << std::endl;

		tree_structure.push_back(current_tag);
		current_data.clear();
		if (current_tag.compare("sbml2biopax") == 0)
		{
			if (tree_structure.size() != 1)
			{
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
				return false;
			}
			return true;
		}
		else if (current_tag.compare("sbml2biopaxAnnotationParameter_l3") == 0)
		{
			if (tree_structure.size() != 2)
			{
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
				return false;
			}
			return true;
		}
		else if (current_tag.compare("publicationModel") == 0)
		{
			if (tree_structure.size() != 3)
			{
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
				return false;
			}
			map_pointer = &publicationModel;
			return true;
		}
		else if (current_tag.compare("publication") == 0)
		{
			if (tree_structure.size() != 4)
			{
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
				return false;
			}
			//publicationModel[] =;

			return true;
		}
		else if (current_tag.compare("speciesAnnotationMap") == 0)
		{
			if (tree_structure.size() != 3)
			{
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
				return false;
			}
			map_pointer = &speciesAnnotationMap;
			return true;
		}
		else if (current_tag.compare("species") == 0)
		{
			if (tree_structure.size() < 4)
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
			return true;
		}
		else if (current_tag.compare("taxonomyMap") == 0)
		{
			if (tree_structure.size() != 3)
			{
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
				return false;
			}
			map_pointer = &taxonomyMap;
			return true;
		}
		else if (current_tag.compare("taxonomy") == 0)
		{
			if (tree_structure.size() != 4)
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
			return true;
		}
		else if (current_tag.compare("annotationSpecies") == 0)
		{
			if (tree_structure.size() != 3)
			{
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
				return false;
			}
			map_pointer = &annotationSpecies;
			return true;
		}
		else if (current_tag.compare("physicalEntity") == 0)
		{
			if (tree_structure.size() != 4)
			{
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
				return false;
			}
			species_type = attributes.value("classBioPAX").toStdString();
			return true;
		}
		else if (current_tag.compare("constraint") == 0)
		{
			if (tree_structure.size() != 5)
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
			return true;
		}
	}
	return true;
}

bool SBMLConfigHandler::characters(const QString & chars)
{
	if (!ignore_rest)
	{
		current_data = chars.toStdString();
		if (debug) std::cout << "characters: " << current_data << std::endl;
	}
	return true;
}

bool SBMLConfigHandler::endElement( const QString& namespaceURI, const QString& localName, const QString& qName)
{
	if (!ignore_rest)
	{
		if (debug) std::cout << "endElement" << std::endl;
		std::string current_full_tag(qName.toStdString());
		std::string current_tag(localName.toStdString());
		if (debug)
		{
			std::cout << "Current tag: " << current_tag << std::endl;
			std::cout << "	with data: " << current_data << std::endl;
		}

		// check if this is closing tag for object attribute reference by id
		if (current_tag != tree_structure.back())
		{
			if (debug) std::cout << "missing closing '" << tree_structure.back() << "' tag." << std::endl;
			return true;
		}
		if (current_tag.compare("sbml2biopaxAnnotationParameter_l3") == 0)
		{
			if (tree_structure.size() != 2)
			{
				std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
				return false;
			}
			ignore_rest = true;
			return true;
		}
		// only if we have data, we fill it into the maps
		if (current_data.compare("") != 0)
		{
			if (current_tag.compare("publication") == 0)
			{ // publicationModel
				if (tree_structure.size() != 4)
				{
					std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
					return false;
				}
				annotationMIRIAM(current_data, publicationModel, miriamLink->getName(current_data));

			}
			else if (current_tag.compare("species") == 0)
			{
				if (tree_structure.size() < 4)
				{
					std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
					return false;
				}
				if (map_pointer == &speciesAnnotationMap)
				{ // speciesAnnotationMap
					annotationMIRIAM(current_data, speciesAnnotationMap, miriamLink->getName(current_data));

				}
				else if (map_pointer == &annotationSpecies)
				{
					annotationMIRIAM(current_data, annotationSpecies, species_type);
				}
				else
				{
					std::cerr << "Missplaced species tag." << std::endl;
					return false;
				}
			}
			else if (current_tag.compare("taxonomy") == 0)
			{ // taxonomyMap
				if (tree_structure.size() != 4)
				{
					std::cerr << "Invalid document structure: " << current_tag << " at depth " << tree_structure.size() << std::endl;
					return false;
				}
				annotationMIRIAM(current_data, taxonomyMap, miriamLink->getName(current_data));

			}


		}

		if (debug) std::cout << "done" << std::endl;
		tree_structure.pop_back();
	}
	return true;

}

bool SBMLConfigHandler::endDocument()
{
	return true;
}


// -----------------------------------------------------------------------
//  Implementations of the SAX ErrorHandler interface
// -----------------------------------------------------------------------

bool SBMLConfigHandler::warning(const QXmlParseException & exception)
{
	std::string message(exception.message().toStdString());
	std::string filename(exception.systemId().toStdString());

	std::cerr << "SBMLConfigHandler - Warning: " << message
			<< ", at file: " << filename
			<< ", at line: " << exception.lineNumber()
			<< ", at char: " << exception.columnNumber() << std::endl;

	return true;
}

bool SBMLConfigHandler::error(const QXmlParseException & exception)
{
	std::string message(exception.message().toStdString());
	std::string filename(exception.systemId().toStdString());

	std::cerr << "SBMLConfigHandler - Warning: " << message
			<< ", at file: " << filename
			<< ", at line: " << exception.lineNumber()
			<< ", at char: " << exception.columnNumber() << std::endl;

	return true;
}

bool SBMLConfigHandler::fatalError(const QXmlParseException & exception)
{
	std::string message(exception.message().toStdString());
	std::string filename(exception.systemId().toStdString());

	std::cerr << "SBMLConfigHandler - Warning: " << message
			<< ", at file: " << filename
			<< ", at line: " << exception.lineNumber()
			<< ", at char: " << exception.columnNumber() << std::endl;

	return true;
}

// -----------------------------------------------------------------------
//  Implementation of our Data-Container / Handling & Helper functions
// -----------------------------------------------------------------------


/*! \brief Convert a string to a long number*/
unsigned long SBMLConfigHandler::string_to_long(std::string text)
{
	std::stringstream sout(text);
	unsigned long number = 0;
	sout >> number;
	return number;
}

/*! \brief Remove not unprintable characters at the end and beginning of a string*/
std::string SBMLConfigHandler::cleanString(std::string s)
{
	unsigned int front=0, end=s.length();

	//remove leading spaces
	for (;front < s.length(); front++)
	{
		if (!((s[front] == '\n') || (s[front] == '\r') || (s[front] == '\t') || (s[front] == ' '))) break;
	}

	//remove ending spaces
	for (; end > 0; end--)
	{
		if (!((s[end-1] == '\n') || (s[end-1] == '\r') || (s[end-1] == '\t') || (s[end-1] == ' '))) break;
	}

	return s.substr(front,end-front);
}


void SBMLConfigHandler::setDebug(bool debug_)
{
	debug = debug_;
}

void SBMLConfigHandler::createObjectsOnly(bool objects_only_)
{
	objects_only = objects_only_;
}

/*UniPAX::PersistenceManager& SBMLConfigHandler::getPersistenceManager()
					{
					return manager;
					}*/

/*const UniPAX::PersistenceManager& SBMLConfigHandler::getPersistenceManager() const
					{
					return manager;
					}*/

UniPAX::MiriamLink * SBMLConfigHandler::getMiriamLink()
{
	return miriamLink;
}

void SBMLConfigHandler::annotationMIRIAM(std::string uri, std::map<std::string, std::string> & table, std::string type) {

	std::string name = miriamLink->getName(uri);

	//std::string officialURN = miriamLink->getDataTypeURN(uri);
	//SBML2BioPAX_l3.officialURIs.put(URI, officialURN);
	//SBML2BioPAX_l3.officialNames.put(URI, name);

	if (name.empty())
	{
		std::cout <<  uri << " URI is not contained in MIRIAM database, no answer possible" << std::endl;
	}
	else
	{
		std::vector<std::string> uris = miriamLink->getDataTypeURIs(name);
		for (int i = 0; i < uris.size(); i++) {
			table[uris[i]] = type;
			if(debug)  std::cout << "key: "+uris[i]+"   value: "+ type << std::endl;
		}
	}

}

std::map<std::string, std::string> SBMLConfigHandler::getPublicationModel()
{
	return publicationModel;
}

std::map<std::string, std::string> SBMLConfigHandler::getAnnotationSpecies()
{
	return annotationSpecies;
}

std::map<std::string, std::string> SBMLConfigHandler::getSpeciesAnnotationMap()
{
	return speciesAnnotationMap;
}

std::map<std::string, std::string> SBMLConfigHandler::getTaxonomyMap()
{
	return taxonomyMap;
}

void SBMLConfigHandler::setMiriamLink(UniPAX::MiriamLink * _miriamLink)
{
	miriamLink = _miriamLink;
}

} //namespace

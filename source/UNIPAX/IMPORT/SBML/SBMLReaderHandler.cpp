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

#include <UNIPAX/IMPORT/SBML/SBMLReaderHandler.h>
#include <QtCore/QString>
#include <sstream>

namespace UniPAX
{
/*!
    \brief the implementation of our file parser
 */


/*! \brief a standard ctor */
SBMLReaderHandler::SBMLReaderHandler() : debug(false), objects_only(false)
{
}

/*! \brief destructor */
SBMLReaderHandler::~SBMLReaderHandler()
{
}


UniPAX::SBMLReaderHandler::SBMLReaderHandler(const SBMLReaderHandler & arg)  :
		manager(arg.manager),
		tree_structure(arg.tree_structure),
		object_tree_structure(arg.object_tree_structure),
		attribute_structure(arg.attribute_structure),
		id_structure(arg.id_structure),
		current_data(arg.current_data),
		last_id(arg.last_id),
		debug(arg.debug),
		objects_only(arg.objects_only)
{
}

UniPAX::SBMLReaderHandler & UniPAX::SBMLReaderHandler::operator =(const SBMLReaderHandler & arg)
{
	manager = arg.manager;
	tree_structure = arg.tree_structure;
	object_tree_structure = arg.object_tree_structure;
	attribute_structure = arg.attribute_structure;
	id_structure = arg.id_structure;
	current_data = arg.current_data;
	last_id = arg.last_id;
	debug = arg.debug;
	objects_only = arg.objects_only;

	return *this;
}

// -----------------------------------------------------------------------
//  Implementations of the SAX DocumentHandler interface
// -----------------------------------------------------------------------

bool SBMLReaderHandler::startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & attributes)
{
	std::string current_full_tag(qName.toStdString());
	std::string current_tag(localName.toStdString());
	std::string attr_name;
	std::string attr_value;

//	std::cout << "startElement : " << current_full_tag << std::endl;

	void* current_object = 0;

	// neglect the non biopax tags
	if (current_full_tag.substr(0,3) != "bp:")
	{
//		std::cout << current_full_tag.substr(0,3) << std::endl;
		return true;
	}




	// if only objects_only flag is true ... only objects instances created, but no attributes set
	if (objects_only)
	{
		for (int index = 0; index < attributes.length(); index++)
		{
			attr_name = attributes.qName(index).toStdString();
			attr_value = attributes.value(index).toStdString();

			if (attr_name == "rdf:ID" || attr_name == "rdf:about")
			{
				// create new instance
				if (debug) std::cout << "createInstance(" << attr_value << "," << current_tag << ") -> ";
				current_object = manager.createInstance(attr_value, current_tag);
				if (debug) std::cout << "done : " << current_object << std::endl;

				if (current_object == 0)
				{
					std::cerr << "Instance was not created: id - " << attr_value << " , object - " << current_tag << std::endl;
					return false;
				}
			}
		}
		return true;
	}



	tree_structure.push_back(current_tag);

	// new data tag
	current_data = "";


	for (int index = 0; index < attributes.length(); index++)
	{
		attr_name = attributes.qName(index).toStdString();
		attr_value = attributes.value(index).toStdString();

		if (attr_name == "rdf:ID" || attr_name == "rdf:about")
		{
			// create new instance
			if (debug) std::cout << "createInstance(" << attr_value << "," << current_tag << ") -> ";
			current_object = manager.createInstance(attr_value, current_tag);
			if (debug) std::cout << "done : " << current_object << std::endl;

			// store new instance type in the object_tree_structure
			object_tree_structure.push_back(current_tag);
			if (current_object == 0)
			{
				std::cerr << "Instance was not created: id - " << attr_value << " , object - " << current_tag << std::endl;
				return false;
			}
			id_structure.push_back(attr_value);
		}
		else if (attr_name == "rdf:datatype")
		{
			// store new attribute type in the attribute_structure
			attribute_structure.push_back(current_tag);
			if (debug) std::cout << "attribute start tag -> " << current_tag << std::endl;

		}
		else if (attr_name == "rdf:resource")
		{
			// remove leading # from resource id
			if (attr_value.substr(0,1) == "#")
				attr_value = attr_value.substr(1, attr_value.length()-1);

			// store new attribute type in the attribute_structure
			if (debug) std::cout << "setAttribute(" << id_structure.back() << "," << current_tag << "," << attr_value << ") -> ";
			if (!manager.setAttribute(id_structure.back(), current_tag, attr_value))
			{
				if (debug) std::cout << std::endl;
				std::cerr << "Attribute was not set: id - " << id_structure.back() << " , attribute - " << current_tag << " , value - " << attr_value << std::endl;
				return false;
			}
			if (debug) std::cout << "done" << std::endl;

			tree_structure.pop_back();

		}
	}


//	std::cerr << "SBMLReaderHandler: Found " << serialize_stack(status) << " as element and don't know how to handle..." << std::endl;

	return true;
}

bool SBMLReaderHandler::characters(const QString & chars)
{
	std::string message(chars.toStdString());
	current_data = message;

//	std::cout << "characters" << std::endl;

	return true;
}

bool SBMLReaderHandler::endElement( const QString& namespaceURI, const QString& localName, const QString& qName)
{
	std::string current_full_tag(qName.toStdString());
	std::string current_tag(localName.toStdString());

//	std::cout << "endElement : " << current_full_tag << std::endl;

//	std::cout << "id_structure: " << id_structure.size() << " - " << (!id_structure.empty()?id_structure.back():"") << std::endl;
//	std::cout << "tree_structure: " << tree_structure.size() << " - " << (!tree_structure.empty()?tree_structure.back():"") << std::endl;
//	std::cout << "object_tree_structure: " << object_tree_structure.size() << " - " << (!object_tree_structure.empty()?object_tree_structure.back():"") << std::endl;
//	std::cout << "attribute_structure: " << attribute_structure.size() << " - " << (!attribute_structure.empty()?attribute_structure.back():"") << std::endl;


	// if only objects_only flag is true ... only objects instances created, but no attributes set
	if (objects_only)
		return true;



	if (current_full_tag.substr(0,3) != "bp:")
	{
//		std::cout << current_full_tag.substr(0,3) << std::endl;
		return true;
	}


	// check if this is closing tag for object attribute reference by id
	if (current_tag != tree_structure.back())
	{
		if (debug) std::cout << "closing object attribute reference" << std::endl;
		return true;
	}


	// check for attribute
	if (!attribute_structure.empty() && attribute_structure.back() == current_tag)
	{
		// write attribute and remove from attribute_structure
		if (debug) std::cout << "setAttribute(" << id_structure.back() << "," << current_tag << "," << current_data << ") -> ";
		if (!manager.setAttribute(id_structure.back(), current_tag, current_data))
		{
			if (debug) std::cout << std::endl;
			std::cerr << "Attribute was not set: id - " << id_structure.back() << " , attribute - " << current_tag << " , value - " << current_data << std::endl;
			return false;
		}
		if (debug) std::cout << "done" << std::endl;

		attribute_structure.pop_back();


		tree_structure.pop_back();
		return true;
	}

	// check for closing object instance
	if (!object_tree_structure.empty() && object_tree_structure.back() == current_tag)
	{
		// do nothing and remove from object_tree_structure
		object_tree_structure.pop_back();
		// store the id for object attribute reference if necessary
		last_id = id_structure.back();
		id_structure.pop_back();


		tree_structure.pop_back();
		return true;
	}

	// check for closing object attribute of a new generated object
	// set object attribute
	if (debug) std::cout << "setAttribute(" << id_structure.back() << "," << current_tag << "," << last_id << ") -> ";
	if (!manager.setAttribute(id_structure.back(), current_tag, last_id))
	{
		if (debug) std::cout << std::endl;
		std::cerr << "Attribute was not set: id - " << id_structure.back() << " , attribute - " << current_tag << " , value - " << last_id << std::endl;
		return false;
	}
	if (debug) std::cout << "done" << std::endl;


	last_id.clear();
	tree_structure.pop_back();
	return true;

}

bool SBMLReaderHandler::endDocument()
{
	return true;
}


// -----------------------------------------------------------------------
//  Implementations of the SAX ErrorHandler interface
// -----------------------------------------------------------------------

bool SBMLReaderHandler::warning(const QXmlParseException & exception)
{
	std::string message(exception.message().toStdString());
	std::string filename(exception.systemId().toStdString());

	std::cerr << "SBMLReaderHandler - Warning: " << message
			<< ", at file: " << filename
			<< ", at line: " << exception.lineNumber()
			<< ", at char: " << exception.columnNumber() << std::endl;

	return true;
}

bool SBMLReaderHandler::error(const QXmlParseException & exception)
{
	std::string message(exception.message().toStdString());
	std::string filename(exception.systemId().toStdString());

	std::cerr << "SBMLReaderHandler - Warning: " << message
			<< ", at file: " << filename
			<< ", at line: " << exception.lineNumber()
			<< ", at char: " << exception.columnNumber() << std::endl;

	return true;
}

bool SBMLReaderHandler::fatalError(const QXmlParseException & exception)
{
	std::string message(exception.message().toStdString());
	std::string filename(exception.systemId().toStdString());

	std::cerr << "SBMLReaderHandler - Warning: " << message
			<< ", at file: " << filename
			<< ", at line: " << exception.lineNumber()
			<< ", at char: " << exception.columnNumber() << std::endl;

	return true;
}

// -----------------------------------------------------------------------
//  Implementation of our Data-Container / Handling & Helper functions
// -----------------------------------------------------------------------


/*! \brief Convert a string to a long number*/
unsigned long SBMLReaderHandler::string_to_long(std::string text)
{
	std::stringstream sout(text);
	unsigned long number = 0;
	sout >> number;
	return number;
}

/*! \brief Remove not unprintable characters at the end and beginning of a string*/
std::string SBMLReaderHandler::cleanString(std::string s)
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


void SBMLReaderHandler::setDebug(bool debug_)
{
	debug = debug_;
}

void SBMLReaderHandler::createObjectsOnly(bool objects_only_)
{
	objects_only = objects_only_;
}

UniPAX::PersistenceManager& SBMLReaderHandler::getPersistenceManager()
{
	return manager;
}

const UniPAX::PersistenceManager& SBMLReaderHandler::getPersistenceManager() const
{
	return manager;
}



} //namespace

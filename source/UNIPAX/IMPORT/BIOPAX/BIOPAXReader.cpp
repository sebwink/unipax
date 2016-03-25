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

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXReader.h>
#include <iostream>
#include <sstream>
#include <QtCore/QFile>
#include <QtXml/QXmlSimpleReader>

namespace UniPAX
{

/*! \brief a standard constructor */
BIOPAXReader::BIOPAXReader() : xmlfilename("")
{
}

/*! \brief a standard constructor with filename parameter*/
BIOPAXReader::BIOPAXReader(const std::string& filename)
{
	xmlfilename=filename;
}

/*! \brief set file for reading*/
bool BIOPAXReader::setFilename(const std::string& filename)
{
	if (filename != "")
	{
		xmlfilename=filename;
		return true;
	}
	else
	{
		return false;
	}
}

/*! \brief a copy constructor */
BIOPAXReader::BIOPAXReader(const BIOPAXReader& to_copy): xmlfilename(to_copy.xmlfilename)
{
}

/*! \brief destructor */
BIOPAXReader::~BIOPAXReader()
{
}

/*! \brief an assignment operator */
BIOPAXReader& BIOPAXReader::operator=(const BIOPAXReader& assign)
{
	xmlfilename=assign.xmlfilename;

	return (*this);
}

/*! \brief read file with filename */
bool BIOPAXReader::parse(const std::string& filename)
{
	setFilename(filename);

	return parse();
}

/*! \brief read file */
bool BIOPAXReader::parse()
{
	//Parser is initialized with the file?
	if (xmlfilename!="")
	{

		QFile xmlFile( QString(xmlfilename.c_str()) );
		QXmlInputSource source( &xmlFile );
		QXmlSimpleReader reader;
		reader.setContentHandler( &xmlhandler );
		reader.setErrorHandler( &xmlhandler );
		reader.parse( source );

		return true;
	}
	else
		return false;
}


void BIOPAXReader::setDebug(bool debug_)
{
	xmlhandler.setDebug(debug_);
}

void BIOPAXReader::createObjectsOnly(bool objects_only_)
{
	xmlhandler.createObjectsOnly(objects_only_);
}

void BIOPAXReader::setErrorOnInconsistentData(bool errorOnInconsistentData_)
{
	xmlhandler.setErrorOnInconsistentData(errorOnInconsistentData_);
}


std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > BIOPAXReader::getData()
{
	return xmlhandler.getPersistenceManager().getData();
}


UniPAX::PersistenceManager& BIOPAXReader::getPersistenceManager()
{
	return xmlhandler.getPersistenceManager();
}

const UniPAX::PersistenceManager& BIOPAXReader::getPersistenceManager() const
{
	return xmlhandler.getPersistenceManager();
}

} // namespace

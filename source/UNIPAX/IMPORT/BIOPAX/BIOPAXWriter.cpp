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

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#include <iostream>
#include <sstream>
#include <QtCore/QFile>
#include <QtXml/QXmlSimpleReader>

namespace UniPAX
{

/*! \brief a standard constructor */
BIOPAXWriter::BIOPAXWriter() : xmlfilename(""), export_type(0), debug(true)
{
}

/*! \brief a standard constructor with filename parameter*/
BIOPAXWriter::BIOPAXWriter(const std::string& filename) : xmlfilename(filename), export_type(0), debug(true)
{
}

/*! \brief set file for reading*/
bool BIOPAXWriter::setFilename(const std::string& filename)
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
BIOPAXWriter::BIOPAXWriter(const BIOPAXWriter& arg)  :
				debug(arg.debug),
				manager(arg.manager),
				xmlfilename(arg.xmlfilename),
				export_type(arg.export_type)
{
}

/*! \brief destructor */
BIOPAXWriter::~BIOPAXWriter()
{
}

/*! \brief an assignment operator */
BIOPAXWriter& BIOPAXWriter::operator=(const BIOPAXWriter& arg)
{
	debug = arg.debug;
	manager = arg.manager;
	xmlfilename = arg.xmlfilename;
	export_type = arg.export_type;

	return (*this);
}

/*! \brief read file with filename */
bool BIOPAXWriter::write(const std::string& filename)
{
	setFilename(filename);

	return write();
}

/*! \brief read file */
bool BIOPAXWriter::write()
{

	//Parser is initialized with the file?
	if (xmlfilename!="")
	{

		QFile xmlFile( QString::fromStdString(xmlfilename) );

		if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			std::cerr << "Cannot open the file " << xmlfilename << std::endl;
			return false;
		}

		if (debug)
		{
			if (export_type == UniPAX::BIOPAXWriter::INTEGRATIVE_EXPORT)
				std::cout << "export type = INTEGRATIVE_EXPORT" << std::endl;
			if (export_type == UniPAX::BIOPAXWriter::SERIAL_EXPORT)
				std::cout << "export type = SERIAL_EXPORT" << std::endl;
		}




		if (debug) std::cout << "Open the file " << xmlfilename << std::endl;

		QXmlStreamWriter out(&xmlFile);

		openDocument(out);
		writeHeader(out);
		writeOntology(out);

		write(out);

		writeFooter(out);
		closeDocument(out);

		if (debug) std::cout << "close file" << std::endl;
		xmlFile.close();
		return true;
	}
	else
	{
		std::cerr << "Please specify a file name" << std::endl;
		return false;
	}
}

void BIOPAXWriter::openDocument(QXmlStreamWriter& out)
{
	out.setCodec("UTF-8");
	out.setAutoFormatting(true);
	out.writeStartDocument();
}

void BIOPAXWriter::writeHeader(QXmlStreamWriter& out)
{
	// first write the RDF tag
	out.writeStartElement("rdf:RDF");
	out.writeAttribute("xml:base", "http://www.biopax.org/releases/biopax-level3.owl");
	out.writeAttribute("xmlns", "http://www.biopax.org/releases/biopax-level3.owl#");
	out.writeAttribute("xmlns:owl", "http://www.w3.org/2002/07/owl#");
	out.writeAttribute("xmlns:rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
	out.writeAttribute("xmlns:rdfs", "http://www.w3.org/2000/01/rdf-schema#");
	out.writeAttribute("xmlns:xs", "http://www.w3.org/2001/XMLSchema#");
	out.writeAttribute("xmlns:bp", "http://www.biopax.org/release/biopax-level3.owl#");
}

void BIOPAXWriter::writeOntology(QXmlStreamWriter& out)
{
	// next write Ontology tag
	out.writeStartElement("owl:Ontology");
	out.writeAttribute("rdf:about", "");
	out.writeStartElement("owl:imports");
	out.writeAttribute("rdf:resource", "http://www.biopax.org/releases/biopax-level3.owl");
	out.writeEndElement();
	out.writeTextElement("rdfs:comment", "UniPAX XML Export");
	out.writeEndElement();
}

void BIOPAXWriter::writeFooter(QXmlStreamWriter& out)
{
	// close RDF and document
	out.writeEndElement();
}

void BIOPAXWriter::closeDocument(QXmlStreamWriter& out)
{
	out.writeEndDocument();
}


/*! \brief read file */
bool BIOPAXWriter::write(QXmlStreamWriter& out)
{
	if (debug) std::cout << "fetch instances from persistence manager -> ";
	// fetch all known instances from the persistence manager
	std::map<std::string, std::string> data_type = manager.getIdToType();
	if (debug) std::cout << data_type.size() << std::endl;

	std::map<std::string, std::string>::iterator it;
	std::string current_id;
	std::string current_type;
	std::vector<std::pair<std::string,std::string> > attributes;
	std::vector<std::pair<std::string,std::string> >::iterator at_it;


	// go through all instances known by the persistence manager
	for (it = data_type.begin(); it != data_type.end(); it++)
	{
		current_id = it->first;
		current_type = it->second;


		// this line should be the only .... for different export types ...
		//			writeObject(current_id, current_type, out);

		attributes.clear();

		if (debug) std::cout << "write Instance of '" << current_type << "' , id '" << current_id << "' -> ";

		// write the instance
		out.writeStartElement("bp:"+QString::fromStdString(current_type));
		out.writeAttribute("rdf:ID", QString::fromStdString(current_id));

		// fetch all attributes of the instance
		manager.getAttribute(current_id, attributes);
		for (at_it = attributes.begin(); at_it != attributes.end(); at_it++)
		{
			// check if attribute was object instance
			if (at_it->first[0] == '#')
			{

				if (debug) std::cout << std::endl << "\twrite object attribute (" << at_it->first.substr(1,at_it->first.length()-1) << " -> " << at_it->second << ") ";
				out.writeStartElement("bp:"+QString::fromStdString(at_it->first.substr(1,at_it->first.length()-1)));
				out.writeAttribute("rdf:resource", "#"+QString::fromStdString(at_it->second));
				out.writeEndElement();
				continue;
			}

			// attribute was primitive
			if (debug) std::cout << std::endl << "\twrite string attribute (" << at_it->first << " -> " << at_it->second << ") ";

//			std::cout << current_id << " (stdstring): " << at_it->second << " " << at_it->second.length() << std::endl;

			QString second(QString::fromStdString(at_it->second));
//			std::cout << current_id << " (second): " << second.toStdString() << std::endl;

			QStringList split(second.split(QChar('#')));

			QString type("string");
			QString value(split[0]);
//			std::cout << current_id << " (value): " << value.toStdString() << std::endl;

			if (split.length() == 2)
				type = split[1];


			out.writeStartElement("bp:"+QString::fromStdString(at_it->first));
			out.writeAttribute("rdf:datatype", type.prepend("http://www.w3.org/2001/XMLSchema#"));
			out.writeCharacters(value);
			out.writeEndElement();

		}

		// close the instance
		out.writeEndElement();
		if (debug) std::cout << std::endl ;

	}

	return true;

}

void BIOPAXWriter::writeObject(std::string id, std::string type, QXmlStreamWriter& out)
{
	std::map<std::string, std::string>::iterator it;
	std::vector<std::pair<std::string,std::string> > attributes;
	std::vector<std::pair<std::string,std::string> >::iterator at_it;

	attributes.clear();
	std::map<std::string, std::string> data_type = manager.getIdToType();

	// if INTEGRATIVE_EXPORT type ... check if already written
	if (export_type == UniPAX::BIOPAXWriter::INTEGRATIVE_EXPORT)
	{
		if (objects_written.find(id) != objects_written.end())
		{
			if (debug) std::cout << "Instance of '" << type << "' , id '" << id << "' already written";
			return;
		}
	}

	objects_written[id] = true;
	if (debug) std::cout << "write Instance of '" << type << "' , id '" << id << "' -> ";

	// write the instance
	out.writeStartElement("bp:"+QString::fromStdString(type));
	out.writeAttribute("rdf:ID", QString::fromStdString(id));

	// fetch all attributes of the instance
	bool okay = manager.getAttribute(id, attributes);
	if (okay)
	{
		for (at_it = attributes.begin(); at_it != attributes.end(); at_it++)
		{
			// check if attribute was object instance
			if (at_it->first[0] == '#')
			{
				// if INTEGRATIVE_EXPORT type ... check if already written
				it = data_type.find(at_it->second);
				if (   (objects_written.find(at_it->second) != objects_written.end())
						&& (export_type == UniPAX::BIOPAXWriter::INTEGRATIVE_EXPORT)
						&& (it != data_type.end()))
				{
					writeObject(at_it->second, it->second, out);
					objects_written[at_it->second] = true;
					continue;
				}

				// else write as reference
				if (debug) std::cout << std::endl << "\twrite object attribute (" << at_it->first.substr(1,at_it->first.length()-1) << " -> " << at_it->second << ") ";
				out.writeStartElement("bp:"+QString::fromStdString(at_it->first.substr(1,at_it->first.length()-1)));
				out.writeAttribute("rdf:resource", "#"+QString::fromStdString(at_it->second));
				out.writeEndElement();
				continue;
			}

			// attribute was string
			if (debug) std::cout << std::endl << "\twrite string attribute (" << at_it->first << " -> " << at_it->second << ") ";

			QString second(QString::fromStdString(at_it->second));
			QStringList split(second.split(QChar('#')));

			QString type("string");
			QString value(split[0]);

			if (split.length() == 2)
				type = split[1];


			out.writeStartElement("bp:"+QString::fromStdString(at_it->first));
			out.writeAttribute("rdf:datatype", type.prepend("http://www.w3.org/2001/XMLSchema#"));
			out.writeCharacters(value);
			out.writeEndElement();
//
//			out.writeStartElement("bp:"+QString::fromStdString(at_it->first));
//			out.writeAttribute("rdf:datatype", "http://www.w3.org/2001/XMLSchema#string");
//			out.writeCharacters(QString::fromStdString(at_it->second));
//			out.writeEndElement();

		}
	}
	else
	{
		std::cout << "Unable to write attributes for id: " << type << ":" << id << std::endl;
		for (std::vector<std::pair<std::string,std::string> >::iterator it = attributes.begin(); it != attributes.end(); it++)
			std::cout << "\t" << it->first << ":" << it->second << std::endl;

		manager.printErrors(std::cout, true);
	}

	// close the instance
	out.writeEndElement();
	if (debug) std::cout << std::endl ;

	return;
}







void BIOPAXWriter::setDebug(bool _debug)
{
	debug = _debug;
}


void BIOPAXWriter::setExportType(int _export_type)
{
	export_type = _export_type;
}


void BIOPAXWriter::setPersistenceManager(PersistenceManager& _manager)
{
	manager = _manager;
}


} // namespace

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

#include <UNIPAX/IMPORT/GENESET/GeneSetWriter.h>
#include <iostream>
#include <sstream>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <set>

#include <UNIPAX/KERNEL/BIOPAX/UnificationXref.h>

namespace UniPAX
{

GeneSetWriter::GeneSetWriter() : filename(""), debug(false), gmx_format(true)
{
}

GeneSetWriter::GeneSetWriter(const std::string& _filename) : debug(false), gmx_format(true)
{
	filename = _filename;
}

bool GeneSetWriter::setFilename(const std::string& _filename)
{
	if (_filename != "")
	{
		filename = _filename;
		return true;
	}
	else
	{
		return false;
	}
}

bool GeneSetWriter::setTitle(const std::string& _title)
{
	if (_title != "")
	{
		title = _title;
		return true;
	}
	else
	{
		return false;
	}
}

bool GeneSetWriter::setDescription(const std::string& _description)
{
	if (_description != "")
	{
		description = _description;
		return true;
	}
	else
	{
		return false;
	}
}

GeneSetWriter::GeneSetWriter(const GeneSetWriter& arg)  :
						manager(arg.manager),
						filename(arg.filename),
						title(arg.title),
						description(arg.description),
						debug(arg.debug),
						gmx_format(arg.gmx_format)
{
}

GeneSetWriter::~GeneSetWriter()
{
}

GeneSetWriter& GeneSetWriter::operator=(const GeneSetWriter& arg)
{
	manager = arg.manager;
	filename = arg.filename;
	title = arg.title;
	description = arg.description;
	debug = arg.debug;
	gmx_format = arg.gmx_format;

	return (*this);
}

void GeneSetWriter::setDebug(bool _debug)
{
	debug = _debug;
}

bool GeneSetWriter::write(const std::string& _filename)
{
	return write(_filename, true);
}

bool GeneSetWriter::write()
{
	return write(true);
}

bool GeneSetWriter::write(const std::string& _filename, bool use_gene_ids)
{
	setFilename(_filename);

	return write(use_gene_ids);
}

bool GeneSetWriter::write(const std::string& filename, bool use_gene_ids, bool gmx_format_)
{
	gmx_format = gmx_format_;

	return write(filename, use_gene_ids);
}



bool GeneSetWriter::write(bool use_gene_ids)
{

	//Parser is initialized with the file?
	if (filename!="")
	{

		QFile file( QString::fromStdString(filename) );

		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			std::cerr << "Cannot open the file " << filename << std::endl;
			return false;
		}


		if (debug) std::cout << "Open the file " << filename << std::endl;

		QTextStream out(&file);

		if (!write(out, use_gene_ids))
		{
			if (debug) std::cout << "close file" << std::endl;
			file.close();
			return false;
		}

		if (debug) std::cout << "close file" << std::endl;
		file.close();
		return true;
	}
	else
	{
		std::cerr << "Please specify a file name" << std::endl;
		return false;
	}
}

bool GeneSetWriter::write(QTextStream& out, bool use_gene_ids, bool gmx_format_)
{
	gmx_format = gmx_format_;

	return write(out, use_gene_ids);
}

bool GeneSetWriter::write(QTextStream& out)
{
	return write(out, true);
}

bool GeneSetWriter::write(QTextStream& out, bool use_gene_ids)
{
	out.setCodec("UTF-8");

	if (debug) std::cout << "write header " << std::endl;
	// first write the RDF tag

	if (title != "")
	{
		out << QString::fromStdString(title).simplified();
		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}
	else
	{
		out << QString::fromStdString(filename).simplified();
		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}

	if (description != "")
	{
		out << QString::fromStdString(description).simplified();
		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}
	else
	{
		out << "na";
		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}

	if (debug) std::cout << "fetch instances from persistence manager -> ";
	// fetch all known instances from the persistence manager
	std::map<std::string, std::string> data_type = manager.getIdToType();
	if (debug) std::cout << data_type.size() << std::endl;

	std::map<std::string, std::string>::iterator it;
	std::string current_id;
	std::string current_type;
	std::vector<std::pair<std::string,std::string> > attributes;
	std::vector<std::pair<std::string,std::string> >::iterator at_it;

	std::set<std::string> gene_list;
	// go through all instances known by the persistence manager
	for (it = data_type.begin(); it != data_type.end(); it++)
	{
		current_id = it->first;
		current_type = it->second;

		if (use_gene_ids)
		{
			if (debug) std::cout << "print gene_ids" << std::endl;
			// only search for GeneIds
			if (current_type != "RelationshipXref")
				continue;

			// this line should be the only .... for different export types ...
			//			writeObject(current_id, current_type, out);

			attributes.clear();

			if (debug) std::cout << "write Instance of '" << current_type << "' , id '" << current_id << "' -> ";

			std::string db = "";
			// fetch all attributes of the instance
			manager.getAttribute(current_id, attributes);
			for (at_it = attributes.begin(); at_it != attributes.end(); at_it++)
			{
				if (at_it->first == "db")
				{
					db = at_it->second;
					if (debug) std::cout << "db = " << db << std::endl;
				}

				if (((db == "EntrezGene") || (db == "NCBI-GeneID")) && (at_it->first == "id"))
				{
					gene_list.insert(at_it->second);
					//						out << QString::fromStdString(at_it->second) << endl;
					if (debug) std::cout << "id = " << at_it->second << std::endl;
				}
			}
		}
		else
		{
			if (debug) std::cout << "print gene_names" << std::endl;

			// only search for Protein and ProteinReference names
			if ((current_type != "Protein") && (current_type != "ProteinReference"))
				continue;

			attributes.clear();

			if (debug) std::cout << "write Instance of '" << current_type << "' , id '" << current_id << "' -> ";

			// fetch all attributes of the instance
			manager.getAttribute(current_id, attributes);
			for (at_it = attributes.begin(); at_it != attributes.end(); at_it++)
			{
				if (at_it->first == "name")
				{
					gene_list.insert(at_it->second);
					//						out << QString::fromStdString(at_it->second) << endl;
					if (debug) std::cout << "name = " << at_it->second << std::endl;
					break;
				}
			}
		}
	}

	std::set<std::string>::iterator gene_list_it;
	for(gene_list_it = gene_list.begin(); gene_list_it != gene_list.end(); gene_list_it++)
	{
		if (*gene_list_it == "")
			continue;
		out << QString::fromStdString(*gene_list_it);

		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}

	if (!gmx_format)
	{
		out << endl;
	}

	return true;
}

void GeneSetWriter::setPersistenceManager(PersistenceManager& _manager)
{
	manager = _manager;
}

std::set<std::string> GeneSetWriter::getAvailableIdTypes()
{
	std::set<std::string> idTypes;
	typedef std::map<std::string, std::string> IdTypeMap;
	IdTypeMap id_type = manager.getIdToType();
	for (IdTypeMap::const_iterator it = id_type.begin(); it != id_type.end(); ++it)
	{
		if (it->second.compare("UnificationXref"))
		{
			UnificationXrefPtr instance = boost::dynamic_pointer_cast<UnificationXref>(manager.getInstance(it->first, it->second));
			idTypes.insert(instance->getDb());
		}
	}
	return idTypes;
}

bool GeneSetWriter::write(QTextStream& out, std::string id_type, bool gmx_format_)
{
	gmx_format = gmx_format_;

	return write(out, id_type);
}

bool GeneSetWriter::write(QTextStream& out, std::string id_type)
{
	std::set<std::string> types = getAvailableIdTypes();
	if (types.find(id_type) == types.end())
	{
		if (debug) std::cout << "No ids of type '" << id_type << "' in PersistenceManager." << std::endl;
		return false;
	}

	out.setCodec("UTF-8");

	if (debug) std::cout << "write header " << std::endl;
	// first write the RDF tag

	if (title != "")
	{
		out << QString::fromStdString(title).simplified();
		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}
	else
	{
		out << QString::fromStdString(filename).simplified();
		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}

	if (description != "")
	{
		out << QString::fromStdString(description).simplified();
		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}
	else
	{
		out << "na";
		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}

	if (debug) std::cout << "fetch instances from persistence manager -> ";
	// fetch all known instances from the persistence manager
	std::map<std::string, std::string> data_type = manager.getIdToType();
	if (debug) std::cout << data_type.size() << std::endl;

	std::map<std::string, std::string>::iterator it;
	std::string current_id;
	std::string current_type;
	std::vector<std::pair<std::string,std::string> > attributes;
	std::vector<std::pair<std::string,std::string> >::iterator at_it;

	std::set<std::string> gene_list;
	// go through all instances known by the persistence manager
	for (it = data_type.begin(); it != data_type.end(); it++)
	{
		current_id = it->first;
		current_type = it->second;

		if (debug) std::cout << "print gene_ids" << std::endl;
		// only UnificationXref contains usable ID
		if (current_type != "UnificationXref")
		{
				continue;
		}

		// this line should be the only .... for different export types ...
		//			writeObject(current_id, current_type, out);

		attributes.clear();

		if (debug) std::cout << "write Instance of '" << current_type << "' , id '" << current_id << "' -> ";

		std::string db = "";
		// fetch all attributes of the instance
		manager.getAttribute(current_id, attributes);
		for (at_it = attributes.begin(); at_it != attributes.end(); at_it++)
		{
			if (at_it->first == "db")
			{
				db = at_it->second;
				if (debug) std::cout << "db = " << db << std::endl;
			}

			if (db == id_type)
			{
				gene_list.insert(at_it->second);
				//						out << QString::fromStdString(at_it->second) << endl;
				if (debug) std::cout << "id = " << at_it->second << std::endl;
			}
		}
	}
	std::set<std::string>::iterator gene_list_it;
	for(gene_list_it = gene_list.begin(); gene_list_it != gene_list.end(); gene_list_it++)
	{
		if (*gene_list_it == "")
			continue;
		out << QString::fromStdString(*gene_list_it);

		if (gmx_format)
			out << endl;
		else
			out << QString('\t');
	}

	if (!gmx_format)
	{
		out << endl;
	}

	return true;
}

} // namespace

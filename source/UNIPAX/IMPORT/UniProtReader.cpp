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

#include<UNIPAX/IMPORT/UniProtReader.h>
#include<iostream>
#include<sstream>
#include<QtCore/QFile>
#include<QtCore/QStringList>
#include<QtCore/QTextStream>

namespace UniPAX
{

UniProtReader::UniProtReader() : filename("")
{
}

UniProtReader::UniProtReader(const std::string& file)
{
	filename=file;
}

bool UniProtReader::setFilename(const std::string& file)
{
	if (file != "")
	{
		filename=file;
		return true;
	}
	else
	{
		return false;
	}
}

UniProtReader::UniProtReader(const UniProtReader& to_copy): filename(to_copy.filename)
{
}

UniProtReader::~UniProtReader()
{
}

UniProtReader& UniProtReader::operator=(const UniProtReader& assign)
{
	filename=assign.filename;

	return (*this);
}

bool UniProtReader::parse(const std::string& filename)
{
	setFilename(filename);

	return parse();
}

bool UniProtReader::parse()
{
	//Parser is initialized with the file?
	if (filename != "")
	{

		QFile file( QString(filename.c_str()) );
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return false;

		std::vector<std::string> tmp_vec;
		std::map<std::string, std::vector<std::string> > tmp_map;


		QTextStream in(&file);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			QString delimiterPattern("\t");
			QStringList ids = line.split(delimiterPattern);

			if (data.find(ids[0].toStdString()) == data.end())
			{
				tmp_map.clear();
				data[ids[0].toStdString()] = tmp_map;
			}

			if (data[ids[0].toStdString()].find(ids[1].toStdString()) == data[ids[0].toStdString()].end())
			{
				tmp_vec.clear();
				data[ids[0].toStdString()][ids[1].toStdString()] = tmp_vec;
			}

			data[ids[0].toStdString()][ids[1].toStdString()].push_back(ids[2].toStdString());
		}

		return true;
	}
	else
		return false;
}




bool UniProtReader::parseSecondaryAccs(const std::string& sec_filename)
{
	//Parser is initialized with the file?
	if (sec_filename != "")
	{

		QFile file( QString(sec_filename.c_str()) );
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return false;

		std::vector<std::string> tmp_vec;
		std::map<std::string, std::vector<std::string> > tmp_map;

		bool header = true;
		QTextStream in(&file);
		while (!in.atEnd())
		{
			QString line = in.readLine();

			// do not parse the header lines
			if (line.startsWith("____________"))
				header = false;
			if (header)
				continue;

			QString delimiterPattern(" ");
			QStringList ids = line.split(delimiterPattern, QString::SkipEmptyParts);

			secondary_accession_map[ids[0].toStdString()] = ids[1].toStdString();
		}

		return true;
	}
	else
		return false;
}


std::vector<std::string> UniProtReader::getMappedId(std::string swissprot_id, std::string database)
{
	if (data.find(swissprot_id) != data.end())
	{
		if (data[swissprot_id].find(database) != data[swissprot_id].end())
		{
			return data[swissprot_id][database];
		}
	}

	// check if the id was a secondary accession number
	if (secondary_accession_map.find(swissprot_id) != secondary_accession_map.end())
	{
		std::string primary_id = secondary_accession_map[swissprot_id];

		if (data.find(primary_id) != data.end())
		{
			if (data[primary_id].find(database) != data[primary_id].end())
			{
				return data[primary_id][database];
			}
		}
	}



	std::vector<std::string> empty;

	return empty;
}

std::map<std::string, std::vector<std::string> > UniProtReader::getMappedId(std::string swissprot_id)
{
	if (data.find(swissprot_id) != data.end())
	{
		return data[swissprot_id];
	}


	// check if the id was a secondary accession number
	if (secondary_accession_map.find(swissprot_id) != secondary_accession_map.end())
	{
		std::string primary_id = secondary_accession_map[swissprot_id];

		if (data.find(primary_id) != data.end())
		{
			return data[primary_id];
		}
	}

	std::map<std::string, std::vector<std::string> > empty;

	return empty;
}


std::map<std::string, std::map<std::string, std::vector<std::string> > > UniProtReader::getIdMapping()
{
	return data;
}

}

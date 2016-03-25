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

#include <UNIPAX/IMPORT/MZTAB/MzTabReader.h>
#include <iostream>
#include <sstream>
#include <set>
#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>

namespace UniPAX
{

/*! \brief a standard constructor */
MzTabReader::MzTabReader() : mzTab_filename(""), id_cnt(0)
{
	if (!std::numeric_limits<double>::is_iec559)
		std::cerr << "Your compilers 'double' type does not adhere to IEC-559 / IEEE-754 standard." << std::endl;
}

/*! \brief a standard constructor with filename parameter*/
MzTabReader::MzTabReader(const std::string& filename) :mzTab_filename(filename), id_cnt(0)
{
	if (!std::numeric_limits<double>::is_iec559)
		std::cerr << "Your compilers 'double' type does not adhere to IEC-559 / IEEE-754 standard." << std::endl;
}

/*! \brief set file for reading*/
bool MzTabReader::setFilename(const std::string& filename)
{
	if (filename != "")
	{
		mzTab_filename=filename;
		return true;
	}
	else
	{
		return false;
	}
}

/*! \brief a copy constructor */
MzTabReader::MzTabReader(const MzTabReader& to_copy): mzTab_filename(to_copy.mzTab_filename), manager(to_copy.manager), data_series(to_copy.data_series), id_cnt(to_copy.id_cnt)
{
}

/*! \brief destructor */
MzTabReader::~MzTabReader()
{
}

/*! \brief an assignment operator */
MzTabReader& MzTabReader::operator=(const MzTabReader& assign)
{
	mzTab_filename=assign.mzTab_filename;
	manager=assign.manager;
	return (*this);
}

/*! \brief read file with filename */
bool MzTabReader::parse(const std::string& filename)
{
	setFilename(filename);

	return parse();
}

/*! \brief read file */
bool MzTabReader::parse()
{
	bool created = false;
	std::string id = boost::lexical_cast<std::string>(id_cnt++);
	data_series = manager.createInstance<UniPAX::Series>(id, created);
	if (!created)
	{
		std::cerr << "MzTabReader::parse() : Could not create Series object." << std::endl;
		return false;
	}
	//Parser is initialized with the file?
	if (!mzTab_filename.empty())
	{
		enum { NA, MTD, PRH, PRT, PEH, PEP, SMH, SML, COM };
		std::vector<int> section_stack;
		section_stack.push_back(NA);
		std::set<int> section_set;

		QFile file( QString(mzTab_filename.c_str()) );
		unsigned int line_nr = 0;
		unsigned int sub_line = 0;

		unsigned int prt_lines = 0;
		unsigned int prt_columns = 0;

		unsigned int pep_lines = 0;
		unsigned int pep_columns = 0;

		unsigned int sml_lines = 0;
		unsigned int sml_columns = 0;

		// first run to determine number of data lines
		UniPAX::SeriesPtr dummy_series(new UniPAX::Series);
		UniPAX::SamplePtr dummy_sample;
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			return false;
		}
		else
		{
			QTextStream in(&file);
			while (!in.atEnd())
			{
				std::string line = in.readLine().toStdString();
				++line_nr;
				int section = NA;
				if (line.empty())
				{
					continue;
				}
				else if (MzTabReader::parseMTD(line.begin(), line.end(), true))
				{
					section = MTD;
				}
				else if (MzTabReader::parsePRH(line.begin(), line.end(), true, prt_columns))
				{
					section = PRH;
					sub_line = 0;
				}
				else if (MzTabReader::parsePRT(line.begin(), line.end(), true))
				{
					section = PRT;
					prt_lines++;
					sub_line++;
				}
				else if (MzTabReader::parsePEH(line.begin(), line.end(), true, pep_columns))
				{
					section = PEH;
					sub_line = 0;
				}
				else if (MzTabReader::parsePEP(line.begin(), line.end(), true))
				{
					section = PEP;
					pep_lines++;
					sub_line++;
				}
				else if (MzTabReader::parseSMH(line.begin(), line.end(), true, sml_columns))
				{
					section = SMH;
					sub_line = 0;
				}
				else if (MzTabReader::parseSML(line.begin(), line.end(), true))
				{
					section = SML;
					sml_lines++;
					sub_line++;
				}
				else if (MzTabReader::parseCOM(line.begin(), line.end()))
				{
					section = COM;
				}
				else
				{
					if (debug)
					{
						std::cout << "Section order in infile:" << std::endl;
						for (std::vector<int>::iterator it = section_stack.begin(); it != section_stack.end(); ++it)
							std::cout << *it << std::endl;
					}
					std::cerr << "Unknown format in line " << line_nr << ":\n" << line << std::endl;
					return false;
				}
				if (debug)
				{
					std::cout << "Read line of section " << section << std::endl;
				}
				if (section != COM && section_stack.back() != section)
				{
					section_stack.push_back(section);

					if (!section_set.insert(section).second)
					{
						if (debug)
						{
							std::cout << "Section order in infile:" << std::endl;
							for (std::vector<int>::iterator it = section_stack.begin(); it != section_stack.end(); ++it)
								std::cout << *it << std::endl;
						}
						std::cerr << "Reoccuring section " << section << "in line " << line_nr << std::endl;
						return false;
					}
				}
			}
		}
		file.close();
		if (debug)
		{
			std::cout << "First parse finished. Section order in infile:" << std::endl;
			for (std::vector<int>::iterator it = section_stack.begin(); it != section_stack.end(); ++it)
				std::cout << *it << std::endl;
		}
		// second run with known number of data lines
		section_stack.clear();
		section_stack.push_back(NA);
		section_set.clear();

		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			return false;
		}
		else
		{
			QTextStream in(&file);
			while (!in.atEnd())
			{
				std::string line = in.readLine().toStdString();
				++line_nr;
				int section = NA;
				if (line.empty())
				{
					continue;
				}
				else if (MzTabReader::parseMTD(line.begin(), line.end(), false, data_series))
				{
					section = MTD;
				}
				else if (MzTabReader::parsePRH(line.begin(), line.end(), false, prt_columns, prt_lines, data_series))
				{
					section = PRH;
					sub_line = 0;
				}
				else if (MzTabReader::parsePRT(line.begin(), line.end(), false, sub_line, data_series))
				{
					section = PRT;
					sub_line++;
				}
				else if (MzTabReader::parsePEH(line.begin(), line.end(), false, pep_columns, pep_lines, data_series))
				{
					section = PEH;
					sub_line = 0;
				}
				else if (MzTabReader::parsePEP(line.begin(), line.end(), false, sub_line, data_series))
				{
					section = PEP;
					sub_line++;
				}
				else if (MzTabReader::parseSMH(line.begin(), line.end(), false, sml_columns, sml_lines, data_series))
				{
					section = SMH;
					sub_line = 0;
				}
				else if (MzTabReader::parseSML(line.begin(), line.end(), false, sub_line, data_series))
				{
					section = SML;
					sub_line++;
				}
				else if (MzTabReader::parseCOM(line.begin(), line.end()))
				{
					section = COM;
				}
				else
				{
					if (debug)
					{
						std::cout << "Section order in infile:" << std::endl;
						for (std::vector<int>::iterator it = section_stack.begin(); it != section_stack.end(); ++it)
							std::cout << *it << std::endl;
					}
					std::cerr << "Unknown format in line " << line_nr << ":\n" << line << std::endl;
					return false;
				}
				if (debug)
				{
					std::cout << "Read line of section " << section << std::endl;
				}
				if (section != COM && section_stack.back() != section)
				{
					section_stack.push_back(section);

					if (!section_set.insert(section).second)
					{
						if (debug)
						{
							std::cout << "Section order in infile:" << std::endl;
							for (std::vector<int>::iterator it = section_stack.begin(); it != section_stack.end(); ++it)
								std::cout << *it << std::endl;
						}
						std::cerr << "Reoccuring section " << section << "in line " << line_nr << std::endl;
						return false;
					}
				}
			}
		}
		file.close();
		return true;
	}
	else
	{
		std::cerr << "No infile given." << std::endl;
		return false;
	}
}


void MzTabReader::setDebug(bool debug_)
{
	debug = debug_;
}

std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > MzTabReader::getData()
{
	return manager.getData();
}

boost::shared_ptr<UniPAX::Series> MzTabReader::getSeriesData()
{
	return data_series;
}

UniPAX::PersistenceManager& MzTabReader::getPersistenceManager()
{
	return manager;
}

const UniPAX::PersistenceManager& MzTabReader::getPersistenceManager() const
{
	return manager;
}

} // namespace

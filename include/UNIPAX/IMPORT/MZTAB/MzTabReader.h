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


#ifndef UNIPAX_IMPORT_MZTAB_MZTABREADER_H
#define UNIPAX_IMPORT_MZTAB_MZTABREADER_H

#include<string>
#include<vector>
#include<UNIPAX/COMMON/PersistenceManager.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<UNIPAX/KERNEL/EXT/Series.h>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_lexeme.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/lexical_cast.hpp>
#include <limits>

namespace UniPAX
{

/** \brief class for reading the mzTab format.

					\ingroup Importer
 */
class UNIPAX_EXPORT MzTabReader
{
public:

	/**	@name	standard methods
	 */
	//@{
	/// \brief a standard Constructor
	MzTabReader();
	/// \brief a standard Constructor with filename parameter
	MzTabReader(const std::string& filename);
	/// \brief copy constructor
	MzTabReader(const MzTabReader& to_copy);
	/// \brief a standard destructor
	~MzTabReader();
	/// \brief an assignment operator
	MzTabReader& operator=(const MzTabReader& assign);
	//@}

	/**	@name miscellaneous
	 */
	//@{

	/// \brief set file for reading
	bool setFilename(const std::string& filename);

	/// \brief parse file */
	bool parse();

	/// \brief parse file */
	bool parse(const std::string& filename);
	void setDebug(bool debug);
	//void setNAvalue(bool value);

	std::map<std::string, UniPAX::UPBasePtr> getData();
	UniPAX::SeriesPtr getSeriesData();

	PersistenceManager& getPersistenceManager();
	const PersistenceManager& getPersistenceManager() const;

	//@}

private:
	bool debug;
	std::string mzTab_filename;
	UniPAX::PersistenceManager manager;
	UniPAX::SeriesPtr data_series;
	int id_cnt;


	// metadata
	template <typename Iterator>
	bool parseMTD(Iterator first, Iterator last, bool just_check, UniPAX::SeriesPtr series = UniPAX::SeriesPtr())
	{
		boost::spirit::qi::rule<Iterator, std::string()> std_string;
		std_string %= boost::spirit::qi::lexeme[+(boost::spirit::qi::char_ - '\t')];
		std::string tag, value;
		bool r = boost::spirit::qi::parse(first, last,
				//  Begin grammar
				(
						boost::spirit::qi::lit("MTD")
		>> boost::spirit::qi::char_('\t')
		>> std_string[boost::phoenix::ref(tag) =boost::spirit::qi::_1]
		              >> boost::spirit::qi::char_('\t')
		>> std_string[boost::phoenix::ref(value) =boost::spirit::qi::_1]
				)
				//  End grammar
		);

		if (first != last) // fail if we did not get a full match
			return false;
		if (debug)
		{
			std::cerr << tag << " : " << value << std::endl;
		}
		if (just_check)
			return true;
		series->setDescriptionTag(tag, value);
		// unit title tag
		unsigned found = tag.rfind("-title");
		if (found != std::string::npos)
		{
			std::string s = series->getName();
			if (s != "")
				s.append(", ");
			s.append(value);
			series->setName(value);
		}
		// unit description tag
		found = tag.rfind("-description");
		if (found != std::string::npos)
		{
			std::string s = series->getDescription();
			if (s != "")
				s.append(", ");
			s.append(value);
			series->setDescription(value);
		}
		return r;
	}

	// protein table header
	template <typename Iterator>
	bool parsePRH(Iterator first, Iterator last, bool just_check, unsigned int & m_col, unsigned int n_row = 0, UniPAX::SeriesPtr series = UniPAX::SeriesPtr())
	{
		std::vector<std::string> values;
		boost::spirit::qi::rule<Iterator, std::string()> std_string;
		std_string %= boost::spirit::qi::lexeme[+(boost::spirit::qi::char_ - '\t')];
		bool r = boost::spirit::qi::parse(first, last,
				//  Begin grammar
				(
						boost::spirit::qi::lit("PRH")
		>> *('\t' >> std_string[boost::phoenix::push_back(boost::phoenix::ref(values), boost::spirit::qi::_1)])
				)
				//  End grammar
		);

		if (first != last) // fail if we did not get a full match
			return false;
		UniPAX::SamplePtr sample;

		DoubleMatrixSampleDataPtr matrix(new DoubleMatrixSampleData(n_row, m_col));

		if (just_check)
		{
			sample = UniPAX::SamplePtr(new UniPAX::Sample());
			//				return true;
		}
		else
		{
			// create Sample
			bool created = false;
			sample = manager.createInstance<UniPAX::Sample>(boost::lexical_cast<std::string>(id_cnt++), created);
			if (!created)
			{
				std::cerr << "MzTabReader::parsePRH : Could not create Sample object." << std::endl;
				return false;
			}
			if (debug)
			{
				std::cerr << "MzTabReader::parsePRH : created Sample object." << std::endl;
			}

			sample->setSampleData(matrix);
//			setDataMatrix(UniPAX::DataMatrixPtr(new UniPAX::DataMatrix(n_row, m_col, double(0))));
			series->addSample(sample);
			// create IdMapping
			UniPAX::IdMappingPtr mapping =  manager.createInstance<UniPAX::IdMapping>(boost::lexical_cast<std::string>(id_cnt++), created);
			if (!created)
			{
				std::cerr << "MzTabReader::parsePRH : Could not create IdMapping object." << std::endl;
				return false;
			}
			if (debug)
			{
				std::cerr << "MzTabReader::parsePRH : created IdMapping object." << std::endl;
			}
			mapping->setSampleIndex(series->getSampleList().size()-1);

			series->addIdMapping(mapping);
		}
		unsigned int num_sub = 0;
		int num_cols = 0;
		unsigned int num_double = 0;
		for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); it++)
		{
			sample->setDescriptionTag(boost::lexical_cast<std::string>(num_cols), *it);
			if (it->find("protein_abundance") != std::string::npos)
			{
				if (it->find("protein_abundance_sub") != std::string::npos)
				{
					num_sub++;
				}
				// add column name to matrix!!!
				if (!just_check)
				{
					matrix->column_names[num_double] = *it;
				}
				num_double++;
			}
			num_cols++;
		}
		if (debug)
		{
			std::cerr << "MzTabReader::parsePRH : found " << num_sub << " sub-samples." << std::endl;
		}
		if (just_check)
			m_col = num_double;
		return r;
	}

	// row of the protein table
	template <typename Iterator>
	bool parsePRT(Iterator first, Iterator last, bool just_check, unsigned int row = 0, UniPAX::SeriesPtr series = UniPAX::SeriesPtr())
	{
		std::vector<std::string> values;
		boost::spirit::qi::rule<Iterator, std::string()> std_string;
		std_string %= boost::spirit::qi::lexeme[+(boost::spirit::qi::char_ - '\t')];
		bool r = boost::spirit::qi::parse(first, last,
				//  Begin grammar
				(
						boost::spirit::qi::lit("PRT")
		>> *('\t' >> std_string[boost::phoenix::push_back(boost::phoenix::ref(values), boost::spirit::qi::_1)])
				)
				//  End grammar
		);

		if (first != last) // fail if we did not get a full match
			return false;
		if (just_check)
			return true;
		UniPAX::SamplePtr sample = series->getSampleList().back();
		UniPAX::IdMappingPtr mapping = series->getIdMappingList().back();
		int col = 0;
		std::string accession;
		for (int i=0; i < values.size(); i++)
		{
			std::map<std::string, std::string> tmp_map = sample->getDescriptionTags();
			std::string column_label = tmp_map.find(boost::lexical_cast<std::string>(i))->second;
			if (column_label.find("accession") != std::string::npos)
			{
				accession = values[i];
			}
			// check if ID system changed -> new IdMapping
			else if (column_label.find("database_version") != std::string::npos)
			{
				std::pair<std::string, std::string> id_system(values[i-1], values[i]);
				if (debug)
				{
					std::cerr << "Database: " << id_system.first << "v" << id_system.second << std::endl;
				}

				if (mapping->getDbName().empty())
				{
					mapping->setDbName(id_system.first);
					mapping->setDbVersion(id_system.second);
				}
				else if (mapping->getDbName().compare(id_system.first) != 0 || mapping->getDbVersion().compare(id_system.second) != 0)
				{
					// we need a new IdMapping:
					bool created = false;
					mapping =  manager.createInstance<UniPAX::IdMapping>(boost::lexical_cast<std::string>(id_cnt++), created);
					if (!created)
					{
						std::cerr << "MzTabReader::parsePRT : Could not create IdMapping object." << std::endl;
						return false;
					}
					if (debug)
					{
						std::cerr << "MzTabReader::parsePRT : created IdMapping object." << std::endl;
					}
					mapping->setDbName(id_system.first);
					mapping->setDbVersion(id_system.second);
					mapping->setSampleIndex(series->getSampleList().size()-1);

					series->addIdMapping(mapping);

				}
			}

			// set double values
			else if (tmp_map.find(boost::lexical_cast<std::string>(i))->second.find("protein_abundance") != std::string::npos)
			{
				if (debug)
				{
					std::cerr << "Tag: " << i << " : " << tmp_map.at(boost::lexical_cast<std::string>(i)) << std::endl;
					std::cerr << "row: " << row << " col: " << col << " := value " << i << " : " << values[i] << std::endl;
				}
				if (values[i].compare("null") == 0)
				{
					boost::dynamic_pointer_cast<DoubleMatrixSampleData>(sample->getSampleData())->values[row][col++] = std::numeric_limits<double>::quiet_NaN();
				}
				else
				{
					boost::dynamic_pointer_cast<DoubleMatrixSampleData>(sample->getSampleData())->values[row][col++] = boost::lexical_cast<double>(values[i]);
				}
			}
		}
		// insert Id into Mapping
		mapping->getIds().insert(std::pair<int, std::string>(row, accession));
		return r;
	}

	// peptide table header
	template <typename Iterator>
	bool parsePEH(Iterator first, Iterator last, bool just_check, unsigned int & m_col, unsigned int n_row = 0, UniPAX::SeriesPtr series = UniPAX::SeriesPtr())
	{
		std::vector<std::string> values;
		boost::spirit::qi::rule<Iterator, std::string()> std_string;
		std_string %= boost::spirit::qi::lexeme[+(boost::spirit::qi::char_ - '\t')];
		bool r = boost::spirit::qi::parse(first, last,
				//  Begin grammar
				(
						boost::spirit::qi::lit("PEH")
		>> *('\t' >> std_string[boost::phoenix::push_back(boost::phoenix::ref(values), boost::spirit::qi::_1)])
				)
				//  End grammar
		);

		if (first != last) // fail if we did not get a full match
			return false;

		DoubleMatrixSampleDataPtr matrix(new DoubleMatrixSampleData(n_row, m_col));

		UniPAX::SamplePtr sample;
		if (just_check)
		{
			sample = UniPAX::SamplePtr(new UniPAX::Sample());
		}
		else
		{
			bool created = false;
			sample = manager.createInstance<UniPAX::Sample>(boost::lexical_cast<std::string>(id_cnt++), created);
			if (!created)
			{
				std::cerr << "MzTabReader::parsePEH : Could not create Sample object." << std::endl;
				return false;
			}
			if (debug)
			{
				std::cerr << "MzTabReader::parsePEH : created Sample object." << std::endl;
			}
			std::cerr << "create (" << n_row << "x" << m_col << " Matrix" << ")" << std::endl;
			sample->setSampleData(matrix);
			series->addSample(sample);
			// create IdMapping
			UniPAX::IdMappingPtr mapping =  manager.createInstance<UniPAX::IdMapping>(boost::lexical_cast<std::string>(id_cnt++), created);
			if (!created)
			{
				std::cerr << "MzTabReader::parsePEH : Could not create IdMapping object." << std::endl;
				return false;
			}
			if (debug)
			{
				std::cerr << "MzTabReader::parsePEH : created IdMapping object." << std::endl;
			}
			mapping->setSampleIndex(series->getSampleList().size()-1);
			series->addIdMapping(mapping);
		}
		unsigned int num_sub = 0;
		int num_cols = 0;
		unsigned int num_double = 0;
		for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); it++)
		{
			sample->setDescriptionTag(boost::lexical_cast<std::string>(num_cols), *it);
			if (it->find("peptide_abundance") != std::string::npos)
			{
				if (it->find("peptide_abundance_sub") != std::string::npos)
				{
					num_sub++;
				}
				// add column name to matrix!!!
				if (!just_check)
				{
					matrix->column_names[num_double] = *it;
				}
				num_double++;
			}
			num_cols++;
		}
		if (debug)
		{
			std::cerr << "MzTabReader::parsePEH : found " << num_sub << " sub-samples." << std::endl;
		}
		if (just_check)
			m_col = num_double;
		return r;
	}

	// row of the peptide table
	template <typename Iterator>
	bool parsePEP(Iterator first, Iterator last, bool just_check, unsigned int row = 0, UniPAX::SeriesPtr series = UniPAX::SeriesPtr())
	{
		std::vector<std::string> values;
		boost::spirit::qi::rule<Iterator, std::string()> std_string;
		std_string %= boost::spirit::qi::lexeme[+(boost::spirit::qi::char_ - '\t')];
		bool r = boost::spirit::qi::parse(first, last,
				//  Begin grammar
				(
						boost::spirit::qi::lit("PEP")
		>> *('\t' >> std_string[boost::phoenix::push_back(boost::phoenix::ref(values), boost::spirit::qi::_1)])
				)
				//  End grammar
		);

		if (first != last) // fail if we did not get a full match
			return false;
		if (just_check)
			return true;
		UniPAX::SamplePtr sample = series->getSampleList().back();
		UniPAX::IdMappingPtr mapping = series->getIdMappingList().back();
		int col = 0;
		std::string accession;
		for (int i=0; i < values.size(); i++)
		{
			std::map<std::string, std::string> tmp_map = sample->getDescriptionTags();
			std::string column_label = tmp_map.find(boost::lexical_cast<std::string>(i))->second;
			if (debug)
			{
				std::cerr << "MzTabReader::parsePEP : column_label = '" << column_label << "'" << std::endl;
			}
			if (column_label.find("accession") != std::string::npos)
			{
				accession = values[i];
			}
			// check if ID system changed -> new IdMapping
			else if (column_label.find("database_version") != std::string::npos)
			{
				std::pair<std::string, std::string> id_system(values[i-1], values[i]);
				if (debug)
				{
					std::cerr << "Database: " << id_system.first << "v" << id_system.second << std::endl;
				}
				if (mapping->getDbName().empty())
				{
					mapping->setDbName(id_system.first);
					mapping->setDbVersion(id_system.second);
				}
				else if (mapping->getDbName().compare(id_system.first) != 0 || mapping->getDbVersion().compare(id_system.second) != 0)
				{
					// we need a new IdMapping:
					bool created = false;
					mapping =  manager.createInstance<UniPAX::IdMapping>(boost::lexical_cast<std::string>(id_cnt++), created);
					if (!created)
					{
						std::cerr << "MzTabReader::parsePEP : Could not create IdMapping object." << std::endl;
						return false;
					}
					if (debug)
					{
						std::cerr << "MzTabReader::parsePEP : created IdMapping object." << std::endl;
					}
					mapping->setDbName(id_system.first);
					mapping->setDbVersion(id_system.second);
					mapping->setSampleIndex(series->getSampleList().size()-1);

					series->addIdMapping(mapping);
				}
			}
			// set double values
			else if (tmp_map.find(boost::lexical_cast<std::string>(i))->second.find("peptide_abundance") != std::string::npos)
			{
				if (debug)
				{
					std::cerr << "Tag: " << i << " : " << tmp_map.at(boost::lexical_cast<std::string>(i)) << std::endl;
					std::cerr << "row: " << row << " col: " << col << " := value " << i << " : " << values[i] << std::endl;
				}
				if (values[i].compare("null") == 0)
				{
					boost::dynamic_pointer_cast<DoubleMatrixSampleData>(sample->getSampleData())->values[row][col++] = std::numeric_limits<double>::quiet_NaN();
				}
				else
				{
					boost::dynamic_pointer_cast<DoubleMatrixSampleData>(sample->getSampleData())->values[row][col++] = boost::lexical_cast<double>(values[i]);
				}
			}
		}
		// insert Id into Mapping
		mapping->getIds().insert(std::pair<int, std::string>(row, accession));
		return r;
	}

	// small molecule table header
	template <typename Iterator>
	bool parseSMH(Iterator first, Iterator last, bool just_check, unsigned int & m_col, unsigned int n_row = 0, UniPAX::SeriesPtr series = UniPAX::SeriesPtr())
	{
		std::vector<std::string> values;
		boost::spirit::qi::rule<Iterator, std::string()> std_string;
		std_string %= boost::spirit::qi::lexeme[+(boost::spirit::qi::char_ - '\t')];
		bool r = boost::spirit::qi::parse(first, last,
				//  Begin grammar
				(
						boost::spirit::qi::lit("SMH")
		>> *('\t' >> std_string[boost::phoenix::push_back(boost::phoenix::ref(values), boost::spirit::qi::_1)])
				)
				//  End grammar
		);

		if (first != last) // fail if we did not get a full match
			return false;

		DoubleMatrixSampleDataPtr matrix(new DoubleMatrixSampleData(n_row, m_col));

		UniPAX::SamplePtr sample;
		if (just_check)
		{
			sample = UniPAX::SamplePtr(new UniPAX::Sample());
		}
		else
		{
			bool created = false;
			sample = manager.createInstance<UniPAX::Sample>(boost::lexical_cast<std::string>(id_cnt++), created);
			if (!created)
			{
				std::cerr << "MzTabReader::parseSMH : Could not create Sample object." << std::endl;
				return false;
			}
			if (debug)
			{
				std::cerr << "MzTabReader::parseSMH : created Sample object." << std::endl;
			}
			std::cerr << "create (" << n_row << "x" << m_col << " Matrix" << std::endl;
			sample->setSampleData(matrix); //setDataMatrix(UniPAX::DataMatrixPtr(new UniPAX::DataMatrix(n_row, m_col, double(0))));
			series->addSample(sample);
			// create IdMapping
			UniPAX::IdMappingPtr mapping =  manager.createInstance<UniPAX::IdMapping>(boost::lexical_cast<std::string>(id_cnt++), created);
			if (!created)
			{
				std::cerr << "MzTabReader::parseSMH : Could not create IdMapping object." << std::endl;
				return false;
			}
			if (debug)
			{
				std::cerr << "MzTabReader::parseSMH : created IdMapping object." << std::endl;
			}
			mapping->setSampleIndex(series->getSampleList().size()-1);
			series->addIdMapping(mapping);
		}
		unsigned int num_sub = 0;
		int num_cols = 0;
		unsigned int num_double = 0;
		for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); it++)
		{
			sample->setDescriptionTag(boost::lexical_cast<std::string>(num_cols), *it);
			if (it->find("smallmolecule_abundance") != std::string::npos)
			{
				if (it->find("smallmolecule_abundance_sub") != std::string::npos)
				{
					num_sub++;
				}
				// add column name to matrix!!!
				if (!just_check)
				{
					matrix->column_names[num_double] = *it;
				}
				num_double++;
			}
			num_cols++;
		}
		if (debug)
		{
			std::cerr << "MzTabReader::parseSMH : found " << num_sub << " sub-samples." << std::endl;
		}
		if (just_check)
			m_col = num_double;
		return r;
	}

	// row of the small molecule table
	template <typename Iterator>
	bool parseSML(Iterator first, Iterator last, bool just_check, unsigned int row = 0, UniPAX::SeriesPtr series = UniPAX::SeriesPtr())
	{
		std::vector<std::string> values;
		boost::spirit::qi::rule<Iterator, std::string()> std_string;
		std_string %= boost::spirit::qi::lexeme[+(boost::spirit::qi::char_ - '\t')];
		bool r = boost::spirit::qi::parse(first, last,
				//  Begin grammar
				(
						boost::spirit::qi::lit("SML")
		>> *('\t' >> std_string[boost::phoenix::push_back(boost::phoenix::ref(values), boost::spirit::qi::_1)])
				)
				//  End grammar
		);

		if (first != last) // fail if we did not get a full match
			return false;
		if (just_check)
			return true;
		UniPAX::SamplePtr sample =  series->getSampleList().back();
		UniPAX::IdMappingPtr mapping = series->getIdMappingList().back();
		int col = 0;
		std::string accession;
		for (int i=0; i < values.size(); i++)
		{
			std::map<std::string, std::string> tmp_map = sample->getDescriptionTags();
			std::string column_label = tmp_map.find(boost::lexical_cast<std::string>(i))->second;
			if (column_label.find("identifier") != std::string::npos)
			{
				accession = values[i];
			}
			// check if ID system changed -> new IdMapping
			else if (column_label.find("database_version") != std::string::npos)
			{
				std::pair<std::string, std::string> id_system(values[i-1], values[i]);
				if (debug)
				{
					std::cerr << "Database: " << id_system.first << "v" << id_system.second << std::endl;
				}

				if (mapping->getDbName().empty())
				{
					mapping->setDbName(id_system.first);
					mapping->setDbVersion(id_system.second);
				}
				else if (mapping->getDbName().compare(id_system.first) != 0 || mapping->getDbVersion().compare(id_system.second) != 0)
				{
					// we need a new IdMapping:
					bool created = false;
					mapping =  manager.createInstance<UniPAX::IdMapping>(boost::lexical_cast<std::string>(id_cnt++), created);
					if (!created)
					{
						std::cerr << "MzTabReader::parseSML : Could not create IdMapping object." << std::endl;
						return false;
					}
					if (debug)
					{
						std::cerr << "MzTabReader::parseSML : created IdMapping object." << std::endl;
					}
					mapping->setDbName(id_system.first);
					mapping->setDbVersion(id_system.second);
					mapping->setSampleIndex(series->getSampleList().size()-1);

					series->addIdMapping(mapping);
				}
			}
			// set double values
			else if(tmp_map.find(boost::lexical_cast<std::string>(i))->second.find("smallmolecule_abundance") != std::string::npos)
			{
				if (debug)
				{
					std::cerr << "Tag: " << i << " : " << tmp_map.at(boost::lexical_cast<std::string>(i)) << std::endl;
					std::cerr << "row: " << row << " col: " << col << " := value " << i << " : " << values[i] << std::endl;
				}
				if (values[i].compare("null") == 0)
				{
					boost::dynamic_pointer_cast<DoubleMatrixSampleData>(sample->getSampleData())->values[row][col++] = std::numeric_limits<double>::quiet_NaN();
				}
				else
				{
					boost::dynamic_pointer_cast<DoubleMatrixSampleData>(sample->getSampleData())->values[row][col++] = boost::lexical_cast<double>(values[i]);
				}
			}
		}
		// insert Id into Mapping
		mapping->getIds().insert(std::pair<int, std::string>(row, accession));
		return r;
	}

	// comment line
	template <typename Iterator>
	bool parseCOM(Iterator first, Iterator last)
	{
		bool r = boost::spirit::qi::parse(first, last,
				//  Begin grammar
				(
						boost::spirit::qi::lit("COM")
		>> boost::spirit::qi::char_('\t')
		>> +~boost::spirit::qi::char_('\t')
				)
				//  End grammar
		);

		if (first != last) // fail if we did not get a full match
			return false;
		if (debug)
		{
			std::cerr << "MzTabReader::parseCOM : Comment line parsed." << std::endl;
		}
		return r;
	}

};

}
#endif

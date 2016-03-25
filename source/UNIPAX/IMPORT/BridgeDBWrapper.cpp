#include<UNIPAX/IMPORT/BridgeDBWrapper.h>
#include <boost/filesystem.hpp> // for file control
#include <boost/program_options.hpp> // for parse_config_file
#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QtCore/QFile>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>

UniPAX::BridgeDBWrapper::BridgeDBWrapper() :
executablePath("contrib/BridgeDb/dist/org.bridgedb.tools.batchmapper.jar"),
mappingFilePath("contrib/BridgeDb/mapping-files/current.bridge"),
tmpFilePath("contrib/BridgeDb/tmp")
{
}

UniPAX::BridgeDBWrapper::BridgeDBWrapper(std::string configFile)
{
	UniPAX::BridgeDBWrapper::parseConfigFile(configFile);
}

UniPAX::BridgeDBWrapper::BridgeDBWrapper(const UniPAX::BridgeDBWrapper & rhv) :
						executablePath(rhv.executablePath),
						mappingFilePath(rhv.mappingFilePath),
						tmpFilePath(rhv.tmpFilePath),
						idSystems(rhv.idSystems)
{
}

UniPAX::BridgeDBWrapper & UniPAX::BridgeDBWrapper::operator =(const UniPAX::BridgeDBWrapper & rhv)
{
	executablePath = rhv.executablePath;
	mappingFilePath = rhv.mappingFilePath;
	tmpFilePath = rhv.tmpFilePath;
	idSystems = rhv.idSystems;
}

UniPAX::BridgeDBWrapper::~BridgeDBWrapper()
{
}

void UniPAX::BridgeDBWrapper::parseConfigFile(std::string configFile)
{
	// parse settings for mapping files etc. from config file
	boost::program_options::options_description desc;
	desc.add_options()
										("executablePath", boost::program_options::value<std::string>(&executablePath))
										("mappingFilePath", boost::program_options::value<std::string>(&mappingFilePath))
										("tmpFilePath", boost::program_options::value<std::string>(&tmpFilePath))
										;
	boost::program_options::variables_map vm;
	//boost::program_options::store(boost::program_options::parse_config_file(configFile.c_str(), desc), vm); // broken in boost 1.46
	std::filebuf fb;
	if (fb.open (configFile.c_str() , std::ios::in))
	{
		std::istream in(&fb);
		boost::program_options::store(boost::program_options::parse_config_file(in, desc), vm);
		boost::program_options::notify(vm);
		fb.close();
	}
	/*boost::program_options::variables_map::iterator found = vm.find("executablePath");
					if (found != vm.end())
					{
					executablePath = found->second;
					}
					found = vm.find("mappingFilePath");
					if (found != vm.end())
					{
					mappingFilePath = found->second;
					}
					found = vm.find("tmpFilePath");
					if (found != vm.end())
					{
					tmpFilePath = found->second;
					}*/
}

bool UniPAX::BridgeDBWrapper::isMappingSupported(std::string source_id_system, std::string target_id_system)
{
	if (idSystems.empty())
	{
		std::string filename = tmpFilePath + "/ls_out.tmp";
		boost::filesystem::path p (filename);
		if (boost::filesystem::exists(p))
		{
			boost::filesystem::remove(p);
		}
		// System call to generate output
		{
			std::stringstream ss;
			ss << "java -jar ";
			ss << executablePath;
			ss << " -ls > " << filename;
			system(ss.str().c_str());
		}
		QFile file(QString(filename.c_str()));
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			std::cerr << "UniPAX::BridgeDBWrapper::isMappingSupported : Cannot open file '" << filename << "' for reading." << std::endl;
			return false;
		}
		QTextStream in(&file);
		std::stringstream ss;
		while (!in.atEnd())
		{
			QString line = in.readLine();
			// if the first five signs are spaces we have no short code for this ID system ...
			if (line.startsWith("    ")) continue;
			QStringList tokens = line.split(' ', QString::SkipEmptyParts);
			std::string code = tokens[0].toStdString();
			// The last token is always an example ID.
			ss.str("");
			ss << tokens[1].toStdString();
			for (int i=2; i < tokens.size()-1; ++i)
			{
				ss << " ";
				ss << tokens[i].toStdString();
			}
			idSystems.insert(std::pair<std::string, std::string>(ss.str(), code));
		}
	}
	if (idSystems.find(source_id_system) == idSystems.end()) return false;
	if (idSystems.find(target_id_system) == idSystems.end()) return false;
	return true;
}

void UniPAX::BridgeDBWrapper::mapIds(std::string src_system, std::vector<std::string> src_ids, std::string tgt_system, std::multimap<std::string, std::string> & id_mapping)
{
	if (!isMappingSupported(src_system, tgt_system))
	{
		std::cerr << "UniPAX::BridgeDBWrapper::mapIds : Unsupported mapping." << std::endl;
	}
	else
	{
		// write ids to tmp input file
		std::string infile = tmpFilePath + "/ID_list_in.tmp";
		{
			QFile file(QString(infile.c_str())); // QFile needs to be destroyed before we can read from the file.
			if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text))
			{
				std::cerr << "UniPAX::BridgeDBWrapper::mapIds : Cannot open file '" << infile << "' for writing." << std::endl;
				return;
			}
			QTextStream out(&file);
			for (std::vector<std::string>::iterator it = src_ids.begin(); it != src_ids.end(); ++it)
			{
				out << it->c_str() << "\n";
			}
		}
		// call batch_mapper with correct id_systems
		std::string outfile = tmpFilePath + "/ID_list_out.tmp";
		std::stringstream ss;
		ss << "java -jar " << executablePath;
		ss << " -is " << idSystems.find(src_system)->second;
		ss << " -i " << infile;
		ss << " -os " << idSystems.find(tgt_system)->second;
		ss << " -o " << outfile;
		ss << " -g " << mappingFilePath;
		std::cout << "Calling " << ss.str().c_str() << std::endl;
		system(ss.str().c_str()); // be sure that file is not open any more!
		// parse ids from tmp output file
		QFile file2(QString(outfile.c_str()));
		if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			std::cerr << "UniPAX::BridgeDBWrapper::mapIds : Cannot open file '" << outfile << "' for reading." << std::endl;
			return;
		}
		QTextStream in(&file2);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			if (line.startsWith("\t")) continue;
			QStringList tokens = line.split('\t', QString::SkipEmptyParts);
			std::string code = tokens[0].toStdString();
			id_mapping.insert(std::pair<std::string, std::string>(tokens[1].toStdString(), code));
		}
		//in

	}
}

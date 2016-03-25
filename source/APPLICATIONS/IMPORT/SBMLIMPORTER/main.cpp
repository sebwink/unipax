#include <UNIPAX/IMPORT/SBML/SBMLReader.h>
#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>

#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#endif

#include <boost/program_options.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <QtCore/QCoreApplication>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>

int main(int argC, char** argV)
{
	boost::program_options::options_description desc("Allowed options");
	bool debug = false;
	bool file_out = false;
	std::vector<std::string> input_files;
	std::string mapping_config_file, proxy_host, db_host, db_name, db_user, out_file, service_name;
	int proxy_port, db_port;
	desc.add_options()
		("help,h", "produce help message")
		("debug,d", "use debug modus. Prints out debug information during parse.")
		("out-file,o",boost::program_options::value< std::string >(&out_file), "write in BioPAX format to file.")
		("input-file,i", boost::program_options::value< std::vector<std::string> >(&input_files), "SBML input file to parse")
		("mapping-config,m", boost::program_options::value< std::string >(&mapping_config_file)->default_value("config/SBML2BioPAXconfigFile_withConstraints.xml"), "mapping config file to use")
		("proxy-host,y", boost::program_options::value< std::string >(&proxy_host)->default_value(""), "set proxy host for connection to MIRIAM web service")
		("proxy-port,p", boost::program_options::value< int >(&proxy_port)->default_value(0), "set proxy port for connection to MIRIAM web service")
		("db-host,H", boost::program_options::value< std::string >(&db_host)->default_value("localhost"), "host of the database server")
		("db-user,U", boost::program_options::value< std::string >(&db_user)->default_value("unipax"), "user name for the connection to the UniPAX database")
#ifdef ODB_MYSQL
		("db-name,N", boost::program_options::value< std::string >(&db_name)->default_value("unipax"), "name of the UniPAX database")
		("db-port,P", boost::program_options::value< int >(&db_port)->default_value(3306), "port of the database server")
#elif defined ODB_ORACLE
		("db-sid,S", boost::program_options::value< std::string >(&db_name)->default_value("unipax"), "SID of the UniPAX database")
		("db-service-name,s", boost::program_options::value< std::string >(&service_name)->default_value(""), "Service name of the UniPAX database, if different from SID")
		("db-port,P", boost::program_options::value< int >(&db_port)->default_value(1521), "port of the database server")
#endif
	;
	boost::program_options::positional_options_description pod;
	pod.add("input-file", -1);
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argC, argV).options(desc).positional(pod).run(), vm);
	boost::program_options::notify(vm);
	if (argC == 1 || vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 0;
	}
	if (vm.count("debug"))
	{
		debug = true;
		std::cout << "Debug output activated." << std::endl;
	}
	if (vm.count("out-file"))
	{
		file_out = true;
		std::cout << "Writing imported SBML model in BioPAX format to " << out_file << "." << std::endl;
	}
	for (std::vector<std::string>::const_iterator it = input_files.begin(); it != input_files.end(); it++)
	{
		std::cout << "SBML files to parse: " << *it << "\n";
	}

#ifdef ODB_MYSQL
		UniPAX::mysql::MySQLManager db;
#elif defined ODB_ORACLE
		UniPAX::oracle::OracleManager db;
		// in the case of different service name and SID
		if (!service_name.empty())
		{
			db.setServiceName(service_name);
		}
#endif
	if (!file_out)
	{
		std::cout << "First try to connect to UniPAX database: " << db_user << "@" << db_name << " on " << db_host << ":" << db_port << std::endl;
		std::cout << "Enter password for database: ";
		std::string db_passw;
		std::cin >> db_passw;
		db.setDBCredentials(db_user, db_passw, db_host, db_port, db_name);
		if (!db.initDatabase())
		{
			std::cout << "Could not initialise database. Aborting parse." << std::endl;
			return 1;
		}
		else
		{
			std::cout << "Database successfully initialized." << std::endl;
		}
	}
	std::cout << "Mapping config file used for initialization of SBML reader: " << mapping_config_file << std::endl;
	QCoreApplication core_app(argC, argV);
	UniPAX::SBMLReader reader;
	reader.setDebug(debug);
	reader.init(proxy_host, proxy_port, mapping_config_file);
	for (std::vector<std::string>::const_iterator it = input_files.begin(); it != input_files.end(); it++)
	{
		std::cout << "Start reading file " << *it << std::endl;
		reader.setFilename(*it);
		if (!reader.parse())
		{
			return 1;
		}
		std::cout << "Successfully read file " << *it << std::endl;
		if (!file_out)
		{
			// now create ImportSource object from input
			UniPAX::ImportSourcePtr is(new UniPAX::ImportSource);
			is->setName(*it);
			is->setVersion(boost::posix_time::to_iso_extended_string(boost::posix_time::microsec_clock::universal_time()));
			if (!reader.getPersistenceManager().assignImportSource(is))
			{
				std::cerr << "Could not assign ImportSource info to parsed data. Aborting ..." << std::endl;
				return 1;
			}

			if (!db.persist(reader.getPersistenceManager()))
			{
				 return 1;
			}
			std::cout << "Successfully wrote to database." << std::endl;
			reader.getPersistenceManager().clear();
		}
	}
	UniPAX::BIOPAXWriter writer;
	if (file_out)
	{
		writer.setFilename(out_file);
		writer.setPersistenceManager(reader.getPersistenceManager());
		if (writer.write())
		{
			std::cout << "Successfully wrote to outfile " << out_file << "." << std::endl;
		}
		else
		{
			std::cerr << "Could not write to outfile " << out_file << "." << std::endl;
			return 1;
		}
	}
	return 0;
}

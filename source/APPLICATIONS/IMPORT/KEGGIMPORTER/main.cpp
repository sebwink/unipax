#include <APPLICATIONS/IMPORT/KEGGIMPORTER/KEGGMapper.h>
#include <APPLICATIONS/IMPORT/KEGGIMPORTER/DBConnection.h>

#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#endif

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>

#include <boost/program_options.hpp>
#include <QtGui/QApplication>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>

int main(int argC, char** argV)
{
	std::string kegg_arg;
	std::string unipax_arg;
	std::string data_source, data_version;
	bool all_organisms = false;
	std::vector<std::string> organisms;
	organisms.push_back("hsa");

	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
	("help,h", "produce help message")

#ifdef ODB_MYSQL
	("kegg,k", boost::program_options::value< std::string >(&kegg_arg), "KEGG database connection in format: username@hostname[:port]/dbname")
	("unipax,u", boost::program_options::value< std::string >(&unipax_arg), "UniPAX database connection in format: username@hostname[:port]/dbname")
#elif defined ODB_ORACLE
	("kegg,k", boost::program_options::value< std::string >(&kegg_arg), "KEGG database connection in format: username@hostname[:port]/sid")
	("unipax,u", boost::program_options::value< std::string >(&unipax_arg), "UniPAX database connection in format: username@hostname[:port]/sid")
#endif

	("data-source,D", boost::program_options::value< std::string >(&data_source)->default_value("KEGG"), "name of the data source")
	("data-version,V", boost::program_options::value< std::string >(&data_version)->default_value(boost::posix_time::to_iso_extended_string(boost::posix_time::microsec_clock::universal_time())), "version of the data source")

	("all,a", "Import all organisms")
	("organisms,o", boost::program_options::value< std::vector<std::string> >(&organisms), "List of 3-letter organism description: \"hsa mmu eco\"")
	;
	boost::program_options::positional_options_description pod;
	pod.add("organisms", -1);
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argC, argV).options(desc).positional(pod).run(), vm);
	boost::program_options::notify(vm);
	if (vm.count("help") || !vm.count("kegg") || !vm.count("unipax") || !(vm.count("all") || vm.count("organisms")))
	{
		std::cout << desc << std::endl;
		return 0;
	}

	if (vm.count("all"))
		all_organisms = true;

	QApplication q_app();

	std::string kegg_host;
	std::string kegg_user;
	std::string kegg_database;
#ifdef ODB_MYSQL
	int kegg_port = 3306;
#elif defined ODB_ORACLE
	int kegg_port = 1521;
#endif

	std::size_t pos = 0;
	if ( (pos = kegg_arg.find_first_of('@')) != kegg_arg.npos) {
		kegg_user = kegg_arg.substr(0, pos);
		kegg_arg = kegg_arg.substr(pos + 1);
	} else {
		std::cerr << "KEGG username not found" << std::endl;
		return -1;
	}

	if ( (pos = kegg_arg.find_first_of(':')) != kegg_arg.npos) {
		kegg_host = kegg_arg.substr(0, pos);
		kegg_arg = kegg_arg.substr(pos + 1);

		if ( (pos = kegg_arg.find_first_of('/')) != kegg_arg.npos) {
			std::stringstream ss;
			ss << kegg_arg.substr(0, pos);
			ss >> kegg_port;
			kegg_arg = kegg_arg.substr(pos + 1);
		} else {
			std::cerr << "KEGG database not found" << std::endl;
			return -1;
		}

	} else if ( (pos = kegg_arg.find_first_of('/')) != kegg_arg.npos) {
		kegg_host = kegg_arg.substr(0, pos);
		kegg_arg = kegg_arg.substr(pos + 1);
	} else {
		std::cerr << "KEGG host not found" << std::endl;
		return -1;
	}

	kegg_database = kegg_arg;

	std::string unipax_host;
	std::string unipax_user;
	std::string unipax_database;
#ifdef ODB_MYSQL
	int unipax_port = 3306;
#elif defined ODB_ORACLE
	int unipax_port = 1521;
#endif

	if ( (pos = unipax_arg.find_first_of('@')) != unipax_arg.npos)
	{
		unipax_user = unipax_arg.substr(0, pos);
		unipax_arg = unipax_arg.substr(pos + 1);
	} else
	{
		std::cerr << "UniPAX username not found" << std::endl;
		return -1;
	}

	if ( (pos = unipax_arg.find_first_of(':')) != unipax_arg.npos)
	{
		unipax_host = unipax_arg.substr(0, pos);
		unipax_arg = unipax_arg.substr(pos + 1);

		if ( (pos = unipax_arg.find_first_of('/')) != unipax_arg.npos)
		{
			std::stringstream ss;
			ss << unipax_arg.substr(0, pos);
			ss >> unipax_port;
			unipax_arg = unipax_arg.substr(pos + 1);
		} else
		{
			std::cerr << "UniPAX database not found" << std::endl;
			return -1;
		}

	} else if ( (pos = unipax_arg.find_first_of('/')) != unipax_arg.npos)
	{
		unipax_host = unipax_arg.substr(0, pos);
		unipax_arg = unipax_arg.substr(pos + 1);
	} else
	{
		std::cerr << "UniPAX host not found" << std::endl;
		return -1;
	}

	unipax_database = unipax_arg;

	std::cerr << "Please enter password for KEGG database (" << kegg_user << "@" << kegg_host << ":" << kegg_port << "/" << kegg_database << ")" << std::flush;
	std::string kegg_pw(getpass(": "));

	std::cerr << "Please enter password for UniPAX database (" << unipax_user << "@" << unipax_host << ":" << unipax_port << "/" << unipax_database << ")" << std::flush;
	std::string unipax_pw(getpass(": "));

	UniPAX::DBConnection kegg_conn(kegg_host, kegg_database, kegg_user, kegg_pw, kegg_port);

	if (!kegg_conn.open())
	{
		std::cerr << "Unable to connect to KEGG database." << std::endl;
		return -1;
	}

	if (all_organisms)
	{

#ifdef ODB_MYSQL
		QSqlQuery* result = kegg_conn.exec("SELECT * FROM Organisms");
#elif defined ODB_ORACLE
		QSqlQuery* result = kegg_conn.exec("SELECT * FROM \"Organisms\"");
#endif
		organisms.clear();
		while (result->next())
		{
			std::string three_letter_code = result->value(0).toString().toStdString();
			std::string abbreviation = result->value(1).toString().toStdString();
			std::string full_name = result->value(2).toString().toStdString();

			organisms.push_back(three_letter_code);
		}
		result->clear();
	}
	else
	{
		std::vector<std::string> tmp(organisms);

#ifdef ODB_MYSQL
		QSqlQuery* result = kegg_conn.exec("SELECT * FROM Organisms");
#elif defined ODB_ORACLE
		QSqlQuery* result = kegg_conn.exec("SELECT * FROM \"Organisms\"");
#endif
		organisms.clear();
		while (result->next())
		{
			std::string three_letter_code = result->value(0).toString().toStdString();
			std::string abbreviation = result->value(1).toString().toStdString();
			std::string full_name = result->value(2).toString().toStdString();

			if (std::find(tmp.begin(), tmp.end(), three_letter_code) != tmp.end())
			{
				organisms.push_back(three_letter_code);
				tmp.erase(std::find(tmp.begin(), tmp.end(), three_letter_code));
			}
		}

		for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
		{
			std::cout << "Unable to find organism \"" << *it << "\" in database." << std::endl;
		}

		result->clear();
	}

	if (organisms.size() == 0)
	{
		std::cerr << "No organisms defined. Importer will quit now." << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Importing " << organisms.size() << " organism(s)." << std::endl;
	}

	UniPAX::PersistenceManager manager;

	UniPAX::KEGGMapper kegg_mapper(manager);
	kegg_mapper.setKEGGDatabase(&kegg_conn, std::string());
	kegg_mapper.import(organisms);

	// now create ImportSource object from input
	UniPAX::ImportSourcePtr is(new UniPAX::ImportSource);
	is->setName(data_source);
	is->setVersion(data_version);
	if (!manager.assignImportSource(is))
	{
		std::cerr << "Could not assign ImportSource info to parsed data. Aborting ..." << std::endl;
		return 1;
	}

	std::cout << "Writing to database..." << std::endl;
#ifdef ODB_MYSQL
	UniPAX::mysql::MySQLManager db;
#elif defined ODB_ORACLE
	UniPAX::oracle::OracleManager db;
#endif
	db.setDBCredentials(unipax_user, unipax_pw, unipax_host, unipax_port, unipax_database);
	db.persist(manager);
	std::cout << "finished !" << std::endl;

	kegg_conn.close();


//	std::cout << "start writing" << std::endl;
//	UniPAX::BIOPAXWriter writer;
//	writer.setDebug(false);
//	writer.setPersistenceManager(manager);
//	writer.write("/tmp/test_export2.owl");

	return 0;
}

#include <UNIPAX/IMPORT/UniProtReader.h>
#include <boost/program_options.hpp>

#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#endif

#include <UNIPAX/COMMON/KernelCollector.h>


#include <string>
#include <iostream>
#include <map>

int main(int argC, char** argV)
{
	boost::program_options::options_description desc("Allowed options");
	bool debug = false;
	std::string s_input_file, m_input_file;
	std::string db_host, db_name, db_user, db_passw, id, service_name;
	int db_port;
	desc.add_options()
		("help,h", "produce help message")
//		("debug,d", "use debug modus. Prints out debug information during parse.")
		("mapping-file,i", boost::program_options::value< std::string >(&m_input_file), "HUMAN_9606_idmapping.dat input file to parse \n can be downloaded at ftp://ftp.uniprot.org/pub/databases/uniprot/current_release/knowledgebase/idmapping/by_organism/HUMAN_9606_idmapping.dat.gz")
		("secondary-file,a", boost::program_options::value< std::string >(&s_input_file), "secondary accession numbers input file to parse \n can be downloaded at ftp://ftp.uniprot.org/pub/databases/uniprot/knowledgebase/docs/sec_ac.txt")

//		("data-source,D", boost::program_options::value< std::string >(&data_source)->default_value(input_file), "name of the data source")
//		("data-version,V", boost::program_options::value< std::string >(&data_version)->default_value(boost::posix_time::to_iso_extended_string(boost::posix_time::microsec_clock::universal_time())), "version of the data source")

		("db-host,H", boost::program_options::value< std::string >(&db_host)->default_value("localhost"), "host of the database server")
		("db-passw,p", boost::program_options::value< std::string >(&db_passw)->default_value("unipax"), "password of the UniPAX database")
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
	pod.add("mapping-file", -1);
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argC, argV).options(desc).positional(pod).run(), vm);
	boost::program_options::notify(vm);
	if (argC == 1 || vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 0;
	}
//	if (vm.count("debug"))
//	{
//		debug = true;
//		std::cout << "Debug output activated." << std::endl;
//	}
	if (db_passw.empty())
	{
		std::cout << "Enter password for database: ";
		std::cin >> db_passw;
	}

	// get secondary accession numbers from
	// ftp://ftp.uniprot.org/pub/databases/uniprot/knowledgebase/docs/sec_ac.txt
	// get dat file from
	// ftp://ftp.uniprot.org/pub/databases/uniprot/current_release/knowledgebase/idmapping/by_organism/HUMAN_9606_idmapping.dat.gz
	UniPAX::UniProtReader prot_reader;
	std::cout << "parse secondary accession numbers ..." << std::endl;
	prot_reader.parseSecondaryAccs(s_input_file);
	std::cout << "parse mapping file ..." << std::endl;
	prot_reader.parse(m_input_file);

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
	db.setDBCredentials(db_user, db_passw, db_host, db_port, db_name);
	UniPAX::KernelCollector collector;
	std::map<UnipaxId, std::string> protein_ids;
	std::map<UnipaxId, std::string>::iterator it;

	std::cout << "start mapping ..." << std::endl;
	db.getProteinIds(protein_ids);
	db.getProteinReferenceIds(protein_ids);

	std::map<std::string, boost::shared_ptr<UniPAX::RelationshipXref> > rxref_map;
	for (it = protein_ids.begin(); it != protein_ids.end(); it++)
	{
//		std::cout << "Protein: " << it->first << " | Uniprot: " << it->second << std::endl;
		db.addGeneId(it->first, it->second, rxref_map, collector, prot_reader);
	}

	std::cout << "Collected objects: " << collector.getInstanceCount() << std::endl;

	std::cout << "update ..." << std::endl;
	db.update(collector);


	return 0;
}

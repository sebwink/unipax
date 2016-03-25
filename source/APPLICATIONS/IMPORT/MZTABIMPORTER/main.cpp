#include <UNIPAX/IMPORT/MZTAB/MzTabReader.h>

#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#include <UNIPAX/SERVER/BACKEND/MYSQL/MySQLQueryEngine.h>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#include <UNIPAX/SERVER/BACKEND/ORACLE/OracleQueryEngine.h>
#endif

#include <boost/program_options.hpp>
#include <string>
#include <iostream>

int main(int argC, char** argV)
{
				boost::program_options::options_description desc("Allowed options");
				bool debug = false;
				std::string input_file;
				std::string db_host, db_name, db_user, db_passw, id;
				int db_port;
				desc.add_options()
								("help,h", "produce help message")
								("debug,d", "use debug modus. Prints out debug information during parse.")
								("input-file,i", boost::program_options::value< std::string >(&input_file), "input mzTab file")
//								("NA-value,n", boost::program_options::value< double >(&na_value)->default_value(0.0), "float value which should be inserted for missing numeral values (NA)")
								("db-host,H", boost::program_options::value< std::string >(&db_host)->default_value("localhost"), "host of the database server")
								("db-port,P", boost::program_options::value< int >(&db_port)->default_value(3306), "port of the database server")
								("db-passw,p", boost::program_options::value< std::string >(&db_passw)->default_value("unipax"), "password of the UniPAX database")
								("db-name,N", boost::program_options::value< std::string >(&db_name)->default_value("unipax"), "name of the UniPAX database")
								("db-user,U", boost::program_options::value< std::string >(&db_user)->default_value("unipax"), "user name for the connection to the UniPAX database")
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
				if (0) //(db_passw.empty())
				{
								std::cout << "Enter password for database: ";
								std::cin >> db_passw;
				}

				UniPAX::MzTabReader mztab_reader;
				mztab_reader.setDebug(debug);
				std::cout << "parsing mzTab file " << input_file << "..." << std::endl;
				mztab_reader.parse(input_file);

#ifdef ODB_MYSQL
				std::cout << "start mysql persistence" << std::endl;
				//UniPAX::mysql::MySQLManager db;
				UniPAX::SERVER::MySQLQueryEngine* engine = new UniPAX::SERVER::MySQLQueryEngine();
#elif defined ODB_ORACLE
				std::cout << "start oracle persistence" << std::endl;
				//UniPAX::oracle::OracleManager db;
				UniPAX::SERVER::OracleQueryEngine* engine = new UniPAX::SERVER::OracleQueryEngine();
				// in the case of different service name and SID
				if (!service_name.empty())
				{
								boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(engine->getDBManager())->setServiceName(service_name);
				}
#endif
				//db.setDBCredentials(db_user, db_passw, db_host, db_port, db_name);
				engine->getDBManager()->setDBCredentials(db_user, db_passw, db_host, db_port, db_name);
				engine->getDBManager()->persist(mztab_reader.getPersistenceManager());
				// update ID mappings
				engine->rebuildIdMapping();
				std::cout << "finished !" << std::endl;
				return 0;
}

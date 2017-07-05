
#include <QtGui>
#include <QtNetwork>

#include <UNIPAX/SERVER/BROWSER/UnipaxBrowser.h>
#include <UNIPAX/SERVER/BROWSER/UnipaxBrowserHandler.h>

#ifdef ODB_MYSQL
#include <UNIPAX/SERVER/BACKEND/MYSQL/MySQLQueryEngine.h>
#elif defined ODB_ORACLE
#include <UNIPAX/SERVER/BACKEND/ORACLE/OracleQueryEngine.h>
#endif

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>

int main(int argC, char** argV)
{
	QCoreApplication q_app(argC, argV);

	UniPAX::SERVER::UnipaxBrowser browser;

	std::string help, service_name;

	std::string unipax_arg;
	std::string unipax_pw;

	int port = 8888;
	std::string interface = std::string("*");

	boost::program_options::options_description general("General options");
	general.add_options()
			("help", "produce this help messages")
			("port,P", boost::program_options::value< int >(&port)->default_value(8888), "port of the REST browser")
			("interface,I", boost::program_options::value< std::string >(&interface), "ip address of the REST browser")
			("password", boost::program_options::value< std::string >(&unipax_pw), "Password for UniPAX database connection")
#ifdef ODB_MYSQL
			("unipax,u", boost::program_options::value< std::string >(&unipax_arg), "UniPAX database connection in format: username@hostname[:port]/dbname")
#elif defined ODB_ORACLE
			("unipax,u", boost::program_options::value< std::string >(&unipax_arg), "UniPAX database connection in format: username@hostname[:port]/sid")
			("db-service-name,s", boost::program_options::value< std::string >(&service_name)->default_value(""), "Service name of the UniPAX database, if different from SID")
#endif
		;

	boost::program_options::positional_options_description general_pod;
	general_pod.add("unipax", 1);
	general_pod.add("port", 2);

	boost::program_options::options_description all("Allowed options");

	all.add(general);

	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argC, argV).options(all).positional(general_pod).run(), vm);
	boost::program_options::notify(vm);



	if (vm.count("help") || !vm.count("unipax") || !vm.count("port"))
	{
		std::cout << general << std::endl;
		return 0;
	}

	std::string unipax_host;
	std::string unipax_user;
	std::string unipax_database;

#ifdef ODB_MYSQL
	int unipax_port = 3306;
#elif defined ODB_ORACLE
	int unipax_port = 1521;
#endif

	std::size_t pos = 0;
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

	if (!vm.count("password"))
	{
		std::cerr << "Please enter password for UniPAX database (" << unipax_user << "@" << unipax_host << ":" << unipax_port << "/" << unipax_database << ")" << std::flush;
		unipax_pw = getpass(": ");
	}

	bool cache_enabled = true;
	if (vm.count("disable-caching"))
	{
		// Disable cache !!!
		cache_enabled = false;
		std::cerr << "odb session cache disabled." << std::endl;
	}

#ifdef ODB_MYSQL
	UniPAX::SERVER::MySQLQueryEngine* engine = new UniPAX::SERVER::MySQLQueryEngine(cache_enabled);
#elif defined ODB_ORACLE
	UniPAX::SERVER::OracleQueryEngine* engine = new UniPAX::SERVER::OracleQueryEngine();
	// in the case of different service name and SID
	if (!service_name.empty())
	{
		boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(engine->getDBManager())->setServiceName(service_name);
	}
#endif
	engine->getDBManager()->setDBCredentials(unipax_user, unipax_pw, unipax_host, unipax_port, unipax_database);

	if (!engine->getDBManager()->initDatabase())
	{
		std::cerr << "Unable to initialize database." << std::endl;
		return 1;
	}

	if (vm.count("rebuild-query-index"))
		engine->rebuildAllIndexes();
	else
		engine->checkIndexes();

	browser.setEngine(engine);

	QHostAddress hostAddress = interface == std::string("*") ? QHostAddress::Any : QHostAddress(QString::fromStdString(interface));

	if (browser.listen(hostAddress, port))
	{
		std::cout << "Brwoser is listening on " << interface << ":" << port << "." << std::endl;
		return q_app.exec();
	}
	else
	{
		std::cerr << "Unable to start browser." << std::endl;
	}

	return 0;
}

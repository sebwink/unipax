#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#endif

#include <UNIPAX/COMMON/util.h>

#include <boost/program_options.hpp>

#include <QtGui/QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlError>
#include <QtCore/QVariant>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <unistd.h>

int main(int argC, char** argV)
{
	std::string db_arg;
	std::string pw;

	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
	("help,h", "produce help message")
	("force,f", "force dropping, if database already exists.")

#ifdef ODB_MYSQL
	("database,d", boost::program_options::value< std::string >(&db_arg), "New database connection in format: username@hostname[:port]/dbname")
#elif defined ODB_ORACLE
	("database,d", boost::program_options::value< std::string >(&db_arg), "New database connection in format: username@hostname[:port]/sid")
#endif

	("pw,p", boost::program_options::value< std::string >(&pw)->default_value(""), "password of the UniPAX database")
	;
	boost::program_options::positional_options_description pod;
	pod.add("organisms", -1);
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argC, argV).options(desc).positional(pod).run(), vm);
	boost::program_options::notify(vm);
	if (vm.count("help") || !vm.count("database"))
	{
		std::cout << desc << std::endl;
		return 0;
	}

	QApplication q_app();

	std::string db_host;
	std::string db_user;
	std::string db_database;

	int db_port;
#ifdef ODB_MYSQL
	db_port = 3306;
#elif defined ODB_ORACLE
	db_port = 1521;
#endif

	UniPAX::parseDBargument(db_arg, db_host, db_user, db_database, db_port);

	std::cerr << "Please enter password for new UniPAX database (" << db_user << "@" << db_host << ":" << db_port << ")" << std::flush;
	std::string unipax_pw(getpass(": "));

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", (db_user + "@" + db_host).c_str());

	db.setHostName(QString(db_host.c_str()));
//	db.setDatabaseName(QString(db_database.c_str()));
	db.setUserName(QString(db_user.c_str()));
	db.setPassword(QString(unipax_pw.c_str()));
	db.setPort(db_port);

	if (!db.open())
	{
		std::cerr << "failed. - Unable to connect to database " << db.userName().toStdString() << "@" << db.hostName().toStdString() << ":" << db.port() << std::endl;
		std::cerr << "Error from database driver:" << std::endl;
		std::cerr << db.lastError().text().toStdString() << std::endl;
		return 1;
	}

	QSqlQuery query(db);
	query.setForwardOnly(true);
	query.exec(QString("SET NAMES UTF8"));
	if (query.lastError().isValid())
	{
		std::cerr << "Database Error: " << query.lastError().databaseText().toStdString() << std::endl;
		db.close();
		return 1;
	}

#ifdef ODB_MYSQL
	query.exec(QString("USE `").append(QString(db_database.c_str())).append(QString("`")));
	if (!query.lastError().isValid()) {
		if (vm.count("force"))
		{
			std::cout << "Dropping existing database " << db_database << "..."<< std::flush;
			query.exec(QString("DROP DATABASE `").append(QString(db_database.c_str())).append(QString("`")));
			if (query.lastError().isValid())
			{
				std::cout << "failed." << std::endl;
				std::cerr << "Database Error: " << query.lastError().databaseText().toStdString() << std::endl;
				db.close();
				return 1;
			}
			std::cout << "ok." << std::endl;
		} else
		{
			std::cout << "Database " << db_database << " already exists. Use -f to force dropping of existing database." << std::endl;
			db.close();
			return 1;
		}
	}


	std::cout << "Creating database..." << std::flush;
	query.exec(QString("CREATE DATABASE `").append(QString(db_database.c_str())).append(QString("`")));
	if (query.lastError().isValid())
	{
		std::cout << "failed." << std::endl;
		std::cerr << "Database Error: " << query.lastError().databaseText().toStdString() << std::endl;
		db.close();
		return 1;
	}
	std::cout << "done." << std::endl;

	query.exec(QString("USE `").append(QString(db_database.c_str())).append(QString("`")));
	if (query.lastError().isValid())
	{
		std::cerr << "Unable to switch to new database." << std::endl;
		std::cerr << "Database Error: " << query.lastError().databaseText().toStdString() << std::endl;
		db.close();
		return 1;
	}

	std::cout << "Creating database structure..." << std::flush;

	QString script;
	QFileInfo fi(QDir("schemata"), "UniPAX_MySQL.sql");
	QString path = fi.absoluteFilePath();
	QFile file(path);
	if(file.exists()){
	    file.open(QIODevice::Text | QIODevice::ReadOnly);
	    QTextStream stream(&file);
	    script = stream.readAll();

	    QStringList queries = script.split(QChar(';'));
	    foreach(QString s, queries){
	    	if (!s.trimmed().isEmpty()) {
	    		query.exec(s);
	    		if (query.lastError().isValid())
	    		{
	    			std::cout << "failed." << std::endl;
	    			std::cerr << "Unable to execute " << s.toStdString() << std::endl;
	    			std::cerr << "Database Error: " << query.lastError().databaseText().toStdString() << std::endl;
	    			db.close();
	    			return 1;
	    		}
	    	}
	    }
	}

	std::cout << "done." << std::endl;


#elif defined ODB_ORACLE

#endif

	db.close();

	return 0;
}

/*
 * DBConnection.cpp
 *
 *  Created on: Jun 14, 2011
 *      Author: gerasch
 */

#include <APPLICATIONS/IMPORT/KEGGIMPORTER/DBConnection.h>

namespace UniPAX
{


DBConnection::DBConnection(std::string serverName, std::string databaseName, std::string userName, std::string passwd, int port) {
	db = QSqlDatabase::addDatabase("QMYSQL", (userName + "@" + serverName + "/" + databaseName).c_str());

	db.setHostName(QString(serverName.c_str()));
	db.setDatabaseName(QString(databaseName.c_str()));
	db.setUserName(QString(userName.c_str()));
	db.setPassword(QString(passwd.c_str()));
	db.setPort(port);
}

DBConnection::DBConnection(QSqlDatabase* db) {
	this->db = *db;
}

bool DBConnection::open() {
	bool open = db.open();
	if (open)
	{
		exec("SET NAMES UTF8");
	}
	return open;
}

void DBConnection::close() {
	clearQueries();
	db.close();
}

QSqlQuery* DBConnection::exec(std::string sql)
{
	QSqlQuery* query = new QSqlQuery(db);
	query->setForwardOnly(true);
	query->exec(QString(sql.c_str()));
	if (query->lastError().isValid())
	{
		std::cout << "Database: " << query->lastError().databaseText().toStdString() << std::endl;
		std::cout << "Problem with: " << sql << std::endl;
	}
	return query;
}

void DBConnection::clearQueries() {
	for (std::tr1::unordered_map<std::string, QSqlQuery*>::const_iterator iter = preparedQueries.begin(); iter != preparedQueries.end(); iter++)
	{
		QSqlQuery* query = iter->second;
		query->clear();

		delete (query);
	}

	preparedQueries.clear();
}

void DBConnection::deleteQuery(std::string sql)
{
	QSqlQuery* query = NULL;

	if (preparedQueries.find(sql) != preparedQueries.end())
	{
		query = preparedQueries[sql];
		preparedQueries.erase(sql);

		delete (query);
	}
}

QSqlQuery* DBConnection::exec(std::string sql, QVariant arg1, QVariant arg2, QVariant arg3, QVariant arg4, QVariant arg5, QVariant arg6)
{
	QSqlQuery* query = NULL;

	if (preparedQueries.find(sql) != preparedQueries.end())
	{
		query = preparedQueries[sql];
	}
	else
	{
		query = new QSqlQuery(db);
		query->setForwardOnly(true);
		query->prepare(QString(sql.c_str()));
		preparedQueries[sql] = query;
	}

	if (arg1.isValid())
		query->bindValue(0, arg1);
	if (arg2.isValid())
		query->bindValue(1, arg2);
	if (arg3.isValid())
		query->bindValue(2, arg3);
	if (arg4.isValid())
		query->bindValue(3, arg4);
	if (arg5.isValid())
		query->bindValue(4, arg5);
	if (arg6.isValid())
		query->bindValue(5, arg6);

	query->exec();

	if (query->lastError().isValid())
	{
		std::cout << "Database: " << query->lastError().databaseText().toStdString() << std::endl;
		std::cout << "Problem with: " << sql << std::endl;
	}
	return query;
}



QSqlQuery* DBConnection::exec(std::string sql, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5)
	{
		QSqlQuery* query = NULL;

		if (preparedQueries.find(sql) != preparedQueries.end())
		{
			query = preparedQueries[sql];
		}
		else
		{
			query = new QSqlQuery(db);
			query->setForwardOnly(true);
			query->prepare(QString(sql.c_str()));
			preparedQueries[sql] = query;
		}



		if (arg1 != "")
		{
			query->bindValue(0, QVariant(arg1.c_str()));
			if (arg2 != "")
			{
				query->bindValue(1, QVariant(arg2.c_str()));
				if (arg3 != "")
				{
					query->bindValue(2, QVariant(arg3.c_str()));
					if (arg4 != "")
					{
						query->bindValue(3, QVariant(arg4.c_str()));
						if (arg5 != "")
						{
							query->bindValue(4, QVariant(arg5.c_str()));
						}
					}
				}
			}
		}

		query->exec();

		if (query->lastError().isValid())
		{
			std::cout << "Database: " << query->lastError().databaseText().toStdString() << std::endl;
			std::cout << "Problem with: " << sql << std::endl;
		}

		return query;
	}
}

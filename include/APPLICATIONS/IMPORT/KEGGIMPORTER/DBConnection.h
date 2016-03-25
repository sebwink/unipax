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

#ifndef DBCONNECTION_H_
#define DBCONNECTION_H_

#include<UNIPAX/COMMON/common.h>

#include <iostream>
#include <string>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlError>
#include <QtCore/QVariant>

#include <boost/tr1/unordered_map.hpp>

namespace UniPAX
{

class UNIPAX_EXPORT DBConnection
{


private:

	QSqlDatabase db;

	std::tr1::unordered_map<std::string, QSqlQuery*> preparedQueries;

public:

	DBConnection(std::string serverName, std::string databaseName, std::string userName, std::string passwd, int port);

	DBConnection(QSqlDatabase* db);

	bool open();

	void close();

	void clearQueries();

	void deleteQuery(const std::string sql);

	QSqlQuery* exec(const std::string sql);

	QSqlQuery* exec(const std::string sql, QVariant arg1, QVariant arg2, QVariant arg3, QVariant arg4, QVariant arg5, QVariant arg6);

	QSqlQuery* exec(const std::string sql, const std::string arg1, const std::string arg2 = "", const std::string arg3 = "", const std::string arg4 = "", const std::string arg5 = "");


};

}


#endif /* DBCONNECTION_H_ */

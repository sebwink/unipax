/*
 * util.h
 *
 *  Created on: Feb 24, 2012
 *      Author: gerasch
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <vector>
#include <sstream>
#include <boost/shared_ptr.hpp>


namespace UniPAX
{

template <class S, class T> void castAndPushBack(std::vector<boost::shared_ptr<T> > & target, std::vector<boost::shared_ptr<S> > & values)
{
	for (typename std::vector<boost::shared_ptr<S> >::const_iterator it = values.begin(); it != values.end(); ++it)
	{
		if (boost::dynamic_pointer_cast<T>(*it))
			target.push_back(boost::dynamic_pointer_cast<T>(*it));
	}
}

static void parseDBargument(std::string db_arg, std::string & db_host, std::string & db_user, std::string & db_database, int & db_port)
{
	std::size_t pos = 0;
	if ( (pos = db_arg.find_first_of('@')) != db_arg.npos) {
		db_user = db_arg.substr(0, pos);
		db_arg = db_arg.substr(pos + 1);
	} else {
		throw std::runtime_error("User name not found in " + db_arg);
	}

	if ( (pos = db_arg.find_first_of(':')) != db_arg.npos) {
		db_host = db_arg.substr(0, pos);
		db_arg = db_arg.substr(pos + 1);

		if ( (pos = db_arg.find_first_of('/')) != db_arg.npos) {
			std::stringstream ss;
			ss << db_arg.substr(0, pos);
			ss >> db_port;
			db_arg = db_arg.substr(pos + 1);
		} else {
			throw std::runtime_error("Database name not found in " + db_arg);
		}

	} else if ( (pos = db_arg.find_first_of('/')) != db_arg.npos) {
		db_host = db_arg.substr(0, pos);
		db_arg = db_arg.substr(pos + 1);
	} else {
		throw std::runtime_error("Host name not found in " + db_arg);
	}

	db_database = db_arg;
}

}

#endif /* UTIL_H_ */

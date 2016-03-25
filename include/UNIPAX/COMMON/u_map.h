/*
 * u_map.h
 *
 *  Created on: Oct 30, 2013
 *      Author: gerasch
 */

#ifndef U_MAP_H_
#define U_MAP_H_

#include <boost/tr1/unordered_map.hpp>
#include <QtCore>

inline std::size_t hash_value(QString const& b)
{
	return boost::hash_value(b.toStdString());
}

namespace UniPAX
{

template<typename K, typename V>
struct u_map {
    typedef std::tr1::unordered_map<K, V> type;
};

}

#endif /* U_MAP_H_ */

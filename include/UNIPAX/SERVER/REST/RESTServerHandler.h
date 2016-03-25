/*
 * RESTServerHandler.h
 *
 *  Created on: Feb 13, 2012
 *      Author: gerasch
 */

#ifndef RESTSERVERHANDLER_H_
#define RESTSERVERHANDLER_H_

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/SERVER/HTTP/qhttpserver.h>
#include <UNIPAX/SERVER/HTTP/qhttprequest.h>
#include <UNIPAX/SERVER/HTTP/qhttpresponse.h>

#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>

#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>

#include <QRegExp>

#include <vector>
#include <set>


namespace UniPAX
{

namespace SERVER
{

class UNIPAX_EXPORT RESTServerHandler
{

public:

	RESTServerHandler(QString name);

	virtual ~RESTServerHandler()
	{
	}

	QString name()
	{
		return _name;
	}

	boost::program_options::options_description & options()
	{
		return _options;
	}

	std::vector<QRegExp> pattern()
	{
		return _pattern;
	};

	void setEngine(QueryEngine* _engine)
	{
		engine = _engine;
	}

	virtual void init(boost::program_options::variables_map & _vm) = 0;

	virtual bool handle(QHttpRequest *req, QHttpResponse *resp) = 0;

	virtual QString help(QString format = "") = 0;


protected:

	QString _name;

	boost::program_options::options_description _options;

	QueryEngine* engine;

	std::vector<QRegExp> _pattern;

	void respond(QHttpRequest *req, QHttpResponse *resp, std::set<UnipaxId> & ids, QString format);

};

}

}

Q_DECLARE_INTERFACE(UniPAX::SERVER::RESTServerHandler, "info.unipax.server.rest.RESTServerHandler/1.0")



#endif /* RESTSERVERHANDLER_H_ */

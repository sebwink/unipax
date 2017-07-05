/*
 * UnipaxBrowserHandler.h
 *
 *  Created on: Feb 13, 2012
 *      Author: gerasch
 */

#ifndef UNIPAXBROWSERHANDLER_H_
#define UNIPAXBROWSERHANDLER_H_

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

class UNIPAX_EXPORT UnipaxBrowserHandler
{

public:

	UnipaxBrowserHandler(QString name);

	virtual ~UnipaxBrowserHandler()
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

Q_DECLARE_INTERFACE(UniPAX::SERVER::UnipaxBrowserHandler, "info.unipax.server.rest.UnipaxBrowserHandler/1.0")



#endif /* UNIPAXBROWSERHANDLER_H_ */

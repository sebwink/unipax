#ifndef BENCHMARKSERVERHANDLER_H_
#define BENCHMARKSERVERHANDLER_H_

#include <UNIPAX/SERVER/REST/RESTServerHandler.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>
#include <UNIPAX/COMMON/DBConnector.h>

#include <QObject>
#include <vector>


class BenchmarkServerHandler : public QObject, protected UniPAX::SERVER::RESTServerHandler
{
	Q_OBJECT
	Q_INTERFACES(UniPAX::SERVER::RESTServerHandler)

public:

        BenchmarkServerHandler();

        ~BenchmarkServerHandler();

	QString help(QString format = "");

	void init(boost::program_options::variables_map & _vm);

	bool handle(QHttpRequest *req, QHttpResponse *resp);

private:

	static QRegExp benchmark_cache, benchmark_cache_auto; 
	UniPAX::DBConnectorPtr dbc;
};


#endif /* BENCHMARKSERVERHANDLER_H_ */

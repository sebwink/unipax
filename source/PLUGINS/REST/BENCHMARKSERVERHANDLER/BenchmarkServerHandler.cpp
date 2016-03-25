#include <PLUGINS/REST/BENCHMARKSERVERHANDLER/BenchmarkServerHandler.h>

#include <UNIPAX/COMMON/OrganismSet.h>
#include <UNIPAX/COMMON/PathwaySet.h>
#include <UNIPAX/COMMON/KernelClassSet.h>
#include <UNIPAX/KERNEL/EXT/ResultObject.h>
#include <UNIPAX/KERNEL/all.h>

#include <UNIPAX/SERVER/HTTP/qhttpconnection.h>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>

#include <stdlib.h>
#include <sstream>
#include <time.h>

#include <QtXml>

#include <QtCore/qplugin.h>
#include <QtNetwork>

QRegExp BenchmarkServerHandler::benchmark_cache("/benchmark/cache", Qt::CaseSensitive, QRegExp::RegExp2);

QRegExp BenchmarkServerHandler::benchmark_cache_auto("/benchmark/cache/auto", Qt::CaseSensitive, QRegExp::RegExp2);

BenchmarkServerHandler::BenchmarkServerHandler() : RESTServerHandler("Benchmark Server Handler")
{
				_pattern.push_back(BenchmarkServerHandler::benchmark_cache);
				_pattern.push_back(BenchmarkServerHandler::benchmark_cache_auto);
}


BenchmarkServerHandler::~BenchmarkServerHandler()
{
				engine = 0;
}

void BenchmarkServerHandler::init(boost::program_options::variables_map & _vm)
{
				dbc = UniPAX::DBConnectorPtr(new UniPAX::DBConnector());
				dbc->setEngine(UnipaxPtr<UniPAX::SERVER::QueryEngine>::type(engine));
}

QString BenchmarkServerHandler::help(QString format)
{
				if (format == "html")
				{
								return 	QString("<tr><td colspan=2><b>Benchmarks the UniPAX REST server:</b></td></tr>")
												// cache
												.append("<tr><td valign=top><b>/benchmark/cache</b></td><td>")
												.append("Returns the time needed for loading from DB vs from cache.<br/>")
												.append("<br/>")
												.append("<b>Syntax:</b> /benchmark/cache?result=&lt;ResultObject IDd&gt;<br/>")
												.append("<br/>")
												.append("<b>Parameters:</b> ")
												.append("<ul>")
												.append("<li>result - specifies the ResultObject which contains all ids to load in the benchmark. Can not be empty.</li>")
												.append("</ul>")
												.append("</td><tr/>")
												.append("<tr><td valign=top><b>/benchmark/cache/auto?repeats=&lt;Integer&gt;&max=&lt;Integer&gt;</b></td><td>")
												.append("Runs an automatic test for loading from DB vs from cache.<br/>")
												.append("<br/>")
												.append("<b>Syntax:</b> /benchmark/cache/auto<br/>")
												.append("<br/>")
												.append("<b>Parameters:</b> ")
												.append("<ul>")
												.append("<li>repeats - specifies the number of repeated loading benchmarks. If left empty defaults to 3.</li>")
												.append("<li>max - specifies the maximum number of objects loaded in the benchmark. If left empty defaults to the number of objects in the db	.</li>")
												.append("</ul>")
												.append("</td></tr>");
				}

				return "";

}

bool BenchmarkServerHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{
	QString path(req->path());

	if ( BenchmarkServerHandler::benchmark_cache_auto.exactMatch(path) )
	{
		int repeats = 3;
		QString repeats_field = req->url().queryItemValue("repeats");
		if (!repeats_field.isEmpty())
		{

			bool ok;
			repeats = repeats_field.toInt(&ok);
			if (!ok)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Argument of 'repeats' must be an Integer."));
				resp->end();
				return true;
			}

		}
		// determine IDs to load
		UniPAX::OrganismSet orgs(dbc);
		UniPAX::PathwaySet pwys(dbc);
		UniPAX::KernelClassSet types(dbc);
		UniPAX::ResultObjectPtr all_ids = dbc->query(orgs, pwys, types);
		int max_ids = all_ids->getObjectIds().size();
		QString max_ids_field = req->url().queryItemValue("max");
		if (!max_ids_field.isEmpty())
		{

			bool ok;
			max_ids = max_ids_field.toInt(&ok);
			if (!ok)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Argument of 'max' must be an Integer."));
				resp->end();
				return true;
			}
			if (max_ids > all_ids->getObjectIds().size())
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(404);
				resp->write(QString("ERROR: Argument of 'max' higher than number of objects in db."));
				resp->end();
				return true;
			}

		}
		QString body("Benchmark result:\n");

		body.append(QString("Number of object ids in DB: "))
														.append(QString::number(all_ids->getObjectIds().size()))
														.append(QString("\n\n"));
		// random select 10^i ids to load and measure loading times repeat 3 times
		int id_amount = 10;
		boost::mt19937 gen;
		while (id_amount <= max_ids)
		{
			body.append(QString("Random select "))
																		.append(QString::number(id_amount))
																		.append(QString(" ids to load:\n"));

			for (int repeat=0; repeat<repeats; repeat++)
			{
				std::vector<UnipaxId> urn(all_ids->getObjectIds().begin(),all_ids->getObjectIds().end());
				boost::uniform_int<> rand_all(0, urn.size()-1);
				std::vector<UnipaxId> ids_v;
				for (int i=0; i<id_amount; i++)
				{
					int idx = rand_all(gen, urn.size()-1);
					ids_v.push_back(urn.at(idx));
					urn.erase(urn.begin()+idx);
				}
				std::vector<UniPAX::UPBasePtr> objects;
				// delete all ids from cache
				if (!dbc->getEngine()->getDBManager()->removeObjectsFromCache(ids_v))
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Could not delete Objects from Cache."));
					resp->end();
					return true;
				}

				// load all ids (from DB)
				boost::posix_time::ptime t_start(micro_sec::universal_time());
				if (!dbc->getEngine()->getDBManager()->getObjectsByIDs(objects, ids_v))
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Could not load Objects from DB."));
					resp->end();
					return true;
				}
				boost::posix_time::time_duration db_time(micro_sec::universal_time() - t_start);
				// load all ids (from Cache)
				objects.clear();
				t_start = micro_sec::universal_time();

				if (!dbc->getEngine()->getDBManager()->getObjectsByIDs(objects, ids_v))
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(404);
					resp->write(QString("ERROR: Could not load Objects from cache."));
					resp->end();
					return true;
				}
				boost::posix_time::time_duration cache_time(micro_sec::universal_time() - t_start);
				body.append(QString("Loading times:\n"))
																						.append(QString("from database (sec)\tfrom cache (sec)\tdifference (sec)\n"))
																						.append(QString(boost::posix_time::to_iso_string(db_time).c_str()))
																						.append(QString("\t"))
																						.append(QString(boost::posix_time::to_iso_string(cache_time).c_str()))
																						.append(QString("\t"))
																						.append(QString(boost::posix_time::to_iso_string(db_time - cache_time).c_str()))
																						.append(QString("\n"));

			}
			id_amount*=10;
			body.append(QString("\n"));
		}
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(body);
		resp->end();
		return true;
	}
	if ( BenchmarkServerHandler::benchmark_cache.exactMatch(path) )
	{
		// load ResultObject
		QString from = req->url().queryItemValue("result");
		if (from.size() == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: '/benchmark/cache' needs a ResultObject id as 'result' argument."));
			resp->end();
			return true;

		}
		bool ok;
		UnipaxId from_id = from.toULongLong(&ok);
		if (!ok)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not convert '")
					.append(from)
					.append(QString("' to a UnipaxId.")));
			resp->end();
			return true;
		}
		UniPAX::ResultObjectPtr result = boost::dynamic_pointer_cast<UniPAX::ResultObject>(dbc->getEngine()->getDBManager()->getObjectByID(from_id));
		if (result == 0)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not load ResultObject from id '")
					.append(from)
					.append(QString("'.")));
			resp->end();
			return true;
		}
		std::vector<UnipaxId> ids_v(result->getObjectIds().begin(), result->getObjectIds().end());
		// delete all ids from cache
		if (!dbc->getEngine()->getDBManager()->removeObjectsFromCache(ids_v))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not delete Objects from Cache. ResultObject: ")
					.append(from)
					.append(QString("'.")));
			resp->end();
			return true;
		}

		// load all ids (from DB)
		std::vector<UniPAX::UPBasePtr> objects;
		boost::posix_time::ptime t_start(micro_sec::universal_time());
		if (!dbc->getEngine()->getDBManager()->getObjectsByIDs(objects, ids_v))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not load Objects from DB. ResultObject: ")
					.append(from)
					.append(QString("'.")));
			resp->end();
			return true;
		}
		boost::posix_time::time_duration db_time(micro_sec::universal_time() - t_start);

		// load all ids (from Cache)
		objects.clear();
		t_start = micro_sec::universal_time();

		if (!dbc->getEngine()->getDBManager()->getObjectsByIDs(objects, ids_v))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(404);
			resp->write(QString("ERROR: Could not load Objects from cache.")
					.append(from)
					.append(QString("'.")));
			resp->end();
			return true;
		}
		boost::posix_time::time_duration cache_time(micro_sec::universal_time() - t_start);
		// report times

		QString body("Benchmark result:\n");

		body.append(QString("Loaded object id list:\n"));

		std::set<UnipaxId> ids = result->getObjectIds();
		for (std::set<UnipaxId>::const_iterator it = ids.begin(); it != ids.end(); ++it)
		{
			if (it != ids.begin())
				body.append(QString("\n"));
			body.append(QString::number(*it));
		}
		body.append(QString("\n\nLoading times:\n"))
														.append(QString("from database (sec)\tfrom cache (sec)\tdifference (sec)\n"))
														.append(QString(boost::posix_time::to_iso_string(db_time).c_str()))
														.append(QString("\t"))
														.append(QString(boost::posix_time::to_iso_string(cache_time).c_str()))
														.append(QString("\t"))
														.append(QString(boost::posix_time::to_iso_string(db_time - cache_time).c_str()))
														.append(QString("\n"));
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(body);
		resp->end();
		return true;

	}
	return false;
}

Q_EXPORT_PLUGIN2(BenchmarkServerHandler, BenchmarkServerHandler)


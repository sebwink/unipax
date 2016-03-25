#include <PLUGINS/REST/DATAUPLOADSERVERHANDLER/DataUploadServerHandler.h>

#include <UNIPAX/COMMON/Singleton.h>
#include <UNIPAX/IMPORT/SBML/MiriamLinkREST.h>
//#include <UNIPAX/COMMON/KernelClassSet.h>
//#include <UNIPAX/KERNEL/EXT/ResultObject.h>
//#include <UNIPAX/KERNEL/all.h>

#include <UNIPAX/SERVER/HTTP/qhttpconnection.h>
//#include <boost/date_time/posix_time/posix_time.hpp>

#include <vector>
#include <algorithm>
//#include <stdlib.h>
//#include <sstream>
//#include <time.h>

#include <QUrl>

#include <boost/asio.hpp>

#include <QtCore/qplugin.h>
#include <QtNetwork>

QRegExp DataUploadServerHandler::upload_csv("/upload/csv", Qt::CaseSensitive, QRegExp::RegExp2);

DataUploadServerHandler::DataUploadServerHandler() : RESTServerHandler("DataUpload Server Handler")
{
	_pattern.push_back(DataUploadServerHandler::upload_csv);
}


DataUploadServerHandler::~DataUploadServerHandler()
{
	engine = 0;
}

void DataUploadServerHandler::init(boost::program_options::variables_map & _vm)
{
	dbc = UniPAX::DBConnectorPtr(new UniPAX::DBConnector());
	dbc->setEngine(UnipaxPtr<UniPAX::SERVER::QueryEngine>::type(engine));
}

QString DataUploadServerHandler::help(QString format)
{
	if (format == "html")
	{
		return 	QString("<tr><td colspan=2><b>Upload data to the UniPAX REST server:</b></td></tr>")
				// cache
				.append("<tr><td valign=top><b>/upload/csv</b></td><td>")
				.append("Upload a data file in comma/tab separated value format via an html form.<br/>")
				.append("<br/>")
				.append("<b>Syntax:</b> /upload/csv?form=1<br/>")
				//				.append("<b>Syntax:</b> /upload/csv?file=&lt;URL&gt;&id_columns=0,1&ignore_columns=2,3&column_names=1<br/>")
				//				.append("<br/>")
				//				.append("<b>Parameters:</b> ")
				//				.append("<ul>")
				//				.append("<li>file - Url to the file containing the data.</li>")
				//				.append("</ul>")
				//				.append("<ul>")
				//				.append("<li>id_columns - Columns (counting from 0) containing the probe ids.</li>")
				//				.append("</ul>")
				//				.append("<ul>")
				//				.append("<li>ignore_columns - Columns (counting from 0) to be ignored (not containing relevant ids or data points).</li>")
				//				.append("</ul>")
				//				.append("<ul>")
				//				.append("<li>column_names - Row (counting from 0) containing the column names.</li>")
				//				.append("</ul>")
				.append("</td></tr>");
	}

	return "";

}

bool DataUploadServerHandler::parseSeparator(ConstIterator line)
{
	if (line->startsWith("-------------------"))
		return true;
	return false;
}

bool DataUploadServerHandler::parseName(std::string & name, ConstIterator & line)
{
	if (!line->startsWith("Content-Disposition: form-data; name=\"sample_name\"")) return false;
	line++;
	if (!line->trimmed().isEmpty()) return false;
	line++;
	name = QString(line->trimmed()).toStdString();
	line++;
	return true;
}

bool DataUploadServerHandler::parseDesc(std::map<std::string, std::string> & desc_tags, ConstIterator & line)
{
	if (!line->startsWith("Content-Disposition: form-data; name=\"desc_tags\"")) return false;
	line++;
	if (!line->trimmed().isEmpty()) return false;
	line++;
	// ignore default example tags...
	if (line->startsWith("tag_name_1=value_1"))
	{
		while (!parseSeparator(line)) line++;
		return true;
	}
	// parse tags and values
	while (!parseSeparator(line))
	{
		QList<QByteArray> tag_value = line->split('=');
		// check
		if (tag_value.size() != 2) return false;
		desc_tags.insert(std::pair<std::string, std::string>(QString(tag_value[0].trimmed()).toStdString(), QString(tag_value[1].trimmed()).toStdString()));
		line++;
	}
	return true;
}

bool DataUploadServerHandler::parseFormat(std::string & format, ConstIterator & line)
{
	if (!line->startsWith("Content-Disposition: form-data; name=\"file_type\"")) return false;
	line++;
	if (!line->trimmed().isEmpty()) return false;
	line++;
	format = QString(*line).trimmed().toStdString();
	line++;
	return true;
}

bool DataUploadServerHandler::parseSubFieldSep(char & sub_sep, ConstIterator & line)
{
	if (!line->startsWith("Content-Disposition: form-data; name=\"sub_sep\"")) return false;
	line++;
	if (!line->trimmed().isEmpty()) return false;
	line++;
	sub_sep = QString(*line).at(0).toAscii(); // may be space
	line++;
	return true;
}

bool DataUploadServerHandler::parseDbName(std::string & db_name, ConstIterator & line)
{
	if (!line->startsWith("Content-Disposition: form-data; name=\"db_name\"")) return false;
	line++;
	if (!line->trimmed().isEmpty()) return false;
	line++;
	db_name = QString(*line).trimmed().toStdString();
	line++;
	return true;
}

bool DataUploadServerHandler::parseColNameRow(unsigned int & row, ConstIterator & line)
{
	if (!line->startsWith("Content-Disposition: form-data; name=\"col_name\"")) return false;
	line++;
	if (!line->trimmed().isEmpty()) return false;
	line++;
	bool ok = false;
	row = (*line).trimmed().toUInt(&ok);
	if (!ok) return false;
	line++;
	return true;
}

bool DataUploadServerHandler::parseIdCol(unsigned int & col, ConstIterator & line)
{
	if (!line->startsWith("Content-Disposition: form-data; name=\"id_col\"")) return false;
	line++;
	if (!line->trimmed().isEmpty()) return false;
	line++;
	bool ok = false;
	col = (*line).trimmed().toUInt(&ok);
	if (!ok) return false;
	line++;
	return true;
}

bool DataUploadServerHandler::parseFirstDataCol(unsigned int & col, ConstIterator & line)
{
	if (!line->startsWith("Content-Disposition: form-data; name=\"first_data_col\"")) return false;
	line++;
	if (!line->trimmed().isEmpty()) return false;
	line++;
	bool ok = false;
	col = (*line).trimmed().toUInt(&ok);
	if (!ok) return false;
	line++;
	return true;
}

bool DataUploadServerHandler::parseXsv(UniPAX::SeriesPtr & series, char sep, ConstIterator & line, const unsigned int id_col, const unsigned int first_val_col, const char sub_sep)
{
	// get last added Sample object.
	UniPAX::SamplePtr sample = series->getSampleList().back();
	// if there are already data, something is wrong
	if (sample->getSampleData() != 0) return false;
	//sample->setSampleData(UniPAX::DoubleMatrixSampleDataPtr(new DoubleMatrixSampleData(data, column_names)));
	UniPAX::IdMappingPtr mapping = series->getIdMappingList().back();

	std::vector<std::string> column_names;
	std::vector<UniPAX::DoubleMatrixSampleData::SampleDataType> rows;

	unsigned int lnum = 0;
	while (!parseSeparator(line))
	{
		if (!line->trimmed().isEmpty())
		{

			QList<QByteArray> tokens = line->split(sep);
			if (lnum == 0) // first line, column names
			{
				for (int i=0; i < tokens.size(); ++i)
				{
					column_names.push_back(QString(tokens[i]).trimmed().toStdString());
				}
			}
			else
			{
				UniPAX::DoubleMatrixSampleData::SampleDataType row;
				for (int i=0; i < tokens.size(); ++i)
				{
					if (i<first_val_col)
					{
						if (i == id_col) // id column
						{
							QList<QByteArray> multi_ids = tokens[i].trimmed().split(sub_sep);
							for (ConstIterator it = multi_ids.constBegin(); it != multi_ids.constEnd(); it++)
							{
								mapping->getIds().insert(std::pair<int, std::string>(lnum, QString(it->trimmed()).toStdString()));
							}
						}
						else
						{
							// ignore other cols
							// TODO could be put into StringSampeData
						}
					}
					else // value column
					{
						row.push_back(QString(tokens[i].trimmed()).toDouble());
					}
				}
				rows.push_back(row);
			}
			lnum++;
		}
		line++;
	}
	sample->setSampleData(UniPAX::DoubleMatrixSampleDataPtr(new UniPAX::DoubleMatrixSampleData(rows, column_names)));
	std::string debug_info = sample->getSampleData()->getValueType();
	return true;
}

bool DataUploadServerHandler::parseData(UniPAX::SeriesPtr & series, std::string format, ConstIterator & line, const unsigned int col_name_row, const unsigned int id_col, const unsigned int first_data_col, const char sub_sep)
{
	if (!line->startsWith("Content-Disposition: form-data; name=\"file_data\"; filename=")) return false;
	line++;
	if (!line->startsWith("Content-Type: application/octet-stream") && !line->startsWith("Content-Type: text/")) return false;
	line++;
	if (!line->trimmed().isEmpty()) return false;
	line++;
	std::stringstream ss;
	for (unsigned int i=0; i != col_name_row; i++)
	{ // ignore lines before column names
		std::string data(line->trimmed().data());
		if (!data.empty())
		{
			ss.str("non-data-line");
			ss << i;
			series->getSampleList().back()->setDescriptionTag(ss.str(), data);
		}
		line++;
	}
	if (format.compare("csv") == 0)
	{ // parse csv data
		if (!parseXsv(series, ',', line, id_col, first_data_col, sub_sep)) return false;
	}
	else if (format.compare("tsv") == 0)
	{
		if (!parseXsv(series, '\t', line, id_col, first_data_col, sub_sep)) return false;
	}
	// TODO other formats go here!
	else
	{
		return false;
	}
	return true;
}


UniPAX::SeriesPtr DataUploadServerHandler::parseSeriesData(bool & ok, QByteArray data)
{
	UniPAX::SeriesPtr series(new UniPAX::Series());

	UniPAX::SamplePtr sample(new UniPAX::Sample());
	series->addSample(sample);

	UniPAX::IdMappingPtr mapping(new UniPAX::IdMapping());
	mapping->setSampleIndex(0);
	series->addIdMapping(mapping);

	QList<QByteArray> lines = data.split('\n');
	ConstIterator lit = lines.constBegin();
	ConstIterator errit = lines.constEnd();
	int state = NAME;
	std::string format = "none";
	std::string db_name;
	char sub_sep = ' ';
	unsigned int col_name_row, id_col, first_data_col;
	while (lit != lines.constEnd() && state != ERROR)
	{
		switch (state) {
		case ERROR:
			// should never be reached
			break;
		case NAME:
		{
			if (!parseSeparator(lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			lit++;
			std::string name;
			if (!parseName(name, lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			sample->setName(name);
			state = DESC;
		}
		break;
		case DESC:
		{
			if (!parseSeparator(lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			lit++;
			std::map<std::string, std::string> desc_tags;
			if (!parseDesc(desc_tags, lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			sample->setDescriptionTags(desc_tags);
			state = FORMAT;
		}
		break;
		case FORMAT:
		{
			if (!parseSeparator(lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			lit++;
			if (!parseFormat(format, lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			state = SUBSEP;
		}
		break;
		case SUBSEP:
		{
			if (!parseSeparator(lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			lit++;
			if (!parseSubFieldSep(sub_sep, lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			state = DBNAME;
		}
		break;
		case DBNAME:
		{
			if (!parseSeparator(lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			lit++;
			if (!parseDbName(db_name, lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			state = CNROW;
		}
		break;
		case CNROW:
		{
			if (!parseSeparator(lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			lit++;
			if (!parseColNameRow(col_name_row, lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			state = IDCOL;
		}
		break;
		case IDCOL:
		{
			if (!parseSeparator(lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			lit++;
			if (!parseIdCol(id_col, lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			state = FDCOL;
		}
		break;
		case FDCOL:
		{
			if (!parseSeparator(lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			lit++;
			if (!parseFirstDataCol(first_data_col, lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			state = DATA;
		}
		break;
		case DATA:
		{
			if (!parseSeparator(lit))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			lit++;
			if (!parseData(series, format, lit, col_name_row, id_col, first_data_col, sub_sep))
			{
				state = ERROR;
				errit = lit;
				break;
			}
			series->getIdMappingList().back()->setDbName(db_name);
			lit++;
			state = END;
		}
		break;
		case END:
		{
			// data after end?
					if (!lit->trimmed().isEmpty())
					{
						state = ERROR;
						errit = lit;
					}
					lit++;
		}
		break;
		}
		//lit++;
	}
	ok = true;
	if (state == ERROR)
	{
		error_ln = errit-lines.constBegin();
		error_line = *errit;
		ok = false;
	}
	if (state != END)
	{
		ok = false;
	}
	return series;
}

bool DataUploadServerHandler::checkMiriam(UniPAX::SeriesPtr series)
{
	for (std::vector<UniPAX::IdMappingPtr>::const_iterator mit = series->getIdMappingList().begin(); mit != series->getIdMappingList().end(); ++mit)
	{
		UniPAX::MiriamLink* miriam = UniPAX::Singleton<UniPAX::MiriamLink>::getInstance(new UniPAX::MiriamLink()).get();
		if ((miriam->getDataTypeURIs((*mit)->getDbName())).empty())
		{
			return false;
		}
	}
	return true;
}

void DataUploadServerHandler::handlePostRequest(QHttpRequest *req, QHttpResponse *resp)
{
	QByteArray data = req->body();
	if (data.isEmpty())
	{
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(400);
		resp->write(QString("ERROR: No data in HTTP POST request."));
		resp->end();
	}
	else
	{
		bool success;
		UniPAX::SeriesPtr series = parseSeriesData(success, data);
		UniPAX::SamplePtr sample = series->getSampleList().back();
		UniPAX::IdMappingPtr mapping = series->getIdMappingList().back();
		UniPAX::SampleDataPtr sdata = sample->getSampleData();
		if (!success)
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(422);
			resp->write(QString("ERROR: Parsing error for data in HTTP POST request line ").append(QString::number(error_ln)).append(":\n"));
			resp->write(error_line);
			resp->write(QString("\n\n").append(data));
			resp->end();
			return;
		}
		if(!checkMiriam(series))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Database name of Experiment ID mapping is invalid."));
			resp->end();
			return;
		}
//		if(!dbc->assignId(sdata))
//		{
//			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
//			resp->writeHead(500);
//			resp->write(QString("ERROR: Could not assign an id to SampleDataBase."));
//			resp->end();
//			return;
//		}
//		try {
//			odb::transaction t(dbc->getEngine()->getDBManager()->getOdbDatabase()->begin());
//			dbc->getEngine()->getDBManager()->getOdbDatabase()->persist(boost::dynamic_pointer_cast<UniPAX::SampleData>(sdata));
//			t.commit();
//		}
//		catch (const odb::exception& e)
//		{
////		if (!)
////		{
//			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
//			resp->writeHead(500);
//			resp->write(QString("ERROR: Created SampleDataBase could not be persisted."));
//			resp->end();
//			return;
//		}
//		if (!dbc->update(sdata))
//		{
//			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
//			resp->writeHead(500);
//			resp->write(QString("ERROR: Created SampleDataBase could not be updated."));
//			resp->end();
//			return;
//		}
		if(!dbc->assignId(sample))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Could not assign an id to Sample."));
			resp->end();
			return;
		}
		if (!dbc->persist(sample))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Created Sample could not be persisted."));
			resp->end();
			return;
		}
		if (!dbc->update(sample))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Created Sample could not be updated."));
			resp->end();
			return;
		}
		if(!dbc->assignId(mapping))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Could not assign an id to IdMapping."));
			resp->end();
			return;
		}
		if (!dbc->persist(mapping))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Created IdMapping could not be persisted."));
			resp->end();
			return;
		}
		if (!dbc->update(mapping))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Created IdMapping could not be updated."));
			resp->end();
			return;
		}
		if(!dbc->assignId(series))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Could not assign an id to Experiment."));
			resp->end();
			return;
		}
		if (!dbc->persist(series))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Created Experiment could not be persisted."));
			resp->end();
			return;
		}
		if (!dbc->update(series))
		{
			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(500);
			resp->write(QString("ERROR: Created Experiment could not be updated."));
			resp->end();
			return;
		}
		resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
		resp->writeHead(200);
		resp->write(QString::number(series->getUnipaxId()));
		resp->end();
	}
}

void DataUploadServerHandler::supplyUploadForm(QHttpRequest *req, QHttpResponse *resp)
{
	//std::cout << "Server address: " << req->url().host().toStdString() << ":" << req->url().port() << std::endl;
	resp->setHeader("Content-Type", "text/html; charset=UTF-8");
	resp->writeHead(200);
	resp->write(QString("<!DOCTYPE html>")
			.append("<html lang=\"en\">")
			.append("<head>")
			.append("<meta charset=\"utf-8\"/>")
			.append("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">")
			.append("<link rel=\"stylesheet\" href=\"http://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css\">")
			.append("<title>UniPAX Data Upload</title>")
			.append("</head>")
			.append("<body>")
			.append("<h2>UniPAX Data Upload form</h2>")
			.append("<form action=\"http://").append(req->url().authority()).append("/upload/csv\" method=\"post\" enctype=\"multipart/form-data\">")
			.append("<div class=\"container-fluid\">")
			.append("<div class=\"form-group\">")
			.append("<label for=\"sample_name\">Enter a name for the sample:</label>")
			.append("<input type=\"text\" name=\"sample_name\" id=\"sample_name\" required>")
			.append("</div>")
			.append("<div class=\"form-group\">")
			.append("<label for=\"desc_tags\">Enter description tags:</label>")
			.append("<textarea rows=\"4\" cols=\"50\" name=\"desc_tags\" id=desc_tags>")
			.append("tag_name_1=value_1\n")
			.append("tag_name_2=value_2\n")
			.append("...")
			.append("</textarea>")
			.append("</div>")
			.append("<div class=\"form-group\">")
			.append("<label for=\"file_type\">Select the file type:</label>")
			.append("<input type=\"text\" id=\"file_type\" name=\"file_type\" list=\"file_types\" required>")
			.append("<datalist id=\"file_types\">")
			.append("<option value=\"csv\">")
			.append("<option value=\"tsv\">")
			.append("</datalist>")
			.append("</div>")
			.append("<div class=\"form-group\">")
			.append("<label for=\"sub_sep\">Sub-field separator:</label>")
			.append("<input type=\"text\" name=\"sub_sep\" id=\"sub_sep\" value=\";\" required>")
			.append("</div>")
			.append("</div>")
			.append("<div class=\"form-group\">")
			.append("<label for=\"db_name\">Official name of id system:</label>")
			.append("<input type=\"text\" name=\"db_name\" id=\"db_name\" required>")
			.append("</div>")
			.append("<div class=\"form-group\">")
			.append("<label for=\"id_col\">Index of line containing the column names:</label>")
			.append("<input type=\"text\" name=\"col_name\" id=\"col_name\" value=\"0\" required>")
			.append("</div>")
			.append("<div class=\"form-group\">")
			.append("<label for=\"id_col\">Index of column containing the ids:</label>")
			.append("<input type=\"text\" name=\"id_col\" id=\"id_col\" value=\"0\" required>")
			.append("</div>")
			.append("<div class=\"form-group\">")
			.append("<label for=\"first_data_col\">Index of first data column:</label>")
			.append("<input type=\"text\" name=\"first_data_col\" id=\"first_data_col\" value=\"1\" required>")
			.append("</div>")
			.append("<div class=\"form-group\">")
			.append("<label for=\"sample_data_file\">Select the sample file:</label>")
			.append("<input type=\"file\" name=\"file_data\" id=\"sample_data_file\" required>")
			.append("</div>")
			.append("<div class=\"form-group\">")
			.append("<button type=\"submit\">Upload</button>")
			.append("</div>")
			.append("</div>")
			.append("</form>")
			.append("</body>")
			.append("</html>"));
	resp->end();
}

bool DataUploadServerHandler::handle(QHttpRequest *req, QHttpResponse *resp)
{
	QString path(req->path());

	if (DataUploadServerHandler::upload_csv.exactMatch(path))
	{
		if (req->method() == "POST")
		{
			handlePostRequest(req, resp);
		}
		else
		{
			if(req->url().hasQueryItem("form"))
			{
				supplyUploadForm(req, resp);
				return true;
			}
			// Check if file field contains a valid URL.
			QString file_field = req->url().queryItemValue("file");
			QUrl file_url;
			if (!file_field.isEmpty())
			{
				file_url = QUrl(file_field, QUrl::StrictMode);
				if (!file_url.isValid())
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(422);
					resp->write(QString("ERROR: 'file' contains an invalid URL."));
					resp->end();
					return true;
				}
				if (file_url.host().isEmpty())
				{
					file_url.setHost(req->remoteAddress());
					//file_url.setPort(req->remotePort());
				}
			}
			// Parse other parameters
			QStringList id_columns_field = req->url().queryItemValue("id_columns").split(",", QString::SkipEmptyParts);
			std::vector<size_t> id_columns;
			if (id_columns_field.isEmpty())
			{
				id_columns.push_back(0);
			}
			else
			{
				size_t index;
				for (QStringList::iterator it = id_columns_field.begin(); it != id_columns_field.end(); ++it)
				{
					bool ok;
					index = it->toUInt(&ok);
					if (!ok)
					{
						resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
						resp->writeHead(422);
						resp->write(QString("ERROR: 'id_columns' must be a comma separated list of non-negative Integers."));
						resp->end();
						return true;
					}
					id_columns.push_back(index);
				}
			}
			QStringList ignore_columns_field = req->url().queryItemValue("ignore_columns").split(",", QString::SkipEmptyParts);
			std::vector<size_t> ignore_columns;
			if (!ignore_columns_field.isEmpty())
			{
				size_t index;
				for (QStringList::iterator it = ignore_columns_field.begin(); it != ignore_columns_field.end(); ++it)
				{
					bool ok;
					index = it->toUInt(&ok);
					if (!ok)
					{
						resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
						resp->writeHead(422);
						resp->write(QString("ERROR: 'ignore_columns' must be a comma separated list of non-negative Integers."));
						resp->end();
						return true;
					}
					ignore_columns.push_back(index);
				}
			}
			QString column_names_field = req->url().queryItemValue("column_names");
			size_t column_names;
			if (!column_names_field.isEmpty())
			{
				bool ok;
				column_names = column_names_field.toUInt(&ok);
				if (!ok)
				{
					resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
					resp->writeHead(422);
					resp->write(QString("ERROR: 'column_names' must be a non negative Integer."));
					resp->end();
					return true;
				}
			}
			// check that 'id_columns' & 'ignore_columns' are mutually inequal
			std::sort(id_columns.begin(), id_columns.end());
			std::sort(ignore_columns.begin(), ignore_columns.end());
			if (id_columns.size() != 0 && ignore_columns.size() != 0)
			{
				std::vector<size_t>::const_iterator it1=id_columns.begin();
				std::vector<size_t>::const_iterator it2=ignore_columns.begin();
				bool done = false;
				while (!done)
				{
					if (it1==id_columns.end() || it2==ignore_columns.end())
						done = true;
					else
					{
						if (*it1 == *it2)
						{
							resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
							resp->writeHead(422);
							resp->write(QString("ERROR: 'id_columns' and 'ignore_columns' must be mutually different."));
							resp->end();
							return true;
						}
						else if (*it1 < *it2)
						{
							++it1;
						}
						else
						{
							++it2;
						}
					}
				}
				// If we reach this place, everything looks ok.
			}
			QByteArray data;
			QNetworkReply::NetworkError e_code = httpGetFile(file_url, data);
			if (e_code != QNetworkReply::NoError)
			{
				resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
				resp->writeHead(303);
				resp->write(QString("ERROR: QNetworkReply::NetworkError ").append(QString::number(e_code)));
				resp->end();
				return true;
			}
			QString csv_data(data);
			//		std::stringstream file_data;
			//		boost::system::error_code ec = httpGetFile(file_url, file_data);
			//		if (ec.value() != boost::system::errc::success)
			//		{
			//			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			//			resp->writeHead(303);
			//			resp->write(QString("ERROR: boost::system::error_code ").append(QString::fromStdString(ec.message())));
			//			resp->end();
			//			return true;
			//		}
			//TODO load & parse file, save it in the db.

			resp->setHeader("Content-Type", "text/plain; charset=UTF-8");
			resp->writeHead(501);
			//		resp->write(QString::fromStdString(file_data.str()));
			resp->write(csv_data);
			resp->write(QString("ERROR: Sorry, this service is not yet implemented."));
			resp->end();
		}
		return true;
	}
	return false;
}

QNetworkReply::NetworkError DataUploadServerHandler::httpGetFile(QUrl file_location, QByteArray& data)
{
	std::string debug = file_location.toString().toStdString();
	int e=0;
	file_location = QUrl(QString::fromStdString(debug));
	QEventLoop eventLoop;
	QNetworkAccessManager nam(this);
	QObject::connect(&nam, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	QNetworkRequest request(file_location);
	//request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
	typedef UnipaxPtr<QNetworkReply>::type QNetworkReplyPtr;
	QNetworkReplyPtr reply(nam.get(request));

	eventLoop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		data = reply->readAll();
	}
	e = reply->error();
	return reply->error();
}

QNetworkReply::NetworkError DataUploadServerHandler::httpPostAccept(QByteArray& data, QHttpRequest *req)
{
	// TODO accept POST request data
	//req->data(data);
	if (data.size() == 0) std::cerr << "No data in POST request." << std::endl;
	return QNetworkReply::NoError;
}

boost::system::error_code DataUploadServerHandler::httpGetFile(QUrl file_location, std::stringstream& data)
{
	std::string host = file_location.host().toStdString();
	std::string path = file_location.path().toStdString();
	boost::system::error_code error = boost::asio::error::host_not_found;
	try
	{
		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(host, "http");
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		boost::asio::ip::tcp::resolver::iterator end;

		// Try each endpoint until we successfully establish a connection.
		boost::asio::ip::tcp::socket socket(io_service);
		while (error && endpoint_iterator != end)
		{
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if (error)
		{
			std::cerr << "DataUploadServerHandler::httpGetFile: Could not establish a socket connection." << std::endl;
			return error;
		}

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.
		boost::asio::streambuf request;
		std::ostream request_stream(&request);
		request_stream << "GET " << path << " HTTP/1.0\r\n";
		request_stream << "Host: " << host << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		// Send the request.
		boost::asio::write(socket, request);

		// Read the response status line.
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK.
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;

		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			std::cerr << "Invalid response\n" << std::endl;
		}
		if (status_code != 200)
		{
			std::cerr << "Response returned with HTTP status code " << status_code << std::endl;
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
			std::cout << header << "\n";
		std::cout << "\n";

		// Write whatever content we already have to output.
		if (response.size() > 0)
			data << &response;

		// Read until EOF, writing data to output as we go.
		boost::system::error_code read_error;
		while (boost::asio::read(socket, response,
				boost::asio::transfer_at_least(1), read_error))
		{
			data << &response;
		}
		if (read_error != boost::asio::error::eof)
			return read_error;
	}
	catch (boost::system::system_error &e)
	{
		std::cout << "boost::system::system_error: " << e.code().message() << "\n";
		return e.code();
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}
	return error;
}


Q_EXPORT_PLUGIN2(DataUploadServerHandler, DataUploadServerHandler)


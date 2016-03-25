#ifndef DATAUPLOADSERVERHANDLER_H_
#define DATAUPLOADSERVERHANDLER_H_

#include <UNIPAX/SERVER/REST/RESTServerHandler.h>
#include <UNIPAX/COMMON/DBConnector.h>

#include <UNIPAX/KERNEL/EXT/Series.h>

#include <QObject>
#include <QNetworkReply>

#include <boost/system/error_code.hpp>

class DataUploadServerHandler : public QObject, protected UniPAX::SERVER::RESTServerHandler
{
	Q_OBJECT
	Q_INTERFACES(UniPAX::SERVER::RESTServerHandler)

public:

	DataUploadServerHandler();

	~DataUploadServerHandler();

	QString help(QString format = "");

	void init(boost::program_options::variables_map & _vm);

	bool handle(QHttpRequest *req, QHttpResponse *resp);

	/**
	 * returns true if the data from file at <file_location> is successfully retrieved into <data>
	 */
	QNetworkReply::NetworkError httpGetFile(QUrl file_location, QByteArray& data);
	QNetworkReply::NetworkError httpPostAccept(QByteArray& data, QHttpRequest *req);
	boost::system::error_code httpGetFile(QUrl file_location, std::stringstream& data);

private:
	typedef QList<QByteArray>::const_iterator ConstIterator;

	QHttpRequest *m_request;
	QHttpResponse *m_response;
	static QRegExp upload_csv;
	UniPAX::DBConnectorPtr dbc;
	QByteArray error_line;
	int error_ln;

	void supplyUploadForm(QHttpRequest *req, QHttpResponse *resp);

	enum p_state { NAME, DESC, FORMAT, SUBSEP, DBNAME, CNROW, IDCOL, FDCOL, DATA, END, ERROR };
	bool parseSeparator(ConstIterator line);
	bool parseName(std::string & name, ConstIterator & line);
	bool parseDesc(std::map<std::string, std::string> & desc_tags, ConstIterator & line);
	bool parseFormat(std::string & format, ConstIterator & line);
	bool parseSubFieldSep(char & sub_sep, ConstIterator & line);
	bool parseDbName(std::string & db_name, ConstIterator & line);
	bool parseColNameRow(unsigned int & col, ConstIterator & line);
	bool parseIdCol(unsigned int & col, ConstIterator & line);
	bool parseFirstDataCol(unsigned int & col, ConstIterator & line);
	bool parseXsv(UniPAX::SeriesPtr & series, char sep, ConstIterator & line, const unsigned int id_col = 0, const unsigned int first_val_col = 1, const char sub_sep = ';');
	bool parseData(UniPAX::SeriesPtr & series, std::string format, ConstIterator & line, const unsigned int col_name_row, const unsigned int id_col, const unsigned int first_val_col, const char sub_sep);
	UniPAX::SeriesPtr parseSeriesData(bool & ok, QByteArray data);

	bool checkMiriam(UniPAX::SeriesPtr exp);

	void handlePostRequest(QHttpRequest *req, QHttpResponse *resp);
};

#endif /* DATAUPLOADSERVERHANDLER_H_ */

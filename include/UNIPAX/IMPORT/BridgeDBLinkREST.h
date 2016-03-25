#ifndef UNIPAX_BridgeDBLinkREST_H
#define UNIPAX_BridgeDBLinkREST_H

#include<UNIPAX/COMMON/common.h>

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<Qt/QtNetwork>
#include<Qt/QtXml>
#include<Qt/QtCore>
#include<boost/scoped_ptr.hpp>
#include<boost/shared_ptr.hpp>
//#include<boost/weak_ptr.hpp>
//#include "gtest/gtest_prod.h"


namespace UniPAX {


class UNIPAX_EXPORT BridgeDBLink : public QObject
{
private:

	static const char *STR_TRUE;
	static const char *STR_FALSE;
	static const char *defaultWsAddress;

public:
	BridgeDBLink();

	/**
	 * @brief constructs a BridgeDBLink to an alternative address (endpoint)
	 *
	 * @param endPoint adress of the BridgeDB web service
	 */
	BridgeDBLink(QUrl endPoint);

	/**
	 * @brief constructs a BridgeDBLink through a proxy server
	 *
	 * @param endPoint adress of the BridgeDB web service (may be empty)
	 *
	 * @param proxy_host address of the proxy server
	 *
	 * @param proxy_port port of the proxy server
	 */
	BridgeDBLink(std::string proxy_host, int proxy_port, QUrl endPoint = QUrl(defaultWsAddress));

	~BridgeDBLink();

	/**
	 * @brief returns the db symbol used in BridgeDB for the official db name.
	 */
	bool getDbSymbol(std::string & symbol, std::string official_name);

	/**
	 * @brief returns true if the content species could be retrieved.
	 *
	 * @param english_scientific_name returns the english and scientific names for all species contained in the webservice.
	 */
	bool contents(std::map<std::string, std::string> & english_scientific_name);

	/**
	 * @brief returns true if the properties for the given species could be retrieved.
	 */
	bool speciesProperties(std::map<std::string, std::string> & tag_value, const std::string species_name);

	/**
	 * @brief returns true if the source id systems for the given species could be retrieved.
	 */
	bool sourceDataSources(std::vector<std::string> & id_systems, const std::string species_name);

	/**
	 * @brief returns true if the target id systems for the given species could be retrieved.
	 */
	bool targetDataSources(std::vector<std::string> & id_systems, const std::string species_name);

	/**
	 * @brief returns true if the properties for the given species could be retrieved.
	 */
	bool isMappingSupported(bool & supported, const std::string species_name, const std::string source_idSystem, const std::string target_idSystem);

	/**
	 * @brief returns true if the status of the xref of source_idSystem for the given species could be retrieved.
	 */
	bool xrefExists(bool & exists, const std::string species_name, const std::string source_idSystem, const std::string xref);

	/**
	 * @brief returns true if the mapping from source_id of source_idSystem to target_idSystem or if not specified all other id systems was successful.
	 */
	bool mapXref(std::multimap<std::string, std::string> & id_idSystem, const std::string species_name, const std::string source_idSystem, const std::string source_id, const std::string target_idSystem = "");

	/**
	 * @brief returns true if the attribute(s) for the given species could be retrieved.
	 */
	bool attributes(std::multimap<std::string, std::string> & tag_value, const std::string species_name, const std::string source_idSystem, const std::string source_id, const std::string attribute_name = "");

	/**
	 * @brief returns true if the free search status for the given species could be retrieved.
	 */
	bool isFreeSearchSupported(bool & supported, const std::string species_name);

	/**
	 * @brief returns true if the free search for the given species succeeded.
	 */
	bool freeSearch(std::map<std::string, std::string> & tag_value, const std::string species_name, const std::string search_item, const unsigned int limit = 0);

	/**
	 * @brief sets the adress for the web service
	 */
	void setAddress(std::string host, int port = 80);

	/**
	 * @brief set the address (endpoint) for the web service.
	 *
	 * @param address the address (endpoint).
	 */
	void setEndpoint(QUrl address);

	/**
	 * @brief get the current address (endpoint) for the web service.
	 */
	const QUrl getEndpoint() const;

	/**
	 * @brief set the proxy for the web service.
	 *
	 * @param proxy_host the proxy address.
	 *
	 * @param proxy_port the proxy port.
	 */
	void setProxy(std::string _proxy_host, int _proxy_port);

	std::string getProxyHost() const;

	int getProxyPort() const;

	void setDebug(bool _debug);

private:

	bool request(const QUrl & request_url, QByteArray & data);
	void initMap();

	// private class members :
	bool debug;

	std::map<std::string, std::string> officialName_dbSymbol;
	boost::scoped_ptr< QNetworkAccessManager > network_manager;
	boost::scoped_ptr< QNetworkProxy > proxy;
	QUrl end_point;
	std::string proxy_host;
	int proxy_port;

}; // class end

} // namespace end
#endif

#ifndef MiriamLink_H
#define MiriamLink_H

#include<UNIPAX/COMMON/common.h>

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<Qt/QtNetwork>
#include<Qt/QtXml>
#include<Qt/QtCore>

#include<boost/shared_ptr.hpp>
//#include<boost/weak_ptr.hpp>
//#include "gtest/gtest_prod.h"


namespace UniPAX {

		static const std::string STR_TRUE = "true";
		static const std::string STR_FALSE = "false";
		static const std::string defaultWsAddress = "http://www.ebi.ac.uk/miriamws/main/MiriamWebServices"; // needs to be defined because of crappy gSOAP default address hard coding...

		class UNIPAX_EXPORT MiriamLink : public QObject
		{
						//Q_OBJECT

				public:
						MiriamLink();

						/**
						 * @brief constructs a MiriamLink to an alternative address (endpoint)
						 *
						 * @param endPoint adress of the MIRIAM web service
						 */
						MiriamLink(std::string endPoint);

						/**
						 * @brief constructs a MiriamLink through a proxy server
						 *
						 * @param endPoint adress of the MIRIAM web service (may be empty)
						 *
						 * @param proxy_host address of the proxy server
						 *
						 * @param proxy_port port of the proxy server
						 */
						MiriamLink(std::string proxy_host, int proxy_port, std::string endPoint = defaultWsAddress);

						MiriamLink(const MiriamLink & lhs);

						~MiriamLink();

						/**
						 * @brief returns true if the id matches the RegExp of the data type 
						 *
						 * @param identifier id used by the data type
						 *
						 * @param datatype name, synonym or MIRIAM URI of a data type 
						 *
						 * @return bool true if the identifier matches the RegExp of the data type and false else
						 */
						bool checkRegExp(std::string identifier, std::string datatype);

						/**
						 * @brief returns the address (endpoint) of the web service
						 *
						 * @return string containing the address (endpoint) of the web service
						 */
						//std::string getAddress();

						/**
						 * @brief Retrieves the physical locations (URLs) of web pages about the data-entry.
						 *
						 * @param uri a data-entry
						 *
						 * @return all physical locations (URLs)
						 */
						//std::vector<std::string> getDataEntries(std::string uri);

						/**
						 * @brief Retrieves the physical locations (URLs) of web pages about the data-entry.
						 *
						 * @param nickname name (can be a synonym) or URN or URL of a data type.
						 *
						 * @param id identifier of an element.
						 *
						 * @return all physical locations (URLs).
						 */
						//std::vector<std::string> getDataEntries(std::string nickname, std::string id);

						/**
						 * @brief Retrieves the physical location (URL) of a web page about the data-entry, using a specific resource.
						 *
						 * @param uri Miriam URI of an element.
						 *
						 * @param resource internal identifier of a resource.
						 *
						 * @return a physical location (URL).
						 */
						//std::string getDataEntry(std::string uri, std::string resource);

						/**
						 * @brief Retrieves all the physical locations (URLs) of the services providing the data type (web page). 
						 *
						 * @param nickname name (can be a synonym) or URL or URN of a data type name (or synonym) or URI (URL or URN).
						 *
						 * @return all physical locations (URLs).
						 */
						//std::vector<std::string> getDataResources(std::string nickname);

						/**
						 * @brief Retrieves all the URLs and URNs of the data type including all the deprecated ones.
						 *
						 * @param name name of the data type.
						 *
						 * @return all the URLs and URNs of the data type.
						 */
						//std::vector<std::string> getDataTypeAllURIs(std::string name);

						/**
						 * @brief Retrieves the definition of the data type.
						 *
						 * @param nickname name or URI (URN or URL) of a data type.
						 *
						 * @return definition of the data type.
						 */
						//std::string getDataTypeDef(std::string nickname);

						/**
						 * @brief Retrieves the pattern (regular expression) of the data type.
						 *
						 * @param nickname name or URI (URN or URL) of a data type.
						 *
						 * @return pattern of the data type.
						 */
						//std::string getDataTypePattern(std::string nickname);

						/**
						 * @brief Retrieves the list of identifiers (stable and perenial) of all the data types.
						 *
						 * @return identifiers of all the data types
						 */
						//std::vector<std::string> getDataTypesId();

						/**
						 * @brief Retrieves the list of names of all available data types. 
						 *
						 * @return list of names of all the data types.
						 */
						//std::vector<std::string> getDataTypesName();

						/**
						 * @brief Retrieves all synonym names of the data type, with the original name.
						 *
						 * @param name name or synonym of a data type.
						 *
						 * @return all synonym names of the data type.
						 */
						//std::vector<std::string> getDataTypeSynonyms(std::string name);

						/**
						 * @brief Retrieves the unique (official) URL or URN of the data type (example: "http://www.taxonomy.org/", "urn:lsid:uniprot.org"). 
						 *
						 * @param name name of the data type (examples: "ChEBI", "UniProt")
						 *
						 * @param type type of the URI the user wants to recover ('URN' or 'URL'), can be empty
						 *
						 * @return all physical locations (URLs)
						 */
						//std::string getDataTypeURI(std::string name, std::string type);

						/**
						 * @brief Retrieves all the URLs or URNs of the data type (examples: "http://www.taxonomy.org/", "urn:lsid:uniprot.org") including all the deprecated ones.
						 *
						 * @param type name of the data type (examples: "ChEBI", "UniProt").
						 */
						std::vector<std::string> getDataTypeURIs(std::string type);

						/**
						 * @brief Retrieves unique (official) URL (not a physical URL but a URI) of the data type (example: "http://www.taxonomy.org/").
						 *
						 * @param name name of a data type (examples: "ChEBI", "UniProt").
						 *
						 * @return unique (official) URL of the data type.
						 */
						//std::string getDataTypeURL(std::string name);

						/**
						 * @brief Retrieves the unique (official) URL (not a physical URL but a URI) of the data type (example: "http://www.taxonomy.org/") and all the deprecated ones.
						 *
						 * @param name name of a data type (examples: "ChEBI", "UniProt").
						 *
						 * @return unique URL of the data type and all the deprecated ones.
						 */
						//std::vector<std::string> getDataTypeURLs(std::string name);

						/**
						 * @brief Retrieves the unique URN of a data type (example: "urn:lsid:uniprot.org").
						 *
						 * @param name primary name (or synonym) of a data type (examples: "ChEBI", "UniProt", "GO").
						 *
						 * @return unique URN of a data type.
						 */
						//std::string getDataTypeURN(std::string name);

						/**
						 * @brief Retrieves the unique (official) URN of the data type (example: "urn:lsid:uniprot.org") and all the deprecated ones.
						 *
						 * @param name primary name (or synonym) of a data type (examples: "ChEBI", "UniProt", "GO").
						 *
						 * @return unique (official) URN of the data type and all the deprecated ones.
						 */
						//std::vector<std::string> getDataTypeURNs(std::string name);

						/**
						 * @brief Retrieves the common name of a data type.
						 *
						 * @param uri URI (URL or URN) of a data type.
						 *
						 * @return common name of a data type.
						 */
						std::string getName(std::string uri);

						/**
						 * @brief Retrieves all the names (with synonyms) of a data type.
						 *
						 * @param uri uri - URI (URL or URN) of a data type.
						 *
						 * @return common name of the data type and all the synonyms.
						 */
						//std::vector<std::string> getNames(std::string uri);

						/**
						 * @brief Retrieves the offical URI (URN if the user entered a URN, URL if not) corresponding to the deprecated one.
						 *
						 * @param uri deprecated URI (URN or URL) of a data type.
						 *
						 * @return offical URI corresponding to the deprecated one.
						 */
						std::string getOfficialURI(std::string uri);

						/**
						 * @brief Retrieves information about a resource.
						 *
						 * @param id identifier of a resource (example: "MIR:00100009").
						 *
						 * @return information about a resource.
						 */
						//std::string getResourceInfo(std::string id);

						/**
						 * @brief Retrieves the institution managing a resource (example: "European Bioinformatics Institute").
						 *
						 * @param id identifier of a resource (example: "MIR:00100009").
						 *
						 * @return institution managing resource.
						 */
						//std::string getResourceInstitution(std::string id);

						/**
						 * @brief Retrieves the location (or country) of a resource (example: "United Kingdom").
						 *
						 * @param id identifier of a resource (example: "MIR:00100009").
						 *
						 * @return location (or country) of a resource.
						 */
						//std::string getResourceLocation(std::string id);

						/**
						 * @brief Retrieves the unique URI (URL or URN) of the data-entry (example: "http://www.geneontology.org/#GO:0045202", "urn:lsid:uniprot.org").
						 *
						 * @param name name of a data type (examples: "ChEBI", "UniProt").
						 *
						 * @param id identifier of an element (examples: "GO:0045202", "P62158").
						 *
						 * @param type type of the URI the user wants to recover ('URN' or 'URL').
						 *
						 * @return unique URI (URL or URN) of the data-entry.
						 */
						//std::string getURI(std::string name, std::string id, std::string type);

						/**
						 * @brief Retrieves unique URN of the data-entry (example: "http://www.geneontology.org/#GO:0045202").
						 *
						 * @param name name of a data type (examples: "ChEBI", "UniProt").
						 *
						 * @param id identifier of an element (examples: "GO:0045202", "P62158").
						 *
						 * @return unique URN of the data-entry.
						 */
						//std::string getURL(std::string name, std::string id);

						/**
						 * @brief Retrieves unique URN of the data-entry (example: "http://www.geneontology.org/#GO:0045202").
						 *
						 * @param name name of a data type (examples: "ChEBI", "UniProt").
						 *
						 * @param id identifier of an element (examples: "GO:0045202", "P62158").
						 *
						 * @return unique URN of the data-entry.
						 */
						//std::string getURN(std::string name, std::string id);

						/**
						 * @brief checks if the data-entry is marked as deprecated.
						 *
						 * @param uri a data-entry.
						 *
						 * @return true if uri is deprecated.
						 */
						//bool isDeprecated(std::string uri);

						/**
						 * @brief set the address (endpoint) for the web service.
						 *
						 * @param address the address (endpoint).
						 */
						void setAddress(std::string address);

						/**
						 * @brief set the proxy for the web service.
						 *
						 * @param proxy_host the proxy address.
						 *
						 * @param proxy_port the proxy port.
						 */
						void setProxy(std::string _proxy_host, int _proxy_port);

						std::string getProxyName();

						int getProxyPort();

						void setDebug(bool _debug);
				private:

						bool request(const QUrl & request_url, boost::shared_ptr<QDomDocument> & reply);

						bool initDataTypes();

						// private class members :
						bool initialized;
						bool debug;

						boost::shared_ptr< std::map<std::string, std::string> > dataTypesId; // <all_type_names, id>
						boost::shared_ptr< std::map<std::string, std::string> > id_dataTypesName; // <id, type_name>
						boost::shared_ptr< std::map<std::string, std::string> > uris_id; // <all_uris, id>
						boost::shared_ptr< std::map<std::string, std::string> > id_uri; // <id, official_uri>
						boost::shared_ptr< QNetworkAccessManager > network_manager;
						boost::shared_ptr< QNetworkProxy > proxy;
						std::string end_point;
						std::string proxy_host;
						int proxy_port;

		}; // class end

} // namespace end
#endif


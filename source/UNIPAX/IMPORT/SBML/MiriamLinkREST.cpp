#include<UNIPAX/IMPORT/SBML/MiriamLinkREST.h>
//#include<moc_MiriamLinkREST.h>

UniPAX::MiriamLink::MiriamLink() :
		initialized(0),
		debug(0),
		dataTypesId(new std::map<std::string, std::string>()),
		id_dataTypesName(new std::map<std::string, std::string>()),
		uris_id(new std::map<std::string, std::string>()),
		id_uri(new std::map<std::string, std::string>()),
		network_manager(new QNetworkAccessManager(this)),
		proxy(new QNetworkProxy()),
		proxy_port(0)
{
}

UniPAX::MiriamLink::MiriamLink(const std::string endPoint) :
		initialized(0),
		debug(0),
		dataTypesId(new std::map<std::string, std::string>()),
		id_dataTypesName(new std::map<std::string, std::string>()),
		uris_id(new std::map<std::string, std::string>()),
		id_uri(new std::map<std::string, std::string>()),
		network_manager(new QNetworkAccessManager(this)),
		proxy(new QNetworkProxy()),
		end_point(endPoint),
		proxy_port(0)
{
}

UniPAX::MiriamLink::MiriamLink(const std::string proxy_host, int proxy_port, const std::string endPoint) :
		initialized(0),
		debug(0),
		dataTypesId(new std::map<std::string, std::string>()),
		id_dataTypesName(new std::map<std::string, std::string>()),
		uris_id(new std::map<std::string, std::string>()),
		id_uri(new std::map<std::string, std::string>()),
		network_manager(new QNetworkAccessManager(this)),
		proxy(new QNetworkProxy(QNetworkProxy::HttpProxy, QString::fromStdString(proxy_host), proxy_port)),
		end_point(endPoint),
		proxy_host(proxy_host),
		proxy_port(proxy_port)
{
		network_manager->setProxy(*proxy);
}

UniPAX::MiriamLink::MiriamLink(const UniPAX::MiriamLink & lhs) :
		initialized(lhs.initialized),
		debug(lhs.debug),
		dataTypesId(lhs.dataTypesId),
		id_dataTypesName(lhs.id_dataTypesName),
		uris_id(lhs.uris_id),
		id_uri(lhs.id_uri),
		network_manager(lhs.network_manager),
		proxy(lhs.proxy),
		end_point(lhs.end_point),
		proxy_host(lhs.proxy_host),
		proxy_port(lhs.proxy_port)
{
}

UniPAX::MiriamLink::~MiriamLink()
{
}

bool UniPAX::MiriamLink::request(const QUrl & request_url, boost::shared_ptr<QDomDocument> & doc)
{

		QNetworkRequest request;
		if (debug) std::cout << "Request URL: " << request_url.toString().toStdString() << std::endl;
		request.setUrl(request_url);
		if (proxy_host.empty())
		{
			network_manager->setProxy(QNetworkProxy(QNetworkProxy::NoProxy));
		}
		else
		{
			network_manager->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy, QString::fromStdString(proxy_host), proxy_port));
		}
		boost::shared_ptr<QNetworkReply> reply(network_manager->get(request));
		QEventLoop eLoop;
		connect(network_manager.get(), SIGNAL(finished(QNetworkReply *)), &eLoop, SLOT(quit()) );
		eLoop.exec( QEventLoop::ExcludeUserInputEvents );
		if (reply == 0)
				std::cerr << "Reply is null-pointer." << std::endl;
		if (reply->error() != QNetworkReply::NoError)
		{
				std::cerr << reply->errorString().toStdString() << std::endl;
				return false;
		}
		if (!doc.get()->setContent(reply.get()))
		{
				std::cerr << "Cannot set network reply as content for xml doc." << std::endl;
				return false;
		}
		return true;
}

bool UniPAX::MiriamLink::initDataTypes()
{
		std::cout << "Initializing MIRIAM link..." << std::endl;
		boost::shared_ptr<QDomDocument> doc(new QDomDocument());
		if (!request(QUrl(QString::fromStdString("http://www.ebi.ac.uk/miriamws/main/rest/datatypes")), doc))
		{
				return false;
		}
		QDomElement root = doc->documentElement();
		if (debug) std::cout << "root element: " << root.tagName().toStdString() << std::endl;
		for (QDomElement elt = root.firstChildElement("datatype"); !elt.isNull(); elt = elt.nextSiblingElement("datatype"))
		{
				QDomElement id = elt.firstChildElement("id");
				QDomElement name = elt.firstChildElement("name");
				if (debug) std::cout << "id: " << id.text().toStdString() << " name: " << name.text().toStdString() << std::endl;
				dataTypesId->insert(std::pair<std::string, std::string>(name.text().toStdString(), id.text().toStdString()));
				id_dataTypesName->insert(std::pair<std::string, std::string>(id.text().toStdString(),name.text().toStdString()));
		}
		std::vector<std::pair<std::string, std::string> > synonyms;
		for (std::map<std::string, std::string>::const_iterator dit = dataTypesId->begin(); dit != dataTypesId->end(); dit++)
		{
				if(!request(QUrl(QString::fromStdString("http://www.ebi.ac.uk/miriamws/main/rest/datatypes/" + dit->second)), doc))
				{
						return false;
				}
				if (debug) std::cout << "Data type request successful." << std::endl;
				// find all synonyms
				QDomElement uris = doc->documentElement().firstChildElement("synonyms");
				for (QDomElement elt = uris.firstChildElement("synonym"); !elt.isNull(); elt = elt.nextSiblingElement("synonym"))
				{
						synonyms.push_back(std::pair<std::string, std::string>(elt.text().toStdString(), dit->second));
				}
				// find all uris
				uris = doc->documentElement().firstChildElement("uris");
				for (QDomElement elt = uris.firstChildElement("uri"); !elt.isNull(); elt = elt.nextSiblingElement("uri"))
				{
						uris_id->insert(std::pair<std::string, std::string>(elt.text().toStdString(), dit->second));
						if (!elt.hasAttribute("deprecated"))
						{
								id_uri->insert(std::pair<std::string, std::string>(dit->second, elt.text().toStdString()));
						}
				}

		}
		for (std::vector<std::pair<std::string, std::string> >::const_iterator sit = synonyms.begin(); sit !=synonyms.end(); sit++)
		{
				dataTypesId->insert(*sit);
		}
		initialized = true;
		std::cout << "Success!" << std::endl;
		return true;
}

bool UniPAX::MiriamLink::checkRegExp(std::string identifier, std::string datatype)
{
		if (!initialized && !initDataTypes())
		{
				std::cerr << "MIRIAM REST client not initialized." << std::endl;
				return false;
		}
		if (debug) std::cout << "call to checkRegExp(identifier=" << identifier << ", datatype=  " << datatype << ")" << std::endl;
		std::string data_id;
		if (dataTypesId->find(datatype) != dataTypesId->end())
		{
				dataTypesId->insert(std::pair<std::string, std::string>(data_id, datatype));
		}
		else
		{
				data_id = datatype;
		}
		if (debug) std::cout << "data_id = " << data_id  << std::endl;
		boost::shared_ptr<QDomDocument> doc(new QDomDocument());
		if(!request(QUrl(QString::fromStdString("http://www.ebi.ac.uk/miriamws/main/rest/datatypes/" + data_id)), doc))
		{
				return false;
		}
		if (debug) std::cout << "Data type request successful." << std::endl;
		QDomElement root = doc->firstChildElement("datatype");
		QString pattern;
		if (root.hasAttribute("pattern"))
				pattern = root.attribute("pattern");
		else
		{
				std::cerr << "No attribute 'pattern'." << std::endl;
				return false;
		}
		if (debug) std::cout << "Pattern: " << pattern.toStdString() << "\nIdentifier: " << identifier << std::endl;
		QRegExp regExp(pattern);
		return regExp.exactMatch(QString::fromStdString(identifier));
}

/*std::string UniPAX::MiriamLink::getAddress()
  {
  initSoapObj();
  if (miriamWS->soap_endpoint)
  {
  return miriamWS->soap_endpoint;
  }
  else
  {
  return defaultWsAddress;
  }
  }

  std::vector<std::string> UniPAX::MiriamLink::getDataEntries(std::string uri)
  {
  initSoapObj();
  std::vector<std::string> entries = std::vector<std::string>();
  ns2__getLocationsResponse_ answers;
  if (miriamWS->getLocations_(uri, answers) == SOAP_OK)
  {
  for (int i=0; i < answers._getLocationsReturn->__size; i++)
  {
  entries.push_back(answers._getLocationsReturn->__ptr[i]);
  }
  return entries;
  }
  else
  {
  miriamWS->soap_stream_fault(std::cerr);
  return entries;
  }
  }

  std::vector<std::string> UniPAX::MiriamLink::getDataEntries(std::string nickname, std::string id)
  {
  initSoapObj();
  std::vector<std::string> entries = std::vector<std::string>();
  ns2__getLocationsResponse answers;
  if (miriamWS->getLocations(nickname, id, answers) == SOAP_OK)
  {
  for (int i=0; i < answers._getLocationsReturn->__size; i++)
  {
  entries.push_back(answers._getLocationsReturn->__ptr[i]);
  }
  return entries;
  }
  else
  {
  miriamWS->soap_stream_fault(std::cerr);
  return entries;
  }
  }

  std::string	UniPAX::MiriamLink::getDataEntry(std::string uri, std::string resource)
  {
  initSoapObj();
  std::string answer;
  if (miriamWS->getDataEntry(uri, resource, answer) == SOAP_OK)
  {
  return answer;
  }
  else
  {
  miriamWS->soap_stream_fault(std::cerr);
  return answer;
  }
  }


  std::vector<std::string> UniPAX::MiriamLink::getDataResources(std::string nickname)
  {
initSoapObj();
std::vector<std::string> entries = std::vector<std::string>();
ns2__getDataResourcesResponse answers;
if (miriamWS->getDataResources(nickname, answers) == SOAP_OK)
{
		for (int i=0; i < answers._getDataResourcesReturn->__size; i++)
		{
				entries.push_back(answers._getDataResourcesReturn->__ptr[i]);
		}
		return entries;
}
else
{
		miriamWS->soap_stream_fault(std::cerr);
		return entries;
}
}

std::vector<std::string> UniPAX::MiriamLink::getDataTypeAllURIs(std::string name)
{
		initSoapObj();
		std::vector<std::string> entries = std::vector<std::string>();
		ns2__getDataTypeAllURIsResponse answers;
		if (miriamWS->getDataTypeAllURIs(name, answers) == SOAP_OK)
		{
				for (int i=0; i < answers._getDataTypeAllURIsReturn->__size; i++)
				{
						entries.push_back(answers._getDataTypeAllURIsReturn->__ptr[i]);
				}
				return entries;
		}
		else
		{
				miriamWS->soap_stream_fault(std::cerr);
				return entries;
		}
}

std::string UniPAX::MiriamLink::getDataTypeDef(std::string nickname)
{
		initSoapObj();
		std::string answer;
		if (miriamWS->getDataTypeDef(nickname, answer) == SOAP_OK)
		{
				return answer;
		}
		else
		{
				miriamWS->soap_stream_fault(std::cerr);
				return answer;
		}
}

std::string UniPAX::MiriamLink::getDataTypePattern(std::string nickname)
{
		initSoapObj();
		std::string answer;
		if (miriamWS->getDataTypePattern(nickname, answer) == SOAP_OK)
		{
				return answer;
		}
		else
		{
				miriamWS->soap_stream_fault(std::cerr);
				return answer;
		}
}

std::vector<std::string> UniPAX::MiriamLink::getDataTypesId()
{
		initSoapObj();
		std::vector<std::string> entries = std::vector<std::string>();
		ns2__getDataTypesIdResponse answers;
		if (miriamWS->getDataTypesId(answers) == SOAP_OK)
		{
				for (int i=0; i < answers.getDataTypesIdReturn->__size; i++)
				{
						entries.push_back(answers.getDataTypesIdReturn->__ptr[i]);
				}
				return entries;
		}
		else
		{
				miriamWS->soap_stream_fault(std::cerr);
				return entries;
		}
}

std::vector<std::string> UniPAX::MiriamLink::getDataTypesName()
{
		initSoapObj();
		std::vector<std::string> entries = std::vector<std::string>();
		ns2__getDataTypesNameResponse answers;
		if (miriamWS->getDataTypesName(answers) == SOAP_OK)
		{
				for (int i=0; i < answers.getDataTypesNameReturn->__size; i++)
				{
						entries.push_back(answers.getDataTypesNameReturn->__ptr[i]);
				}
				return entries;
		}
		else
		{
				miriamWS->soap_stream_fault(std::cerr);
				//std::cerr << miriamWS->soap_socket_errno << std:::endl;
				return entries;
		}
}

std::vector<std::string> UniPAX::MiriamLink::getDataTypeSynonyms(std::string name)
{
		initSoapObj();
		std::vector<std::string> entries = std::vector<std::string>();
		ns2__getDataTypeSynonymsResponse answers;
		if (miriamWS->getDataTypeSynonyms(name, answers) == SOAP_OK)
		{
				for (int i=0; i < answers._getDataTypeSynonymsReturn->__size; i++)
				{
						entries.push_back(answers._getDataTypeSynonymsReturn->__ptr[i]);
				}
				return entries;
		}
		else
		{
				miriamWS->soap_stream_fault(std::cerr);
				return entries;
		}
}

std::string UniPAX::MiriamLink::getDataTypeURI(std::string name, std::string type)
{
		initSoapObj();
		std::string answer;
		if (miriamWS->getDataTypeURI(name, type, answer) == SOAP_OK)
		{
				return answer;
		}
		else
		{
				miriamWS->soap_stream_fault(std::cerr);
				return answer;
		}
}*/

std::vector<std::string> UniPAX::MiriamLink::getDataTypeURIs(std::string type)
{
		std::vector<std::string> entries = std::vector<std::string>();
		if (!initialized && !initDataTypes())
		{
				std::cerr << "MIRIAM REST client not initialized." << std::endl;
				return entries;
		}

		std::string data_id;
		if (dataTypesId->find(type) != dataTypesId->end())
		{
				data_id = dataTypesId->find(type)->second;
		}
		else
		{
				data_id = type;
		}
		if (debug) std::cout << "data_id = " << data_id  << std::endl;
		boost::shared_ptr<QDomDocument> doc(new QDomDocument());
		if(!request(QUrl(QString::fromStdString("http://www.ebi.ac.uk/miriamws/main/rest/datatypes/" + data_id)), doc))
		{
				std::cerr << "Could not retrieve datatype for " << data_id << " from webservice." << std::endl;
				return entries;
		}
		if (debug) std::cout << "Data type request successful." << std::endl;
		QDomElement uris = doc->documentElement().firstChildElement("uris");

		for (QDomElement elt = uris.firstChildElement("uri"); !elt.isNull(); elt = elt.nextSiblingElement("uri"))
		{
				entries.push_back(elt.text().toStdString());
		}
		return entries;
}
/*
   std::string UniPAX::MiriamLink::getDataTypeURL(std::string name)
   {
   initSoapObj();
   std::string answer;
   if (miriamWS->getDataTypeURL(name, answer) == SOAP_OK)
   {
   return answer;
   }
   else
   {
   miriamWS->soap_stream_fault(std::cerr);
   return answer;
   }
   }


   std::vector<std::string> UniPAX::MiriamLink::getDataTypeURLs(std::string name)
   {
   initSoapObj();
   std::vector<std::string> entries = std::vector<std::string>();
   ns2__getDataTypeURLsResponse answers;
   if (miriamWS->getDataTypeURLs(name, answers) == SOAP_OK)
   {
   for (int i=0; i < answers._getDataTypeURLsReturn->__size; i++)
   {
   entries.push_back(answers._getDataTypeURLsReturn->__ptr[i]);
   }
   return entries;
   }
   else
   {
   miriamWS->soap_stream_fault(std::cerr);
   return entries;
   }
   }

   std::string UniPAX::MiriamLink::getDataTypeURN(std::string name)
   {
   initSoapObj();
   std::string answer;
   if (miriamWS->getDataTypeURN(name, answer) == SOAP_OK)
   {
   return answer;
   }
   else
   {
   miriamWS->soap_stream_fault(std::cerr);
   return answer;
   }
   }

   std::vector<std::string> UniPAX::MiriamLink::getDataTypeURNs(std::string name)
   {
   initSoapObj();
   std::vector<std::string> entries = std::vector<std::string>();
   ns2__getDataTypeURNsResponse answers;
   if (miriamWS->getDataTypeURNs(name, answers) == SOAP_OK)
   {
   for (int i=0; i < answers._getDataTypeURNsReturn->__size; i++)
   {
   entries.push_back(answers._getDataTypeURNsReturn->__ptr[i]);
   }
   return entries;
   }
   else
   {
   miriamWS->soap_stream_fault(std::cerr);
   return entries;
   }
   }*/

std::string UniPAX::MiriamLink::getName(std::string uri)
{
		if (!initialized && !initDataTypes())
		{
				std::cerr << "MIRIAM REST client not initialized." << std::endl;
				return "";
		}
		std::map<std::string, std::string>::const_iterator id = uris_id->find(uri);
		if (id == uris_id->end())
		{
				std::cerr << "URI " << uri << " not known by webservice." << std::endl;
				return "";
		}
		else 
		{
				return id_dataTypesName->find(id->second)->second;
		}
}
/*
   std::vector<std::string> UniPAX::MiriamLink::getNames(std::string uri)
   {
   initSoapObj();
   std::vector<std::string> entries = std::vector<std::string>();
   ns2__getNamesResponse answers;
   if (miriamWS->getNames(uri, answers) == SOAP_OK)
   {
   for (int i=0; i < answers._getNamesReturn->__size; i++)
   {
   entries.push_back(answers._getNamesReturn->__ptr[i]);
   }
   return entries;
   }
   else
   {
   miriamWS->soap_stream_fault(std::cerr);
   return entries;
   }
   }*/

std::string UniPAX::MiriamLink::getOfficialURI(std::string uri)
{
		if (!initialized && !initDataTypes())
		{
				std::cerr << "MIRIAM REST client not initialized." << std::endl;
				return "";
		}
		std::map<std::string, std::string>::const_iterator id = uris_id->find(uri);
		if (id == uris_id->end())
		{
				std::cerr << "URI " << uri << " not known by webservice." << std::endl;
				return "";
		}
		else 
		{
				return id_uri->find(id->second)->second;
		}

}

/*
   std::string UniPAX::MiriamLink::getResourceInfo(std::string id)
   {
   initSoapObj();
   std::string answer;
   if (miriamWS->getResourceInfo(id, answer) == SOAP_OK)
   {
   return answer;
   }
   else
   {
   miriamWS->soap_stream_fault(std::cerr);
   return answer;
   }
   }

   std::string UniPAX::MiriamLink::getResourceInstitution(std::string id)
   {
   initSoapObj();
   std::string answer;
   if (miriamWS->getResourceInstitution(id, answer) == SOAP_OK)
   {
   return answer;
   }
   else
   {
   miriamWS->soap_stream_fault(std::cerr);
   return answer;
   }
   }

   std::string UniPAX::MiriamLink::getResourceLocation(std::string id)
   {
   initSoapObj();
   std::string answer;
   if (miriamWS->getResourceLocation(id, answer) == SOAP_OK)
   {
   return answer;
   }
   else
   {
   miriamWS->soap_stream_fault(std::cerr);
   return answer;
   }
   }

   std::string UniPAX::MiriamLink::getURI(std::string name, std::string id, std::string type)
   {
   initSoapObj();
   std::string answer;
   if (miriamWS->getURI(name, id, type, answer) == SOAP_OK)
   {
   return answer;
   }
   else
   {
   miriamWS->soap_stream_fault(std::cerr);
   return answer;
   }
   }

   std::string UniPAX::MiriamLink::getURL(std::string name, std::string id)
   {
   initSoapObj();
   std::string answer;
   if (miriamWS->getURL(name, id, answer) == SOAP_OK)
   {
   return answer;
   }
   else
   {
miriamWS->soap_stream_fault(std::cerr);
return answer;
}
}

std::string UniPAX::MiriamLink::getURN(std::string name, std::string id)
{
		std::string answer;
		if (miriamWS->getURN(name, id, answer) == SOAP_OK)
		{
				return answer;
		}
		else
		{
				miriamWS->soap_stream_fault(std::cerr);
				return answer;
		}
}

bool UniPAX::MiriamLink::isDeprecated(std::string uri)
{
		initSoapObj();
		std::string isDeprecatedReturn;
		if(miriamWS->isDeprecated(uri, isDeprecatedReturn) == SOAP_OK)
				if (isDeprecatedReturn.compare(STR_TRUE) == 0)
				{
						return true;
				}
				else if (isDeprecatedReturn.compare(STR_FALSE) == 0)
				{
						return false;
				}
				else
				{
						std::cerr << "Unknown return value from SOAP service method 'checkRegExp': " << isDeprecatedReturn << std::endl;
						return false;
				}
		else
		{
				miriamWS->soap_stream_fault(std::cerr);
				return false;
		}
}*/

void UniPAX::MiriamLink::setAddress(std::string address)
{
		end_point = address;
}

void UniPAX::MiriamLink::setProxy(std::string _proxy_host = "", int _proxy_port = 0)
{
		proxy_host = _proxy_host;
		proxy_port = _proxy_port;
		if (_proxy_host.empty() && _proxy_port == 0)
		{
			proxy.reset(new QNetworkProxy(QNetworkProxy::NoProxy, QString::fromStdString(proxy_host), proxy_port));
		}
		else
		{
			proxy.reset(new QNetworkProxy(QNetworkProxy::HttpProxy, QString::fromStdString(proxy_host), proxy_port));
		}
		network_manager->setProxy(*proxy.get());
		//network_manager->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy, QString::fromStdString(proxy_host), proxy_port));
}

std::string UniPAX::MiriamLink::getProxyName()
{
		return proxy_host;
}

int UniPAX::MiriamLink::getProxyPort()
{
		return proxy_port;
}

void UniPAX::MiriamLink::setDebug(bool _debug)
{
		debug = _debug;
}

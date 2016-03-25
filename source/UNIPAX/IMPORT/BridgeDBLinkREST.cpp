#include<UNIPAX/IMPORT/BridgeDBLinkREST.h>

const char *UniPAX::BridgeDBLink::STR_TRUE = "true";
const char *UniPAX::BridgeDBLink::STR_FALSE = "false";
const char *UniPAX::BridgeDBLink::defaultWsAddress = "http://http://webservice.bridgedb.org";

UniPAX::BridgeDBLink::BridgeDBLink() :
//initialized(0),
debug(0),
network_manager(new QNetworkAccessManager(this)),
proxy(new QNetworkProxy()),
proxy_port(0),
end_point(QString(UniPAX::BridgeDBLink::defaultWsAddress))
{
}

UniPAX::BridgeDBLink::BridgeDBLink(const QUrl endPoint) :
						//initialized(0),
						debug(0),
						network_manager(new QNetworkAccessManager(this)),
						proxy(new QNetworkProxy()),
						end_point(endPoint),
						proxy_port(0)
{
}

UniPAX::BridgeDBLink::BridgeDBLink(const std::string proxy_host, const int proxy_port, const QUrl endPoint) :
						//initialized(0),
						debug(0),
						network_manager(new QNetworkAccessManager(this)),
						proxy(new QNetworkProxy(QNetworkProxy::HttpProxy, QString::fromStdString(proxy_host), proxy_port)),
						end_point(endPoint),
						proxy_host(proxy_host),
						proxy_port(proxy_port)
{
	network_manager->setProxy(*proxy);
}

UniPAX::BridgeDBLink::~BridgeDBLink()
{
}

bool UniPAX::BridgeDBLink::getDbSymbol(std::string & symbol, std::string official_name)
{
	if (officialName_dbSymbol.empty())
	{
		initMap();
	}
	std::map<std::string, std::string>::iterator it = officialName_dbSymbol.find(official_name);
	if (it != officialName_dbSymbol.end())
	{
		symbol = it->second;
		return true;
	}
	return false;
}

bool UniPAX::BridgeDBLink::request(const QUrl & request_url, QByteArray & data)
{
	if (request_url.isRelative())
	{
		std::cerr << "BridgeDBLink::request: Warning! Relative URL used for request." << std::endl;
	}
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

	//network_manager->setProxy(QNetworkProxy(QNetworkProxy::HttpProxy, QString::fromStdString(proxy_host), proxy_port));
	boost::scoped_ptr<QNetworkReply> reply(network_manager->get(request));
	QEventLoop eLoop;
	connect(network_manager.get(), SIGNAL(finished(QNetworkReply *)), &eLoop, SLOT(quit()) );
	eLoop.exec( QEventLoop::ExcludeUserInputEvents );
	if (reply == 0)
	{
		std::cerr << "Reply is null-pointer." << std::endl;
		return false;
	}
	if (reply->error() != QNetworkReply::NoError)
	{
		std::cerr << reply->errorString().toStdString() << std::endl;
		return false;
	}
	data = reply->readAll();
	return true;
}

bool UniPAX::BridgeDBLink::contents(std::map<std::string, std::string> & english_scientific_name)
{
	QUrl url(end_point);
	QByteArray species_names;
	url.setPath(QString("contents"));
	if (!request(url, species_names))
	{
		return false;
	}
	english_scientific_name.clear();
	QList<QByteArray> lines = species_names.split('\n');
	for (QList<QByteArray>::iterator line = lines.begin(); line != lines.end(); ++line)
	{
		QList<QByteArray> token = line->split('\t');
		if (token.size() != 2)
		{
			return false;
		}
		english_scientific_name.insert(std::pair<std::string, std::string>(QString(token.at(0)).toStdString(), QString(token.at(1)).toStdString()));
	}
	return true;
}

bool UniPAX::BridgeDBLink::speciesProperties(std::map<std::string, std::string> & tag_value, const std::string species_name)
{
	QUrl url(end_point);
	QByteArray tags;
	url.setPath(QString::fromStdString(species_name).append("/properties"));
	if (!request(url, tags))
	{
		return false;
	}
	tag_value.clear();
	QList<QByteArray> lines = tags.split('\n');
	for (QList<QByteArray>::iterator line = lines.begin(); line != lines.end(); ++line)
	{
		QList<QByteArray> token = line->split('\t');
		if (token.size() != 2)
		{
			return false;
		}
		tag_value.insert(std::pair<std::string, std::string>(QString(token.at(0)).toStdString(), QString(token.at(1)).toStdString()));
	}
	return true;
}

bool UniPAX::BridgeDBLink::sourceDataSources(std::vector<std::string> & id_systems, const std::string species_name)
{
	QUrl url(end_point);
	QByteArray tags;
	url.setPath(QString::fromStdString(species_name).append("/sourceDataSources"));
	if (!request(url, tags))
	{
		return false;
	}
	id_systems.clear();
	QList<QByteArray> lines = tags.split('\n');
	for (QList<QByteArray>::iterator line = lines.begin(); line != lines.end(); ++line)
	{
		id_systems.push_back(QString(*line).toStdString());
	}
	return true;
}

bool UniPAX::BridgeDBLink::targetDataSources(std::vector<std::string> & id_systems, const std::string species_name)
{
	QUrl url(end_point);
	QByteArray tags;
	url.setPath(QString::fromStdString(species_name).append("/targetDataSources"));
	if (!request(url, tags))
	{
		return false;
	}
	id_systems.clear();
	QList<QByteArray> lines = tags.split('\n');
	for (QList<QByteArray>::iterator line = lines.begin(); line != lines.end(); ++line)
	{
		id_systems.push_back(QString(*line).toStdString());
	}
	return true;
}

bool UniPAX::BridgeDBLink::isMappingSupported(bool & ok, const std::string species_name, const std::string source_idSystem, const std::string target_idSystem)
{
	QUrl url(end_point);
	QByteArray answer;
	url.setPath(QString::fromStdString(species_name).append("/isMappingSupported/").append(source_idSystem.c_str()).append("/").append(target_idSystem.c_str()));
	if (!request(url, answer))
	{
		return false;
	}
	if (QString(answer) == STR_TRUE)
	{
		ok = true;
	}
	else
	{
		ok = false;
	}
	return true;
}

bool UniPAX::BridgeDBLink::xrefExists(bool & ok,const std::string species_name, const std::string source_idSystem, const std::string xref)
{
	QUrl url(end_point);
	QByteArray answer;
	url.setPath(QString::fromStdString(species_name).append("/xrefExists/").append(source_idSystem.c_str()).append("/").append(xref.c_str()));
	if (!request(url, answer))
	{
		return false;
	}
	if (QString(answer) == STR_TRUE)
	{
		ok = true;
	}
	else
	{
		ok = false;
	}
	return true;
}

bool UniPAX::BridgeDBLink::mapXref(std::multimap<std::string, std::string> & id_idSystem, const std::string species_name, const std::string source_idSystem, const std::string source_id, const std::string target_idSystem)
{
	QUrl url(end_point);
	QByteArray answer;
	url.setPath(QString::fromStdString(species_name).append("/xrefs/").append(source_idSystem.c_str()).append("/").append(source_id.c_str()));
	if (!target_idSystem.empty())
		{
			url.addQueryItem(QString("dataSource"), QString::fromStdString(target_idSystem));
		}
	if (!request(url, answer))
	{
		return false;
	}
	id_idSystem.clear();
	QList<QByteArray> lines = answer.split('\n');
	for (QList<QByteArray>::iterator line = lines.begin(); line != lines.end(); ++line)
	{
		QList<QByteArray> token = line->split('\t');
		if (token.size() != 2)
		{
			return false;
		}
		id_idSystem.insert(std::pair<std::string, std::string>(QString(token.at(0)).toStdString(), QString(token.at(1)).toStdString()));
	}
	return true;
}

bool UniPAX::BridgeDBLink::attributes(std::multimap<std::string, std::string> & tag_value, const std::string species_name , const std::string source_idSystem, const std::string xref, const std::string attribute_name)
{
	QUrl url(end_point);
	QByteArray answer;
	url.setPath(QString::fromStdString(species_name).append("/attributes/").append(source_idSystem.c_str()).append("/").append(xref.c_str()));
	if (!attribute_name.empty())
		{
			url.addQueryItem(QString("attrName"), QString::fromStdString(attribute_name));
		}
	if (!request(url, answer))
	{
		return false;
	}
	tag_value.clear();
	QList<QByteArray> lines = answer.split('\n');
	for (QList<QByteArray>::iterator line = lines.begin(); line != lines.end(); ++line)
	{
		QList<QByteArray> token = line->split('\t');
		if (token.size() == 2)
		{
			tag_value.insert(std::pair<std::string, std::string>(QString(token.at(0)).toStdString(), QString(token.at(1)).toStdString()));
		}
		else if (token.size() == 1)
		{
			tag_value.insert(std::pair<std::string, std::string>(attribute_name, QString(token.at(0)).toStdString()));
		}
	}
	return true;
}

bool UniPAX::BridgeDBLink::isFreeSearchSupported(bool & ok,const std::string species_name)
{
	QUrl url(end_point);
	QByteArray answer;
	url.setPath(QString::fromStdString(species_name).append("/isFreeSearchSupported"));
	if (!request(url, answer))
	{
		return false;
	}

	if (QString(answer) == STR_TRUE)
	{
		ok = true;
	}
	else
	{
		ok = false;
	}
	return true;
}

bool UniPAX::BridgeDBLink::freeSearch(std::map<std::string, std::string> & tag_value, const std::string species_name, const std::string search_item, const unsigned int limit)
{
	bool ok = false;
	if (!isFreeSearchSupported(ok, species_name) || !ok)
	{
		return false;
	}
	QUrl url(end_point);
	QByteArray answer;
	url.setPath(QString::fromStdString(species_name).append("/search").append(search_item.c_str()));
	if (limit != 0)
	{
		url.addQueryItem(QString("limit"), QString::number(limit));
	}
	if (!request(url, answer))
	{
		return false;
	}
	tag_value.clear();
	QList<QByteArray> lines = answer.split('\n');
	for (QList<QByteArray>::iterator line = lines.begin(); line != lines.end(); ++line)
	{
		QList<QByteArray> token = line->split('\t');
		if (token.size() != 2)
		{
			return false;
		}
		tag_value.insert(std::pair<std::string, std::string>(QString(token.at(0)).toStdString(), QString(token.at(1)).toStdString()));
	}
	return true;
}

void UniPAX::BridgeDBLink::setAddress(std::string host, int port)
{
	end_point.setHost(QString::fromStdString(host));
	end_point.setPort(port);
}

void UniPAX::BridgeDBLink::setEndpoint(QUrl address)
{
	end_point = address;
}

void UniPAX::BridgeDBLink::setProxy(std::string _proxy_host, int _proxy_port)
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

std::string UniPAX::BridgeDBLink::getProxyHost() const
{
	return proxy_host;
}

int UniPAX::BridgeDBLink::getProxyPort() const
{
	return proxy_port;
}

void UniPAX::BridgeDBLink::setDebug(bool _debug)
{
	debug = _debug;
}

void UniPAX::BridgeDBLink::initMap()
{
	officialName_dbSymbol.clear();
	officialName_dbSymbol["Affymetrix Probeset"] = "X";
	officialName_dbSymbol["Agilent"] = "Ag";
	officialName_dbSymbol["BIND"] = "Bi";
	officialName_dbSymbol["BioCyc"] = "Bc";
	officialName_dbSymbol["BioGRID"] = "Bg";
	officialName_dbSymbol["BioModels Database"] = "Bm";
	officialName_dbSymbol["BioSystems"] = "Bs";
	officialName_dbSymbol["BRENDA"] = "Br";
	officialName_dbSymbol["CAS"] = "Ca";
	officialName_dbSymbol["Consensus CDS"] = "Cc";
	officialName_dbSymbol["ChEBI"] = "Ce";
	officialName_dbSymbol["ChemSpider"] = "Cs";
	officialName_dbSymbol["CodeLink"] = "Ge";
	officialName_dbSymbol["Database of Interacting Proteins"] = "Dip";
	officialName_dbSymbol["dbSNP"] = "Sn";
	officialName_dbSymbol["DrugBank"] = "Dr";
	officialName_dbSymbol["EcoCyc"] = "Eco";
	officialName_dbSymbol["EcoGene"] = "Ec";
	officialName_dbSymbol["European Nucleotide Archive"] = "Em";
	officialName_dbSymbol["Ensembl"] = "En";
	officialName_dbSymbol["Ensembl B. subtilis"] = "EnBs";
	officialName_dbSymbol["Ensembl C. elegans"] = "EnCe";
	officialName_dbSymbol["Ensembl Chicken"] = "EnGg";
	officialName_dbSymbol["Ensembl Chimp"] = "EnPt";
	officialName_dbSymbol["Ensembl Cow"] = "EnBt";
	officialName_dbSymbol["Ensembl Dog"] = "EnCf";
	officialName_dbSymbol["Ensembl E. coli"] = "EnEc";
	officialName_dbSymbol["Ensembl Fruitfly"] = "EnDm";
	officialName_dbSymbol["Ensembl Horse"] = "EnQc";
	officialName_dbSymbol["Ensembl Human"] = "EnHs";
	officialName_dbSymbol["Ensembl M. tuberculosis"] = "EnMx";
	officialName_dbSymbol["Ensembl Mosquito"] = "EnAg";
	officialName_dbSymbol["Ensembl Mouse"] = "EnMm";
	officialName_dbSymbol["Ensembl Pig"] = "EnSs";
	officialName_dbSymbol["Ensembl Plants"] = "EP";
	officialName_dbSymbol["Ensembl Rat"] = "EnRn";
	officialName_dbSymbol["Ensembl Xenopus"] = "EnXt";
	officialName_dbSymbol["Ensembl Yeast"] = "EnSc";
	officialName_dbSymbol["Ensembl Zebrafish"] = "EnDr";
	officialName_dbSymbol["Entrez Gene"] = "L";
	officialName_dbSymbol["Enzyme Nomenclature"] = "E";
	officialName_dbSymbol["FlyBase"] = "F";
	officialName_dbSymbol["GenBank"] = "G";
	officialName_dbSymbol["Gene Wiki"] = "Gw";
	officialName_dbSymbol["GeneOntology"] = "T";
	officialName_dbSymbol["Gramene Arabidopsis"] = "EnAt";
	officialName_dbSymbol["Gramene Genes"] = "Gg";
	officialName_dbSymbol["Gramene Literature"] = "Gl";
	officialName_dbSymbol["Gramene Maize"] = "EnZm";
	officialName_dbSymbol["Gramene Pathway"] = "Gp";
	officialName_dbSymbol["Gramene Rice"] = "EnOj";
	officialName_dbSymbol["HGNC Symbol"] = "H";
	officialName_dbSymbol["HGNC"] = "Hac";
	officialName_dbSymbol["HMDB"] = "Ch";
	officialName_dbSymbol["HomoloGene"] = "Hg";
	officialName_dbSymbol["HPRD"] = "Hp";
	officialName_dbSymbol["Illumina"] = "Il";
	officialName_dbSymbol["IntAct"] = "Ia";
	officialName_dbSymbol["InterPro"] = "I";
	officialName_dbSymbol["IPI"] = "Ip";
	officialName_dbSymbol["IRGSP Gene"] = "Ir";
	officialName_dbSymbol["KEGG Compound"] = "Ck";
	officialName_dbSymbol["KEGG Drug"] = "Kd";
	officialName_dbSymbol["KEGG Genes"] = "Kg";
	officialName_dbSymbol["KEGG Glycan"] = "Kl";
	officialName_dbSymbol["KEGG Pathway"] = "Kp";
	officialName_dbSymbol["KEGG Reaction"] = "Rk";
	officialName_dbSymbol["LIPID MAPS"] = "Lm";
	officialName_dbSymbol["LipidBank"] = "Lb";
	officialName_dbSymbol["MACiE"] = "Ma";
	officialName_dbSymbol["MaizeGDB"] = "Mg";
	officialName_dbSymbol["MatrixDB"] = "Md";
	officialName_dbSymbol["MetaCyc"] = "Mc";
	officialName_dbSymbol["Mouse Genome Database"] = "M";
	officialName_dbSymbol["MINT"] = "Mi";
	officialName_dbSymbol["miRBase mature sequence"] = "Mbm";
	officialName_dbSymbol["miRBase Sequence"] = "Mb";
	officialName_dbSymbol["NASC Gene"] = "N";
	officialName_dbSymbol["NCBI Protein"] = "Np";
	officialName_dbSymbol["NCI Pathway Interaction"] = "Pid";
	officialName_dbSymbol["NuGO wiki"] = "Nw";
	officialName_dbSymbol["OMIM"] = "Om";
	officialName_dbSymbol["Oryzabase"] = "Ob";
	officialName_dbSymbol["Other"] = "O";
	officialName_dbSymbol["Pathway Commons"] = "Pc";
	officialName_dbSymbol["Protein Data Bank"] = "Pd";
	officialName_dbSymbol["Pfam"] = "Pf";
	officialName_dbSymbol["PharmGKB Drug"] = "Pgd";
	officialName_dbSymbol["PharmGKB Gene"] = "Pgg";
	officialName_dbSymbol["PharmGKB Pathways"] = "Pgp";
	officialName_dbSymbol["PhosphoSite Protein"] = "Pp";
	officialName_dbSymbol["PINA"] = "Pi";
	officialName_dbSymbol["PlantGDB"] = "Pl";
	officialName_dbSymbol["PubChem-bioassay"] = "Cpb";
	officialName_dbSymbol["PubChem-compound"] = "Cpc";
	officialName_dbSymbol["PubChem-substance"] = "Cps";
	officialName_dbSymbol["Reactome"] = "Re";
	officialName_dbSymbol["RefSeq"] = "Q";
	officialName_dbSymbol["RESID"] = "Res";
	officialName_dbSymbol["RFAM"] = "Rf";
	officialName_dbSymbol["Rat Genome Database"] = "R";
	officialName_dbSymbol["Rhea"] = "Rh";
	officialName_dbSymbol["Rice Ensembl Gene"] = "Os";
	officialName_dbSymbol["SGD"] = "D";
	officialName_dbSymbol["Small Molecule Pathway Database"] = "Sm";
	officialName_dbSymbol["SMART"] = "Sma";
	officialName_dbSymbol["SPIKE Map"] = "Sk";
	officialName_dbSymbol["SPRINT"] = "Spr";
	officialName_dbSymbol["STRING"] = "Str";
	officialName_dbSymbol["SubstrateDB"] = "Sdb";
	officialName_dbSymbol["SubtiWiki"] = "Bsu";
	officialName_dbSymbol["SUPFAM"] = "Sf";
	officialName_dbSymbol["SWISS-MODEL"] = "Sw";
	officialName_dbSymbol["Systems Biology Ontology"] = "Sbo";
	officialName_dbSymbol["TAIR Locus"] = "A";
	officialName_dbSymbol["TIGR"] = "Ti";
	officialName_dbSymbol["TTD Drug"] = "Td";
	officialName_dbSymbol["TTD Target"] = "Tt";
	officialName_dbSymbol["TubercuList"] = "Tb";
	officialName_dbSymbol["UCSC Genome Browser"] = "Uc";
	officialName_dbSymbol["UniGene"] = "U";
	officialName_dbSymbol["Unipathway"] = "Up";
	officialName_dbSymbol["UniProtKB/TrEMBL"] = "S";
	officialName_dbSymbol["UniProtKB/Swiss-Prot"] = "Sp";
	officialName_dbSymbol["Wheat gene names"] = "Wn";
	officialName_dbSymbol[" Wheat gene refs"] = "Wr";
	officialName_dbSymbol["WikiGenes"] = "Wg";
	officialName_dbSymbol["WikiPathways"] = "Wp";
	officialName_dbSymbol["Wikipedia"] = "Wi";
	officialName_dbSymbol["WormBase"] = "W";
	officialName_dbSymbol["ZFIN Gene"] = "Z";
}

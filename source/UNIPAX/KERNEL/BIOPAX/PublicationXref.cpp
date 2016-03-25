#include<UNIPAX/KERNEL/BIOPAX/PublicationXref.h>
#include<set>
//Begin section for file PublicationXref.cpp
//TODO: Add definitions that you want preserved
//End section for file PublicationXref.cpp

UniPAX::PublicationXref::PublicationXref() : UniPAX::Xref(), year(0) {
    }

UniPAX::PublicationXref::PublicationXref(const PublicationXref& arg) : UniPAX::Xref(arg) ,
	author(arg.author),
	source(arg.source),
	title(arg.title),
	url(arg.url),
	year(arg.year)
{
    }

UniPAX::PublicationXref & UniPAX::PublicationXref::operator =(const PublicationXref & arg)  {
	UniPAX::Xref::operator=(arg);
   	author = arg.author;
	source = arg.source;
	title = arg.title;
	url = arg.url;
	year = arg.year;

	return *this;
}

UniPAX::PublicationXref::~PublicationXref()  {
    }

bool UniPAX::PublicationXref::merge(PublicationXref& object)
{
	if (!object.getYear() != 0)
	{
		if (!getYear() != 0)
		{
			if (getYear() != object.getYear())
			{
				std::cerr << "Error during merging: UniPAX::PublicationXref::year not equal ..."
						<< getYear() << " != " << object.getYear() << std::endl;
				return false;
			}
		}
		else
			setYear(object.getYear());
	}
	{
		std::set<std::string> tmp(getUrls().begin(), getUrls().end());
		for (std::vector<std::string>::iterator it = object.getUrls().begin(); it != object.getUrls().end(); it++)
		{
			tmp.insert(*it);
		}
		getUrls().assign(tmp.begin(), tmp.end());
	}
	if (!object.getTitle().empty())
	{
		if (!getTitle().empty())
		{
			if (getTitle() != object.getTitle())
			{
				std::cerr << "Error during merging: UniPAX::PublicationXref::title not equal ..."
						<< getTitle() << " != " << object.getTitle() << std::endl;
				return false;
			}
		}
		else
			setTitle(object.getTitle());
	}
	{
		std::set<std::string> tmp(getSources().begin(), getSources().end());
		for (std::vector<std::string>::iterator it = object.getSources().begin(); it != object.getSources().end(); it++)
		{
			tmp.insert(*it);
		}
		getSources().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<std::string> tmp(getAuthors().begin(), getAuthors().end());
		for (std::vector<std::string>::iterator it = object.getAuthors().begin(); it != object.getAuthors().end(); it++)
		{
			tmp.insert(*it);
		}
		getAuthors().assign(tmp.begin(), tmp.end());
	}

	return UniPAX::Xref::merge(object);
}

bool UniPAX::PublicationXref::update(PersistenceManager& manager)
{
	return UniPAX::Xref::update(manager);
}


const std::vector<std::string> & UniPAX::PublicationXref::getAuthors() const {
        return author;
}

std::vector<std::string> & UniPAX::PublicationXref::getAuthors() {
	return author;
}

void UniPAX::PublicationXref::addAuthor(std::string _author) {
	author.push_back(_author);
}

void UniPAX::PublicationXref::setAuthors(std::vector<std::string> & _authors) {
	author = _authors;
}


const std::vector<std::string> UniPAX::PublicationXref::getSources() const {
        return source;
}

std::vector<std::string> UniPAX::PublicationXref::getSources() {
	return source;
}

void UniPAX::PublicationXref::setSources(std::vector<std::string> _sources) {
	source = _sources;
}

void UniPAX::PublicationXref::addSource(std::string _source) {
	source.push_back(_source);
}


const std::string UniPAX::PublicationXref::getTitle() const {
        return title;
}

std::string UniPAX::PublicationXref::getTitle() {
	return title;
}

void UniPAX::PublicationXref::setTitle(std::string _title) {
	title = _title;
}


const std::vector<std::string> UniPAX::PublicationXref::getUrls() const {
        return url;
}

std::vector<std::string> UniPAX::PublicationXref::getUrls() {
	return url;
}

void UniPAX::PublicationXref::setUrl(std::vector<std::string> _urls) {
	url = _urls;
}

void UniPAX::PublicationXref::addUrl(std::string _url) {
	url.push_back(_url);
}


const int UniPAX::PublicationXref::getYear() const {
	return year;
}

int UniPAX::PublicationXref::getYear()  {
        return year;
}

void UniPAX::PublicationXref::setYear(int _year)  {
        year = _year;
}


bool UniPAX::PublicationXref::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Xref::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"url"))
	{
		addUrl(value);
		return true;
	}
	if (boost::iequals(attribute,"title"))
	{
		setTitle(value);
		return true;
	}
	if (boost::iequals(attribute,"source"))
	{
		addSource(value);
		return true;
	}
	if (boost::iequals(attribute,"author"))
	{
		addAuthor(value);
		return true;
	}
	if (boost::iequals(attribute,"year"))
	{
		return (PersistenceManager::convertAttribute(value,year));
	}

	return false;

}


bool UniPAX::PublicationXref::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Xref::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (!PersistenceManager::convertAttribute(year, tmp))
	{
		return false;
	}
	if (year != 0)
		value.push_back(std::pair<std::string,std::string>("year", tmp));
	tmp.clear();
	{
		std::vector<std::string>::iterator it;
		for (it = url.begin(); it != url.end(); it++)
			value.push_back(std::pair<std::string,std::string>("url", *it));
	}
	if (!getTitle().empty())
		value.push_back(std::pair<std::string,std::string>("title", getTitle()));
	{
		std::vector<std::string>::iterator it;
		for (it = source.begin(); it != source.end(); it++)
			value.push_back(std::pair<std::string,std::string>("source", *it));
	}
	{
		std::vector<std::string>::iterator it;
		for (it = author.begin(); it != author.end(); it++)
			value.push_back(std::pair<std::string,std::string>("author", *it));
	}

	return true;

}

//void UniPAX::PublicationXref::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Xref::init(e,db);
//
//	return;
//}

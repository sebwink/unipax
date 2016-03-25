#ifndef PUBLICATIONXREF_H
#define PUBLICATIONXREF_H
//Begin section for file PublicationXref.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file PublicationXref.h
#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT PublicationXref : public Xref {

protected:

	std::vector<std::string> author;

	std::vector<std::string> source;

	std::string title;

	std::vector<std::string> url;

	int year;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "PublicationXref";
	}

	static std::string type() {
		return std::string("PublicationXref");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idPublicationXref;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idPublicationXref;
        }

        PublicationXref();

	PublicationXref(const PublicationXref & arg);

	PublicationXref & operator =(const PublicationXref & arg);

	~PublicationXref();

	bool merge(PublicationXref& object);
	bool update(PersistenceManager& manager);


	//get author
	const std::vector<std::string> & getAuthors() const;

	std::vector<std::string> & getAuthors();

	void setAuthors(std::vector<std::string> & _authors);

	void addAuthor(std::string _author);


	//get source
	const std::vector<std::string> getSources() const;

	std::vector<std::string> getSources();

	void setSources(std::vector<std::string> _sources);

	void addSource(std::string _source);


	//get title
	const std::string getTitle() const;

	std::string getTitle();

	void setTitle(std::string _title);


	//get url
	const std::vector<std::string> getUrls() const;

	std::vector<std::string> getUrls();

	void setUrl(std::vector<std::string> _urls);

	void addUrl(std::string _url);


	const int getYear() const;

	//get year
	int getYear();

	//set year
	void setYear(int _year);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Xref super;

};  //end class PublicationXref

typedef UnipaxPtr<PublicationXref>::type PublicationXrefPtr;

}//end namespace UniPAX

#endif

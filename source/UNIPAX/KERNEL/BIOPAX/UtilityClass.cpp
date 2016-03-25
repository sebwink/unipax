#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<set>
//Begin section for file UtilityClass.cpp
//TODO: Add definitions that you want preserved
//End section for file UtilityClass.cpp

UniPAX::UtilityClass::UtilityClass() : UniPAX::Thing() {
    }

UniPAX::UtilityClass::UtilityClass(const UniPAX::UtilityClass& arg) : UniPAX::Thing(arg) , comment(arg.comment)
{

    }

UniPAX::UtilityClass & UniPAX::UtilityClass::operator =(const UniPAX::UtilityClass & arg)  {
	UniPAX::Thing::operator=(arg);
	comment = arg.comment;

	return *this;
}

UniPAX::UtilityClass::~UtilityClass()  {
    }

bool UniPAX::UtilityClass::merge(UtilityClass& object)
{
	{
		std::set<std::string> tmp(getComments().begin(), getComments().end());
		for (std::vector<std::string>::iterator it = object.getComments().begin(); it != object.getComments().end(); it++)
		{
			tmp.insert(*it);
		}
		getComments().assign(tmp.begin(), tmp.end());
	}

	return UniPAX::Thing::merge(object);
}

bool UniPAX::UtilityClass::update(PersistenceManager& manager)
{
	return UniPAX::Thing::update(manager);
}

const std::vector<std::string> & UniPAX::UtilityClass::getComments() const {
        return comment;
}

std::vector<std::string> & UniPAX::UtilityClass::getComments() {
	return comment;
}

void UniPAX::UtilityClass::setComments(std::vector<std::string> _comments) {
	comment = _comments;
}

void UniPAX::UtilityClass::addComment(std::string _comment) {
	comment.push_back(_comment);
}


bool UniPAX::UtilityClass::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Thing::setAttribute(attribute, value, manager))
		return true;


	if (boost::iequals(attribute,"comment"))
	{
		addComment(value);
		return true;
	}

	return false;

}

bool UniPAX::UtilityClass::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Thing::getAttribute(value, manager))
		return false;

	{
		std::vector<std::string>::iterator it;
		for (it = comment.begin(); it != comment.end(); it++)
			value.push_back(std::pair<std::string,std::string>("comment", *it));
	}
	return true;
}

//void UniPAX::UtilityClass::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Thing::init(e,db);
//
//	return;
//}

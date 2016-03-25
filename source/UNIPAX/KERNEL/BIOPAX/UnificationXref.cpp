#include<UNIPAX/KERNEL/BIOPAX/UnificationXref.h>
#include<iostream>
//Begin section for file UnificationXref.cpp
//TODO: Add definitions that you want preserved
//End section for file UnificationXref.cpp

UniPAX::UnificationXref::UnificationXref() : UniPAX::Xref() {
    }

UniPAX::UnificationXref::UnificationXref(const UnificationXref& arg) : UniPAX::Xref(arg) {
}

UniPAX::UnificationXref & UniPAX::UnificationXref::operator =(const UnificationXref & arg)  {
	UniPAX::Xref::operator=(arg);

	return *this;
}

UniPAX::UnificationXref::~UnificationXref()  {
    }

bool UniPAX::UnificationXref::merge(UnificationXref& object)
{
	return UniPAX::Xref::merge(object);
}

bool UniPAX::UnificationXref::update(PersistenceManager& manager)
{
	return UniPAX::Xref::update(manager);
}

bool UniPAX::UnificationXref::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Xref::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::UnificationXref::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Xref::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::UnificationXref::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Xref::init(e,db);
//
//	return;
//}


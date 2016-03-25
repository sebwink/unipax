#include<UNIPAX/KERNEL/BIOPAX/ComplexAssembly.h>
#include<set>
//Begin section for file ComplexAssembly.cpp
//TODO: Add definitions that you want preserved
//End section for file ComplexAssembly.cpp

UniPAX::ComplexAssembly::ComplexAssembly() : UniPAX::Conversion() {
    }

UniPAX::ComplexAssembly::ComplexAssembly(const ComplexAssembly& arg) : UniPAX::Conversion(arg) {
    }

UniPAX::ComplexAssembly & UniPAX::ComplexAssembly::operator =(const ComplexAssembly & arg)  {
	UniPAX::Conversion::operator=(arg);

	return *this;
}

UniPAX::ComplexAssembly::~ComplexAssembly()  {
    }

bool UniPAX::ComplexAssembly::merge(ComplexAssembly& object)
{
	return UniPAX::Conversion::merge(object);
}

bool UniPAX::ComplexAssembly::update(PersistenceManager& manager)
{
	return UniPAX::Conversion::update(manager);
}

bool UniPAX::ComplexAssembly::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Conversion::setAttribute(attribute, value, manager))
		return true;

	return false;

}


bool UniPAX::ComplexAssembly::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Conversion::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::ComplexAssembly::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Conversion::init(e,db);
//
//	return;
//}

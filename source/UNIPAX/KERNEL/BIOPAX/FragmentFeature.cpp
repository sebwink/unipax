#include<UNIPAX/KERNEL/BIOPAX/FragmentFeature.h>
#include<set>
//Begin section for file FragmentFeature.cpp
//TODO: Add definitions that you want preserved
//End section for file FragmentFeature.cpp

UniPAX::FragmentFeature::FragmentFeature() : UniPAX::EntityFeature()  {
    }

UniPAX::FragmentFeature::FragmentFeature(const FragmentFeature& arg) : UniPAX::EntityFeature(arg) {
    }

UniPAX::FragmentFeature & UniPAX::FragmentFeature::operator =(const FragmentFeature & arg)  {
	UniPAX::EntityFeature::operator=(arg);

	return *this;
}

UniPAX::FragmentFeature::~FragmentFeature()  {
    }

bool UniPAX::FragmentFeature::merge(FragmentFeature& object)
{
	return UniPAX::EntityFeature::merge(object);
}

bool UniPAX::FragmentFeature::update(PersistenceManager& manager)
{
	return UniPAX::EntityFeature::update(manager);
}

bool UniPAX::FragmentFeature::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::EntityFeature::setAttribute(attribute, value, manager))
		return true;

	return false;

}

bool UniPAX::FragmentFeature::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::EntityFeature::getAttribute(value, manager))
		return false;

	return true;

}

//void UniPAX::FragmentFeature::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::EntityFeature::init(e,db);
//
//	return;
//}

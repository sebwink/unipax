#include<UNIPAX/KERNEL/BIOPAX/RelationshipXref.h>
#include<set>
//Begin section for file RelationshipXref.cpp
//TODO: Add definitions that you want preserved
//End section for file RelationshipXref.cpp

UniPAX::RelationshipXref::RelationshipXref() : UniPAX::Xref() {
    }

UniPAX::RelationshipXref::RelationshipXref(const RelationshipXref& arg) : UniPAX::Xref(arg) ,
	relationshipType(arg.relationshipType)
{
    }

UniPAX::RelationshipXref & UniPAX::RelationshipXref::operator =(const RelationshipXref & arg)  {
	UniPAX::Xref::operator=(arg);
	relationshipType = arg.relationshipType;

	return *this;
}

UniPAX::RelationshipXref::~RelationshipXref()  {
    }

bool UniPAX::RelationshipXref::merge(RelationshipXref& object)
{
	{
		std::set<UniPAX::RelationshipTypeVocabularyPtr> tmp(getRelationshipTypes().begin(), getRelationshipTypes().end());
		for (std::vector<UniPAX::RelationshipTypeVocabularyPtr>::iterator it = object.getRelationshipTypes().begin(); it != object.getRelationshipTypes().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getRelationshipTypes().assign(tmp.begin(), tmp.end());
	}

	return UniPAX::Xref::merge(object);
}

bool UniPAX::RelationshipXref::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> >::iterator it;
		for (it = relationshipType.begin(); it != relationshipType.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<RelationshipTypeVocabulary>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setRelationshipTypes(tmp_vec);
	}

	return UniPAX::Xref::update(manager);
}


const std::vector<boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> > UniPAX::RelationshipXref::getRelationshipTypes() const {
        return relationshipType;
}

std::vector<boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> > UniPAX::RelationshipXref::getRelationshipTypes() {
	return relationshipType;
}

void UniPAX::RelationshipXref::setRelationshipTypes(std::vector<boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> > _relationshipTypes) {
	relationshipType = _relationshipTypes;
}

void UniPAX::RelationshipXref::addRelationshipType(boost::shared_ptr<UniPAX::RelationshipTypeVocabulary>  _relationshipType) {
	relationshipType.push_back(_relationshipType);
}


bool UniPAX::RelationshipXref::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Xref::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"relationshipType"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "RelationshipXref::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		relationshipType.push_back(boost::dynamic_pointer_cast<UniPAX::RelationshipTypeVocabulary>(object));
		return true;
	}

	return false;

}



bool UniPAX::RelationshipXref::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Xref::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	/*if (relationshipType == 0)
	{
//		value.push_back(std::pair<std::string,std::string>("#relationshipType", "NIL"));
	}
	else
	{
		tmp.clear();
		if (!manager.getId(relationshipType,tmp))
		{
			return false;
		}
		value.push_back(std::pair<std::string,std::string>("#relationshipType", tmp));

	}*/
	{
		std::vector<boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> >::iterator it;
		for (it = relationshipType.begin(); it != relationshipType.end(); it++)
		{
			if (*it == 0)
			{
	//			value.push_back(std::pair<std::string,std::string>("#relationshipType", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#relationshipType", tmp));

			}
		}
	}
	
	return true;

}

//void UniPAX::RelationshipXref::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Xref::init(e,db);
//
//	return;
//}

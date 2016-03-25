#include <UNIPAX/KERNEL/EXT/Series.h>

UniPAX::Series::Series() : UniPAX::UIBase()
{
}

UniPAX::Series::Series(const UniPAX::Series & arg) : UniPAX::UIBase(arg),
   description_tags(arg.description_tags),
   idMapping_list(arg.idMapping_list),
   sample_list(arg.sample_list)
{
}

UniPAX::Series & UniPAX::Series::operator =(const UniPAX::Series & arg)
{
    UniPAX::UIBase::operator =(arg);
    description_tags = arg.description_tags;
    idMapping_list = arg.idMapping_list;
    sample_list = arg.sample_list;
    return *this;
}

UniPAX::Series::~Series()
{
}

//void UniPAX::Series::init (odb::callback_event e, odb::database& db) const
//{
//    UniPAX::Entity::init(e, db);
//
//    if (e == odb::callback_event::post_load)
//    {
//            // load the object pointer
//            idMapping_list.clear();
//            for (std::vector<UnipaxId>::iterator it = id_idMapping_list.begin(); it != id_idMapping_list.end(); it++)
//            {
//                idMapping_list.push_back(boost::dynamic_pointer_cast<UniPAX::IdMapping>(getObjectByID(db, *it)));
//            }
//            sample_list.clear();
//            for (std::vector<UnipaxId>::iterator it = id_sample_list.begin(); it != id_sample_list.end(); it++)
//            {
//                sample_list.push_back(boost::dynamic_pointer_cast<UniPAX::Sample>(getObjectByID(db, *it)));
//            }
//    }
//    else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//    {
//            // set the object ids
//            id_idMapping_list.clear();
//            for (std::vector<UnipaxPtr<UniPAX::IdMapping>::type >::iterator it = idMapping_list.begin(); it != idMapping_list.end(); it++)
//            {
//                    if (*it)
//                            id_idMapping_list.push_back((*it)->getUnipaxId());
//            }
//            id_sample_list.clear();
//            for (std::vector<UnipaxPtr<UniPAX::Sample>::type >::iterator it = sample_list.begin(); it != sample_list.end(); it++)
//            {
//                    if (*it)
//                            id_sample_list.push_back((*it)->getUnipaxId());
//            }
//    }
//}

bool UniPAX::Series::merge(UniPAX::Series& object)
{
    return false;
}

bool UniPAX::Series::update(UniPAX::PersistenceManager& manager)
{
    return true;
}

// description_tags
std::map<std::string, std::string> & UniPAX::Series::getDescriptionTags()
{
    return description_tags;
}

const std::map<std::string, std::string> & UniPAX::Series::getDescriptionTags() const
{
    return description_tags;
}

void UniPAX::Series::setDescriptionTags(std::map<std::string, std::string> _description_tags)
{
    description_tags = _description_tags;
}

void UniPAX::Series::setDescriptionTag(std::string tag, std::string value)
{
    description_tags[tag] = value;
}

// idMapping_list
std::vector<UnipaxPtr<UniPAX::IdMapping>::type > & UniPAX::Series::getIdMappingList()
{
    return idMapping_list;
}

const std::vector<UnipaxPtr<UniPAX::IdMapping>::type > & UniPAX::Series::getIdMappingList() const
{
    return idMapping_list;
}

void UniPAX::Series::setIdMappingList(std::vector<UnipaxPtr<UniPAX::IdMapping>::type > _idMapping_list)
{
    idMapping_list = _idMapping_list;
}

void UniPAX::Series::addIdMapping(UnipaxPtr<UniPAX::IdMapping>::type _idMapping)
{
    idMapping_list.push_back(_idMapping);
}

// sample_list
const std::vector<UnipaxPtr<UniPAX::Sample>::type > & UniPAX::Series::getSampleList() const
{
    return sample_list;
}

std::vector<UnipaxPtr<UniPAX::Sample>::type > & UniPAX::Series::getSampleList()
{
    return sample_list;
}

void UniPAX::Series::setSampleList(std::vector<UnipaxPtr<UniPAX::Sample>::type > _sample_list)
{
    sample_list = _sample_list;
}

void UniPAX::Series::addSample(UnipaxPtr<UniPAX::Sample>::type _sample)
{
    sample_list.push_back(_sample);
}


bool UniPAX::Series::setAttribute(std::string& attribute, std::string& value, UniPAX::PersistenceManager& manager)
{
    if (UniPAX::UIBase::setAttribute(attribute, value, manager))
        return true;
    if (boost::iequals(attribute,"description_tags"))
    {
        int pos = value.find("=");
        if (pos == -1)
        {
            std::cerr << "Series::setAttribute - invalid tag (value = " << value << ")" << std::endl;
            return false;
        }
        description_tags[value.substr(0, pos)] = value.substr(pos);
        return true;
    }
    if (boost::iequals(attribute,"#idMapping_list"))
    {
            // if sometimes set to NIL or empty string neglect
            if (value == "NIL" || value.empty())
                    return true;

            UnipaxPtr<UniPAX::UPBase>::type object = manager.getInstance(value,"");
            if (object == 0)
            {
                    std::cerr << "Series::setAttribute - object not known (value = " << value << ")" << std::endl;
                    return false;
            }

            idMapping_list.push_back(boost::dynamic_pointer_cast<UniPAX::IdMapping>(object));
            return true;
    }
    if (boost::iequals(attribute,"#sample_list"))
    {
            // if sometimes set to NIL or empty string neglect
            if (value == "NIL" || value.empty())
                    return true;

            UnipaxPtr<UniPAX::UPBase>::type object = manager.getInstance(value,"");
            if (object == 0)
            {
                    std::cerr << "Series::setAttribute - object not known (value = " << value << ")" << std::endl;
                    return false;
            }

            sample_list.push_back(boost::dynamic_pointer_cast<UniPAX::Sample>(object));
            return true;
    }

    return false;
}

bool UniPAX::Series::getAttribute(std::vector<std::pair<std::string,std::string> >& value, UniPAX::PersistenceManager& manager)
{
    if (!UniPAX::UIBase::getAttribute(value, manager))
        return false;
    std::stringstream ss;
    for (std::map<std::string, std::string>::const_iterator it = description_tags.begin(); it != description_tags.end(); it++)
    {
        ss.str("");
        ss << it->first << "=" << it->second;
        value.push_back(std::pair<std::string, std::string>("description_tags", ss.str()));
    }
    std::string tmp;
    for (std::vector<UnipaxPtr<UniPAX::IdMapping>::type>::const_iterator it = idMapping_list.begin(); it != idMapping_list.end(); it++)
    {
        if (*it == 0)
        {
        }
        else
        {
                tmp.clear();
                if (!manager.getId(*it, tmp))
                {
                        manager.setError(this->type() + ":idMapping_list contains unknown reference.");
                        return false;
                }
                value.push_back(std::pair<std::string, std::string>("#idMapping_list", tmp));
        }
    }
    tmp.clear();
    for (std::vector<UnipaxPtr<UniPAX::Sample>::type>::const_iterator it = sample_list.begin(); it != sample_list.end(); it++)
    {
        if (*it == 0)
        {
        }
        else
        {
                tmp.clear();
                if (!manager.getId(*it, tmp))
                {
                        manager.setError(this->type() + ":sample_list contains unknown reference.");
                        return false;
                }
                value.push_back(std::pair<std::string, std::string>("#sample_list", tmp));
        }
    }
    return true;
}

const std::string & UniPAX::Series::getName() const
{
	return name;
}

std::string & UniPAX::Series::getName()
{
	return name;
}

void UniPAX::Series::setName(std::string _name)
{
	name = _name;
}

const std::string & UniPAX::Series::getDescription() const
{
	return description;
}

std::string & UniPAX::Series::getDescription()
{
	return description;
}

void UniPAX::Series::setDescription(std::string _description)
{
	description = _description;
}

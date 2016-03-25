#include<UNIPAX/KERNEL/EXT/SBase.h>
//Begin section for file SBase.cpp
//TODO: Add definitions that you want preserved
//End section for file SBase.cpp


UniPAX::SBase::SBase() : UniPAX::UIBase()
//, unipaxSource(0)
{
}

UniPAX::SBase::SBase(const UniPAX::SBase & arg) : UniPAX::UIBase(arg),
		metaId(arg.metaId),
		sboTerm(arg.sboTerm),
		notes(arg.notes),
		annotation(arg.annotation)
{
}

UniPAX::SBase & UniPAX::SBase::operator =(const UniPAX::SBase & arg) {
	UniPAX::UIBase::operator=(arg);
	metaId = arg.metaId;
	sboTerm = arg.sboTerm;
	notes = arg.notes;
	annotation = arg.annotation;

	return *this;
}

UniPAX::SBase::~SBase()  {
}

bool UniPAX::SBase::merge(SBase& object)
{
	if (metaId.empty())
	{
		metaId = object.getMetaId();
	}
	else
	{
		if (metaId.compare(object.getMetaId()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::SBase::metaId not equal ..."
					<< metaId << " != " << object.getMetaId() << std::endl;
			return false;
		}
	}
	if (sboTerm.empty())
	{
		sboTerm = object.getSboTerm();
	}
	else
	{
		if (sboTerm.compare(object.getSboTerm()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::SBase::sboTerm not equal ..."
					<< sboTerm << " != " << object.getSboTerm() << std::endl;
			return false;
		}
	}
	if (notes.empty())
	{
		notes = object.getNotes();
	}
	else
	{
		if (notes.compare(object.getNotes()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::SBase::notes not equal ..."
					<< notes << " != " << object.getNotes() << std::endl;
			return false;
		}
	}
	if (annotation.empty())
	{
		annotation = object.getAnnotation();
	}
	else
	{
		if (annotation.compare(object.getAnnotation()) != 0)
		{
			std::cerr << "Error during merging: UniPAX::SBase::annotation not equal ..."
					<< annotation << " != " << object.getAnnotation() << std::endl;
			return false;
		}
	}

//	if (unipaxSource != 0)
//	{
//		if (object.getUnipaxSource() != 0)
//		{
//
//			if (unipaxSource->getUnipaxId() != object.getUnipaxSource()->getUnipaxId())
//			{
//				std::cerr << "Error during merging: UniPAX::SBase::unipaxSource not equal ..."
//						<< unipaxSource->getUnipaxId() << " != " << object.getUnipaxSource()->getUnipaxId() << std::endl;
//				return false;
//			}
//		}
//	}
//	else
//	{
//		unipaxSource = object.getUnipaxSource();
//	}

	return UniPAX::UIBase::merge(object);
}

bool UniPAX::SBase::update(PersistenceManager& manager)
{
	// check single pointer if object was merged
//	if (manager.isMerged(getUnipaxSource()))
//	{
//		setUnipaxSource(boost::dynamic_pointer_cast<ImportSource>(manager.getMergedObject(getUnipaxSource())));
//	}

	return UniPAX::UIBase::update(manager);
}

// metaId
const std::string & UniPAX::SBase::getMetaId() const
{
	return metaId;
}

std::string & UniPAX::SBase::getMetaId()
{
	return metaId;
}

void UniPAX::SBase::setMetaId(std::string _metaId)
{
	metaId = _metaId;
}

// sboTerm
const std::string & UniPAX::SBase::getSboTerm() const
{
	return sboTerm;
}

std::string & UniPAX::SBase::getSboTerm()
{
	return sboTerm;
}

void UniPAX::SBase::setSboTerm(std::string _sboTerm)
{
	sboTerm = _sboTerm;
}

// notes
const std::string & UniPAX::SBase::getNotes() const
{
	return notes;
}

std::string & UniPAX::SBase::getNotes()
{
	return notes;
}

void UniPAX::SBase::setNotes(std::string _notes)
{
	notes = _notes;
}

// annotation
const std::string & UniPAX::SBase::getAnnotation() const
{
	return annotation;
}

std::string & UniPAX::SBase::getAnnotation()
{
	return annotation;
}

void UniPAX::SBase::setAnnotation(std::string _annotation)
{
	annotation = _annotation;
}

bool UniPAX::SBase::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UIBase::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"sboTerm"))
	{
		setSboTerm(value);
		return true;
	}
	if (boost::iequals(attribute,"metaId"))
	{
		setMetaId(value);
		return true;
	}
	if (boost::iequals(attribute,"notes"))
	{
		setNotes(value);
		return true;
	}
	if (boost::iequals(attribute,"annotation"))
	{
		setAnnotation(value);
		return true;
	}
	return false;

}


bool UniPAX::SBase::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UIBase::getAttribute(value, manager))
		return false;
	{
		if (! getMetaId().empty())
			value.push_back(std::pair<std::string,std::string>("metaId", getMetaId()));
	}
	{
		if (!getSboTerm().empty())
			value.push_back(std::pair<std::string,std::string>("sboTerm", getSboTerm()));
	}
	{
		if (!getNotes().empty())
			value.push_back(std::pair<std::string,std::string>("notes", getNotes()));
	}
	{
		if (!getAnnotation().empty())
			value.push_back(std::pair<std::string,std::string>("annotation", getAnnotation()));
	}
	return true;

}

//void UniPAX::SBase::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UPBase::init(e,db);
//
//	return;
//}

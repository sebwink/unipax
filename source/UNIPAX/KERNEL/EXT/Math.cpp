#include<UNIPAX/KERNEL/EXT/Math.h>
//Begin section for file Math.cpp
//TODO: Add definitions that you want preserved
//End section for file Math.cpp

UniPAX::Math::Math() : UniPAX::UPBase() {
    }

UniPAX::Math::Math(const Math & arg)  : UniPAX::UPBase(arg),
	mathML(arg.mathML)
{}

UniPAX::Math & UniPAX::Math::operator =(const Math & arg)  {
	UniPAX::UPBase::operator=(arg);
	mathML = arg.mathML;

	return *this;
}

UniPAX::Math::~Math()  {
    }

bool UniPAX::Math::merge(UniPAX::Math& object)
{
	if (mathML.empty())
	{
		mathML = object.getMathML();
	}
	else
	{
		if (mathML.compare(object.getMathML()) != 0)
		{
								std::cerr << "Error during merging: UniPAX::Math::mathML not equal ..."
								<< mathML << " != " << object.getMathML() << std::endl;
						return false;
	
		}
	}
	return UniPAX::UPBase::merge(object);
}

bool UniPAX::Math::update(PersistenceManager& manager)
{
		return UniPAX::UPBase::update(manager);
}

const std::string & UniPAX::Math::getMathML() const {
        return mathML;
}

std::string & UniPAX::Math::getMathML() {
	return mathML;
}

void UniPAX::Math::setMathML(std::string _mathML) {
	mathML = _mathML;
}

bool UniPAX::Math::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UPBase::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"mathML"))
	{
		setMathML(value);
		return true;
	}
	return false;
}

bool UniPAX::Math::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UPBase::getAttribute(value, manager))
		return false;

	value.push_back(std::pair<std::string,std::string>("mathML", getMathML()));

	return true;
}

//void UniPAX::Math::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UPBase::init(e,db);
//
//	return;
//}

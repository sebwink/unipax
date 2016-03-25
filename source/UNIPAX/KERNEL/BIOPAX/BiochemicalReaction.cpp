#include<UNIPAX/KERNEL/BIOPAX/BiochemicalReaction.h>
#include<set>
//Begin section for file BiochemicalReaction.cpp
//TODO: Add definitions that you want preserved
//End section for file BiochemicalReaction.cpp

UniPAX::BiochemicalReaction::BiochemicalReaction()  : UniPAX::Conversion(),
deltaH(0.),
deltaS(0.)
{
    }

UniPAX::BiochemicalReaction::BiochemicalReaction(const BiochemicalReaction& arg) : UniPAX::Conversion(arg) ,
    deltaH(arg.deltaH),
    deltaS(arg.deltaS),
	eCNumber(arg.eCNumber),
	deltaG(arg.deltaG),
	kEQ(arg.kEQ)
{
    }

UniPAX::BiochemicalReaction & UniPAX::BiochemicalReaction::operator =(const BiochemicalReaction & arg)  {
	UniPAX::Conversion::operator=(arg);
    deltaH = arg.deltaH;
    deltaS = arg.deltaS;
	eCNumber = arg.eCNumber;
	deltaG = arg.deltaG;
	kEQ = arg.kEQ;

	return *this;
}

UniPAX::BiochemicalReaction::~BiochemicalReaction()
{
}


bool UniPAX::BiochemicalReaction::merge(BiochemicalReaction& object)
{
	{
		std::set<UniPAX::KPrimePtr> tmp(getKEQs().begin(), getKEQs().end());
		for (std::vector<UniPAX::KPrimePtr>::iterator it = object.getKEQs().begin(); it != object.getKEQs().end(); it++)
		{
			if (*it == 0)
			{
				tmp.insert(*it);
			}
		}
		getKEQs().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::DeltaGPtr> tmp(getDeltaGs().begin(), getDeltaGs().end());
		for (std::vector<UniPAX::DeltaGPtr>::iterator it = object.getDeltaGs().begin(); it != object.getDeltaGs().end(); it++)
		{
			if (*it == 0)
			{
				tmp.insert(*it);
			}
		}
		getDeltaGs().assign(tmp.begin(), tmp.end());
	}

	if (!object.getDeltaS() != 0.)
	{
		if (!getDeltaS() != 0.)
		{
			if (getDeltaS() != object.getDeltaS())
			{
				std::cerr << "Error during merging: UniPAX::BiochemicalReaction::deltaS not equal ..."
						<< getDeltaS() << " != " << object.getDeltaS() << std::endl;
				return false;
			}
		}
		else
			setDeltaS(object.getDeltaS());
	}

	if (!object.getDeltaH() != 0.)
	{
		if (!getDeltaH() != 0.)
		{
			if (getDeltaH() != object.getDeltaH())
			{
				std::cerr << "Error during merging: UniPAX::BiochemicalReaction::deltaH not equal ..."
						<< getDeltaH() << " != " << object.getDeltaH() << std::endl;
				return false;
			}
		}
		else
			setDeltaH(object.getDeltaH());
	}
	if (!object.getECNumber().empty())
	{
		if (!getECNumber().empty())
		{
			if (getECNumber() != object.getECNumber())
			{
				std::cerr << "Error during merging: UniPAX::BiochemicalReaction::ecNumber not equal ..."
						<< getECNumber() << " != " << object.getECNumber() << std::endl;
				return false;
			}
		}
		else
			setECNumber(object.getECNumber());
	}

	return UniPAX::Conversion::merge(object);

}

bool UniPAX::BiochemicalReaction::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::KPrime> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::KPrime> >::iterator it;
		for (it = kEQ.begin(); it != kEQ.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<KPrime>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setKEQs(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::DeltaG> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::DeltaG> >::iterator it;
		for (it = deltaG.begin(); it != deltaG.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<DeltaG>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setDeltaGs(tmp_vec);
	}

	return UniPAX::Conversion::update(manager);
}

const double UniPAX::BiochemicalReaction::getDeltaH() const {
        return deltaH;
}

double UniPAX::BiochemicalReaction::getDeltaH() {
	return deltaH;
}

void UniPAX::BiochemicalReaction::setDeltaH(double _deltaH)  {
        deltaH = _deltaH;
}

const double UniPAX::BiochemicalReaction::getDeltaS() const {
	return deltaS;
}

double UniPAX::BiochemicalReaction::getDeltaS()  {
        return deltaS;
}

void UniPAX::BiochemicalReaction::setDeltaS(double _deltaS)  {
        deltaS = _deltaS;
}

const std::string & UniPAX::BiochemicalReaction::getECNumber() const {
        return eCNumber;
}

std::string & UniPAX::BiochemicalReaction::getECNumber() {
	return eCNumber;
}

void UniPAX::BiochemicalReaction::setECNumber(std::string _eCNumber) {
	eCNumber = _eCNumber;
}

const std::vector<boost::shared_ptr<UniPAX::DeltaG> > & UniPAX::BiochemicalReaction::getDeltaGs() const {
        return deltaG;
}

std::vector<boost::shared_ptr<UniPAX::DeltaG> > & UniPAX::BiochemicalReaction::getDeltaGs() {
	return deltaG;
}

void UniPAX::BiochemicalReaction::setDeltaGs(std::vector<boost::shared_ptr<UniPAX::DeltaG> > _deltaGs) {
	deltaG = _deltaGs;
}

void UniPAX::BiochemicalReaction::addDeltaG(boost::shared_ptr<UniPAX::DeltaG>  _deltaG) {
	deltaG.push_back(_deltaG);
}

const std::vector<boost::shared_ptr<UniPAX::KPrime> > & UniPAX::BiochemicalReaction::getKEQs() const {
        return kEQ;
}

std::vector<boost::shared_ptr<UniPAX::KPrime> > & UniPAX::BiochemicalReaction::getKEQs() {
	return kEQ;
}

void UniPAX::BiochemicalReaction::setKEQs(std::vector<boost::shared_ptr<UniPAX::KPrime> > _kEQs) {
	kEQ = _kEQs;
}

void UniPAX::BiochemicalReaction::addKEQ(boost::shared_ptr<UniPAX::KPrime>  _kEQ) {
	kEQ.push_back(_kEQ);
}

bool UniPAX::BiochemicalReaction::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Conversion::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"kEQ"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "BiochemicalReaction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		kEQ.push_back(boost::dynamic_pointer_cast<UniPAX::KPrime>(object));
		return true;
	}
	if (boost::iequals(attribute,"deltaG"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "BiochemicalReaction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		deltaG.push_back(boost::dynamic_pointer_cast<UniPAX::DeltaG>(object));
		return true;
	}
	if (boost::iequals(attribute,"deltaS"))
	{
		return (PersistenceManager::convertAttribute(value,deltaS));
	}
	if (boost::iequals(attribute,"deltaH"))
	{
		return (PersistenceManager::convertAttribute(value,deltaH));
	}
	if (boost::iequals(attribute,"eCNumber"))
	{
		setECNumber(value);
		return true;
	}

	return false;

}


bool UniPAX::BiochemicalReaction::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Conversion::getAttribute(value, manager))
		return false;

	std::string tmp = "";


	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::KPrime> >::iterator it;
		for (it = kEQ.begin(); it != kEQ.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#kEQ", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#kEQ", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::DeltaG> >::iterator it;
		for (it = deltaG.begin(); it != deltaG.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#deltaG", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#deltaG", tmp));

			}
		}
	}
	tmp.clear();
	if (!PersistenceManager::convertAttribute(deltaS, tmp))
	{
		return false;
	}
	if (deltaS != 0.)
		value.push_back(std::pair<std::string,std::string>("deltaS", tmp));
	tmp.clear();
	if (!PersistenceManager::convertAttribute(deltaH, tmp))
	{
		return false;
	}
	if (deltaH != 0.)
		value.push_back(std::pair<std::string,std::string>("deltaH", tmp));


	if (!getECNumber().empty())
		value.push_back(std::pair<std::string,std::string>("eCNumber", getECNumber()));

	return true;

}


//void UniPAX::BiochemicalReaction::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Conversion::init(e,db);
//
//	return;
//}

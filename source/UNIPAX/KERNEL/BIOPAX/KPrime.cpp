#include<UNIPAX/KERNEL/BIOPAX/KPrime.h>
#include<set>
//Begin section for file KPrime.cpp
//TODO: Add definitions that you want preserved
//End section for file KPrime.cpp

UniPAX::KPrime::KPrime() : UniPAX::UtilityClass(),
	ionicStrength(0.),
	kPrime(0.),
	ph(0.),
	pMg(0.),
	temperature(0.)
{
    }

UniPAX::KPrime::KPrime(const KPrime & arg)  : UniPAX::UtilityClass(arg),
    ionicStrength(arg.ionicStrength),
    kPrime(arg.kPrime),
    ph(arg.ph),
    pMg(arg.pMg),
    temperature(arg.temperature)
{
}

UniPAX::KPrime & UniPAX::KPrime::operator =(const KPrime & arg)  {
	UniPAX::UtilityClass::operator=(arg);
    ionicStrength = arg.ionicStrength;
    kPrime = arg.kPrime;
    ph = arg.ph;
    pMg = arg.pMg;
    temperature = arg.temperature;

	return *this;
 }

UniPAX::KPrime::~KPrime()  {
    }

bool UniPAX::KPrime::merge(KPrime& object)
{
	if (!object.getTemperature() != 0.)
	{
		if (!getTemperature() != 0.)
		{
			if (getTemperature() != object.getTemperature())
			{
				std::cerr << "Error during merging: UniPAX::KPrime::temperature not equal ..."
						<< getTemperature() << " != " << object.getTemperature() << std::endl;
				return false;
			}
		}
		else
			setTemperature(object.getTemperature());
	}

	if (!object.getPMg() != 0.)
	{
		if (!getPMg() != 0.)
		{
			if (getPMg() != object.getPMg())
			{
				std::cerr << "Error during merging: UniPAX::KPrime::pMg not equal ..."
						<< getPMg() << " != " << object.getPMg() << std::endl;
				return false;
			}
		}
		else
			setPMg(object.getPMg());
	}

	if (!object.getPh() != 0.)
	{
		if (!getPh() != 0.)
		{
			if (getPh() != object.getPh())
			{
				std::cerr << "Error during merging: UniPAX::KPrime::ph not equal ..."
						<< getPh() << " != " << object.getPh() << std::endl;
				return false;
			}
		}
		else
			setPh(object.getPh());
	}

	if (!object.getKPrime() != 0.)
	{
		if (!getKPrime() != 0.)
		{
			if (getKPrime() != object.getKPrime())
			{
				std::cerr << "Error during merging: UniPAX::KPrime::kPrime not equal ..."
						<< getKPrime() << " != " << object.getKPrime() << std::endl;
				return false;
			}
		}
		else
			setKPrime(object.getKPrime());
	}

	if (!object.getIonicStrength() != 0.)
	{
		if (!getIonicStrength() != 0.)
		{
			if (getIonicStrength() != object.getIonicStrength())
			{
				std::cerr << "Error during merging: UniPAX::KPrime::ionicStrength not equal ..."
						<< getIonicStrength() << " != " << object.getIonicStrength() << std::endl;
				return false;
			}
		}
		else
			setIonicStrength(object.getIonicStrength());
	}

	return UniPAX::UtilityClass::merge(object);
}

bool UniPAX::KPrime::update(PersistenceManager& manager)
{
	return UniPAX::UtilityClass::update(manager);
}


const double UniPAX::KPrime::getIonicStrength() const {
	return ionicStrength;
}

double UniPAX::KPrime::getIonicStrength()  {
        return ionicStrength;
}

void UniPAX::KPrime::setIonicStrength(double _ionicStrength)  {
        ionicStrength = _ionicStrength;
}

const double UniPAX::KPrime::getKPrime() const {
	return kPrime;
}

double UniPAX::KPrime::getKPrime()  {
        return kPrime;
}

void UniPAX::KPrime::setKPrime(double _kPrime)  {
        kPrime = _kPrime;
}

const double UniPAX::KPrime::getPh() const {
	return ph;
}

double UniPAX::KPrime::getPh()  {
        return ph;
}

void UniPAX::KPrime::setPh(double _ph)  {
        ph = _ph;
}

const double UniPAX::KPrime::getPMg() const {
	return pMg;
}

double UniPAX::KPrime::getPMg()  {
        return pMg;
}

void UniPAX::KPrime::setPMg(double _pMg)  {
        pMg = _pMg;
}

const double UniPAX::KPrime::getTemperature() const {
	return temperature;
}

double UniPAX::KPrime::getTemperature()  {
        return temperature;
}

void UniPAX::KPrime::setTemperature(double _temperature)  {
        temperature = _temperature;
}

bool UniPAX::KPrime::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::UtilityClass::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"temperature"))
	{
		return (PersistenceManager::convertAttribute(value,temperature));
	}
	if (boost::iequals(attribute,"pMg"))
	{
		return (PersistenceManager::convertAttribute(value,pMg));
	}
	if (boost::iequals(attribute,"ph"))
	{
		return (PersistenceManager::convertAttribute(value,ph));
	}
	if (boost::iequals(attribute,"kPrime"))
	{
		return (PersistenceManager::convertAttribute(value,kPrime));
	}
	if (boost::iequals(attribute,"ionicStrength"))
	{
		return (PersistenceManager::convertAttribute(value,ionicStrength));
	}

	return false;

}

bool UniPAX::KPrime::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::UtilityClass::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	if (!PersistenceManager::convertAttribute(temperature, tmp))
	{
		return false;
	}
	if (temperature != 0.)
		value.push_back(std::pair<std::string,std::string>("temperature", tmp));
	tmp.clear();
	if (!PersistenceManager::convertAttribute(pMg, tmp))
	{
		return false;
	}
	if (pMg != 0.)
		value.push_back(std::pair<std::string,std::string>("pMg", tmp));
	tmp.clear();
	if (!PersistenceManager::convertAttribute(ph, tmp))
	{
		return false;
	}
	if (ph != 0.)
		value.push_back(std::pair<std::string,std::string>("ph", tmp));
	tmp.clear();
	if (!PersistenceManager::convertAttribute(kPrime, tmp))
	{
		return false;
	}
	if (kPrime != 0.)
		value.push_back(std::pair<std::string,std::string>("kPrime", tmp));
	tmp.clear();
	if (!PersistenceManager::convertAttribute(ionicStrength, tmp))
	{
		return false;
	}
	if (ionicStrength != 0.)
		value.push_back(std::pair<std::string,std::string>("ionicStrength", tmp));


	return true;

}

//void UniPAX::KPrime::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	return;
//}

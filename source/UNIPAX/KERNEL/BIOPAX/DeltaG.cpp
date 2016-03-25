#include<UNIPAX/KERNEL/BIOPAX/DeltaG.h>
#include<set>
//Begin section for file DeltaG.cpp
//TODO: Add definitions that you want preserved
//End section for file DeltaG.cpp

UniPAX::DeltaG::DeltaG()  : UniPAX::UtilityClass(),
	deltaGPrime0(0.),
	ionicStrength(0.),
	ph(0.),
	pMg(0.),
	temperature(0.)
{
    }

UniPAX::DeltaG::DeltaG(const DeltaG& arg) : UniPAX::UtilityClass(arg) ,
    deltaGPrime0(arg.deltaGPrime0),
    ionicStrength(arg.ionicStrength),
    ph(arg.ph),
    pMg(arg.pMg),
    temperature(arg.temperature)
{
}

UniPAX::DeltaG & UniPAX::DeltaG::operator =(const DeltaG & arg)  {
	UniPAX::UtilityClass::operator=(arg);
    deltaGPrime0 = arg.deltaGPrime0;
    ionicStrength = arg.ionicStrength;
    ph = arg.ph;
    pMg = arg.pMg;
    temperature = arg.temperature;

	return *this;
}

UniPAX::DeltaG::~DeltaG()  {
    }

bool UniPAX::DeltaG::merge(DeltaG& object)
{
	if (!object.getTemperature() != 0.)
	{
		if (!getTemperature() != 0.)
		{
			if (getTemperature() != object.getTemperature())
			{
				std::cerr << "Error during merging: UniPAX::DeltaG::temperature not equal ..."
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
				std::cerr << "Error during merging: UniPAX::DeltaG::pMg not equal ..."
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
				std::cerr << "Error during merging: UniPAX::DeltaG::ph not equal ..."
						<< getPh() << " != " << object.getPh() << std::endl;
				return false;
			}
		}
		else
			setPh(object.getPh());
	}
	if (!object.getIonicStrength() != 0.)
	{
		if (!getIonicStrength() != 0.)
		{
			if (getIonicStrength() != object.getIonicStrength())
			{
				std::cerr << "Error during merging: UniPAX::DeltaG::ionicStrength not equal ..."
						<< getIonicStrength() << " != " << object.getIonicStrength() << std::endl;
				return false;
			}
		}
		else
			setIonicStrength(object.getIonicStrength());
	}
	if (!object.getDeltaGPrime0() != 0.)
	{
		if (!getDeltaGPrime0() != 0.)
		{
			if (getDeltaGPrime0() != object.getDeltaGPrime0())
			{
				std::cerr << "Error during merging: UniPAX::DeltaG::deltaGPrime0 not equal ..."
						<< getDeltaGPrime0() << " != " << object.getDeltaGPrime0() << std::endl;
				return false;
			}
		}
		else
			setDeltaGPrime0(object.getDeltaGPrime0());
	}

	return UniPAX::UtilityClass::merge(object);
}


bool UniPAX::DeltaG::update(PersistenceManager& manager)
{
	return UniPAX::UtilityClass::update(manager);
}

const double UniPAX::DeltaG::getDeltaGPrime0() const {
        return deltaGPrime0;
}

double UniPAX::DeltaG::getDeltaGPrime0() {
	return deltaGPrime0;
}

void UniPAX::DeltaG::setDeltaGPrime0(double _deltaGPrime0)  {
        deltaGPrime0 = _deltaGPrime0;
}

const double UniPAX::DeltaG::getIonicStrength() const {
	return ionicStrength;
}

double UniPAX::DeltaG::getIonicStrength()  {
        return ionicStrength;
}

void UniPAX::DeltaG::setIonicStrength(double _ionicStrength)  {
        ionicStrength = _ionicStrength;
}

const double UniPAX::DeltaG::getPh() const {
	return ph;
}

double UniPAX::DeltaG::getPh()  {
        return ph;
}

void UniPAX::DeltaG::setPh(double _ph)  {
        ph = _ph;
}

const double UniPAX::DeltaG::getPMg() const {
	return pMg;
}

double UniPAX::DeltaG::getPMg()  {
        return pMg;
}

void UniPAX::DeltaG::setPMg(double _pMg)  {
        pMg = _pMg;
}

const double UniPAX::DeltaG::getTemperature() const {
	return temperature;
}

double UniPAX::DeltaG::getTemperature()  {
        return temperature;
}

void UniPAX::DeltaG::setTemperature(double _temperature)  {
        temperature = _temperature;
}

bool UniPAX::DeltaG::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

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
	if (boost::iequals(attribute,"ionicStrength"))
	{
		return (PersistenceManager::convertAttribute(value,ionicStrength));
	}
	if (boost::iequals(attribute,"deltaGPrime0"))
	{
		return (PersistenceManager::convertAttribute(value,deltaGPrime0));
	}

	return false;

}

bool UniPAX::DeltaG::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

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
	if (!PersistenceManager::convertAttribute(ionicStrength, tmp))
	{
		return false;
	}
	if (ionicStrength != 0.)
		value.push_back(std::pair<std::string,std::string>("ionicStrength", tmp));
	tmp.clear();
	if (!PersistenceManager::convertAttribute(deltaGPrime0, tmp))
	{
		return false;
	}
	if (deltaGPrime0 != 0.)
		value.push_back(std::pair<std::string,std::string>("deltaGPrime0", tmp));
	tmp.clear();

	return true;

}

//
//void UniPAX::DeltaG::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::UtilityClass::init(e,db);
//
//	return;
//}

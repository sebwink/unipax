#include<UNIPAX/KERNEL/EXT/KineticLaw.h>
//Begin section for file KineticLaw.cpp
//TODO: Add definitions that you want preserved
//End section for file KineticLaw.cpp

UniPAX::KineticLaw::KineticLaw() : UniPAX::SBase()
		//, conversion(0),
//		id_conversion(0)

{
}

UniPAX::KineticLaw::KineticLaw(const KineticLaw& arg) : UniPAX::SBase(arg) ,
		localParameter(arg.localParameter),
		conversion(arg.conversion)
//		id_conversion(arg.id_conversion)
{
}

UniPAX::KineticLaw & UniPAX::KineticLaw::operator =(const KineticLaw & arg)  {
		UniPAX::SBase::operator=(arg);
		localParameter = arg.localParameter;
		conversion = arg.conversion;
//		id_conversion = arg.id_conversion;

		return *this;
}

UniPAX::KineticLaw::~KineticLaw()  {
}

bool UniPAX::KineticLaw::merge(KineticLaw& object)
{

		if (conversion != 0)
		{
				if (object.getConversion() != 0)
				{
						if (conversion->getUnipaxId() != object.getConversion()->getUnipaxId())
						{
								std::cerr << "Error during merging: UniPAX::KineticLaw::conversion not equal ..."
										<< conversion->getUnipaxId() << " != " << object.getConversion()->getUnipaxId() << std::endl;
								return false;
						}
				}
		}
		else
		{
				setConversion(object.getConversion());
		}

		// merge localParameters
		{
				std::vector<boost::shared_ptr<UniPAX::LocalParameter> >::iterator it;
				for (it = object.getLocalParameters().begin(); it != object.getLocalParameters().end(); it++)
				{
						if (*it != 0)
						{
								localParameter.push_back(*it);
						}
				}
		}

		return UniPAX::SBase::merge(object);
}

bool UniPAX::KineticLaw::update(PersistenceManager& manager)
{
		{
				// run through vector to check each pointer
				std::vector<boost::shared_ptr<UniPAX::LocalParameter> > tmp_vec;
				std::vector<boost::shared_ptr<UniPAX::LocalParameter> >::iterator it;
				for (it = localParameter.begin(); it != localParameter.end(); it++)
				{
						if (manager.isMerged(*it))
								tmp_vec.push_back(boost::dynamic_pointer_cast<LocalParameter>(manager.getMergedObject(*it)));
						else
								tmp_vec.push_back(*it);
				}
				setLocalParameters(tmp_vec);
		}
		// check single pointer if object was merged
		if (manager.isMerged(getConversion()))
		{
				setConversion(boost::dynamic_pointer_cast<UniPAX::Conversion>(manager.getMergedObject(getConversion())));
		}

		return UniPAX::SBase::update(manager);
}

const std::vector<boost::shared_ptr<UniPAX::LocalParameter> > UniPAX::KineticLaw::getLocalParameters() const {
		return localParameter;
}

std::vector<boost::shared_ptr<UniPAX::LocalParameter> > UniPAX::KineticLaw::getLocalParameters()  {
		return localParameter;
}

void UniPAX::KineticLaw::setLocalParameters(std::vector<boost::shared_ptr<UniPAX::LocalParameter> > _localParameters)  {
		localParameter = _localParameters;
}
void UniPAX::KineticLaw::addLocalParameter(boost::shared_ptr<UniPAX::LocalParameter >  _localParameter)  {
		localParameter.push_back(_localParameter);
}


const boost::shared_ptr<UniPAX::Conversion> UniPAX::KineticLaw::getConversion() const {
		return conversion;
}

boost::shared_ptr<UniPAX::Conversion> UniPAX::KineticLaw::getConversion()  {
		return conversion;
}

void UniPAX::KineticLaw::setConversion(boost::shared_ptr<UniPAX::Conversion> _conversion)  {
		conversion = _conversion;
}


bool UniPAX::KineticLaw::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

		if (UniPAX::SBase::setAttribute(attribute, value, manager))
				return true;

		if (boost::iequals(attribute,"localParameter"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "KineticLaw::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				localParameter.push_back(boost::dynamic_pointer_cast<UniPAX::LocalParameter>(object));
				return true;
		}

		if (boost::iequals(attribute,"conversion"))
		{
				// if sometimes set to NIL or empty string neglect
				if (value == "NIL" || value.empty())
						return true;

				boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
				if (object == 0)
				{
						std::cerr << "KineticLaw::setAttribute - object not known (value = " << value << ")" << std::endl;
						return false;
				}

				conversion = boost::dynamic_pointer_cast<UniPAX::Conversion>(object);
				return true;
		}

		return false;

}

bool UniPAX::KineticLaw::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

		if (!UniPAX::SBase::getAttribute(value, manager))
				return false;

		std::string tmp = "";
		{
				std::vector<boost::shared_ptr<UniPAX::LocalParameter> >::iterator it;
				for (it = localParameter.begin(); it != localParameter.end(); it++)
				{
						if (*it == 0)
						{
								//			value.push_back(std::pair<std::string,std::string>("#xref", "NIL"));
						}
						else
						{
								tmp.clear();
								if (!manager.getId(*it,tmp))
								{
										manager.setError(this->type() + ":localParameter contains unknown reference.");
										return false;
								}
								value.push_back(std::pair<std::string,std::string>("#localParameter", tmp));
						}
				}
		}
		tmp.clear();

		if (conversion == 0)
		{
				//		value.push_back(std::pair<std::string,std::string>("#conversion", "NIL"));
		}
		else
		{
				tmp.clear();
				if (!manager.getId(conversion,tmp))
				{
						manager.setError(this->type() + ":conversion contains unknown reference.");
						return false;
				}
				value.push_back(std::pair<std::string,std::string>("#conversion", tmp));

		}

		return true;
}


//void UniPAX::KineticLaw::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::SBase::init(e,db);
//
//		if (e == odb::callback_event::post_load)
//		{
//				// load the object pointer
//				conversion = boost::dynamic_pointer_cast<UniPAX::Conversion>(getObjectByID(db, id_conversion));
//
//		}
//		else if ((e == odb::callback_event::pre_persist) || (e == odb::callback_event::pre_update))
//		{
//				// set the object ids
//				if (conversion != 0)
//						id_conversion = conversion->getUnipaxId();
//		}
//
//		return;
//}

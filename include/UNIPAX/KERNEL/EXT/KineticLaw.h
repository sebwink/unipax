#ifndef KINETICLAW_H
#define KINETICLAW_H
//Begin section for file KineticLaw.h
//TODO: Add definitions that you want preserved
#include<string>
#include<vector>
//End section for file KineticLaw.h
#include<UNIPAX/KERNEL/EXT/SBase.h>
#include<UNIPAX/KERNEL/EXT/LocalParameter.h>
#include<UNIPAX/KERNEL/BIOPAX/Conversion.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

class LocalParameter;
class Conversion;

#pragma db object polymorphic
class UNIPAX_EXPORT KineticLaw : public SBase {

protected:

	std::vector<UnipaxPtr<LocalParameter>::type > localParameter;

	//unsigned long long id_conversion;
	//#pragma db transient
	UnipaxPtr<Conversion>::type conversion;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "KineticLaw";
	}

	static std::string type() {
		return std::string("KineticLaw");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idKineticLaw;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idKineticLaw;
	}

	KineticLaw();

	KineticLaw(const KineticLaw & arg);

	KineticLaw & operator =(const KineticLaw & arg);

	~KineticLaw();

	bool merge(KineticLaw& object);

	bool update(PersistenceManager& manager);

	const std::vector<UnipaxPtr<LocalParameter>::type >  getLocalParameters() const;

	//get localParameter
	std::vector<UnipaxPtr<LocalParameter>::type >  getLocalParameters();

	//set localParameter
	void setLocalParameters(std::vector<UnipaxPtr<LocalParameter>::type > _localParameters);

	void addLocalParameter(boost::shared_ptr<LocalParameter >  _localParameter);


	const boost::shared_ptr<Conversion > getConversion() const;

	//get conversion
	boost::shared_ptr<Conversion > getConversion();

	//set conversion
	void setConversion(boost::shared_ptr<Conversion > _conversion);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class KineticLaw

typedef UnipaxPtr<KineticLaw>::type KineticLawPtr;

}//end namespace UniPAX

#endif

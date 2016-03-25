#ifndef EXPERIMENTALFORM_H
#define EXPERIMENTALFORM_H
//Begin section for file ExperimentalForm.h
//TODO: Add definitions that you want preserved
//End section for file ExperimentalForm.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/EntityFeature.h>
#include<UNIPAX/KERNEL/BIOPAX/ExperimentalFormVocabulary.h>
#include<UNIPAX/KERNEL/BIOPAX/Entity.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

class Entity;
class EntityFeature;
class ExperimentalFormVocabulary;

#pragma db object polymorphic
class UNIPAX_EXPORT ExperimentalForm : public UtilityClass {

protected:

	// std::vector<unsigned long long> id_experimentalFormEntity;
	//#pragma db transient
	std::vector<UnipaxPtr<Entity>::type > experimentalFormEntity;

	// std::vector<unsigned long long> id_experimentalFeature;
	//#pragma db transient
	std::vector<UnipaxPtr<EntityFeature>::type > experimentalFeature;

	std::vector<UnipaxPtr<ExperimentalFormVocabulary>::type > experimentalFormDescription;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "ExperimentalForm";
	}

	static std::string type() {
		return std::string("ExperimentalForm");
	}


	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idExperimentalForm;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idExperimentalForm;
	}

	ExperimentalForm();

	ExperimentalForm(const ExperimentalForm & arg);

	ExperimentalForm & operator =(const ExperimentalForm & arg);

	~ExperimentalForm();

	bool merge(ExperimentalForm& object);
	bool update(PersistenceManager& manager);


	//get experimentalFeature
	const std::vector<UnipaxPtr<EntityFeature>::type > & getExperimentalFeatures() const;

	std::vector<UnipaxPtr<EntityFeature>::type > & getExperimentalFeatures();

	void setExperimentalFeatures(std::vector<UnipaxPtr<EntityFeature>::type > _experimentalFeatures);

	void addExperimentalFeature(UnipaxPtr<EntityFeature>::type  _experimentalFeature);


	//get experimentalFormDescription
	const std::vector<UnipaxPtr<ExperimentalFormVocabulary>::type > & getExperimentalFormDescriptions() const;

	std::vector<UnipaxPtr<ExperimentalFormVocabulary>::type > & getExperimentalFormDescriptions();

	void setExperimentalFormDescriptions(std::vector<UnipaxPtr<ExperimentalFormVocabulary>::type > _experimentalFormDescriptions);

	void addExperimentalFormDescription(UnipaxPtr<ExperimentalFormVocabulary>::type  _experimentalFormDescription);


	//get experimentalFormEntity
	std::vector<UnipaxPtr<Entity>::type > & getExperimentalFormEntitys();

	const std::vector<UnipaxPtr<Entity>::type > & getExperimentalFormEntitys() const;

	//set experimentalFormEntity
	void setExperimentalFormEntitys(std::vector<UnipaxPtr<Entity>::type > _experimentalFormEntitys);

	void addExperimentalFormEntity(UnipaxPtr<Entity>::type  _experimentalFormEntity);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef UtilityClass super;

};  //end class ExperimentalForm

typedef UnipaxPtr<ExperimentalForm>::type ExperimentalFormPtr;

}//end namespace UniPAX

#endif

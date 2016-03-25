#ifndef EXPERIMENT_H
#define EXPERIMENT_H
//Begin section for file Experiment.h
//TODO: Add definitions that you want preserved
#include<string>
#include<vector>
//End section for file Experiment.h
#include<UNIPAX/KERNEL/EXT/UPBase.h>
#include<UNIPAX/KERNEL/EXT/Sample.h>
#include<UNIPAX/KERNEL/EXT/IdMapping.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Experiment : public UPBase {

protected:

	int experimentId;

	std::string name;

	std::string shortDescription;

	std::string source;

	std::string user;

	std::string metaInfos;

	int valuesPerSample;

	std::string defaultMapping;

	std::vector<IdMappingPtr> mapping;

	std::vector<SamplePtr> sample;



	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Experiment";
	}

	static std::string type() {
		return std::string("Experiment");
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idExperiment;
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idExperiment;
	}

	Experiment();

	Experiment(const Experiment & arg);

	Experiment & operator =(const Experiment & arg);

	~Experiment();

	bool merge(Experiment& object);

	bool update(PersistenceManager& manager);

	const int getExperimentId() const;

	//get experimentId
	int getExperimentId();

	//set experimentId
	void setExperimentId(int _experimentId);

	//get name
	const std::string & getName() const;

	std::string & getName();

	void setName(std::string _name);

	//get shortDescription
	const std::string & getShortDescription() const;

	std::string & getShortDescription();

	void setShortDescription(std::string _shortDescription);

	//get source
	const std::string & getSource() const;

	std::string & getSource();

	void setSource(std::string _source);

	//get user
	const std::string & getUser() const;

	std::string & getUser();

	void setUser(std::string _user);

	//get metaInfos
	const std::string & getMetaInfos() const;

	std::string & getMetaInfos();

	void setMetaInfos(std::string _metaInfos);

	const int getValuesPerSample() const;

	//get valuesPerSample
	int getValuesPerSample();

	//set valuesPerSample
	void setValuesPerSample(int _valuesPerSample);

	//get defaultMapping
	const std::string & getDefaultMapping() const;

	std::string & getDefaultMapping();

	void setDefaultMapping(std::string _defaultMapping);

	const std::vector<IdMappingPtr> & getMappings() const;

	//get mapping
	std::vector<IdMappingPtr> & getMappings();

	//set mapping
	void setMappings(std::vector<IdMappingPtr> _mappings);
	void addMapping(IdMappingPtr _mapping);

	const std::vector<SamplePtr> & getSamples() const;

	//get sample
	std::vector<SamplePtr > & getSamples();

	//set sample
	void setSamples(std::vector<SamplePtr> _samples);
	void addSample(SamplePtr _sample);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

};  //end class Experiment

typedef UnipaxPtr<Experiment>::type ExperimentPtr;

}//end namespace UniPAX

#endif

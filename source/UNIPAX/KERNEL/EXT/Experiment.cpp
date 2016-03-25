#include<UNIPAX/KERNEL/EXT/Experiment.h>
//Begin section for file Experiment.cpp
//TODO: Add definitions that you want preserved
//End section for file Experiment.cpp


UniPAX::Experiment::Experiment() : UniPAX::UPBase() {
}

UniPAX::Experiment::Experiment(const Experiment & arg) : UniPAX::UPBase(arg),
		experimentId(arg.experimentId),
		name(arg.name),
		shortDescription(arg.shortDescription),
		source(arg.source),
		user(arg.user),
		metaInfos(arg.metaInfos),
		valuesPerSample(arg.valuesPerSample),
		mapping(arg.mapping),
		sample(arg.sample)
{
}

UniPAX::Experiment& UniPAX::Experiment::operator =(const Experiment& arg) {

		UniPAX::UPBase::operator=(arg);

		experimentId = arg.experimentId;
		name = arg.name;
		shortDescription = arg.shortDescription;
		source = arg.source;
		user = arg.user;
		metaInfos = arg.metaInfos;
		valuesPerSample = arg.valuesPerSample;
		mapping = arg.mapping;
		sample = arg.sample;

		return *this;
}


UniPAX::Experiment::~Experiment()  {
}

bool UniPAX::Experiment::merge(Experiment& object)
{
		std::cerr << "Error during merging: UniPAX::Experiment should not be merged." << std::endl;
		return UniPAX::UPBase::merge(object);
}

bool UniPAX::Experiment::update(PersistenceManager& manager)
{

	{
                std::vector<UniPAX::IdMappingPtr> tmp_vec;
                std::vector<UniPAX::IdMappingPtr>::iterator it;
		for (it = mapping.begin(); it != mapping.end(); it++)
		{
			if (manager.isMerged(*it))
                                tmp_vec.push_back(boost::dynamic_pointer_cast<IdMapping>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setMappings(tmp_vec);
	}
	{
		std::vector<UniPAX::SamplePtr> tmp_vec;
		std::vector<UniPAX::SamplePtr>::iterator it;
		for (it = sample.begin(); it != sample.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Sample>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setSamples(tmp_vec);
	}

	return UniPAX::UPBase::update(manager);
}

const int UniPAX::Experiment::getExperimentId() const {
		return experimentId;
}

int UniPAX::Experiment::getExperimentId()  {
		return experimentId;
}

void UniPAX::Experiment::setExperimentId(int _experimentId)  {
		experimentId = _experimentId;
}

const std::string & UniPAX::Experiment::getName() const {
		return name;
}

std::string & UniPAX::Experiment::getName() {
		return name; 
}

void UniPAX::Experiment::setName(std::string _name) {
		name = _name;
}

const std::string & UniPAX::Experiment::getShortDescription() const {
		return shortDescription;
}

std::string & UniPAX::Experiment::getShortDescription() {
		return shortDescription;
}

void UniPAX::Experiment::setShortDescription(std::string _shortDescription) {
		shortDescription = _shortDescription;
}

const std::string & UniPAX::Experiment::getSource() const {
		return source;
}

std::string & UniPAX::Experiment::getSource() {
		return source;
}

void UniPAX::Experiment::setSource(std::string _source) {
		source = _source;
}

const std::string & UniPAX::Experiment::getUser() const {
		return user;
}

std::string & UniPAX::Experiment::getUser() {
		return user;
}

void UniPAX::Experiment::setUser(std::string _user) {
		user = _user;
}

const std::string & UniPAX::Experiment::getMetaInfos() const {
		return metaInfos;
}

std::string & UniPAX::Experiment::getMetaInfos() {
		return metaInfos;
}

void UniPAX::Experiment::setMetaInfos(std::string _metaInfos) {
		metaInfos = _metaInfos;
}

const int UniPAX::Experiment::getValuesPerSample() const {
		return valuesPerSample;
}

int UniPAX::Experiment::getValuesPerSample()  {
		return valuesPerSample;
}

void UniPAX::Experiment::setValuesPerSample(int _valuesPerSample)  {
		valuesPerSample = _valuesPerSample;
}

const std::string & UniPAX::Experiment::getDefaultMapping() const {
		return defaultMapping;
}

std::string & UniPAX::Experiment::getDefaultMapping() {
		return defaultMapping;
}

void UniPAX::Experiment::setDefaultMapping(std::string _defaultMapping) {
		defaultMapping = _defaultMapping;
}

const std::vector<UniPAX::IdMappingPtr> & UniPAX::Experiment::getMappings() const {
		return mapping;
}

std::vector<UniPAX::IdMappingPtr> & UniPAX::Experiment::getMappings()  {
		return mapping;
}

void UniPAX::Experiment::setMappings(std::vector<UniPAX::IdMappingPtr> _mappings)  {
		mapping = _mappings;
}

void UniPAX::Experiment::addMapping(UniPAX::IdMappingPtr _mapping)  {
		mapping.push_back(_mapping);
}

const std::vector<UniPAX::SamplePtr> & UniPAX::Experiment::getSamples() const {
		return sample;
}

std::vector<UniPAX::SamplePtr> & UniPAX::Experiment::getSamples()  {
		return sample;
}

void UniPAX::Experiment::setSamples(std::vector<UniPAX::SamplePtr> _samples)  {
		sample = _samples;
}

void UniPAX::Experiment::addSample(UniPAX::SamplePtr _sample)  {
		sample.push_back(_sample);
}


bool UniPAX::Experiment::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

		return false;
}

bool UniPAX::Experiment::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

		return true;
}

//void UniPAX::Experiment::init (odb::callback_event e, odb::database& db) const
//{
//		UniPAX::UPBase::init(e,db);
//
//		return;
//}

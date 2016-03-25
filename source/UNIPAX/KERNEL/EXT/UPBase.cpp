#include<UNIPAX/KERNEL/EXT/UPBase.h>

#include<memory>

#include<UNIPAX/COMMON/PersistenceManager.h>
#ifdef ODB_ORACLE
#include<odb/oracle/database.hxx>
#include<UNIPAX/PERSISTENCE/ORACLE/all.h>
#endif

#ifdef ODB_MYSQL
#include<odb/mysql/database.hxx>
#include<UNIPAX/PERSISTENCE/MYSQL/all.h>
#endif

#include<UNIPAX/KERNEL/all.h>

UniPAX::UPBase::UPBase() : unipaxId(0.) {
}

UniPAX::UPBase::UPBase(const UniPAX::UPBase & arg) : unipaxId(arg.unipaxId)
{
}

UniPAX::UPBase & UniPAX::UPBase::operator =(const UniPAX::UPBase & arg)  {

	unipaxId = arg.unipaxId;
	return *this;
}

bool UniPAX::UPBase::equals(UniPAX::UPBase & arg, PersistenceManager& manager) {
	if (getTypeID() != arg.getTypeID())
	{	// different types
		return false;
	}
	typedef std::vector<std::pair<std::string, std::string> > TagValueVec;
	TagValueVec attr1, attr2;
	if (!getAttribute(attr1, manager) || !arg.getAttribute(attr2, manager))
	{	// cannot retrieve attributes
		return false;
	}
	if (attr1.size() != attr2.size())
	{	// different amount of attributes
		return false;
	}
	TagValueVec::const_iterator it1, it2;
	for (it1=attr1.begin(), it2=attr2.begin(); it1 != attr1.end(); ++it1, ++it2)
	{
		if (it1->second != it2->second)
		{	// different value for a attribute
			return false;
		}
	}
	// otherwise objects can be considered equal
	return true;
}

UniPAX::UPBase::~UPBase()  {
}

const UnipaxId UniPAX::UPBase::getUnipaxId() const {
	return unipaxId;
}


bool UniPAX::UPBase::merge(UPBase& object)
{
	// unipaxSource cannot be merged since merging means unifying of objects from potentially different sources!!!
	return true;
}

bool UniPAX::UPBase::update(PersistenceManager& manager)
{
	return true;
}

std::string UniPAX::UPBase::getType()
{
	return "UPBase";
}

UniPAX::ClassType::ID UniPAX::UPBase::getTypeID()
{
	return UniPAX::ClassType::END_ENUM;
}



//get unipaxId
UnipaxId UniPAX::UPBase::getUnipaxId() {
	return unipaxId;
}

//set unipaxId
void UniPAX::UPBase::setUnipaxId(UnipaxId _unipaxId) {
	unipaxId=_unipaxId;
}

bool UniPAX::UPBase::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {
//	if (boost::iequals(attribute,"unipaxSource"))
//	{
//		// if sometimes set to NIL or empty string neglect
//		if (value == "NIL" || value.empty())
//			return true;
//
//		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value);
//		if (object == 0)
//		{
//			std::cerr << "SBase::setAttribute - object not known (value = " << value << ")" << std::endl;
//			return false;
//		}
//
//		//unipaxSource = boost::dynamic_pointer_cast<UniPAX::ImportSource>(object);
//		return true;
//	}

	return false;
}


bool UniPAX::UPBase::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

//	if (unipaxSource == 0)
//	{
//		//		value.push_back(std::pair<std::string,std::string>("#unipaxSource", "NIL"));
//	}
//	else
//	{
//		std::string tmp;
//		//tmp.clear();
//		if (!manager.getId(unipaxSource,tmp))
//		{
//			return false;
//		}
//		value.push_back(std::pair<std::string,std::string>("#unipaxSource", tmp));
//
//	}

	return true;

}

//
//void UniPAX::UPBase::init (odb::callback_event e, odb::database& db) const const
//{
//	std::cout << "Init " << getType() << std::endl;
//
//	return;
//}

//boost::shared_ptr<UniPAX::UPBase> UniPAX::UPBase::getObjectByID(odb::database& odb_db, UnipaxId id)
//{
//
//	if (id == 0)
//		return boost::shared_ptr<UniPAX::UPBase>();
//
//	try
//	{
//
//		// BioPAX
//		if ((id >> 24) == UniPAX::ClassType::idBindingFeature) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::BindingFeature>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idBioSource) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::BioSource>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idBiochemicalPathwayStep) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::BiochemicalPathwayStep>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idBiochemicalReaction) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::BiochemicalReaction>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idCatalysis) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Catalysis>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idCellVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::CellVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idCellularLocationVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::CellularLocationVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idChemicalStructure) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::ChemicalStructure>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idComplex) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Complex>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idComplexAssembly) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::ComplexAssembly>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idControl) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Control>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idControlledVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::ControlledVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idConversion) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Conversion>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idCovalentBindingFeature) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::CovalentBindingFeature>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idDegradation) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Degradation>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idDeltaG) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::DeltaG>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idDna) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Dna>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idDnaReference) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::DnaReference>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idDnaRegion) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::DnaRegion>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idDnaRegionReference) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::DnaRegionReference>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idEntity) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Entity>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idEntityFeature) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::EntityFeature>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idEntityReference) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::EntityReference>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idEntityReferenceTypeVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::EntityReferenceTypeVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idEvidence) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Evidence>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idEvidenceCodeVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::EvidenceCodeVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idExperimentalForm) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::ExperimentalForm>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idExperimentalFormVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::ExperimentalFormVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idFragmentFeature) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::FragmentFeature>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idGene) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Gene>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idGeneticInteraction) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::GeneticInteraction>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idInteraction) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Interaction>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idInteractionVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::InteractionVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idKPrime) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::KPrime>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idModificationFeature) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::ModificationFeature>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idModulation) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Modulation>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idMolecularInteraction) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::MolecularInteraction>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idPathway) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Pathway>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idPathwayStep) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::PathwayStep>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idPhenotypeVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::PhenotypeVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idPhysicalEntity) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::PhysicalEntity>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idProtein) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Protein>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idProteinReference) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::ProteinReference>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idProvenance) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Provenance>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idPublicationXref) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::PublicationXref>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idRelationshipTypeVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::RelationshipTypeVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idRelationshipXref) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::RelationshipXref>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idRna) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Rna>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idRnaReference) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::RnaReference>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idRnaRegion) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::RnaRegion>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idRnaRegionReference) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::RnaRegionReference>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idScore) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Score>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idSequenceInterval) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::SequenceInterval>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idSequenceLocation) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::SequenceLocation>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idSequenceModificationVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::SequenceModificationVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idSequenceRegionVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::SequenceRegionVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idSequenceSite) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::SequenceSite>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idSmallMolecule) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::SmallMolecule>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idSmallMoleculeReference) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::SmallMoleculeReference>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idStoichiometry) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Stoichiometry>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idTemplateReaction) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::TemplateReaction>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idTemplateReactionRegulation) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::TemplateReactionRegulation>(id));
//		//else if ((id >> 24) == UniPAX::ClassType::idThing) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Thing>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idTissueVocabulary) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::TissueVocabulary>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idTransport) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Transport>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idTransportWithBiochemicalReaction) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::TransportWithBiochemicalReaction>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idUnificationXref) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::UnificationXref>(id));
//		//else if ((id >> 24) == UniPAX::ClassType::idUtilityClass) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::UtilityClass>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idXref) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Xref>(id));
//
//
//		// EXT
//		else if ((id >> 24) == UniPAX::ClassType::idAlgebraicRule) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::AlgebraicRule>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idAssignmentRule) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::AssignmentRule>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idConstraint) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Constraint>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idDelay) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Delay>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idEventAssignment) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::EventAssignment>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idEvent) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Event>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idExperiment) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Experiment>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idFunctionDefinition) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::FunctionDefinition>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idIdMapping) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::IdMapping>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idImportSource) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::ImportSource>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idInitialAssignment) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::InitialAssignment>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idKineticLaw) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::KineticLaw>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idLocalParameter) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::LocalParameter>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idMath) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Math>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idModel) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Model>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idParameter) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Parameter>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idPriority) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Priority>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idRateRule) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::RateRule>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idResultObject) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::ResultObject>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idRule) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Rule>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idSample) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Sample>(id));
//		//else if ((id >> 24) == UniPAX::ClassType::idSBase) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::SBase>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idSeries) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Series>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idTrigger) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Trigger>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idUnitDefinition) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::UnitDefinition>(id));
//		else if ((id >> 24) == UniPAX::ClassType::idUnit) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::Unit>(id));
//		//else if ((id >> 24) == UniPAX::ClassType::idUPBase) return boost::dynamic_pointer_cast<UniPAX::UPBase>(odb_db.load<UniPAX::UPBase>(id));
//	}
//	catch (const odb::exception& e)
//	{
//		std::cerr << "UPBase::getObjectByID: odb_exception - " << e.what() << std::endl;
//		std::cerr << "                       id - " << id << std::endl;
//		std::cerr << "                       type - " << ((int)(id >> 24)) << std::endl;
//	}
//
//	return boost::shared_ptr<UniPAX::UPBase>();
//}

boost::shared_ptr<UniPAX::UPBase> UniPAX::UPBase::dynamic_copy()
{

//	if (this->getTypeID() == UniPAX::ClassType::idUPBase)
//		return boost::shared_ptr<UniPAX::UPBase>(new UniPAX::UPBase(*(dynamic_cast<UniPAX::UPBase*>(this))));
	// BioPAX
	if (this->getTypeID() == UniPAX::ClassType::idBindingFeature)
		return boost::shared_ptr<UniPAX::BindingFeature>(new UniPAX::BindingFeature(*(dynamic_cast<UniPAX::BindingFeature*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idBioSource)
		return boost::shared_ptr<UniPAX::BioSource>(new UniPAX::BioSource(*(dynamic_cast<UniPAX::BioSource*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idBiochemicalPathwayStep)
		return boost::shared_ptr<UniPAX::BiochemicalPathwayStep>(new UniPAX::BiochemicalPathwayStep(*(dynamic_cast<UniPAX::BiochemicalPathwayStep*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idBiochemicalReaction)
		return boost::shared_ptr<UniPAX::BiochemicalReaction>(new UniPAX::BiochemicalReaction(*(dynamic_cast<UniPAX::BiochemicalReaction*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idCatalysis)
		return boost::shared_ptr<UniPAX::Catalysis>(new UniPAX::Catalysis(*(dynamic_cast<UniPAX::Catalysis*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idCellVocabulary)
		return boost::shared_ptr<UniPAX::CellVocabulary>(new UniPAX::CellVocabulary(*(dynamic_cast<UniPAX::CellVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idCellularLocationVocabulary)
		return boost::shared_ptr<UniPAX::CellularLocationVocabulary>(new UniPAX::CellularLocationVocabulary(*(dynamic_cast<UniPAX::CellularLocationVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idChemicalStructure)
		return boost::shared_ptr<UniPAX::ChemicalStructure>(new UniPAX::ChemicalStructure(*(dynamic_cast<UniPAX::ChemicalStructure*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idComplex)
		return boost::shared_ptr<UniPAX::Complex>(new UniPAX::Complex(*(dynamic_cast<UniPAX::Complex*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idComplexAssembly)
		return boost::shared_ptr<UniPAX::ComplexAssembly>(new UniPAX::ComplexAssembly(*(dynamic_cast<UniPAX::ComplexAssembly*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idControl)
		return boost::shared_ptr<UniPAX::Control>(new UniPAX::Control(*(dynamic_cast<UniPAX::Control*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idControlledVocabulary)
		return boost::shared_ptr<UniPAX::ControlledVocabulary>(new UniPAX::ControlledVocabulary(*(dynamic_cast<UniPAX::ControlledVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idConversion)
		return boost::shared_ptr<UniPAX::Conversion>(new UniPAX::Conversion(*(dynamic_cast<UniPAX::Conversion*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idCovalentBindingFeature)
		return boost::shared_ptr<UniPAX::CovalentBindingFeature>(new UniPAX::CovalentBindingFeature(*(dynamic_cast<UniPAX::CovalentBindingFeature*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idDegradation)
		return boost::shared_ptr<UniPAX::Degradation>(new UniPAX::Degradation(*(dynamic_cast<UniPAX::Degradation*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idDeltaG)
		return boost::shared_ptr<UniPAX::DeltaG>(new UniPAX::DeltaG(*(dynamic_cast<UniPAX::DeltaG*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idDna)
		return boost::shared_ptr<UniPAX::Dna>(new UniPAX::Dna(*(dynamic_cast<UniPAX::Dna*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idDnaReference)
		return boost::shared_ptr<UniPAX::DnaReference>(new UniPAX::DnaReference(*(dynamic_cast<UniPAX::DnaReference*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idDnaRegion)
		return boost::shared_ptr<UniPAX::DnaRegion>(new UniPAX::DnaRegion(*(dynamic_cast<UniPAX::DnaRegion*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idDnaRegionReference)
		return boost::shared_ptr<UniPAX::DnaRegionReference>(new UniPAX::DnaRegionReference(*(dynamic_cast<UniPAX::DnaRegionReference*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idEntity)
		return boost::shared_ptr<UniPAX::Entity>(new UniPAX::Entity(*(dynamic_cast<UniPAX::Entity*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idEntityFeature)
		return boost::shared_ptr<UniPAX::EntityFeature>(new UniPAX::EntityFeature(*(dynamic_cast<UniPAX::EntityFeature*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idEntityReference)
		return boost::shared_ptr<UniPAX::EntityReference>(new UniPAX::EntityReference(*(dynamic_cast<UniPAX::EntityReference*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idEntityReferenceTypeVocabulary)
		return boost::shared_ptr<UniPAX::EntityReferenceTypeVocabulary>(new UniPAX::EntityReferenceTypeVocabulary(*(dynamic_cast<UniPAX::EntityReferenceTypeVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idEvidence)
		return boost::shared_ptr<UniPAX::Evidence>(new UniPAX::Evidence(*(dynamic_cast<UniPAX::Evidence*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idEvidenceCodeVocabulary)
		return boost::shared_ptr<UniPAX::EvidenceCodeVocabulary>(new UniPAX::EvidenceCodeVocabulary(*(dynamic_cast<UniPAX::EvidenceCodeVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idExperimentalForm)
		return boost::shared_ptr<UniPAX::ExperimentalForm>(new UniPAX::ExperimentalForm(*(dynamic_cast<UniPAX::ExperimentalForm*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idExperimentalFormVocabulary)
		return boost::shared_ptr<UniPAX::ExperimentalFormVocabulary>(new UniPAX::ExperimentalFormVocabulary(*(dynamic_cast<UniPAX::ExperimentalFormVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idFragmentFeature)
		return boost::shared_ptr<UniPAX::FragmentFeature>(new UniPAX::FragmentFeature(*(dynamic_cast<UniPAX::FragmentFeature*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idGene)
		return boost::shared_ptr<UniPAX::Gene>(new UniPAX::Gene(*(dynamic_cast<UniPAX::Gene*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idGeneticInteraction)
		return boost::shared_ptr<UniPAX::GeneticInteraction>(new UniPAX::GeneticInteraction(*(dynamic_cast<UniPAX::GeneticInteraction*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idInteraction)
		return boost::shared_ptr<UniPAX::Interaction>(new UniPAX::Interaction(*(dynamic_cast<UniPAX::Interaction*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idInteractionVocabulary)
		return boost::shared_ptr<UniPAX::InteractionVocabulary>(new UniPAX::InteractionVocabulary(*(dynamic_cast<UniPAX::InteractionVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idKPrime)
		return boost::shared_ptr<UniPAX::KPrime>(new UniPAX::KPrime(*(dynamic_cast<UniPAX::KPrime*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idModificationFeature)
		return boost::shared_ptr<UniPAX::ModificationFeature>(new UniPAX::ModificationFeature(*(dynamic_cast<UniPAX::ModificationFeature*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idModulation)
		return boost::shared_ptr<UniPAX::Modulation>(new UniPAX::Modulation(*(dynamic_cast<UniPAX::Modulation*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idMolecularInteraction)
		return boost::shared_ptr<UniPAX::MolecularInteraction>(new UniPAX::MolecularInteraction(*(dynamic_cast<UniPAX::MolecularInteraction*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idPathway)
		return boost::shared_ptr<UniPAX::Pathway>(new UniPAX::Pathway(*(dynamic_cast<UniPAX::Pathway*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idPathwayStep)
		return boost::shared_ptr<UniPAX::PathwayStep>(new UniPAX::PathwayStep(*(dynamic_cast<UniPAX::PathwayStep*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idPhenotypeVocabulary)
		return boost::shared_ptr<UniPAX::PhenotypeVocabulary>(new UniPAX::PhenotypeVocabulary(*(dynamic_cast<UniPAX::PhenotypeVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idPhysicalEntity)
		return boost::shared_ptr<UniPAX::PhysicalEntity>(new UniPAX::PhysicalEntity(*(dynamic_cast<UniPAX::PhysicalEntity*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idProtein)
		return boost::shared_ptr<UniPAX::Protein>(new UniPAX::Protein(*(dynamic_cast<UniPAX::Protein*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idProteinReference)
		return boost::shared_ptr<UniPAX::ProteinReference>(new UniPAX::ProteinReference(*(dynamic_cast<UniPAX::ProteinReference*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idProvenance)
		return boost::shared_ptr<UniPAX::Provenance>(new UniPAX::Provenance(*(dynamic_cast<UniPAX::Provenance*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idPublicationXref)
		return boost::shared_ptr<UniPAX::PublicationXref>(new UniPAX::PublicationXref(*(dynamic_cast<UniPAX::PublicationXref*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idRelationshipTypeVocabulary)
		return boost::shared_ptr<UniPAX::RelationshipTypeVocabulary>(new UniPAX::RelationshipTypeVocabulary(*(dynamic_cast<UniPAX::RelationshipTypeVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idRelationshipXref)
		return boost::shared_ptr<UniPAX::RelationshipXref>(new UniPAX::RelationshipXref(*(dynamic_cast<UniPAX::RelationshipXref*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idRna)
		return boost::shared_ptr<UniPAX::Rna>(new UniPAX::Rna(*(dynamic_cast<UniPAX::Rna*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idRnaReference)
		return boost::shared_ptr<UniPAX::RnaReference>(new UniPAX::RnaReference(*(dynamic_cast<UniPAX::RnaReference*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idRnaRegion)
		return boost::shared_ptr<UniPAX::RnaRegion>(new UniPAX::RnaRegion(*(dynamic_cast<UniPAX::RnaRegion*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idRnaRegionReference)
		return boost::shared_ptr<UniPAX::RnaRegionReference>(new UniPAX::RnaRegionReference(*(dynamic_cast<UniPAX::RnaRegionReference*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idScore)
		return boost::shared_ptr<UniPAX::Score>(new UniPAX::Score(*(dynamic_cast<UniPAX::Score*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idSequenceInterval)
		return boost::shared_ptr<UniPAX::SequenceInterval>(new UniPAX::SequenceInterval(*(dynamic_cast<UniPAX::SequenceInterval*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idSequenceLocation)
		return boost::shared_ptr<UniPAX::SequenceLocation>(new UniPAX::SequenceLocation(*(dynamic_cast<UniPAX::SequenceLocation*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idSequenceModificationVocabulary)
		return boost::shared_ptr<UniPAX::SequenceModificationVocabulary>(new UniPAX::SequenceModificationVocabulary(*(dynamic_cast<UniPAX::SequenceModificationVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idSequenceRegionVocabulary)
		return boost::shared_ptr<UniPAX::SequenceRegionVocabulary>(new UniPAX::SequenceRegionVocabulary(*(dynamic_cast<UniPAX::SequenceRegionVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idSequenceSite)
		return boost::shared_ptr<UniPAX::SequenceSite>(new UniPAX::SequenceSite(*(dynamic_cast<UniPAX::SequenceSite*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idSmallMolecule)
		return boost::shared_ptr<UniPAX::SmallMolecule>(new UniPAX::SmallMolecule(*(dynamic_cast<UniPAX::SmallMolecule*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idSmallMoleculeReference)
		return boost::shared_ptr<UniPAX::SmallMoleculeReference>(new UniPAX::SmallMoleculeReference(*(dynamic_cast<UniPAX::SmallMoleculeReference*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idStoichiometry)
		return boost::shared_ptr<UniPAX::Stoichiometry>(new UniPAX::Stoichiometry(*(dynamic_cast<UniPAX::Stoichiometry*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idTemplateReaction)
		return boost::shared_ptr<UniPAX::TemplateReaction>(new UniPAX::TemplateReaction(*(dynamic_cast<UniPAX::TemplateReaction*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idTemplateReactionRegulation)
		return boost::shared_ptr<UniPAX::TemplateReactionRegulation>(new UniPAX::TemplateReactionRegulation(*(dynamic_cast<UniPAX::TemplateReactionRegulation*>(this))));
//	else if (this->getTypeID() == UniPAX::ClassType::idThing)
//		return boost::shared_ptr<UniPAX::Thing>(new UniPAX::Thing(*(dynamic_cast<UniPAX::Thing*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idTissueVocabulary)
		return boost::shared_ptr<UniPAX::TissueVocabulary>(new UniPAX::TissueVocabulary(*(dynamic_cast<UniPAX::TissueVocabulary*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idTransport)
		return boost::shared_ptr<UniPAX::Transport>(new UniPAX::Transport(*(dynamic_cast<UniPAX::Transport*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idTransportWithBiochemicalReaction)
		return boost::shared_ptr<UniPAX::TransportWithBiochemicalReaction>(new UniPAX::TransportWithBiochemicalReaction(*(dynamic_cast<UniPAX::TransportWithBiochemicalReaction*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idUnificationXref)
		return boost::shared_ptr<UniPAX::UnificationXref>(new UniPAX::UnificationXref(*(dynamic_cast<UniPAX::UnificationXref*>(this))));
//	else if (this->getTypeID() == UniPAX::ClassType::idUtilityClass)
//		return boost::shared_ptr<UniPAX::UtilityClass>(new UniPAX::UtilityClass(*(dynamic_cast<UniPAX::UtilityClass*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idXref)
		return boost::shared_ptr<UniPAX::Xref>(new UniPAX::Xref(*(dynamic_cast<UniPAX::Xref*>(this))));
	// EXT
	else if (this->getTypeID() == UniPAX::ClassType::idAlgebraicRule)
		return boost::shared_ptr<UniPAX::AlgebraicRule>(new UniPAX::AlgebraicRule(*(dynamic_cast<UniPAX::AlgebraicRule*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idAssignmentRule)
		return boost::shared_ptr<UniPAX::AssignmentRule>(new UniPAX::AssignmentRule(*(dynamic_cast<UniPAX::AssignmentRule*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idConstraint)
		return boost::shared_ptr<UniPAX::Constraint>(new UniPAX::Constraint(*(dynamic_cast<UniPAX::Constraint*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idDelay)
		return boost::shared_ptr<UniPAX::Delay>(new UniPAX::Delay(*(dynamic_cast<UniPAX::Delay*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idEvent)
		return boost::shared_ptr<UniPAX::Event>(new UniPAX::Event(*(dynamic_cast<UniPAX::Event*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idEventAssignment)
		return boost::shared_ptr<UniPAX::EventAssignment>(new UniPAX::EventAssignment(*(dynamic_cast<UniPAX::EventAssignment*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idExperiment)
		return boost::shared_ptr<UniPAX::Experiment>(new UniPAX::Experiment(*(dynamic_cast<UniPAX::Experiment*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idFunctionDefinition)
		return boost::shared_ptr<UniPAX::FunctionDefinition>(new UniPAX::FunctionDefinition(*(dynamic_cast<UniPAX::FunctionDefinition*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idIdMapping)
		return boost::shared_ptr<UniPAX::IdMapping>(new UniPAX::IdMapping(*(dynamic_cast<UniPAX::IdMapping*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idImportSource)
		return boost::shared_ptr<UniPAX::ImportSource>(new UniPAX::ImportSource(*(dynamic_cast<UniPAX::ImportSource*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idInitialAssignment)
		return boost::shared_ptr<UniPAX::InitialAssignment>(new UniPAX::InitialAssignment(*(dynamic_cast<UniPAX::InitialAssignment*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idKineticLaw)
		return boost::shared_ptr<UniPAX::KineticLaw>(new UniPAX::KineticLaw(*(dynamic_cast<UniPAX::KineticLaw*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idLocalParameter)
		return boost::shared_ptr<UniPAX::LocalParameter>(new UniPAX::LocalParameter(*(dynamic_cast<UniPAX::LocalParameter*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idMath)
		return boost::shared_ptr<UniPAX::Math>(new UniPAX::Math(*(dynamic_cast<UniPAX::Math*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idModel)
		return boost::shared_ptr<UniPAX::Model>(new UniPAX::Model(*(dynamic_cast<UniPAX::Model*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idParameter)
		return boost::shared_ptr<UniPAX::Parameter>(new UniPAX::Parameter(*(dynamic_cast<UniPAX::Parameter*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idPriority)
		return boost::shared_ptr<UniPAX::Priority>(new UniPAX::Priority(*(dynamic_cast<UniPAX::Priority*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idRateRule)
		return boost::shared_ptr<UniPAX::RateRule>(new UniPAX::RateRule(*(dynamic_cast<UniPAX::RateRule*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idResultObject)
		return boost::shared_ptr<UniPAX::ResultObject>(new UniPAX::ResultObject(*(dynamic_cast<UniPAX::ResultObject*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idRule)
		return boost::shared_ptr<UniPAX::Rule>(new UniPAX::Rule(*(dynamic_cast<UniPAX::Rule*>(this))));
//	else if (this->getTypeID() == UniPAX::ClassType::idSBase)
//		return boost::shared_ptr<UniPAX::SBase>(new UniPAX::SBase(*(dynamic_cast<UniPAX::SBase*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idSample)
		return boost::shared_ptr<UniPAX::Sample>(new UniPAX::Sample(*(dynamic_cast<UniPAX::Sample*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idSeries)
		return boost::shared_ptr<UniPAX::Series>(new UniPAX::Series(*(dynamic_cast<UniPAX::Series*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idTrigger)
		return boost::shared_ptr<UniPAX::Trigger>(new UniPAX::Trigger(*(dynamic_cast<UniPAX::Trigger*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idUnit)
		return boost::shared_ptr<UniPAX::Unit>(new UniPAX::Unit(*(dynamic_cast<UniPAX::Unit*>(this))));
	else if (this->getTypeID() == UniPAX::ClassType::idUnitDefinition)
		return boost::shared_ptr<UniPAX::UnitDefinition>(new UniPAX::UnitDefinition(*(dynamic_cast<UniPAX::UnitDefinition*>(this))));
	std::cerr << "Unknown object type: " << this->getType() << std::endl;
	return boost::shared_ptr<UniPAX::UPBase>();
}

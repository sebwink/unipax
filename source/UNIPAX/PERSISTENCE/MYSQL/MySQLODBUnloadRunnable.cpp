#include<UNIPAX/PERSISTENCE/MYSQL/MySQLODBUnloadRunnable.h>

UniPAX::mysql::MySQLODBUnloadRunnable::MySQLODBUnloadRunnable(std::vector<UnipaxId> & _ids) : UniPAX::ODBUnloadRunnable(_ids)
{
}


UniPAX::mysql::MySQLODBUnloadRunnable::~MySQLODBUnloadRunnable()
{
}


void UniPAX::mysql::MySQLODBUnloadRunnable::run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database)
{


	for (std::vector<UnipaxId>::const_iterator it =ids.begin(); it != ids.end(); ++it)
	{
		// BioPAX
		if ((*it >> 24) == UniPAX::ClassType::idBindingFeature) session->cache_erase<UniPAX::BindingFeature>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idBioSource) session->cache_erase<UniPAX::BioSource>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idBiochemicalPathwayStep) session->cache_erase<UniPAX::BiochemicalPathwayStep>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idBiochemicalReaction) session->cache_erase<UniPAX::BiochemicalReaction>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idCatalysis) session->cache_erase<UniPAX::Catalysis>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idCellVocabulary) session->cache_erase<UniPAX::CellVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idCellularLocationVocabulary) session->cache_erase<UniPAX::CellularLocationVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idChemicalStructure) session->cache_erase<UniPAX::ChemicalStructure>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idComplex) session->cache_erase<UniPAX::Complex>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idComplexAssembly) session->cache_erase<UniPAX::ComplexAssembly>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idControl) session->cache_erase<UniPAX::Control>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idControlledVocabulary) session->cache_erase<UniPAX::ControlledVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idConversion) session->cache_erase<UniPAX::Conversion>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idCovalentBindingFeature) session->cache_erase<UniPAX::CovalentBindingFeature>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idDegradation) session->cache_erase<UniPAX::Degradation>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idDeltaG) session->cache_erase<UniPAX::DeltaG>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idDna) session->cache_erase<UniPAX::Dna>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idDnaReference) session->cache_erase<UniPAX::DnaReference>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idDnaRegion) session->cache_erase<UniPAX::DnaRegion>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idDnaRegionReference) session->cache_erase<UniPAX::DnaRegionReference>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idEntity) session->cache_erase<UniPAX::Entity>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idEntityFeature) session->cache_erase<UniPAX::EntityFeature>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idEntityReference) session->cache_erase<UniPAX::EntityReference>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idEntityReferenceTypeVocabulary) session->cache_erase<UniPAX::EntityReferenceTypeVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idEvidence) session->cache_erase<UniPAX::Evidence>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idEvidenceCodeVocabulary) session->cache_erase<UniPAX::EvidenceCodeVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idExperimentalForm) session->cache_erase<UniPAX::ExperimentalForm>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idExperimentalFormVocabulary) session->cache_erase<UniPAX::ExperimentalFormVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idFragmentFeature) session->cache_erase<UniPAX::FragmentFeature>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idGene) session->cache_erase<UniPAX::Gene>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idGeneticInteraction) session->cache_erase<UniPAX::GeneticInteraction>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idInteraction) session->cache_erase<UniPAX::Interaction>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idInteractionVocabulary) session->cache_erase<UniPAX::InteractionVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idKPrime) session->cache_erase<UniPAX::KPrime>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idModificationFeature) session->cache_erase<UniPAX::ModificationFeature>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idModulation) session->cache_erase<UniPAX::Modulation>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idMolecularInteraction) session->cache_erase<UniPAX::MolecularInteraction>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idPathway) session->cache_erase<UniPAX::Pathway>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idPathwayStep) session->cache_erase<UniPAX::PathwayStep>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idPhenotypeVocabulary) session->cache_erase<UniPAX::PhenotypeVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idPhysicalEntity) session->cache_erase<UniPAX::PhysicalEntity>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idProtein) session->cache_erase<UniPAX::Protein>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idProteinReference) session->cache_erase<UniPAX::ProteinReference>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idProvenance) session->cache_erase<UniPAX::Provenance>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idPublicationXref) session->cache_erase<UniPAX::PublicationXref>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idRelationshipTypeVocabulary) session->cache_erase<UniPAX::RelationshipTypeVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idRelationshipXref) session->cache_erase<UniPAX::RelationshipXref>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idRna) session->cache_erase<UniPAX::Rna>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idRnaReference) session->cache_erase<UniPAX::RnaReference>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idRnaRegion) session->cache_erase<UniPAX::RnaRegion>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idRnaRegionReference) session->cache_erase<UniPAX::RnaRegionReference>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idScore) session->cache_erase<UniPAX::Score>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idSequenceInterval) session->cache_erase<UniPAX::SequenceInterval>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idSequenceLocation) session->cache_erase<UniPAX::SequenceLocation>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idSequenceModificationVocabulary) session->cache_erase<UniPAX::SequenceModificationVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idSequenceRegionVocabulary) session->cache_erase<UniPAX::SequenceRegionVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idSequenceSite) session->cache_erase<UniPAX::SequenceSite>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idSmallMolecule) session->cache_erase<UniPAX::SmallMolecule>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idSmallMoleculeReference) session->cache_erase<UniPAX::SmallMoleculeReference>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idStoichiometry) session->cache_erase<UniPAX::Stoichiometry>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idTemplateReaction) session->cache_erase<UniPAX::TemplateReaction>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idTemplateReactionRegulation) session->cache_erase<UniPAX::TemplateReactionRegulation>(*database, *it);
//		else if ((*it >> 24) == UniPAX::ClassType::idThing) session->cache_erase<UniPAX::Thing>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idTissueVocabulary) session->cache_erase<UniPAX::TissueVocabulary>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idTransport) session->cache_erase<UniPAX::Transport>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idTransportWithBiochemicalReaction) session->cache_erase<UniPAX::TransportWithBiochemicalReaction>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idUnificationXref) session->cache_erase<UniPAX::UnificationXref>(*database, *it);
//		else if ((*it >> 24) == UniPAX::ClassType::idUtilityClass) session->cache_erase<UniPAX::UtilityClass>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idXref) session->cache_erase<UniPAX::Xref>(*database, *it);


		// EXT
		else if ((*it >> 24) == UniPAX::ClassType::idAlgebraicRule) session->cache_erase<UniPAX::AlgebraicRule>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idAssignmentRule) session->cache_erase<UniPAX::AssignmentRule>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idConstraint) session->cache_erase<UniPAX::Constraint>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idDelay) session->cache_erase<UniPAX::Delay>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idEventAssignment) session->cache_erase<UniPAX::EventAssignment>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idEvent) session->cache_erase<UniPAX::Event>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idExperiment) session->cache_erase<UniPAX::Experiment>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idFunctionDefinition) session->cache_erase<UniPAX::FunctionDefinition>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idIdMapping) session->cache_erase<UniPAX::IdMapping>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idImportSource) session->cache_erase<UniPAX::ImportSource>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idInitialAssignment) session->cache_erase<UniPAX::InitialAssignment>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idKineticLaw) session->cache_erase<UniPAX::KineticLaw>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idLocalParameter) session->cache_erase<UniPAX::LocalParameter>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idMath) session->cache_erase<UniPAX::Math>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idModel) session->cache_erase<UniPAX::Model>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idParameter) session->cache_erase<UniPAX::Parameter>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idPriority) session->cache_erase<UniPAX::Priority>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idRateRule) session->cache_erase<UniPAX::RateRule>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idResultObject) session->cache_erase<UniPAX::ResultObject>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idRule) session->cache_erase<UniPAX::Rule>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idSample) session->cache_erase<UniPAX::Sample>(*database, *it);
//		else if ((*it >> 24) == UniPAX::ClassType::idSBase) session->cache_erase<UniPAX::SBase>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idSeries) session->cache_erase<UniPAX::Series>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idTrigger) session->cache_erase<UniPAX::Trigger>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idUnitDefinition) session->cache_erase<UniPAX::UnitDefinition>(*database, *it);
		else if ((*it >> 24) == UniPAX::ClassType::idUnit) session->cache_erase<UniPAX::Unit>(*database, *it);
//		else if ((*it >> 24) == UniPAX::ClassType::idUPBase) session->cache_erase<UniPAX::UPBase>(*database, *it);
	}
}	

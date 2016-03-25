#include <UNIPAX/GRAPH/MAPPING/ORACLE/OracleMappingEngine.h>

#include <UNIPAX/KERNEL/Kernel.h>

#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QSqlError>

#include <exception>

UniPAX::GRAPH::oracle::OracleMappingEngine::OracleMappingEngine(boost::shared_ptr<UniPAX::DBManager> _db_manager) : UniPAX::GRAPH::MappingEngine(_db_manager)
{

}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::needsRebuildDatabaseCache()
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "OracleCache::init: Failed to connect oracle with QT";
			return false;
		}
	}

	QSqlQuery q = db->exec("SELECT * FROM C_RELATIONS WHERE ROWNUM = 1");
	if (!q.next())
		return true;
	q.finish();

	q = db->exec("SELECT * FROM C_ENTITY_ORGANISM WHERE ROWNUM = 1");
	if (!q.next())
		return true;
	q.finish();

	q = db->exec("SELECT * FROM C_ENTITY_DBKEY WHERE ROWNUM = 1");
	if (!q.next())
		return true;
	q.finish();

	q = db->exec("SELECT * FROM C_ENTITY_PATHWAY WHERE ROWNUM = 1");
	if (!q.next())
		return true;
	q.finish();

	return false;
}

void UniPAX::GRAPH::oracle::OracleMappingEngine::rebuildDatabaseCache()
{

	std::cerr << "Init C_RELATION..." << std::flush;

	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "OracleCache::init: Failed to connect oracle with QT";
			return;
		}
	}

	db->exec(QString("BEGIN")
			.append("EXECUTE IMMEDIATE 'DROP TABLE C_RELATIONS CASCADE CONSTRAINTS';")
			.append("EXCEPTION")
			.append("  WHEN OTHERS THEN")
			.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
			.append("END;"));
	QSqlQuery query = db->exec(QString("CREATE TABLE C_RELATIONS (")
			.append("source NUMBER(20),")
			.append("target NUMBER(20),")
			.append("relation VARCHAR2(255),")
			.append("constraint c_rel_pk primary key (source, target, relation)")
			.append(")"));

	if (query.lastError().type() > 0)
		throw std::runtime_error("Unable to create table C_RELATIONS: " + query.lastQuery().toStdString());


	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'bindsTo' FROM BindingFeature_id_bindsTo");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'featureLocation' FROM BindingFeature_id_featureLocat");

	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberFeature' FROM BindingFeature_id_memberFeatur");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM BioSource_id_xref");
	// BiochemicalPathwayStep_evidence
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'nextStep' FROM BiochemicalPathwayStep_id_next");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'stepProcess' FROM BiochemicalPathwayStep_id_step");
	// BiochemicalReaction_deltaG
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'leftEntity' FROM 	 BiochemicalReaction_id_leftEnt");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM  BiochemicalReaction_id_partici");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'rightEntity' FROM BiochemicalReaction_id_rightEn");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM BiochemicalReaction_id_xref");
	// BiochemicalReaction_participantStoichiometry
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"unipaxId\", \"id_controlled\", 'controlled' FROM Catalysis");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'cofactor' FROM Catalysis_id_cofactor");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'controller' FROM Catalysis_id_controller");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM Catalysis_id_participant");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Catalysis_id_xref");
	// Catalysis_interactionType
	// Catalysis_name
	// CellVocabulary
	// CellVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM CellVocabulary_id_xref");
	// CellularLocationVocabulary
	// CellularLocationVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM CellularLocationVocabulary_id_f");
	// ChemicalStructure
	// ChemicalStructure_comment
	// Complex
	// ComplexAssembly
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'leftEntity' FROM ComplexAssembly_id_leftEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM ComplexAssembly_id_participant");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'rightEntity' FROM ComplexAssembly_id_rightEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM ComplexAssembly_id_xref");
	// ComplexAssembly_interactionType
	// ComplexAssembly_name
	// ComplexAssembly_participantStoichiometry
	// Complex_componentStoichiometry
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'component' FROM Complex_id_component");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'feature' FROM Complex_id_feature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberPhysicalEntity' FROM Complex_id_memberPhysicalEntit");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'notFeature' FROM Complex_id_notFeature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Complex_id_xref");
	// Complex_name
	// Constraint
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"unipaxId\", \"id_controlled\", 'controlled' FROM Control");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'controller' FROM Control_id_controller");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM Control_id_participant");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Control_id_xref");
	// Control_interactionType
	// Control_name
	// ControlledVocabulary
	// ControlledVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM ControlledVocabulary_id_xref");
	// Conversion
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'leftEntity' FROM Conversion_id_leftEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM Conversion_id_participant");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'rightEntity' FROM Conversion_id_rightEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Conversion_id_xref");
	// Conversion_interactionType
	// Conversion_name
	// Conversion_participantStoichiometry
	// CovalentBindingFeature
	// CovalentBindingFeature_comment
	// CovalentBindingFeature_evidence
	// CovalentBindingFeature_featureLocationType
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'bindsTo' FROM CovalentBindingFeat_id_bindsTo");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'featureLocation' FROM CovalentBindingFeat_id_featureLoc");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberFeature' FROM CovalentBindingFeat_id_memberFeat");
	// Degradation
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'leftEntity' FROM Degradation_id_leftEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM Degradation_id_participant");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'rightEntity' FROM Degradation_id_rightEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Degradation_id_xref");
	// Degradation_interactionType
	// Degradation_name
	// Degradation_participantStoichiometry
	// Delay
	// DeltaG
	// DeltaG_comment
	// Dna
	// DnaReference
	// DnaReference_comment
	// DnaReference_evidence
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM DnaReference_id_xref");
	// DnaReference_name
	// DnaRegion
	// DnaRegionReference
	// DnaRegionReference_comment
	// DnaRegionReference_evidence
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM DnaRegionReference_id_xref");
	// DnaRegionReference_name
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'entityReference' FROM DnaRegion_id_entityReference");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'feature' FROM DnaRegion_id_feature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberPhysicalEntity' FROM DnaRegion_id_memberPhysicalEnt");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'notFeature' FROM DnaRegion_id_notFeature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM DnaRegion_id_xref");
	// DnaRegion_name
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'entityReference' FROM Dna_id_entityReference");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'feature' FROM Dna_id_feature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberPhysicalEntity' FROM Dna_id_memberPhysicalEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'notFeature' FROM Dna_id_notFeature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Dna_id_xref");
	// Dna_name
	// Entity
	// EntityFeature
	// EntityFeature_comment
	// EntityFeature_evidence
	// EntityFeature_featureLocationType
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'featureLocation' FROM EntityFeature_id_featureLocati");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberFeature' FROM EntityFeature_id_memberFeature");
	// EntityReference
	// EntityReferenceTypeVocabulary
	// EntityReferenceTypeVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM EntityReferenceTypeVocabulary_id_xref");
	// EntityReference_comment
	// EntityReference_evidence
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM EntityReference_id_xref");
	// EntityReference_name
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Entity_id_xref");
	// Entity_name
	// Event
	// EventAssignment
	// Event_eventAssignment
	// Evidence
	// EvidenceCodeVocabulary
	// EvidenceCodeVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM EvidenceCodeVocabulary_id_xref");
	// Evidence_comment
	// Evidence_confidence
	// Evidence_evidenceCode
	// Evidence_experimentalForm
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Evidence_id_xref");
	// Experiment
	// Experiment_mapping
	// Experiment_sample
	// ExperimentalForm
	// ExperimentalFormVocabulary
	// ExperimentalFormVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM ExperimentalFormVocabulary_id_xref");
	// ExperimentalForm_comment
	// ExperimentalForm_experimentalFormDescription
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'experimentalFeature' FROM ExperimentalForm_id_experimentalFeature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'experimentalFormEntity' FROM ExperimentalForm_id_experimentalFormEnt");
	// FragmentFeature
	// FragmentFeature_comment
	// FragmentFeature_evidence
	// FragmentFeature_featureLocationType
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'featureLocation' FROM FragmentFeature_id_featureLoca");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberFeature' FROM FragmentFeature_id_memberFeatu");
	// FunctionDefinition
	// Gene
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Gene_id_xref");
	// Gene_name
	// GeneticInteraction
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM GeneticInteraction_id_particip");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM GeneticInteraction_id_xref");
	// GeneticInteraction_interactionScore
	// GeneticInteraction_interactionType
	// GeneticInteraction_name
	// GeneticInteraction_phenotype
	// ImportSource
	// InitialAssignment
	// Interaction
	// InteractionVocabulary
	// InteractionVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM InteractionVocabulary_id_xref");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM Interaction_id_participant");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Interaction_id_xref");
	// Interaction_interactionType
	// Interaction_name
	// KPrime
	// KPrime_comment
	// KineticLaw
	// KineticLaw_localParameter
	// LocalParameter
	// Mapping
	// Math
	// Model
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'constraint' FROM Model_id_constraint");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'event' FROM Model_id_event");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'functionDefinition' FROM Model_id_functionDefinition");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'initialAssignment' FROM Model_id_initialAssignment");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'parameter' FROM Model_id_parameter");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'rule' FROM Model_id_rule");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'unitDefinition' FROM Model_id_unitDefinition");
	// ModificationFeature
	// ModificationFeature_comment
	// ModificationFeature_evidence
	// ModificationFeature_featureLocationType
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'featureLocation' FROM ModificationFeature_id_featureLoc");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberFeature' FROM ModificationFeature_id_memberF");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"unipaxId\", \"id_controlled\", 'controlled' FROM Modulation");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'controller' FROM Modulation_id_controller");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM Modulation_id_participant");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Modulation_id_xref");
	// Modulation_interactionType
	// Modulation_name
	// MolecularInteraction
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM MolecularInteraction_id_partic");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM MolecularInteraction_id_xref");
	// MolecularInteraction_interactionType
	// MolecularInteraction_name
	// Parameter
	// Pathway
	// PathwayStep
	// PathwayStep_comment
	// PathwayStep_evidence
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'nextStep' FROM PathwayStep_id_nextStep");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'stepProcess' FROM PathwayStep_id_stepProcess");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'modelExtensions' FROM Pathway_id_modelExtensions");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'pathwayComponent' FROM Pathway_id_pathwayComponent");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'pathwayOrder' FROM Pathway_id_pathwayOrder");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Pathway_id_xref");
	// Pathway_name
	// PhenotypeVocabulary
	// PhenotypeVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM PhenotypeVocabulary_id_xref");
	// PhysicalEntity
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'feature' FROM PhysicalEntity_id_feature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberPhysicalEntity' FROM PhysicalEntity_id_memberPhysic");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'notFeature' FROM PhysicalEntity_id_notFeature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM PhysicalEntity_id_xref");
	// PhysicalEntity_name
	// Priority
	// Protein
	// ProteinReference
	// ProteinReference_comment
	// ProteinReference_evidence
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM ProteinReference_id_xref");
	// ProteinReference_name
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'entityReference' FROM Protein_id_entityReference");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'feature' FROM Protein_id_feature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberPhysicalEntity' FROM Protein_id_memberPhysicalEnti");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'notFeature' FROM Protein_id_notFeature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Protein_id_xref");
	// Protein_name
	// Provenance
	// Provenance_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Provenance_id_xref");
	// Provenance_name
	// PublicationXref
	// PublicationXref_author
	// PublicationXref_comment
	// PublicationXref_source
	// PublicationXref_url
	// RateRule
	// RelationshipTypeVocabulary
	// RelationshipTypeVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM RelationshipTypeVocabulary_id_xref");
	// RelationshipXref
	// RelationshipXref_comment
	// RelationshipXref_relationshipType
	// Rna
	// RnaReference
	// RnaReference_comment
	// RnaReference_evidence
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM RnaReference_id_xref");
	// RnaReference_name
	// RnaRegion
	// RnaRegionReference
	// RnaRegionReference_comment
	// RnaRegionReference_evidence
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM RnaRegionReference_id_xref");
	// RnaRegionReference_name
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'entityReference' FROM RnaRegion_id_entityReference");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'feature' FROM RnaRegion_id_feature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberPhysicalEntity' FROM RnaRegion_id_memberPhysicalEnt");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'notFeature' FROM RnaRegion_id_notFeature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM RnaRegion_id_xref");
	// RnaRegion_name
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'entityReference' FROM Rna_id_entityReference");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'feature' FROM Rna_id_feature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberPhysicalEntity' FROM Rna_id_memberPhysicalEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'notFeature' FROM Rna_id_notFeature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Rna_id_xref");
	// Rna_name
	// Rule
	// SBase
	// Sample
	// Score
	// Score_comment
	// SequenceInterval
	// SequenceInterval_comment
	// SequenceLocation
	// SequenceLocation_comment
	// SequenceModificationVocabulary
	// SequenceModificationVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM SequenceModificationVocabulary_id_xref");
	// SequenceRegionVocabulary
	// SequenceRegionVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM SequenceRegionVocabulary_id_xref");
	// SequenceSite
	// SequenceSite_comment
	// SmallMolecule
	// SmallMoleculeReference
	// SmallMoleculeReference_comment
	// SmallMoleculeReference_evidence
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM SmallMoleculeReference_id_xref");
	// SmallMoleculeReference_name
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'entityReference' FROM SmallMolecule_id_entityReferen");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'feature' FROM SmallMolecule_id_feature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'memberPhysicalEntity' FROM SmallMolecule_id_memberPhysica");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'notFeature' FROM SmallMolecule_id_notFeature");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM SmallMolecule_id_xref");
	// SmallMolecule_name
	// Stoichiometry
	// Stoichiometry_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"unipaxId\", \"id_templateEntity\", 'template' FROM TemplateReaction");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"unipaxId\", \"id_controlled\", 'controlled' FROM TemplateReactionRegulation);
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'controller' FROM TemplateReactionRegulation_id_control");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM TemplateReactionRegulation_id_partici");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM TemplateReactionRegulation_id_xref");
	// TemplateReactionRegulation_interactionType
	// TemplateReactionRegulation_name
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM TemplateReaction_id_participan");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'product' FROM TemplateReaction_id_product");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM TemplateReaction_id_xref");
	// TemplateReaction_interactionType
	// TemplateReaction_name
	// Thing
	// TissueVocabulary
	// TissueVocabulary_comment
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM TissueVocabulary_id_xref");
	// Transport
	// TransportWithBiochemicalReaction
	// TransportWithBiochemicalReaction_deltaG
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'leftEntity' FROM TransportWithBiochemicalReaction_id_leftEn");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM TransportWithBiochemicalReaction_id_partic");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'rightEntity' FROM TransportWithBiochemicalReaction_id_rightE");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM TransportWithBiochemicalReaction_id_xref");
	// TransportWithBiochemicalReaction_interactionType
	// TransportWithBiochemicalReaction_kEQ
	// TransportWithBiochemicalReaction_name
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'leftEntity' FROM Transport_id_leftEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'participant' FROM Transport_id_participant");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'rightEntity' FROM Transport_id_rightEntity");
	db->exec("INSERT INTO C_RELATIONS (source, target, relation) SELECT \"object_id\", \"value\", 'xref' FROM Transport_id_xref");
	// Transport_interactionType
	// Transport_name
	// Transport_participantStoichiometry
	// Trigger
	// UPBase
	// UnificationXref
	// UnificationXref_comment
	// Unit
	// UnitDefinition
	// UnitDefinition_unit
	// UtilityClass
	// UtilityClass_comment
	// Xref
	// Xref_comment
	std::cerr << "finished." << std::endl;

	std::cerr << "Init C_ENTITY_ORGANISM..." << std::flush;

	db->exec(QString("BEGIN")
				.append("EXECUTE IMMEDIATE 'DROP TABLE C_ENTITY_ORGANISM CASCADE CONSTRAINTS';")
				.append("EXCEPTION")
				.append("  WHEN OTHERS THEN")
				.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
				.append("END;"));
	db->exec(QString("CREATE TABLE C_ENTITY_ORGANISM (")
			.append("entityId NUMBER(20),")
			.append("referenceId NUMBER(20),")
			.append("organismId NUMBER(20),")
			.append("constraint c_ent_org_pk primary key (entityId, referenceId, organismId)")
			.append(")"));

	db->exec("INSERT INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT \"object_id\", \"unipaxId\", \"organism\" FROM \"Protein_id_entityReference\" pe LEFT JOIN ProteinReference pr ON (pe.\"value\" = pr.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT \"object_id\", \"unipaxId\", \"organism\" FROM \"Dna_id_entityReference\" pe LEFT JOIN DnaReference pr ON (pe.\"value\" = pr.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT \"object_id\", \"unipaxId\", \"organism\" FROM \"DnaRegion_id_entityReference\" pe LEFT JOIN DnaRegionReference pr ON (pe.\"value\" = pr.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT \"object_id\", \"unipaxId\", \"organism\" FROM \"Rna_id_entityReference\" pe LEFT JOIN RnaReference pr ON (pe.\"value\" = pr.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT \"object_id\", \"unipaxId\", \"organism\" FROM \"RnaRegion_id_entityReference\" pe LEFT JOIN RnaRegionReference pr ON (pe.\"value\" = pr.\"unipaxId\")");

	// small molecules do not have organism
	db->exec("INSERT INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT \"object_id\", \"value\", -1 FROM \"SmallMolecule_id_entityReferen");

	// special case for complexes, they do not have entity references - the organism will be assigned from the components of the complex.
	db->exec("INSERT INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT DISTINCT cc.\"object_id\", -1, eo.\"organismId\" FROM C_ENTITY_ORGANISM eo LEFT JOIN \"Complex_id_component\" cc ON (eo.\"entityId\" = cc.\"value\") WHERE \"object_id\" > -1");


	std::cerr << "finished." << std::endl;

	std::cerr << "Init C_ENTITY_PATHWAY..." << std::flush;


	db->exec(QString("BEGIN")
				.append("EXECUTE IMMEDIATE 'DROP TABLE C_ENTITY_PATHWAY CASCADE CONSTRAINTS';")
				.append("EXCEPTION")
				.append("  WHEN OTHERS THEN")
				.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
				.append("END;"));
	db->exec(QString("CREATE TABLE C_ENTITY_PATHWAY (")
			.append("entityId NUMBER(20),")
			.append("interactionId NUMBER(20),")
			.append("pathwayId NUMBER(20),")
			.append("constraint c_ent_path_pk primary key (entityId, interactionId, pathwayId)")
			.append(")"));

	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Interaction_id_participant\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"GeneticInteraction_id_particip\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"MolecularInteraction_id_partic\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"TemplateReaction_id_participan\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"TemplateReaction_id_product\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT tr.\"id_templateEntity\", tr.\"unipaxId\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"TemplateReaction\" tr WHERE pe.\"value\" = tr.\"unipaxId\"");
	// control objects
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Control_id_controller\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT i.\"id_controlled\", i.\"unipaxId\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Control\" i WHERE pe.\"value\" = i.\"unipaxId\" AND i.\"id_controlled\" != 0");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"TemplateReactionRegulation_id_control\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT i.\"id_controlled\", i.\"unipaxId\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"TemplateReactionRegulation" i WHERE pe.\"value\" = i.\"unipaxId\" AND i.\"id_controlled\" != 0");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Modulation_id_controller\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT i.\"id_controlled\", i.\"unipaxId\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Modulation\" i WHERE pe.\"value\" = i.\"unipaxId\" AND i.\"id_controlled\" != 0");

	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Catalysis_id_controller\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT i.\"id_controlled\", i.\"unipaxId\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Catalysis\" i WHERE pe.\"value\" = i.\"unipaxId\" AND i.\"id_controlled\" != 0");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Catalysis_id_cofactor\" iip WHERE pe.\"value\" = iip.\"object_id\"");

	// conversion objects
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Conversion_id_leftEntity\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Conversion_id_rightEntity\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"ComplexAssembly_id_leftEntity\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"ComplexAssembly_id_rightEntity\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"BiochemicalReaction_id_leftEnt\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"BiochemicalReaction_id_rightEn\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Degradation_id_leftEntity\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Degradation_id_rightEntity\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Transport_id_leftEntity\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"Transport_id_rightEntity\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"TransportWithBiochemicalReaction_id_leftEn\" iip WHERE pe.\"value\" = iip.\"object_id\"");
	db->exec("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.\"value\", iip.\"object_id\", pe.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pe, \"TransportWithBiochemicalReaction_id_rightE\" iip WHERE pe.\"value\" = iip.\"object_id\"");

	// last check all pathway objects ...

	// speed up queries using pathway id range
	UnipaxId pathway_low = DBManager::getBase("Pathway");
	UnipaxId pathway_high = ((pathway_low >> 24) + 1) << 24;

	int numRowsAffected = 1;

	int maxDepth = 20;
	int currentDepth = 0;

	while (numRowsAffected > 0 && currentDepth < maxDepth)
	{

		QSqlQuery q = db->exec(QString("INSERT INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT cep.\"entityId\", cep.\"interactionId\", pip.\"object_id\" FROM \"Pathway_id_pathwayComponent\" pip, C_ENTITY_PATHWAY cep WHERE pip.\"value\" >= %1 AND pip.\"value\" < %2 AND pip.\"value\" = cep.\"pathwayId\"").arg(pathway_low).arg(pathway_high));
		numRowsAffected = q.numRowsAffected();

		++currentDepth;
	}

	std::cerr << "finished. Recursion depth: " << currentDepth << std::endl;

	std::cerr << "Init C_ENTITY_DBKEY..." << std::flush;


	db->exec(QString("BEGIN")
				.append("EXECUTE IMMEDIATE 'DROP TABLE C_ENTITY_DBKEY CASCADE CONSTRAINTS';")
				.append("EXCEPTION")
				.append("  WHEN OTHERS THEN")
				.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
				.append("END;"));
	db->exec(QString("CREATE TABLE C_ENTITY_DBKEY (")
			.append("entityId NUMBER(20),")
			.append("db CLOB,")
			.append("id CLOB,")
			.append("constraint c_ent_dbkey_pk primary key (entityId, db, id)")
			.append(")"));

	// entity references

	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Protein_id_entityReference\" pe INNER JOIN \"ProteinReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Dna_id_entityReference\" pe INNER JOIN \"DnaReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"DnaRegion_id_entityReference\" pe INNER JOIN \"DnaRegionReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Rna_id_entityReference\" pe INNER JOIN \"RnaReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"RnaRegion_id_entityReference\" pe INNER JOIN \"RnaRegionReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"SmallMolecule_id_entityReference\" pe INNER JOIN \"SmallMoleculeReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");

	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Protein_id_entityReference\" pe INNER JOIN \"ProteinReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Dna_id_entityReference\" pe INNER JOIN \"DnaReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"DnaRegion_id_entityReference\" pe INNER JOIN \"DnaRegionReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Rna_id_entityReference\" pe INNER JOIN \"RnaReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"RnaRegion_id_entityReference\" pe INNER JOIN \"RnaRegionReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"SmallMolecule_id_entityReference\" pe INNER JOIN \"SmallMoleculeReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");

	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Protein_id_entityReference\" pe INNER JOIN \"ProteinReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Dna_id_entityReference\" pe INNER JOIN \"DnaReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"DnaRegion_id_entityReference\" pe INNER JOIN \"DnaRegionReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Rna_id_entityReference\" pe INNER JOIN \"RnaReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"RnaRegion_id_entityReference\" pe INNER JOIN \"RnaRegionReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"SmallMolecule_id_entityReference\" pe INNER JOIN \"SmallMoleculeReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");

	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Protein_id_entityReference\" pe INNER JOIN \"ProteinReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Dna_id_entityReference\" pe INNER JOIN \"DnaReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"DnaRegion_id_entityReference\" pe INNER JOIN \"DnaRegionReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Rna_id_entityReference\" pe INNER JOIN \"RnaReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"RnaRegion_id_entityReference\" pe INNER JOIN \"RnaRegionReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.\"object_id\", xref.\"db\", xref.\"id\" FROM \"SmallMolecule_id_entityReference\" pe INNER JOIN \"SmallMoleculeReference_id_xref\" prx ON (pe.\"value\" = prx.\"object_id\") INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");

	// entities

	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Protein_id_xref\" prx INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Dna_id_xref\" prx INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"DnaRegion_id_xref\" prx INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Rna_id_xref\" prx INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"RnaRegion_id_xref\" prx INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"SmallMolecule_id_xref\" prx INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Complex_id_xref\" prx INNER JOIN \"UnificationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");

	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Protein_id_xref\" prx INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Dna_id_xref\" prx INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"DnaRegion_id_xref\" prx INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Rna_id_xref\" prx INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"RnaRegion_id_xref\" prx INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"SmallMolecule_id_xref\" prx INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Complex_id_xref\" prx INNER JOIN \"RelationshipXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");

	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Protein_id_xref\" prx INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Dna_id_xref\" prx INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"DnaRegion_id_xref\" prx INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Rna_id_xref\" prx INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"RnaRegion_id_xref\" prx INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"SmallMolecule_id_xref\" prx INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Complex_id_xref\" prx INNER JOIN \"PublicationXref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");

	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Protein_id_xref\" prx INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Dna_id_xref\" prx INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"DnaRegion_id_xref\" prx INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Rna_id_xref\" prx INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"RnaRegion_id_xref\" prx INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"SmallMolecule_id_xref\" prx INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");
	db->exec("INSERT INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.\"object_id\", xref.\"db\", xref.\"id\" FROM \"Complex_id_xref\" prx INNER JOIN \"Xref\" xref ON (prx.\"value\" = xref.\"unipaxId\")");

	std::cerr << "finished." << std::endl;

	std::cerr << "Init C_NAMES..." << std::flush;


	db->exec(QString("BEGIN")
				.append("EXECUTE IMMEDIATE 'DROP TABLE C_NAMES CASCADE CONSTRAINTS';")
				.append("EXCEPTION")
				.append("  WHEN OTHERS THEN")
				.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
				.append("END;"));
	db->exec(QString("CREATE TABLE C_NAMES (")
			.append("unipaxId NUMBER(20),")
			.append("value CLOB,")
			.append("standard NUMBER(1) DEFAULT 0,")
			.append("display NUMBER(1) DEFAULT 0,")
			.append("constraint c_names_pk primary key (unipaxId, value)")
			.append(")"));

	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"BioSource\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"BiochemicalReaction\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Catalysis\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"ComplexAssembly\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Complex\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Control\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Conversion\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Degradation\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"DnaReference\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"DnaRegionReference\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"DnaRegion\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Dna\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"EntityReference\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Entity\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Gene\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"GeneticInteraction\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Interaction\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Modulation\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"MolecularInteraction\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Pathway\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"PhysicalEntity\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"ProteinReference\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Protein\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Provenance\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"RnaReference\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"RnaRegionReference\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"RnaRegion\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Rna\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"SmallMoleculeReference" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"SmallMolecule\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"TemplateReactionRegulation" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"TemplateReaction\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"TransportWithBiochemicalReaction\" WHERE \"standardName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"standardName\", 1, 0 FROM \"Transport\" WHERE \"standardName\" is not null ");

	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"BioSource\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"BiochemicalReaction\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Catalysis\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"ComplexAssembly\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Complex\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Control\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Conversion\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Degradation\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"DnaReference\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"DnaRegionReference\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"DnaRegion\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Dna\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"EntityReference\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Entity\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Gene\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"GeneticInteraction\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Interaction\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Modulation\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"MolecularInteraction\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Pathway\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"PhysicalEntity\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"ProteinReference\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Protein\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Provenance\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"RnaReference\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"RnaRegionReference\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"RnaRegion\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Rna\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"SmallMoleculeReference" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"SmallMolecule\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"TemplateReactionRegulation" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"TemplateReaction\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"TransportWithBiochemicalReaction\" WHERE \"displayName\" is not null ");
	db->exec("INSERT INTO C_NAMES (unipaxId, value, standard, display) SELECT \"unipaxId\", \"displayName\", 0, 1 FROM \"Transport\" WHERE \"displayName\" is not null ");

	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"BioSource_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"BiochemicalReaction_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Catalysis_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"ComplexAssembly_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Complex_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Control_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Conversion_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Degradation_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"DnaReference_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"DnaRegionReference_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"DnaRegion_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Dna_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"EntityReference_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Entity_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Gene_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"GeneticInteraction_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Interaction_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Modulation_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"MolecularInteraction_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Pathway_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"PhysicalEntity_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"ProteinReference_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Protein_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Provenance_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"RnaReference_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"RnaRegionReference_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"RnaRegion_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Rna_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"SmallMoleculeReference_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"SmallMolecule_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"TemplateReactionRegulation_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"TemplateReaction_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"TransportWithBiochemicalReaction_name\"");
	db->exec("INSERT INTO C_NAMES (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Transport_name\"");

	std::cerr << "finished." << std::endl;




	std::cerr << "Init C_ENTITY_FEATURES..." << std::flush;

	db->exec(QString("BEGIN")
				.append("EXECUTE IMMEDIATE 'DROP TABLE C_ENTITY_FEATURES CASCADE CONSTRAINTS';")
				.append("EXCEPTION")
				.append("  WHEN OTHERS THEN")
				.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
				.append("END;"));
	db->exec(QString("CREATE TABLE C_ENTITY_FEATURES (")
			.append("unipaxId NUMBER(20),")
			.append("type VARCHAR2(20),")
			.append("value CLOB,")
			.append("constraint c_names_pk primary key (unipaxId, type, value)")
			.append(")"));


	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'modification_feature', smv.\"term\" FROM \"Protein_id_feature\" pf LEFT JOIN \"ModificationFeature\" mf ON (pf.\"value\" = mf.\"unipaxId\") LEFT JOIN \"SequenceModificationVocabulary\" smv ON (mf.\"modificationType\" = smv.\"unipaxId\") WHERE smv.\"term\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'modification_feature', smv.\"term\" FROM \"Dna_id_feature\" pf LEFT JOIN \"ModificationFeature\" mf ON (pf.\"value\" = mf.\"unipaxId\") LEFT JOIN \"SequenceModificationVocabulary\" smv ON (mf.\"modificationType\" = smv.\"unipaxId\") WHERE smv.\"term\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'modification_feature', smv.\"term\" FROM \"DnaRegion_id_feature\" pf LEFT JOIN \"ModificationFeature\" mf ON (pf.\"value\" = mf.\"unipaxId\") LEFT JOIN \"SequenceModificationVocabulary\" smv ON (mf.\"modificationType\" = smv.\"unipaxId\") WHERE smv.\"term\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'modification_feature', smv.\"term\" FROM \"Rna_id_feature\" pf LEFT JOIN \"ModificationFeature\" mf ON (pf.\"value\" = mf.\"unipaxId\") LEFT JOIN \"SequenceModificationVocabulary\" smv ON (mf.\"modificationType\" = smv.\"unipaxId\") WHERE smv.\"term\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'modification_feature', smv.\"term\" FROM \"RnaRegion_id_feature\" pf LEFT JOIN \"ModificationFeature\" mf ON (pf.\"value\" = mf.\"unipaxId\") LEFT JOIN \"SequenceModificationVocabulary\" smv ON (mf.\"modificationType\" = smv.\"unipaxId\") WHERE smv.\"term\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'modification_feature', smv.\"term\" FROM \"SmallMolecule_id_feature\" pf LEFT JOIN \"ModificationFeature\" mf ON (pf.\"value\" = mf.\"unipaxId\") LEFT JOIN \"SequenceModificationVocabulary\" smv ON (mf.\"modificationType\" = smv.\"unipaxId\") WHERE smv.\"term\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'modification_feature', smv.\"term\" FROM \"Complex_id_feature\" pf LEFT JOIN \"ModificationFeature\" mf ON (pf.\"value\" = mf.\"unipaxId\") LEFT JOIN \"SequenceModificationVocabulary\" smv ON (mf.\"modificationType\" = smv.\"unipaxId\") WHERE smv.\"term\" IS NOT NULL");

	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'feature_comment', comment.\"value\" FROM \"Protein_id_feature\" pf LEFT JOIN \"EntityFeature_comment\" comment ON (pf.\"value\" = comment.\"object_id\") WHERE comment.\"value\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'feature_comment', comment.\"value\" FROM \"Dna_id_feature\" pf LEFT JOIN \"EntityFeature_comment\" comment ON (pf.\"value\" = comment.\"object_id\") WHERE comment.\"value\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'feature_comment', comment.\"value\" FROM \"DnaRegion_id_feature\" pf LEFT JOIN \"EntityFeature_comment\" comment ON (pf.\"value\" = comment.\"object_id\") WHERE comment.\"value\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'feature_comment', comment.\"value\" FROM \"Rna_id_feature\" pf LEFT JOIN \"EntityFeature_comment\" comment ON (pf.\"value\" = comment.\"object_id\") WHERE comment.\"value\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'feature_comment', comment.\"value\" FROM \"RnaRegion_id_feature\" pf LEFT JOIN \"EntityFeature_comment\" comment ON (pf.\"value\" = comment.\"object_id\") WHERE comment.\"value\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'feature_comment', comment.\"value\" FROM \"SmallMolecule_id_feature\" pf LEFT JOIN \"EntityFeature_comment\" comment ON (pf.\"value\" = comment.\"object_id\") WHERE comment.\"value\" IS NOT NULL");
	db->exec("INSERT INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.\"object_id\", 'feature_comment', comment.\"value\" FROM \"Complex_id_feature\" pf LEFT JOIN \"EntityFeature_comment\" comment ON (pf.\"value\" = comment.\"object_id\") WHERE comment.\"value\" IS NOT NULL");


}

boost::shared_ptr<UniPAX::GRAPH::RelationsGraph> UniPAX::GRAPH::oracle::OracleMappingEngine::createRelationsGraph()
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "OracleCache::createRelationsGraph: Failed to connect oracle with QT";
			return boost::shared_ptr<UniPAX::GRAPH::RelationsGraph>();
		}
	}

	QSqlQuery query = db->exec("SELECT source, target, relation FROM C_RELATIONS");

	boost::shared_ptr<UniPAX::GRAPH::RelationsGraph> rg(new UniPAX::GRAPH::RelationsGraph());

	while (query.next())
	{
		UnipaxId source = query.value(0).toULongLong();
		UnipaxId target = query.value(1).toULongLong();
		std::string relation = query.value(2).toString().toStdString();

		lemon::ListDigraphBase::Node sourceNode;

		if (rg->nodeMap.find(source) == rg->nodeMap.end())
		{
			sourceNode = rg->graph.addNode();
			rg->nodeMap[source] = sourceNode;
			rg->idMap[sourceNode] = source;
		}
		else
			sourceNode = rg->nodeMap[source];

		lemon::ListDigraphBase::Node targetNode;

		if (rg->nodeMap.find(target) == rg->nodeMap.end())
		{
			targetNode = rg->graph.addNode();
			rg->nodeMap[target] = targetNode;
			rg->idMap[targetNode] = target;
		}
		else
			targetNode = rg->nodeMap[target];

		lemon::ListDigraphBase::Arc arc = rg->graph.addArc(sourceNode, targetNode);
		rg->relationMap[arc] = relation;

	}


	return rg;
}

boost::shared_ptr<UniPAX::GRAPH::ProteinProteinInteractionNetwork> UniPAX::GRAPH::oracle::OracleMappingEngine::createProteinProteinInteractionNetwork(const std::set<std::string> & physical_entities)
{


	boost::shared_ptr<ProteinProteinInteractionNetwork> ppi(new UniPAX::GRAPH::ProteinProteinInteractionNetwork());

	addInteractions(*ppi, physical_entities);

	return ppi;

}

boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> UniPAX::GRAPH::oracle::OracleMappingEngine::createRegulatoryNetwork(const std::set<std::string> & physical_entities)
{
	boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> regulatory(new UniPAX::GRAPH::RegulatoryNetwork());

	addTemplateRegulations(*regulatory, physical_entities);
	addControlOfBiochemicalReactions(*regulatory, physical_entities);
	addControlOfConversions(*regulatory, physical_entities);

	return regulatory;

}

boost::shared_ptr<UniPAX::GRAPH::MetabolicNetwork> UniPAX::GRAPH::oracle::OracleMappingEngine::createMetabolicNetwork(const std::set<std::string> & physical_entities)
{
	boost::shared_ptr<UniPAX::GRAPH::MetabolicNetwork> metabolic(new UniPAX::GRAPH::MetabolicNetwork());

	addBiochemicalReactions(*metabolic, physical_entities);

	return metabolic;

}



bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapRegulationTypes(UniPAX::GRAPH::RegulatoryNetwork & network, UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcMap<std::string> & regulation_type)
{

	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "OracleCache::mapRegulationTypes: Failed to connect oracle with QT";
			return false;
		}
	}

	{
		QSqlQuery query = db->exec("SELECT \"unipaxId\", \"controlType\" FROM \"TemplateReactionRegulation\"");

		while (query.next())
		{
			UnipaxId unipaxId = query.value(0).toULongLong();
			std::string controlType = query.value(1).toString().toStdString();

			if (network.id_arcs_map.find(unipaxId) != network.id_arcs_map.end())
			{
				for (RegulatoryNetwork::ArcMapEqualRange p = network.id_arcs_map.equal_range(unipaxId); p.first != p.second; ++p.first)
				{
					regulation_type[p.first->second] = controlType;
				}
			}

		}
		query.finish();
	}
	{
		QSqlQuery query = db->exec("SELECT \"unipaxId\", \"controlType\" FROM \"Control\"");

		while (query.next())
		{
			UnipaxId unipaxId = query.value(0).toULongLong();
			std::string controlType = query.value(1).toString().toStdString();

			for (RegulatoryNetwork::ArcMapEqualRange p = network.id_arcs_map.equal_range(unipaxId); p.first != p.second; ++p.first)
			{
				regulation_type[p.first->second] = controlType;
			}

		}
		query.finish();
	}
	return true;
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::getEntityIdsByOrganism(std::set<UnipaxId> & organism_entities, UnipaxId organismId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "OracleMappingEngine::getEntityIdsByOrganism: Failed to connect oracle with QT";
			return false;
		}
	}

	QSqlQuery query = db->exec(QString("SELECT entityId FROM C_ENTITY_ORGANISM WHERE organismId = %1 OR organismId = -1").arg(organismId));

	while (query.next())
	{
		organism_entities.insert(query.value(0).toULongLong());
	}

	return true;
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::getEntityIdsByPathway(std::set<UnipaxId> & pathway_entities, UnipaxId pathwayId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "OracleMappingEngine::getEntityIdsByPathway: Failed to connect oracle with QT";
			return false;
		}
	}

	QSqlQuery query = db->exec(QString("SELECT distinct entityId FROM C_ENTITY_PATHWAY WHERE pathwayId = %1").arg(pathwayId));

	while (query.next())
	{
		pathway_entities.insert(query.value(0).toULongLong());
	}

	return true;
}

std::string UniPAX::GRAPH::oracle::OracleMappingEngine::getName(UnipaxId unipaxId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "OracleMappingEngine::getName: Failed to connect oracle with QT";
			return false;
		}
	}

	QSqlQuery query = db->exec(QString("SELECT value FROM C_NAMES WHERE unipaxId = %1").arg(unipaxId));

	if (query.next())
	{
		return query.value(0).toString().toStdString();
	}

	return "";
}

std::string UniPAX::GRAPH::oracle::OracleMappingEngine::getPathwayName(UnipaxId unipaxId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "OracleMappingEngine::getPathwayName: Failed to connect oracle with QT";
			return false;
		}
	}

	QSqlQuery query = db->exec(QString("select p.\"displayName\", pa.\"displayName\" from \"Provenance\" p, \"Pathway\" pa where pa.\"unipaxId\" = %1 and p.\"unipaxId\" = pa.\"dataSource\"").arg(unipaxId));

	std::string name = "";
	if (query.next())
	{
		name = query.value(1).toString().toStdString() + " (" + query.value(0).toString().toStdString() + ")";
	}

	return name;
}

std::string UniPAX::GRAPH::oracle::OracleMappingEngine::getPathwayDescription(UnipaxId unipaxId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::oracle::OracleManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "OracleMappingEngine::getPathwayDescription: Failed to connect oracle with QT";
			return false;
		}
	}

	std::string description = "";
	QSqlQuery query = db->exec(QString("select \"value\" from \"Pathway_comments\" where \"object_id\" = %1").arg(unipaxId));

	while (query.next())
	{
		if (description == "")
			description = query.value(0).toString().remove(QString("\n")).toStdString();
		else
			description = description + " | " + query.value(0).toString().remove(QString("\n")).toStdString();
	}

	return description;
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addInteractions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addInteractions(network, physical_entities);
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addTemplateRegulations(RegulatoryNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addTemplateRegulations(network, physical_entities);
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addControlOfBiochemicalReactions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addControlOfBiochemicalReactions(network, physical_entities);
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addControlOfConversions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addControlOfConversions(network, physical_entities);
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addComplexAssemblies(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions)
{
	return _addComplexAssemblies(network, physical_entities, search_in_biochemicalreactions);
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addInteractions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addInteractions(network, physical_entities);
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addTemplateRegulations(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addTemplateRegulations(network, physical_entities);
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addControlOfBiochemicalReactions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addControlOfBiochemicalReactions(network, physical_entities);
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addComplexAssemblies(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions)
{
	return _addComplexAssemblies(network, physical_entities, search_in_biochemicalreactions);
}

int UniPAX::GRAPH::oracle::OracleMappingEngine::addBiochemicalReactions(MetabolicNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addBiochemicalReactions(network, physical_entities);
}


bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db)
{
	return _mapXrefData(network, nodeMap, external_db);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & arcMap, std::string external_db)
{
	return _mapXrefData(network, arcMap, external_db);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapNames(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapNames(network, nodeMap, type);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapFeatures(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapFeatures(network, nodeMap, type);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapXrefData(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db)
{
	return _mapXrefData(network, nodeMap, external_db);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapXrefData(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::EdgeMap<std::string> & edgeMap, std::string external_db)
{
	return _mapXrefData(network, edgeMap, external_db);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapNames(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapNames(network, nodeMap, type);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapFeatures(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapFeatures(network, nodeMap, type);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapXrefData(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db)
{
	return _mapXrefData(network, nodeMap, external_db);
}

/*bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapXrefData(MetabolicNetwork & network, MetabolicNetwork::Graph::ArcMap<std::string> & arcMap, std::string external_db)
{
	return _mapXrefData(network, arcMap, external_db);
}*/

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapNames(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapNames(network, nodeMap, type);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::mapFeatures(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapFeatures(network, nodeMap, type);
}


bool UniPAX::GRAPH::oracle::OracleMappingEngine::filterByOrganisms(RegulatoryNetwork & network, std::set<UnipaxId> & organismIds)
{
	return _filterByOrganism(network, organismIds);
}


bool UniPAX::GRAPH::oracle::OracleMappingEngine::filterByPathways(RegulatoryNetwork & network, std::set<UnipaxId> & pathwayIds)
{
	return _filterByPathway(network, pathwayIds);
}



bool UniPAX::GRAPH::oracle::OracleMappingEngine::filterByOrganisms(ProteinProteinInteractionNetwork & network, std::set<UnipaxId> & organismIds)
{
	return _filterByOrganism(network, organismIds);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::filterByPathways(ProteinProteinInteractionNetwork & network, std::set<UnipaxId> & pathwayIds)
{
	return _filterByPathway(network, pathwayIds);
}


bool UniPAX::GRAPH::oracle::OracleMappingEngine::filterByPathways(MetabolicNetwork & network, std::set<UnipaxId> & pathwayIds)
{
	return _filterByPathway(network, pathwayIds);
}

bool UniPAX::GRAPH::oracle::OracleMappingEngine::filterByOrganisms(MetabolicNetwork & network, std::set<UnipaxId> & organismIds)
{
	return _filterByOrganism(network, organismIds);
}



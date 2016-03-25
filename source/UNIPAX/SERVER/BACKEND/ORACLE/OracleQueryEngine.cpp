#include <UNIPAX/SERVER/BACKEND/ORACLE/OracleQueryEngine.h>
#include <UNIPAX/SERVER/BACKEND/QueryEngine.h>
#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>

#include<UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#include<UNIPAX/KERNEL/Kernel.h>

#include <QtXml>
#include <QtSql>

#include <iostream>
#include <sstream>

#include<odb/transaction.hxx>


UniPAX::SERVER::OracleQueryEngine::OracleQueryEngine() : QueryEngine(), manager(new UniPAX::oracle::OracleManager())
{
}

UniPAX::SERVER::OracleQueryEngine::~OracleQueryEngine()
{

}

void UniPAX::SERVER::OracleQueryEngine::createResultSetTables()
{
	checkDatabaseConnection();

	std::cout << "Creating result set tables... " << std::flush;

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "OracleQueryEngine::createResultSetTables: Failed to connect oracle with QT";
	}

	db->exec(QString("BEGIN")
			.append("EXECUTE IMMEDIATE 'DROP TABLE Q_RESULTSETS CASCADE CONSTRAINTS';")
			.append("EXCEPTION")
			.append("  WHEN OTHERS THEN")
			.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
			.append("END;"));
	db->exec(QString("CREATE TABLE Q_RESULTSETS (")
			.append("resultSetId NUMBER(20),")
			.append("value VARCHAR2(4000)")
			.append(")"));

	std::cout << "finished." << std::endl;
}


void UniPAX::SERVER::OracleQueryEngine::checkIndexes()
{
	checkDatabaseConnection();

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "OracleQueryEngine::checkIndexes: Failed to connect oracle with QT";
	}

	QSqlQuery q = db->exec(QString("SELECT * FROM Q_NAME_INDEX WHERE ROWNUM = 1"));
	if (!q.next())
		rebuildNameIndex();

	q = db->exec(QString("SELECT * FROM Q_ATTRIBUTE_INDEX WHERE ROWNUM = 1"));
	if (!q.next())
		rebuildAttributeIndex();

	q = db->exec(QString("SELECT * FROM Q_PATHWAY_INDEX WHERE ROWNUM = 1"));
	if (!q.next())
		rebuildPathwayIndex();


}

void UniPAX::SERVER::OracleQueryEngine::rebuildNameIndex()
{
	std::cout << "Rebuilding name index... " << std::flush;

	checkDatabaseConnection();

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "OracleQueryEngine::rebuildNameIndex: Failed to connect oracle with QT";
	}

	db->exec(QString("BEGIN")
				.append("EXECUTE IMMEDIATE 'DROP TABLE Q_NAME_INDEX CASCADE CONSTRAINTS';")
				.append("EXCEPTION")
				.append("  WHEN OTHERS THEN")
				.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
				.append("END;"));
	db->exec(QString("CREATE TABLE Q_NAME_INDEX (")
			.append("unipaxId NUMBER(20),")
			.append("value VARCHAR2(4000)")
			.append(")"));

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"BioSource_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"BiochemicalReaction_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Catalysis_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"ComplexAssembly_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Complex_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Control_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Conversion_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Degradation_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"DnaReference_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"DnaRegionReference_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"DnaRegion_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Dna_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"EntityReference_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Entity_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Gene_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"GeneticInteraction_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Interaction_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Modulation_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"MolecularInteraction_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Pathway_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"PhysicalEntity_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"ProteinReference_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Protein_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Provenance_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"RnaReference_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"RnaRegionReference_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"RnaRegion_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Rna_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"SmallMoleculeReference_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"SmallMolecule_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"TemplateReactionRegulation_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"TemplateReaction_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX (unipaxId, value) SELECT \"object_id\", \"value\" FROM \"TransportWithBiochemicalReaction_name\"");

	db->exec("INSERT INTO Q_NAME_INDEX QString((unipaxId, value) SELECT \"object_id\", \"value\" FROM \"Transport_name\"");

	db->exec(QString("CREATE INDEX q_name_value_index ON Q_NAME_INDEX (value) INDEXTYPE IS CTXSYS.CONTEXT"));

	std::cout << "finished." << std::endl;
}

void UniPAX::SERVER::OracleQueryEngine::rebuildAttributeIndex()
{
	std::cout << "Rebuilding attribute index... " << std::flush;

	checkDatabaseConnection();

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "OracleQueryEngine::rebuildAttributeIndex: Failed to connect oracle with QT";
	}

	db->exec(QString("BEGIN")
				.append("EXECUTE IMMEDIATE 'DROP TABLE Q_ATTRIBUTE_INDEX CASCADE CONSTRAINTS';")
				.append("EXCEPTION")
				.append("  WHEN OTHERS THEN")
				.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
				.append("END;"));
	db->exec(QString("CREATE TABLE Q_ATTRIBUTE_INDEX (")
			.append("unipaxId NUMBER(20) NOT NULL,")
			.append("type VARCHAR2(40) NOT NULL,")
			.append("standardName VARCHAR2(4000) DEFAULT NULL,")
			.append("displayName VARCHAR2(4000) DEFAULT NULL,")
			.append("organism NUMBER(20) DEFAULT NULL,")
			.append("dataSource NUMBER(20) DEFAULT NULL,")
			.append("PRIMARY KEY(unipaxId)")
			.append(")"));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'AlgebraicRule', '")
                 .append(QString::number(UniPAX::ClassType::AlgebraicRule))
                 .append("', NULL, NULL, NULL, NULL FROM \"AlgebraicRule\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'AssignmentRule', '")
                 .append(QString::number(UniPAX::ClassType::AssignmentRule))
                 .append("', NULL, NULL, NULL, NULL FROM \"AssignmentRule\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'BindingFeature', '")
                 .append(QString::number(UniPAX::ClassType::BindingFeature))
                 .append("', NULL, NULL, NULL, NULL FROM \"BindingFeature\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'BioSource', '")
                 .append(QString::number(UniPAX::ClassType::BioSource))
                 .append(",standardName, displayName, NULL, NULL FROM \"BioSource\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'BiochemicalPathwayStep', '")
                 .append(QString::number(UniPAX::ClassType::BiochemicalPathwayStep))
                 .append("', NULL, NULL, NULL, NULL FROM \"BiochemicalPathwayStep\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'BiochemicalReaction', '")
                 .append(QString::number(UniPAX::ClassType::BiochemicalReaction))
                 .append("', NULL, NULL, NULL, NULL FROM \"BiochemicalReaction\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Catalysis', '")
                 .append(QString::number(UniPAX::ClassType::Catalysis))
                 .append("', standardName, displayName, NULL, dataSource FROM \"Catalysis\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'CellVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::CellVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"CellVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'CellularLocationVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::CellularLocationVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"CellularLocationVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'ChemicalStructure', '")
                 .append(QString::number(UniPAX::ClassType::ChemicalStructure))
                 .append("', NULL, NULL, NULL, NULL FROM \"ChemicalStructure\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Complex', '")
                 .append(QString::number(UniPAX::ClassType::Complex))
                 .append("', standardName, displayName, NULL, dataSource FROM \"Complex\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'ComplexAssembly', '")
                 .append(QString::number(UniPAX::ClassType::ComplexAssembly))
                 .append("', NULL, NULL, NULL, NULL FROM \"ComplexAssembly\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Constraint', '")
                 .append(QString::number(UniPAX::ClassType::Constraint))
                 .append("', NULL, NULL, NULL, NULL FROM \"Constraint\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Control', '")
                 .append(QString::number(UniPAX::ClassType::Control))
                 .append("', NULL, NULL, NULL, NULL FROM \"Control\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'ControlledVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::ControlledVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"ControlledVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Conversion', '")
                 .append(QString::number(UniPAX::ClassType::Conversion))
                 .append("', NULL, NULL, NULL, NULL FROM \"Conversion\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'CovalentBindingFeature', '")
                 .append(QString::number(UniPAX::ClassType::CovalentBindingFeature))
                 .append("', NULL, NULL, NULL, NULL FROM \"CovalentBindingFeature\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Degradation', '")
                 .append(QString::number(UniPAX::ClassType::Degradation))
                 .append("', NULL, NULL, NULL, NULL FROM \"Degradation\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Delay', '")
                 .append(QString::number(UniPAX::ClassType::Delay))
                 .aapend(", NULL, NULL, NULL, NULL FROM \"Delay\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'DeltaG', '")
                 .append(QString::number(UniPAX::ClassType::DeltaG))
                 .append("', NULL, NULL, NULL, NULL FROM \"DeltaG\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Dna', '")
                 .append(QString::number(UniPAX::ClassType::Dna))
                 .append("', standardName, displayName, NULL, dataSource FROM \"Dna\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'DnaReference', '")
                 .append(QString::number(UniPAX::ClassType::DnaReference))
                 .append("', standardName, displayName, organism, NULL FROM \"DnaReference\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'DnaRegion', '")
                 .append(QString::number(UniPAX::ClassType::DnaRegion))
                 .append("', standardName, displayName, NULL, dataSource FROM \"DnaRegion\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'DnaRegionReference', '")
                 .append(QString::number(UniPAX::ClassType::DnaRegionReference))
                 .append("', standardName, displayName, organism, NULL FROM \"DnaRegionReference\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Entity', '")
                 .append(QString::number(UniPAX::ClassType::Entity))
                 .append("', standardName, displayName, NULL, dataSource FROM \"Entity\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'EntityFeature', '")
                 .append(QString::number(UniPAX::ClassType::EntityFeature))
                 .append("', NULL, NULL, NULL, NULL FROM \"EntityFeature\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'EntityReference', '")
                 .append(QString::number(UniPAX::ClassType::EntityReference))
                 .append("', standardName, displayName, NULL, NULL FROM \"EntityReference\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'EntityReferenceTypeVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::EntityReferenceTypeVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"EntityReferenceTypeVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Event', '")
                 .append(QString::number(UniPAX::ClassType::Event))
                 .append("', NULL, NULL, NULL, NULL FROM \"Event\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'EventAssignment', '")
                 .append(QString::number(UniPAX::ClassType::EventAssignment))
                 .append("', NULL, NULL, NULL, NULL FROM \"EventAssignment\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Evidence', '")
                 .append(QString::number(UniPAX::ClassType::Evidence))
                 .append("', NULL, NULL, NULL, NULL FROM \"Evidence\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'EvidenceCodeVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::EvidenceCodeVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"EvidenceCodeVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Experiment', '")
                 .append(QString::number(UniPAX::ClassType::Experiment))
                 .append("', NULL, NULL, NULL, NULL FROM \"Experiment\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'ExperimentalForm', '")
                 .append(QString::number(UniPAX::ClassType::ExperimentalForm))
                 .append("', NULL, NULL, NULL, NULL FROM \"ExperimentalForm\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'ExperimentalFormVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::ExperimentalFormVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"ExperimentalFormVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'FragmentFeature', '")
                 .append(QString::number(UniPAX::ClassType::FragmentFeature))
                 .append("', NULL, NULL, NULL, NULL FROM \"FragmentFeature\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'FunctionDefinition', '")
                 .append(QString::number(UniPAX::ClassType::FunctionDefinition))
                 .append("', NULL, NULL, NULL, NULL FROM \"FunctionDefinition\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Gene', '")
                 .append(QString::number(UniPAX::ClassType::Gene))
                 .append("', standardName, displayName, organism, dataSource FROM \"Gene\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'GeneticInteraction', '")
                 .append(QString::number(UniPAX::ClassType::GeneticInteraction))
                 .append("', NULL, NULL, NULL, NULL FROM \"GeneticInteraction\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'ImportSource', '")
                 .append(QString::number(UniPAX::ClassType::ImportSource))
                 .append("', NULL, NULL, NULL, NULL FROM \"ImportSource\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'InitialAssignment', '")
                 .append(QString::number(UniPAX::ClassType::InitialAssignment))
                 .append("', NULL, NULL, NULL, NULL FROM \"InitialAssignment\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Interaction', '")
                 .append(QString::number(UniPAX::ClassType::Interaction))
                 .append("', NULL, NULL, NULL, NULL FROM \"Interaction\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'InteractionVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::InteractionVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"InteractionVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'KPrime', '")
                 .append(QString::number(UniPAX::ClassType::KPrime))
                 .append("', NULL, NULL, NULL, NULL FROM \"KPrime\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'KineticLaw', '")
                 .append(QString::number(UniPAX::ClassType::KineticLaw))
                 .append("', NULL, NULL, NULL, NULL FROM \"KineticLaw\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'LocalParameter', '")
                         .append(QString::number(UniPAX::ClassType::LocalParameter))
                         .append("', NULL, NULL, NULL, NULL FROM \"LocalParameter\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'IdMapping', '")
                 .append(QString::number(UniPAX::ClassType::IdMapping))
                 .append("', NULL, NULL, NULL, NULL FROM \"IdMapping\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Math', '")
                 .append(QString::number(UniPAX::ClassType::Math))
                 .append("', NULL, NULL, NULL, NULL FROM \"Math\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Model', '")
                 .append(QString::number(UniPAX::ClassType::Model))
                 .append("', NULL, NULL, NULL, NULL FROM \"Model\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'ModificationFeature', '")
                 .append(QString::number(UniPAX::ClassType::ModificationFeature))
                 .append("', NULL, NULL, NULL, NULL FROM \"ModificationFeature\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Modulation', '")
                 .append(QString::number(UniPAX::ClassType::Modulation))
                 .append("', NULL, NULL, NULL, NULL FROM \"Modulation\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'MolecularInteraction', '")
                 .append(QString::number(UniPAX::ClassType::MolecularInteraction))
                 .append("', NULL, NULL, NULL, NULL FROM \"MolecularInteraction\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Parameter', '")
                 .append(QString::number(UniPAX::ClassType::Parameter))
                 .append("', NULL, NULL, NULL, NULL FROM \"Parameter\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Pathway', '")
                 .append(QString::number(UniPAX::ClassType::Pathway))
                 .append("', standardName, displayName, organism, dataSource FROM \"Pathway\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'PathwayStep', '")
                 .append(QString::number(UniPAX::ClassType::PathwayStep))
                 .append("', NULL, NULL, NULL, NULL FROM \"PathwayStep\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'PhenotypeVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::PhenotypeVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"PhenotypeVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'PhysicalEntity', '")
                 .append(QString::number(UniPAX::ClassType::PhysicalEntity))
                 .append("', NULL, NULL, NULL, NULL FROM \"PhysicalEntity\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Priority', '")
                 .append(QString::number(UniPAX::ClassType::Priority))
                 .append("', NULL, NULL, NULL, NULL FROM \"Priority\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Protein', '")
                 .append(QString::number(UniPAX::ClassType::Protein))
                 .append("', standardName, displayName, NULL, dataSource FROM \"Protein\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'ProteinReference', '")
                 .append(QString::number(UniPAX::ClassType::ProteinReference))
                 .append("', standardName, displayName, organism, NULL FROM ProteinReference"));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Provenance', '")
                 .append(QString::number(UniPAX::ClassType::Provenance))
                 .append("', standardName, displayName, NULL, NULL FROM \"Provenance\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'PublicationXref', '")
                 .append(QString::number(UniPAX::ClassType::PublicationXref))
                 .append("', NULL, NULL, NULL, NULL FROM \"PublicationXref\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'RateRule', '")
                 .append(QString::number(UniPAX::ClassType::RateRule))
                 .append("', NULL, NULL, NULL, NULL FROM \"RateRule\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'RelationshipTypeVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::RelationshipTypeVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"RelationshipTypeVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'RelationshipXref', '")
                 .append(QString::number(UniPAX::ClassType::RelationshipXref))
                 .append("', NULL, NULL, NULL, NULL FROM \"RelationshipXref\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Rna', '")
                 .append(QString::number(UniPAX::ClassType::Rna))
                 .append("', standardName, displayName, NULL, dataSource FROM \"Rna\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'RnaReference', '")
                 .append(QString::number(UniPAX::ClassType::RnaReference))
                 .append("', standardName, displayName, organism, NULL FROM \"RnaReference\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'RnaRegion', '")
                 .append(QString::number(UniPAX::ClassType::RnaRegion))
                 .append("', standardName, displayName, NULL, dataSource FROM \"RnaRegion\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'RnaRegionReference', '")
                 .append(QString::number(UniPAX::ClassType::RnaRegionReference))
                 .append("', standardName, displayName, organism, NULL FROM \"RnaRegionReference\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Rule', '")
                 .append(QString::number(UniPAX::ClassType::Rule))
                 .append("', NULL, NULL, NULL, NULL FROM \"Rule\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'SBase', '")
                 .append(QString::number(UniPAX::ClassType::SBase))
                 .append("', NULL, NULL, NULL, NULL FROM \"SBase\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Sample', '")
                 .append(QString::number(UniPAX::ClassType::Sample))
                 .append("', NULL, NULL, NULL, NULL FROM \"Sample\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Score', '")
                 .append(QString::number(UniPAX::ClassType::Score))
                 .append("', NULL, NULL, NULL, NULL FROM \"Score\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'SequenceInterval', '")
                 .append(QString::number(UniPAX::ClassType::SequenceInterval))
                 .append("', NULL, NULL, NULL, NULL FROM \"SequenceInterval\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'SequenceLocation', '")
                 .append(QString::number(UniPAX::ClassType::SequenceLocation))
                 .append("', NULL, NULL, NULL, NULL FROM \"SequenceLocation\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'SequenceModificationVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::SequenceModificationVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"SequenceModificationVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'SequenceRegionVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::SequenceRegionVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"SequenceRegionVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'SequenceSite', '")
                 .append(QString::number(UniPAX::ClassType::SequenceSite))
                 .append("', NULL, NULL, NULL, NULL FROM \"SequenceSite\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'SmallMolecule', '")
                 .append(QString::number(UniPAX::ClassType::SmallMolecule))
                 .append("', NULL, NULL, NULL, NULL FROM \"SmallMolecule\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'SmallMoleculeReference', '")
                 .append(QString::number(UniPAX::ClassType::SmallMoleculeReference))
                 .append("', NULL, NULL, NULL, NULL FROM \"SmallMoleculeReference\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Stoichiometry', '")
                 .append(QString::number(UniPAX::ClassType::Stoichiometry))
                 .append("', NULL, NULL, NULL, NULL FROM \"Stoichiometry\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'TemplateReaction', '")
                 .append(QString::number(UniPAX::ClassType::TemplateReaction))
                 .append("', NULL, NULL, NULL, NULL FROM \"TemplateReaction\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'TemplateReactionRegulation', '")
                 .append(QString::number(UniPAX::ClassType::TemplateReactionRegulation))
                 .append("', NULL, NULL, NULL, NULL FROM \"TemplateReactionRegulation\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Thing', '")
                 .append(QString::number(UniPAX::ClassType::Thing))
                 .append("', NULL, NULL, NULL, NULL FROM \"Thing\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'TissueVocabulary', '")
                 .append(QString::number(UniPAX::ClassType::TissueVocabulary))
                 .append("', NULL, NULL, NULL, NULL FROM \"TissueVocabulary\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Transport', '")
                 .append(QString::number(UniPAX::ClassType::Transport))
                 .append("', NULL, NULL, NULL, NULL FROM \"Transport\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'TransportWithBiochemicalReaction', '")
                 .append(QString::number(UniPAX::ClassType::TransportWithBiochemicalReaction))
                 .append("', NULL, NULL, NULL, NULL FROM \"TransportWithBiochemicalReaction\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Trigger', '")
                 .append(QString::number(UniPAX::ClassType::Trigger))
                 .append("', NULL, NULL, NULL, NULL FROM \"Trigger\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'UPBase', '")
                 .append(QString::number(UniPAX::ClassType::UPBase))
                 .append("', NULL, NULL, NULL, NULL FROM \"UPBase\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'UnificationXref', '")
                 .append(QString::number(UniPAX::ClassType::UnificationXref))
                 .append("', NULL, NULL, NULL, NULL FROM \"UnificationXref\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Unit', '")
                 .append(QString::number(UniPAX::ClassType::Unit))
                 .append("', NULL, NULL, NULL, NULL FROM \"Unit\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'UnitDefinition', '")
                 .append(QString::number(UniPAX::ClassType::UnitDefinition))
                 .append("', NULL, NULL, NULL, NULL FROM \"UnitDefinition\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'UtilityClass', '")
                 .append(QString::number(UniPAX::ClassType::UtilityClass))
                 .append("', NULL, NULL, NULL, NULL FROM \"UtilityClass\""));

        db->exec(QString("INSERT INTO Q_ATTRIBUTE_INDEX (unipaxId, type, typeId, standardName, displayName, organism, dataSource) SELECT \"unipaxId\", 'Xref', '")
                 .append(QString::number(UniPAX::ClassType::Xref))
                 .append("', NULL, NULL, NULL, NULL FROM \"Xref\""));


	std::cout << "finished." << std::endl;
}



void UniPAX::SERVER::OracleQueryEngine::rebuildPathwayIndex()
{
	std::cout << "Rebuilding pathway index... " << std::flush;

	checkDatabaseConnection();

	QSqlDatabase* db = manager->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open()) std::cerr << "OracleQueryEngine::rebuildPathwayIndex: Failed to connect oracle with QT";
	}


	db->exec(QString("BEGIN")
				.append("EXECUTE IMMEDIATE 'DROP TABLE Q_PATHWAY_INDEX CASCADE CONSTRAINTS';")
				.append("EXCEPTION")
				.append("  WHEN OTHERS THEN")
				.append("    IF SQLCODE != -942 THEN RAISE; END IF;")
				.append("END;"));
	db->exec(QString("CREATE TABLE Q_PATHWAY_INDEX (")
			.append("unipaxId NUMBER(20) NOT NULL,")
			.append("type VARCHAR2(40) NOT NULL,")
			.append("pathway_unipaxId NUMBER(20) NOT NULL,")
			.append("pathway_standardName VARCHAR2(4000) DEFAULT NULL,")
			.append("PRIMARY KEY(unipaxId, pathway_unipaxId)")
			.append(")"));

	QSqlQuery query = db->exec(QString("select \"unipaxId\", \"standardName\" from \"Pathway\""));
	UniPAX::UPBase* current_pathway;
	std::map<std::string, std::string> data_type;
	std::map<UnipaxId, std::string>::iterator map_it;
	std::map<std::string, std::string>::iterator map_it2;
	std::map<UnipaxId, std::string> pathway_map;

	while (query.next())
	{
		pathway_map[query.value(0).toLongLong()] = query.value(1).toString().toStdString();
	}

	for (map_it = pathway_map.begin(); map_it != pathway_map.end(); map_it++)
	{
		boost::shared_ptr<UniPAX::UPBase> current_pathway = getObject(map_it->first);

		if (current_pathway != 0)
		{
	//		std::cout << map_it->first << " | " << current_pathway->get_unipaxId() << std::endl;

	//		std::cout << "start collecting: " << map_it->second << " ... ";
			UniPAX::KernelCollector collector;
			collector.skipPathwaySteps(true);
			collector.collect(current_pathway);
	//		std::cout << " cache ... ";
			data_type = collector.getIdToType();
			for (map_it2 = data_type.begin(); map_it2 != data_type.end(); map_it2++)
			{
	//			std::cout << QString("INSERT INTO Q_PATHWAY_INDEX (unipaxId, type, pathway_unipaxId, pathway_standardName) VALUES (%1,%2,%3,%4)").arg(QString(map_it2->first.c_str()),QString(map_it2->second.c_str()),QString::number(map_it->first),QString(map_it->second.c_str())).toStdString() << std::endl;
				db->exec(QString("INSERT INTO Q_PATHWAY_INDEX (unipaxId, type, pathway_unipaxId, pathway_standardName) VALUES (%1,'%2',%3,'%4')").arg(QString(map_it2->first.c_str()),QString(map_it2->second.c_str()),QString::number(map_it->first),QString(map_it->second.c_str())));
			}
		}

//		std::cout << " done! " << std::endl;
	}



	std::cout << "finished." << std::endl;
}



boost::shared_ptr<UniPAX::DBManager> UniPAX::SERVER::OracleQueryEngine::getDBManager()
{
	return manager;
}

boost::shared_ptr<UniPAX::UPBase> UniPAX::SERVER::OracleQueryEngine::getObject(UnipaxId id)
{
	checkDatabaseConnection();

	if (id > 0 && manager->isValid(id))
	{
		return boost::dynamic_pointer_cast<UniPAX::DBManager>(manager)->getObjectByID(id);
	}

	return boost::shared_ptr<UniPAX::UPBase>();
}

bool UniPAX::SERVER::OracleQueryEngine::getObjects(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> ids)
{
	checkDatabaseConnection();

	if (!ids.empty())
	{
		std::vector<UnipaxId>::iterator it = ids.begin();
		while (it != ids.end())
		{
			if (*it > 0 && manager->isValid(*it))
			{
				it++;
			}
			else
			{
				it = ids.erase(it);
			}
		}
		return boost::dynamic_pointer_cast<UniPAX::DBManager>(manager)->getObjectsByIDs(result, ids);
	}

	return false;
}

bool UniPAX::SERVER::OracleQueryEngine::getObjectsByType(QByteArray& data, QString type)
{

	std::cout << "getObjectsByType: " << type.toStdString() << std::endl;

	checkDatabaseConnection();
	QXmlStreamWriter out(&data);
	out.setCodec("UTF-8");
	if (manager->getDatabase()->isValid())
	{
		KernelCollector collector;

		boost::shared_ptr<odb::database> db = manager->getOdbDatabase();

		if (!manager->getDatabase()->isOpen())
		{
			if (!manager->getDatabase()->open()) std::cerr << "OracleQueryEngine::getObjectsByType: Failed to connect oracle with QT";
		}

		// need to shorten the type due to Oracle specifications for table names
		type = QString::fromStdString(UniPAX::Kernel::shortType(type.toStdString()));

		QSqlQuery query = manager->getDatabase()->exec(QString("SELECT \"unipaxId\" FROM \"%1\"").arg(type));
		std::vector<UnipaxId> ids;
		while (query.next())
		{
			UnipaxId id = query.value(0).toULongLong();
			ids.push_back(id);
		}
		std::vector<boost::shared_ptr<UniPAX::UPBase> > result;

		boost::dynamic_pointer_cast<UniPAX::DBManager>(manager)->getObjectsByIDs(result, ids);

		for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::const_iterator it(result.begin()); it != result.end(); it++)
		{
			collector.collect(*it);
		}

		BIOPAXWriter writer;
		writer.setPersistenceManager(collector);

		writer.write(out);
		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;
}

bool UniPAX::SERVER::OracleQueryEngine::getIDsByName(QByteArray& data, QString name)
{

	if (name.length() < 3)
	{
		data.append("ERROR: at least three characters required.\n");
		return false;
	}

	if (manager->getDatabase() != 0)
	{
		checkDatabaseConnection();
		boost::shared_ptr<odb::database> db = manager->getOdbDatabase();

		UnipaxId c = 0;



		if (!manager->getDatabase()->isOpen())
		{
			if (!manager->getDatabase()->open()) std::cerr << "OracleQueryEngine::getIDsByName: Failed to connect oracle with QT";
		}

		std::map<QString, QString> org_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"BioSource\"");
		while (query.next())
		{
			org_map[query.value(0).toString().toUtf8()] = query.value(1).toString().toUtf8();
		}
		query.finish();

		std::map<QString, QString> datasource_map;
		query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"Provenance\"");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();


		data.append("% unipaxId\ttype\tstandardName\tdisplayName\torganism\tname value\tdataSource\n");

		QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId WHERE Q_NAME_INDEX.value LIKE '%1'").arg(name.prepend('%').append('%')));
//		std::cout << sql.toStdString() << std::endl;
		query = manager->getDatabase()->exec(sql);
		while (query.next())
		{
			data.append(query.value(0).toString().toUtf8());
			data.append('\t');
			data.append(query.value(1).toString().toUtf8());
			data.append('\t');
			if (query.value(2).isNull())
				data.append("NULL");
			else
				data.append(query.value(2).toString().toUtf8());
			data.append('\t');
			if (query.value(3).isNull())
				data.append("NULL");
			else
				data.append(query.value(3).toString().toUtf8());
			data.append('\t');
			if (query.value(4).isNull())
				data.append("NULL");
			else
			{
				if (org_map.find(query.value(4).toString().toUtf8()) != org_map.end())
					data.append(org_map[query.value(4).toString().toUtf8()]);
				else
					data.append(query.value(4).toString().toUtf8());
			}
			data.append('\t');
			if (query.value(5).isNull())
				data.append("NULL");
			else
				data.append(query.value(5).toString().toUtf8());
			data.append('\t');
			if (query.value(6).isNull())
				data.append("NULL");
			else
			{
				if (datasource_map.find(query.value(6).toString().toUtf8()) != datasource_map.end())
					data.append(datasource_map[query.value(6).toString().toUtf8()]);
				else
					data.append(query.value(6).toString().toUtf8());
			}

			data.append('\n');
			c++;
		}
		query.finish();

		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;
}

bool UniPAX::SERVER::OracleQueryEngine::getAttributesForType(QString type, const std::vector<QString> & attributes, std::map<UnipaxId, std::vector<QString> > & result, bool derived )
{
	result.clear();
	if (manager->getDatabase() != 0)
	{
		checkDatabaseConnection();
		boost::shared_ptr<odb::database> db = manager->getOdbDatabase();

		if (!manager->getDatabase()->isOpen())
		{
			if (!manager->getDatabase()->open()) std::cerr << "OracleQueryEngine::getIDsByType: Failed to connect oracle with QT";
		}

		std::map<QString, QString> org_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"BioSource\"");
		while (query.next())
		{
			org_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();

		std::map<QString, QString> datasource_map;
		query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"Provenance\"");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();

		std::vector<std::string> types;
		types.push_back(type.toStdString());

		if (derived)
		{
			std::set<std::string> derived_types = UniPAX::Kernel::children(type.toStdString(), true);
			types.insert(types.end(), derived_types.begin(), derived_types.end());
		}

		for (std::vector<std::string>::const_iterator type_iter = types.begin(); type_iter != types.end(); type_iter++)
		{
			QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX WHERE Q_ATTRIBUTE_INDEX.type = '%1'").arg(QString::fromStdString(*type_iter)));
//			std::cout << sql.toStdString() << std::endl;
			query = manager->getDatabase()->exec(sql);
			while (query.next())
			{
				std::vector<QString> tmp;

				UnipaxId id = query.value(0).toULongLong();

				for (int i = 0; i < attributes.size(); ++i)
				{
					if (attributes[i] == "type")
						tmp.push_back(query.value(1).toString());
					else if (attributes[i] == "standardName" || attributes[i] == "name")
						tmp.push_back(query.value(2).toString());
					else if (attributes[i] == "displayName")
						tmp.push_back(query.value(3).toString());
					else if (attributes[i] == "organism")
					{
						if (org_map.find(query.value(4).toString()) != org_map.end())
							tmp.push_back(org_map[query.value(4).toString()]);
						else
							tmp.push_back(query.value(4).toString());
					}
					else if (attributes[i] == "dataSource")
					{
						if (datasource_map.find(query.value(5).toString()) != datasource_map.end())
							tmp.push_back(datasource_map[query.value(5).toString()]);
						else
							tmp.push_back(query.value(5).toString());
					}
					else
						tmp.push_back("?");
				}

				result[id] = tmp;
			}
			query.finish();
		}

		return !result.empty();

	}

	return false;
}

bool UniPAX::SERVER::OracleQueryEngine::getAttributes(UnipaxId id, const std::vector<QString> & attributes, std::vector<QString> & result  )
{
	result.clear();
	if (manager->getDatabase() != 0)
	{
		checkDatabaseConnection();
		boost::shared_ptr<odb::database> db = manager->getOdbDatabase();

		if (!manager->getDatabase()->isOpen())
		{
			if (!manager->getDatabase()->open()) std::cerr << "OracleQueryEngine::getIDsByType: Failed to connect oracle with QT";
		}

		std::map<QString, QString> org_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"BioSource\"");
		while (query.next())
		{
			org_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();

		std::map<QString, QString> datasource_map;
		query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"Provenance\"");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();

		QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX WHERE Q_ATTRIBUTE_INDEX.unipaxId = %1").arg(id));
		query = manager->getDatabase()->exec(sql);
		if (query.next())
		{
			for (int i = 0; i < attributes.size(); ++i)
			{
				if (attributes[i] == "id")
					result.push_back(query.value(0).toString());
				else if (attributes[i] == "type")
					result.push_back(query.value(1).toString());
				else if (attributes[i] == "standardName" || attributes[i] == "name")
					result.push_back(query.value(2).toString());
				else if (attributes[i] == "displayName")
					result.push_back(query.value(3).toString());
				else if (attributes[i] == "organism")
				{
					if (org_map.find(query.value(4).toString()) != org_map.end())
						result.push_back(org_map[query.value(4).toString()]);
					else
						result.push_back(query.value(4).toString());
				}
				else if (attributes[i] == "dataSource")
				{
					if (datasource_map.find(query.value(5).toString()) != datasource_map.end())
						result.push_back(datasource_map[query.value(5).toString()]);
					else
						result.push_back(query.value(5).toString());
				}
				else
					result.push_back("?");
			}

			return true;
		}

	}

	return false;
}

bool UniPAX::SERVER::OracleQueryEngine::getIDsByType(QByteArray& data, QString type)
{
	if (manager->getDatabase() != 0)
	{
		checkDatabaseConnection();
		boost::shared_ptr<odb::database> db = manager->getOdbDatabase();

		UnipaxId c = 0;

		if (!manager->getDatabase()->isOpen())
		{
			if (!manager->getDatabase()->open()) std::cerr << "OracleQueryEngine::getIDsByType: Failed to connect oracle with QT";
		}

		std::map<QString, QString> org_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"BioSource\"");
		while (query.next())
		{
			org_map[query.value(0).toString().toUtf8()] = query.value(1).toString().toUtf8();
		}
		query.finish();

		std::map<QString, QString> datasource_map;
		query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"Provenance\"");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();

		data.append("% unipaxId\ttype\tstandardName\tdisplayName\torganism\tdataSource\n");

		QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX WHERE Q_ATTRIBUTE_INDEX.type = '%1'").arg(type));
		query = manager->getDatabase()->exec(sql);
		while (query.next())
		{
			data.append(query.value(0).toString().toUtf8());
			data.append('\t');
			data.append(query.value(1).toString().toUtf8());
			data.append('\t');
			if (query.value(2).isNull())
				data.append("NULL");
			else
				data.append(query.value(2).toString().toUtf8());
			data.append('\t');
			if (query.value(3).isNull())
				data.append("NULL");
			else
				data.append(query.value(3).toString().toUtf8());
			data.append('\t');
			if (query.value(4).isNull())
				data.append("NULL");
			else
			{
				if (org_map.find(query.value(4).toString().toUtf8()) != org_map.end())
					data.append(org_map[query.value(4).toString().toUtf8()]);
				else
					data.append(query.value(4).toString().toUtf8());
			}
			data.append('\t');
			if (query.value(5).isNull())
				data.append("NULL");
			else
			{
				if (datasource_map.find(query.value(5).toString().toUtf8()) != datasource_map.end())
					data.append(datasource_map[query.value(5).toString().toUtf8()]);
				else
					data.append(query.value(5).toString().toUtf8());
			}
			data.append('\n');
			c++;
		}

		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;
}

bool UniPAX::SERVER::OracleQueryEngine::getPathwaysOfAllGeneIDs(QByteArray& data)
{

//	std::cout << "getPathwaysOfAllGeneIDs " << std::endl;

	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open()) std::cerr << "MySQLQueryEngine::getPathwaysOfAllGeneIDs: Failed to connect mysql with QT";
	}

	if (manager->getDatabase()->isValid())
	{
		std::map<QString, QString> datasource_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"Provenance\"");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();

		QSqlQuery query2; //, query3;
		query = manager->getDatabase()->exec("select distinct r.\"id\"  from Q_PATHWAY_INDEX q, \"RelationshipXref\" r "
				" where q.type = 'RelationshipXref' "
				" and q.unipaxId = r.\"unipaxId\" and r.\"db\" = 'EntrezGene' order by r.\"id\"");
		while (query.next())
		{
			QString current_gene_id = query.value(0).toString().toUtf8();
			data.append(current_gene_id);
			std::cout << current_gene_id.toStdString() << std::endl;

			query2 = manager->getDatabase()->exec(QString("select DISTINCT q.pathway_unipaxId, q.pathway_standardName, a.dataSource "
					"from Q_PATHWAY_INDEX q, Q_ATTRIBUTE_INDEX a, \"RelationshipXref\" r where q.type = 'RelationshipXref' "
					"and q.unipaxId = r.\"unipaxId\" and r.\"db\" = 'EntrezGene' "
					"and r.\"id\" = '%1' and a.unipaxId = q.pathway_unipaxId ").arg(current_gene_id));
			while (query2.next())
			{
//				QString unipax_id = query2.value(0).toString().toUtf8();
//
//				QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX WHERE Q_ATTRIBUTE_INDEX.unipaxId = '%1'").arg(unipax_id));
//				query3 = manager->getDatabase()->exec(sql);
//				while (query3.next())
//				{
					data.append('\t');
					data.append(query2.value(1).toString().toUtf8());
					data.append(" | ");
					if (query2.value(2).isNull())
						data.append("NULL");
					else
					{
						if (datasource_map.find(query2.value(2).toString().toUtf8()) != datasource_map.end())
							data.append(datasource_map[query2.value(2).toString().toUtf8()]);
						else
							data.append(query2.value(2).toString().toUtf8());
					}
					data.append(" | ");
					data.append(query2.value(0).toString().toUtf8());
//				}
			}
			data.append('\n');

		}
		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;

}


bool UniPAX::SERVER::OracleQueryEngine::getPathwaysOfGeneID(QByteArray& data, QString id)
{

//	std::cout << "getPathwaysOfGeneID: " << id.toStdString() << std::endl;

//	data.append("% unipaxId\tstandardName\n");
	data.append("% unipaxId\ttype\tstandardName\tdisplayName\torganism\tname value\tdataSource\n");

	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open()) std::cerr << "OracleQueryEngine::getPathwaysOfGeneID: Failed to connect oracle with QT";
	}


	if (manager->getDatabase()->isValid())
	{

		std::map<QString, QString> org_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"BioSource\"");
		while (query.next())
		{
			org_map[query.value(0).toString().toUtf8()] = query.value(1).toString().toUtf8();
		}
		query.finish();

		std::map<QString, QString> datasource_map;
		query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"Provenance\"");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();
//
//
//		QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, "
//				"Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value FROM Q_ATTRIBUTE_INDEX "
//				"INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId "
//				"WHERE Q_ATTRIBUTE_INDEX.unipaxId in (select distinct DISTINCT q.pathway_unipaxId "
//				"from Q_PATHWAY_INDEX q, RelationshipXref r where q.type = 'RelationshipXref' "
//				"and q.unipaxId = r.unipaxId and r.db = 'Entrez Gene' "
//				"and r.id = '%1')").arg(id));
//
//		query = manager->getDatabase()->exec(sql);

		QSqlQuery query2;
		query = manager->getDatabase()->exec(QString("select distinct q.pathway_unipaxId, q.pathway_standardName "
				"from Q_PATHWAY_INDEX q, \"RelationshipXref\" r where q.type = 'RelationshipXref' "
				"and q.unipaxId = r.\"unipaxId\" and r.\"db\" = 'EntrezGene' "
				"and r.\"id\" = '%1'").arg(id));
		while (query.next())
		{
			QString unipax_id = query.value(0).toString().toUtf8();
//			data.append(query.value(0).toString().toUtf8());
//			data.append('\t');
//			data.append(query.value(1).toString().toUtf8());
//			data.append('\n');

			QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId WHERE Q_ATTRIBUTE_INDEX.unipaxId = '%1'").arg(unipax_id));
			query2 = manager->getDatabase()->exec(sql);
			while (query2.next())
			{
				data.append(query2.value(0).toString().toUtf8());
				data.append('\t');
				data.append(query2.value(1).toString().toUtf8());
				data.append('\t');
				if (query2.value(2).isNull())
					data.append("NULL");
				else
					data.append(query2.value(2).toString().toUtf8());
				data.append('\t');
				if (query2.value(3).isNull())
					data.append("NULL");
				else
					data.append(query2.value(3).toString().toUtf8());
				data.append('\t');
				if (query2.value(4).isNull())
					data.append("NULL");
				else
				{
					if (org_map.find(query2.value(4).toString().toUtf8()) != org_map.end())
						data.append(org_map[query2.value(4).toString().toUtf8()]);
					else
						data.append(query2.value(4).toString().toUtf8());
				}
				data.append('\t');
				if (query2.value(5).isNull())
					data.append("NULL");
				else
					data.append(query2.value(5).toString().toUtf8());
				data.append('\t');
				if (query2.value(6).isNull())
					data.append("NULL");
				else
				{
					if (datasource_map.find(query2.value(6).toString().toUtf8()) != datasource_map.end())
						data.append(datasource_map[query2.value(6).toString().toUtf8()]);
					else
						data.append(query2.value(6).toString().toUtf8());
				}

				data.append('\n');
			}
		}
		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;
}

bool UniPAX::SERVER::OracleQueryEngine::getPathwaysOf(QByteArray& data, QString id)
{

	std::cout << "getPathwaysOf: " << id.toStdString() << std::endl;

//	data.append("% unipaxId\tstandardName\n");
	data.append("% unipaxId\ttype\tstandardName\tdisplayName\torganism\tname value\tdataSource\n");

	checkDatabaseConnection();
	if (!manager->getDatabase()->isOpen())
	{
		if (!manager->getDatabase()->open()) std::cerr << "OracleQueryEngine::getPathwaysOf: Failed to connect oracle with QT";
	}


	if (manager->getDatabase()->isValid())
	{

		std::map<QString, QString> org_map;
		QSqlQuery query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"BioSource\"");
		while (query.next())
		{
			org_map[query.value(0).toString().toUtf8()] = query.value(1).toString().toUtf8();
		}
		query.finish();

		std::map<QString, QString> datasource_map;
		query = manager->getDatabase()->exec("SELECT \"unipaxId\", \"standardName\" FROM \"Provenance\"");
		while (query.next())
		{
			datasource_map[query.value(0).toString()] = query.value(1).toString();
		}
		query.finish();

		QSqlQuery query2;
		query = manager->getDatabase()->exec(QString("SELECT DISTINCT pathway_unipaxId, pathway_standardName FROM Q_PATHWAY_INDEX WHERE unipaxId = %1").arg(id));
		while (query.next())
		{
//			data.append(query.value(0).toString().toUtf8());
//			data.append('\t');
//			data.append(query.value(1).toString().toUtf8());
//			data.append('\n');

			QString unipax_id = query.value(0).toString().toUtf8();
			QString sql(QString("SELECT DISTINCT Q_ATTRIBUTE_INDEX.unipaxId, Q_ATTRIBUTE_INDEX.type, Q_ATTRIBUTE_INDEX.standardName, Q_ATTRIBUTE_INDEX.displayName, Q_ATTRIBUTE_INDEX.organism, Q_NAME_INDEX.value, Q_ATTRIBUTE_INDEX.dataSource FROM Q_ATTRIBUTE_INDEX INNER JOIN Q_NAME_INDEX ON Q_ATTRIBUTE_INDEX.unipaxId = Q_NAME_INDEX.unipaxId WHERE Q_ATTRIBUTE_INDEX.unipaxId = '%1'").arg(unipax_id));
			query2 = manager->getDatabase()->exec(sql);
			while (query2.next())
			{
				data.append(query2.value(0).toString().toUtf8());
				data.append('\t');
				data.append(query2.value(1).toString().toUtf8());
				data.append('\t');
				if (query2.value(2).isNull())
					data.append("NULL");
				else
					data.append(query2.value(2).toString().toUtf8());
				data.append('\t');
				if (query2.value(3).isNull())
					data.append("NULL");
				else
					data.append(query2.value(3).toString().toUtf8());
				data.append('\t');
				if (query2.value(4).isNull())
					data.append("NULL");
				else
				{
					if (org_map.find(query2.value(4).toString().toUtf8()) != org_map.end())
						data.append(org_map[query2.value(4).toString().toUtf8()]);
					else
						data.append(query2.value(4).toString().toUtf8());
				}
				data.append('\t');
				if (query2.value(5).isNull())
					data.append("NULL");
				else
					data.append(query2.value(5).toString().toUtf8());
				data.append('\t');
				if (query2.value(6).isNull())
					data.append("NULL");
				else
				{
					if (datasource_map.find(query2.value(6).toString().toUtf8()) != datasource_map.end())
						data.append(datasource_map[query2.value(6).toString().toUtf8()]);
					else
						data.append(query2.value(6).toString().toUtf8());
				}
				data.append('\n');
			}
		}
		return true;
	}
	else
	{
		data.append("Database not available.\n");
	}

	return false;
}

bool UniPAX::SERVER::OracleQueryEngine::search(QByteArray& data, const QUrl& url, QString resultID)
{

	std::cout << "search: " << url.toString().toStdString() << " " << resultID.toStdString() << std::endl;

	QString type = url.queryItemValue("type");

	// need to shorten the type due to Oracle specifications for table names
	type = QString::fromStdString(UniPAX::Kernel::shortType(type.toStdString()));

	std::cout << "Type: " << type.toStdString() << std::endl;

	if (type != "")
	{
		checkDatabaseConnection();
		if (!manager->getDatabase()->isOpen())
		{
			if (!manager->getDatabase()->open()) std::cerr << "OracleQueryEngine::search: Failed to connect oracle with QT";
		}
		if (manager->getDatabase()->isValid())
		{
			QSqlQuery query = manager->getDatabase()->exec("SELECT * FROM \"" + type + "\"");
			while (query.next())
			{
				std::string id = query.value(0).toString().toStdString();

				data.append(id.c_str());
				data.append("\n");
			}

			return true;

		}
		else
		{
			data.append("Database not available.\n");
		}

	}
	else
	{
		data.append("Unknown filter.\n");
	}
	return false;
}

bool UniPAX::SERVER::OracleQueryEngine::checkDatabaseConnection()
{
	QSqlDatabase* db = manager->getDatabase();


	if (!manager->getDatabase()->isOpen())
	{
		db->open();
	}

	QSqlQuery query = db->exec("SELECT 1 FROM DUAL");
	query.next();
	QSqlError error = query.lastError();

	if (error.type() > 0)
	{
		std::cout << "check connection (error code " << error.type() << ")" << std::endl;
		std::cout << "reconnect... ";
		db->open();
		std::cout << "done!" << std::endl;
	}

	return true;


}

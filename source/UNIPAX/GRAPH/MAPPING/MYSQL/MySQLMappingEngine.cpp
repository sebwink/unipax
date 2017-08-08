#include <UNIPAX/GRAPH/MAPPING/MYSQL/MySQLMappingEngine.h>

#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QSqlError>

#include <exception>

UniPAX::GRAPH::mysql::MySQLMappingEngine::MySQLMappingEngine(boost::shared_ptr<UniPAX::DBManager> _db_manager) : UniPAX::GRAPH::MappingEngine(_db_manager)
{

}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::needsRebuildDatabaseCache()
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "MySQLCache::init: Failed to connect mysql with QT";
			return false;
		}
	}

	QSqlQuery q = db->exec("SELECT * FROM C_RELATIONS LIMIT 1");
	if (!q.next())
		return true;
	q.finish();

	q = db->exec("SELECT * FROM C_ENTITY_ORGANISM LIMIT 1");
	if (!q.next())
		return true;
	q.finish();

	q = db->exec("SELECT * FROM C_ENTITY_DBKEY LIMIT 1");
	if (!q.next())
		return true;
	q.finish();

	q = db->exec("SELECT * FROM C_ENTITY_PATHWAY LIMIT 1");
	if (!q.next())
		return true;
	q.finish();

	return false;
}

void UniPAX::GRAPH::mysql::MySQLMappingEngine::rebuildDatabaseCache()
{

	std::cerr << "Init C_RELATION..." << std::flush;

	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "MySQLCache::init: Failed to connect mysql with QT";
			return;
		}
	}

	db->exec("DROP TABLE IF EXISTS C_RELATIONS");
	QSqlQuery query = db->exec(QString("CREATE TABLE C_RELATIONS (")
			.append("source BIGINT(20) UNSIGNED,")
			.append("target BIGINT(20) UNSIGNED,")
			.append("relation VARCHAR(255),")
			.append("PRIMARY KEY (source, target, relation)")
			.append(") ENGINE=MyISAM"));

	if (query.lastError().type() > 0)
		throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());


	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"bindsTo\" FROM BindingFeature_bindsTo");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"xref\" FROM BioSource_xref");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"cofactor\" FROM Catalysis_cofactor");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"component\" FROM Complex_component");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT unipaxId, controlled, \"controlled\" FROM Control");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT unipaxId, controlType, \"controlType\" FROM Control WHERE controlType != ''");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"xref\" FROM ControlledVocabulary_xref");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"leftEntity\" FROM Conversion_leftEntity");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"rightEntity\" FROM Conversion_rightEntity");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"entityReference\" FROM DnaRegion_entityReference");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"entityReference\" FROM Dna_entityReference");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"featureLocation\" FROM EntityFeature_featureLocation");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"memberFeature\" FROM EntityFeature_memberFeature");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"xref\" FROM EntityReference_xref");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"xref\" FROM Entity_xref");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"xref\" FROM Evidence_xref");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"experimentalFeature\" FROM ExperimentalForm_experimentalFeature");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"experimentalFormEntity\" FROM ExperimentalForm_experimentalFormEntity");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"participant\" FROM Interaction_participant");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"constraint\" FROM Model_constraint");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"event\" FROM Model_event");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"functionDefinition\" FROM Model_functionDefinition");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"initialAssignment\" FROM Model_initialAssignment");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"parameter\" FROM Model_parameter");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"rule\" FROM Model_rule");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"unitDefinition\" FROM Model_unitDefinition");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"nextStep\" FROM PathwayStep_nextStep");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"stepProcess\" FROM PathwayStep_stepProcess");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"modelExtensions\" FROM Pathway_modelExtensions");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"pathwayComponent\" FROM Pathway_pathwayComponent");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"pathwayOrder\" FROM Pathway_pathwayOrder");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"feature\" FROM PhysicalEntity_feature");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"memberPhysicalEntity\" FROM PhysicalEntity_memberPhysicalEntity");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"notFeature\" FROM PhysicalEntity_notFeature");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"entityReference\" FROM Protein_entityReference");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"xref\" FROM Provenance_xref");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"entityReference\" FROM RnaRegion_entityReference");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"entityReference\" FROM Rna_entityReference");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"entityReference\" FROM SmallMolecule_entityReference");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT unipaxId, templateEntity, \"templateEntity\" FROM TemplateReaction");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	query = db->exec("INSERT IGNORE INTO C_RELATIONS (source, target, relation) SELECT object_id, value, \"product\" FROM TemplateReaction_product");
	if (query.lastError().type() > 0)
			throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	std::cerr << "finished." << std::endl;

	std::cerr << "Init C_ENTITY_ORGANISM..." << std::flush;

	db->exec("DROP TABLE IF EXISTS C_ENTITY_ORGANISM");
	db->exec(QString("CREATE TABLE C_ENTITY_ORGANISM (")
			.append("entityId BIGINT(21),")
			.append("referenceId BIGINT(21),")
			.append("organismId BIGINT(21),")
			.append("PRIMARY KEY (entityId, referenceId, organismId)")
			.append(") ENGINE=MyISAM"));

	query = db->exec("INSERT IGNORE INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT object_id, unipaxId, organism FROM Protein_entityReference pe LEFT JOIN ProteinReference pr ON (pe.value = pr.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT object_id, unipaxId, organism FROM Dna_entityReference pe LEFT JOIN DnaReference pr ON (pe.value = pr.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT object_id, unipaxId, organism FROM DnaRegion_entityReference pe LEFT JOIN DnaRegionReference pr ON (pe.value = pr.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT object_id, unipaxId, organism FROM Rna_entityReference pe LEFT JOIN RnaReference pr ON (pe.value = pr.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT object_id, unipaxId, organism FROM RnaRegion_entityReference pe LEFT JOIN RnaRegionReference pr ON (pe.value = pr.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	// small molecules do not have organism
	query = db->exec("INSERT IGNORE INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT object_id, value, -1 FROM SmallMolecule_entityReference");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	// special case for complexes, they do not have entity references - the organism will be assigned from the components of the complex.
	query = db->exec("INSERT IGNORE INTO C_ENTITY_ORGANISM (entityId, referenceId, organismId) SELECT DISTINCT cc.object_id, -1, eo.organismId FROM C_ENTITY_ORGANISM eo LEFT JOIN Complex_component cc ON (eo.entityId = cc.value) WHERE object_id > -1");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());

	std::cerr << "finished." << std::endl;

	std::cerr << "Init C_ENTITY_PATHWAY..." << std::flush;

	db->exec("DROP TABLE IF EXISTS C_ENTITY_PATHWAY");
	db->exec(QString("CREATE TABLE C_ENTITY_PATHWAY (")
			.append("entityId BIGINT(21),")
			.append("interactionId BIGINT(21),")
			.append("pathwayId BIGINT(21),")
			.append("PRIMARY KEY (entityId, interactionId, pathwayId)")
			.append(") ENGINE=MyISAM"));

	query = db->exec("INSERT IGNORE INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.value, iip.object_id, pe.object_id FROM Pathway_pathwayComponent pe, Interaction_participant iip WHERE pe.value = iip.object_id");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	// control objects
	query = db->exec("INSERT IGNORE INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.value, iip.object_id, pe.object_id FROM Pathway_pathwayComponent pe, Control_controller iip WHERE pe.value = iip.object_id");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT i.controlled, i.unipaxId, pe.object_id FROM Pathway_pathwayComponent pe, Control i WHERE pe.value = i.unipaxId AND i.controlled != 0");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	// conversion objects
	query = db->exec("INSERT IGNORE INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.value, iip.object_id, pe.object_id FROM Pathway_pathwayComponent pe, Conversion_leftEntity iip WHERE pe.value = iip.object_id");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT iip.value, iip.object_id, pe.object_id FROM Pathway_pathwayComponent pe, Conversion_rightEntity iip WHERE pe.value = iip.object_id");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	// last check all pathway objects ...

	// speed up queries using pathway id range
	UnipaxId pathway_low = DBManager::getBase("Pathway");
	UnipaxId pathway_high = ((pathway_low >> 24) + 1) << 24;

	int numRowsAffected = 1;

	int maxDepth = 20;
	int currentDepth = 0;

	while (numRowsAffected > 0 && currentDepth < maxDepth)
	{

		query = db->exec(QString("INSERT IGNORE INTO C_ENTITY_PATHWAY (entityId, interactionId, pathwayId) SELECT cep.entityId, cep.interactionId, pip.object_id FROM Pathway_pathwayComponent pip, C_ENTITY_PATHWAY cep WHERE pip.value >= %1 AND pip.value < %2 AND pip.value = cep.pathwayId").arg(pathway_low).arg(pathway_high));
		if (query.lastError().type() > 0)
					throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
		numRowsAffected = query.numRowsAffected();

		++currentDepth;
	}

	std::cerr << "finished. Recursion depth: " << currentDepth << std::endl;

	std::cerr << "Init C_ENTITY_DBKEY..." << std::flush;

	db->exec("DROP TABLE IF EXISTS C_ENTITY_DBKEY");
	db->exec(QString("CREATE TABLE C_ENTITY_DBKEY (")
			.append("entityId BIGINT(20) UNSIGNED,")
			.append("db TEXT,")
			.append("id TEXT,")
			.append("PRIMARY KEY (entityId, db(255), id(255))")
			.append(") ENGINE=InnoDB"));

	// entity references

	query = db->exec("INSERT IGNORE INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.object_id, xref.db, xref.id FROM Protein_entityReference pe INNER JOIN EntityReference_xref prx ON (pe.value = prx.object_id) INNER JOIN Xref xref ON (prx.value = xref.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_ENTITY_DBKEY: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.object_id, xref.db, xref.id FROM Dna_entityReference pe INNER JOIN EntityReference_xref prx ON (pe.value = prx.object_id) INNER JOIN Xref xref ON (prx.value = xref.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_ENTITY_DBKEY: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.object_id, xref.db, xref.id FROM DnaRegion_entityReference pe INNER JOIN EntityReference_xref prx ON (pe.value = prx.object_id) INNER JOIN Xref xref ON (prx.value = xref.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_ENTITY_DBKEY: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.object_id, xref.db, xref.id FROM Rna_entityReference pe INNER JOIN EntityReference_xref prx ON (pe.value = prx.object_id) INNER JOIN Xref xref ON (prx.value = xref.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_ENTITY_DBKEY: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.object_id, xref.db, xref.id FROM RnaRegion_entityReference pe INNER JOIN EntityReference_xref prx ON (pe.value = prx.object_id) INNER JOIN Xref xref ON (prx.value = xref.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_ENTITY_DBKEY: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_DBKEY (entityId, db, id) SELECT pe.object_id, xref.db, xref.id FROM SmallMolecule_entityReference pe INNER JOIN EntityReference_xref prx ON (pe.value = prx.object_id) INNER JOIN Xref xref ON (prx.value = xref.unipaxId)");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_ENTITY_DBKEY: " + query.lastQuery().toStdString());

	// entities

	query = db->exec("INSERT IGNORE INTO C_ENTITY_DBKEY (entityId, db, id) SELECT prx.object_id, xref.db, xref.id FROM Entity_xref prx INNER JOIN Xref xref ON (prx.value = xref.unipaxId)");

	std::cerr << "finished." << std::endl;

	std::cerr << "Init C_ENTITY_FEATURES..." << std::flush;

	db->exec(QString("DROP TABLE IF EXISTS C_ENTITY_FEATURES"));
	db->exec(QString("CREATE TABLE C_ENTITY_FEATURES (")
			.append("unipaxId BIGINT(20) UNSIGNED,")
			.append("type VARCHAR(20),")
			.append("value TEXT,")
			.append("PRIMARY KEY (unipaxId, type, value(255))")
			.append(") ENGINE=MyISAM"));


	query = db->exec("INSERT IGNORE INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.object_id, 'modification_feature', smv.term FROM PhysicalEntity_feature pf LEFT JOIN ModificationFeature mf ON (pf.value = mf.unipaxId) LEFT JOIN ControlledVocabulary smv ON (mf.modificationType = smv.unipaxId) WHERE smv.term IS NOT NULL");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	query = db->exec("INSERT IGNORE INTO C_ENTITY_FEATURES (unipaxId, type, value) SELECT pf.object_id, 'feature_comment', comment.value FROM PhysicalEntity_feature pf LEFT JOIN EntityFeature_comment comment ON (pf.value = comment.object_id) WHERE comment.value IS NOT NULL");
	if (query.lastError().type() > 0)
				throw std::runtime_error("Unable to insert into table C_RELATIONS: " + query.lastQuery().toStdString());
	std::cerr << "finished." << std::endl;
}

boost::shared_ptr<UniPAX::GRAPH::RelationsGraph> UniPAX::GRAPH::mysql::MySQLMappingEngine::createRelationsGraph()
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "MySQLCache::createRelationsGraph: Failed to connect mysql with QT";
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

UniPAX::GRAPH::ProteinProteinInteractionNetworkPtr UniPAX::GRAPH::mysql::MySQLMappingEngine::createProteinProteinInteractionNetwork(const ResultObject & result_obj)
{
	BiologicalNetworkPtr nw;
	std::string cacheString = "PPI_" + result_obj.getConstitutingQuery();
	// create network
	ProteinProteinInteractionNetworkPtr ppi(new UniPAX::GRAPH::ProteinProteinInteractionNetwork());
	addInteractions(*ppi, result_obj);
	
	if (network_cache.get(cacheString, nw))
	{
		//return boost::dynamic_pointer_cast<ProteinProteinInteractionNetwork>(nw);
		std::cout << "Found cached Network " << cacheString << ". Still creating new one (Github Issue#4)" << std::endl;
	}
	else
	{
		std::cout << "Creating Network " << cacheString << ". Putting it into Cache, which is not usable (Github Issue#4)" << std::endl;
		network_cache.insert(cacheString, boost::dynamic_pointer_cast<BiologicalNetwork>(ppi));
	}
	return ppi;
}


boost::shared_ptr<UniPAX::GRAPH::ProteinProteinInteractionNetwork> UniPAX::GRAPH::mysql::MySQLMappingEngine::createProteinProteinInteractionNetwork(const std::set<std::string> & physical_entities)
{
	BiologicalNetworkPtr nw;
	std::string cacheString = "PPI_" + collate(physical_entities);
	// create Network
	ProteinProteinInteractionNetworkPtr ppi(new UniPAX::GRAPH::ProteinProteinInteractionNetwork());
	addInteractions(*ppi, physical_entities);
	if (network_cache.get(cacheString, nw))
	{
		//return boost::dynamic_pointer_cast<ProteinProteinInteractionNetwork>(nw);
		std::cout << "Found cached Network " << cacheString << ". Still creating new one (Github Issue#4)" << std::endl;
	}
	else
	{
		std::cout << "Creating Network " << cacheString << ". Putting it into Cache, which is not usable (Github Issue#4)" << std::endl;
		network_cache.insert("PPI_" + collate(physical_entities), boost::dynamic_pointer_cast<BiologicalNetwork>(ppi));
	}
	return ppi;
}

boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> UniPAX::GRAPH::mysql::MySQLMappingEngine::createRegulatoryNetwork(const std::set<std::string> & physical_entities, const UniPAX::ResultObject & result_obj)
{
	BiologicalNetworkPtr nw;
	std::string cacheString = "RGL_" + collate(physical_entities) + result_obj.getConstitutingQuery();
	// create network
	boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> regulatory(new UniPAX::GRAPH::RegulatoryNetwork());
	addTemplateRegulations(*regulatory, physical_entities, result_obj);
	addControlOfBiochemicalReactions(*regulatory, physical_entities, result_obj);
	addControlOfConversions(*regulatory, physical_entities, result_obj);
	if (network_cache.get(cacheString, nw))
	{
		//return boost::dynamic_pointer_cast<RegulatoryNetwork>(nw);
		std::cout << "Found cached Network " << cacheString << ". Still creating new one (Github Issue#4)" << std::endl;
	}
	else
	{
		std::cout << "Creating Network " << cacheString << ". Putting it into Cache, which is not usable (Github Issue#4)" << std::endl;
		network_cache.insert("RGL_" + collate(physical_entities) + result_obj.getConstitutingQuery(), boost::dynamic_pointer_cast<BiologicalNetwork>(regulatory));
	}
	return regulatory;
}

boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> UniPAX::GRAPH::mysql::MySQLMappingEngine::createRegulatoryNetwork(const std::set<std::string> & physical_entities)
{
	BiologicalNetworkPtr nw;
	std::string cacheString = "RGL_" + collate(physical_entities);
	// create network
	boost::shared_ptr<UniPAX::GRAPH::RegulatoryNetwork> regulatory(new UniPAX::GRAPH::RegulatoryNetwork());
	addTemplateRegulations(*regulatory, physical_entities);
	addControlOfBiochemicalReactions(*regulatory, physical_entities);
	addControlOfConversions(*regulatory, physical_entities);
	if (network_cache.get(cacheString, nw))
	{
		//return boost::dynamic_pointer_cast<RegulatoryNetwork>(nw);
		std::cout << "Found cached Network " << cacheString << ". Still creating new one (Github Issue#4)" << std::endl;
	}
	else
	{
		std::cout << "Creating Network " << cacheString << ". Putting it into Cache, which is not usable (Github Issue#4)" << std::endl;
		network_cache.insert("RGL_" + collate(physical_entities), boost::dynamic_pointer_cast<BiologicalNetwork>(regulatory));
	}
	return regulatory;
}

boost::shared_ptr<UniPAX::GRAPH::MetabolicNetwork> UniPAX::GRAPH::mysql::MySQLMappingEngine::createMetabolicNetwork(const std::set<std::string> & physical_entities, const UniPAX::ResultObject & result_obj)
{
	BiologicalNetworkPtr nw;
	std::string cacheString = "MTB_" + collate(physical_entities) + result_obj.getConstitutingQuery();
	// creating network
	boost::shared_ptr<UniPAX::GRAPH::MetabolicNetwork> metabolic(new UniPAX::GRAPH::MetabolicNetwork());
	addBiochemicalReactions(*metabolic, physical_entities, result_obj);
	
	if (network_cache.get(cacheString, nw))
	{
		//return boost::dynamic_pointer_cast<MetabolicNetwork>(nw);
		std::cout << "Found cached Network " << cacheString << ". Still creating new one (Github Issue#4)" << std::endl;
	}
	else
	{
		std::cout << "Creating Network " << cacheString << ". Putting it into Cache, which is not usable (Github Issue#4)" << std::endl;
		network_cache.insert("MTB_" + collate(physical_entities) + result_obj.getConstitutingQuery(), boost::dynamic_pointer_cast<BiologicalNetwork>(metabolic));
	}
	return metabolic;
}

boost::shared_ptr<UniPAX::GRAPH::MetabolicNetwork> UniPAX::GRAPH::mysql::MySQLMappingEngine::createMetabolicNetwork(const std::set<std::string> & physical_entities)
{
	BiologicalNetworkPtr nw;
	std::string cacheString = "MTB_" + collate(physical_entities);
	// creating network
	boost::shared_ptr<UniPAX::GRAPH::MetabolicNetwork> metabolic(new UniPAX::GRAPH::MetabolicNetwork());
	addBiochemicalReactions(*metabolic, physical_entities);
	if (network_cache.get(cacheString, nw))
	{
		std::cout << "Found cached Network " << cacheString << ". Still creating new one (Github Issue#4)" << std::endl;
	//	return boost::dynamic_pointer_cast<MetabolicNetwork>(nw);
	}
	else
	{
		std::cout << "Creating Network " << cacheString << ". Putting it into Cache, which is not usable (Github Issue#4)" << std::endl;
		network_cache.insert("MTB_" + collate(physical_entities), boost::dynamic_pointer_cast<BiologicalNetwork>(metabolic));
	}
	return metabolic;
}



bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapRegulationTypes(UniPAX::GRAPH::RegulatoryNetwork & network, UniPAX::GRAPH::RegulatoryNetwork::Graph::ArcMap<std::string> & regulation_type)
{

	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "MySQLCache::mapRegulationTypes: Failed to connect mysql with QT";
			return false;
		}
	}

	{
		QSqlQuery query = db->exec("SELECT unipaxId, controlType FROM TemplateReactionRegulation");

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
		QSqlQuery query = db->exec("SELECT unipaxId, controlType FROM Control");

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

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::getEntityIdsByOrganism(std::set<UnipaxId> & organism_entities, UnipaxId organismId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "MySQLMappingEngine::getEntityIdsByOrganism: Failed to connect mysql with QT";
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

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::getEntityIdsByPathway(std::set<UnipaxId> & pathway_entities, UnipaxId pathwayId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "MySQLMappingEngine::getEntityIdsByPathway: Failed to connect mysql with QT";
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

std::string UniPAX::GRAPH::mysql::MySQLMappingEngine::getName(UnipaxId unipaxId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "MySQLMappingEngine::getName: Failed to connect mysql with QT";
			return "";
		}
	}

	QString table;

	if (UniPAX::DBManager::isType(unipaxId, ClassType::idBioSource))
	{
		table == "BioSource";
	}
	else if (UniPAX::DBManager::isType(unipaxId, ClassType::idEntityReference))
	{
		table == "EntityReference";
	}
	else if (UniPAX::DBManager::isType(unipaxId, ClassType::idEntity))
	{
		table == "Entity";
	}
	else if (UniPAX::DBManager::isType(unipaxId, ClassType::idProvenance))
	{
		table == "Provenance";
	}


	if (table != "")
	{
		QSqlQuery query = db->exec(QString("SELECT standardName, displayName FROM `%1` WHERE unipaxId = %2").arg(table, unipaxId));
		if (query.next())
		{
			QString standardName = query.value(0).toString();
			QString displayName = query.value(0).toString();
			if (standardName != "")
				return standardName.toStdString();;
			if (displayName != "")
				return displayName.toStdString();
		}
		query = db->exec(QString("SELECT GROUP_CONCAT(DISTINCT value ORDER BY value SEPARATOR  ', ') as name FROM `%1_name` WHERE object_id = '%2' GROUP BY object_id").arg(table, unipaxId));
		if (query.next())
		{
			return query.value(0).toString().toStdString();
		}
	}

	return "";
}

std::string UniPAX::GRAPH::mysql::MySQLMappingEngine::getPathwayName(UnipaxId unipaxId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "MySQLMappingEngine::getPathwayName: Failed to connect mysql with QT";
			return "";
		}
	}

	QSqlQuery query = db->exec(QString("select p.standardName, pa.standardName from Provenance p, Pathway pa where pa.unipaxId = %1 and p.unipaxId = pa.dataSource").arg(unipaxId));

	std::string name = "";
	if (query.next())
	{
		name = query.value(1).toString().toStdString() + " (" + query.value(0).toString().toStdString() + ")";
	}

	return name;
}

std::string UniPAX::GRAPH::mysql::MySQLMappingEngine::getPathwayDescription(UnipaxId unipaxId)
{
	QSqlDatabase* db = boost::dynamic_pointer_cast<UniPAX::mysql::MySQLManager>(db_manager)->getDatabase();

	if (!db->isOpen())
	{
		if (!db->open())
		{
			std::cerr << "MySQLMappingEngine::getPathwayDescription: Failed to connect mysql with QT";
			return "";
		}
	}

	std::string description = "";
	QSqlQuery query = db->exec(QString("select value from Pathway_comments where object_id = %1").arg(unipaxId));

	while (query.next())
	{
		if (description == "")
			description = query.value(0).toString().remove(QString("\n")).toStdString();
		else
			description = description + " | " + query.value(0).toString().remove(QString("\n")).toStdString();
	}

	return description;
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addInteractions(RegulatoryNetwork & network, const UniPAX::ResultObject & result_obj)
{
	return _addInteractions(network, result_obj);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addInteractions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addInteractions(network, physical_entities);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addTemplateRegulations(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, const UniPAX::ResultObject & result_obj)
{
	return _addTemplateRegulations(network, physical_entities, result_obj);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addTemplateRegulations(RegulatoryNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addTemplateRegulations(network, physical_entities);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addControlOfBiochemicalReactions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, const UniPAX::ResultObject & result_obj)
{
	return _addControlOfBiochemicalReactions(network, physical_entities, result_obj);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addControlOfBiochemicalReactions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addControlOfBiochemicalReactions(network, physical_entities);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addControlOfConversions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, const UniPAX::ResultObject & result_obj)
{
	return _addControlOfConversions(network, physical_entities, result_obj);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addControlOfConversions(RegulatoryNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addControlOfConversions(network, physical_entities);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addComplexAssemblies(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, const UniPAX::ResultObject & result_obj, bool search_in_biochemicalreactions)
{
	return _addComplexAssemblies(network, physical_entities, result_obj, search_in_biochemicalreactions);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addComplexAssemblies(RegulatoryNetwork & network, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions)
{
	return _addComplexAssemblies(network, physical_entities, search_in_biochemicalreactions);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addInteractions(ProteinProteinInteractionNetwork & network, const UniPAX::ResultObject & result_obj)
{
	return _addInteractions(network, result_obj);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addInteractions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addInteractions(network, physical_entities);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addTemplateRegulations(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addTemplateRegulations(network, physical_entities);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addControlOfBiochemicalReactions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addControlOfBiochemicalReactions(network, physical_entities);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addComplexAssemblies(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities, bool search_in_biochemicalreactions)
{
	return _addComplexAssemblies(network, physical_entities, search_in_biochemicalreactions);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addBiochemicalReactions(MetabolicNetwork & network, const std::set<std::string> & physical_entities)
{
	return _addBiochemicalReactions(network, physical_entities);
}

int UniPAX::GRAPH::mysql::MySQLMappingEngine::addBiochemicalReactions(MetabolicNetwork & network, const std::set<std::string> & physical_entities, const UniPAX::ResultObject & result_obj)
{
	return _addBiochemicalReactions(network, physical_entities, result_obj);
}


bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db)
{
	return _mapXrefData(network, nodeMap, external_db);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapXrefData(RegulatoryNetwork & network, RegulatoryNetwork::Graph::ArcMap<std::string> & arcMap, std::string external_db)
{
	return _mapXrefData(network, arcMap, external_db);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapNames(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapNames(network, nodeMap, type);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapFeatures(RegulatoryNetwork & network, RegulatoryNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapFeatures(network, nodeMap, type);
}

	/*int UniPAX::GRAPH::mysql::MySQLMappingEngine::addInteractions(ProteinProteinInteractionNetwork & network, const std::set<std::string> & physical_entities, const ResultObject & result_obj)
	{
	//TODO
	return 1;
	}*/

	int UniPAX::GRAPH::mysql::MySQLMappingEngine::addTemplateRegulations(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj)
	{
	//TODO
	return 1;
	}

	int UniPAX::GRAPH::mysql::MySQLMappingEngine::addControlOfBiochemicalReactions(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj)
	{
	//TODO
	return 1;
	}

	int UniPAX::GRAPH::mysql::MySQLMappingEngine::addComplexAssemblies(ProteinProteinInteractionNetwork & regulatory, const std::set<std::string> & physical_entities, const ResultObject & result_obj, bool search_in_biochemicalreactions)
	{
	//TODO
	return 1;
	}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapXrefData(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db)
{
	return _mapXrefData(network, nodeMap, external_db);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapXrefData(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::EdgeMap<std::string> & edgeMap, std::string external_db)
{
	return _mapXrefData(network, edgeMap, external_db);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapNames(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string nameType)
{
	return _mapNames(network, nodeMap, nameType);
}


bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapFeatures(ProteinProteinInteractionNetwork & network, ProteinProteinInteractionNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapFeatures(network, nodeMap, type);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapXrefData(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeMap, std::string external_db)
{
	return _mapXrefData(network, nodeMap, external_db);
}


/*bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapXrefData(MetabolicNetwork & network, MetabolicNetwork::Graph::ArcMap<std::string> & arcMap, std::string external_db)
{
	return _mapXrefData(network, arcMap, external_db);
}*/

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapNames(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapNames(network, nodeMap, type);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapFeatures(MetabolicNetwork & network, MetabolicNetwork::Graph::NodeMap<std::string> & nodeMap, std::string type)
{
	return _mapFeatures(network, nodeMap, type);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapSeriesData(MetabolicNetwork & network, std::vector<std::pair<std::string, TNodeMapPtr<MetabolicNetwork>::type> > & nodeMaps, UnipaxId result_id)
{
	return _mapSeriesData(network, nodeMaps, result_id);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapSeriesData(RegulatoryNetwork & network, std::vector<std::pair<std::string, TNodeMapPtr<RegulatoryNetwork>::type> > & nodeMaps, UnipaxId result_id)
{
	return _mapSeriesData(network, nodeMaps, result_id);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::mapSeriesData(ProteinProteinInteractionNetwork & network, std::vector<std::pair<std::string, TNodeMapPtr<ProteinProteinInteractionNetwork>::type> > & nodeMaps, UnipaxId result_id)
{
	return _mapSeriesData(network, nodeMaps, result_id);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::filterByOrganisms(RegulatoryNetwork & network, std::set<UnipaxId> & organismIds)
{
	return _filterByOrganism(network, organismIds);
}


bool UniPAX::GRAPH::mysql::MySQLMappingEngine::filterByPathways(RegulatoryNetwork & network, std::set<UnipaxId> & pathwayIds)
{
	return _filterByPathway(network, pathwayIds);
}



bool UniPAX::GRAPH::mysql::MySQLMappingEngine::filterByOrganisms(ProteinProteinInteractionNetwork & network, std::set<UnipaxId> & organismIds)
{
	return _filterByOrganism(network, organismIds);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::filterByPathways(ProteinProteinInteractionNetwork & network, std::set<UnipaxId> & pathwayIds)
{
	return _filterByPathway(network, pathwayIds);
}


bool UniPAX::GRAPH::mysql::MySQLMappingEngine::filterByPathways(MetabolicNetwork & network, std::set<UnipaxId> & pathwayIds)
{
	return _filterByPathway(network, pathwayIds);
}

bool UniPAX::GRAPH::mysql::MySQLMappingEngine::filterByOrganisms(MetabolicNetwork & network, std::set<UnipaxId> & organismIds)
{
	return _filterByOrganism(network, organismIds);
}



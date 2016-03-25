#include<UNIPAX/PERSISTENCE/ORACLE/OracleODBPersistRunnable.h>


UniPAX::oracle::OracleODBPersistRunnable::OracleODBPersistRunnable(boost::shared_ptr<UniPAX::UPBase> _object) : UniPAX::ODBPersistRunnable(_object)
{
}

UniPAX::oracle::OracleODBPersistRunnable::OracleODBPersistRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects) : UniPAX::ODBPersistRunnable(_objects)
{
}

UniPAX::oracle::OracleODBPersistRunnable::~OracleODBPersistRunnable()
{
}

void UniPAX::oracle::OracleODBPersistRunnable::run(boost::shared_ptr<odb::database> database)
{
	try
	{
		odb::transaction t (database->begin());
//		t.tracer (odb::stderr_tracer);


		int i = 0;

		for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::const_iterator it(objects.begin()); it != objects.end(); it++)
		{
			std::string type = (*it)->get_type();

//			std::cout << "persist object of type - " << type <<  " - " << (*it)->get_unipaxId() << std::endl;

			// BIOPAX

			if (boost::iequals(type,"BindingFeature"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<BindingFeature>(*it));
			}
			else if (boost::iequals(type,"BioSource"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<BioSource>(*it));
			}
			else if (boost::iequals(type,"BiochemicalPathwayStep"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<BiochemicalPathwayStep>(*it));
			}
			else if (boost::iequals(type,"BiochemicalReaction"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<BiochemicalReaction>(*it));
			}
			else if (boost::iequals(type,"Catalysis"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Catalysis>(*it));
			}
			else if (boost::iequals(type,"CellVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<CellVocabulary>(*it));
			}
			else if (boost::iequals(type,"CellularLocationVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<CellularLocationVocabulary>(*it));
			}
			else if (boost::iequals(type,"ChemicalStructure"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<ChemicalStructure>(*it));
			}
			else if (boost::iequals(type,"Complex"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Complex>(*it));
			}
			else if (boost::iequals(type,"ComplexAssembly"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<ComplexAssembly>(*it));
			}
			else if (boost::iequals(type,"Control"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Control>(*it));
			}
			else if (boost::iequals(type,"ControlledVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<ControlledVocabulary>(*it));
			}
			else if (boost::iequals(type,"Conversion"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Conversion>(*it));
			}
			else if (boost::iequals(type,"CovalentBindingFeature"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<CovalentBindingFeature>(*it));
			}
			else if (boost::iequals(type,"Degradation"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Degradation>(*it));
			}
			else if (boost::iequals(type,"DeltaG"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<DeltaG>(*it));
			}
			else if (boost::iequals(type,"Dna"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Dna>(*it));
			}
			else if (boost::iequals(type,"DnaReference"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<DnaReference>(*it));
			}
			else if (boost::iequals(type,"DnaRegion"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<DnaRegion>(*it));
			}
			else if (boost::iequals(type,"DnaRegionReference"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<DnaRegionReference>(*it));
			}
			else if (boost::iequals(type,"Entity"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Entity>(*it));
			}
			else if (boost::iequals(type,"EntityFeature"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<EntityFeature>(*it));
			}
			else if (boost::iequals(type,"EntityReference"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<EntityReference>(*it));
			}
			else if (boost::iequals(type,"EntityReferenceTypeVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<EntityReferenceTypeVocabulary>(*it));
			}
			else if (boost::iequals(type,"Evidence"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Evidence>(*it));
			}
			else if (boost::iequals(type,"EvidenceCodeVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<EvidenceCodeVocabulary>(*it));
			}
			else if (boost::iequals(type,"ExperimentalForm"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<ExperimentalForm>(*it));
			}
			else if (boost::iequals(type,"ExperimentalFormVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<ExperimentalFormVocabulary>(*it));
			}
			else if (boost::iequals(type,"FragmentFeature"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<FragmentFeature>(*it));
			}
			else if (boost::iequals(type,"Gene"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Gene>(*it));
			}
			else if (boost::iequals(type,"GeneticInteraction"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<GeneticInteraction>(*it));
			}
			else if (boost::iequals(type,"Interaction"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Interaction>(*it));
			}
			else if (boost::iequals(type,"InteractionVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<InteractionVocabulary>(*it));
			}
			else if (boost::iequals(type,"KPrime"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<KPrime>(*it));
			}
			else if (boost::iequals(type,"ModificationFeature"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<ModificationFeature>(*it));
			}
			else if (boost::iequals(type,"Modulation"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Modulation>(*it));
			}
			else if (boost::iequals(type,"MolecularInteraction"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<MolecularInteraction>(*it));
			}
			else if (boost::iequals(type,"Pathway"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Pathway>(*it));
			}
			else if (boost::iequals(type,"PathwayStep"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<PathwayStep>(*it));
			}
			else if (boost::iequals(type,"PhenotypeVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<PhenotypeVocabulary>(*it));
			}
			else if (boost::iequals(type,"PhysicalEntity"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<PhysicalEntity>(*it));
			}
			else if (boost::iequals(type,"Protein"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Protein>(*it));
			}
			else if (boost::iequals(type,"ProteinReference"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<ProteinReference>(*it));
			}
			else if (boost::iequals(type,"Provenance"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Provenance>(*it));
			}
			else if (boost::iequals(type,"PublicationXref"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<PublicationXref>(*it));
			}
			else if (boost::iequals(type,"RelationshipTypeVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<RelationshipTypeVocabulary>(*it));
			}
			else if (boost::iequals(type,"RelationshipXref"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<RelationshipXref>(*it));
			}
			else if (boost::iequals(type,"Rna"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Rna>(*it));
			}
			else if (boost::iequals(type,"RnaReference"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<RnaReference>(*it));
			}
			else if (boost::iequals(type,"RnaRegion"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<RnaRegion>(*it));
			}
			else if (boost::iequals(type,"RnaRegionReference"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<RnaRegionReference>(*it));
			}
			else if (boost::iequals(type,"Score"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Score>(*it));
			}
			else if (boost::iequals(type,"SequenceInterval"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<SequenceInterval>(*it));
			}
			else if (boost::iequals(type,"SequenceLocation"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<SequenceLocation>(*it));
			}
			else if (boost::iequals(type,"SequenceModificationVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<SequenceModificationVocabulary>(*it));
			}
			else if (boost::iequals(type,"SequenceRegionVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<SequenceRegionVocabulary>(*it));
			}
			else if (boost::iequals(type,"SequenceSite"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<SequenceSite>(*it));
			}
			else if (boost::iequals(type,"SmallMolecule"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<SmallMolecule>(*it));
			}
			else if (boost::iequals(type,"SmallMoleculeReference"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<SmallMoleculeReference>(*it));
			}
			else if (boost::iequals(type,"Stoichiometry"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Stoichiometry>(*it));
			}
			else if (boost::iequals(type,"TemplateReaction"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<TemplateReaction>(*it));
			}
			else if (boost::iequals(type,"TemplateReactionRegulation"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<TemplateReactionRegulation>(*it));
			}
			else if (boost::iequals(type,"Thing"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Thing>(*it));
			}
			else if (boost::iequals(type,"TissueVocabulary"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<TissueVocabulary>(*it));
			}
			else if (boost::iequals(type,"Transport"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Transport>(*it));
			}
			else if (boost::iequals(type,"TransportWithBiochemicalReaction"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<TransportWithBiochemicalReaction>(*it));
			}
			else if (boost::iequals(type,"UnificationXref"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<UnificationXref>(*it));
			}
			else if (boost::iequals(type,"UtilityClass"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<UtilityClass>(*it));
			}
			else if (boost::iequals(type,"Xref"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Xref>(*it));
			}

			// EXT

			else if (boost::iequals(type,"AlgebraicRule"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<AlgebraicRule>(*it));
			}
			else if (boost::iequals(type,"AssignmentRule"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<AssignmentRule>(*it));
			}
			else if (boost::iequals(type,"Constraint"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Constraint>(*it));
			}
			else if (boost::iequals(type,"Delay"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Delay>(*it));
			}
			else if (boost::iequals(type,"Event"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Event>(*it));
			}
			else if (boost::iequals(type,"EventAssignment"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<EventAssignment>(*it));
			}
			else if (boost::iequals(type,"Experiment"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Experiment>(*it));
			}
			else if (boost::iequals(type,"FunctionDefinition"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<FunctionDefinition>(*it));
			}
                        else if (boost::iequals(type,"IdMapping"))
                        {
                                ids[i] = database->persist(boost::dynamic_pointer_cast<IdMapping>(*it));
                        }
                        else if (boost::iequals(type,"ImportSource"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<ImportSource>(*it));
			}
			else if (boost::iequals(type,"InitialAssignment"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<InitialAssignment>(*it));
			}
			else if (boost::iequals(type,"KineticLaw"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<KineticLaw>(*it));
			}
			else if (boost::iequals(type,"LocalParameter"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<LocalParameter>(*it));
			}
                        else if (boost::iequals(type,"Math"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Math>(*it));
			}
			else if (boost::iequals(type,"Model"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Model>(*it));
			}
			else if (boost::iequals(type,"Parameter"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Parameter>(*it));
			}
			else if (boost::iequals(type,"Priority"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Priority>(*it));
			}
			else if (boost::iequals(type,"RateRule"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<RateRule>(*it));
			}
                        else if (boost::iequals(type,"ResultObject"))
                        {
                                ids[i] = database->persist(boost::dynamic_pointer_cast<ResultObject>(*it));
                        }
                        else if (boost::iequals(type,"Rule"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Rule>(*it));
			}
			else if (boost::iequals(type,"SBase"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<SBase>(*it));
			}
			else if (boost::iequals(type,"Sample"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Sample>(*it));
			}
                        else if (boost::iequals(type,"Series"))
                        {
                                ids[i] = database->persist(boost::dynamic_pointer_cast<Series>(*it));
                        }
                        else if (boost::iequals(type,"Trigger"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Trigger>(*it));
			}
			else if (boost::iequals(type,"UPBase"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<UPBase>(*it));
			}
			else if (boost::iequals(type,"Unit"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<Unit>(*it));
			}
			else if (boost::iequals(type,"UnitDefinition"))
			{
				ids[i] = database->persist(boost::dynamic_pointer_cast<UnitDefinition>(*it));
			}
		}

		t.commit();
	}
	catch (const odb::exception& e)
	{
		std::cerr << "OracleODBPersistRunnable::persist: odb_exception - " << e.what() << std::endl;
	}


}

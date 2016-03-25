#include<UNIPAX/PERSISTENCE/ORACLE/OracleODBUpdateRunnable.h>


UniPAX::oracle::OracleODBUpdateRunnable::OracleODBUpdateRunnable(boost::shared_ptr<UniPAX::UPBase> _object) : UniPAX::ODBUpdateRunnable(_object)
{
}

UniPAX::oracle::OracleODBUpdateRunnable::OracleODBUpdateRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > _objects) : UniPAX::ODBUpdateRunnable(_objects)
{
}

UniPAX::oracle::OracleODBUpdateRunnable::~OracleODBUpdateRunnable()
{
}

void UniPAX::oracle::OracleODBUpdateRunnable::run(boost::shared_ptr<odb::database> database)
{
    try
    {
        odb::transaction t (database->begin());

        int i = 0;

        for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::const_iterator it(objects.begin()); it != objects.end(); it++)
        {
            std::string type = (*it)->get_type();

            // BIOPAX

            if (boost::iequals(type,"BindingFeature"))
            {
                if (database->find<UniPAX::BindingFeature>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<BindingFeature>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<BindingFeature>(*it));
                }
            }
            else if (boost::iequals(type,"BioSource"))
            {
                if (database->find<UniPAX::BioSource>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<BioSource>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<BioSource>(*it));
                }
            }
            else if (boost::iequals(type,"BiochemicalPathwayStep"))
            {
                if (database->find<UniPAX::BiochemicalPathwayStep>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<BiochemicalPathwayStep>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<BiochemicalPathwayStep>(*it));
                }
            }
            else if (boost::iequals(type,"BiochemicalReaction"))
            {
                if (database->find<UniPAX::BiochemicalReaction>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<BiochemicalReaction>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<BiochemicalReaction>(*it));
                }
            }
            else if (boost::iequals(type,"Catalysis"))
            {
                if (database->find<UniPAX::Catalysis>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Catalysis>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Catalysis>(*it));
                }
            }
            else if (boost::iequals(type,"CellVocabulary"))
            {
                if (database->find<UniPAX::CellVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<CellVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<CellVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"CellularLocationVocabulary"))
            {
                if (database->find<UniPAX::CellularLocationVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<CellularLocationVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<CellularLocationVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"ChemicalStructure"))
            {
                if (database->find<UniPAX::ChemicalStructure>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<ChemicalStructure>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<ChemicalStructure>(*it));
                }
            }
            else if (boost::iequals(type,"Complex"))
            {
                if (database->find<UniPAX::Complex>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Complex>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Complex>(*it));
                }
            }
            else if (boost::iequals(type,"ComplexAssembly"))
            {
                if (database->find<UniPAX::ComplexAssembly>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<ComplexAssembly>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<ComplexAssembly>(*it));
                }
            }
            else if (boost::iequals(type,"Control"))
            {
                if (database->find<UniPAX::Control>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Control>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Control>(*it));
                }
            }
            else if (boost::iequals(type,"ControlledVocabulary"))
            {
                if (database->find<UniPAX::ControlledVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<ControlledVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<ControlledVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"Conversion"))
            {
                if (database->find<UniPAX::Conversion>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Conversion>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Conversion>(*it));
                }
            }
            else if (boost::iequals(type,"CovalentBindingFeature"))
            {
                if (database->find<UniPAX::CovalentBindingFeature>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<CovalentBindingFeature>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<CovalentBindingFeature>(*it));
                }
            }
            else if (boost::iequals(type,"Degradation"))
            {
                if (database->find<UniPAX::Degradation>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Degradation>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Degradation>(*it));
                }
            }
            else if (boost::iequals(type,"DeltaG"))
            {
                if (database->find<UniPAX::DeltaG>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<DeltaG>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<DeltaG>(*it));
                }
            }
            else if (boost::iequals(type,"Dna"))
            {
                if (database->find<UniPAX::Dna>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Dna>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Dna>(*it));
                }
            }
            else if (boost::iequals(type,"DnaReference"))
            {
                if (database->find<UniPAX::DnaReference>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<DnaReference>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<DnaReference>(*it));
                }
            }
            else if (boost::iequals(type,"DnaRegion"))
            {
                if (database->find<UniPAX::DnaRegion>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<DnaRegion>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<DnaRegion>(*it));
                }
            }
            else if (boost::iequals(type,"DnaRegionReference"))
            {
                if (database->find<UniPAX::DnaRegionReference>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<DnaRegionReference>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<DnaRegionReference>(*it));
                }
            }
            else if (boost::iequals(type,"Entity"))
            {
                if (database->find<UniPAX::Entity>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Entity>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Entity>(*it));
                }
            }
            else if (boost::iequals(type,"EntityFeature"))
            {
                if (database->find<UniPAX::EntityFeature>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<EntityFeature>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<EntityFeature>(*it));
                }
            }
            else if (boost::iequals(type,"EntityReference"))
            {
                if (database->find<UniPAX::EntityReference>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<EntityReference>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<EntityReference>(*it));
                }
            }
            else if (boost::iequals(type,"EntityReferenceTypeVocabulary"))
            {
                if (database->find<UniPAX::EntityReferenceTypeVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<EntityReferenceTypeVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<EntityReferenceTypeVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"Evidence"))
            {
                if (database->find<UniPAX::Evidence>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Evidence>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Evidence>(*it));
                }
            }
            else if (boost::iequals(type,"EvidenceCodeVocabulary"))
            {
                if (database->find<UniPAX::EvidenceCodeVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<EvidenceCodeVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<EvidenceCodeVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"ExperimentalForm"))
            {
                if (database->find<UniPAX::ExperimentalForm>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<ExperimentalForm>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<ExperimentalForm>(*it));
                }
            }
            else if (boost::iequals(type,"ExperimentalFormVocabulary"))
            {
                if (database->find<UniPAX::ExperimentalFormVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<ExperimentalFormVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<ExperimentalFormVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"FragmentFeature"))
            {
                if (database->find<UniPAX::FragmentFeature>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<FragmentFeature>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<FragmentFeature>(*it));
                }
            }
            else if (boost::iequals(type,"Gene"))
            {
                if (database->find<UniPAX::Gene>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Gene>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Gene>(*it));
                }
            }
            else if (boost::iequals(type,"GeneticInteraction"))
            {
                if (database->find<UniPAX::GeneticInteraction>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<GeneticInteraction>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<GeneticInteraction>(*it));
                }
            }
            else if (boost::iequals(type,"Interaction"))
            {
                if (database->find<UniPAX::Interaction>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Interaction>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Interaction>(*it));
                }
            }
            else if (boost::iequals(type,"InteractionVocabulary"))
            {
                if (database->find<UniPAX::InteractionVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<InteractionVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<InteractionVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"KPrime"))
            {
                if (database->find<UniPAX::KPrime>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<KPrime>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<KPrime>(*it));
                }
            }
            else if (boost::iequals(type,"ModificationFeature"))
            {
                if (database->find<UniPAX::ModificationFeature>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<ModificationFeature>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<ModificationFeature>(*it));
                }
            }
            else if (boost::iequals(type,"Modulation"))
            {
                if (database->find<UniPAX::Modulation>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Modulation>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Modulation>(*it));
                }
            }
            else if (boost::iequals(type,"MolecularInteraction"))
            {
                if (database->find<UniPAX::MolecularInteraction>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<MolecularInteraction>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<MolecularInteraction>(*it));
                }
            }
            else if (boost::iequals(type,"Pathway"))
            {
                if (database->find<UniPAX::Pathway>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Pathway>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Pathway>(*it));
                }
            }
            else if (boost::iequals(type,"PathwayStep"))
            {
                if (database->find<UniPAX::PathwayStep>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<PathwayStep>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<PathwayStep>(*it));
                }
            }
            else if (boost::iequals(type,"PhenotypeVocabulary"))
            {
                if (database->find<UniPAX::PhenotypeVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<PhenotypeVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<PhenotypeVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"PhysicalEntity"))
            {
                if (database->find<UniPAX::PhysicalEntity>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<PhysicalEntity>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<PhysicalEntity>(*it));
                }
            }
            else if (boost::iequals(type,"Protein"))
            {
                if (database->find<UniPAX::Protein>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Protein>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Protein>(*it));
                }
            }
            else if (boost::iequals(type,"ProteinReference"))
            {
                if (database->find<UniPAX::ProteinReference>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<ProteinReference>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<ProteinReference>(*it));
                }
            }
            else if (boost::iequals(type,"Provenance"))
            {
                if (database->find<UniPAX::Provenance>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Provenance>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Provenance>(*it));
                }
            }
            else if (boost::iequals(type,"PublicationXref"))
            {
                if (database->find<UniPAX::PublicationXref>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<PublicationXref>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<PublicationXref>(*it));
                }
            }
            else if (boost::iequals(type,"RelationshipTypeVocabulary"))
            {
                if (database->find<UniPAX::RelationshipTypeVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<RelationshipTypeVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<RelationshipTypeVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"RelationshipXref"))
            {
                if (database->find<UniPAX::RelationshipXref>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<RelationshipXref>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<RelationshipXref>(*it));
                }
            }
            else if (boost::iequals(type,"Rna"))
            {
                if (database->find<UniPAX::Rna>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Rna>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Rna>(*it));
                }
            }
            else if (boost::iequals(type,"RnaReference"))
            {
                if (database->find<UniPAX::RnaReference>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<RnaReference>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<RnaReference>(*it));
                }
            }
            else if (boost::iequals(type,"RnaRegion"))
            {
                if (database->find<UniPAX::RnaRegion>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<RnaRegion>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<RnaRegion>(*it));
                }
            }
            else if (boost::iequals(type,"RnaRegionReference"))
            {
                if (database->find<UniPAX::RnaRegionReference>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<RnaRegionReference>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<RnaRegionReference>(*it));
                }
            }
            else if (boost::iequals(type,"Score"))
            {
                if (database->find<UniPAX::Score>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Score>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Score>(*it));
                }
            }
            else if (boost::iequals(type,"SequenceInterval"))
            {
                if (database->find<UniPAX::SequenceInterval>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<SequenceInterval>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<SequenceInterval>(*it));
                }
            }
            else if (boost::iequals(type,"SequenceLocation"))
            {
                if (database->find<UniPAX::SequenceLocation>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<SequenceLocation>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<SequenceLocation>(*it));
                }
            }
            else if (boost::iequals(type,"SequenceModificationVocabulary"))
            {
                if (database->find<UniPAX::SequenceModificationVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<SequenceModificationVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<SequenceModificationVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"SequenceRegionVocabulary"))
            {
                if (database->find<UniPAX::SequenceRegionVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<SequenceRegionVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<SequenceRegionVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"SequenceSite"))
            {
                if (database->find<UniPAX::SequenceSite>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<SequenceSite>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<SequenceSite>(*it));
                }
            }
            else if (boost::iequals(type,"SmallMolecule"))
            {
                if (database->find<UniPAX::SmallMolecule>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<SmallMolecule>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<SmallMolecule>(*it));
                }
            }
            else if (boost::iequals(type,"SmallMoleculeReference"))
            {
                if (database->find<UniPAX::SmallMoleculeReference>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<SmallMoleculeReference>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<SmallMoleculeReference>(*it));
                }
            }
            else if (boost::iequals(type,"Stoichiometry"))
            {
                if (database->find<UniPAX::Stoichiometry>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Stoichiometry>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Stoichiometry>(*it));
                }
            }
            else if (boost::iequals(type,"TemplateReaction"))
            {
                if (database->find<UniPAX::TemplateReaction>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<TemplateReaction>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<TemplateReaction>(*it));
                }
            }
            else if (boost::iequals(type,"TemplateReactionRegulation"))
            {
                if (database->find<UniPAX::TemplateReactionRegulation>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<TemplateReactionRegulation>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<TemplateReactionRegulation>(*it));
                }
            }
            else if (boost::iequals(type,"Thing"))
            {
                if (database->find<UniPAX::Thing>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Thing>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Thing>(*it));
                }
            }
            else if (boost::iequals(type,"TissueVocabulary"))
            {
                if (database->find<UniPAX::TissueVocabulary>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<TissueVocabulary>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<TissueVocabulary>(*it));
                }
            }
            else if (boost::iequals(type,"Transport"))
            {
                if (database->find<UniPAX::Transport>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Transport>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Transport>(*it));
                }
            }
            else if (boost::iequals(type,"TransportWithBiochemicalReaction"))
            {
                if (database->find<UniPAX::TransportWithBiochemicalReaction>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<TransportWithBiochemicalReaction>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<TransportWithBiochemicalReaction>(*it));
                }
            }
            else if (boost::iequals(type,"UnificationXref"))
            {
                if (database->find<UniPAX::UnificationXref>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<UnificationXref>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<UnificationXref>(*it));
                }
            }
            else if (boost::iequals(type,"UtilityClass"))
            {
                if (database->find<UniPAX::UtilityClass>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<UtilityClass>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<UtilityClass>(*it));
                }
            }
            else if (boost::iequals(type,"Xref"))
            {
                if (database->find<UniPAX::Xref>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Xref>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Xref>(*it));
                }
            }

            // EXT

            else if (boost::iequals(type,"AlgebraicRule"))
            {
                if (database->find<UniPAX::AlgebraicRule>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<AlgebraicRule>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<AlgebraicRule>(*it));
                }
            }
            else if (boost::iequals(type,"AssignmentRule"))
            {
                if (database->find<UniPAX::AssignmentRule>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<AssignmentRule>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<AssignmentRule>(*it));
                }
            }
            else if (boost::iequals(type,"Constraint"))
            {
                if (database->find<UniPAX::Constraint>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Constraint>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Constraint>(*it));
                }
            }
            else if (boost::iequals(type,"Delay"))
            {
                if (database->find<UniPAX::Delay>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Delay>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Delay>(*it));
                }
            }
            else if (boost::iequals(type,"Event"))
            {
                if (database->find<UniPAX::Event>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Event>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Event>(*it));
                }
            }
            else if (boost::iequals(type,"EventAssignment"))
            {
                if (database->find<UniPAX::EventAssignment>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<EventAssignment>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<EventAssignment>(*it));
                }
            }
            else if (boost::iequals(type,"Experiment"))
            {
                if (database->find<UniPAX::Experiment>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Experiment>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Experiment>(*it));
                }
            }
            else if (boost::iequals(type,"FunctionDefinition"))
            {
                if (database->find<UniPAX::FunctionDefinition>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<FunctionDefinition>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<FunctionDefinition>(*it));
                }
            }
            else if (boost::iequals(type,"IdMapping"))
            {
                if (database->find<UniPAX::IdMapping>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<IdMapping>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<IdMapping>(*it));
                }
            }
            else if (boost::iequals(type,"ImportSource"))
            {
                if (database->find<UniPAX::ImportSource>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<ImportSource>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<ImportSource>(*it));
                }
            }
            else if (boost::iequals(type,"InitialAssignment"))
            {
                if (database->find<UniPAX::InitialAssignment>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<InitialAssignment>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<InitialAssignment>(*it));
                }
            }
            else if (boost::iequals(type,"KineticLaw"))
            {
                if (database->find<UniPAX::KineticLaw>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<KineticLaw>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<KineticLaw>(*it));
                }
            }
            else if (boost::iequals(type,"LocalParameter"))
            {
                if (database->find<UniPAX::LocalParameter>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<LocalParameter>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<LocalParameter>(*it));
                }
            }
            else if (boost::iequals(type,"Math"))
            {
                if (database->find<UniPAX::Math>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Math>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Math>(*it));
                }
            }
            else if (boost::iequals(type,"Model"))
            {
                if (database->find<UniPAX::Model>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Model>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Model>(*it));
                }
            }
            else if (boost::iequals(type,"Parameter"))
            {
                if (database->find<UniPAX::Parameter>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Parameter>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Parameter>(*it));
                }
            }
            else if (boost::iequals(type,"Priority"))
            {
                if (database->find<UniPAX::Priority>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Priority>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Priority>(*it));
                }
            }
            else if (boost::iequals(type,"RateRule"))
            {
                if (database->find<UniPAX::RateRule>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<RateRule>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<RateRule>(*it));
                }
            }
            else if (boost::iequals(type,"ResultObject"))
            {
                if (database->find<UniPAX::ResultObject>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<ResultObject>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<ResultObject>(*it));
                }
            }
            else if (boost::iequals(type,"Rule"))
            {
                if (database->find<UniPAX::Rule>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Rule>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Rule>(*it));
                }
            }
            else if (boost::iequals(type,"SBase"))
            {
                if (database->find<UniPAX::SBase>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<SBase>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<SBase>(*it));
                }
            }
            else if (boost::iequals(type,"Sample"))
            {
                if (database->find<UniPAX::Sample>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Sample>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Sample>(*it));
                }
            }
            else if (boost::iequals(type,"Series"))
            {
                if (database->find<UniPAX::Series>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<UniPAX::Series>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<UniPAX::Series>(*it));
                }
            }
            else if (boost::iequals(type,"Trigger"))
            {
                if (database->find<UniPAX::Trigger>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Trigger>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Trigger>(*it));
                }
            }
            else if (boost::iequals(type,"UPBase"))
            {
                if (database->find<UniPAX::UPBase>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<UPBase>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<UPBase>(*it));
                }
            }
            else if (boost::iequals(type,"Unit"))
            {
                if (database->find<UniPAX::Unit>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<Unit>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<Unit>(*it));
                }
            }
            else if (boost::iequals(type,"UnitDefinition"))
            {
                if (database->find<UniPAX::UnitDefinition>((*it)->get_unipaxId()))
                {
                    database->update(boost::dynamic_pointer_cast<UnitDefinition>(*it));
                }
                else
                {
                    database->persist(boost::dynamic_pointer_cast<UnitDefinition>(*it));
                }
            }

            successful[i] = true;
            ++i;
        }

        t.commit();

    }
    catch (const odb::exception& e)
    {
        std::cerr << "OracleODBUpdateRunnable::update: odb_exception - " << e.what() << std::endl;
    }


}

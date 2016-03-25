#include<UNIPAX/PERSISTENCE/MYSQL/MySQLODBLoadRunnable.h>
#include <UNIPAX/PERSISTENCE/DBManager.h>

UniPAX::mysql::MySQLODBLoadRunnable::MySQLODBLoadRunnable(std::vector<boost::shared_ptr<UniPAX::UPBase> > & result, std::vector<UnipaxId> & _ids) : UniPAX::ODBLoadRunnable(result, _ids)
{
}


UniPAX::mysql::MySQLODBLoadRunnable::~MySQLODBLoadRunnable()
{
}


void UniPAX::mysql::MySQLODBLoadRunnable::run(boost::shared_ptr<odb::session> session, boost::shared_ptr<odb::database> database)
{
	try
	{
		odb::transaction t (database->begin());

		for (std::vector<UnipaxId>::const_iterator it(ids.begin()); it != ids.end(); it++)
		{
			std::string type = DBManager::getType(*it, "");


			std::cerr << "loading " << type << " " << *it << std::endl;


			if (boost::iequals(type,"BindingFeature"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::BindingFeature>(*it)));
			}

			else if (boost::iequals(type,"BioSource"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::BioSource>(*it)));
			}

			else if (boost::iequals(type,"BiochemicalPathwayStep"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::BiochemicalPathwayStep>(*it)));
			}

			else if (boost::iequals(type,"BiochemicalReaction"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::BiochemicalReaction>(*it)));
			}

			else if (boost::iequals(type,"Catalysis"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Catalysis>(*it)));
			}

			else if (boost::iequals(type,"CellVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::CellVocabulary>(*it)));
			}

			else if (boost::iequals(type,"CellularLocationVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::CellularLocationVocabulary>(*it)));
			}

			else if (boost::iequals(type,"ChemicalStructure"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::ChemicalStructure>(*it)));
			}

			else if (boost::iequals(type,"Complex"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Complex>(*it)));
			}

			else if (boost::iequals(type,"ComplexAssembly"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::ComplexAssembly>(*it)));
			}

			else if (boost::iequals(type,"Control"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Control>(*it)));
			}

			else if (boost::iequals(type,"ControlledVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::ControlledVocabulary>(*it)));
			}

			else if (boost::iequals(type,"Conversion"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Conversion>(*it)));
			}

			else if (boost::iequals(type,"CovalentBindingFeature"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::CovalentBindingFeature>(*it)));
			}

			else if (boost::iequals(type,"Degradation"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Degradation>(*it)));
			}

			else if (boost::iequals(type,"DeltaG"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::DeltaG>(*it)));
			}

			else if (boost::iequals(type,"Dna"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Dna>(*it)));
			}

			else if (boost::iequals(type,"DnaReference"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::DnaReference>(*it)));
			}

			else if (boost::iequals(type,"DnaRegion"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::DnaRegion>(*it)));
			}

			else if (boost::iequals(type,"DnaRegionReference"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::DnaRegionReference>(*it)));
			}

			else if (boost::iequals(type,"Entity"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Entity>(*it)));
			}

			else if (boost::iequals(type,"EntityFeature"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::EntityFeature>(*it)));
			}

			else if (boost::iequals(type,"EntityReference"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::EntityReference>(*it)));
			}

			else if (boost::iequals(type,"EntityReferenceTypeVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::EntityReferenceTypeVocabulary>(*it)));
			}

			else if (boost::iequals(type,"Evidence"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Evidence>(*it)));
			}

			else if (boost::iequals(type,"EvidenceCodeVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::EvidenceCodeVocabulary>(*it)));
			}

			else if (boost::iequals(type,"ExperimentalForm"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::ExperimentalForm>(*it)));
			}

			else if (boost::iequals(type,"ExperimentalFormVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::ExperimentalFormVocabulary>(*it)));
			}

			else if (boost::iequals(type,"FragmentFeature"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::FragmentFeature>(*it)));
			}

			else if (boost::iequals(type,"Gene"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Gene>(*it)));
			}

			else if (boost::iequals(type,"GeneticInteraction"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::GeneticInteraction>(*it)));
			}

			else if (boost::iequals(type,"Interaction"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Interaction>(*it)));
			}

			else if (boost::iequals(type,"InteractionVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::InteractionVocabulary>(*it)));
			}

			else if (boost::iequals(type,"KPrime"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::KPrime>(*it)));
			}

			else if (boost::iequals(type,"ModificationFeature"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::ModificationFeature>(*it)));
			}

			else if (boost::iequals(type,"Modulation"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Modulation>(*it)));
			}

			else if (boost::iequals(type,"MolecularInteraction"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::MolecularInteraction>(*it)));
			}

			else if (boost::iequals(type,"Pathway"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Pathway>(*it)));
			}

			else if (boost::iequals(type,"PathwayStep"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::PathwayStep>(*it)));
			}

			else if (boost::iequals(type,"PhenotypeVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::PhenotypeVocabulary>(*it)));
			}

			else if (boost::iequals(type,"PhysicalEntity"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::PhysicalEntity>(*it)));
			}

			else if (boost::iequals(type,"Protein"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Protein>(*it)));
			}

			else if (boost::iequals(type,"ProteinReference"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::ProteinReference>(*it)));
			}

			else if (boost::iequals(type,"Provenance"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Provenance>(*it)));
			}

			else if (boost::iequals(type,"PublicationXref"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::PublicationXref>(*it)));
			}

			else if (boost::iequals(type,"RelationshipTypeVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::RelationshipTypeVocabulary>(*it)));
			}

			else if (boost::iequals(type,"RelationshipXref"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::RelationshipXref>(*it)));
			}

			else if (boost::iequals(type,"Rna"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Rna>(*it)));
			}

			else if (boost::iequals(type,"RnaReference"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::RnaReference>(*it)));
			}

			else if (boost::iequals(type,"RnaRegion"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::RnaRegion>(*it)));
			}

			else if (boost::iequals(type,"RnaRegionReference"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::RnaRegionReference>(*it)));
			}

			else if (boost::iequals(type,"Score"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Score>(*it)));
			}

			else if (boost::iequals(type,"SequenceInterval"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::SequenceInterval>(*it)));
			}

			else if (boost::iequals(type,"SequenceLocation"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::SequenceLocation>(*it)));
			}

			else if (boost::iequals(type,"SequenceModificationVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::SequenceModificationVocabulary>(*it)));
			}

			else if (boost::iequals(type,"SequenceRegionVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::SequenceRegionVocabulary>(*it)));
			}

			else if (boost::iequals(type,"SequenceSite"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::SequenceSite>(*it)));
			}

			else if (boost::iequals(type,"SmallMolecule"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::SmallMolecule>(*it)));
			}

			else if (boost::iequals(type,"SmallMoleculeReference"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::SmallMoleculeReference>(*it)));
			}

			else if (boost::iequals(type,"Stoichiometry"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Stoichiometry>(*it)));
			}

			else if (boost::iequals(type,"TemplateReaction"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::TemplateReaction>(*it)));
			}

			else if (boost::iequals(type,"TemplateReactionRegulation"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::TemplateReactionRegulation>(*it)));
			}

			//			else if (boost::iequals(type,"Thing"))
			//			{
			//				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Thing>(*it)));
			//			}

			else if (boost::iequals(type,"TissueVocabulary"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::TissueVocabulary>(*it)));
			}

			else if (boost::iequals(type,"Transport"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Transport>(*it)));
			}

			else if (boost::iequals(type,"TransportWithBiochemicalReaction"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::TransportWithBiochemicalReaction>(*it)));
			}

			else if (boost::iequals(type,"UnificationXref"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::UnificationXref>(*it)));
			}
			//			else if (boost::iequals(type,"UtilityClass"))
			//			{
			//				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::UtilityClass>(*it)));
			//			}
			else if (boost::iequals(type,"Xref"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Xref>(*it)));
			}

			// EXT:
			else if (boost::iequals(type,"AlgebraicRule"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::AlgebraicRule>(*it)));
			}
			else if (boost::iequals(type,"AssignmentRule"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::AssignmentRule>(*it)));
			}
			else if (boost::iequals(type,"Constraint"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Constraint>(*it)));
			}
			else if (boost::iequals(type,"Delay"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Delay>(*it)));
			}
			else if (boost::iequals(type,"EventAssignment"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::EventAssignment>(*it)));
			}
			else if (boost::iequals(type,"Experiment"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Experiment>(*it)));
			}
			else if (boost::iequals(type,"FunctionDefinition"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::FunctionDefinition>(*it)));
			}
			else if (boost::iequals(type,"IdMapping"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::IdMapping>(*it)));
			}
			else if (boost::iequals(type,"ImportSource"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::ImportSource>(*it)));
			}
			else if (boost::iequals(type,"InitialAssignment"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::InitialAssignment>(*it)));
			}
			else if (boost::iequals(type,"KineticLaw"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::KineticLaw>(*it)));
			}
			else if (boost::iequals(type,"LocalParameter"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::LocalParameter>(*it)));
			}
			else if (boost::iequals(type,"Math"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Math>(*it)));
			}
			else if (boost::iequals(type,"Model"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Model>(*it)));
			}
			else if (boost::iequals(type,"Parameter"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Parameter>(*it)));
			}
			else if (boost::iequals(type,"Priority"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Priority>(*it)));
			}
			else if (boost::iequals(type,"RateRule"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::RateRule>(*it)));
			}
			else if (boost::iequals(type,"ResultObject"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::ResultObject>(*it)));
			}
			else if (boost::iequals(type,"Rule"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Rule>(*it)));
			}
			else if (boost::iequals(type,"Sample"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Sample>(*it)));
			}
//			else if (boost::iequals(type,"SBase"))
//			{
//				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::SBase>(*it)));
//			}
			else if (boost::iequals(type,"Series"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Series>(*it)));
			}
			else if (boost::iequals(type,"Trigger"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Trigger>(*it)));
			}
//			else if (boost::iequals(type,"UPBase"))
//			{
//				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::UPBase>(*it)));
//			}
			else if (boost::iequals(type,"Unit"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::Unit>(*it)));
			}
			else if (boost::iequals(type,"UnitDefinition"))
			{
				objects.push_back(boost::dynamic_pointer_cast<UniPAX::UPBase>(database->load<UniPAX::UnitDefinition>(*it)));
			}
		}
		t.commit();
	}
	catch (const odb::exception& e)
	{
		std::cerr << "MySQLManager::getObjectByID: odb_exception - " << e.what() << std::endl;
	}


}

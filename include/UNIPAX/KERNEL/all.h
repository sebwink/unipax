/*
 * All.h
 *
 *  Created on: Jun 9, 2011
 *      Author: gerasch
 */

#ifndef ALL_H_
#define ALL_H_

#include <UNIPAX/KERNEL/ClassType.h>

#include <UNIPAX/KERNEL/BIOPAX/BindingFeature.h>
#include <UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include <UNIPAX/KERNEL/BIOPAX/BiochemicalPathwayStep.h>
#include <UNIPAX/KERNEL/BIOPAX/BiochemicalReaction.h>
#include <UNIPAX/KERNEL/BIOPAX/Catalysis.h>
#include <UNIPAX/KERNEL/BIOPAX/CellVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/CellularLocationVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/ChemicalStructure.h>
#include <UNIPAX/KERNEL/BIOPAX/Complex.h>
#include <UNIPAX/KERNEL/BIOPAX/ComplexAssembly.h>
#include <UNIPAX/KERNEL/BIOPAX/Control.h>
#include <UNIPAX/KERNEL/BIOPAX/ControlledVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/Conversion.h>
#include <UNIPAX/KERNEL/BIOPAX/CovalentBindingFeature.h>
#include <UNIPAX/KERNEL/BIOPAX/Degradation.h>
#include <UNIPAX/KERNEL/BIOPAX/DeltaG.h>
#include <UNIPAX/KERNEL/BIOPAX/Dna.h>
#include <UNIPAX/KERNEL/BIOPAX/DnaReference.h>
#include <UNIPAX/KERNEL/BIOPAX/DnaRegion.h>
#include <UNIPAX/KERNEL/BIOPAX/DnaRegionReference.h>
#include <UNIPAX/KERNEL/BIOPAX/Entity.h>
#include <UNIPAX/KERNEL/BIOPAX/EntityFeature.h>
#include <UNIPAX/KERNEL/BIOPAX/EntityReference.h>
#include <UNIPAX/KERNEL/BIOPAX/EntityReferenceTypeVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/Evidence.h>
#include <UNIPAX/KERNEL/BIOPAX/EvidenceCodeVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/ExperimentalForm.h>
#include <UNIPAX/KERNEL/BIOPAX/ExperimentalFormVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/FragmentFeature.h>
#include <UNIPAX/KERNEL/BIOPAX/Gene.h>
#include <UNIPAX/KERNEL/BIOPAX/GeneticInteraction.h>
#include <UNIPAX/KERNEL/BIOPAX/Interaction.h>
#include <UNIPAX/KERNEL/BIOPAX/InteractionVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/KPrime.h>
#include <UNIPAX/KERNEL/BIOPAX/ModificationFeature.h>
#include <UNIPAX/KERNEL/BIOPAX/Modulation.h>
#include <UNIPAX/KERNEL/BIOPAX/MolecularInteraction.h>
#include <UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include <UNIPAX/KERNEL/BIOPAX/PathwayStep.h>
#include <UNIPAX/KERNEL/BIOPAX/PhenotypeVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include <UNIPAX/KERNEL/BIOPAX/Protein.h>
#include <UNIPAX/KERNEL/BIOPAX/ProteinReference.h>
#include <UNIPAX/KERNEL/BIOPAX/Provenance.h>
#include <UNIPAX/KERNEL/BIOPAX/PublicationXref.h>
#include <UNIPAX/KERNEL/BIOPAX/RelationshipTypeVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/RelationshipXref.h>
#include <UNIPAX/KERNEL/BIOPAX/Rna.h>
#include <UNIPAX/KERNEL/BIOPAX/RnaReference.h>
#include <UNIPAX/KERNEL/BIOPAX/RnaRegion.h>
#include <UNIPAX/KERNEL/BIOPAX/RnaRegionReference.h>
#include <UNIPAX/KERNEL/BIOPAX/Score.h>
#include <UNIPAX/KERNEL/BIOPAX/SequenceInterval.h>
#include <UNIPAX/KERNEL/BIOPAX/SequenceLocation.h>
#include <UNIPAX/KERNEL/BIOPAX/SequenceModificationVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/SequenceRegionVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/SequenceSite.h>
#include <UNIPAX/KERNEL/BIOPAX/SmallMolecule.h>
#include <UNIPAX/KERNEL/BIOPAX/SmallMoleculeReference.h>
#include <UNIPAX/KERNEL/BIOPAX/Stoichiometry.h>
#include <UNIPAX/KERNEL/BIOPAX/TemplateReaction.h>
#include <UNIPAX/KERNEL/BIOPAX/TemplateReactionRegulation.h>
#include <UNIPAX/KERNEL/BIOPAX/Thing.h>
#include <UNIPAX/KERNEL/BIOPAX/TissueVocabulary.h>
#include <UNIPAX/KERNEL/BIOPAX/Transport.h>
#include <UNIPAX/KERNEL/BIOPAX/TransportWithBiochemicalReaction.h>
#include <UNIPAX/KERNEL/BIOPAX/UnificationXref.h>
#include <UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include <UNIPAX/KERNEL/BIOPAX/Xref.h>

#include <UNIPAX/KERNEL/EXT/AlgebraicRule.h>
#include <UNIPAX/KERNEL/EXT/AssignmentRule.h>
#include <UNIPAX/KERNEL/EXT/Constraint.h>
#include <UNIPAX/KERNEL/EXT/Delay.h>
#include <UNIPAX/KERNEL/EXT/Event.h>
#include <UNIPAX/KERNEL/EXT/EventAssignment.h>
#include <UNIPAX/KERNEL/EXT/Experiment.h>
#include <UNIPAX/KERNEL/EXT/FunctionDefinition.h>
#include <UNIPAX/KERNEL/EXT/IdMapping.h>
#include <UNIPAX/KERNEL/EXT/ImportSource.h>
#include <UNIPAX/KERNEL/EXT/InitialAssignment.h>
#include <UNIPAX/KERNEL/EXT/KineticLaw.h>
#include <UNIPAX/KERNEL/EXT/LocalParameter.h>
#include <UNIPAX/KERNEL/EXT/Math.h>
#include <UNIPAX/KERNEL/EXT/Model.h>
#include <UNIPAX/KERNEL/EXT/Parameter.h>
#include <UNIPAX/KERNEL/EXT/Priority.h>
#include <UNIPAX/KERNEL/EXT/RateRule.h>
#include <UNIPAX/KERNEL/EXT/ResultObject.h>
#include <UNIPAX/KERNEL/EXT/Rule.h>
#include <UNIPAX/KERNEL/EXT/SBase.h>
#include <UNIPAX/KERNEL/EXT/Sample.h>
#include <UNIPAX/KERNEL/EXT/SampleData.h>
#include <UNIPAX/KERNEL/EXT/Series.h>
#include <UNIPAX/KERNEL/EXT/Trigger.h>
#include <UNIPAX/KERNEL/EXT/UIBase.h>
#include <UNIPAX/KERNEL/EXT/UPBase.h>
#include <UNIPAX/KERNEL/EXT/Unit.h>
#include <UNIPAX/KERNEL/EXT/UnitDefinition.h>

#include <map>
#include <string>

namespace UniPAX {

struct ObjectFactory
{
	static boost::shared_ptr<UPBase> getInstance(int type)
										{
		switch (type)
		{
		case ClassType::idAlgebraicRule:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<AlgebraicRule>::type(new AlgebraicRule()));
		case ClassType::idAssignmentRule:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<AssignmentRule>::type(new AssignmentRule()));
		case ClassType::idBindingFeature:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<BindingFeature>::type(new BindingFeature()));
		case ClassType::idBiochemicalPathwayStep:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<BiochemicalPathwayStep>::type(new BiochemicalPathwayStep()));
		case ClassType::idBiochemicalReaction:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<BiochemicalReaction>::type(new BiochemicalReaction()));
		case ClassType::idBioSource:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<BioSource>::type(new BioSource()));
		case ClassType::idCatalysis:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Catalysis>::type(new Catalysis()));
		case ClassType::idCellularLocationVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<CellularLocationVocabulary>::type(new CellularLocationVocabulary()));
		case ClassType::idCellVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<CellVocabulary>::type(new CellVocabulary()));
		case ClassType::idChemicalStructure:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<ChemicalStructure>::type(new ChemicalStructure()));
		case ClassType::idComplex:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Complex>::type(new Complex()));
		case ClassType::idComplexAssembly:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<ComplexAssembly>::type(new ComplexAssembly()));
		case ClassType::idConstraint:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Constraint>::type(new Constraint()));
		case ClassType::idControl:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Control>::type(new Control()));
		case ClassType::idControlledVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<ControlledVocabulary>::type(new ControlledVocabulary()));
		case ClassType::idConversion:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Conversion>::type(new Conversion()));
		case ClassType::idCovalentBindingFeature:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<CovalentBindingFeature>::type(new CovalentBindingFeature()));
		case ClassType::idDegradation:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Degradation>::type(new Degradation()));
		case ClassType::idDelay:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Delay>::type(new Delay()));
		case ClassType::idDeltaG:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<DeltaG>::type(new DeltaG()));
		case ClassType::idDna:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Dna>::type(new Dna()));
		case ClassType::idDnaReference:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<DnaReference>::type(new DnaReference()));
		case ClassType::idDnaRegion:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<DnaRegion>::type(new DnaRegion()));
		case ClassType::idDnaRegionReference:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<DnaRegionReference>::type(new DnaRegionReference()));
		case ClassType::idEntity:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Entity>::type(new Entity()));
		case ClassType::idEntityFeature:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<EntityFeature>::type(new EntityFeature()));
		case ClassType::idEntityReference:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<EntityReference>::type(new EntityReference()));
		case ClassType::idEntityReferenceTypeVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<EntityReferenceTypeVocabulary>::type(new EntityReferenceTypeVocabulary()));
		case ClassType::idEvent:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Event>::type(new Event()));
		case ClassType::idEventAssignment:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<EventAssignment>::type(new EventAssignment()));
		case ClassType::idEvidence:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Evidence>::type(new Evidence()));
		case ClassType::idEvidenceCodeVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<EvidenceCodeVocabulary>::type(new EvidenceCodeVocabulary()));
		case ClassType::idExperiment:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Experiment>::type(new Experiment()));
		case ClassType::idExperimentalForm:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<ExperimentalForm>::type(new ExperimentalForm()));
		case ClassType::idExperimentalFormVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<ExperimentalFormVocabulary>::type(new ExperimentalFormVocabulary()));
		case ClassType::idFragmentFeature:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<FragmentFeature>::type(new FragmentFeature()));
		case ClassType::idFunctionDefinition:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<FunctionDefinition>::type(new FunctionDefinition()));
		case ClassType::idGene:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Gene>::type(new Gene()));
		case ClassType::idGeneticInteraction:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<GeneticInteraction>::type(new GeneticInteraction()));
		case ClassType::idIdMapping:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<IdMapping>::type(new IdMapping()));
		case ClassType::idImportSource:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<ImportSource>::type(new ImportSource()));
		case ClassType::idInitialAssignment:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<InitialAssignment>::type(new InitialAssignment()));
		case ClassType::idInteraction:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Interaction>::type(new Interaction()));
		case ClassType::idInteractionVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<InteractionVocabulary>::type(new InteractionVocabulary()));
		case ClassType::idKineticLaw:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<KineticLaw>::type(new KineticLaw()));
		case ClassType::idKPrime:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<KPrime>::type(new KPrime()));
		case ClassType::idLocalParameter:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<LocalParameter>::type(new LocalParameter()));
		case ClassType::idMath:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Math>::type(new Math()));
		case ClassType::idModel:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Model>::type(new Model()));
		case ClassType::idModificationFeature:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<ModificationFeature>::type(new ModificationFeature()));
		case ClassType::idModulation:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Modulation>::type(new Modulation()));
		case ClassType::idMolecularInteraction:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<MolecularInteraction>::type(new MolecularInteraction()));
		case ClassType::idParameter:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Parameter>::type(new Parameter()));
		case ClassType::idPathway:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Pathway>::type(new Pathway()));
		case ClassType::idPathwayStep:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<PathwayStep>::type(new PathwayStep()));
		case ClassType::idPhenotypeVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<PhenotypeVocabulary>::type(new PhenotypeVocabulary()));
		case ClassType::idPhysicalEntity:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<PhysicalEntity>::type(new PhysicalEntity()));
		case ClassType::idPriority:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Priority>::type(new Priority()));
		case ClassType::idProtein:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Protein>::type(new Protein()));
		case ClassType::idProteinReference:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<ProteinReference>::type(new ProteinReference()));
		case ClassType::idProvenance:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Provenance>::type(new Provenance()));
		case ClassType::idPublicationXref:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<PublicationXref>::type(new PublicationXref()));
		case ClassType::idRateRule:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<RateRule>::type(new RateRule()));
		case ClassType::idRelationshipTypeVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<RelationshipTypeVocabulary>::type(new RelationshipTypeVocabulary()));
		case ClassType::idRelationshipXref:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<RelationshipXref>::type(new RelationshipXref()));
		case ClassType::idResultObject:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<ResultObject>::type(new ResultObject()));
		case ClassType::idRna:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Rna>::type(new Rna()));
		case ClassType::idRnaReference:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<RnaReference>::type(new RnaReference()));
		case ClassType::idRnaRegion:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<RnaRegion>::type(new RnaRegion()));
		case ClassType::idRnaRegionReference:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<RnaRegionReference>::type(new RnaRegionReference()));
		case ClassType::idRule:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Rule>::type(new Rule()));
		case ClassType::idSample:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Sample>::type(new Sample()));
//		case ClassType::idSBase:
//			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<SBase>::type(new SBase()));
		case ClassType::idScore:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Score>::type(new Score()));
		case ClassType::idSequenceInterval:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<SequenceInterval>::type(new SequenceInterval()));
		case ClassType::idSequenceLocation:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<SequenceLocation>::type(new SequenceLocation()));
		case ClassType::idSequenceModificationVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<SequenceModificationVocabulary>::type(new SequenceModificationVocabulary()));
		case ClassType::idSequenceRegionVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<SequenceRegionVocabulary>::type(new SequenceRegionVocabulary()));
		case ClassType::idSequenceSite:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<SequenceSite>::type(new SequenceSite()));
		case ClassType::idSeries:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Series>::type(new Series()));
		case ClassType::idSmallMolecule:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<SmallMolecule>::type(new SmallMolecule()));
		case ClassType::idSmallMoleculeReference:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<SmallMoleculeReference>::type(new SmallMoleculeReference()));
		case ClassType::idStoichiometry:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Stoichiometry>::type(new Stoichiometry()));
		case ClassType::idTemplateReaction:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<TemplateReaction>::type(new TemplateReaction()));
		case ClassType::idTemplateReactionRegulation:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<TemplateReactionRegulation>::type(new TemplateReactionRegulation()));
//		case ClassType::idThing:
//			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Thing>::type(new Thing()));
		case ClassType::idTissueVocabulary:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<TissueVocabulary>::type(new TissueVocabulary()));
		case ClassType::idTransport:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Transport>::type(new Transport()));
		case ClassType::idTransportWithBiochemicalReaction:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<TransportWithBiochemicalReaction>::type(new TransportWithBiochemicalReaction()));
		case ClassType::idTrigger:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Trigger>::type(new Trigger()));
		case ClassType::idUnificationXref:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<UnificationXref>::type(new UnificationXref()));
		case ClassType::idUnit:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Unit>::type(new Unit()));
		case ClassType::idUnitDefinition:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<UnitDefinition>::type(new UnitDefinition()));
//		case ClassType::idUPBase:
//			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<UPBase>::type(new UPBase()));
//		case ClassType::idUtilityClass:
//			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<UtilityClass>::type(new UtilityClass()));
		case ClassType::idXref:
			return boost::dynamic_pointer_cast<UPBase>(UnipaxPtr<Xref>::type(new Xref()));
		default:
			throw std::runtime_error("Unknown ClassType" + type);
		}
										}
};

} // end namespace UniPAX

#endif /* ALL_H_ */

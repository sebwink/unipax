/*
 * ClassType.h
 *
 *  Created on: Jan 10, 2013
 *      Author: niermann
 */

#ifndef CLASSTYPE_H_
#define CLASSTYPE_H_

namespace UniPAX
{

namespace ClassType
{

// BioPAX classes
enum ID {
	idBindingFeature,
	idBioSource,
	idBiochemicalPathwayStep,
	idBiochemicalReaction,
	idCatalysis,
	idCellVocabulary,
	idCellularLocationVocabulary,
	idChemicalStructure,
	idComplex,
	idComplexAssembly,
	idControl,
	idControlledVocabulary,
	idConversion,
	idCovalentBindingFeature,
	idDegradation,
	idDeltaG,
	idDna,
	idDnaReference,
	idDnaRegion,
	idDnaRegionReference,
	idEntity,
	idEntityFeature,
	idEntityReference,
	idEntityReferenceTypeVocabulary,
	idEvidence,
	idEvidenceCodeVocabulary,
	idExperimentalForm,
	idExperimentalFormVocabulary,
	idFragmentFeature,
	idGene,
	idGeneticInteraction,
	idInteraction,
	idInteractionVocabulary,
	idKPrime,
	idModificationFeature,
	idModulation,
	idMolecularInteraction,
	idPathway,
	idPathwayStep,
	idPhenotypeVocabulary,
	idPhysicalEntity,
	idProtein,
	idProteinReference,
	idProvenance,
	idPublicationXref,
	idRelationshipTypeVocabulary,
	idRelationshipXref,
	idRna,
	idRnaReference,
	idRnaRegion,
	idRnaRegionReference,
	idScore,
	idSequenceInterval,
	idSequenceLocation,
	idSequenceModificationVocabulary,
	idSequenceRegionVocabulary,
	idSequenceSite,
	idSmallMolecule,
	idSmallMoleculeReference,
	idStoichiometry,
	idTemplateReaction,
	idTemplateReactionRegulation,
//	idThing,
	idTissueVocabulary,
	idTransport,
	idTransportWithBiochemicalReaction,
	idUnificationXref,
//	idUtilityClass,
	idXref,
	// EXT classes
	idAlgebraicRule,
	idAssignmentRule,
	idConstraint,
	idDelay,
	idEvent,
	idEventAssignment,
	idExperiment,
	idFunctionDefinition,
	idIdMapping,
	idImportSource,
	idInitialAssignment,
	idKineticLaw,
	idLocalParameter,
	idMath,
	idModel,
	idParameter,
	idPriority,
	idRateRule,
	idResultObject,
	idRule,
	idSample,
//	idSBase,
	idSeries,
	idTrigger,
	idUnit,
	idUnitDefinition,
//	idUPBase,
	idSampleData,
	END_ENUM
}; // end enum



} // end namespace ClassType
} // end namespace UniPAX

#endif // CLASSTYPE_H_

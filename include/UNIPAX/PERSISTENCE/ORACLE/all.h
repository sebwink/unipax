/*
 * All-odb.hxx
 *
 *  Created on: Jun 29, 2011
 *      Author: kuentzer
 */

#ifndef ALL_ODB_ORACLE_H_
#define ALL_ODB_ORACLE_H_

#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/BindingFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/BioSource-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/BiochemicalPathwayStep-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/BiochemicalReaction-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Catalysis-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/CellVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/CellularLocationVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ChemicalStructure-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Complex-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ComplexAssembly-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Control-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ControlledVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Conversion-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/CovalentBindingFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Degradation-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/DeltaG-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Dna-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/DnaReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/DnaRegion-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/DnaRegionReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Entity-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/EntityFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/EntityReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/EntityReferenceTypeVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Evidence-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/EvidenceCodeVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ExperimentalForm-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ExperimentalFormVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/FragmentFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Gene-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/GeneticInteraction-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Interaction-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/InteractionVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/KPrime-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ModificationFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Modulation-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/MolecularInteraction-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Pathway-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/PathwayStep-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/PhenotypeVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/PhysicalEntity-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Protein-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/ProteinReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Provenance-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/PublicationXref-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/RelationshipTypeVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/RelationshipXref-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Rna-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/RnaReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/RnaRegion-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/RnaRegionReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Score-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/SequenceInterval-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/SequenceLocation-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/SequenceModificationVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/SequenceRegionVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/SequenceSite-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/SmallMolecule-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/SmallMoleculeReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Stoichiometry-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/TemplateReaction-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/TemplateReactionRegulation-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Thing-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/TissueVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Transport-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/TransportWithBiochemicalReaction-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/UnificationXref-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/UtilityClass-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/BIOPAX/Xref-odb.hxx>

#include <UNIPAX/PERSISTENCE/ORACLE/EXT/AlgebraicRule-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/AssignmentRule-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Constraint-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Delay-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Event-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/EventAssignment-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Experiment-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/FunctionDefinition-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/ImportSource-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/InitialAssignment-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/KineticLaw-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/LocalParameter-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Mapping-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Math-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Model-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Parameter-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Priority-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/RateRule-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Rule-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/SBase-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Sample-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Trigger-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/UPBase-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/UIBase-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/Unit-odb.hxx>
#include <UNIPAX/PERSISTENCE/ORACLE/EXT/UnitDefinition-odb.hxx>



#endif /* ALL_ODB_ORACLE_H_ */
